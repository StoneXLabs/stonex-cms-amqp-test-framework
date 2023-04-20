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

#include <MessageContent/MessageTestField.h>
#include <ConfigParser/TestSuiteJsonConfigParser.h>


namespace interoperability_tests::config::parser {

	class ConfigurationParser : public TestSuiteJsonConfigParser
	{
	public:
		ConfigurationParser(const std::string& configFile);
		TestCaseProducerConfiguration* createTestCaseProducerConfig(const std::string& configName, const boost::json::value& json) const override;
		TestCaseMessageReceiverConfiguration* createTestReceiverConfig(const std::string& configName, const boost::json::value& json) const override;
		MessageTestField* createMessageFieldConfig(const std::string& configName, const boost::json::value& json) const;


	};

}