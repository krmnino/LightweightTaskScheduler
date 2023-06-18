# Light-weight Task Scheduler
The Light-weight Task Scheduler is a flexible standalone program that allows launching tasks at a specific time and date. This program has been implemented entirely in C++ and requires no major dependencies.

## Repository Structure
- `src`: contains all the source files and `make` recipes required to build the `scheduler` executable.
- `testing`: contains testcases covering different aspects of the scheduler implementation.

## Requirements and Dependencies
- Ubuntu 18.04 or later
- C++17
- Make

## Build and Run
1. To build the binary, navigate to the `src` directory and issue the command `make release`. This will generate the `scheduler` binary.
2. Place the `scheduler` binary anywhere you want, as long as the directory has the necessary (r/w/x) permissions.
3. Create two directories named `tasks` and `scripts` in the same directory where the `scheduler` executable is located. 
4. The `tasks` directory should contain the configuration files that define a single task. The `scripts` directory should contain the scripts to be invoked by the task.
4. To run the binary, issue the command `./scheduler`. 
5. Once the `>>` characters are printed in the command prompt, indicates the scheduler is ready to take user input.

## Defining Tasks
A task is defined by a configuration file that can be found in the `tasks` directory. The configuration file must contain the following attributes:
|Attribute|Type|Description|Constraints and Formats|
|-|-|-|-|
`Name`|Required|A unique string identifier.|Maximum of 32 characters long.|
`Description`|Optional|A brief description of what the task does.|None.|
`ScriptFilename`|Required|The name of script file to be invoked by the task. For exmaple, it can be Bash shell script or a Python script.|Must match a file in the `scripts` directory.|
`Frequency`|Required|Indicates if the task is to run one or more times.|Either `Once`, `Hourly` , `Daily`, `Weekly`, `Monthly`, or `Yearly`.|
`Datetime`|Required|Indicates the datetime of when the task should start executing.|Either `HH:MM:SS`, `YYYY-MM-DD HH:MM:SS`, `WDAY HH:MM:SS`, or `YYYY-MM-DD`. See Setting Datetimes with Frequencies section for details.|

## Setting Datetimes with Frequencies
Not all datetime formats are compatible with every frequency value. Here are the compatible frequencies and datetimes:
- Once: `HH:MM:SS`, `YYYY-MM-DD HH:MM:SS`, `WDAY HH:MM:SS`, or `YYYY-MM-DD`.
- Hourly: `HH:MM:SS` or `YYYY-MM-DD HH:MM:SS`.
- Daily: `HH:MM:SS`, `YYYY-MM-DD HH:MM:SS`, or `WDAY HH:MM:SS`.
- Weekly: `HH:MM:SS`, `YYYY-MM-DD HH:MM:SS`, `WDAY HH:MM:SS`, or `YYYY-MM-DD`.
- Monthly: `HH:MM:SS`, `YYYY-MM-DD HH:MM:SS`, or `YYYY-MM-DD`.
- Yearly: `YYYY-MM-DD HH:MM:SS`, or `YYYY-MM-DD`.

## Commands
The scheduler is a command line based program; therefore, there is a set of commands defined that can be issued.
- `check registry`: Displays relevant information about the tasks loaded in the scheduler.
- `check task <task_name>`: Displays the full information about the specified task.
- `check status`: Displays operational information about the scheduler.
- `check output <task_name>`: Displays output of a specific task.
- `dump output <task_name>`: Generates output dump file from specified task name.
- `dump outputs <name1, name2, ...>`: Generates output dump files from specified list of task names.
- `dump events`: Generates a dump file containing all events recorded in the scheduler.
- `help`: Displays usage for all verbs.
- `help check`: Displays usage for the `check` verb only.
- `help remove`: Displays usage for the `remove` verb only.
- `help load`: Displays usage for the `load` verb only.
- `help reload`: Displays usage for the `reload` verb only.
- `load task <config_name>`: Load task in schdeuler from specified configuration filename.
- `load tasks <config_name1, config_name2, ...>`: Load multiple tasks in scheduler from specified list of configuration filenames.
- `load all`: Load all tasks defined in `tasks` directory.
- `remove task <task_name>`: Removes the specified task from the scheduler.
- `remove tasks <name1, name2, ...>`: Removes multiple tasks in scheduler from specified list of task names.
- `reload task <name>`: Reload task in scheduler from specified task.
- `reload tasks <name1, name2, ...>`: Reload multiple tasks in scheduler from specified list of task names.
- `reload all`: Reload all tasks loaded in the Scheduler.

## Changelog v1.1
- Task `Name` attribute is now limited to 32 characters in length.
- Updated Makefile release compile rule.
- Implemented new command `check output <task_name>`.
- Implemented new command `load all`.
- Implemented new command `load tasks <config_name1, config_name2, ...>`.
- Implemented new command `remove tasks <name1, name2, ...>`.
- Implemented new command `reload all`.
- Implemented new command `reload task <task_name>`.
- Implemented new command `reload tasks <name1, name2, ...>`.
- Implemented new command `dump output <task_name>`.
- Implemented new command `dump outputs <name1, name2, ...>`.
- Implemented new command `dump events`.
- Tasks with `Frequency` of `Hourly` now require the `Datetime` attribute of the following formats `HH:MM:SS` or `YYYY-MM-DD HH:MM:SS`.
- Handle invalid configuration files when attempting to load/reload.
- Optimizated and refactored code. 