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

#include "BytesMessageTest.h"

#include <CMS_BytesMessage.h>

using namespace cms;

////////////////////////////////////////////////////////////////////////////////
BytesMessageTest::BytesMessageTest() {
}

////////////////////////////////////////////////////////////////////////////////
BytesMessageTest::~BytesMessageTest() {
}

////////////////////////////////////////////////////////////////////////////////
void BytesMessageTest::testCreateBytesMessage() {

    CMS_Message* message = NULL;
    int result = -1;
    int length = -1;

    CPPUNIT_ASSERT(createBytesMessage(session, &message, NULL, 0) == CMS_SUCCESS);
    CPPUNIT_ASSERT(getMessageType(message, &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL((int)CMS_BYTES_MESSAGE, result);

    CPPUNIT_ASSERT(getBytesMessageBodyLength(message, &length) == CMS_MESSAGE_NOT_READABLE);

    destroyMessage(message);

    CPPUNIT_ASSERT(createBytesMessage(session, &message, NULL, 0) == CMS_SUCCESS);
    CPPUNIT_ASSERT(getMessageType(message, &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL((int)CMS_BYTES_MESSAGE, result);

    destroyMessage(message);

    CPPUNIT_ASSERT(createBytesMessage(session, NULL, NULL, 0) == CMS_ERROR);
    CPPUNIT_ASSERT(createBytesMessage(NULL, &message, NULL, 0) == CMS_ERROR);
    CPPUNIT_ASSERT(createBytesMessage(NULL, NULL, NULL, 0) == CMS_ERROR);
}

////////////////////////////////////////////////////////////////////////////////
void BytesMessageTest::testGetByteMessageBodyLength() {

    CMS_Message* message = NULL;
    int length = -1;

    const int count = 10;

    CPPUNIT_ASSERT(createBytesMessage(session, &message, NULL, 0) == CMS_SUCCESS);

    for( int i = 0; i < count; i++ ) {
        CPPUNIT_ASSERT(writeLongToBytesMessage(message, 5LL) == CMS_SUCCESS);
    }

    CPPUNIT_ASSERT(resetBytesMessage(message) == CMS_SUCCESS);
    CPPUNIT_ASSERT(getBytesMessageBodyLength(message, &length) == CMS_SUCCESS);
    CPPUNIT_ASSERT(length == (count * 8));

    CPPUNIT_ASSERT(resetBytesMessage(NULL) == CMS_ERROR);
    CPPUNIT_ASSERT(getBytesMessageBodyLength(NULL, &length) == CMS_ERROR);
    CPPUNIT_ASSERT(getBytesMessageBodyLength(message, NULL) == CMS_ERROR);
    CPPUNIT_ASSERT(getBytesMessageBodyLength(NULL, NULL) == CMS_ERROR);

    destroyMessage(message);
}

////////////////////////////////////////////////////////////////////////////////
void BytesMessageTest::testReadBoolean() {

    CMS_Message* message = NULL;
    int result = -1;

    CPPUNIT_ASSERT(createBytesMessage(session, &message, NULL, 0) == CMS_SUCCESS);

    CPPUNIT_ASSERT(writeBooleanToBytesMessage(message, 1) == CMS_SUCCESS);
    CPPUNIT_ASSERT(resetBytesMessage(message) == CMS_SUCCESS);
    CPPUNIT_ASSERT(readBooleanFromBytesMessage(message, &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT(result == 1);

    CPPUNIT_ASSERT(writeBooleanToBytesMessage(NULL, 1) == CMS_ERROR);
    CPPUNIT_ASSERT(readBooleanFromBytesMessage(NULL, &result) == CMS_ERROR);
    CPPUNIT_ASSERT(readBooleanFromBytesMessage(message, NULL) == CMS_ERROR);
    CPPUNIT_ASSERT(readBooleanFromBytesMessage(NULL, NULL) == CMS_ERROR);

    destroyMessage(message);
}

////////////////////////////////////////////////////////////////////////////////
void BytesMessageTest::testReadByte() {

    CMS_Message* message = NULL;
    unsigned char result = -1;

    CPPUNIT_ASSERT(createBytesMessage(session, &message, NULL, 0) == CMS_SUCCESS);

    CPPUNIT_ASSERT(writeByteToBytesMessage(message, 32) == CMS_SUCCESS);
    CPPUNIT_ASSERT(resetBytesMessage(message) == CMS_SUCCESS);
    CPPUNIT_ASSERT(readByteFromBytesMessage(message, &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT(result == 32);

    CPPUNIT_ASSERT(writeByteToBytesMessage(NULL, 32) == CMS_ERROR);
    CPPUNIT_ASSERT(readByteFromBytesMessage(NULL, &result) == CMS_ERROR);
    CPPUNIT_ASSERT(readByteFromBytesMessage(message, NULL) == CMS_ERROR);
    CPPUNIT_ASSERT(readByteFromBytesMessage(NULL, NULL) == CMS_ERROR);

    destroyMessage(message);
}
