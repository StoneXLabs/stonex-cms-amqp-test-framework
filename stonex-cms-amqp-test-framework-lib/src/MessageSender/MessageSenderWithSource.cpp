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

#include <MessageSender/MessageSenderWithSource.h>
#include <Verifier/EventStatus.h>

MessageSenderWithSource::MessageSenderWithSource(const TestCaseProducerConfiguration & params, CMSClientTestUnit & client_params, MessageSource* messageSource, CMSMessageDecorator* decorator, EventStatusObserver& parent)
	:MessageSender(params, client_params, parent),
	mMessagesAvailable{ params.messageToSend() },
	mMessageSource{messageSource},
	mMessageDecorator{ decorator }
{
	
}


bool MessageSenderWithSource::messageAvailable() const
{
	return mMessagesAvailable > 0;
}

bool MessageSenderWithSource::send(int msg_delay_ms)
{
	if (mMessagesAvailable  && mMessageSource)
	{
		if (auto message_body = mMessageSource->getMessage(); !message_body.empty())
		{
			auto amq_mes = mSession->createTextMessage(message_body);
			if (mMessageDecorator)
				mMessageDecorator->decorate(amq_mes, mSession);
			mProducer->send(amq_mes);
			mMessagesAvailable--;
			delete amq_mes;
			return true;
		}
		else 
		{
			mMessagesAvailable = 0;
			return false;
		}
		
	}
	else
	{
		return false;
	}
}

