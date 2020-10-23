#include <iostream>
#include <string>
#include <map>

std::map<std::string, int> userInputPool;

int main()
{
	std::cout << "Please enter sequence or ctrl+c to close\n";
	while (true)
	{
		std::cout << "> ";
		std::string userInputSTR;
		std::getline(std::cin, userInputSTR);
		std::cout << "Your input is: \'" << userInputSTR << "\' ";
		std::map<std::string, int>::iterator matchingUserInput = userInputPool.find(userInputSTR);
		if (matchingUserInput != userInputPool.end())
		{
			matchingUserInput->second++;
			std::cout << "been stored for " << matchingUserInput->second << " times\n";
		}
		else
		{
			std::cout << "will be stored now\n";
			userInputPool.insert(std::pair<std::string, int>(userInputSTR, 1));
		}
	}
	return 0;
}