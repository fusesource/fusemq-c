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

#ifndef _CMS_SINGLECONNECTIONTESTCASE_H_
#define _CMS_SINGLECONNECTIONTESTCASE_H_

#include <CMSTestCase.h>

#include <cms.h>

namespace cms {

	class SingleConnectionTestCase : public CMSTestCase {
	protected:

		CMS_ConnectionFactory* factory;
		CMS_Connection* connection;
		CMS_Session* session;

	public:

		SingleConnectionTestCase();
		virtual ~SingleConnectionTestCase();

		virtual void setUp();
		virtual void tearDown();

	protected:

		void drainDestination(CMS_Destination* destination);

	};

}

#endif /* _CMS_SINGLECONNECTIONTESTCASE_H_ */
