SRC_FILES = ../src/Variant.hpp			\
			../src/Variant.cpp			\
			../src/Value.hpp			\
			../src/Value.cpp			\
			../src/CLErrorHandler.hpp 	\
			../src/CLErrorHandler.cpp 	\
			../src/ConfigLoader.hpp 	\
			../src/ConfigLoader.cpp 	\
			../src/CommandLine.hpp 		\
			../src/CommandLine.cpp 		\
			../src/EventReporter.hpp	\
			../src/EventReporter.cpp	\
			../src/Scheduler.hpp		\
			../src/Scheduler.cpp		\
			../src/Task.hpp				\
			../src/Task.cpp

OBJ_FILES = Variant.o					\
			Value.o						\
			CLErrorHandler.o 			\
			ConfigLoader.o	 			\
			CommandLine.o	 			\
			EventReporter.o				\
			Scheduler.o					\
			Task.o

SRC_TESTCASES =	Task_constructor						\
				Task_methods							\
				validate_hms							\
				validate_wday							\
				validate_wday_hms						\
				validate_yyyymmdd						\
				validate_yyyymmdd_hms					\
				init_today								\
				init_year								\
				today_add_hms							\
				today_add_dhms							\
				today_add_wday_hms						\
				today_add_yyyymmdd						\
				today_add_yyyymmdd_hms					\
				compute_datetime_format					\
				validate_task_parms						\
				validate_task_parms_Once				\
				validate_task_parms_Hourly				\
				validate_task_parms_Daily				\
				validate_task_parms_Weekly				\
				validate_task_parms_Monthly				\
				validate_task_parms_Yearly				\
				Task_update_execution_datetime_Once		\
				Task_update_execution_datetime_Hourly	\
				Task_update_execution_datetime_Daily	\
				Task_update_execution_datetime_Weekly	\
				Task_update_execution_datetime_Monthly	\
				Task_update_execution_datetime_Yearly	\
				Task_setting_exec_datetime_Once			\
				Task_setting_exec_datetime_Hourly		\
				Task_setting_exec_datetime_Daily		\
				Task_setting_exec_datetime_Weekly		\
				Task_setting_exec_datetime_Monthly		\
				Task_setting_exec_datetime_Yearly		\
				Scheduler_get_instance					\
				Scheduler_methods						\
				Scheduler_Task_run_task					\
				Scheduler_load_tasks_from_dir			\
				Scheduler_load_task						\
				EventReporter_get_instance				\
				EventReporter_methods					\
				CommandLine_get_instance				\
				CommandLine_methods						\
				CommandLine_verb_check					\
				CommandLine_verb_remove					\
				CommandLine_verb_load

###################################################################################################

all: task_scheduler.o $(SRC_TESTCASES)

task_scheduler.o: 
	g++ -g -c -std=c++17 -pthread -D SILENT $(SRC_FILES)

Task_constructor: task_scheduler.o 
	g++ -g -Wall -c -std=c++17 Task_constructor.cpp
	g++ -g -Wall -o Task_constructor Task_constructor.o $(OBJ_FILES) -pthread -lstdc++fs

Task_methods: task_scheduler.o 
	g++ -g -Wall -c -std=c++17 Task_methods.cpp
	g++ -g -Wall -o Task_methods Task_methods.o $(OBJ_FILES) -pthread -lstdc++fs

validate_hms: task_scheduler.o 
	g++ -g -Wall -c -std=c++17 validate_hms.cpp
	g++ -g -Wall -o validate_hms validate_hms.o $(OBJ_FILES) -pthread -lstdc++fs

validate_wday: task_scheduler.o 
	g++ -g -Wall -c -std=c++17 validate_wday.cpp
	g++ -g -Wall -o validate_wday validate_wday.o $(OBJ_FILES) -pthread -lstdc++fs

validate_wday_hms: task_scheduler.o 
	g++ -g -Wall -c -std=c++17 validate_wday_hms.cpp
	g++ -g -Wall -o validate_wday_hms validate_wday_hms.o $(OBJ_FILES) -pthread -lstdc++fs

validate_yyyymmdd: task_scheduler.o 
	g++ -g -Wall -c -std=c++17 validate_yyyymmdd.cpp
	g++ -g -Wall -o validate_yyyymmdd validate_yyyymmdd.o $(OBJ_FILES) -pthread -lstdc++fs

validate_yyyymmdd_hms: task_scheduler.o 
	g++ -g -Wall -c -std=c++17 validate_yyyymmdd_hms.cpp
	g++ -g -Wall -o validate_yyyymmdd_hms validate_yyyymmdd_hms.o $(OBJ_FILES) -pthread -lstdc++fs

init_today: task_scheduler.o 
	g++ -g -Wall -c -std=c++17 init_today.cpp
	g++ -g -Wall -o init_today init_today.o $(OBJ_FILES) -pthread -lstdc++fs

init_year: task_scheduler.o 
	g++ -g -Wall -c -std=c++17 init_year.cpp
	g++ -g -Wall -o init_year init_year.o $(OBJ_FILES) -pthread -lstdc++fs

today_add_hms: task_scheduler.o 
	g++ -g -Wall -c -std=c++17 today_add_hms.cpp
	g++ -g -Wall -o today_add_hms today_add_hms.o $(OBJ_FILES) -pthread -lstdc++fs

today_add_dhms: task_scheduler.o 
	g++ -g -Wall -c -std=c++17 today_add_dhms.cpp
	g++ -g -Wall -o today_add_dhms today_add_dhms.o $(OBJ_FILES) -pthread -lstdc++fs

today_add_wday_hms: task_scheduler.o 
	g++ -g -Wall -c -std=c++17 today_add_wday_hms.cpp
	g++ -g -Wall -o today_add_wday_hms today_add_wday_hms.o $(OBJ_FILES) -pthread -lstdc++fs

today_add_yyyymmdd: task_scheduler.o 
	g++ -g -Wall -c -std=c++17 today_add_yyyymmdd.cpp
	g++ -g -Wall -o today_add_yyyymmdd today_add_yyyymmdd.o $(OBJ_FILES) -pthread -lstdc++fs

today_add_yyyymmdd_hms: task_scheduler.o 
	g++ -g -Wall -c -std=c++17 today_add_yyyymmdd_hms.cpp
	g++ -g -Wall -o today_add_yyyymmdd_hms today_add_yyyymmdd_hms.o $(OBJ_FILES) -pthread -lstdc++fs

compute_datetime_format: task_scheduler.o 
	g++ -g -Wall -c -std=c++17 compute_datetime_format.cpp
	g++ -g -Wall -o compute_datetime_format compute_datetime_format.o $(OBJ_FILES) -pthread -lstdc++fs

validate_task_parms: task_scheduler.o 
	g++ -g -Wall -c -std=c++17 validate_task_parms.cpp
	g++ -g -Wall -o validate_task_parms validate_task_parms.o $(OBJ_FILES) -pthread -lstdc++fs

validate_task_parms_Once: task_scheduler.o 
	g++ -g -Wall -c -std=c++17 validate_task_parms_Once.cpp
	g++ -g -Wall -o validate_task_parms_Once validate_task_parms_Once.o $(OBJ_FILES) -pthread -lstdc++fs

validate_task_parms_Hourly: task_scheduler.o 
	g++ -g -Wall -c -std=c++17 validate_task_parms_Hourly.cpp
	g++ -g -Wall -o validate_task_parms_Hourly validate_task_parms_Hourly.o $(OBJ_FILES) -pthread -lstdc++fs

validate_task_parms_Daily: task_scheduler.o 
	g++ -g -Wall -c -std=c++17 validate_task_parms_Daily.cpp
	g++ -g -Wall -o validate_task_parms_Daily validate_task_parms_Daily.o $(OBJ_FILES) -pthread -lstdc++fs

validate_task_parms_Weekly: task_scheduler.o 
	g++ -g -Wall -c -std=c++17 validate_task_parms_Weekly.cpp
	g++ -g -Wall -o validate_task_parms_Weekly validate_task_parms_Weekly.o $(OBJ_FILES) -pthread -lstdc++fs

validate_task_parms_Monthly: task_scheduler.o 
	g++ -g -Wall -c -std=c++17 validate_task_parms_Monthly.cpp
	g++ -g -Wall -o validate_task_parms_Monthly validate_task_parms_Monthly.o $(OBJ_FILES) -pthread -lstdc++fs

validate_task_parms_Yearly: task_scheduler.o 
	g++ -g -Wall -c -std=c++17 validate_task_parms_Yearly.cpp
	g++ -g -Wall -o validate_task_parms_Yearly validate_task_parms_Yearly.o $(OBJ_FILES) -pthread -lstdc++fs

Task_update_execution_datetime_Once: task_scheduler.o 
	g++ -g -Wall -c -std=c++17 Task_update_execution_datetime_Once.cpp
	g++ -g -Wall -o Task_update_execution_datetime_Once Task_update_execution_datetime_Once.o $(OBJ_FILES) -pthread -lstdc++fs

Task_update_execution_datetime_Hourly: task_scheduler.o 
	g++ -g -Wall -c -std=c++17 Task_update_execution_datetime_Hourly.cpp
	g++ -g -Wall -o Task_update_execution_datetime_Hourly Task_update_execution_datetime_Hourly.o $(OBJ_FILES) -pthread -lstdc++fs

Task_update_execution_datetime_Daily: task_scheduler.o 
	g++ -g -Wall -c -std=c++17 Task_update_execution_datetime_Daily.cpp
	g++ -g -Wall -o Task_update_execution_datetime_Daily Task_update_execution_datetime_Daily.o $(OBJ_FILES) -pthread -lstdc++fs

Task_update_execution_datetime_Weekly: task_scheduler.o 
	g++ -g -Wall -c -std=c++17 Task_update_execution_datetime_Weekly.cpp
	g++ -g -Wall -o Task_update_execution_datetime_Weekly Task_update_execution_datetime_Weekly.o $(OBJ_FILES) -pthread -lstdc++fs

Task_update_execution_datetime_Monthly: task_scheduler.o 
	g++ -g -Wall -c -std=c++17 Task_update_execution_datetime_Monthly.cpp
	g++ -g -Wall -o Task_update_execution_datetime_Monthly Task_update_execution_datetime_Monthly.o $(OBJ_FILES) -pthread -lstdc++fs

Task_update_execution_datetime_Yearly: task_scheduler.o 
	g++ -g -Wall -c -std=c++17 Task_update_execution_datetime_Yearly.cpp
	g++ -g -Wall -o Task_update_execution_datetime_Yearly Task_update_execution_datetime_Yearly.o $(OBJ_FILES) -pthread -lstdc++fs

Task_setting_exec_datetime_Once: task_scheduler.o 
	g++ -g -Wall -c -std=c++17 Task_setting_exec_datetime_Once.cpp
	g++ -g -Wall -o Task_setting_exec_datetime_Once Task_setting_exec_datetime_Once.o $(OBJ_FILES) -pthread -lstdc++fs

Task_setting_exec_datetime_Hourly: task_scheduler.o 
	g++ -g -Wall -c -std=c++17 Task_setting_exec_datetime_Hourly.cpp
	g++ -g -Wall -o Task_setting_exec_datetime_Hourly Task_setting_exec_datetime_Hourly.o $(OBJ_FILES) -pthread -lstdc++fs

Task_setting_exec_datetime_Daily: task_scheduler.o 
	g++ -g -Wall -c -std=c++17 Task_setting_exec_datetime_Daily.cpp
	g++ -g -Wall -o Task_setting_exec_datetime_Daily Task_setting_exec_datetime_Daily.o $(OBJ_FILES) -pthread -lstdc++fs

Task_setting_exec_datetime_Weekly: task_scheduler.o 
	g++ -g -Wall -c -std=c++17 Task_setting_exec_datetime_Weekly.cpp
	g++ -g -Wall -o Task_setting_exec_datetime_Weekly Task_setting_exec_datetime_Weekly.o $(OBJ_FILES) -pthread -lstdc++fs

Task_setting_exec_datetime_Monthly: task_scheduler.o 
	g++ -g -Wall -c -std=c++17 Task_setting_exec_datetime_Monthly.cpp
	g++ -g -Wall -o Task_setting_exec_datetime_Monthly Task_setting_exec_datetime_Monthly.o $(OBJ_FILES) -pthread -lstdc++fs

Task_setting_exec_datetime_Yearly: task_scheduler.o 
	g++ -g -Wall -c -std=c++17 Task_setting_exec_datetime_Yearly.cpp
	g++ -g -Wall -o Task_setting_exec_datetime_Yearly Task_setting_exec_datetime_Yearly.o $(OBJ_FILES) -pthread -lstdc++fs

Scheduler_get_instance: task_scheduler.o 
	g++ -g -Wall -c -std=c++17 Scheduler_get_instance.cpp
	g++ -g -Wall -o Scheduler_get_instance Scheduler_get_instance.o $(OBJ_FILES) -pthread -lstdc++fs

Scheduler_methods: task_scheduler.o 
	g++ -g -Wall -c -std=c++17 Scheduler_methods.cpp
	g++ -g -Wall -o Scheduler_methods Scheduler_methods.o $(OBJ_FILES) -pthread -lstdc++fs

Scheduler_Task_run_task: task_scheduler.o 
	g++ -g -Wall -c -std=c++17 Scheduler_Task_run_task.cpp
	g++ -g -Wall -o Scheduler_Task_run_task Scheduler_Task_run_task.o $(OBJ_FILES) -pthread -lstdc++fs

Scheduler_load_tasks_from_dir: task_scheduler.o 
	g++ -g -Wall -c -std=c++17 Scheduler_load_tasks_from_dir.cpp
	g++ -g -Wall -o Scheduler_load_tasks_from_dir Scheduler_load_tasks_from_dir.o $(OBJ_FILES) -pthread -lstdc++fs

Scheduler_load_task: task_scheduler.o 
	g++ -g -Wall -c -std=c++17 Scheduler_load_task.cpp
	g++ -g -Wall -o Scheduler_load_task Scheduler_load_task.o $(OBJ_FILES) -pthread -lstdc++fs

EventReporter_get_instance: task_scheduler.o 
	g++ -g -Wall -c -std=c++17 EventReporter_get_instance.cpp
	g++ -g -Wall -o EventReporter_get_instance EventReporter_get_instance.o $(OBJ_FILES) -pthread -lstdc++fs

EventReporter_methods: task_scheduler.o 
	g++ -g -Wall -c -std=c++17 EventReporter_methods.cpp
	g++ -g -Wall -o EventReporter_methods EventReporter_methods.o $(OBJ_FILES) -pthread -lstdc++fs

CommandLine_get_instance: task_scheduler.o 
	g++ -g -Wall -c -std=c++17 CommandLine_get_instance.cpp
	g++ -g -Wall -o CommandLine_get_instance CommandLine_get_instance.o $(OBJ_FILES) -pthread -lstdc++fs

CommandLine_methods: task_scheduler.o 
	g++ -g -Wall -c -std=c++17 CommandLine_methods.cpp
	g++ -g -Wall -o CommandLine_methods CommandLine_methods.o $(OBJ_FILES) -pthread -lstdc++fs

CommandLine_verb_check: task_scheduler.o 
	g++ -g -Wall -c -std=c++17 CommandLine_verb_check.cpp
	g++ -g -Wall -o CommandLine_verb_check CommandLine_verb_check.o $(OBJ_FILES) -pthread -lstdc++fs

CommandLine_verb_remove: task_scheduler.o 
	g++ -g -Wall -c -std=c++17 CommandLine_verb_remove.cpp
	g++ -g -Wall -o CommandLine_verb_remove CommandLine_verb_remove.o $(OBJ_FILES) -pthread -lstdc++fs

CommandLine_verb_load: task_scheduler.o 
	g++ -g -Wall -c -std=c++17 CommandLine_verb_load.cpp
	g++ -g -Wall -o CommandLine_verb_load CommandLine_verb_load.o $(OBJ_FILES) -pthread -lstdc++fs

###################################################################################################

clean:
	rm *.o 									\
	*.gch									\
	../src/*.gch							\
	tasks/TestTask.cl						\
	$(SRC_TESTCASES)