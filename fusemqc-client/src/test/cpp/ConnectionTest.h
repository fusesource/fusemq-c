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

#ifndef _CMS_CONNECTIONTEST_H_
#define _CMS_CONNECTIONTEST_H_

#include "CMSTestCase.h"

namespace cms {

    class ConnectionTest : public CMSTestCase {

        CPPUNIT_TEST_SUITE( ConnectionTest );
        CPPUNIT_TEST( testConnectToNullHost );
        CPPUNIT_TEST( testConnectToValidHost );
        CPPUNIT_TEST( testConnectToInvalidHost );
        CPPUNIT_TEST( testCreateSessionFromConnection );
        CPPUNIT_TEST( testGetErrorString );
        CPPUNIT_TEST_SUITE_END();

    public:

        ConnectionTest();
        virtual ~ConnectionTest();

    public:

        void testConnectToNullHost();
        void testConnectToValidHost();
        void testConnectToInvalidHost();
        void testCreateSessionFromConnection();
        void testGetErrorString();

    };

}

#endif /* _CMS_CONNECTIONTEST_H_ */
