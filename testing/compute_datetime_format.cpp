#include <assert.h>
#include <iostream>

#include "../src/Task.hpp"
#include "../src/Scheduler.hpp"

lts::Scheduler* lts::Scheduler::scheduler_ptr = nullptr;

int test1(){
    // TEST 1: testing compute_datetime_format() function -> PASS
    // Datetime format HH:MM:SS
    
    lts::DatetimeFormat ret;
    std::vector<std::string> datetime = {
        "12:00:00",
        "1A:00:00",
        "12:A0:00",
        "12:0A:00",
        "12:00:A0",
        "12:00:0A",
        "1111111:00:00",
        "12:1111111:00",
        "12:00:1111111",
        "1111111:1111111:1111111",
    };

    for(size_t i = 0; i < datetime.size(); i++){
        ret = lts::compute_datetime_format(datetime[i]);
        assert(ret == lts::DatetimeFormat::HHMMSS);
    }

    std::cout << ">> compute_datetime_format: 1 done" << std::endl;
    return 0;
}


int test2(){
    // TEST 2: testing compute_datetime_format() function -> PASS
    // Datetime format abbreviated weekday + HH:MM:SS
    
    lts::DatetimeFormat ret;
    std::vector<std::string> datetime = {
        "Sun 20:00:00",
        "Mon 20:00:00",
        "Tue 20:00:00",
        "Wed 20:00:00",
        "Thu 20:00:00",
        "Fri 20:00:00",
        "Sat 20:00:00",
        "Mon 1A:00:00",
        "Mon 12:A0:00",
        "Mon 12:0A:00",
        "Mon 12:00:A0",
        "Mon 12:00:0A",
        "Mon 1111111:00:00",
        "Mon 12:1111111:00",
        "Mon 12:00:1111111",
        "Mon 1111111:1111111:1111111",
    };

    for(size_t i = 0; i < datetime.size(); i++){
        ret = lts::compute_datetime_format(datetime[i]);
        assert(ret == lts::DatetimeFormat::WDAY_HHMMSS);
    }

    std::cout << ">> compute_datetime_format: 2 done" << std::endl;
    return 0;
}


int test3(){
    // TEST 3: testing compute_datetime_format() function -> PASS
    // Datetime format full weekday + HH:MM:SS
    
    lts::DatetimeFormat ret;
    std::vector<std::string> datetime = {
        "Sunday 20:00:00",
        "Monday 20:00:00",
        "Tuesday 20:00:00",
        "Wednesday 20:00:00",
        "Thursday 20:00:00",
        "Friday 20:00:00",
        "Saturday 20:00:00",
        "Monday 1A:00:00",
        "Monday 12:A0:00",
        "Monday 12:0A:00",
        "Monday 12:00:A0",
        "Monday 12:00:0A",
        "Monday 1111111:00:00",
        "Monday 12:1111111:00",
        "Monday 12:00:1111111",
        "Monday 1111111:1111111:1111111",
        "Aaaaaaaaaaaaaaaa 20:00:00",
    };

    for(size_t i = 0; i < datetime.size(); i++){
        ret = lts::compute_datetime_format(datetime[i]);
        assert(ret == lts::DatetimeFormat::WDAY_HHMMSS);
    }

    std::cout << ">> compute_datetime_format: 3 done" << std::endl;
    return 0;
}


int test4(){
    // TEST 4: testing compute_datetime_format() function -> PASS
    // Datetime format YYYY-MM-DD
    
    lts::DatetimeFormat ret;
    std::vector<std::string> datetime = {
        "2022-02-22",
        "2A22-02-22",
        "20A2-02-22",
        "202A-02-22",
        "2022-A2-22",
        "2022-0A-22",
        "2022-02-A2",
        "2022-02-2A",
        "1111111111-02-22",
        "2022-111111111-22",
        "2022-02-111111111",
    };

    for(size_t i = 0; i < datetime.size(); i++){
        ret = lts::compute_datetime_format(datetime[i]);
        assert(ret == lts::DatetimeFormat::YYYYMMDD);
    }

    std::cout << ">> compute_datetime_format: 4 done" << std::endl;
    return 0;
}


int test5(){
    // TEST 5: testing compute_datetime_format() function -> PASS
    // Datetime format YYYY-MM-DD HH:MM:SS
    
    lts::DatetimeFormat ret;
    std::vector<std::string> datetime = {
        "2022-02-22 13:00:00",
        "2A22-02-22 13:00:00",
        "20A2-02-22 13:00:00",
        "202A-02-22 13:00:00",
        "2022-A2-22 13:00:00",
        "2022-0A-22 13:00:00",
        "2022-02-A2 13:00:00",
        "2022-02-2A 13:00:00",
        "1111111111-02-22 13:00:00",
        "2022-111111111-22 13:00:00",
        "2022-02-111111111 13:00:00",
        "2022-02-22 12:00:00",
        "2022-02-22 1A:00:00",
        "2022-02-22 12:A0:00",
        "2022-02-22 12:0A:00",
        "2022-02-22 12:00:A0",
        "2022-02-22 12:00:0A",
        "2022-02-22 1111111:00:00",
        "2022-02-22 12:1111111:00",
        "2022-02-22 12:00:1111111",
        "2022-02-22 1111111:1111111:1111111",
    };

    for(size_t i = 0; i < datetime.size(); i++){
        ret = lts::compute_datetime_format(datetime[i]);
        assert(ret == lts::DatetimeFormat::YYYYMMDD_HHMMSS);
    }
    
    std::cout << ">> compute_datetime_format: 5 done" << std::endl;
    return 0;
}


int test6(){
    // TEST 6: testing compute_datetime_format() function -> FAIL
    // Datetime format YYYY-MM-DD HH:MM:SS
    
    lts::DatetimeFormat ret;
    std::vector<std::string> datetime = {
        "anything",
        "A2:00:00",
        "AA:AA:AA",
        "A022-02-22",
        "AAAA-AA-AA",
    };

    for(size_t i = 0; i < datetime.size(); i++){
        ret = lts::compute_datetime_format(datetime[i]);
        assert(ret == lts::DatetimeFormat::INVALID_DATE_FORMAT);
    }

    std::cout << ">> compute_datetime_format: 6 done" << std::endl;
    return 0;
}


int main(){
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
}