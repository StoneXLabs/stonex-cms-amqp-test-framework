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

#include "MessageReceiver/VeryfyingMessageReceiver.h"

#include <chrono>

#include <API/CMSQueue.h>
#include <API/CMSTopic.h>
#include <API/CMSTemporaryQueue.h>
#include <API/CMSTemporaryTopic.h>

#include <API/CMSTextMessage.h>
#include <API/CMSBytesMessage.h>

#include <UnitUnderTest/CMSClientTestUnit.h>
#include <Verifier/MessageReceiverVerifier.h>
#include <TestEventWrapperFactory/EventWrapperFactory.h>
#include <MessageListener/VeryfingMessageListener.h>



VeryfyingMessageReceiver::VeryfyingMessageReceiver(CMSMessageListenerFactory* messageListenerFactory, TestNotifier& notifier, MessageReceiverVerifier* verifier)
	:TestMessageReceiver(messageListenerFactory, notifier),
	mVerifiers{verifier}
{
	mLastReceived = std::chrono::system_clock::now();
}

void VeryfyingMessageReceiver::received(EventStatus status)
{
	mLastReceived = std::chrono::system_clock::now();
}

VeryfyingMessageReceiver::~VeryfyingMessageReceiver()
{
	std::for_each(std::begin(mMessageListeners), std::end(mMessageListeners), [this](cms::MessageListener* item) {
		if (item) {
			if (auto listener = dynamic_cast<VeryfingMessageListener*>(item))
			{
				onMessageReceived(listener->status());
			}

			delete item;
		}
	});
}



void VeryfyingMessageReceiver::wait()
{
	while (!receivedTimeoutReached());


	std::cout << "no message Received since " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - mLastReceived).count() << "[ms]" << std::endl;
}


bool VeryfyingMessageReceiver::receivedTimeoutReached()
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - mLastReceived).count() > 10000 ;
}
