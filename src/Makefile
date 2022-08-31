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

testing: 
		g++ -g -std=c++17 		\
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
		Testing.cpp -o scheduler_testing 	\
		-lstdc++fs

clean:
	rm scheduler scheduler_testing test Test