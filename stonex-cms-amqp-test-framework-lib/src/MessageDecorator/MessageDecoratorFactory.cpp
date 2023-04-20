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

#include <MessageDecorator/MessageDecoratorFactory.h>
#include <MessageDecorator/ApplicationPropertyDecorator.h>
#include <MessageDecorator/CMSPropertyDecorator.h>
#include <MessageDecorator/ApplicationPropertyDecorator.h>
#include <MessageDecorator/CMSDestinationDecorator.h>

#include <MessageContent/MessageTestField.h>

#include <Configuration/MessageSenderConfiguration.h>

CMSMessageDecorator * MessageDecoratorFactory::create(const TestCaseProducerConfiguration& config) const
{
	CMSMessageDecorator* decorator{ nullptr };
	if (auto sender_config = dynamic_cast<const interoperability_tests::config::producer::MessageSenderConfiguration*>(&config))
	{

		std::for_each(std::cbegin(sender_config->properties()), std::cend(sender_config->properties()), [&decorator](const MessageTestField* item) {

			CMSMessageDecorator* current_item{ nullptr };

			switch (item->type())
			{

			case FIELD_TYPE::BOOLEANPROPERTY:
			case FIELD_TYPE::BYTEPROPERTY:
			case FIELD_TYPE::DOUBLEPROPERTY:
			case FIELD_TYPE::FLOATPROPERTY:
			case FIELD_TYPE::INTPROPERTY:
			case FIELD_TYPE::LONGPROPERTY:
			case FIELD_TYPE::SHORTPROPERTY:
			case FIELD_TYPE::STRINGPROPERTY:
				current_item = new ApplicationPropertyDecorator(item);
				break;
			case FIELD_TYPE::CMS_CORRELATION_ID:
			case FIELD_TYPE::CMS_DELIVERY_MODE:
			case FIELD_TYPE::CMS_EXPIRATION:
			case FIELD_TYPE::CMS_MESSAGE_ID:
			case FIELD_TYPE::CMS_PRIORITY:
			case FIELD_TYPE::CMS_REDELIVERED:
			case FIELD_TYPE::CMS_TIMESTAMP:
			case FIELD_TYPE::CMS_TYPE:
				current_item = new CMSPropertyDecorator(item);
				break;
			case FIELD_TYPE::CMS_DESTINATION:
			case FIELD_TYPE::CMS_REPLY_TO:
				current_item = new CMSDestinationDecorator(item);
				break;
			default:
				break;
			}

			if (decorator)
				decorator->addNext(current_item);
			else
				decorator = current_item;

		});
	}


	return decorator;
}
