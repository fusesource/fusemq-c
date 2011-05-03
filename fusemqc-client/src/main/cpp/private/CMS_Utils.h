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

#ifndef CMS_UTILS_H_
#define CMS_UTILS_H_

#include <cms.h>

#include <cms/CMSException.h>
#include <cms/CMSSecurityException.h>
#include <cms/MessageEOFException.h>
#include <cms/MessageFormatException.h>
#include <cms/MessageNotReadableException.h>
#include <cms/MessageNotWriteableException.h>
#include <cms/InvalidClientIdException.h>
#include <cms/InvalidDestinationException.h>
#include <cms/InvalidSelectorException.h>
#include <cms/IllegalStateException.h>
#include <cms/UnsupportedOperationException.h>

/**
 * Macro for catching exceptions in CMS wrapper methods where
 * the connection is not present or not available for storing
 * the last connection related exception, from the type of
 * exception this macro sets the provided result value to an
 * appropriate CMS Error value.
 *
 * @param result
 * 		The result value where the type of error is indicated.
 */
#define CMS_CATCH_EXCEPTION( result ) \
    catch( cms::CMSSecurityException& ex ){ \
        result = CMS_SECURITY_ERROR; \
    } catch( cms::IllegalStateException& ex ){ \
        result = CMS_ILLEGAL_STATE; \
    } catch( cms::InvalidClientIdException& ex ){ \
        result = CMS_INVALID_CLIENTID; \
    } catch( cms::InvalidDestinationException& ex ){ \
        result = CMS_INVALID_DESTINATION; \
    } catch( cms::InvalidSelectorException& ex ){ \
        result = CMS_INVALID_SELECTOR; \
    } catch( cms::MessageEOFException& ex ){ \
        result = CMS_MESSAGE_EOF; \
    } catch( cms::MessageFormatException& ex ){ \
        result = CMS_MESSAGE_FORMAT_ERROR; \
    } catch( cms::MessageNotReadableException& ex ){ \
        result = CMS_MESSAGE_NOT_READABLE; \
    } catch( cms::MessageNotWriteableException& ex ){ \
        result = CMS_MESSAGE_NOT_WRITABLE; \
    } catch( cms::UnsupportedOperationException& ex ){ \
        result = CMS_UNSUPPORTEDOP; \
    } catch( cms::CMSException& ex ){ \
        result = CMS_ERROR; \
    } catch( std::exception& ex ){ \
        result = CMS_ERROR; \
    } catch(...) { \
        result = CMS_ERROR; \
    }

/**
 * Macro for catching and storing an exception of some type.
 *
 * The Exception is cloned into the CMS_Connection struct's stored
 * exception field for use in retrieving the last error message.
 *
 * @param connection
 * 		The CMS_Connection instance to clone the exception into.
 * @param result
 * 		The result value where the error type is stored.
 */
#define CMS_CATCH_CONNECTION_EXCEPTION( connection, result ) \
    catch( cms::CMSSecurityException& ex ){ \
        ex.setMark( __FILE__, __LINE__ ); \
        delete connection->lastException; \
        connection->lastException = new CMSSecurityException( ex ); \
        result = CMS_SECURITY_ERROR; \
    } catch( cms::IllegalStateException& ex ){ \
        ex.setMark( __FILE__, __LINE__ ); \
        delete connection->lastException; \
        connection->lastException = new IllegalStateException( ex ); \
        result = CMS_ILLEGAL_STATE; \
    } catch( cms::InvalidClientIdException& ex ){ \
        ex.setMark( __FILE__, __LINE__ ); \
        delete connection->lastException; \
        connection->lastException = new InvalidClientIdException( ex ); \
        result = CMS_INVALID_CLIENTID; \
    } catch( cms::InvalidDestinationException& ex ){ \
        ex.setMark( __FILE__, __LINE__ ); \
        delete connection->lastException; \
        connection->lastException = new InvalidDestinationException( ex ); \
        result = CMS_INVALID_DESTINATION; \
    } catch( cms::InvalidSelectorException& ex ){ \
        ex.setMark( __FILE__, __LINE__ ); \
        delete connection->lastException; \
        connection->lastException = new InvalidSelectorException( ex ); \
        result = CMS_INVALID_SELECTOR; \
    } catch( cms::MessageEOFException& ex ){ \
        ex.setMark( __FILE__, __LINE__ ); \
        delete connection->lastException; \
        connection->lastException = new MessageEOFException( ex ); \
        result = CMS_MESSAGE_EOF; \
    } catch( cms::MessageFormatException& ex ){ \
        ex.setMark( __FILE__, __LINE__ ); \
        delete connection->lastException; \
        connection->lastException = new MessageFormatException( ex ); \
        result = CMS_MESSAGE_FORMAT_ERROR; \
    } catch( cms::MessageNotReadableException& ex ){ \
        ex.setMark( __FILE__, __LINE__ ); \
        delete connection->lastException; \
        connection->lastException = new MessageNotReadableException( ex ); \
        result = CMS_MESSAGE_NOT_READABLE; \
    } catch( cms::MessageNotWriteableException& ex ){ \
        ex.setMark( __FILE__, __LINE__ ); \
        delete connection->lastException; \
        connection->lastException = new MessageNotWriteableException( ex ); \
        result = CMS_MESSAGE_NOT_WRITABLE; \
    } catch( cms::UnsupportedOperationException& ex ){ \
        ex.setMark( __FILE__, __LINE__ ); \
        delete connection->lastException; \
        connection->lastException = new UnsupportedOperationException( ex ); \
        result = CMS_UNSUPPORTEDOP; \
    } catch( cms::CMSException& ex ){ \
        ex.setMark( __FILE__, __LINE__ ); \
        delete connection->lastException; \
        connection->lastException = new CMSException( ex ); \
        result = CMS_ERROR; \
    } catch( std::exception& ex ){ \
        delete connection->lastException; \
        connection->lastException = new CMSException( ex.what(), NULL ); \
        result = CMS_ERROR; \
    } catch(...) { \
        delete connection->lastException; \
        connection->lastException = new CMSException( "Caught unknown error.", NULL ); \
        result = CMS_ERROR; \
    }

#endif /* CMS_UTILS_H_ */
