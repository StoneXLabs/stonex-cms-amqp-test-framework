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

#include <MessageDecorator/CMSDestinationDecorator.h>

CMSDestinationDecorator::CMSDestinationDecorator(const MessageTestField* field)
	:MessageDestinationTestField(field->type(),field->name(), field->valueString()),
	CMSMessageDecorator(*field),
	MessageTestField(*field)
{
}

void CMSDestinationDecorator::decorate(cms::Message * mes, cms::Session * sess) const
{
	switch (mFieldType)
	{
	case FIELD_TYPE::CMS_DESTINATION:
		if (auto dest = createDestination(sess); dest != nullptr)
			mes->setCMSDestination(dest);
		break;
	case FIELD_TYPE::CMS_REPLY_TO:
		if (auto dest = createDestination(sess); dest != nullptr)
			mes->setCMSReplyTo(dest);
		break;
	default:
		break;
	}


	CMSMessageDecorator::decorate(mes, sess);
}

cms::Destination * CMSDestinationDecorator::createDestination(cms::Session * sess) const
{
	if (name() == "queue")
	{
		return sess->createQueue(valueString());
	}
	else if (name() == "topic")
	{
		return sess->createTopic(valueString());
	}
	else if (name() == "temporary-queue")
	{
		return sess->createTemporaryQueue();
	}
	else if (name() == "temporary-topic")
	{
		return sess->createTemporaryTopic();
	}
}
