#pragma once
#include "task.h"
#include "utils.h"
#include <map>

class TaskManager
{
private:
	std::map<std::string, bool> taskStatusPool;
	std::vector<Task> tasksPool;

public:
	void parseInputSTR(const std::string& schedulesSTR);
};

