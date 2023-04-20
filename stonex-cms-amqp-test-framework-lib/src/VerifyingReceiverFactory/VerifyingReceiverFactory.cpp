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

#include <VerifyingReceiverFactory/VerifyingReceiverFactory.h>

#include <Verifier/MessageReceiverVerifier.h>
#include <Verifier/TestVerifierFactory.h>
#include <MessageReceiver/VeryfyingMessageReceiver.h>
#include <MessageListener/VeryfingMessageListenerFactory.h>


VerifyingReceiverFactory::VerifyingReceiverFactory(TestVerifierFactory* verifierFactory, EventWrapperFactory* eventWrappdrFactory)
	:mVerifierFactory{ verifierFactory },
	mEventWrapperFactory{eventWrappdrFactory}
{
}

TestMessageReceiver * VerifyingReceiverFactory::create(const TestCaseConfiguration& config, TestNotifier& notifier) const
{
	if (mVerifiers) {
		delete mVerifiers;
		mVerifiers = nullptr;
	}

	if (mEventListenerFactory)
	{
		delete mEventListenerFactory;
		mEventListenerFactory = nullptr;
	}


	if (mVerifierFactory)
	{
		mVerifiers = mVerifierFactory->create(config);
		mEventListenerFactory = new VeryfingMessageListenerFactory(mVerifiers, mEventWrapperFactory);
		return new VeryfyingMessageReceiver(mEventListenerFactory, notifier, mVerifiers);
	}
	else
		return nullptr;
		
}
