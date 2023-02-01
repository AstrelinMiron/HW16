#pragma once
#include <vector>
#include <unordered_map>
#include <exception>
#include "Message.h"


struct UserLoginExp : public std::exception
{
	const char* what() const noexcept override 	{ return "Логин уже использован, введите другой вариант"; }
};

struct UserNameExp : public std::exception
{
	const char* what() const noexcept override { return "Имя уже использовано, введите другой вариант"; }
};

class Chat
{
private:
	//Array of users
	std::vector <User> userArr_;
	//Array of messages
	std::vector <Message> messageArr_;
	//Smart pointer to the current user
	std::shared_ptr <User> currentUser_ = nullptr;
	
	bool work_ = false;

	//Login to chat with username and password
	void userLogin();
	//Chat Registration
	void userRegistration();
	//Returns message history
	void showChat() const;
	//Returns a list of users
	void showAllUsers() const;
	//Sending a message
	void addMessage();

	//Returns a smart pointer to the required user by login, if it exists in the user base, or nullptr if not
	std::shared_ptr <User> getUserLogin(const std::string& login) const;
	//Returns a smart pointer to the required user by name if it exists in the user base or nullptr if not
	std::shared_ptr <User> getUserName(const std::string& name) const;

public:
	//Launching a chat
	void startChat();
	//Main chat menu
	void showLoginMenu();
	//Chat Menu
	void showUserMenu();
	//Method for keeping chat open
	bool work() const { return work_; }
	//Returns a smart pointer to the current user
	std::shared_ptr <User> getCurrentUser() const { return currentUser_; }
};