#include <iostream>
#include <fstream>
#include <sstream>
#include "taskManager.h"

int main()
{
	std::fstream schedulesFile("schedules.txt", std::ios::in);

	std::stringstream ssBuffer;
	ssBuffer << schedulesFile.rdbuf();
	auto schedulesSTR = ssBuffer.str();
	std::cout << "Input string:\n" << schedulesSTR << "\n";
	TaskManager tManager;
	tManager.parseInputSTR(schedulesSTR);
}