all:
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
		Constants.hpp			\
		CommandLine.hpp			\
		CommandLine.cpp			\
		EventReporter.hpp		\
		EventReporter.cpp		\
		Scheduler.hpp			\
		Scheduler.cpp			\
		Task.hpp				\
		Task.cpp				\
		Main.cpp -o scheduler 	\
		-lstdc++fs

clean:
	rm *.o scheduler