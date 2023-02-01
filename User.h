#pragma once
#include <string>

class User
{
private:
	std::string login_;
	std::string password_;
	std::string name_;

public:
	User(const std::string& login, const std::string& password, const std::string& name) : login_(login), password_(password), name_(name) {}

	const std::string& getLogin() const { return login_; }
	const std::string& getName() const { return name_; }
	const std::string& getPassword() const { return password_; }

	void setName(const std::string& name) { name_ = name; }
	void setPassword(const std::string& password) { password_ = password; }
};