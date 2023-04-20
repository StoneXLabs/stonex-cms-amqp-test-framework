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

#include <MessageDecorator/ApplicationPropertyDecorator.h>
#include <cms/Message.h>

ApplicationPropertyDecorator::ApplicationPropertyDecorator(const MessageTestField* field)
	:CMSMessageDecorator(*field),
	MessageTestField(*field)
{
}

void ApplicationPropertyDecorator::decorate(cms::Message * mes, cms::Session * sess) const
{
	switch (mFieldType)
	{
	case FIELD_TYPE::BOOLEANPROPERTY:
		mes->setBooleanProperty(mName, std::atoi(mValueString.c_str()));
		break;
	case FIELD_TYPE::BYTEPROPERTY:
		break;
	case FIELD_TYPE::DOUBLEPROPERTY:
		mes->setDoubleProperty(mName, std::stod(mValueString.c_str()));
		break;
	case FIELD_TYPE::FLOATPROPERTY:
		mes->setFloatProperty(mName, std::stof(mValueString.c_str()));
		break;
	case FIELD_TYPE::INTPROPERTY:
		mes->setIntProperty(mName, std::atoi(mValueString.c_str()));
		break;
	case FIELD_TYPE::LONGPROPERTY:
		mes->setLongProperty(mName, std::stod(mValueString.c_str()));
		break;
	case FIELD_TYPE::SHORTPROPERTY:
		mes->setShortProperty(mName, std::atoi(mValueString.c_str()));
		break;
	case FIELD_TYPE::STRINGPROPERTY:
		mes->setStringProperty(mName, mValueString.c_str());
		break;
	default:
		break;
	}

	CMSMessageDecorator::decorate(mes, sess);
}
