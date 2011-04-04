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

#include "MessageTest.h"

#include <CMS_Message.h>
#include <CMS_Destination.h>
#include <CMS_BytesMessage.h>

#include <decaf/lang/Integer.h>

using namespace cms;
using namespace decaf;
using namespace decaf::lang;

////////////////////////////////////////////////////////////////////////////////
MessageTest::MessageTest() {
}

////////////////////////////////////////////////////////////////////////////////
MessageTest::~MessageTest() {
}

////////////////////////////////////////////////////////////////////////////////
void MessageTest::testCreateMessage() {

    CMS_Message* message = NULL;
    int result = 0;

    CPPUNIT_ASSERT(createMessage(NULL, &message) == CMS_ERROR);
    CPPUNIT_ASSERT(createMessage(session, NULL) == CMS_ERROR);
    CPPUNIT_ASSERT(createMessage(NULL, NULL) == CMS_ERROR);

    CPPUNIT_ASSERT(createMessage(session, &message) == CMS_SUCCESS);

    int type = -1;
    CPPUNIT_ASSERT(getMessageType(message, &type) == CMS_SUCCESS);
    CPPUNIT_ASSERT(type == CMS_MESSAGE);

    result = -1;
    CPPUNIT_ASSERT(getNumMessageProperties(message, &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL(0, result);
    result = -1;
    CPPUNIT_ASSERT(messagePropertyExists(message, "some-property", &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL(0, result);

    destroyMessage(message);
}

////////////////////////////////////////////////////////////////////////////////
void MessageTest::testGetNumMessageProperties() {

    CMS_Message* message = NULL;
    int result = 0;

    CPPUNIT_ASSERT(createMessage(session, &message) == CMS_SUCCESS);

    result = -1;
    CPPUNIT_ASSERT(getNumMessageProperties(message, &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL(0, result);

    CPPUNIT_ASSERT(setMessageBooleanProperty(message, "1", 0) == CMS_SUCCESS);
    CPPUNIT_ASSERT(setMessageBooleanProperty(message, "2", 1) == CMS_SUCCESS);
    CPPUNIT_ASSERT(setMessageBooleanProperty(message, "3", 0) == CMS_SUCCESS);
    CPPUNIT_ASSERT(setMessageBooleanProperty(message, "4", 1) == CMS_SUCCESS);
    CPPUNIT_ASSERT(setMessageBooleanProperty(message, "5", 0) == CMS_SUCCESS);

    CPPUNIT_ASSERT(getNumMessageProperties(message, &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL(5, result);

    CPPUNIT_ASSERT(getNumMessageProperties(message, NULL) == CMS_ERROR);
    CPPUNIT_ASSERT(getNumMessageProperties(NULL, &result) == CMS_ERROR);
    CPPUNIT_ASSERT(getNumMessageProperties(NULL, NULL) == CMS_ERROR);

    destroyMessage(message);
}

////////////////////////////////////////////////////////////////////////////////
void MessageTest::testGetMessagePropertyNames() {

    CMS_Message* message = NULL;
    int result = 0;

    CPPUNIT_ASSERT(createMessage(session, &message) == CMS_SUCCESS);

    result = -1;
    CPPUNIT_ASSERT(getNumMessageProperties(message, &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL(0, result);

    CPPUNIT_ASSERT(setMessageBooleanProperty(message, "1", 0) == CMS_SUCCESS);
    CPPUNIT_ASSERT(setMessageBooleanProperty(message, "2", 1) == CMS_SUCCESS);
    CPPUNIT_ASSERT(setMessageBooleanProperty(message, "3", 0) == CMS_SUCCESS);
    CPPUNIT_ASSERT(setMessageBooleanProperty(message, "4", 1) == CMS_SUCCESS);
    CPPUNIT_ASSERT(setMessageBooleanProperty(message, "5", 0) == CMS_SUCCESS);

    char** names = NULL;
    int size = 0;

    CPPUNIT_ASSERT(getMessagePropertyNames(message, &names, &size) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL(5, size);

    for(int i = 0; i < size; ++i) {
        CPPUNIT_ASSERT(std::string(Integer::toString(i+1)) == std::string(names[i]) );
        delete names[i];
    }

    delete names;

    CPPUNIT_ASSERT(getMessagePropertyNames(NULL, &names, &size) == CMS_ERROR);
    CPPUNIT_ASSERT(getMessagePropertyNames(message, NULL, &size) == CMS_ERROR);
    CPPUNIT_ASSERT(getMessagePropertyNames(message, &names, NULL) == CMS_ERROR);
    CPPUNIT_ASSERT(getMessagePropertyNames(NULL, &names, NULL) == CMS_ERROR);
    CPPUNIT_ASSERT(getMessagePropertyNames(message, NULL, NULL) == CMS_ERROR);
    CPPUNIT_ASSERT(getMessagePropertyNames(NULL, NULL, NULL) == CMS_ERROR);

    destroyMessage(message);
}

////////////////////////////////////////////////////////////////////////////////
void MessageTest::testMessagePropertyExists() {

    CMS_Message* message = NULL;
    int result = 0;

    CPPUNIT_ASSERT(createMessage(session, &message) == CMS_SUCCESS);

    result = -1;
    CPPUNIT_ASSERT(getNumMessageProperties(message, &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL(0, result);

    CPPUNIT_ASSERT(setMessageBooleanProperty(message, "1", 0) == CMS_SUCCESS);
    CPPUNIT_ASSERT(setMessageBooleanProperty(message, "2", 1) == CMS_SUCCESS);
    CPPUNIT_ASSERT(setMessageBooleanProperty(message, "3", 0) == CMS_SUCCESS);
    CPPUNIT_ASSERT(setMessageBooleanProperty(message, "4", 1) == CMS_SUCCESS);
    CPPUNIT_ASSERT(setMessageBooleanProperty(message, "5", 0) == CMS_SUCCESS);

    result = -1;
    CPPUNIT_ASSERT(messagePropertyExists(message, "2", &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL(1, result);

    result = -1;
    CPPUNIT_ASSERT(messagePropertyExists(message, "8", &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL(0, result);

    CPPUNIT_ASSERT(messagePropertyExists(NULL, "2", &result) == CMS_ERROR);
    CPPUNIT_ASSERT(messagePropertyExists(message, NULL, &result) == CMS_ERROR);
    CPPUNIT_ASSERT(messagePropertyExists(message, "2", NULL) == CMS_ERROR);
    CPPUNIT_ASSERT(messagePropertyExists(message, NULL, NULL) == CMS_ERROR);
    CPPUNIT_ASSERT(messagePropertyExists(NULL, "2", NULL) == CMS_ERROR);
    CPPUNIT_ASSERT(messagePropertyExists(NULL, NULL, NULL) == CMS_ERROR);

    destroyMessage(message);
}

////////////////////////////////////////////////////////////////////////////////
void MessageTest::testClearMessageProperties() {

    CMS_Message* message = NULL;
    int result = 0;

    CPPUNIT_ASSERT(createMessage(session, &message) == CMS_SUCCESS);

    result = -1;
    CPPUNIT_ASSERT(getNumMessageProperties(message, &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL(0, result);

    CPPUNIT_ASSERT(setMessageBooleanProperty(message, "1", 0) == CMS_SUCCESS);
    CPPUNIT_ASSERT(setMessageBooleanProperty(message, "2", 1) == CMS_SUCCESS);
    CPPUNIT_ASSERT(setMessageBooleanProperty(message, "3", 0) == CMS_SUCCESS);
    CPPUNIT_ASSERT(setMessageBooleanProperty(message, "4", 1) == CMS_SUCCESS);
    CPPUNIT_ASSERT(setMessageBooleanProperty(message, "5", 0) == CMS_SUCCESS);

    result = -1;
    CPPUNIT_ASSERT(getNumMessageProperties(message, &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL(5, result);

    CPPUNIT_ASSERT(clearMessageProperties(message) == CMS_SUCCESS);

    result = -1;
    CPPUNIT_ASSERT(getNumMessageProperties(message, &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL(0, result);

    CPPUNIT_ASSERT(clearMessageProperties(NULL) == CMS_ERROR);

    destroyMessage(message);
}

////////////////////////////////////////////////////////////////////////////////
void MessageTest::testClearMessageBody() {

    CMS_Message* message = NULL;

    CPPUNIT_ASSERT(createMessage(session, &message) == CMS_SUCCESS);

    int length = -1;

    const int count = 10;

    CPPUNIT_ASSERT(createBytesMessage(session, &message, NULL, 0) == CMS_SUCCESS);

    for( int i = 0; i < count; i++ ) {
        CPPUNIT_ASSERT(writeLongToBytesMessage(message, 5LL) == CMS_SUCCESS);
    }

    CPPUNIT_ASSERT(resetBytesMessage(message) == CMS_SUCCESS);
    CPPUNIT_ASSERT(getBytesMessageBodyLength(message, &length) == CMS_SUCCESS);
    CPPUNIT_ASSERT(length == (count * 8));

    CPPUNIT_ASSERT(clearMessageBody(message) == CMS_SUCCESS);
    CPPUNIT_ASSERT(resetBytesMessage(message) == CMS_SUCCESS);
    CPPUNIT_ASSERT(getBytesMessageBodyLength(message, &length) == CMS_SUCCESS);
    CPPUNIT_ASSERT(length == 0);

    CPPUNIT_ASSERT(clearMessageBody(NULL) == CMS_ERROR);

    destroyMessage(message);
}

////////////////////////////////////////////////////////////////////////////////
void MessageTest::testMessageBooleanProperties() {

    CMS_Message* message = NULL;
    int result = 0;

    CPPUNIT_ASSERT(createMessage(session, &message) == CMS_SUCCESS);

    result = -1;
    CPPUNIT_ASSERT(getNumMessageProperties(message, &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL(0, result);

    result = -1;
    CPPUNIT_ASSERT(setMessageBooleanProperty(message, "boolean", 0) == CMS_SUCCESS);
    CPPUNIT_ASSERT(getMessageBooleanProperty(message, "boolean", &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT(result == 0);

    result = -1;
    CPPUNIT_ASSERT(getNumMessageProperties(message, &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL(1, result);

    CPPUNIT_ASSERT(setMessageBooleanProperty(message, "boolean", 1) == CMS_SUCCESS);
    CPPUNIT_ASSERT(getMessageBooleanProperty(message, "boolean", &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT(result == 1);

    result = -1;
    CPPUNIT_ASSERT(getNumMessageProperties(message, &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL(1, result);

    CPPUNIT_ASSERT(setMessageBooleanProperty(NULL, "boolean", 0) == CMS_ERROR);
    CPPUNIT_ASSERT(setMessageBooleanProperty(NULL, NULL, 0) == CMS_ERROR);
    CPPUNIT_ASSERT(setMessageBooleanProperty(message, NULL, 0) == CMS_ERROR);

    CPPUNIT_ASSERT(getMessageBooleanProperty(message, "boolean", NULL) == CMS_ERROR);
    CPPUNIT_ASSERT(getMessageBooleanProperty(message, NULL, &result) == CMS_ERROR);
    CPPUNIT_ASSERT(getMessageBooleanProperty(message, NULL, NULL) == CMS_ERROR);
    CPPUNIT_ASSERT(getMessageBooleanProperty(NULL, "boolean", &result) == CMS_ERROR);
    CPPUNIT_ASSERT(getMessageBooleanProperty(NULL, NULL, &result) == CMS_ERROR);
    CPPUNIT_ASSERT(getMessageBooleanProperty(NULL, NULL, NULL) == CMS_ERROR);

    destroyMessage(message);
}

////////////////////////////////////////////////////////////////////////////////
void MessageTest::testMessageByteProperties() {

    CMS_Message* message = NULL;
    int result = 0;
    unsigned char value = 0;

    CPPUNIT_ASSERT(createMessage(session, &message) == CMS_SUCCESS);

    result = -1;
    CPPUNIT_ASSERT(getNumMessageProperties(message, &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL(0, result);

    result = -1;
    CPPUNIT_ASSERT(setMessageByteProperty(message, "byte", 0) == CMS_SUCCESS);
    CPPUNIT_ASSERT(getMessageByteProperty(message, "byte", &value) == CMS_SUCCESS);
    CPPUNIT_ASSERT(value == 0);

    result = -1;
    CPPUNIT_ASSERT(getNumMessageProperties(message, &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL(1, result);

    CPPUNIT_ASSERT(setMessageByteProperty(message, "byte", 127) == CMS_SUCCESS);
    CPPUNIT_ASSERT(getMessageByteProperty(message, "byte", &value) == CMS_SUCCESS);
    CPPUNIT_ASSERT(value == 127);

    result = -1;
    CPPUNIT_ASSERT(getNumMessageProperties(message, &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL(1, result);

    CPPUNIT_ASSERT(setMessageByteProperty(NULL, "byte", 0) == CMS_ERROR);
    CPPUNIT_ASSERT(setMessageByteProperty(NULL, NULL, 0) == CMS_ERROR);
    CPPUNIT_ASSERT(setMessageByteProperty(message, NULL, 0) == CMS_ERROR);

    CPPUNIT_ASSERT(getMessageByteProperty(message, "byte", NULL) == CMS_ERROR);
    CPPUNIT_ASSERT(getMessageByteProperty(message, NULL, &value) == CMS_ERROR);
    CPPUNIT_ASSERT(getMessageByteProperty(message, NULL, NULL) == CMS_ERROR);
    CPPUNIT_ASSERT(getMessageByteProperty(NULL, "byte", &value) == CMS_ERROR);
    CPPUNIT_ASSERT(getMessageByteProperty(NULL, NULL, &value) == CMS_ERROR);
    CPPUNIT_ASSERT(getMessageByteProperty(NULL, NULL, NULL) == CMS_ERROR);

    destroyMessage(message);
}

////////////////////////////////////////////////////////////////////////////////
void MessageTest::testMessageDoubleProperties() {

    CMS_Message* message = NULL;
    int result = 0;
    double value = 0;

    CPPUNIT_ASSERT(createMessage(session, &message) == CMS_SUCCESS);

    result = -1;
    CPPUNIT_ASSERT(getNumMessageProperties(message, &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL(0, result);

    result = -1;
    CPPUNIT_ASSERT(setMessageDoubleProperty(message, "double", 0) == CMS_SUCCESS);
    CPPUNIT_ASSERT(getMessageDoubleProperty(message, "double", &value) == CMS_SUCCESS);
    CPPUNIT_ASSERT(value == 0);

    result = -1;
    CPPUNIT_ASSERT(getNumMessageProperties(message, &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL(1, result);

    CPPUNIT_ASSERT(setMessageDoubleProperty(message, "double", 127) == CMS_SUCCESS);
    CPPUNIT_ASSERT(getMessageDoubleProperty(message, "double", &value) == CMS_SUCCESS);
    CPPUNIT_ASSERT(value == 127);

    result = -1;
    CPPUNIT_ASSERT(getNumMessageProperties(message, &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL(1, result);

    CPPUNIT_ASSERT(setMessageDoubleProperty(NULL, "double", 0) == CMS_ERROR);
    CPPUNIT_ASSERT(setMessageDoubleProperty(NULL, NULL, 0) == CMS_ERROR);
    CPPUNIT_ASSERT(setMessageDoubleProperty(message, NULL, 0) == CMS_ERROR);

    CPPUNIT_ASSERT(getMessageDoubleProperty(message, "double", NULL) == CMS_ERROR);
    CPPUNIT_ASSERT(getMessageDoubleProperty(message, NULL, &value) == CMS_ERROR);
    CPPUNIT_ASSERT(getMessageDoubleProperty(message, NULL, NULL) == CMS_ERROR);
    CPPUNIT_ASSERT(getMessageDoubleProperty(NULL, "double", &value) == CMS_ERROR);
    CPPUNIT_ASSERT(getMessageDoubleProperty(NULL, NULL, &value) == CMS_ERROR);
    CPPUNIT_ASSERT(getMessageDoubleProperty(NULL, NULL, NULL) == CMS_ERROR);

    destroyMessage(message);
}

////////////////////////////////////////////////////////////////////////////////
void MessageTest::testMessageFloatProperties() {

    CMS_Message* message = NULL;
    int result = 0;
    float value = 0;

    CPPUNIT_ASSERT(createMessage(session, &message) == CMS_SUCCESS);

    result = -1;
    CPPUNIT_ASSERT(getNumMessageProperties(message, &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL(0, result);

    result = -1;
    CPPUNIT_ASSERT(setMessageFloatProperty(message, "float", 0) == CMS_SUCCESS);
    CPPUNIT_ASSERT(getMessageFloatProperty(message, "float", &value) == CMS_SUCCESS);
    CPPUNIT_ASSERT(value == 0);

    result = -1;
    CPPUNIT_ASSERT(getNumMessageProperties(message, &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL(1, result);

    CPPUNIT_ASSERT(setMessageFloatProperty(message, "float", 127) == CMS_SUCCESS);
    CPPUNIT_ASSERT(getMessageFloatProperty(message, "float", &value) == CMS_SUCCESS);
    CPPUNIT_ASSERT(value == 127);

    result = -1;
    CPPUNIT_ASSERT(getNumMessageProperties(message, &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL(1, result);

    CPPUNIT_ASSERT(setMessageFloatProperty(NULL, "float", 0) == CMS_ERROR);
    CPPUNIT_ASSERT(setMessageFloatProperty(NULL, NULL, 0) == CMS_ERROR);
    CPPUNIT_ASSERT(setMessageFloatProperty(message, NULL, 0) == CMS_ERROR);

    CPPUNIT_ASSERT(getMessageFloatProperty(message, "float", NULL) == CMS_ERROR);
    CPPUNIT_ASSERT(getMessageFloatProperty(message, NULL, &value) == CMS_ERROR);
    CPPUNIT_ASSERT(getMessageFloatProperty(message, NULL, NULL) == CMS_ERROR);
    CPPUNIT_ASSERT(getMessageFloatProperty(NULL, "float", &value) == CMS_ERROR);
    CPPUNIT_ASSERT(getMessageFloatProperty(NULL, NULL, &value) == CMS_ERROR);
    CPPUNIT_ASSERT(getMessageFloatProperty(NULL, NULL, NULL) == CMS_ERROR);

    destroyMessage(message);
}

////////////////////////////////////////////////////////////////////////////////
void MessageTest::testMessageLongProperties() {

    CMS_Message* message = NULL;
    int result = 0;
    long long value = 0;

    CPPUNIT_ASSERT(createMessage(session, &message) == CMS_SUCCESS);

    result = -1;
    CPPUNIT_ASSERT(getNumMessageProperties(message, &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL(0, result);

    result = -1;
    CPPUNIT_ASSERT(setMessageLongProperty(message, "long", 0) == CMS_SUCCESS);
    CPPUNIT_ASSERT(getMessageLongProperty(message, "long", &value) == CMS_SUCCESS);
    CPPUNIT_ASSERT(value == 0);

    result = -1;
    CPPUNIT_ASSERT(getNumMessageProperties(message, &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL(1, result);

    CPPUNIT_ASSERT(setMessageLongProperty(message, "long", 127) == CMS_SUCCESS);
    CPPUNIT_ASSERT(getMessageLongProperty(message, "long", &value) == CMS_SUCCESS);
    CPPUNIT_ASSERT(value == 127);

    result = -1;
    CPPUNIT_ASSERT(getNumMessageProperties(message, &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL(1, result);

    CPPUNIT_ASSERT(setMessageLongProperty(NULL, "long", 0) == CMS_ERROR);
    CPPUNIT_ASSERT(setMessageLongProperty(NULL, NULL, 0) == CMS_ERROR);
    CPPUNIT_ASSERT(setMessageLongProperty(message, NULL, 0) == CMS_ERROR);

    CPPUNIT_ASSERT(getMessageLongProperty(message, "long", NULL) == CMS_ERROR);
    CPPUNIT_ASSERT(getMessageLongProperty(message, NULL, &value) == CMS_ERROR);
    CPPUNIT_ASSERT(getMessageLongProperty(message, NULL, NULL) == CMS_ERROR);
    CPPUNIT_ASSERT(getMessageLongProperty(NULL, "long", &value) == CMS_ERROR);
    CPPUNIT_ASSERT(getMessageLongProperty(NULL, NULL, &value) == CMS_ERROR);
    CPPUNIT_ASSERT(getMessageLongProperty(NULL, NULL, NULL) == CMS_ERROR);

    destroyMessage(message);
}

////////////////////////////////////////////////////////////////////////////////
void MessageTest::testMessageIntProperties() {

    CMS_Message* message = NULL;
    int result = 0;
    int value = 0;

    CPPUNIT_ASSERT(createMessage(session, &message) == CMS_SUCCESS);

    result = -1;
    CPPUNIT_ASSERT(getNumMessageProperties(message, &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL(0, result);

    result = -1;
    CPPUNIT_ASSERT(setMessageIntProperty(message, "int", 0) == CMS_SUCCESS);
    CPPUNIT_ASSERT(getMessageIntProperty(message, "int", &value) == CMS_SUCCESS);
    CPPUNIT_ASSERT(value == 0);

    result = -1;
    CPPUNIT_ASSERT(getNumMessageProperties(message, &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL(1, result);

    CPPUNIT_ASSERT(setMessageIntProperty(message, "int", 127) == CMS_SUCCESS);
    CPPUNIT_ASSERT(getMessageIntProperty(message, "int", &value) == CMS_SUCCESS);
    CPPUNIT_ASSERT(value == 127);

    result = -1;
    CPPUNIT_ASSERT(getNumMessageProperties(message, &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL(1, result);

    CPPUNIT_ASSERT(setMessageIntProperty(NULL, "int", 0) == CMS_ERROR);
    CPPUNIT_ASSERT(setMessageIntProperty(NULL, NULL, 0) == CMS_ERROR);
    CPPUNIT_ASSERT(setMessageIntProperty(message, NULL, 0) == CMS_ERROR);

    CPPUNIT_ASSERT(getMessageIntProperty(message, "int", NULL) == CMS_ERROR);
    CPPUNIT_ASSERT(getMessageIntProperty(message, NULL, &value) == CMS_ERROR);
    CPPUNIT_ASSERT(getMessageIntProperty(message, NULL, NULL) == CMS_ERROR);
    CPPUNIT_ASSERT(getMessageIntProperty(NULL, "int", &value) == CMS_ERROR);
    CPPUNIT_ASSERT(getMessageIntProperty(NULL, NULL, &value) == CMS_ERROR);
    CPPUNIT_ASSERT(getMessageIntProperty(NULL, NULL, NULL) == CMS_ERROR);

    destroyMessage(message);
}

////////////////////////////////////////////////////////////////////////////////
void MessageTest::testMessageShortProperties() {

    CMS_Message* message = NULL;
    int result = 0;
    short value = 0;

    CPPUNIT_ASSERT(createMessage(session, &message) == CMS_SUCCESS);

    result = -1;
    CPPUNIT_ASSERT(getNumMessageProperties(message, &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL(0, result);

    result = -1;
    CPPUNIT_ASSERT(setMessageShortProperty(message, "short", 0) == CMS_SUCCESS);
    CPPUNIT_ASSERT(getMessageShortProperty(message, "short", &value) == CMS_SUCCESS);
    CPPUNIT_ASSERT(value == 0);

    result = -1;
    CPPUNIT_ASSERT(getNumMessageProperties(message, &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL(1, result);

    CPPUNIT_ASSERT(setMessageShortProperty(message, "short", 127) == CMS_SUCCESS);
    CPPUNIT_ASSERT(getMessageShortProperty(message, "short", &value) == CMS_SUCCESS);
    CPPUNIT_ASSERT(value == 127);

    result = -1;
    CPPUNIT_ASSERT(getNumMessageProperties(message, &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL(1, result);

    CPPUNIT_ASSERT(setMessageShortProperty(NULL, "short", 0) == CMS_ERROR);
    CPPUNIT_ASSERT(setMessageShortProperty(NULL, NULL, 0) == CMS_ERROR);
    CPPUNIT_ASSERT(setMessageShortProperty(message, NULL, 0) == CMS_ERROR);

    CPPUNIT_ASSERT(getMessageShortProperty(message, "short", NULL) == CMS_ERROR);
    CPPUNIT_ASSERT(getMessageShortProperty(message, NULL, &value) == CMS_ERROR);
    CPPUNIT_ASSERT(getMessageShortProperty(message, NULL, NULL) == CMS_ERROR);
    CPPUNIT_ASSERT(getMessageShortProperty(NULL, "short", &value) == CMS_ERROR);
    CPPUNIT_ASSERT(getMessageShortProperty(NULL, NULL, &value) == CMS_ERROR);
    CPPUNIT_ASSERT(getMessageShortProperty(NULL, NULL, NULL) == CMS_ERROR);

    destroyMessage(message);
}

////////////////////////////////////////////////////////////////////////////////
void MessageTest::testMessageStringProperties() {

    CMS_Message* message = NULL;
    int result = 0;
    const char* inValue1 = "Test String 1";
    const char* inValue2 = "Test String 2";
    char* outValue = new char[256];

    CPPUNIT_ASSERT(createMessage(session, &message) == CMS_SUCCESS);

    result = -1;
    CPPUNIT_ASSERT(getNumMessageProperties(message, &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL(0, result);

    result = -1;
    CPPUNIT_ASSERT(setMessageStringProperty(message, "string", inValue1) == CMS_SUCCESS);
    CPPUNIT_ASSERT(getMessageStringProperty(message, "string", outValue, 256) == CMS_SUCCESS);
    CPPUNIT_ASSERT(std::string(inValue1) == std::string(outValue));

    result = -1;
    CPPUNIT_ASSERT(getNumMessageProperties(message, &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL(1, result);

    CPPUNIT_ASSERT(setMessageStringProperty(message, "string", inValue2) == CMS_SUCCESS);
    CPPUNIT_ASSERT(getMessageStringProperty(message, "string", outValue, 256) == CMS_SUCCESS);
    CPPUNIT_ASSERT(std::string(inValue2) == std::string(outValue));

    result = -1;
    CPPUNIT_ASSERT(getNumMessageProperties(message, &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL(1, result);

    CPPUNIT_ASSERT(setMessageStringProperty(NULL, "string", 0) == CMS_ERROR);
    CPPUNIT_ASSERT(setMessageStringProperty(NULL, NULL, 0) == CMS_ERROR);
    CPPUNIT_ASSERT(setMessageStringProperty(message, NULL, 0) == CMS_ERROR);

    CPPUNIT_ASSERT(getMessageStringProperty(message, "string", NULL, 255) == CMS_ERROR);
    CPPUNIT_ASSERT(getMessageStringProperty(message, NULL, outValue, 256) == CMS_ERROR);
    CPPUNIT_ASSERT(getMessageStringProperty(message, NULL, NULL, 255) == CMS_ERROR);
    CPPUNIT_ASSERT(getMessageStringProperty(NULL, "string", outValue, 256) == CMS_ERROR);
    CPPUNIT_ASSERT(getMessageStringProperty(NULL, NULL, outValue, 256) == CMS_ERROR);
    CPPUNIT_ASSERT(getMessageStringProperty(NULL, NULL, NULL, 256) == CMS_ERROR);

    destroyMessage(message);
    delete [] outValue;
}

////////////////////////////////////////////////////////////////////////////////
void MessageTest::testCMSMessageCorrelationID() {

    CMS_Message* message = NULL;
    const char* inValue1 = "Test String 1";
    const char* inValue2 = "Test String 2";
    char* outValue = new char[256];

    CPPUNIT_ASSERT(createMessage(session, &message) == CMS_SUCCESS);

    CPPUNIT_ASSERT(setCMSMessageCorrelationID(message, inValue1) == CMS_SUCCESS);
    CPPUNIT_ASSERT(getCMSMessageCorrelationID(message, outValue, 256) == CMS_SUCCESS);
    CPPUNIT_ASSERT(std::string(inValue1) == std::string(outValue));

    CPPUNIT_ASSERT(setCMSMessageCorrelationID(message, inValue2) == CMS_SUCCESS);
    CPPUNIT_ASSERT(getCMSMessageCorrelationID(message, outValue, 256) == CMS_SUCCESS);
    CPPUNIT_ASSERT(std::string(inValue2) == std::string(outValue));

    CPPUNIT_ASSERT(setCMSMessageCorrelationID(NULL, inValue1) == CMS_ERROR);
    CPPUNIT_ASSERT(setCMSMessageCorrelationID(NULL, NULL) == CMS_ERROR);
    CPPUNIT_ASSERT(setCMSMessageCorrelationID(message, NULL) == CMS_ERROR);

    CPPUNIT_ASSERT(getCMSMessageCorrelationID(message, NULL, 255) == CMS_ERROR);
    CPPUNIT_ASSERT(getCMSMessageCorrelationID(message, outValue, 0) == CMS_ERROR);
    CPPUNIT_ASSERT(getCMSMessageCorrelationID(message, NULL, 0) == CMS_ERROR);
    CPPUNIT_ASSERT(getCMSMessageCorrelationID(NULL, outValue, 256) == CMS_ERROR);
    CPPUNIT_ASSERT(getCMSMessageCorrelationID(NULL, outValue, 0) == CMS_ERROR);
    CPPUNIT_ASSERT(getCMSMessageCorrelationID(NULL, NULL, 256) == CMS_ERROR);

    destroyMessage(message);
    delete [] outValue;
}

////////////////////////////////////////////////////////////////////////////////
void MessageTest::testCMSMessageDeliveryMode() {

    CMS_Message* message = NULL;
    int result = 0;

    CPPUNIT_ASSERT(createMessage(session, &message) == CMS_SUCCESS);

    CPPUNIT_ASSERT(setCMSMessageDeliveryMode(message, CMS_MSG_PERSISTENT) == CMS_SUCCESS);
    CPPUNIT_ASSERT(getCMSMessageDeliveryMode(message, &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT(result == CMS_MSG_PERSISTENT);

    CPPUNIT_ASSERT(setCMSMessageDeliveryMode(message, CMS_MSG_NON_PERSISTENT) == CMS_SUCCESS);
    CPPUNIT_ASSERT(getCMSMessageDeliveryMode(message, &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT(result == CMS_MSG_NON_PERSISTENT);

    CPPUNIT_ASSERT(setCMSMessageDeliveryMode(NULL, 2) == CMS_ERROR);

    CPPUNIT_ASSERT(getCMSMessageDeliveryMode(message, NULL) == CMS_ERROR);
    CPPUNIT_ASSERT(getCMSMessageDeliveryMode(NULL, &result) == CMS_ERROR);
    CPPUNIT_ASSERT(getCMSMessageDeliveryMode(NULL, NULL) == CMS_ERROR);

    destroyMessage(message);
}

////////////////////////////////////////////////////////////////////////////////
void MessageTest::testCMSMessageDestination() {

    CMS_Message* message = NULL;
    CMS_Destination* destination = 0;
    CMS_Destination* result = 0;
    int equals = 0;

    CPPUNIT_ASSERT(createDestination(session, CMS_TEMPORARY_TOPIC, NULL, &destination) == CMS_SUCCESS);

    CPPUNIT_ASSERT(createMessage(session, &message) == CMS_SUCCESS);

    CPPUNIT_ASSERT(setCMSMessageDestination(message, destination) == CMS_SUCCESS);
    CPPUNIT_ASSERT(getCMSMessageDestination(message, &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT(compareDestinations(result, destination, &equals) == CMS_SUCCESS);
    CPPUNIT_ASSERT_EQUAL(1, equals);

    CPPUNIT_ASSERT(setCMSMessageDestination(NULL, destination) == CMS_ERROR);

    CPPUNIT_ASSERT(getCMSMessageDestination(message, NULL) == CMS_ERROR);
    CPPUNIT_ASSERT(getCMSMessageDestination(NULL, &result) == CMS_ERROR);
    CPPUNIT_ASSERT(getCMSMessageDestination(NULL, NULL) == CMS_ERROR);

    destroyMessage(message);
    destroyDestination(destination);
    destroyDestination(result);
}

////////////////////////////////////////////////////////////////////////////////
void MessageTest::testCMSMessageExpiration() {

    CMS_Message* message = NULL;
    long long result = 0;

    CPPUNIT_ASSERT(createMessage(session, &message) == CMS_SUCCESS);

    CPPUNIT_ASSERT(setCMSMessageExpiration(message, 55) == CMS_SUCCESS);
    CPPUNIT_ASSERT(getCMSMessageExpiration(message, &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT(result == 55);

    CPPUNIT_ASSERT(setCMSMessageExpiration(message, 127) == CMS_SUCCESS);
    CPPUNIT_ASSERT(getCMSMessageExpiration(message, &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT(result == 127);

    CPPUNIT_ASSERT(setCMSMessageExpiration(NULL, 2) == CMS_ERROR);

    CPPUNIT_ASSERT(getCMSMessageExpiration(message, NULL) == CMS_ERROR);
    CPPUNIT_ASSERT(getCMSMessageExpiration(NULL, &result) == CMS_ERROR);
    CPPUNIT_ASSERT(getCMSMessageExpiration(NULL, NULL) == CMS_ERROR);

    destroyMessage(message);
}

////////////////////////////////////////////////////////////////////////////////
void MessageTest::testCMSMessageMessageID() {

    // TODO - Not working in AMQ-CPP Yet
//	CMS_Message* message = NULL;
//	const char* inValue1 = "Test String 1";
//	const char* inValue2 = "Test String 2";
//	char* outValue = new char[256];
//
//	CPPUNIT_ASSERT(createMessage(session, &message) == CMS_SUCCESS);
//
//	CPPUNIT_ASSERT(setCMSMessageMessageID(message, inValue1) == CMS_SUCCESS);
//	CPPUNIT_ASSERT(getCMSMessageMessageID(message, outValue, 256) == CMS_SUCCESS);
//	CPPUNIT_ASSERT(std::string(inValue1) == std::string(outValue));
//
//	CPPUNIT_ASSERT(setCMSMessageMessageID(message, inValue2) == CMS_SUCCESS);
//	CPPUNIT_ASSERT(getCMSMessageMessageID(message, outValue, 256) == CMS_SUCCESS);
//	CPPUNIT_ASSERT(std::string(inValue2) == std::string(outValue));
//
//	CPPUNIT_ASSERT(setCMSMessageMessageID(NULL, inValue1) == CMS_ERROR);
//	CPPUNIT_ASSERT(setCMSMessageMessageID(NULL, NULL) == CMS_ERROR);
//	CPPUNIT_ASSERT(setCMSMessageMessageID(message, NULL) == CMS_ERROR);
//
//	CPPUNIT_ASSERT(getCMSMessageMessageID(message, NULL, 255) == CMS_ERROR);
//	CPPUNIT_ASSERT(getCMSMessageMessageID(message, outValue, 0) == CMS_ERROR);
//	CPPUNIT_ASSERT(getCMSMessageMessageID(message, NULL, 0) == CMS_ERROR);
//	CPPUNIT_ASSERT(getCMSMessageMessageID(NULL, outValue, 256) == CMS_ERROR);
//	CPPUNIT_ASSERT(getCMSMessageMessageID(NULL, outValue, 0) == CMS_ERROR);
//	CPPUNIT_ASSERT(getCMSMessageMessageID(NULL, NULL, 256) == CMS_ERROR);
//
//	destroyMessage(message);
}

////////////////////////////////////////////////////////////////////////////////
void MessageTest::testCMSMessagePriority() {

    CMS_Message* message = NULL;
    int result = 0;

    CPPUNIT_ASSERT(createMessage(session, &message) == CMS_SUCCESS);

    CPPUNIT_ASSERT(setCMSMessagePriority(message, 1) == CMS_SUCCESS);
    CPPUNIT_ASSERT(getCMSMessagePriority(message, &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT(result == 1);

    CPPUNIT_ASSERT(setCMSMessagePriority(message, 4) == CMS_SUCCESS);
    CPPUNIT_ASSERT(getCMSMessagePriority(message, &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT(result == 4);

    CPPUNIT_ASSERT(setCMSMessagePriority(NULL, 2) == CMS_ERROR);

    CPPUNIT_ASSERT(getCMSMessagePriority(message, NULL) == CMS_ERROR);
    CPPUNIT_ASSERT(getCMSMessagePriority(NULL, &result) == CMS_ERROR);
    CPPUNIT_ASSERT(getCMSMessagePriority(NULL, NULL) == CMS_ERROR);

    destroyMessage(message);
}

////////////////////////////////////////////////////////////////////////////////
void MessageTest::testCMSMessageRedelivered() {

// TODO - Not working in AMQ-CPP Yet
//	CMS_Message* message = NULL;
//	int result = 0;
//
//	CPPUNIT_ASSERT(createMessage(session, &message) == CMS_SUCCESS);
//
//	CPPUNIT_ASSERT(setCMSMessageRedelivered(message, 1) == CMS_SUCCESS);
//	CPPUNIT_ASSERT(getCMSMessageRedelivered(message, &result) == CMS_SUCCESS);
//	CPPUNIT_ASSERT(result == 1);
//
//	CPPUNIT_ASSERT(setCMSMessageRedelivered(message, 0) == CMS_SUCCESS);
//	CPPUNIT_ASSERT(getCMSMessageRedelivered(message, &result) == CMS_SUCCESS);
//	CPPUNIT_ASSERT(result == 0);
//
//	CPPUNIT_ASSERT(setCMSMessageRedelivered(NULL, 2) == CMS_ERROR);
//
//	CPPUNIT_ASSERT(getCMSMessageRedelivered(message, NULL) == CMS_ERROR);
//	CPPUNIT_ASSERT(getCMSMessageRedelivered(NULL, &result) == CMS_ERROR);
//	CPPUNIT_ASSERT(getCMSMessageRedelivered(NULL, NULL) == CMS_ERROR);
//
//	destroyMessage(message);
}

////////////////////////////////////////////////////////////////////////////////
void MessageTest::testCMSMessageReplyTo() {

}

////////////////////////////////////////////////////////////////////////////////
void MessageTest::testCMSMessageTimestamp() {

    CMS_Message* message = NULL;
    long long result = 0;

    CPPUNIT_ASSERT(createMessage(session, &message) == CMS_SUCCESS);

    CPPUNIT_ASSERT(setCMSMessageTimestamp(message, 55) == CMS_SUCCESS);
    CPPUNIT_ASSERT(getCMSMessageTimestamp(message, &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT(result == 55);

    CPPUNIT_ASSERT(setCMSMessageTimestamp(message, 127) == CMS_SUCCESS);
    CPPUNIT_ASSERT(getCMSMessageTimestamp(message, &result) == CMS_SUCCESS);
    CPPUNIT_ASSERT(result == 127);

    CPPUNIT_ASSERT(setCMSMessageTimestamp(NULL, 2) == CMS_ERROR);

    CPPUNIT_ASSERT(getCMSMessageTimestamp(message, NULL) == CMS_ERROR);
    CPPUNIT_ASSERT(getCMSMessageTimestamp(NULL, &result) == CMS_ERROR);
    CPPUNIT_ASSERT(getCMSMessageTimestamp(NULL, NULL) == CMS_ERROR);

    destroyMessage(message);
}

////////////////////////////////////////////////////////////////////////////////
void MessageTest::testCMSMessageType() {

    CMS_Message* message = NULL;
    const char* inValue1 = "Test String 1";
    const char* inValue2 = "Test String 2";
    char* outValue = new char[256];

    CPPUNIT_ASSERT(createMessage(session, &message) == CMS_SUCCESS);

    CPPUNIT_ASSERT(setCMSMessageType(message, inValue1) == CMS_SUCCESS);
    CPPUNIT_ASSERT(getCMSMessageType(message, outValue, 256) == CMS_SUCCESS);
    CPPUNIT_ASSERT(std::string(inValue1) == std::string(outValue));

    CPPUNIT_ASSERT(setCMSMessageType(message, inValue2) == CMS_SUCCESS);
    CPPUNIT_ASSERT(getCMSMessageType(message, outValue, 256) == CMS_SUCCESS);
    CPPUNIT_ASSERT(std::string(inValue2) == std::string(outValue));

    CPPUNIT_ASSERT(setCMSMessageType(NULL, inValue1) == CMS_ERROR);
    CPPUNIT_ASSERT(setCMSMessageType(NULL, NULL) == CMS_ERROR);
    CPPUNIT_ASSERT(setCMSMessageType(message, NULL) == CMS_ERROR);

    CPPUNIT_ASSERT(getCMSMessageType(message, NULL, 255) == CMS_ERROR);
    CPPUNIT_ASSERT(getCMSMessageType(message, outValue, 0) == CMS_ERROR);
    CPPUNIT_ASSERT(getCMSMessageType(message, NULL, 0) == CMS_ERROR);
    CPPUNIT_ASSERT(getCMSMessageType(NULL, outValue, 256) == CMS_ERROR);
    CPPUNIT_ASSERT(getCMSMessageType(NULL, outValue, 0) == CMS_ERROR);
    CPPUNIT_ASSERT(getCMSMessageType(NULL, NULL, 256) == CMS_ERROR);

    destroyMessage(message);
    delete [] outValue;
}
