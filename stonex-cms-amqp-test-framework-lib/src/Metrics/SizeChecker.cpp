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
#include <fmt/format.h>

#include <Metrics/SizeChecker.h>

#include <cms/BytesMessage.h>
#include <cms/TextMessage.h>
#include <cms/MapMessage.h>
#include <cms/StreamMessage.h>

SizeChecker::SizeChecker(const std::string id, size_t maxMessageSize)
	:mId{ id },
	mSize{maxMessageSize}
 {
 }

EventStatus SizeChecker::onMessage(const cms::Message* message)
{
	size_t size;

	if (auto mes = dynamic_cast<const cms::BytesMessage*>(message))
	{
		size = mes->getBodyLength();
	}
	else if (auto mes = dynamic_cast<const cms::TextMessage*>(message))
	{
		
		size = mes->getText().size();
	}
	else if (auto mes = dynamic_cast<const cms::MapMessage*>(message))
	{
		size = sizeof(*mes);
	}
	else if (auto mes = dynamic_cast<const cms::StreamMessage*>(message))
	{
		size = sizeof(*mes);
	}

	if(size <= mSize)
		return EventStatus(true,mId,fmt::format("received message body size {}B max size {}B",size, mSize));
	else
		return EventStatus(false, mId, fmt::format("received message body size {}B exceeds max size {}B", size, mSize));
}

