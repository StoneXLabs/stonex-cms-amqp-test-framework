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

#include <memory>
#include <ConfigurationParser/TestSuiteJsonConfigParser.h>
#include <MessageSender/TestMessageSenderFactory.h>
#include <TestSuite/TestFunctionRegister.h>
#include <Notifier/StdOutTestObserver.h>
#include <StdOutLogger/StdOutLogger.h>
#include <TestSuite/TestRunner.h>
#include <MessageReceiver/MessageReceiverFactory.h>
#include <SpdLogLogger/SpdLogLogger.h>
#include <Log4CxxLogger/Log4CxxLogger.h>

#include <TestSuite/TestCasePerformer.h>


TEST_CASE_STATUS test_fun(CMSClientTestUnit* a, TestCasePerformer* b) {

	b->sendAll();
	std::this_thread::sleep_for(std::chrono::seconds(3));
	return TEST_CASE_STATUS::FINISHED;
};

int main() {

	auto sender_factory = new stonex::messaging::test::TestSenderFactory();

	{
		TestSuiteJsonConfigParser parser("test_case_all.config");
		auto suite_config = parser.createConfiguration();

		TestFunctionRegister test_register;
		test_register.registerTestFunction("test_function_1", test_fun);

		StdOutTestObserver testObserver;
		MessageReceiverFactory dummy;
		std::shared_ptr<StonexLogger> logger = std::make_shared<StdOutLogger>();
		logger->configure("");

		TestRunner testRunner(parser, test_register, dummy, *sender_factory, &testObserver, logger);
		testRunner.run();

	}

	{
		TestSuiteJsonConfigParser parser("test_case_all_protobuf.config");
		auto suite_config = parser.createConfiguration();

		TestFunctionRegister test_register;
		test_register.registerTestFunction("test_function_1", test_fun);

		StdOutTestObserver testObserver;
		MessageReceiverFactory dummy;
		std::shared_ptr<StonexLogger> logger = std::make_shared<StdOutLogger>();
		logger->configure("");

		TestRunner testRunner(parser, test_register, dummy, *sender_factory, &testObserver, logger);
		testRunner.run();

	}
	
	return 0;
}




