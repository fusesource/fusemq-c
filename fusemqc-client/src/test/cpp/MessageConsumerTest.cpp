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

#include "MessageConsumerTest.h"

#include <cms.h>
#include <CMS_Connection.h>
#include <CMS_Session.h>
#include <CMS_Destination.h>
#include <CMS_TextMessage.h>
#include <CMS_MessageProducer.h>
#include <CMS_MessageConsumer.h>

#include <decaf/lang/Thread.h>

using namespace cms;
using namespace decaf;
using namespace decaf::lang;

////////////////////////////////////////////////////////////////////////////////
MessageConsumerTest::MessageConsumerTest() {
}

////////////////////////////////////////////////////////////////////////////////
MessageConsumerTest::~MessageConsumerTest() {
}

////////////////////////////////////////////////////////////////////////////////
void MessageConsumerTest::testCreateConsumer() {

    CMS_Destination* destination = NULL;
    CMS_MessageConsumer* consumer = NULL;

    CPPUNIT_ASSERT(cms_createTemporaryDestination(session, CMS_TEMPORARY_TOPIC, &destination) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_createDefaultConsumer(session, destination, &consumer) == CMS_SUCCESS);

    char* selector = new char[256];
    CPPUNIT_ASSERT(cms_getConsumerMessageSelector(consumer, selector, 256) == CMS_SUCCESS);
    CPPUNIT_ASSERT(std::string("") == std::string(selector));
    delete [] selector;

    CPPUNIT_ASSERT(cms_destroyConsumer(consumer) == CMS_SUCCESS);

    cms_destroyDestination(destination);
}

////////////////////////////////////////////////////////////////////////////////
void MessageConsumerTest::testAutoAckConsumerReceive() {

    CMS_Destination* destination = NULL;
    CMS_Message* message = NULL;
    CMS_MessageConsumer* consumer = NULL;
    CMS_MessageProducer* producer = NULL;

    cms_createTemporaryDestination(session, CMS_TEMPORARY_TOPIC, &destination);
    cms_createDefaultConsumer(session, destination, &consumer);
    cms_createProducer(session, destination, &producer);
    cms_setProducerDeliveryMode(producer, CMS_MSG_NON_PERSISTENT);

    cms_startConnection(connection);

    cms_createTextMessage(session, &message, NULL);

    for( unsigned int i = 0; i < 256; ++i ) {
        cms_producerSendWithDefaults(producer, message);
    }

    cms_destroyMessage(message);

    for( unsigned int i = 0; i < 256; ++i ) {
        CMS_Message* received = NULL;
        CPPUNIT_ASSERT(cms_consumerReceiveWithTimeout(consumer, &received, 2000) == CMS_SUCCESS);
        cms_destroyMessage(received);
    }

    cms_destroyConsumer(consumer);
    cms_destroyProducer(producer);
    cms_destroyDestination(destination);
}

////////////////////////////////////////////////////////////////////////////////
void MessageConsumerTest::testClientAckConsumerReceive() {

    CMS_Destination* destination = NULL;
    CMS_Message* message = NULL;
    CMS_MessageConsumer* consumer = NULL;
    CMS_MessageProducer* producer = NULL;
    CMS_Session* session = NULL;

    cms_createSession(connection, &session, CMS_CLIENT_ACKNOWLEDGE);

    cms_createTemporaryDestination(session, CMS_TEMPORARY_TOPIC, &destination);
    cms_createDefaultConsumer(session, destination, &consumer);
    cms_createProducer(session, destination, &producer);
    cms_setProducerDeliveryMode(producer, CMS_MSG_NON_PERSISTENT);

    cms_startConnection(connection);

    cms_createTextMessage(session, &message, NULL);

    for( unsigned int i = 0; i < 256; ++i ) {
        cms_producerSendWithDefaults(producer, message);
    }

    cms_destroyMessage(message);

    for( unsigned int i = 0; i < 256; ++i ) {
        CMS_Message* received = NULL;
        CPPUNIT_ASSERT(cms_consumerReceiveWithTimeout(consumer, &received, 2000) == CMS_SUCCESS);
        CPPUNIT_ASSERT(cms_acknowledgeMessage(received) == CMS_SUCCESS);
        cms_destroyMessage(received);
    }

    cms_destroyConsumer(consumer);
    cms_destroyProducer(producer);
    cms_destroyDestination(destination);
    cms_destroySession(session);
}

////////////////////////////////////////////////////////////////////////////////
void MessageConsumerTest::testIndividualAckConsumerReceive() {

    CMS_Destination* destination = NULL;
    CMS_Message* message = NULL;
    CMS_MessageConsumer* consumer = NULL;
    CMS_MessageProducer* producer = NULL;
    CMS_Session* session = NULL;

    cms_createSession(connection, &session, CMS_INDIVIDUAL_ACKNOWLEDGE);

    cms_createTemporaryDestination(session, CMS_TEMPORARY_TOPIC, &destination);
    cms_createDefaultConsumer(session, destination, &consumer);
    cms_createProducer(session, destination, &producer);
    cms_setProducerDeliveryMode(producer, CMS_MSG_NON_PERSISTENT);

    cms_startConnection(connection);

    cms_createTextMessage(session, &message, NULL);

    for( unsigned int i = 0; i < 256; ++i ) {
        cms_producerSendWithDefaults(producer, message);
    }

    cms_destroyMessage(message);

    for( unsigned int i = 0; i < 256; ++i ) {
        CMS_Message* received = NULL;
        CPPUNIT_ASSERT(cms_consumerReceiveWithTimeout(consumer, &received, 2000) == CMS_SUCCESS);
        CPPUNIT_ASSERT(cms_acknowledgeMessage(received) == CMS_SUCCESS);
        cms_destroyMessage(received);
    }

    cms_destroyConsumer(consumer);
    cms_destroyProducer(producer);
    cms_destroyDestination(destination);
    cms_destroySession(session);
}

////////////////////////////////////////////////////////////////////////////////
void MessageConsumerTest::testTransactionRollback() {

    CMS_Destination* destination = NULL;
    CMS_Message* message = NULL;
    CMS_MessageConsumer* consumer = NULL;
    CMS_MessageProducer* producer = NULL;
    CMS_Session* session = NULL;

    cms_createSession(connection, &session, CMS_SESSION_TRANSACTED);

    cms_createTemporaryDestination(session, CMS_TEMPORARY_TOPIC, &destination);
    cms_createDefaultConsumer(session, destination, &consumer);
    cms_createProducer(session, destination, &producer);
    cms_setProducerDeliveryMode(producer, CMS_MSG_NON_PERSISTENT);

    cms_startConnection(connection);

    cms_createTextMessage(session, &message, NULL);

    for( unsigned int i = 0; i < 50; ++i ) {
        cms_producerSendWithDefaults(producer, message);
    }

    cms_destroyMessage(message);

    CPPUNIT_ASSERT(cms_commitSession(session) == CMS_SUCCESS);
    Thread::sleep( 50 );

    for( unsigned int i = 0; i < 50; ++i ) {
        CMS_Message* received = NULL;
        CPPUNIT_ASSERT(cms_consumerReceiveWithTimeout(consumer, &received, 2000) == CMS_SUCCESS);
        cms_destroyMessage(received);
    }

    CPPUNIT_ASSERT(cms_commitSession(session) == CMS_SUCCESS);
    Thread::sleep( 50 );

    cms_createTextMessage(session, &message, NULL);

    for( unsigned int i = 0; i < 50; ++i ) {
        cms_producerSendWithDefaults(producer, message);
    }

    cms_destroyMessage(message);

    CPPUNIT_ASSERT(cms_rollbackSession(session) == CMS_SUCCESS);
    Thread::sleep( 50 );

    cms_createTextMessage(session, &message, NULL);
    cms_producerSendWithDefaults(producer, message);
    cms_destroyMessage(message);

    CPPUNIT_ASSERT(cms_commitSession(session) == CMS_SUCCESS);

    // Wait for the messages to get here
    CMS_Message* received = NULL;
    CPPUNIT_ASSERT(cms_consumerReceiveWithTimeout(consumer, &received, 2000) == CMS_SUCCESS);
    cms_destroyMessage(received);

    cms_createTextMessage(session, &message, NULL);
    cms_producerSendWithDefaults(producer, message);
    cms_destroyMessage(message);

    CPPUNIT_ASSERT(cms_commitSession(session) == CMS_SUCCESS);

    // Wait for the messages to get here
    CPPUNIT_ASSERT(cms_consumerReceiveWithTimeout(consumer, &received, 2000) == CMS_SUCCESS);
    cms_destroyMessage(received);
    CPPUNIT_ASSERT(cms_commitSession(session) == CMS_SUCCESS);
}
