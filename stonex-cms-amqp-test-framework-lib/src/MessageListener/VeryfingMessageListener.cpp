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

#include <MessageListener/VeryfingMessageListener.h>
#include <Verifier/MessageVerifier.h>

VeryfingMessageListener::VeryfingMessageListener(const std::string & id, TestMessageReceiver * parent, std::shared_ptr<BaseVerifier> verifier, EventWrapperFactory * eventWrapperFactory)
	:MessageCounter(),
	SizeChecker(),
	mId{ id },
	mParent{ parent },
	mMessageVerifier{ verifier },
	mEventWrapperFactory{ eventWrapperFactory }
{
	if (mMessageVerifier)
	{
		if (auto verifier = dynamic_cast<MessageVerifier*>(mMessageVerifier.get()))
			expectedCount(verifier->expectCount());
	}
		
}

VeryfingMessageListener::~VeryfingMessageListener()
{
	
}

void VeryfingMessageListener::onMessage(const cms::Message * message)
{
	count(message);
	check(message);

	if (mMessageVerifier && mEventWrapperFactory && mParent) {
		mParent->onMessageReceived(mMessageVerifier->trigger(mEventWrapperFactory->create(message)));
		
	}
	delete message;

}
EventStatus VeryfingMessageListener::status() const
{
	auto receivedMessageCount = count();
	auto expectedMessageCount = expectedCount();

	if (receivedMessageCount == expectedMessageCount)
		return EventStatus(true, mId, "all expected messages received");
	else if (receivedMessageCount < expectedMessageCount)
		return EventStatus(false, mId, "missing " + std::to_string( expectedMessageCount - receivedMessageCount) + " messages");
	else if (receivedMessageCount > expectedMessageCount)
		return EventStatus(false, mId, "expected messages overflow " + std::to_string(receivedMessageCount - expectedMessageCount) + " messages");

}