#include <assert.h>
#include <iostream>

#include "../src/Task.hpp"
#include "../src/Scheduler.hpp"

ts::Scheduler* ts::Scheduler::scheduler_ptr = nullptr;

int test1(){
    // TEST 1: testing get_datetime_format() function -> PASS
    // Datetime format HH:MM:SS
    
    std::string datetime = "12:00:00";
    ts::DatetimeFormat ret = ts::get_datetime_format(datetime);

    assert(ret == ts::DatetimeFormat::HHMMSS);

    std::cout << ">> get_datetime_format: 1 done" << std::endl;
    return 0;
}


int test2(){
    // TEST 2: testing get_datetime_format() function -> PASS
    // Datetime format abbreviated weekday + HH:MM:SS
    
    ts::DatetimeFormat ret;
    std::vector<std::string> datetime = {
        "Sun 20:00:00",
        "Mon 20:00:00",
        "Tue 20:00:00",
        "Wed 20:00:00",
        "Thu 20:00:00",
        "Fri 20:00:00",
        "Sat 20:00:00"
    };

    for(int i = 0; i < datetime.size(); i++){
        ret = ts::get_datetime_format(datetime[i]);
        assert(ret == ts::DatetimeFormat::WDAY_HHMMSS);
    }

    std::cout << ">> get_datetime_format: 2 done" << std::endl;
    return 0;
}


int test3(){
    // TEST 3: testing get_datetime_format() function -> PASS
    // Datetime format full weekday + HH:MM:SS
    
    ts::DatetimeFormat ret;
    std::string datetime;

    datetime = "Sunday 20:00:00";
    ret = ts::get_datetime_format(datetime);
    assert(ret == ts::DatetimeFormat::WDAY6_HHMMSS);

    datetime = "Monday 20:00:00";
    ret = ts::get_datetime_format(datetime);
    assert(ret == ts::DatetimeFormat::WDAY6_HHMMSS);

    datetime = "Tuesday 20:00:00";
    ret = ts::get_datetime_format(datetime);
    assert(ret == ts::DatetimeFormat::WDAY7_HHMMSS);

    datetime = "Wednesday 20:00:00";
    ret = ts::get_datetime_format(datetime);
    assert(ret == ts::DatetimeFormat::WDAY9_HHMMSS);

    datetime = "Thursday 20:00:00";
    ret = ts::get_datetime_format(datetime);
    assert(ret == ts::DatetimeFormat::WDAY8_HHMMSS);

    datetime = "Friday 20:00:00";
    ret = ts::get_datetime_format(datetime);
    assert(ret == ts::DatetimeFormat::WDAY6_HHMMSS);

    datetime = "Saturday 20:00:00";
    ret = ts::get_datetime_format(datetime);
    assert(ret == ts::DatetimeFormat::WDAY8_HHMMSS);

    std::cout << ">> get_datetime_format: 3 done" << std::endl;
    return 0;
}


int test4(){
    // TEST 4: testing get_datetime_format() function -> PASS
    // Datetime format YYYY-MM-DD
    
    std::string datetime = "2022-02-22";
    ts::DatetimeFormat ret = ts::get_datetime_format(datetime);

    assert(ret == ts::DatetimeFormat::YYYYMMDD);

    std::cout << ">> get_datetime_format: 4 done" << std::endl;
    return 0;
}


int test5(){
    // TEST 5: testing get_datetime_format() function -> PASS
    // Datetime format YYYY-MM-DD HH:MM:SS
    
    std::string datetime = "2022-02-22 13:00:00";
    ts::DatetimeFormat ret = ts::get_datetime_format(datetime);

    assert(ret == ts::DatetimeFormat::YYYYMMDD_HHMMSS);

    std::cout << ">> get_datetime_format: 5 done" << std::endl;
    return 0;
}


int test6(){
    // TEST 6: testing get_datetime_format() function -> FAIL
    // Datetime format YYYY-MM-DD HH:MM:SS
    
    std::string datetime = "anything";
    ts::DatetimeFormat ret = ts::get_datetime_format(datetime);

    assert(ret == ts::DatetimeFormat::INVALID_DATE_FORMAT);

    std::cout << ">> get_datetime_format: 6 done" << std::endl;
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