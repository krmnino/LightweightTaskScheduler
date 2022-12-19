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
		validate_wday					\
		validate_wday_hms				\
		validate_mmdd					\
		validate_mmdd_hms				\
		validate_yyyymmdd				\
		validate_yyyymmdd_hms			\
		init_today						\
		init_year						\
		today_add_hms					\
		today_add_dhms					\
		today_add_wday_hms				\
		today_add_mmdd

Task_constructor:
	g++ -g -std=c++17 -pthread $(SRC_FILES) Task_constructor.cpp -o Task_constructor -lstdc++fs

Task_methods:
	g++ -g -std=c++17 -pthread $(SRC_FILES) Task_methods.cpp -o Task_methods -lstdc++fs

validate_hms:
	g++ -g -std=c++17 -pthread $(SRC_FILES) validate_hms.cpp -o validate_hms -lstdc++fs

validate_wday:
	g++ -g -std=c++17 -pthread $(SRC_FILES) validate_wday.cpp -o validate_wday -lstdc++fs

validate_wday_hms:
	g++ -g -std=c++17 -pthread $(SRC_FILES) validate_wday_hms.cpp -o validate_wday_hms -lstdc++fs

validate_mmdd:
	g++ -g -std=c++17 -pthread $(SRC_FILES) validate_mmdd.cpp -o validate_mmdd -lstdc++fs

validate_mmdd_hms:
	g++ -g -std=c++17 -pthread $(SRC_FILES) validate_mmdd_hms.cpp -o validate_mmdd_hms -lstdc++fs

validate_yyyymmdd:
	g++ -g -std=c++17 -pthread $(SRC_FILES) validate_yyyymmdd.cpp -o validate_yyyymmdd -lstdc++fs

validate_yyyymmdd_hms:
	g++ -g -std=c++17 -pthread $(SRC_FILES) validate_yyyymmdd_hms.cpp -o validate_yyyymmdd_hms -lstdc++fs

init_today:
	g++ -g -std=c++17 -pthread $(SRC_FILES) init_today.cpp -o init_today -lstdc++fs

init_year:
	g++ -g -std=c++17 -pthread $(SRC_FILES) init_year.cpp -o init_year -lstdc++fs

today_add_hms:
	g++ -g -std=c++17 -pthread $(SRC_FILES) today_add_hms.cpp -o today_add_hms -lstdc++fs

today_add_dhms:
	g++ -g -std=c++17 -pthread $(SRC_FILES) today_add_dhms.cpp -o today_add_dhms -lstdc++fs

today_add_wday_hms:
	g++ -g -std=c++17 -pthread $(SRC_FILES) today_add_wday_hms.cpp -o today_add_wday_hms -lstdc++fs

today_add_mmdd:
	g++ -g -std=c++17 -pthread $(SRC_FILES) today_add_mmdd.cpp -o today_add_mmdd -lstdc++fs

clean:
	rm *.o 						\
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
	today_add_mmdd