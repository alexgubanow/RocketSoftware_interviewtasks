#include "taskManager.h"

inline void TaskManager::parseInputSTR(const std::string& schedulesSTR)
{
	auto tasksSTR = stringSplit(schedulesSTR, '\n');
	for (auto& taskSTR : tasksSTR)
	{
		if (taskSTR[0] == 'z')
		{
			int sdacsd = 0;
		}
		auto prerequisites = stringSplit(taskSTR, ' ');
		if (prerequisites.size() > 0)
		{
			Task tmpTask(prerequisites[0]);
			prerequisites.erase(prerequisites.begin());//removes task itself from input
			tmpTask._prerequisites = prerequisites;
			tasksPool.push_back(tmpTask);
			taskStatusPool.insert(std::pair<std::string, bool>(tmpTask._name, false));
		}
	}
}
