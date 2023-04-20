/*
 * Copyright 2022 StoneX Financial Ltd.
 *
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

#pragma once

#include <Configuration/TestCaseMessageReceiverConfiguration.h>
#include <MessageContent/MessageTestField.h>

namespace interoperability_tests::config::consumer {

	class MessageReceiverConfiguration : public TestCaseMessageReceiverConfiguration
	{
	public:
		MessageReceiverConfiguration(const std::string consumerId, int message_count, const std::string& destination_type, const std::string& destination_address, const std::vector<MessageTestField*>& fields);

		int expectedMessagesCount() const;
		const std::vector<MessageTestField*>& properties() const;
		void addProperty(MessageTestField* property);
	private:
		const int mExpectedCount{ 0 };
		std::vector<MessageTestField*> mParameters;
	};

}