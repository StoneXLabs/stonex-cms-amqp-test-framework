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

#include <VerifierFactory/CompoundTestVerifier.h>
#include <Configuration/MessageReceiverConfiguration.h>


#include <Verifier/MessageVerifier.h>

CompoundTestVerifier::CompoundTestVerifier(const TestCaseConfiguration & config, const FieldVerifierFactory& verifierFactory)
	: MessageReceiverVerifier(config),
	mFieldVerifierFactory(verifierFactory)
{
	if (!config.verifierConfig().messageExpectations().empty())
	{
			std::transform(std::cbegin(config.verifierConfig().messageExpectations()), std::cend(config.verifierConfig().messageExpectations()), std::begin(mVerifiers), [this](TestCaseMessageReceiverConfiguration* item) {
				
				MessageVerifier mv(*item);

				if (auto config = dynamic_cast<interoperability_tests::config::consumer::MessageReceiverConfiguration*>(item)){

					mv.expectCount(config->expectedMessagesCount());

					auto fields = config->properties();
					std::for_each(std::cbegin(fields), std::cend(fields), [&mv, this](const MessageTestField* field_item) {
						auto tmp = mFieldVerifierFactory.create(field_item->type(), true, true, field_item->valueString(), field_item->name());
						mv.addFieldVerifier(tmp);
					});
				
				}

				return std::make_shared<MessageVerifier>(mv);

			});


	}
}

CompoundTestVerifier::~CompoundTestVerifier()
{
}

void CompoundTestVerifier::addVerifier(TestCaseMessageReceiverConfiguration& config) {

	if (auto verifier_config = dynamic_cast<interoperability_tests::config::consumer::MessageReceiverConfiguration*>(&config))
	{

		auto mv = std::make_shared<MessageVerifier>(config);
		mv->expectCount(verifier_config->expectedMessagesCount());


		auto fields = verifier_config->properties();
		std::for_each(std::cbegin(fields), std::cend(fields), [&mv, this](MessageTestField* item) {
			auto tmp = mFieldVerifierFactory.create(item->type(), true, true, item->valueString());
			mv->addFieldVerifier(tmp);
		});


		mVerifiers.push_back(mv);
	}
	else
		MessageReceiverVerifier::addVerifier(config);

}