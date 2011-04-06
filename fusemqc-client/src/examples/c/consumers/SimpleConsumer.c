/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <cms.h>
#include <CMS_ConnectionFactory.h>
#include <CMS_Connection.h>
#include <CMS_Session.h>
#include <CMS_Message.h>
#include <CMS_TextMessage.h>
#include <CMS_MessageConsumer.h>
#include <CMS_MessageProducer.h>
#include <CMS_Destination.h>

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]) {

    cms_initialize();

    printf("=====================================================\n");
    printf("Starting the SimpleConsumer:\n");
    printf("-----------------------------------------------------\n");

    const char* brokerUri = "failover:(tcp://127.0.0.1:61616)";
    const char* queueName = "cms.test.c.client.queue";

    CMS_ConnectionFactory* factory = NULL;
    CMS_Connection* connection = NULL;
    CMS_Session* session = NULL;
    CMS_Destination* destination = NULL;
    CMS_MessageConsumer* consumer = NULL;

    if (cms_createConnectionFactory(&factory, brokerUri, NULL, NULL) != CMS_SUCCESS) {
        printf("Failed to create a Connection Factory\n");
        exit(1);
    }

    if (cms_createDefaultConnection(factory, &connection) != CMS_SUCCESS) {
        printf("Failed to create a Connection\n");
        exit(1);
    }

    cms_destroyConnectionFactory(factory);

    if (cms_createDefaultSession(connection, &session) != CMS_SUCCESS) {
        printf("Failed to create a Session\n");
        exit(1);
    }

    if (cms_createDestination(session, CMS_QUEUE, queueName, &destination) != CMS_SUCCESS) {
        printf("Failed to create a Destination\n");
        exit(1);
    }

    if (cms_createDefaultConsumer(session, destination, &consumer) != CMS_SUCCESS) {
        printf("Failed to create a MessageConsumer\n");
        exit(1);
    }

    if (cms_startConnection(connection) != CMS_SUCCESS) {
        printf("Failed to start the Connection\n");
        exit(1);
    }

    for(;;) {
        CMS_Message* message = NULL;
        if (cms_consumerReceive(consumer, &message) != CMS_SUCCESS) {
            printf("Error while waiting for next message to arrive.");
            exit(1);
        }

        int result = 0;
        cms_messagePropertyExists(message, "terminate", &result);

        if(result > 0) {
            cms_destroyMessage(message);
            break;
        }

        int type = -1;

        cms_getMessageType(message, &type);

        if(type == CMS_TEXT_MESSAGE) {
            char text[256];
            text[255] = 0;
            int numProperties = 0;

            if(cms_getMessageText(message, text, 256) == CMS_ERROR) {
                printf("Error while retrieving text from Message.\n");
                exit(1);
            }

            cms_getNumMessageProperties(message, &numProperties);

            printf("Text Message body contained the string: %s, and %d properties.\n", text, numProperties);
        } else {
            printf("Received some other type of message.\n");
        }

        cms_destroyMessage(message);
    }

    cms_destroyConsumer(consumer);
    cms_destroyDestination(destination);
    cms_destroySession(session);
    cms_destroyConnection(connection);

    printf("-----------------------------------------------------\n");
    printf("Finished with the SimpleConsumer.\n");
    printf("=====================================================\n");

    cms_terminate();
}
