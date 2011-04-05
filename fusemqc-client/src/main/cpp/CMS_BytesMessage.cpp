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

#include <CMS_Message.h>
#include <CMS_BytesMessage.h>

#include <Config.h>
#include <types/CMS_Types.h>

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif
#ifdef HAVE_STRINGS_H
#include <strings.h>
#endif
#ifdef HAVE_STRING_H
#include <string.h>
#endif

#include <memory>

////////////////////////////////////////////////////////////////////////////////
cms_status cms_getBytesMessageBodyLength(CMS_Message* message, int* length) {

    cms_status result = CMS_ERROR;

    if(message != NULL && message->message != NULL && length != NULL) {

        if( message->type != CMS_BYTES_MESSAGE ) {
            return CMS_INVALID_MESSAGE_TYPE;
        }

        cms::BytesMessage* bytesMessage = dynamic_cast<cms::BytesMessage*>( message->message );

        try {
            *length = bytesMessage->getBodyLength();
            result = CMS_SUCCESS;
        } catch(cms::MessageNotReadableException& ex) {
            result = CMS_MESSAGE_NOT_READABLE;
        } catch(...) {
            result = CMS_ERROR;
        }
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status cms_resetBytesMessage(CMS_Message* message) {

    cms_status result = CMS_ERROR;

    if(message != NULL && message->message != NULL) {

        if( message->type != CMS_BYTES_MESSAGE ) {
            return CMS_INVALID_MESSAGE_TYPE;
        }

        cms::BytesMessage* bytesMessage = dynamic_cast<cms::BytesMessage*>( message->message );

        try{
            bytesMessage->reset();
            result = CMS_SUCCESS;
        } catch(cms::MessageFormatException& ex) {
            result = CMS_MESSAGE_FORMAT_ERROR;
        } catch(...) {
            result = CMS_ERROR;
        }
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status cms_readBooleanFromBytesMessage(CMS_Message* message, int* value) {

    cms_status result = CMS_ERROR;

    if(message != NULL && message->message != NULL && value != NULL) {

        if( message->type != CMS_BYTES_MESSAGE ) {
            return CMS_INVALID_MESSAGE_TYPE;
        }

        cms::BytesMessage* bytesMessage = dynamic_cast<cms::BytesMessage*>( message->message );

        try{
            *value = bytesMessage->readBoolean();
            result = CMS_SUCCESS;
        } catch(cms::MessageFormatException& ex) {
            result = CMS_MESSAGE_FORMAT_ERROR;
        } catch(cms::MessageNotReadableException& ex) {
            result = CMS_MESSAGE_NOT_READABLE;
        } catch(...) {
            result = CMS_ERROR;
        }
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status cms_writeBooleanToBytesMessage(CMS_Message* message, int value) {

    cms_status result = CMS_ERROR;

    if(message != NULL && message->message != NULL) {

        if( message->type != CMS_BYTES_MESSAGE ) {
            return CMS_INVALID_MESSAGE_TYPE;
        }

        cms::BytesMessage* bytesMessage = dynamic_cast<cms::BytesMessage*>( message->message );

        try{
            bytesMessage->writeBoolean((bool)value);
            result = CMS_SUCCESS;
        } catch(cms::MessageFormatException& ex) {
            result = CMS_MESSAGE_FORMAT_ERROR;
        } catch(cms::MessageNotWriteableException& ex) {
            result = CMS_MESSAGE_NOT_WRITABLE;
        } catch(...) {
            result = CMS_ERROR;
        }
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status cms_readByteFromBytesMessage(CMS_Message* message, unsigned char* value) {

    cms_status result = CMS_ERROR;

    if(message != NULL && message->message != NULL && value != NULL) {

        if( message->type != CMS_BYTES_MESSAGE ) {
            return CMS_INVALID_MESSAGE_TYPE;
        }

        cms::BytesMessage* bytesMessage = dynamic_cast<cms::BytesMessage*>( message->message );

        try{
            *value = bytesMessage->readByte();
            result = CMS_SUCCESS;
        } catch(cms::MessageFormatException& ex) {
            result = CMS_MESSAGE_FORMAT_ERROR;
        } catch(cms::MessageNotReadableException& ex) {
            result = CMS_MESSAGE_NOT_READABLE;
        } catch(...) {
            result = CMS_ERROR;
        }
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status cms_writeByteToBytesMessage(CMS_Message* message, unsigned char value) {

    cms_status result = CMS_ERROR;

    if(message != NULL && message->message != NULL) {

        if( message->type != CMS_BYTES_MESSAGE ) {
            return CMS_INVALID_MESSAGE_TYPE;
        }

        cms::BytesMessage* bytesMessage = dynamic_cast<cms::BytesMessage*>( message->message );

        try{
            bytesMessage->writeByte(value);
            result = CMS_SUCCESS;
        } catch(cms::MessageFormatException& ex) {
            result = CMS_MESSAGE_FORMAT_ERROR;
        } catch(cms::MessageNotWriteableException& ex) {
            result = CMS_MESSAGE_NOT_WRITABLE;
        } catch(...) {
            result = CMS_ERROR;
        }
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status cms_readCharFromBytesMessage(CMS_Message* message, char* value) {

    cms_status result = CMS_ERROR;

    if(message != NULL && message->message != NULL && value != NULL) {

        if( message->type != CMS_BYTES_MESSAGE ) {
            return CMS_INVALID_MESSAGE_TYPE;
        }

        cms::BytesMessage* bytesMessage = dynamic_cast<cms::BytesMessage*>( message->message );

        try{
            *value = bytesMessage->readChar();
            result = CMS_SUCCESS;
        } catch(cms::MessageFormatException& ex) {
            result = CMS_MESSAGE_FORMAT_ERROR;
        } catch(cms::MessageNotReadableException& ex) {
            result = CMS_MESSAGE_NOT_READABLE;
        } catch(...) {
            result = CMS_ERROR;
        }
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status cms_writeCharToBytesMessage(CMS_Message* message, char value) {

    cms_status result = CMS_ERROR;

    if(message != NULL && message->message != NULL) {

        if( message->type != CMS_BYTES_MESSAGE ) {
            return CMS_INVALID_MESSAGE_TYPE;
        }

        cms::BytesMessage* bytesMessage = dynamic_cast<cms::BytesMessage*>( message->message );

        try{
            bytesMessage->writeChar(value);
            result = CMS_SUCCESS;
        } catch(cms::MessageFormatException& ex) {
            result = CMS_MESSAGE_FORMAT_ERROR;
        } catch(cms::MessageNotWriteableException& ex) {
            result = CMS_MESSAGE_NOT_WRITABLE;
        } catch(...) {
            result = CMS_ERROR;
        }
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status cms_readFloatFromBytesMessage(CMS_Message* message, float* value) {

    cms_status result = CMS_ERROR;

    if(message != NULL && message->message != NULL && value != NULL) {

        if( message->type != CMS_BYTES_MESSAGE ) {
            return CMS_INVALID_MESSAGE_TYPE;
        }

        cms::BytesMessage* bytesMessage = dynamic_cast<cms::BytesMessage*>( message->message );

        try{
            *value = bytesMessage->readFloat();
            result = CMS_SUCCESS;
        } catch(cms::MessageFormatException& ex) {
            result = CMS_MESSAGE_FORMAT_ERROR;
        } catch(cms::MessageNotReadableException& ex) {
            result = CMS_MESSAGE_NOT_READABLE;
        } catch(...) {
            result = CMS_ERROR;
        }
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status cms_writeFloatToBytesMessage(CMS_Message* message, float value) {

    cms_status result = CMS_ERROR;

    if(message != NULL && message->message != NULL) {

        if( message->type != CMS_BYTES_MESSAGE ) {
            return CMS_INVALID_MESSAGE_TYPE;
        }

        cms::BytesMessage* bytesMessage = dynamic_cast<cms::BytesMessage*>( message->message );

        try{
            bytesMessage->writeFloat(value);
            result = CMS_SUCCESS;
        } catch(cms::MessageFormatException& ex) {
            result = CMS_MESSAGE_FORMAT_ERROR;
        } catch(cms::MessageNotWriteableException& ex) {
            result = CMS_MESSAGE_NOT_WRITABLE;
        } catch(...) {
            result = CMS_ERROR;
        }
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status cms_readDoubleFromBytesMessage(CMS_Message* message, double* value) {

    cms_status result = CMS_ERROR;

    if(message != NULL && message->message != NULL && value != NULL) {

        if( message->type != CMS_BYTES_MESSAGE ) {
            return CMS_INVALID_MESSAGE_TYPE;
        }

        cms::BytesMessage* bytesMessage = dynamic_cast<cms::BytesMessage*>( message->message );

        try{
            *value = bytesMessage->readDouble();
            result = CMS_SUCCESS;
        } catch(cms::MessageFormatException& ex) {
            result = CMS_MESSAGE_FORMAT_ERROR;
        } catch(cms::MessageNotReadableException& ex) {
            result = CMS_MESSAGE_NOT_READABLE;
        } catch(...) {
            result = CMS_ERROR;
        }
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status cms_writeDoubleToBytesMessage(CMS_Message* message, double value) {

    cms_status result = CMS_ERROR;

    if(message != NULL && message->message != NULL) {

        if( message->type != CMS_BYTES_MESSAGE ) {
            return CMS_INVALID_MESSAGE_TYPE;
        }

        cms::BytesMessage* bytesMessage = dynamic_cast<cms::BytesMessage*>( message->message );

        try{
            bytesMessage->writeDouble(value);
            result = CMS_SUCCESS;
        } catch(cms::MessageFormatException& ex) {
            result = CMS_MESSAGE_FORMAT_ERROR;
        } catch(cms::MessageNotWriteableException& ex) {
            result = CMS_MESSAGE_NOT_WRITABLE;
        } catch(...) {
            result = CMS_ERROR;
        }
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status cms_readShortFromBytesMessage(CMS_Message* message, short* value) {

    cms_status result = CMS_ERROR;

    if(message != NULL && message->message != NULL && value != NULL) {

        if( message->type != CMS_BYTES_MESSAGE ) {
            return CMS_INVALID_MESSAGE_TYPE;
        }

        cms::BytesMessage* bytesMessage = dynamic_cast<cms::BytesMessage*>( message->message );

        try{
            *value = bytesMessage->readShort();
            result = CMS_SUCCESS;
        } catch(cms::MessageFormatException& ex) {
            result = CMS_MESSAGE_FORMAT_ERROR;
        } catch(cms::MessageNotReadableException& ex) {
            result = CMS_MESSAGE_NOT_READABLE;
        } catch(...) {
            result = CMS_ERROR;
        }
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status cms_writeShortToBytesMessage(CMS_Message* message, short value) {

    cms_status result = CMS_ERROR;

    if(message != NULL && message->message != NULL) {

        if( message->type != CMS_BYTES_MESSAGE ) {
            return CMS_INVALID_MESSAGE_TYPE;
        }

        cms::BytesMessage* bytesMessage = dynamic_cast<cms::BytesMessage*>( message->message );

        try{
            bytesMessage->writeShort(value);
            result = CMS_SUCCESS;
        } catch(cms::MessageFormatException& ex) {
            result = CMS_MESSAGE_FORMAT_ERROR;
        } catch(cms::MessageNotWriteableException& ex) {
            result = CMS_MESSAGE_NOT_WRITABLE;
        } catch(...) {
            result = CMS_ERROR;
        }
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status cms_readIntFromBytesMessage(CMS_Message* message, int* value) {

    cms_status result = CMS_ERROR;

    if(message != NULL && message->message != NULL && value != NULL) {

        if( message->type != CMS_BYTES_MESSAGE ) {
            return CMS_INVALID_MESSAGE_TYPE;
        }

        cms::BytesMessage* bytesMessage = dynamic_cast<cms::BytesMessage*>( message->message );

        try{
            *value = bytesMessage->readInt();
            result = CMS_SUCCESS;
        } catch(cms::MessageFormatException& ex) {
            result = CMS_MESSAGE_FORMAT_ERROR;
        } catch(cms::MessageNotReadableException& ex) {
            result = CMS_MESSAGE_NOT_READABLE;
        } catch(...) {
            result = CMS_ERROR;
        }
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status cms_writeIntToBytesMessage(CMS_Message* message, int value) {

    cms_status result = CMS_ERROR;

    if(message != NULL && message->message != NULL) {

        if( message->type != CMS_BYTES_MESSAGE ) {
            return CMS_INVALID_MESSAGE_TYPE;
        }

        cms::BytesMessage* bytesMessage = dynamic_cast<cms::BytesMessage*>( message->message );

        try{
            bytesMessage->writeInt(value);
            result = CMS_SUCCESS;
        } catch(cms::MessageFormatException& ex) {
            result = CMS_MESSAGE_FORMAT_ERROR;
        } catch(cms::MessageNotWriteableException& ex) {
            result = CMS_MESSAGE_NOT_WRITABLE;
        } catch(...) {
            result = CMS_ERROR;
        }
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status cms_readLongFromBytesMessage(CMS_Message* message, long long* value) {

    cms_status result = CMS_ERROR;

    if(message != NULL && message->message != NULL && value != NULL) {

        if( message->type != CMS_BYTES_MESSAGE ) {
            return CMS_INVALID_MESSAGE_TYPE;
        }

        cms::BytesMessage* bytesMessage = dynamic_cast<cms::BytesMessage*>( message->message );

        try{
            *value = bytesMessage->readLong();
            result = CMS_SUCCESS;
        } catch(cms::MessageFormatException& ex) {
            result = CMS_MESSAGE_FORMAT_ERROR;
        } catch(cms::MessageNotReadableException& ex) {
            result = CMS_MESSAGE_NOT_READABLE;
        } catch(...) {
            result = CMS_ERROR;
        }
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status cms_writeLongToBytesMessage(CMS_Message* message, long long value) {

    cms_status result = CMS_ERROR;

    if(message != NULL && message->message != NULL) {

        if( message->type != CMS_BYTES_MESSAGE ) {
            return CMS_INVALID_MESSAGE_TYPE;
        }

        cms::BytesMessage* bytesMessage = dynamic_cast<cms::BytesMessage*>( message->message );

        try{
            bytesMessage->writeLong(value);
            result = CMS_SUCCESS;
        } catch(cms::MessageFormatException& ex) {
            result = CMS_MESSAGE_FORMAT_ERROR;
        } catch(cms::MessageNotWriteableException& ex) {
            result = CMS_MESSAGE_NOT_WRITABLE;
        } catch(...) {
            result = CMS_ERROR;
        }
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status cms_readBytesFromBytesMessage(CMS_Message* message, unsigned char* value, int size) {

    cms_status result = CMS_ERROR;

    if(message != NULL && message->message != NULL && value != NULL) {

        try{

            if( message->type != CMS_BYTES_MESSAGE ) {
                return CMS_INVALID_MESSAGE_TYPE;
            }

            cms::BytesMessage* bytesMessage = dynamic_cast<cms::BytesMessage*>( message->message );

            int readCount = bytesMessage->readBytes(value, size);

            if( readCount == -1 ) {
                result = CMS_INCOMPLETE_READ;
            } else {
                result = CMS_SUCCESS;
            }

        } catch(cms::MessageFormatException& ex) {
            result = CMS_MESSAGE_FORMAT_ERROR;
        } catch(cms::MessageNotReadableException& ex) {
            result = CMS_MESSAGE_NOT_READABLE;
        } catch(...) {
            result = CMS_ERROR;
        }
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status cms_writeBytesToBytesMessage(CMS_Message* message, const unsigned char* value, int offset, int length) {

    cms_status result = CMS_ERROR;

    if(message != NULL && message->message != NULL && value != NULL) {

        try{

            if( message->type != CMS_BYTES_MESSAGE ) {
                return CMS_INVALID_MESSAGE_TYPE;
            }

            cms::BytesMessage* bytesMessage = dynamic_cast<cms::BytesMessage*>( message->message );

            bytesMessage->writeBytes(value, offset, length);
            result = CMS_SUCCESS;

        } catch(cms::MessageFormatException& ex) {
            result = CMS_MESSAGE_FORMAT_ERROR;
        } catch(cms::MessageNotWriteableException& ex) {
            result = CMS_MESSAGE_NOT_WRITABLE;
        } catch(...) {
            result = CMS_ERROR;
        }
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status cms_readStringFromBytesMessage(CMS_Message* message, char* value, int size) {

    cms_status result = CMS_ERROR;

    if(message != NULL && message->message != NULL && value != NULL) {

        try{

            if( message->type != CMS_BYTES_MESSAGE ) {
                return CMS_INVALID_MESSAGE_TYPE;
            }

            cms::BytesMessage* bytesMessage = dynamic_cast<cms::BytesMessage*>( message->message );

            std::string str = bytesMessage->readString();

            if(!str.empty()) {

                std::size_t pos = 0;
                for(; pos < str.size() && pos < (std::size_t)size - 1; ++pos) {
                    value[pos] = str.at(pos);
                }

                value[pos] = '\0';
            } else {
                value[0] = '\0';
            }

            result = CMS_SUCCESS;

        } catch(cms::MessageFormatException& ex) {
            value[0] = '\0';
            result = CMS_MESSAGE_FORMAT_ERROR;
        } catch(cms::MessageNotReadableException& ex) {
            value[0] = '\0';
            result = CMS_MESSAGE_NOT_READABLE;
        } catch(...) {
            value[0] = '\0';
            result = CMS_ERROR;
        }
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status cms_writeStringToBytesMessage(CMS_Message* message, const char* value) {

    cms_status result = CMS_ERROR;

    if(message != NULL && message->message != NULL && value != NULL) {

        try{

            if( message->type != CMS_BYTES_MESSAGE ) {
                return CMS_INVALID_MESSAGE_TYPE;
            }

            cms::BytesMessage* bytesMessage = dynamic_cast<cms::BytesMessage*>( message->message );

            if(strlen(value) > 0) {
                bytesMessage->writeString(value);
            }

            result = CMS_SUCCESS;

        } catch(cms::MessageFormatException& ex) {
            result = CMS_MESSAGE_FORMAT_ERROR;
        } catch(cms::MessageNotWriteableException& ex) {
            result = CMS_MESSAGE_NOT_WRITABLE;
        } catch(...) {
            result = CMS_ERROR;
        }
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status cms_readUTFFromBytesMessage(CMS_Message* message, char* value, int size) {

    cms_status result = CMS_ERROR;

    if(message != NULL && message->message != NULL && value != NULL) {

        try{

            if( message->type != CMS_BYTES_MESSAGE ) {
                return CMS_INVALID_MESSAGE_TYPE;
            }

            cms::BytesMessage* bytesMessage = dynamic_cast<cms::BytesMessage*>( message->message );

            std::string str = bytesMessage->readUTF();

            if(!str.empty()) {

                std::size_t pos = 0;
                for(; pos < str.size() && pos < (std::size_t)size - 1; ++pos) {
                    value[pos] = str.at(pos);
                }

                value[pos] = '\0';
            } else {
                value[0] = '\0';
            }

            result = CMS_SUCCESS;

        } catch(cms::MessageFormatException& ex) {
            value[0] = '\0';
            result = CMS_MESSAGE_FORMAT_ERROR;
        } catch(cms::MessageNotReadableException& ex) {
            value[0] = '\0';
            result = CMS_MESSAGE_NOT_READABLE;
        } catch(...) {
            value[0] = '\0';
            result = CMS_ERROR;
        }
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////
cms_status cms_writeUTFToBytesMessage(CMS_Message* message, const char* value) {

    cms_status result = CMS_ERROR;

    if(message != NULL && message->message != NULL && value != NULL) {

        try{

            if( message->type != CMS_BYTES_MESSAGE ) {
                return CMS_INVALID_MESSAGE_TYPE;
            }

            cms::BytesMessage* bytesMessage = dynamic_cast<cms::BytesMessage*>( message->message );

            if(strlen(value) > 0) {
                bytesMessage->writeUTF(value);
            }

            result = CMS_SUCCESS;

        } catch(cms::MessageFormatException& ex) {
            result = CMS_MESSAGE_FORMAT_ERROR;
        } catch(cms::MessageNotWriteableException& ex) {
            result = CMS_MESSAGE_NOT_WRITABLE;
        } catch(...) {
            result = CMS_ERROR;
        }
    }

    return result;
}
