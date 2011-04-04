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

#ifndef _CMS_MESSAGETEST_H_
#define _CMS_MESSAGETEST_H_

#include "SingleConnectionTestCase.h"

namespace cms {

    class MessageTest : public SingleConnectionTestCase {

        CPPUNIT_TEST_SUITE( MessageTest );
        CPPUNIT_TEST( testCreateMessage );
        CPPUNIT_TEST( testGetNumMessageProperties );
        CPPUNIT_TEST( testGetMessagePropertyNames );
        CPPUNIT_TEST( testMessagePropertyExists );
        CPPUNIT_TEST( testClearMessageProperties );
        CPPUNIT_TEST( testClearMessageBody );
        CPPUNIT_TEST( testMessageBooleanProperties );
        CPPUNIT_TEST( testMessageByteProperties );
        CPPUNIT_TEST( testMessageDoubleProperties );
        CPPUNIT_TEST( testMessageFloatProperties );
        CPPUNIT_TEST( testMessageLongProperties );
        CPPUNIT_TEST( testMessageIntProperties );
        CPPUNIT_TEST( testMessageShortProperties );
        CPPUNIT_TEST( testMessageStringProperties );
        CPPUNIT_TEST( testCMSMessageCorrelationID );
        CPPUNIT_TEST( testCMSMessageDeliveryMode );
        CPPUNIT_TEST( testCMSMessageDestination );
        CPPUNIT_TEST( testCMSMessageExpiration );
        CPPUNIT_TEST( testCMSMessageMessageID );
        CPPUNIT_TEST( testCMSMessagePriority );
        CPPUNIT_TEST( testCMSMessageRedelivered );
        CPPUNIT_TEST( testCMSMessageReplyTo );
        CPPUNIT_TEST( testCMSMessageTimestamp );
        CPPUNIT_TEST( testCMSMessageType );
        CPPUNIT_TEST_SUITE_END();

    public:

        MessageTest();
        virtual ~MessageTest();

        void testCreateMessage();
        void testGetNumMessageProperties();
        void testGetMessagePropertyNames();
        void testMessagePropertyExists();
        void testClearMessageProperties();
        void testClearMessageBody();
        void testMessageBooleanProperties();
        void testMessageByteProperties();
        void testMessageDoubleProperties();
        void testMessageFloatProperties();
        void testMessageLongProperties();
        void testMessageIntProperties();
        void testMessageShortProperties();
        void testMessageStringProperties();
        void testCMSMessageCorrelationID();
        void testCMSMessageDeliveryMode();
        void testCMSMessageDestination();
        void testCMSMessageExpiration();
        void testCMSMessageMessageID();
        void testCMSMessagePriority();
        void testCMSMessageRedelivered();
        void testCMSMessageReplyTo();
        void testCMSMessageTimestamp();
        void testCMSMessageType();

    };

}

#endif /* _CMS_MESSAGETEST_H_ */
