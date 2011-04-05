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

#include "MessageProducerTest.h"

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
MessageProducerTest::MessageProducerTest() {
}

////////////////////////////////////////////////////////////////////////////////
MessageProducerTest::~MessageProducerTest() {
}

////////////////////////////////////////////////////////////////////////////////
void MessageProducerTest::testCreateProducer() {

    CMS_Destination* destination = NULL;
    CMS_MessageProducer* producer = NULL;

    CPPUNIT_ASSERT(cms_createTemporaryDestination(session, CMS_TEMPORARY_TOPIC, &destination) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_createProducer(session, destination, &producer) == CMS_SUCCESS);

    CPPUNIT_ASSERT(cms_destroyProducer(producer) == CMS_SUCCESS);

    cms_destroyDestination(destination);
}

////////////////////////////////////////////////////////////////////////////////
void MessageProducerTest::testGetDeliveryMode() {

    CMS_Destination* destination = NULL;
    CMS_MessageProducer* producer = NULL;
    int mode = -1;

    CPPUNIT_ASSERT(cms_createTemporaryDestination(session, CMS_TEMPORARY_TOPIC, &destination) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_createProducer(session, destination, &producer) == CMS_SUCCESS);

    CPPUNIT_ASSERT(cms_getProducerDeliveryMode(producer, &mode) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL((int)CMS_MSG_PERSISTENT, mode);

    CPPUNIT_ASSERT(cms_setProducerDeliveryMode(producer, CMS_MSG_NON_PERSISTENT) == CMS_SUCCESS);

    CPPUNIT_ASSERT(cms_getProducerDeliveryMode(producer, &mode) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL((int)CMS_MSG_NON_PERSISTENT, mode);

    CPPUNIT_ASSERT(cms_destroyProducer(producer) == CMS_SUCCESS);

    cms_destroyDestination(destination);
}

////////////////////////////////////////////////////////////////////////////////
void MessageProducerTest::testGetDisableTimestamps() {

    CMS_Destination* destination = NULL;
    CMS_MessageProducer* producer = NULL;
    int disable = -1;

    CPPUNIT_ASSERT(cms_createTemporaryDestination(session, CMS_TEMPORARY_TOPIC, &destination) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_createProducer(session, destination, &producer) == CMS_SUCCESS);

    CPPUNIT_ASSERT(cms_getProducerDisableMessageTimeStamp(producer, &disable) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL(0, disable);

    CPPUNIT_ASSERT(cms_setProducerDisableMessageTimeStamp(producer, 1) == CMS_SUCCESS);

    CPPUNIT_ASSERT(cms_getProducerDisableMessageTimeStamp(producer, &disable) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL(1, disable);

    CPPUNIT_ASSERT(cms_destroyProducer(producer) == CMS_SUCCESS);

    cms_destroyDestination(destination);
}

////////////////////////////////////////////////////////////////////////////////
void MessageProducerTest::testGetDisableMessageId() {

    CMS_Destination* destination = NULL;
    CMS_MessageProducer* producer = NULL;
    int disable = -1;

    CPPUNIT_ASSERT(cms_createTemporaryDestination(session, CMS_TEMPORARY_TOPIC, &destination) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_createProducer(session, destination, &producer) == CMS_SUCCESS);

    CPPUNIT_ASSERT(cms_getProducerDisableMessageID(producer, &disable) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL(0, disable);

    CPPUNIT_ASSERT(cms_setProducerDisableMessageID(producer, 1) == CMS_SUCCESS);

    CPPUNIT_ASSERT(cms_getProducerDisableMessageID(producer, &disable) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL(1, disable);

    CPPUNIT_ASSERT(cms_destroyProducer(producer) == CMS_SUCCESS);

    cms_destroyDestination(destination);
}

////////////////////////////////////////////////////////////////////////////////
void MessageProducerTest::testGetPriority() {

    CMS_Destination* destination = NULL;
    CMS_MessageProducer* producer = NULL;
    int priority = -1;

    CPPUNIT_ASSERT(cms_createTemporaryDestination(session, CMS_TEMPORARY_TOPIC, &destination) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_createProducer(session, destination, &producer) == CMS_SUCCESS);

    CPPUNIT_ASSERT(cms_getProducerPriority(producer, &priority) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL(4, priority);

    CPPUNIT_ASSERT(cms_setProducerPriority(producer, 1) == CMS_SUCCESS);

    CPPUNIT_ASSERT(cms_getProducerPriority(producer, &priority) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL(1, priority);

    CPPUNIT_ASSERT(cms_destroyProducer(producer) == CMS_SUCCESS);

    cms_destroyDestination(destination);
}

////////////////////////////////////////////////////////////////////////////////
void MessageProducerTest::testGetTimeToLive() {

    CMS_Destination* destination = NULL;
    CMS_MessageProducer* producer = NULL;
    int ttl = -1;

    CPPUNIT_ASSERT(cms_createTemporaryDestination(session, CMS_TEMPORARY_TOPIC, &destination) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_createProducer(session, destination, &producer) == CMS_SUCCESS);

    CPPUNIT_ASSERT(cms_getProducerTimeToLive(producer, &ttl) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL(0, ttl);

    CPPUNIT_ASSERT(cms_setProducerTimeToLive(producer, 1000) == CMS_SUCCESS);

    CPPUNIT_ASSERT(cms_getProducerTimeToLive(producer, &ttl) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL(1000, ttl);

    CPPUNIT_ASSERT(cms_destroyProducer(producer) == CMS_SUCCESS);

    cms_destroyDestination(destination);
}

////////////////////////////////////////////////////////////////////////////////
void MessageProducerTest::testSendWithDefaults() {

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

    cms_producerSendWithDefaults(producer, message);

    CMS_Message* received = NULL;
    CPPUNIT_ASSERT(cms_consumerReceiveWithTimeout(consumer, &received, 2000) == CMS_SUCCESS);

    int priority = -1;
    int deliveryMode = -1;
    long long expiration = -1;

    CPPUNIT_ASSERT(cms_getCMSMessagePriority(received, &priority) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_getCMSMessageDeliveryMode(received, &deliveryMode) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_getCMSMessageExpiration(received, &expiration) == CMS_SUCCESS);

    CPPUNIT_ASSERT_EQUAL(4, priority);
    CPPUNIT_ASSERT_EQUAL((int)CMS_MSG_NON_PERSISTENT, deliveryMode);
    CPPUNIT_ASSERT_EQUAL(0LL, expiration);

    cms_destroyMessage(received);
    cms_destroyMessage(message);
    cms_destroyConsumer(consumer);
    cms_destroyProducer(producer);
    cms_destroyDestination(destination);
}

////////////////////////////////////////////////////////////////////////////////
void MessageProducerTest::testSendToDestination() {

    CMS_Destination* destination = NULL;
    CMS_Message* message = NULL;
    CMS_MessageConsumer* consumer = NULL;
    CMS_MessageProducer* producer = NULL;

    cms_createTemporaryDestination(session, CMS_TEMPORARY_TOPIC, &destination);
    cms_createDefaultConsumer(session, destination, &consumer);

    CPPUNIT_ASSERT(cms_createProducer(session, NULL, &producer) == CMS_SUCCESS);

    cms_startConnection(connection);

    cms_createTextMessage(session, &message, NULL);

    CPPUNIT_ASSERT(cms_producerSendToDestination(producer, message, NULL, CMS_MSG_NON_PERSISTENT, 5, 5000) == CMS_ERROR);
    CPPUNIT_ASSERT(cms_producerSendToDestination(producer, message, destination, CMS_MSG_NON_PERSISTENT, 5, 5000) == CMS_SUCCESS);

    CMS_Message* received = NULL;
    CPPUNIT_ASSERT(cms_consumerReceiveWithTimeout(consumer, &received, 2000) == CMS_SUCCESS);

    int priority = -1;
    int deliveryMode = -1;
    long long expiration = -1;

    CPPUNIT_ASSERT(cms_getCMSMessagePriority(received, &priority) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_getCMSMessageDeliveryMode(received, &deliveryMode) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_getCMSMessageExpiration(received, &expiration) == CMS_SUCCESS);

    CPPUNIT_ASSERT_EQUAL(5, priority);
    CPPUNIT_ASSERT_EQUAL((int)CMS_MSG_NON_PERSISTENT, deliveryMode);
    CPPUNIT_ASSERT(expiration > 0);

    cms_destroyMessage(received);
    cms_destroyMessage(message);
    cms_destroyConsumer(consumer);
    cms_destroyProducer(producer);
    cms_destroyDestination(destination);
}

////////////////////////////////////////////////////////////////////////////////
void MessageProducerTest::testSend() {

    CMS_Destination* destination = NULL;
    CMS_Message* message = NULL;
    CMS_MessageConsumer* consumer = NULL;
    CMS_MessageProducer* producer = NULL;

    cms_createTemporaryDestination(session, CMS_TEMPORARY_TOPIC, &destination);
    cms_createDefaultConsumer(session, destination, &consumer);

    CPPUNIT_ASSERT(cms_createProducer(session, destination, &producer) == CMS_SUCCESS);

    cms_startConnection(connection);

    cms_createTextMessage(session, &message, NULL);

    CPPUNIT_ASSERT(cms_producerSend(producer, NULL, CMS_MSG_NON_PERSISTENT, 5, 5000) == CMS_ERROR);
    CPPUNIT_ASSERT(cms_producerSend(producer, message, CMS_MSG_NON_PERSISTENT, 5, 5000) == CMS_SUCCESS);

    CMS_Message* received = NULL;
    CPPUNIT_ASSERT(cms_consumerReceiveWithTimeout(consumer, &received, 2000) == CMS_SUCCESS);

    int priority = -1;
    int deliveryMode = -1;
    long long expiration = -1;

    CPPUNIT_ASSERT(cms_getCMSMessagePriority(received, &priority) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_getCMSMessageDeliveryMode(received, &deliveryMode) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_getCMSMessageExpiration(received, &expiration) == CMS_SUCCESS);

    CPPUNIT_ASSERT_EQUAL(5, priority);
    CPPUNIT_ASSERT_EQUAL((int)CMS_MSG_NON_PERSISTENT, deliveryMode);
    CPPUNIT_ASSERT(expiration > 0);

    cms_destroyMessage(received);
    cms_destroyMessage(message);
    cms_destroyConsumer(consumer);
    cms_destroyProducer(producer);
    cms_destroyDestination(destination);
}

////////////////////////////////////////////////////////////////////////////////
void MessageProducerTest::testSendWithTimeoutMessageExpires() {

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

    // Send with 1 Second TTL
    cms_producerSendWithTimeOut(producer, message, 500);

    Thread::sleep(750);

    CMS_Message* received = NULL;
    CPPUNIT_ASSERT(cms_consumerReceiveWithTimeout(consumer, &received, 1000) == CMS_RECEIVE_TIMEDOUT);
    CPPUNIT_ASSERT(NULL == received);

    cms_destroyMessage(received);
    cms_destroyMessage(message);
    cms_destroyConsumer(consumer);
    cms_destroyProducer(producer);
    cms_destroyDestination(destination);
}

////////////////////////////////////////////////////////////////////////////////
void MessageProducerTest::testSendWithTimeoutMessageArrives() {

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

    // Send with 1 Second TTL
    cms_producerSendWithTimeOut(producer, message, 5000);

    Thread::sleep(500);

    CMS_Message* received = NULL;
    CPPUNIT_ASSERT(cms_consumerReceiveWithTimeout(consumer, &received, 2000) == CMS_SUCCESS);
    CPPUNIT_ASSERT(NULL != received);

    cms_destroyMessage(received);
    cms_destroyMessage(message);
    cms_destroyConsumer(consumer);
    cms_destroyProducer(producer);
    cms_destroyDestination(destination);
}
