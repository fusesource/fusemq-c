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

#include "QueueBrowserTest.h"

#include <cms.h>
#include <CMS_Connection.h>
#include <CMS_Session.h>
#include <CMS_Destination.h>
#include <CMS_TextMessage.h>
#include <CMS_MessageProducer.h>
#include <CMS_MessageConsumer.h>
#include <CMS_QueueBrowser.h>

#include <decaf/lang/Thread.h>

using namespace cms;
using namespace decaf;
using namespace decaf::lang;

////////////////////////////////////////////////////////////////////////////////
QueueBrowserTest::QueueBrowserTest() {
}

////////////////////////////////////////////////////////////////////////////////
QueueBrowserTest::~QueueBrowserTest() {
}

////////////////////////////////////////////////////////////////////////////////
void QueueBrowserTest::testCreateBrowser() {

    CMS_Destination* destination = NULL;
    CMS_QueueBrowser* browser = NULL;

    CPPUNIT_ASSERT(cms_createDestination(session, CMS_QUEUE, "QueueBrowserTest.QUEUE", &destination) == CMS_SUCCESS);
    CPPUNIT_ASSERT(cms_createQueueBrowser(session, destination, &browser, NULL) == CMS_SUCCESS);

    char* selector = new char[256];
    CPPUNIT_ASSERT(cms_getBrowserMessageSelector(browser, selector, 256) == CMS_SUCCESS);
    CPPUNIT_ASSERT(std::string("") == std::string(selector));
    delete [] selector;

    CPPUNIT_ASSERT(cms_destroyQueueBrowser(browser) == CMS_SUCCESS);

    cms_destroyDestination(destination);
}

////////////////////////////////////////////////////////////////////////////////
void QueueBrowserTest::testQueueBrowse() {

    CMS_Destination* destination = NULL;
    CMS_Message* message = NULL;
    CMS_QueueBrowser* browser = NULL;
    CMS_MessageProducer* producer = NULL;

    cms_createDestination(session, CMS_QUEUE, "QueueBrowserTest.testQueueBrowse.QUEUE", &destination);

    drainDestination(destination);

    cms_createProducer(session, destination, &producer);
    cms_setProducerDeliveryMode(producer, CMS_MSG_NON_PERSISTENT);

    cms_startConnection(connection);

    cms_createTextMessage(session, &message, NULL);

    for( unsigned int i = 0; i < 128; ++i ) {
        cms_producerSendWithDefaults(producer, message);
    }

    cms_destroyMessage(message);

    CPPUNIT_ASSERT(cms_createQueueBrowser(session, destination, &browser, NULL) == CMS_SUCCESS);

    int count = 0;
    int hasMore = 0;

    while (cms_browserHasMoreMessages(browser, &hasMore) == CMS_SUCCESS && hasMore > 0) {
        CMS_Message* received = NULL;
        CPPUNIT_ASSERT(cms_browserGetNextMessages(browser, &received) == CMS_SUCCESS);
        cms_destroyMessage(received);
        count++;
    }

    cms_destroyQueueBrowser(browser);
    cms_destroyProducer(producer);
    cms_destroyDestination(destination);

    CPPUNIT_ASSERT_EQUAL(128, count);
}

////////////////////////////////////////////////////////////////////////////////
void QueueBrowserTest::testQueueBrowseEmpty() {

    CMS_Destination* destination = NULL;
    CMS_QueueBrowser* browser = NULL;

    cms_createDestination(session, CMS_QUEUE, "QueueBrowserTest.testQueueBrowse.QUEUE", &destination);

    drainDestination(destination);
    cms_startConnection(connection);

    CPPUNIT_ASSERT(cms_createQueueBrowser(session, destination, &browser, NULL) == CMS_SUCCESS);

    int hasMore = 0;

    // Should always succeed and indicate no messages.
    CPPUNIT_ASSERT(cms_browserHasMoreMessages(browser, &hasMore) == CMS_SUCCESS);
    CPPUNIT_ASSERT(hasMore = 0);
    CPPUNIT_ASSERT(cms_browserHasMoreMessages(browser, &hasMore) == CMS_SUCCESS);
    CPPUNIT_ASSERT(hasMore = 0);

    cms_destroyQueueBrowser(browser);
    cms_destroyDestination(destination);
}

////////////////////////////////////////////////////////////////////////////////
void QueueBrowserTest::testQueueBrowseEmptyThenProduce() {

    CMS_Destination* destination = NULL;
    CMS_Message* message = NULL;
    CMS_QueueBrowser* browser = NULL;
    CMS_MessageProducer* producer = NULL;

    cms_createDestination(session, CMS_QUEUE, "QueueBrowserTest.testQueueBrowse.QUEUE", &destination);
    cms_createProducer(session, destination, &producer);
    cms_setProducerDeliveryMode(producer, CMS_MSG_NON_PERSISTENT);

    drainDestination(destination);
    cms_startConnection(connection);

    CPPUNIT_ASSERT(cms_createQueueBrowser(session, destination, &browser, NULL) == CMS_SUCCESS);

    int hasMore = 0;

    CPPUNIT_ASSERT(cms_browserHasMoreMessages(browser, &hasMore) == CMS_SUCCESS);
    CPPUNIT_ASSERT(hasMore = 0);

    cms_createTextMessage(session, &message, NULL);

    for( unsigned int i = 0; i < 128; ++i ) {
        cms_producerSendWithDefaults(producer, message);
    }

    cms_destroyMessage(message);

    int count = 0;

    while (cms_browserHasMoreMessages(browser, &hasMore) == CMS_SUCCESS && hasMore > 0) {
        CMS_Message* received = NULL;
        CPPUNIT_ASSERT(cms_browserGetNextMessages(browser, &received) == CMS_SUCCESS);
        cms_destroyMessage(received);
        count++;
    }

    cms_destroyQueueBrowser(browser);
    cms_destroyProducer(producer);
    cms_destroyDestination(destination);

    CPPUNIT_ASSERT_EQUAL(128, count);
}
