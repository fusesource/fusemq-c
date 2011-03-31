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

    CPPUNIT_ASSERT(writeBooleanToBytesMessage(NULL, 1) == CMS_ERROR);

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
    unsigned char result = 255;

    CPPUNIT_ASSERT(createBytesMessage(session, &message, NULL, 0) == CMS_SUCCESS);

    CPPUNIT_ASSERT(writeByteToBytesMessage(NULL, 32) == CMS_ERROR);

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

////////////////////////////////////////////////////////////////////////////////
void BytesMessageTest::testReadChar() {

    CMS_Message* message = NULL;
    char result = -1;

    CPPUNIT_ASSERT(createBytesMessage(session, &message, NULL, 0) == CMS_SUCCESS);

    CPPUNIT_ASSERT(writeCharToBytesMessage(NULL, 32) == CMS_ERROR);

    CPPUNIT_ASSERT(writeCharToBytesMessage(message, 'a') == CMS_SUCCESS);
    CPPUNIT_ASSERT(resetBytesMessage(message) == CMS_SUCCESS);
    CPPUNIT_ASSERT(readCharFromBytesMessage(message, &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT(result == 'a');

    CPPUNIT_ASSERT(readCharFromBytesMessage(NULL, &result) == CMS_ERROR);
    CPPUNIT_ASSERT(readCharFromBytesMessage(message, NULL) == CMS_ERROR);
    CPPUNIT_ASSERT(readCharFromBytesMessage(NULL, NULL) == CMS_ERROR);

    destroyMessage(message);
}

////////////////////////////////////////////////////////////////////////////////
void BytesMessageTest::testReadDouble() {

    CMS_Message* message = NULL;
    double result = -1;

    CPPUNIT_ASSERT(createBytesMessage(session, &message, NULL, 0) == CMS_SUCCESS);

    CPPUNIT_ASSERT(writeDoubleToBytesMessage(NULL, 32) == CMS_ERROR);

    CPPUNIT_ASSERT(writeDoubleToBytesMessage(message, 42.42) == CMS_SUCCESS);
    CPPUNIT_ASSERT(resetBytesMessage(message) == CMS_SUCCESS);
    CPPUNIT_ASSERT(readDoubleFromBytesMessage(message, &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(42.42, result, 1.0);

    CPPUNIT_ASSERT(readDoubleFromBytesMessage(NULL, &result) == CMS_ERROR);
    CPPUNIT_ASSERT(readDoubleFromBytesMessage(message, NULL) == CMS_ERROR);
    CPPUNIT_ASSERT(readDoubleFromBytesMessage(NULL, NULL) == CMS_ERROR);

    destroyMessage(message);
}

////////////////////////////////////////////////////////////////////////////////
void BytesMessageTest::testReadFloat() {

    CMS_Message* message = NULL;
    float result = -1;

    CPPUNIT_ASSERT(createBytesMessage(session, &message, NULL, 0) == CMS_SUCCESS);

    CPPUNIT_ASSERT(writeFloatToBytesMessage(NULL, 32) == CMS_ERROR);

    CPPUNIT_ASSERT(writeFloatToBytesMessage(message, 23.45f) == CMS_SUCCESS);
    CPPUNIT_ASSERT(resetBytesMessage(message) == CMS_SUCCESS);
    CPPUNIT_ASSERT(readFloatFromBytesMessage(message, &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL(23.45f, result);

    CPPUNIT_ASSERT(readFloatFromBytesMessage(NULL, &result) == CMS_ERROR);
    CPPUNIT_ASSERT(readFloatFromBytesMessage(message, NULL) == CMS_ERROR);
    CPPUNIT_ASSERT(readFloatFromBytesMessage(NULL, NULL) == CMS_ERROR);

    destroyMessage(message);
}

////////////////////////////////////////////////////////////////////////////////
void BytesMessageTest::testReadLong() {

    CMS_Message* message = NULL;
    long long result = -1;

    CPPUNIT_ASSERT(createBytesMessage(session, &message, NULL, 0) == CMS_SUCCESS);

    CPPUNIT_ASSERT(writeLongToBytesMessage(NULL, 32) == CMS_ERROR);

    CPPUNIT_ASSERT(writeLongToBytesMessage(message, 45LL) == CMS_SUCCESS);
    CPPUNIT_ASSERT(resetBytesMessage(message) == CMS_SUCCESS);
    CPPUNIT_ASSERT(readLongFromBytesMessage(message, &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL(45LL, result);

    CPPUNIT_ASSERT(readLongFromBytesMessage(NULL, &result) == CMS_ERROR);
    CPPUNIT_ASSERT(readLongFromBytesMessage(message, NULL) == CMS_ERROR);
    CPPUNIT_ASSERT(readLongFromBytesMessage(NULL, NULL) == CMS_ERROR);

    destroyMessage(message);
}

////////////////////////////////////////////////////////////////////////////////
void BytesMessageTest::testReadInt() {

    CMS_Message* message = NULL;
    int result = -1;

    CPPUNIT_ASSERT(createBytesMessage(session, &message, NULL, 0) == CMS_SUCCESS);

    CPPUNIT_ASSERT(writeIntToBytesMessage(NULL, 32) == CMS_ERROR);

    CPPUNIT_ASSERT(writeIntToBytesMessage(message, 23) == CMS_SUCCESS);
    CPPUNIT_ASSERT(resetBytesMessage(message) == CMS_SUCCESS);
    CPPUNIT_ASSERT(readIntFromBytesMessage(message, &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL(23, result);

    CPPUNIT_ASSERT(readIntFromBytesMessage(NULL, &result) == CMS_ERROR);
    CPPUNIT_ASSERT(readIntFromBytesMessage(message, NULL) == CMS_ERROR);
    CPPUNIT_ASSERT(readIntFromBytesMessage(NULL, NULL) == CMS_ERROR);

    destroyMessage(message);
}

////////////////////////////////////////////////////////////////////////////////
void BytesMessageTest::testReadShort() {

    CMS_Message* message = NULL;
    short result = -1;

    CPPUNIT_ASSERT(createBytesMessage(session, &message, NULL, 0) == CMS_SUCCESS);

    CPPUNIT_ASSERT(writeShortToBytesMessage(NULL, 32) == CMS_ERROR);

    CPPUNIT_ASSERT(writeShortToBytesMessage(message, 32767) == CMS_SUCCESS);
    CPPUNIT_ASSERT(resetBytesMessage(message) == CMS_SUCCESS);
    CPPUNIT_ASSERT(readShortFromBytesMessage(message, &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL((short)32767, result);

    CPPUNIT_ASSERT(readShortFromBytesMessage(NULL, &result) == CMS_ERROR);
    CPPUNIT_ASSERT(readShortFromBytesMessage(message, NULL) == CMS_ERROR);
    CPPUNIT_ASSERT(readShortFromBytesMessage(NULL, NULL) == CMS_ERROR);

    destroyMessage(message);
}

////////////////////////////////////////////////////////////////////////////////
void BytesMessageTest::testReadBytes() {

    CMS_Message* message = NULL;
    unsigned char buffer[50];
    unsigned char data[50];
    for( int i = 0; i < 50; i++ ) {
        data[i] = (unsigned char)i;
    }

    CPPUNIT_ASSERT(createBytesMessage(session, &message, NULL, 0) == CMS_SUCCESS);

    CPPUNIT_ASSERT(writeBytesToBytesMessage(NULL, data, 0, 50) == CMS_ERROR);
    CPPUNIT_ASSERT(writeBytesToBytesMessage(NULL, NULL, 0, 50) == CMS_ERROR);
    CPPUNIT_ASSERT(writeBytesToBytesMessage(message, data, -1, 50) == CMS_ERROR);
    CPPUNIT_ASSERT(writeBytesToBytesMessage(message, data, 0, -1) == CMS_ERROR);

    CPPUNIT_ASSERT(writeBytesToBytesMessage(message, data, 0, 50) == CMS_SUCCESS);
    CPPUNIT_ASSERT(resetBytesMessage(message) == CMS_SUCCESS);
    CPPUNIT_ASSERT(readBytesFromBytesMessage(message, buffer, 50) == CMS_SUCCESS);
    for( int i = 0; i < 50; i++ ) {
        CPPUNIT_ASSERT_EQUAL(data[i], buffer[i]);
    }

    CPPUNIT_ASSERT(readBytesFromBytesMessage(NULL, buffer, 1) == CMS_ERROR);
    CPPUNIT_ASSERT(readBytesFromBytesMessage(message, NULL, 50) == CMS_ERROR);
    CPPUNIT_ASSERT(readBytesFromBytesMessage(NULL, NULL, 50) == CMS_ERROR);
    CPPUNIT_ASSERT(readBytesFromBytesMessage(message, buffer, -1) == CMS_ERROR);

    destroyMessage(message);
}

////////////////////////////////////////////////////////////////////////////////
void BytesMessageTest::testReadString() {

    CMS_Message* message = NULL;
    char buffer[50];
    std::string data = "This is a test string.";

    CPPUNIT_ASSERT(createBytesMessage(session, &message, NULL, 0) == CMS_SUCCESS);

    CPPUNIT_ASSERT(writeStringToBytesMessage(NULL, data.c_str()) == CMS_ERROR);
    CPPUNIT_ASSERT(writeStringToBytesMessage(message, NULL) == CMS_ERROR);
    CPPUNIT_ASSERT(writeStringToBytesMessage(NULL, NULL) == CMS_ERROR);

    CPPUNIT_ASSERT(writeStringToBytesMessage(message, data.c_str()) == CMS_SUCCESS);
    CPPUNIT_ASSERT(resetBytesMessage(message) == CMS_SUCCESS);
    CPPUNIT_ASSERT(readStringFromBytesMessage(message, buffer, 50) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL(data, std::string(buffer));

    CPPUNIT_ASSERT(readStringFromBytesMessage(NULL, buffer, 1) == CMS_ERROR);
    CPPUNIT_ASSERT(readStringFromBytesMessage(message, NULL, 50) == CMS_ERROR);
    CPPUNIT_ASSERT(readStringFromBytesMessage(NULL, NULL, 50) == CMS_ERROR);
    CPPUNIT_ASSERT(readStringFromBytesMessage(message, buffer, -1) == CMS_ERROR);

    destroyMessage(message);
}

////////////////////////////////////////////////////////////////////////////////
void BytesMessageTest::testReadUTF() {

    CMS_Message* message = NULL;
    char buffer[50];
    std::string data = "This is a test string.";

    CPPUNIT_ASSERT(createBytesMessage(session, &message, NULL, 0) == CMS_SUCCESS);

    CPPUNIT_ASSERT(writeUTFToBytesMessage(NULL, data.c_str()) == CMS_ERROR);
    CPPUNIT_ASSERT(writeUTFToBytesMessage(message, NULL) == CMS_ERROR);
    CPPUNIT_ASSERT(writeUTFToBytesMessage(NULL, NULL) == CMS_ERROR);

    CPPUNIT_ASSERT(writeUTFToBytesMessage(message, data.c_str()) == CMS_SUCCESS);
    CPPUNIT_ASSERT(resetBytesMessage(message) == CMS_SUCCESS);
    CPPUNIT_ASSERT(readUTFFromBytesMessage(message, buffer, 50) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL(data, std::string(buffer));

    CPPUNIT_ASSERT(readUTFFromBytesMessage(NULL, buffer, 1) == CMS_ERROR);
    CPPUNIT_ASSERT(readUTFFromBytesMessage(message, NULL, 50) == CMS_ERROR);
    CPPUNIT_ASSERT(readUTFFromBytesMessage(NULL, NULL, 50) == CMS_ERROR);
    CPPUNIT_ASSERT(readUTFFromBytesMessage(message, buffer, -1) == CMS_ERROR);

    destroyMessage(message);
}
