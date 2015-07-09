/*******************************************************************************
* Copyright (c) 2014 Qualcomm Technologies, Inc.  All Rights Reserved.
* Qualcomm Technologies Proprietary and Confidential.
*******************************************************************************/

#include <pthread.h>
#include <string>
#include <errno.h>
#include <string.h>

#include "mmcam_socket_utils.h"
#include "eztune_protocol.h"
#include "eztune_process.h"
#include "eztune_interface.h"

#ifdef _ANDROID_
#include <log/log.h>
#endif
#include "mmcam_log_utils.h"

using mmcam_utils::ServerSocket;
using mmcam_utils::PrintByteStream;
using std::string;

namespace eztune {
const char kStopString [] = "Stop!";
const uint32_t kControlPort = 55555;
const uint32_t kPreviewPort = 55556;

class EztuneInterface {
public:
    static void *RunThreadWrapper(void *ptr)
    {
        EztuneInterface *obj = static_cast<EztuneInterface *>(ptr);

        obj->RunThread();
        return  NULL;
    }

    void RunThread()
    {
        // Create the socket
        ServerSocket server (m_port, m_pipefds[0]);
        m_running = true;

        while (true) {

            bool pipeflag;
            ServerSocket new_sock;

            MMCAM_LOGI("Server: Waiting on new connection...\n");

            int rc = server.accept(new_sock, pipeflag);

            if (rc < 0) {
                MMCAM_LOGE("Socket accept error. Return value = %d", rc);
                goto end;
            }

            if (pipeflag == true) {
                MMCAM_LOGW("Stop message. Exiting server thread");
                goto end;
            }

            MMCAM_LOGI("Server: Connected to new client...");

            if (m_port == kControlPort) {
                m_protocol.Init(EZTUNE_SERVER_CONTROL);
                m_engine->Init(EZTUNE_SERVER_CONTROL);
            } else {
                m_protocol.Init(EZTUNE_SERVER_PREVIEW);
                m_engine->Init(EZTUNE_SERVER_PREVIEW);
            }

            // Ack every new connection immediately
            size_t response_size;
            m_protocol.GenerateAcceptAck(m_response, response_size);

            PrintByteStream(m_response, response_size, "Server: Sending connection response: ");

            if (response_size)
                new_sock.send(m_response, response_size);

            MMCAM_ASSERT(m_engine != NULL, "Client pointer not set, so engine is null");

            while (true) {
                bool payload_received;
                uint16_t cmd;
                size_t payload_size;
                size_t response_size;

                //Get next data size to read from protocol and read requested size from socket
                size_t size;
                m_protocol.NextProcessDataSize(size);

                bool rc = new_sock.recv(m_data, size, pipeflag);

                /* if buffer size is non-zero, run through protocol first to see
                   if payload is received, if yes, pass the data to engine to
                   generate a response. If data size is zero, it means connection
                   reset, so reset protocol, reset engine and wait for new connection
                */
                if (rc == true) {
                    //for debug
                    PrintByteStream(m_data, size, "Server: New message: ");

                    m_protocol.ProcessData(m_data, size, payload_received);

                    if (payload_received) {

                        m_protocol.GenerateCommandAck(m_response, response_size);

                        if (response_size)
                            new_sock.send(m_response, response_size);

                        //reuse data buffer as payload as input data is already parsed
                        string &payload = m_data;

                        m_protocol.GetPayloadInfo(cmd, payload, payload_size, response_size);

                        bool done;
                        do {
                            done = m_engine->ProcessAndGenerateResponse(cmd, payload_size, payload, response_size, m_response);

                            //send data is response size is > 0
                            if (response_size)
                                new_sock.send(m_response, response_size);
                        } while (done == false);
                    }

                } else {

                    if (pipeflag == true) {
                        MMCAM_LOGW("Stop message. Exiting server thread");
                        //De-init skipped as camera is exiting
                        goto end;
                    }

                    //Reset protocol state
                    m_protocol.DeInit();
                    //De-Init engine
                    m_engine->DeInit();

                    MMCAM_LOGW("Client connection lost");
                    //break from inner loop and wait for new clients
                    break;
                }
            }
        }
end:
        m_running = false;
        return;
    }

    bool Run()
    {
        int rc = true;

        //create a pipe to communicate with server thread listening on socket
        int val = pipe(m_pipefds);
        MMCAM_ASSERT(val == 0, "Pipe creation failed: %s", strerror(errno));

        //create server thread
        val = pthread_create(&m_server_thread, NULL, EztuneInterface::RunThreadWrapper, static_cast<void *>(this));
        MMCAM_ASSERT(val == 0, "Thread creation failed: %s", strerror(errno));

        return rc;
    }

    static EztuneInterface *GetInstance(uint32_t port)
    {
        MMCAM_ASSERT(port == kControlPort || port == kPreviewPort, "Wrong port");
        EztuneInterface *instance;

        Lock();
        // Create only if not existing
        if (kControlPort == port) {
            if (!m_control_instance)
                m_control_instance = new EztuneInterface(kControlPort);

            instance = m_control_instance;
        } else {
            if (!m_preview_instance)
                m_preview_instance = new EztuneInterface(kPreviewPort);

            instance = m_preview_instance;
        }
        UnLock();

        return instance;
    }

    void SetClient(void *client)
    {
        m_client = client;
        m_engine = new eztune::ProcessLayer(client);
    }

    void Stop()
    {
        if (m_running == true) {
            int val = write(m_pipefds[1], eztune::kStopString, (strlen(eztune::kStopString) + 1));
            MMCAM_ASSERT(val != -1, "Write to pipe failed, write returned: %s", strerror(errno));

            val = pthread_join(m_server_thread, NULL);
            MMCAM_ASSERT(val == 0, "pthread join returned error: %s", strerror(errno));

            close(m_pipefds[0]);
            close(m_pipefds[1]);
        } else {
            MMCAM_LOGV("Instance not running. Stop just deletes instance");
        }

        //delete processing engine when the client exits
        delete m_engine;
    }

    void EventNotify(uint32_t type, void *data)
    {
        if (m_running == true) {
            m_engine->EventNotify(type, data);
        } else {
            MMCAM_LOGV("Instance not running. Event skipped");
        }
    }

    ~EztuneInterface()
    {
        if (this == m_control_instance)
            m_control_instance = NULL;
        else
            m_preview_instance = NULL;
    }

    static EztuneInterface *m_control_instance;
    static EztuneInterface *m_preview_instance;

    static int Lock()
    {
        return pthread_mutex_lock(&m_lock);
    }

    static int UnLock()
    {
        return pthread_mutex_unlock(&m_lock);
    }

private:
    static pthread_mutex_t m_lock;

    EztuneInterface(uint32_t port):
        m_port(port),
        m_protocol(eztune::kMaxProtocolBufferSize)
    {
        m_data.reserve(eztune::kMaxProtocolBufferSize);
        m_response.reserve(eztune::kMaxProtocolBufferSize);

        m_engine = NULL;
        m_client = NULL;

        m_running = false;
    }

    //avoid accidental copies
    EztuneInterface(EztuneInterface const &); // Don't Implement
    void operator=(EztuneInterface const &); // Don't implement

    void *m_client;
    pthread_t m_server_thread;
    string m_data, m_response;
    uint32_t m_port;
    bool m_running;

    ServerSocket m_server;
    eztune::ProtocolLayer m_protocol;
    eztune::ProcessLayer *m_engine;

    int m_pipefds[2];
};

};

//initialize class static members
eztune::EztuneInterface *eztune::EztuneInterface::m_control_instance = NULL;
eztune::EztuneInterface *eztune::EztuneInterface::m_preview_instance = NULL;
pthread_mutex_t eztune::EztuneInterface::m_lock = PTHREAD_MUTEX_INITIALIZER;

extern "C" void *eztune_create_server(void *client, eztune_server_t type)
{
    eztune::EztuneInterface *obj;

    MMCAM_ASSERT(type == EZTUNE_SERVER_CONTROL || type == EZTUNE_SERVER_PREVIEW, "Wrong server type");

    if (type == EZTUNE_SERVER_CONTROL)
        obj = eztune::EztuneInterface::GetInstance(eztune::kControlPort);
    else
        obj = eztune::EztuneInterface::GetInstance(eztune::kPreviewPort);

    obj->SetClient(client);

    MMCAM_LOGI("Create Server : %p", obj);

    if (obj->Run())
        return obj;
    else
        return NULL;
}

extern "C" void eztune_delete_server(void *handle)
{
    eztune::EztuneInterface::Lock();

    eztune::EztuneInterface *obj = static_cast<eztune::EztuneInterface *> (handle);

    MMCAM_LOGI("Delete Server : %p", obj);

    obj->Stop();

    delete obj;

    eztune::EztuneInterface::UnLock();
}

extern "C" void eztune_notify_server(void *handle, uint32_t type, void *data)
{
    eztune::EztuneInterface::Lock();
    eztune::EztuneInterface *obj = static_cast<eztune::EztuneInterface *> (handle);

    if ((obj == eztune::EztuneInterface::m_control_instance) ||
            (obj == eztune::EztuneInterface::m_preview_instance)) {
        obj->EventNotify(type, data);
    } else {
        MMCAM_LOGI("Object instance do not exist anymore. Event skipped");
    }

    eztune::EztuneInterface::UnLock();
}
