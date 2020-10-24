#pragma once
#include <string>
#include <vector>
#include <algorithm>

#include "utils.h"

class Task
{
public:
	std::string name;
	std::vector<std::string> prerequisites;
	static void parseInputSTR(const std::string& schedulesSTR, std::vector<Task>& pool)
	{
		auto tasksSTR = stringSplit(schedulesSTR, '\n');
		for (auto& taskSTR : tasksSTR)
		{
			auto prerequisites = stringSplit(taskSTR, ' ');
			if (prerequisites.size() > 0)
			{
				//remove ':' from task name
				prerequisites[0].erase(prerequisites[0].end() - 1, prerequisites[0].end());
				//looking for self dependency
				if (std::find(prerequisites.begin() + 1, prerequisites.end(), prerequisites[0]) == prerequisites.end())
				{
					Task tmpTask;
					tmpTask.name = prerequisites[0];
					prerequisites.erase(prerequisites.begin());//removes task itself from input
					tmpTask.prerequisites = prerequisites;
					pool.push_back(tmpTask);
				}
				else
				{
					throw std::exception("self depended task founded");
				}
			}
		}
	}

	static void validateTasks(const std::vector<Task>& pool, std::vector<Task>::const_iterator& rootTaskITR)
	{
		std::vector<std::vector<Task>::const_iterator> rootTasks;
		for (auto taskITR = pool.begin(); taskITR < pool.end(); taskITR++)
		{
			if (taskITR->prerequisites.size() == 0)
			{
				rootTasks.push_back(taskITR);
			}
		}
		if (rootTasks.size() > 1)
		{
			std::ostringstream errStream;
			errStream << "multiple branches detected, list of founded tasks:\n";
			for (auto& task : rootTasks)
			{
				errStream << task->name << '\n';
			}
			throw std::exception(errStream.str().c_str());
		}
		if (rootTasks.size() == 0)
		{
			throw std::exception("no root task founded, probably exist cyclic dependency");
		}
		for (auto& task : pool)
		{
			for (auto& prerequisite : task.prerequisites)
			{
				if (std::count_if(pool.begin(), pool.end(), [prerequisite](Task t) { return t.name == prerequisite; }) == 0)
				{
					std::ostringstream errStream;
					errStream << "unresolvable dependencies founded, task name:\n" << prerequisite;
					throw std::exception(errStream.str().c_str());
				}
			}
		}
		rootTaskITR = rootTasks[0];
	}

	static int countStepsNeeded(const std::vector<Task>& pool, std::vector<Task>::const_iterator& rootTaskITR)
	{
		size_t stepsNeeded = 1;
		std::vector<std::vector<Task>::const_iterator> currStepTasks{ rootTaskITR };
		while (stepsNeeded < pool.size())
		{
			std::vector<std::vector<Task>::const_iterator> nextStepTasks;
			for (auto& currStepTask : currStepTasks)
			{
				for (auto taskITR = pool.begin(); taskITR < pool.end(); taskITR++)
				{
					if (std::find(taskITR->prerequisites.begin(), taskITR->prerequisites.end(), currStepTask->name) != taskITR->prerequisites.end())
					{
						if (std::find(currStepTask->prerequisites.begin(), currStepTask->prerequisites.end(), taskITR->name) != currStepTask->prerequisites.end())
						{
							std::ostringstream errStream;
							errStream << "cyclic dependency founded, task names:\n" << taskITR->name << '\n' << currStepTask->name;
							throw std::exception(errStream.str().c_str());
						}
						nextStepTasks.push_back(taskITR);
					}
				}
			}
			if (nextStepTasks.size() == 0)
			{
				break;
			}
			stepsNeeded++;
			currStepTasks = nextStepTasks;
		}
		if (stepsNeeded == 1 && pool.size() > 1)
		{
			throw std::exception("multiple branches detected");
		}
		return stepsNeeded;
	}
};
