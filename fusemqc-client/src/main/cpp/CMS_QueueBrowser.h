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

#include <cms.h>

#ifndef _CMS_QUEUEBROWSER_WRAPPER_H_
#define _CMS_QUEUEBROWSER_WRAPPER_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Given a Session instance, create a new Queue Browser for the supplied destination.
 *
 * @param session
 *      The Session that is to be used to create the new Queue Browser.
 * @param destination
 *      The Destination that this Queue Browser will subscribe to.
 * @param browser
 *      The memory location where the newly allocated Queue Browser instance is to be stored.
 * @param selector
 *      The selector used to filter Messages on this Queue Browser, can be NULL.
 *
 * @return result code indicating the success or failure of the operation.
 */
cms_status cms_createQueueBrowser(CMS_Session* session, CMS_Destination* destination,
							      CMS_QueueBrowser** browser, const char* selector);

/**
 * Indicates whether or not the QueueBrowser has additional messages available to browser.
 *
 * @param browser
 *      The Queue Browser that is to be queried.
 * @param hasMore
 *      The address to store the boolean result of this operation.
 *
 * @return result code indicating the success or failure of the operation.
 */
cms_status cms_browserHasMoreMessages(CMS_QueueBrowser* browser, int* hasMore);

/**
 * Checks for a Message that's available and stores it in the Location passed to this
 * method.  If a message is not immediately available then this method returns and the
 * message store location is set to null.  Once a browser returns a null message it
 * indicates that there are no more message available the result will be null.
 *
 * @param browser
 *      The Queue Browser that is to be used to try and retrieve the next browsable message.
 * @param message
 *      The Memory location where a newly received message is to be stored.
 *
 * @return result code indicating the success or failure of the operation.
 */
cms_status cms_browserGetNextMessages(CMS_QueueBrowser* browser, CMS_Message** message);

/**
 * Destroys the given Queue Browser instance.
 *
 * @param browser
 *      The Queue Browser that is to be destroyed.
 *
 * @return result code indicating the success or failure of the operation.
 */
cms_status cms_destroyQueueBrowser(CMS_QueueBrowser* browser);

#ifdef __cplusplus
}
#endif

#endif /* _CMS_QUEUEBROWSER_WRAPPER_H_ */
