all: 	Task_constructor

Task_constructor:
	g++ -g -std=c++17 			\
	-pthread					\
	../src/Variant.hpp			\
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
	Task_constructor.cpp -o 	\
	Task_constructor 			\
	-lstdc++fs

clean:
	rm *.o \
	Task_constructor