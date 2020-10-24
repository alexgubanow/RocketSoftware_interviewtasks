#include <iostream>
#include <fstream>
#include <sstream>

#include "task.h"

int main()
{
	std::fstream schedulesFile("schedules.txt", std::ios::in);

	std::stringstream ssBuffer;
	ssBuffer << schedulesFile.rdbuf();
	auto schedulesSTR = ssBuffer.str();
	std::cout << "Schedules from file:\n" << schedulesSTR << "\n";
	std::vector<Task> pool;
	try
	{
		Task::parseInputSTR(schedulesSTR, pool);
	}
	catch (const std::exception& ex)
	{
		std::cout << "Error while parsing:\n" << ex.what() << "\nClosing";
	}
	std::vector<Task>::const_iterator rootTaskName;
	try
	{
		Task::validateTasks(pool, rootTaskName);
	}
	catch (const std::exception& ex)
	{
		std::cout << "Error while validating:\n" << ex.what() << "\nClosing";
	}
	try
	{
		std::cout << "Given tasks can be executed in: " << Task::countStepsNeeded(pool, rootTaskName) << " steps\n";
	}
	catch (const std::exception& ex)
	{
		std::cout << "Error while counting steps:\n" << ex.what() << "\nClosing";
	}
}


