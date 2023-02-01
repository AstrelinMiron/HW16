#pragma once
#include "User.h"

class Message
{
private:
	std::string messageFrom_;
	std::string messageTo_;
	std::string text_;

public:
	Message(const std::string& messageFrom, const std::string& messageTo, const std::string& text) : messageFrom_(messageFrom), messageTo_(messageTo), text_(text) {}

	const std::string& getFrom() const { return messageFrom_; }
	const std::string& getTo() const { return messageTo_; }
	const std::string& getText() const { return text_; }
};