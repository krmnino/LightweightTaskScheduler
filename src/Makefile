debug:
	g++ -g -std=c++17 			\
		-pthread				\
		Variant.hpp				\
		Variant.cpp				\
		Value.hpp				\
		Value.cpp				\
		CLErrorHandler.hpp 		\
		CLErrorHandler.cpp 		\
		ConfigLoader.hpp 		\
		ConfigLoader.cpp 		\
		Scheduler.hpp			\
		Scheduler.cpp			\
		Task.hpp				\
		Task.cpp				\
		Main.cpp -o scheduler 	\
		-lstdc++fs

release:
	g++ -O2 -std=c++17 			\
		-pthread				\
		Variant.hpp				\
		Variant.cpp				\
		Value.hpp				\
		Value.cpp				\
		CLErrorHandler.hpp 		\
		CLErrorHandler.cpp 		\
		ConfigLoader.hpp 		\
		ConfigLoader.cpp 		\
		Scheduler.hpp			\
		Scheduler.cpp			\
		Task.hpp				\
		Task.cpp				\
		Main.cpp -o scheduler 	\
		-lstdc++fs

test: 
	g++ -g -pthread Test.cpp -o test

clean:
	rm scheduler test Test