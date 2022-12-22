SRC_FILES = ../src/Variant.hpp			\
			../src/Variant.cpp			\
			../src/Value.hpp			\
			../src/Value.cpp			\
			../src/CLErrorHandler.hpp 	\
			../src/CLErrorHandler.cpp 	\
			../src/ConfigLoader.hpp 	\
			../src/ConfigLoader.cpp 	\
			../src/Scheduler.hpp		\
			../src/Scheduler.cpp		\
			../src/Task.hpp				\
			../src/Task.cpp

OBJ_FILES = Variant.o					\
			Value.o						\
			CLErrorHandler.o 			\
			ConfigLoader.o	 			\
			Scheduler.o					\
			Task.o

###################################################################################################

all: task_scheduler.o					\
	Task_constructor					\
	Task_methods						\
	validate_hms						\
	validate_wday						\
	validate_wday_hms					\
	validate_mmdd						\
	validate_mmdd_hms					\
	validate_yyyymmdd					\
	validate_yyyymmdd_hms				\
	init_today							\
	init_year							\
	today_add_hms						\
	today_add_dhms						\
	today_add_wday_hms					\
	today_add_mmdd						\
	today_add_mmdd_hms					\
	today_add_yyyymmdd

task_scheduler.o: 
	g++ -g -c -std=c++17 -pthread $(SRC_FILES)

Task_constructor: task_scheduler.o 
	g++ -g -c -std=c++17 Task_constructor.cpp
	g++ -g -o Task_constructor Task_constructor.o $(OBJ_FILES) -pthread -lstdc++fs

Task_methods: task_scheduler.o 
	g++ -g -c -std=c++17 Task_methods.cpp
	g++ -g -o Task_methods Task_methods.o $(OBJ_FILES) -pthread -lstdc++fs

validate_hms: task_scheduler.o 
	g++ -g -c -std=c++17 validate_hms.cpp
	g++ -g -o validate_hms validate_hms.o $(OBJ_FILES) -pthread -lstdc++fs

validate_wday: task_scheduler.o 
	g++ -g -c -std=c++17 validate_wday.cpp
	g++ -g -o validate_wday validate_wday.o $(OBJ_FILES) -pthread -lstdc++fs

validate_wday_hms: task_scheduler.o 
	g++ -g -c -std=c++17 validate_wday_hms.cpp
	g++ -g -o validate_wday_hms validate_wday_hms.o $(OBJ_FILES) -pthread -lstdc++fs

validate_mmdd: task_scheduler.o 
	g++ -g -c -std=c++17 validate_mmdd.cpp
	g++ -g -o validate_mmdd validate_mmdd.o $(OBJ_FILES) -pthread -lstdc++fs

validate_mmdd_hms: task_scheduler.o 
	g++ -g -c -std=c++17 validate_mmdd_hms.cpp
	g++ -g -o validate_mmdd_hms validate_mmdd_hms.o $(OBJ_FILES) -pthread -lstdc++fs

validate_yyyymmdd: task_scheduler.o 
	g++ -g -c -std=c++17 validate_yyyymmdd.cpp
	g++ -g -o validate_yyyymmdd validate_yyyymmdd.o $(OBJ_FILES) -pthread -lstdc++fs

validate_yyyymmdd_hms: task_scheduler.o 
	g++ -g -c -std=c++17 validate_yyyymmdd_hms.cpp
	g++ -g -o validate_yyyymmdd_hms validate_yyyymmdd_hms.o $(OBJ_FILES) -pthread -lstdc++fs

init_today: task_scheduler.o 
	g++ -g -c -std=c++17 init_today.cpp
	g++ -g -o init_today init_today.o $(OBJ_FILES) -pthread -lstdc++fs

init_year: task_scheduler.o 
	g++ -g -c -std=c++17 init_year.cpp
	g++ -g -o init_year init_year.o $(OBJ_FILES) -pthread -lstdc++fs

today_add_hms: task_scheduler.o 
	g++ -g -c -std=c++17 today_add_hms.cpp
	g++ -g -o today_add_hms today_add_hms.o $(OBJ_FILES) -pthread -lstdc++fs

today_add_dhms: task_scheduler.o 
	g++ -g -c -std=c++17 today_add_dhms.cpp
	g++ -g -o today_add_dhms today_add_dhms.o $(OBJ_FILES) -pthread -lstdc++fs

today_add_wday_hms: task_scheduler.o 
	g++ -g -c -std=c++17 today_add_wday_hms.cpp
	g++ -g -o today_add_wday_hms today_add_wday_hms.o $(OBJ_FILES) -pthread -lstdc++fs

today_add_mmdd: task_scheduler.o 
	g++ -g -c -std=c++17 today_add_mmdd.cpp
	g++ -g -o today_add_mmdd today_add_mmdd.o $(OBJ_FILES) -pthread -lstdc++fs

today_add_mmdd_hms: task_scheduler.o 
	g++ -g -c -std=c++17 today_add_mmdd_hms.cpp
	g++ -g -o today_add_mmdd_hms today_add_mmdd_hms.o $(OBJ_FILES) -pthread -lstdc++fs

today_add_yyyymmdd: task_scheduler.o 
	g++ -g -c -std=c++17 today_add_yyyymmdd.cpp
	g++ -g -o today_add_yyyymmdd today_add_yyyymmdd.o $(OBJ_FILES) -pthread -lstdc++fs

###################################################################################################

clean:
	rm *.o 						\
	rm *.gch					\
	rm ../src/*.gch				\
	Task_constructor			\
	Task_methods				\
	validate_hms				\
	validate_wday				\
	validate_wday_hms			\
	validate_mmdd				\
	validate_mmdd_hms			\
	validate_yyyymmdd			\
	validate_yyyymmdd_hms		\
	init_today					\
	init_year					\
	today_add_hms				\
	today_add_dhms				\
	today_add_wday_hms			\
	today_add_mmdd				\
	today_add_mmdd_hms			\
	today_add_yyyymmdd