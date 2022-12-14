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
			../src/Task.cpp				\

all: 	Task_constructor				\
		Task_methods					\
		validate_hms					\
		validate_wday					

Task_constructor:
	g++ -g -std=c++17 			\
	-pthread					\
	$(SRC_FILES)				\
	Task_constructor.cpp -o 	\
	Task_constructor 			\
	-lstdc++fs

Task_methods:
	g++ -g -std=c++17 			\
	-pthread					\
	$(SRC_FILES)				\
	Task_methods.cpp -o 		\
	Task_methods 				\
	-lstdc++fs

validate_hms:
	g++ -g -std=c++17 -pthread $(SRC_FILES) validate_hms.cpp -o validate_hms -lstdc++fs

validate_wday:
	g++ -g -std=c++17 			\
	-pthread					\
	$(SRC_FILES)				\
	validate_wday.cpp -o 		\
	validate_wday				\
	-lstdc++fs

clean:
	rm *.o 						\
	Task_constructor			\
	Task_methods				\
	validate_hms				\
	validate_wday				