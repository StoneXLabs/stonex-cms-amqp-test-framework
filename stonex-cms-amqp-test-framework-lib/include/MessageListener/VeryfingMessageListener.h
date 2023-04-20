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
#include <TestEventListener/CMSMessageListener.h>
#include <MessageReceiver/TestMessageReceiver.h>
#include <TestEventWrapperFactory/EventWrapperFactory.h>
#include <Verifier/BaseVerifier.h>
#include <Verifier/EventStatus.h>

#include <Metrics/SizeChecker.h>
#include <Metrics/MessageCounter.h>

class VeryfingMessageListener : public CMSMessageListener, public MessageCounter, public SizeChecker
{
public:

	VeryfingMessageListener(const std::string& id, TestMessageReceiver* parent, std::shared_ptr<BaseVerifier> verifier, EventWrapperFactory* eventWrapperFactory);
	~VeryfingMessageListener();
	void onMessage(const cms::Message* message) override;
	EventStatus status() const;

private:
	const std::string mId{};
	TestMessageReceiver* mParent;
	std::shared_ptr<BaseVerifier> mMessageVerifier;
	EventWrapperFactory* mEventWrapperFactory;
};