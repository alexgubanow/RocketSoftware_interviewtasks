#pragma once
#include "task.h"

void parseInputSTR(const std::string& schedulesSTR, std::vector<Task>& pool);
void validateTasks(const std::vector<Task>& pool);