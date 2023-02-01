#include <iostream>
#include "Chat.h"

int main()
{
	Chat chat;
	chat.startChat();

	while (chat.work())
	{
		chat.showLoginMenu();
		while (chat.getCurrentUser())
		{
			chat.showUserMenu();
		}
	}
	return 0;
}
