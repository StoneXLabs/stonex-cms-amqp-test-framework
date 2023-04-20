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

#include <Configuration/ConfigurationParser.h>
#include <Configuration/MessageReceiverConfiguration.h>
#include <Configuration/MessageSenderConfiguration.h>

#include <MessageContent/MessageDestinationTestField.h>

interoperability_tests::config::parser::ConfigurationParser::ConfigurationParser(const std::string & configFile)
	:TestSuiteJsonConfigParser(configFile)
{
}

TestCaseProducerConfiguration * interoperability_tests::config::parser::ConfigurationParser::createTestCaseProducerConfig(const std::string & configName, const boost::json::value & json) const
{
	if (json.is_object())
	{
		int message_count{ -1 };
		std::string message_file;
		std::string message_factory;

		if (auto tmp_message_count = json.as_object().if_contains("message_count"); tmp_message_count && tmp_message_count->is_int64())
			message_count = tmp_message_count->as_int64();

		if (auto tmp_message_file = json.as_object().if_contains("message_factory"); tmp_message_file && tmp_message_file->is_string())
			message_factory = tmp_message_file->as_string().c_str();

		if (auto tmp_message_file = json.as_object().if_contains("message_file"); tmp_message_file && tmp_message_file->is_string())
			message_file = tmp_message_file->as_string().c_str();

		if (auto tmp_message_fields = json.as_object().if_contains("properties"); tmp_message_fields && tmp_message_fields->is_object())
		{
			std::vector<MessageTestField*> messageFields;

			std::transform(std::cbegin(tmp_message_fields->as_object()), std::cend(tmp_message_fields->as_object()), std::back_inserter(messageFields), [this](const boost::json::object::value_type& obj) {
				return createMessageFieldConfig(obj.key_c_str(), obj.value());
			});

			return new producer::MessageSenderConfiguration(configName, message_factory, message_count, message_file, messageFields);
		}
		else
			return new producer::MessageSenderConfiguration(configName, message_factory, message_count, message_file, {});

	}
	else
		return new producer::MessageSenderConfiguration(configName, {}, 0, {}, {});
}
#include <iostream>
TestCaseMessageReceiverConfiguration * interoperability_tests::config::parser::ConfigurationParser::createTestReceiverConfig(const std::string & configName, const boost::json::value & json) const
{
	if (json.is_object())
	{
		int message_count{ -1 };
		std::string message_file;
		std::string destination_type;
		std::string destination_address;

		if (auto tmp_message_count = json.as_object().if_contains("message_count"); tmp_message_count && tmp_message_count->is_int64())
			message_count = tmp_message_count->as_int64();

		if (auto tmp_dest_type = json.as_object().if_contains("dest_type"); tmp_dest_type && tmp_dest_type->is_string())
			destination_type = tmp_dest_type->as_string().c_str();

		if (auto tmp_dest_address = json.as_object().if_contains("address"); tmp_dest_address && tmp_dest_address->is_string())
			destination_address = tmp_dest_address->as_string().c_str();

		if (auto tmp_message_fields = json.as_object().if_contains("properties"); tmp_message_fields && tmp_message_fields->is_object())
		{
			std::vector<MessageTestField*> messageFields;

			std::transform(std::cbegin(tmp_message_fields->as_object()), std::cend(tmp_message_fields->as_object()), std::back_inserter(messageFields), [this](const boost::json::object::value_type& obj) {
				auto t = createMessageFieldConfig(obj.key_c_str(), obj.value());
				return createMessageFieldConfig(obj.key_c_str(), obj.value());
			});
			
			return new consumer::MessageReceiverConfiguration(configName, message_count, destination_type, destination_address, messageFields);
		}
		else
			return new consumer::MessageReceiverConfiguration(configName, message_count, destination_type, destination_address, {});

	}
	else
		return new consumer::MessageReceiverConfiguration(configName, 0, {}, {}, {});
}

MessageTestField* interoperability_tests::config::parser::ConfigurationParser::createMessageFieldConfig(const std::string & configName, const boost::json::value & json) const
{
	if (configName == "reply_to")
	{
		if (json.is_object())
		{
			auto dest = json.as_object();
			auto type = dest.at("dest_type").as_string().c_str();
			auto address = dest.at("address").as_string().c_str();
			return new MessageDestinationTestField(FIELD_TYPE::CMS_REPLY_TO, type, address);
		}
	}
	else if (configName == "destination")
	{
		if (json.is_object())
		{
			auto dest = json.as_object();
			auto type = dest.at("dest_type").as_string().c_str();
			auto address = dest.at("address").as_string().c_str();
			return new MessageDestinationTestField(FIELD_TYPE::CMS_DESTINATION, type, address);
		}
	}
	else 
	{
		return new MessageTestField(fromKeyValue(configName, json), configName, values_string(json));
	}


	return nullptr;
}
