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
#include <CMS_MessageProducer.h>
#include <CMS_Destination.h>

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]) {

    cms_initialize();

    printf("=====================================================\n");
    printf("Starting the SimpleProducer:\n");
    printf("-----------------------------------------------------\n");

    const char* brokerUri = "failover:(tcp://127.0.0.1:61616)";
    const char* queueName = "cms.test.c.client.queue";

    CMS_ConnectionFactory* factory = NULL;
    CMS_Connection* connection = NULL;
    CMS_Session* session = NULL;
    CMS_Destination* destination = NULL;
    CMS_MessageProducer* producer = NULL;
    CMS_Message* txtMessage = NULL;

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

    if (cms_createProducer(session, destination, &producer) != CMS_SUCCESS) {
        printf("Failed to create a MessageProducer\n");
        exit(1);
    }

    int i = 0;
    for(; i < 10; ++i) {
        CMS_Message* message = NULL;
        cms_createTextMessage(session, &message, "Test Message Body");

        // Give the receiver a hint that we didn't encode the message body as UTF-8 etc.
        cms_setCMSMessageType(message, "text/plain");

        // Set some sample properties
        cms_setMessageIntProperty(message, "SequenceId", i);
        cms_setMessageStringProperty(message, "MyStringKey", "Something Important");

        if (cms_producerSendWithDefaults(producer, message) != CMS_SUCCESS) {
            printf("Failed to send the Message\n");
            cms_destroyMessage(message);
            exit(1);
        }

        printf("Sent Message number: %d\n", i+1);

        cms_destroyMessage(message);
    }

    CMS_Message* terminus = NULL;
    cms_createMessage(session, &terminus);
    cms_setMessageBooleanProperty(terminus, "terminate", 1);

    if(cms_producerSendWithDefaults(producer, terminus) == CMS_ERROR) {
        printf("Error while attempting to send the terminus message\n");
        exit(1);
    }

    cms_destroyMessage(terminus);

    if (cms_startConnection(connection) != CMS_SUCCESS) {
        printf("Failed to start the Connection\n");
        exit(1);
    }

    cms_destroyProducer(producer);
    cms_destroyDestination(destination);
    cms_destroySession(session);
    cms_destroyConnection(connection);

    printf("-----------------------------------------------------\n");
    printf("Finished with the SimpleProducer.\n");
    printf("=====================================================\n");

    cms_terminate();
}
