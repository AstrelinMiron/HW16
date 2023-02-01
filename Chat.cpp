#include <iostream>
#include "Chat.h"

const std::string RESET = "\033[0m";
const std::string RED = "\033[31m";
const std::string GREEN = "\033[32m";
const std::string YELLOW = "\033[33m";
const std::string BLUE = "\033[34m";
const std::string PURPLE = "\033[35m";
const std::string CYAN = "\033[36m";

void Chat::startChat()
{
	std::cout << PURPLE << "\n********** CONSOLE CHAT v0.0.1 **********\n\n" << RESET;
	work_ = true;
}

std::shared_ptr <User> Chat::getUserLogin(const std::string& login) const
{
	for (auto& user : userArr_)
	{
		if (login == user.getLogin())
		{
			return std::make_shared<User>(user);
		}
	}
	return nullptr;
}

std::shared_ptr <User> Chat::getUserName(const std::string& name) const
{
	for (auto& user : userArr_)
	{
		if (name == user.getName())
		{
			return std::make_shared<User>(user);
		}
	}
	return nullptr;
}

void Chat::showLoginMenu()
{
	std::cout << CYAN << "\n--- MAIN MENU ---\n" << RESET;
	currentUser_ = nullptr;
	char op;
	do
	{
		std::cout << " 1 - Login, 2 - Register, 0 - Logout\n" << GREEN << ">> " << RESET;
		std::cin >> op;

		switch (op)
		{
		case '1':
			userLogin();
			break;
		case '2':
			try
			{
				userRegistration();
			}
			catch (const std::exception& ex)
			{
				std::cout << ex.what() << std::endl;
			}
			break;
		case '0':
			work_ = false;
			break;

		default:
			std::cout << "Please enter a valid character: 1, 2 или 0\n";
		}
	} while (!currentUser_ && work_);
}

void Chat::userLogin()
{
	std::string login, password;
	char op;

	do
	{
		std::cout << CYAN << "\n--- CHAT LOGIN ---\n" << RESET;
		std::cout << "Login: ";
		std::cin >> login;
		std::cout << "Password: ";
		std::cin >> password;

		//Pointer to the current user (nullptr if the login is incorrect)
		currentUser_ = getUserLogin(login);

		//Checking the correctness of the entered login and password
		if (currentUser_ == nullptr || password != currentUser_->getPassword())
		{
			currentUser_ = nullptr;
			std::cout << "Invalid username or password. Enter any character to repeat or \"0\" to go to the main menu\n" << GREEN << ">> " << RESET;
			std::cin >> op;

			if (op == '0') { break;	}
		}

	} while (!currentUser_);
}

void Chat::userRegistration()
{
	std::cout << CYAN << "\n--- REGISTRATION ---\n" << RESET;

	std::string login, password, name;

	std::cout << "Login: ";
	std::cin >> login;

	//Checking the existence of the entered login
	if (getUserLogin(login) || login == "all")
	{
		throw UserLoginExp();
	}

	std::cout << "Password: ";
	std::cin >> password;
	std::cout << "Name: ";
	std::cin >> name;

	//Checking if the entered name exists
	if (getUserName(name))
	{
		throw UserNameExp();
	}

	User user = User(login, password, name);
	userArr_.push_back(user);
	currentUser_ = std::make_shared <User>(user);
}

void Chat::showUserMenu()
{
	char op;
	std::cout << "Hello, " << currentUser_->getLogin();
	while (currentUser_)
	{
		std::cout << "\n1 - Show chat, 2 - Add message, 3 - Show all users, 0 - Exit\n" << GREEN << ">> "<< RESET;
		std::cin >> op;

		switch (op)
		{
		case '1':
			showChat();
			break;
		case '2':
			addMessage();
			break;
		case '3':
			showAllUsers();
			break;
		case '0':
			currentUser_ = nullptr;
			break;

		default:
			std::cout << "Please enter a valid character: 1, 2 или 3\n";
		}
	}
}

void Chat::addMessage()
{
	std::string to, text;
	std::cout << CYAN << "\n--- SENDING A MESSAGE ---\n" << RESET;
	std::cout << "Enter a recipient name or type \"all\" to send the message to all users: ";
	std::cin >> to;
	//Checking if a recipient exists by name
	if (!((to == "all") || getUserName(to)))
	{
		std::cout << "Error! Invalid recipient name entered\n";
		return;
	}

	std::cout << "Enter your message: ";
	std::cin.ignore();
	getline(std::cin, text);
	
	if (to == "all")
	{
		messageArr_.push_back(Message{ currentUser_->getLogin(), "all", text });
	}

	else
	{
		messageArr_.push_back(Message{ currentUser_->getLogin(), getUserName(to)->getLogin(), text });
	}
}

void Chat::showChat() const
{
	std::string from, to;
	std::cout << CYAN << "\n--- MESSAGE HISTORY ---\n" << RESET;

	for (auto& message : messageArr_)
	{
		//Checking for a match between the logins of the current user and the sender / recipient and the match of the recipient with the keyword "all"
		if (currentUser_->getLogin() == message.getFrom() || currentUser_->getLogin() == message.getTo() || message.getTo() != "all")
		{
			from = (currentUser_->getLogin() == message.getFrom()) ? "me" : getUserLogin(message.getFrom())->getName();
		}

		if (message.getTo() == "all")
		{
			to = "(all)";
		}

		else
		{
			to = (currentUser_->getLogin() == message.getTo()) ? "me" : getUserLogin(message.getTo())->getName();
		}

		std::cout << "From: " << from << ", to: " << to << std::endl;
		std::cout << " Message: " << message.getText() << std::endl;
	}
	std::cout << CYAN << "\n--- --- ---\n" << RESET;
}

void Chat::showAllUsers() const
{
	std::cout << CYAN << "\n--- A LIST OF USERS ---\n" << RESET;

	for (auto& user : userArr_)
	{
		std::cout << user.getName();
		if (currentUser_->getLogin() == user.getLogin())
		{
			std::cout << " (me)";
		}
		std::cout << "" << std::endl;
	}
	std::cout << CYAN << "\n--- --- ---\n" << RESET;
}