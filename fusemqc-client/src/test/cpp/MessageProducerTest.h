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

#ifndef _CMS_MESSAGEPRODUCERTEST_H_
#define _CMS_MESSAGEPRODUCERTEST_H_

#include "SingleConnectionTestCase.h"

namespace cms {

    class MessageProducerTest : public SingleConnectionTestCase {

        CPPUNIT_TEST_SUITE( MessageProducerTest );
        CPPUNIT_TEST( testCreateProducer );
        CPPUNIT_TEST( testGetDeliveryMode );
        CPPUNIT_TEST( testGetDisableTimestamps );
        CPPUNIT_TEST( testGetDisableMessageId );
        CPPUNIT_TEST( testGetPriority );
        CPPUNIT_TEST( testGetTimeToLive );
        CPPUNIT_TEST( testSend );
        CPPUNIT_TEST( testSendWithDefaults );
        CPPUNIT_TEST( testSendToDestination );
        CPPUNIT_TEST_SUITE_END();

    public:

        MessageProducerTest();
        virtual ~MessageProducerTest();

        void testCreateProducer();
        void testGetDeliveryMode();
        void testGetDisableTimestamps();
        void testGetDisableMessageId();
        void testGetPriority();
        void testGetTimeToLive();
        void testSend();
        void testSendWithDefaults();
        void testSendToDestination();

    };

}

#endif /* _CMS_MESSAGEPRODUCERTEST_H_ */
