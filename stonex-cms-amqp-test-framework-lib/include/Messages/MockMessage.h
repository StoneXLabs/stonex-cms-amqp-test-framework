#pragma once

#include <string>
#include <MessageContent/MessageTestField.h>

class MockMessage
{
public:
	~MockMessage() = default;
	virtual std::string timeStamp() const;
	virtual std::string messageCount(long long count) const;
	virtual std::string messageProperties(const std::vector <MessageTestField*> &properties) const;
};

