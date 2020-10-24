# RocketSoftware interview tasks solution
Originally it consist two tasks given in word files. It names efficient-memory and task-manager.
# efficient-memory task 
## long story short:
Your program should respond with number of times it has encountered a given input, in same time it should be comparably quick with 10 words and 1000000 words
## Choosen implementation:
I've decided to use std::map, since it has constant access time O(log N) and it is compably quick. Let's calculate log(10)=1, log(1000000)=6. It means with O(log N) access time will grow by 5 times. In my opinion 5 times increase is way better than 100000 times.
# task-manager task 
## long story short:
Your program should count how many steps needed to execute tasks from list. Tasks are expressed as string, where each tasks are separated by '\n',  task prerequisites goes after ':' and separated by ' '. Some inputs may contain cyclic/unresolvable dependencies, multiple branches etc. Need cater for such cases.
## Choosen implementation:
I've done this in three parts: parsing input, validating tasks and counting steps. On all steps I've implemented guards from possible wrong or broken input.
### Bad input hadling

On phase of parsing input program looking for self dependency, by comparing task name to all prerequisites of it.

On phase of validating program looking for:

- multiple branches. If more than one task with no prerequisites was founded, means there is multiple branches.
- cyclic dependencies. If no task with no prerequisites was founded, means there is cyclic/unresolvable dependencies.

On phase of counting steps can find unresolvable dependencies by comparing current step task prerequisites with name of next founded task name

### Steps counting

1. Find root task, which has no prerequisites, and mark it as one of current step tasks
2. Find all tasks, which has prerequisite of current step tasks
3. Increment step count, mark next step tasks as current

repeat 2 and 3 until step count is less than total count of tasks.

