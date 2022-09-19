#include <assert.h>
#include <iostream>

#include "Task.hpp"

int test1(){
    // TEST 1: testing Task constructor Task(std::string, std::string, std::string, std::string)
    // Testing methods 
    // get_name()
    // get_description()
    // get_script_name()
    // get_frequency()

    std::string t_name = "Task Name";
    std::string t_description = "A short description for this task";
    std::string t_script_name = "cat_test.sh";
    std::string t_frequency = "Once";

    ts::Task* t = new ts::Task(t_name, t_description, t_script_name, t_frequency);
    
    assert(t->get_name() == "Task Name");
    assert(t->get_description() == "A short description for this task");
    assert(t->get_script_filename() == "cat_test.sh");
    assert(t->get_frequency() == "Once");

    delete t;

    std::cout << ">> Test 1 done" << std::endl;

    return 0;
}


int test2(){
    // TEST 2: testing Task constructor Task(std::string, std::string, std::string, std::string, std::string)
    // Testing methods 
    // get_name()
    // get_description()
    // get_script_name()
    // get_frequency()
    // get_input_execution_datetime()

    std::string t_name = "Task Name";
    std::string t_description = "A short description for this task";
    std::string t_script_name = "cat_test.sh";
    std::string t_frequency = "Hourly";
    std::string t_input_execution_datetime = "12:00:00";

    ts::Task* t = new ts::Task(t_name, t_description, t_script_name, t_frequency, t_input_execution_datetime);
    
    assert(t->get_name() == "Task Name");
    assert(t->get_description() == "A short description for this task");
    assert(t->get_script_filename() == "cat_test.sh");
    assert(t->get_frequency() == "Hourly");
    assert(t->get_input_execution_datetime() == "12:00:00");

    delete t;

    std::cout << ">> Test 2 done" << std::endl;

    return 0;
}


int test3(){
    // TEST 3: testing methods 
    // get_execution_datetime_fmt()
    // get_creation_datetime_fmt()
    // get_creation_datetime()
    // get_execution_datetime()

    std::string t_name = "Task Name";
    std::string t_description = "A short description for this task";
    std::string t_script_name = "cat_test.sh";
    std::string t_frequency = "Hourly";
    std::string t_input_execution_datetime = "12:00:00";

    ts::Task* t = new ts::Task(t_name, t_description, t_script_name, t_frequency, t_input_execution_datetime);
    
    std::string execution_datetime_fmt = t->get_execution_datetime_fmt();
    std::string creation_datetime_fmt = t->get_creation_datetime_fmt();
    time_t execution_datetime = t->get_creation_datetime(); 
    time_t creation_datetime = t->get_execution_datetime();

    delete t;

    std::cout << ">> Test 3 done" << std::endl;

    return 0;
}


int test4(){
    // TEST 4: testing methods 
    // set_id()
    // get_id()
    // set_status()
    // get_status()

    std::string t_name = "Task Name";
    std::string t_description = "A short description for this task";
    std::string t_script_name = "../scripts/cat_test.sh";
    std::string t_frequency = "Once";

    ts::Task* t = new ts::Task(t_name, t_description, t_script_name, t_frequency);
    
    t->set_id(12345);
    assert(t->get_id() == 12345);

    t->set_status(ts::TaskStatus::QUEUED);
    assert(t->get_status() == ts::TaskStatus::QUEUED);

    delete t;

    std::cout << ">> Test 4 done" << std::endl;

    return 0;
}


int test5(){
    // TEST 5: testing validate_hms() function

    std::string hms;
    ts::DatetimeValidate ret;
    
    hms = "12:00:00";
    ret = ts::validate_hms(hms);
    assert(ret == ts::DatetimeValidate::OK);

    hms = "12:00";
    ret = ts::validate_hms(hms);
    assert(ret == ts::DatetimeValidate::BAD_HMS_LENGTH);

    hms = "1a:00:00";
    ret = ts::validate_hms(hms);
    assert(ret == ts::DatetimeValidate::BAD_NUMBER_CHARACTER);

    hms = "12:a0:00";
    ret = ts::validate_hms(hms);
    assert(ret == ts::DatetimeValidate::BAD_NUMBER_CHARACTER);

    hms = "12:00:a0";
    ret = ts::validate_hms(hms);
    assert(ret == ts::DatetimeValidate::BAD_NUMBER_CHARACTER);

    hms = "30:00:00";
    ret = ts::validate_hms(hms);
    assert(ret == ts::DatetimeValidate::HOURS_OUT_OF_RANGE);

    hms = "12:90:00";
    ret = ts::validate_hms(hms);
    assert(ret == ts::DatetimeValidate::MINUTES_OUT_OF_RANGE);    

    hms = "12:00:88";
    ret = ts::validate_hms(hms);
    assert(ret == ts::DatetimeValidate::SECONDS_OUT_OF_RANGE);

    hms = "12A00:00";
    ret = ts::validate_hms(hms);
    assert(ret == ts::DatetimeValidate::MISSING_COLON);
    
    hms = "12:00A00";
    ret = ts::validate_hms(hms);
    assert(ret == ts::DatetimeValidate::MISSING_COLON);

    std::cout << ">> Test 5 done" << std::endl;

    return 0;
}


int test6(){
    // TEST 6: testing validate_wday() function

    std::string wday;
    ts::DatetimeValidate ret;

    wday = "Monday";
    ret = ts::validate_wday(wday);
    assert(ret == ts::DatetimeValidate::OK);
    
    wday = "Tuesday";
    ret = ts::validate_wday(wday);
    assert(ret == ts::DatetimeValidate::OK);
    
    wday = "Wednesday";
    ret = ts::validate_wday(wday);
    assert(ret == ts::DatetimeValidate::OK);
    
    wday = "Thursday";
    ret = ts::validate_wday(wday);
    assert(ret == ts::DatetimeValidate::OK);

    wday = "Friday";
    ret = ts::validate_wday(wday);
    assert(ret == ts::DatetimeValidate::OK);

    wday = "Mon";
    ret = ts::validate_wday(wday);
    assert(ret == ts::DatetimeValidate::OK);
    
    wday = "Tue";
    ret = ts::validate_wday(wday);
    assert(ret == ts::DatetimeValidate::OK);
    
    wday = "Wed";
    ret = ts::validate_wday(wday);
    assert(ret == ts::DatetimeValidate::OK);
    
    wday = "Thu";
    ret = ts::validate_wday(wday);
    assert(ret == ts::DatetimeValidate::OK);

    wday = "Fri";
    ret = ts::validate_wday(wday);
    assert(ret == ts::DatetimeValidate::OK);

    wday = "anything";
    ret = ts::validate_wday(wday);
    assert(ret == ts::DatetimeValidate::BAD_WDAY);

    std::cout << ">> Test 6 done" << std::endl;

    return 0;
}


int test7(){
    // TEST 7: testing validate_wday_hms() function

    std::string wday_hms;
    ts::DatetimeValidate ret;

    wday_hms = "Monday 01:00:00";
    ret = ts::validate_wday_hms(wday_hms);
    assert(ret == ts::DatetimeValidate::OK);

    wday_hms = "Monday01:00:00";
    ret = ts::validate_wday_hms(wday_hms);
    assert(ret == ts::DatetimeValidate::MISSING_SPACE);

    wday_hms = "Anything 01:00:00";
    ret = ts::validate_wday_hms(wday_hms);
    assert(ret == ts::DatetimeValidate::BAD_WDAY);    

    wday_hms = "Friday 35:00:00";
    ret = ts::validate_wday_hms(wday_hms);
    assert(ret == ts::DatetimeValidate::HOURS_OUT_OF_RANGE);

    std::cout << ">> Test 7 done" << std::endl;

    return 0;
}


int test8(){
    // TEST 8: testing validate_mmdd() function

    std::string mmdd;
    ts::DatetimeValidate ret;

    mmdd = "01-01";
    ret = ts::validate_mmdd(mmdd);
    assert(ret == ts::DatetimeValidate::OK);

    mmdd = "01-31";
    ret = ts::validate_mmdd(mmdd);
    assert(ret == ts::DatetimeValidate::OK);    

    mmdd = "02-01";
    ret = ts::validate_mmdd(mmdd);
    assert(ret == ts::DatetimeValidate::OK);    

    mmdd = "02-28";
    ret = ts::validate_mmdd(mmdd);
    assert(ret == ts::DatetimeValidate::OK);    

    mmdd = "03-01";
    ret = ts::validate_mmdd(mmdd);
    assert(ret == ts::DatetimeValidate::OK);    

    mmdd = "03-31";
    ret = ts::validate_mmdd(mmdd);
    assert(ret == ts::DatetimeValidate::OK);    

    mmdd = "04-01";
    ret = ts::validate_mmdd(mmdd);
    assert(ret == ts::DatetimeValidate::OK);    

    mmdd = "04-30";
    ret = ts::validate_mmdd(mmdd);
    assert(ret == ts::DatetimeValidate::OK);    

    mmdd = "05-01";
    ret = ts::validate_mmdd(mmdd);
    assert(ret == ts::DatetimeValidate::OK);    

    mmdd = "05-31";
    ret = ts::validate_mmdd(mmdd);
    assert(ret == ts::DatetimeValidate::OK);    

    mmdd = "06-01";
    ret = ts::validate_mmdd(mmdd);
    assert(ret == ts::DatetimeValidate::OK);    

    mmdd = "06-30";
    ret = ts::validate_mmdd(mmdd);
    assert(ret == ts::DatetimeValidate::OK);    

    mmdd = "07-01";
    ret = ts::validate_mmdd(mmdd);
    assert(ret == ts::DatetimeValidate::OK);    

    mmdd = "07-31";
    ret = ts::validate_mmdd(mmdd);
    assert(ret == ts::DatetimeValidate::OK);    

    mmdd = "08-01";
    ret = ts::validate_mmdd(mmdd);
    assert(ret == ts::DatetimeValidate::OK);    

    mmdd = "08-31";
    ret = ts::validate_mmdd(mmdd);
    assert(ret == ts::DatetimeValidate::OK);    

    mmdd = "09-01";
    ret = ts::validate_mmdd(mmdd);
    assert(ret == ts::DatetimeValidate::OK);    

    mmdd = "09-30";
    ret = ts::validate_mmdd(mmdd);
    assert(ret == ts::DatetimeValidate::OK);

    mmdd = "10-01";
    ret = ts::validate_mmdd(mmdd);
    assert(ret == ts::DatetimeValidate::OK);    

    mmdd = "10-31";
    ret = ts::validate_mmdd(mmdd);
    assert(ret == ts::DatetimeValidate::OK); 

    mmdd = "11-01";
    ret = ts::validate_mmdd(mmdd);
    assert(ret == ts::DatetimeValidate::OK);    

    mmdd = "11-30";
    ret = ts::validate_mmdd(mmdd);
    assert(ret == ts::DatetimeValidate::OK); 

    mmdd = "12-01";
    ret = ts::validate_mmdd(mmdd);
    assert(ret == ts::DatetimeValidate::OK);    

    mmdd = "12-31";
    ret = ts::validate_mmdd(mmdd);
    assert(ret == ts::DatetimeValidate::OK); 

    mmdd = "12-31-22";
    ret = ts::validate_mmdd(mmdd);
    assert(ret == ts::DatetimeValidate::BAD_MMDD_LENGTH); 

    mmdd = "a2-31";
    ret = ts::validate_mmdd(mmdd);
    assert(ret == ts::DatetimeValidate::BAD_NUMBER_CHARACTER);

    mmdd = "12-3a";
    ret = ts::validate_mmdd(mmdd);
    assert(ret == ts::DatetimeValidate::BAD_NUMBER_CHARACTER);

    mmdd = "12a30";
    ret = ts::validate_mmdd(mmdd);
    assert(ret == ts::DatetimeValidate::MISSING_DASH);

    mmdd = "25-30";
    ret = ts::validate_mmdd(mmdd);
    assert(ret == ts::DatetimeValidate::MONTH_OUT_OF_RANGE);

    mmdd = "01-40";
    ret = ts::validate_mmdd(mmdd);
    assert(ret == ts::DatetimeValidate::DAY_OUT_OF_RANGE);   

    mmdd = "02-40";
    ret = ts::validate_mmdd(mmdd);
    assert(ret == ts::DatetimeValidate::DAY_OUT_OF_RANGE);   

    mmdd = "03-40";
    ret = ts::validate_mmdd(mmdd);
    assert(ret == ts::DatetimeValidate::DAY_OUT_OF_RANGE);  

    mmdd = "04-40";
    ret = ts::validate_mmdd(mmdd);
    assert(ret == ts::DatetimeValidate::DAY_OUT_OF_RANGE);  

    mmdd = "05-40";
    ret = ts::validate_mmdd(mmdd);
    assert(ret == ts::DatetimeValidate::DAY_OUT_OF_RANGE);  

    mmdd = "06-40";
    ret = ts::validate_mmdd(mmdd);
    assert(ret == ts::DatetimeValidate::DAY_OUT_OF_RANGE);  

    mmdd = "07-40";
    ret = ts::validate_mmdd(mmdd);
    assert(ret == ts::DatetimeValidate::DAY_OUT_OF_RANGE);  

    mmdd = "08-40";
    ret = ts::validate_mmdd(mmdd);
    assert(ret == ts::DatetimeValidate::DAY_OUT_OF_RANGE);  

    mmdd = "09-40";
    ret = ts::validate_mmdd(mmdd);
    assert(ret == ts::DatetimeValidate::DAY_OUT_OF_RANGE);  

    mmdd = "10-40";
    ret = ts::validate_mmdd(mmdd);
    assert(ret == ts::DatetimeValidate::DAY_OUT_OF_RANGE);  

    mmdd = "11-40";
    ret = ts::validate_mmdd(mmdd);
    assert(ret == ts::DatetimeValidate::DAY_OUT_OF_RANGE);  

    mmdd = "12-40";
    ret = ts::validate_mmdd(mmdd);
    assert(ret == ts::DatetimeValidate::DAY_OUT_OF_RANGE);  

    std::cout << ">> Test 8 done" << std::endl;

    return 0;
}


int test9(){
    // TEST 9: testing validate_mmdd_hms() function

    std::string mmdd_hms;
    ts::DatetimeValidate ret;

    mmdd_hms = "10-25 01:00:00";
    ret = ts::validate_mmdd_hms(mmdd_hms);
    assert(ret == ts::DatetimeValidate::OK);

    mmdd_hms = "Monday01:00:00";
    ret = ts::validate_mmdd_hms(mmdd_hms);
    assert(ret == ts::DatetimeValidate::MISSING_SPACE);

    mmdd_hms = "56-25 01:00:00";
    ret = ts::validate_mmdd_hms(mmdd_hms);
    assert(ret == ts::DatetimeValidate::MONTH_OUT_OF_RANGE);    

    mmdd_hms = "10-25 35:00:00";
    ret = ts::validate_mmdd_hms(mmdd_hms);
    assert(ret == ts::DatetimeValidate::HOURS_OUT_OF_RANGE);

    std::cout << ">> Test 9 done" << std::endl;

    return 0;
}


int test10(){
    // TEST 10: testing today_add_yyyymmdd() function
    
    std::string yyyymmdd;
    ts::DatetimeValidate ret;

    yyyymmdd = "2022-01-01";
    ret = ts::validate_yyyymmdd(yyyymmdd);
    assert(ret == ts::DatetimeValidate::OK);

    yyyymmdd = "2022-01-31";
    ret = ts::validate_yyyymmdd(yyyymmdd);
    assert(ret == ts::DatetimeValidate::OK);    

    yyyymmdd = "2022-02-01";
    ret = ts::validate_yyyymmdd(yyyymmdd);
    assert(ret == ts::DatetimeValidate::OK);    

    yyyymmdd = "2022-02-28";
    ret = ts::validate_yyyymmdd(yyyymmdd);
    assert(ret == ts::DatetimeValidate::OK);    

    yyyymmdd = "2024-02-29";
    ret = ts::validate_yyyymmdd(yyyymmdd);
    assert(ret == ts::DatetimeValidate::OK);    

    yyyymmdd = "2022-03-01";
    ret = ts::validate_yyyymmdd(yyyymmdd);
    assert(ret == ts::DatetimeValidate::OK);    

    yyyymmdd = "2022-03-31";
    ret = ts::validate_yyyymmdd(yyyymmdd);
    assert(ret == ts::DatetimeValidate::OK);    

    yyyymmdd = "2022-04-01";
    ret = ts::validate_yyyymmdd(yyyymmdd);
    assert(ret == ts::DatetimeValidate::OK);    

    yyyymmdd = "2022-04-30";
    ret = ts::validate_yyyymmdd(yyyymmdd);
    assert(ret == ts::DatetimeValidate::OK);    

    yyyymmdd = "2022-05-01";
    ret = ts::validate_yyyymmdd(yyyymmdd);
    assert(ret == ts::DatetimeValidate::OK);    

    yyyymmdd = "2022-05-31";
    ret = ts::validate_yyyymmdd(yyyymmdd);
    assert(ret == ts::DatetimeValidate::OK);    

    yyyymmdd = "2022-06-01";
    ret = ts::validate_yyyymmdd(yyyymmdd);
    assert(ret == ts::DatetimeValidate::OK);    

    yyyymmdd = "2022-06-30";
    ret = ts::validate_yyyymmdd(yyyymmdd);
    assert(ret == ts::DatetimeValidate::OK);    

    yyyymmdd = "2022-07-01";
    ret = ts::validate_yyyymmdd(yyyymmdd);
    assert(ret == ts::DatetimeValidate::OK);    

    yyyymmdd = "2022-07-31";
    ret = ts::validate_yyyymmdd(yyyymmdd);
    assert(ret == ts::DatetimeValidate::OK);    

    yyyymmdd = "2022-08-01";
    ret = ts::validate_yyyymmdd(yyyymmdd);
    assert(ret == ts::DatetimeValidate::OK);    

    yyyymmdd = "2022-08-31";
    ret = ts::validate_yyyymmdd(yyyymmdd);
    assert(ret == ts::DatetimeValidate::OK);    

    yyyymmdd = "2022-09-01";
    ret = ts::validate_yyyymmdd(yyyymmdd);
    assert(ret == ts::DatetimeValidate::OK);    

    yyyymmdd = "2022-09-30";
    ret = ts::validate_yyyymmdd(yyyymmdd);
    assert(ret == ts::DatetimeValidate::OK);

    yyyymmdd = "2022-10-01";
    ret = ts::validate_yyyymmdd(yyyymmdd);
    assert(ret == ts::DatetimeValidate::OK);    

    yyyymmdd = "2022-10-31";
    ret = ts::validate_yyyymmdd(yyyymmdd);
    assert(ret == ts::DatetimeValidate::OK); 

    yyyymmdd = "2022-11-01";
    ret = ts::validate_yyyymmdd(yyyymmdd);
    assert(ret == ts::DatetimeValidate::OK);    

    yyyymmdd = "2022-11-30";
    ret = ts::validate_yyyymmdd(yyyymmdd);
    assert(ret == ts::DatetimeValidate::OK); 

    yyyymmdd = "2022-12-01";
    ret = ts::validate_yyyymmdd(yyyymmdd);
    assert(ret == ts::DatetimeValidate::OK);    

    yyyymmdd = "2022-12-31";
    ret = ts::validate_yyyymmdd(yyyymmdd);
    assert(ret == ts::DatetimeValidate::OK);

    yyyymmdd = "2022-31-2222";
    ret = ts::validate_yyyymmdd(yyyymmdd);
    assert(ret == ts::DatetimeValidate::BAD_YYYYMMDD_LENGTH); 

    yyyymmdd = "2a22-12-31";
    ret = ts::validate_yyyymmdd(yyyymmdd);
    assert(ret == ts::DatetimeValidate::BAD_NUMBER_CHARACTER);

    yyyymmdd = "2022-1a-31";
    ret = ts::validate_yyyymmdd(yyyymmdd);
    assert(ret == ts::DatetimeValidate::BAD_NUMBER_CHARACTER);

    yyyymmdd = "2022-12-3a";
    ret = ts::validate_yyyymmdd(yyyymmdd);
    assert(ret == ts::DatetimeValidate::BAD_NUMBER_CHARACTER);

    yyyymmdd = "2022a12a30";
    ret = ts::validate_yyyymmdd(yyyymmdd);
    assert(ret == ts::DatetimeValidate::MISSING_DASH);

    yyyymmdd = "2022-12a30";
    ret = ts::validate_yyyymmdd(yyyymmdd);
    assert(ret == ts::DatetimeValidate::MISSING_DASH);

    yyyymmdd = "2022-25-30";
    ret = ts::validate_yyyymmdd(yyyymmdd);
    assert(ret == ts::DatetimeValidate::MONTH_OUT_OF_RANGE);

    yyyymmdd = "2022-01-40";
    ret = ts::validate_yyyymmdd(yyyymmdd);
    assert(ret == ts::DatetimeValidate::DAY_OUT_OF_RANGE);   
    
    std::cout << ">> Test 10 done" << std::endl;
    return 0;
}


int test11(){
    // TEST 11: testing today_add_yyyymmdd_hms() function
    
    std::string yyyymmdd_hms;
    ts::DatetimeValidate ret;

    yyyymmdd_hms = "2022-01-01 12:00:00";
    ret = ts::validate_yyyymmdd_hms(yyyymmdd_hms);
    assert(ret == ts::DatetimeValidate::OK);

    yyyymmdd_hms = "2022-01-0112:00:00";
    ret = ts::validate_yyyymmdd_hms(yyyymmdd_hms);
    assert(ret == ts::DatetimeValidate::MISSING_SPACE);

    yyyymmdd_hms = "202a-01-01 12:00:00";
    ret = ts::validate_yyyymmdd_hms(yyyymmdd_hms);
    assert(ret == ts::DatetimeValidate::BAD_NUMBER_CHARACTER);

    yyyymmdd_hms = "2022-01-01 12:0a:00";
    ret = ts::validate_yyyymmdd_hms(yyyymmdd_hms);
    assert(ret == ts::DatetimeValidate::BAD_NUMBER_CHARACTER);

    std::cout << ">> Test 11 done" << std::endl;
    return 0;
}


int test12(){
    // TEST 12: testing init_today() function

    time_t ret;
    time_t time_now;

    ret = ts::init_today();
    time_now = std::time(&time_now) + (TIMEZONE * 60 * 60);

    std::tm* to_struct;

    to_struct = std::gmtime(&ret);
    std::tm struct_ret = *to_struct;

    to_struct = std::gmtime(&time_now);
    std::tm struct_time_now = *to_struct;
    
    assert(struct_ret.tm_sec == 0);
    assert(struct_ret.tm_min == 0);
    assert(struct_ret.tm_hour == -TIMEZONE);
    assert(struct_ret.tm_yday == struct_time_now.tm_yday);
    assert(struct_ret.tm_mday == struct_time_now.tm_mday);
    assert(struct_ret.tm_mon == struct_time_now.tm_mon);
    assert(struct_ret.tm_year == struct_time_now.tm_year);

    std::cout << ">> Test 12 done" << std::endl;
    return 0;
}


int test13(){
    // TEST 13: testing init_year() function

    time_t ret;
    time_t time_now;

    ret = ts::init_year();
    time_now = std::time(&time_now) + (TIMEZONE * 60 * 60);
  
    std::tm* to_struct;

    to_struct = std::gmtime(&ret);
    std::tm struct_ret = *to_struct;

    to_struct = std::gmtime(&time_now);
    std::tm struct_time_now = *to_struct;
    
    assert(struct_ret.tm_sec == 0);
    assert(struct_ret.tm_min == 0);
    assert(struct_ret.tm_hour == -(TIMEZONE - 1));
    assert(struct_ret.tm_yday == 0);
    assert(struct_ret.tm_mday == 1);
    assert(struct_ret.tm_mon == 0);
    assert(struct_ret.tm_year == struct_time_now.tm_year);
    
    std::cout << ">> Test 13 done" << std::endl;
    return 0;
}


int test14(){
    // TEST 14: testing today_add_hms() function

    time_t ret;
    time_t time_now;
    std::tm* to_struct;
    std::tm struct_time_now;

    time_now = std::time(&time_now) + (TIMEZONE * 60 * 60);
    
    to_struct = std::gmtime(&time_now);
    struct_time_now = *to_struct;

    std::string hours = std::to_string(struct_time_now.tm_hour);
    std::string minutes = std::to_string(struct_time_now.tm_min + 1);
    std::string seconds = std::to_string(struct_time_now.tm_sec);

    if(struct_time_now.tm_hour < 10){
        hours = "0" + hours;
    }
    if(struct_time_now.tm_min + 1 < 10){
        minutes = "0" + minutes;
    }
    if(struct_time_now.tm_sec < 10){
        seconds = "0" + seconds;
    }
    ret = ts::today_add_hms(hours + ":" + minutes + ":" + seconds);

    to_struct = std::gmtime(&ret);
    std::tm struct_ret = *to_struct;

    assert(ret >= time_now);
       
    std::cout << ">> Test 14 done" << std::endl;
    return 0;
}


int test15(){
    // TEST 15: testing today_add_hms() function

    time_t ret;
    time_t time_now;
    std::tm* to_struct;
    std::tm struct_time_now;

    time_now = std::time(&time_now) + (TIMEZONE * 60 * 60);
    
    to_struct = std::gmtime(&time_now);
    struct_time_now = *to_struct;

    std::string hours = std::to_string(struct_time_now.tm_hour);
    std::string minutes = std::to_string(struct_time_now.tm_min - 1);
    std::string seconds = std::to_string(struct_time_now.tm_sec);
    
    if(struct_time_now.tm_hour < 10){
        hours = "0" + hours;
    }
    if(struct_time_now.tm_min - 1 < 10){
        minutes = "0" + minutes;
    }
    if(struct_time_now.tm_sec < 10){
        seconds = "0" + seconds;
    }
    ret = ts::today_add_hms(hours + ":" + minutes + ":" + seconds);

    to_struct = std::gmtime(&ret);
    std::tm struct_ret = *to_struct;

    assert(ret == 0);
       
    std::cout << ">> Test 15 done" << std::endl;
    return 0;
}


int test16(){
    // TEST 16: testing today_add_hms() function

    time_t ret;
    ret = ts::today_add_hms("120000");

    assert(ret == 0);
       
    std::cout << ">> Test 16 done" << std::endl;
    return 0;
}


int test17(){
    // TEST 17: testing today_add_dhms() function

    time_t ret;
    time_t time_now;
    std::tm* to_struct;
    std::tm struct_time_now;

    time_now = std::time(&time_now) + (TIMEZONE * 60 * 60);
    
    to_struct = std::gmtime(&time_now);
    struct_time_now = *to_struct;

    std::string hours = std::to_string(struct_time_now.tm_hour);
    std::string minutes = std::to_string(struct_time_now.tm_min + 1);
    std::string seconds = std::to_string(struct_time_now.tm_sec);
    
    if(struct_time_now.tm_hour < 10){
        hours = "0" + hours;
    }
    if(struct_time_now.tm_min + 1 < 10){
        minutes = "0" + minutes;
    }
    if(struct_time_now.tm_sec < 10){
        seconds = "0" + seconds;
    }    
    ret = ts::today_add_dhms(1, hours + ":" + minutes + ":" + seconds);

    to_struct = std::gmtime(&ret);
    std::tm struct_ret = *to_struct;

    assert(ret >= time_now);
       
    std::cout << ">> Test 17 done" << std::endl;
    return 0;
}


int test18(){
    // TEST 18: testing today_add_dhms() function

    time_t ret;
    time_t time_now;
    std::tm* to_struct;
    std::tm struct_time_now;

    time_now = std::time(&time_now) + (TIMEZONE * 60 * 60);
    
    to_struct = std::gmtime(&time_now);
    struct_time_now = *to_struct;

    std::string hours = std::to_string(struct_time_now.tm_hour);
    std::string minutes = std::to_string(struct_time_now.tm_min - 1);
    std::string seconds = std::to_string(struct_time_now.tm_sec);
    
    if(struct_time_now.tm_hour < 10){
        hours = "0" + hours;
    }
    if(struct_time_now.tm_min - 1 < 10){
        minutes = "0" + minutes;
    }
    if(struct_time_now.tm_sec < 10){
        seconds = "0" + seconds;
    }    
    ret = ts::today_add_dhms(0, hours + ":" + minutes + ":" + seconds);

    to_struct = std::gmtime(&ret);
    std::tm struct_ret = *to_struct;

    assert(ret == 0);
       
    std::cout << ">> Test 18 done" << std::endl;
    return 0;
}


int test19(){
    // TEST 19: testing today_add_dhms() function

    time_t ret;
    time_t time_now;
    std::tm* to_struct;
    std::tm struct_time_now;

    time_now = std::time(&time_now) + (TIMEZONE * 60 * 60);
    
    to_struct = std::gmtime(&time_now);
    struct_time_now = *to_struct;

    std::string hours = std::to_string(struct_time_now.tm_hour);
    std::string minutes = std::to_string(struct_time_now.tm_min - 1);
    std::string seconds = std::to_string(struct_time_now.tm_sec);
    
    if(struct_time_now.tm_hour < 10){
        hours = "0" + hours;
    }
    if(struct_time_now.tm_min - 1 < 10){
        minutes = "0" + minutes;
    }
    if(struct_time_now.tm_sec < 10){
        seconds = "0" + seconds;
    }    
    ret = ts::today_add_dhms(-15, hours + ":" + minutes + ":" + seconds);

    to_struct = std::gmtime(&ret);
    std::tm struct_ret = *to_struct;

    assert(ret == 0);
       
    std::cout << ">> Test 19 done" << std::endl;
    return 0;
}


int test20(){
    // TEST 16: testing today_add_dhms() function -> FAIL
    // Invalid hours-minutes-seconds subtring

    time_t ret;
    ret = ts::today_add_dhms(1, "120000");

    assert(ret == 0);
       
    std::cout << ">> Test 20 done" << std::endl;
    return 0;
}


int test21(){
    // TEST 21: testing today_add_wday_hms() function -> PASS
    // Using full weekday substrings

    time_t time_now = std::time(&time_now) + (TIMEZONE * 60 * 60);

    // Add one minute in seconds to current time
    time_t time_now_add;
    time_now_add = time_now + 60;
    
    // time_t to std::tm*
    std::tm* to_struct;
    to_struct = std::gmtime(&time_now);

    // std::tm* to std::tm
    std::tm struct_time_now_add = *to_struct;

    std::string wday;
    switch (struct_time_now_add.tm_wday)
    {
    case 0:
        wday = "Monday";
        break;
    case 1:
        wday = "Tuesday";
        break;
    case 2:
        wday = "Wednesday";
        break;
    case 3:
        wday = "Thursday";
        break;
    case 4:
        wday = "Friday";
        break;
    case 5:
        wday = "Saturday";
        break;
    case 6:
        wday = "Sunday";
        break;
    default:
        break;
    }

    std::string hours = (struct_time_now_add.tm_hour < 10) ? 
                        "0" + std::to_string(struct_time_now_add.tm_hour) :
                        std::to_string(struct_time_now_add.tm_hour);
    std::string minutes = (struct_time_now_add.tm_min < 10) ? 
                          "0" + std::to_string(struct_time_now_add.tm_min) :
                          std::to_string(struct_time_now_add.tm_min);
    std::string seconds = (struct_time_now_add.tm_sec < 10) ? 
                          "0" + std::to_string(struct_time_now_add.tm_sec) :
                          std::to_string(struct_time_now_add.tm_sec);

    time_t ret = ts::today_add_wday_hms(wday + " " + hours + ":" + minutes + ":" + seconds);

    to_struct = std::gmtime(&ret);
    std::tm struct_ret = *to_struct;

    assert(ret >= time_now);
       
    std::cout << ">> Test 21 done" << std::endl;
    return 0;
}


int test22(){
    // TEST 22: testing today_add_wday_hms() function -> PASS
    // Using abbreviated weekday substrings

    time_t time_now;
    time_now = std::time(&time_now) + (TIMEZONE * 60 * 60);

    // Add one minute in seconds to current time
    time_t time_now_add;
    time_now_add = time_now + 60;
    
    // time_t to std::tm*
    std::tm* to_struct;
    to_struct = std::gmtime(&time_now);
    
    // std::tm* to std::tm
    std::tm struct_time_now_add = *to_struct;

    std::string wday;
    switch (struct_time_now_add.tm_wday)
    {
    case 0:
        wday = "Mon";
        break;
    case 1:
        wday = "Tue";
        break;
    case 2:
        wday = "Wed";
        break;
    case 3:
        wday = "Thu";
        break;
    case 4:
        wday = "Fri";
        break;
    case 5:
        wday = "Sat";
        break;
    case 6:
        wday = "Sun";
        break;
    default:
        break;
    }

    std::string hours = (struct_time_now_add.tm_hour < 10) ? 
                        "0" + std::to_string(struct_time_now_add.tm_hour) :
                        std::to_string(struct_time_now_add.tm_hour);
    std::string minutes = (struct_time_now_add.tm_min < 10) ? 
                          "0" + std::to_string(struct_time_now_add.tm_min) :
                          std::to_string(struct_time_now_add.tm_min);
    std::string seconds = (struct_time_now_add.tm_sec < 10) ? 
                          "0" + std::to_string(struct_time_now_add.tm_sec) :
                          std::to_string(struct_time_now_add.tm_sec);
    
    time_t ret = ts::today_add_wday_hms(wday + " " + hours + ":" + minutes + ":" + seconds);

    to_struct = std::gmtime(&ret);
    std::tm struct_ret = *to_struct;

    assert(ret >= time_now);
       
    std::cout << ">> Test 22 done" << std::endl;
    return 0;
}


int test23(){
    // TEST 23: testing today_add_wday_hms() function -> PASS
    // Attempt setting input weekday to previous weekday (i.e. Sun -> Sat)

    time_t time_now = std::time(&time_now) + (TIMEZONE * 60 * 60);

    // Add one minute in seconds to current time
    time_t time_now_add;
    time_now_add = time_now + 60;
    
    // time_t to std::tm*
    std::tm* to_struct;
    to_struct = std::gmtime(&time_now_add);

    // std::tm* to std::tm
    std::tm struct_time_now_add = *to_struct;

    std::string wday;
    switch (struct_time_now_add.tm_wday)
    {
    case 0:
        wday = "Saturday";
        break;
    case 1:
        wday = "Sunday";
        break;
    case 2:
        wday = "Monday";
        break;
    case 3:
        wday = "Tuesday";
        break;
    case 4:
        wday = "Wednesday";
        break;
    case 5:
        wday = "Thrusday";
        break;
    case 6:
        wday = "Friday";
        break;
    default:
        break;
    }

    std::string hours = (struct_time_now_add.tm_hour < 10) ? 
                        "0" + std::to_string(struct_time_now_add.tm_hour) :
                        std::to_string(struct_time_now_add.tm_hour);
    std::string minutes = (struct_time_now_add.tm_min < 10) ? 
                          "0" + std::to_string(struct_time_now_add.tm_min) :
                          std::to_string(struct_time_now_add.tm_min);
    std::string seconds = (struct_time_now_add.tm_sec < 10) ? 
                          "0" + std::to_string(struct_time_now_add.tm_sec) :
                          std::to_string(struct_time_now_add.tm_sec);
       
    time_t ret = ts::today_add_wday_hms(wday + " " + hours + ":" + minutes + ":" + seconds);

    to_struct = std::gmtime(&ret);
    std::tm struct_ret = *to_struct;

    assert(ret >= time_now);
       
    std::cout << ">> Test 23 done" << std::endl;
    return 0;
}


int test24(){
    // TEST 24: testing today_add_wday_hms() function -> FAIL
    // Invalid hours-minutes-seconds substring

    time_t time_now = std::time(&time_now) + (TIMEZONE * 60 * 60);
  
    std::tm* to_struct;
    to_struct = std::gmtime(&time_now);
    
    std::tm struct_time_now = *to_struct;

    std::string wday;
    switch (struct_time_now.tm_wday)
    {
    case 0:
        wday = "Monday";
        break;
    case 1:
        wday = "Tuesday";
        break;
    case 2:
        wday = "Wednesday";
        break;
    case 3:
        wday = "Thursday";
        break;
    case 4:
        wday = "Friday";
        break;
    case 5:
        wday = "Saturday";
        break;
    case 6:
        wday = "Sunday";
        break;
    default:
        break;
    }
       
    time_t ret = ts::today_add_wday_hms(wday + "120000");

    to_struct = std::gmtime(&ret);
    std::tm struct_ret = *to_struct;

    assert(ret == 0);
       
    std::cout << ">> Test 24 done" << std::endl;
    return 0;
}

int test25(){
    // TEST 25: testing run_task() and get_output() methods -> PASS

    std::string t_name = "Task Name";
    std::string t_description = "A short description for this task";
    std::string t_script_name = "../scripts/cat_test.sh";
    std::string t_frequency = "Once";

    ts::Task* t = new ts::Task(t_name, t_description, t_script_name, t_frequency);
    
    t->run_task();

    assert(t->get_output() == "ls -l");

    delete t;

    std::cout << ">> Test 25 done" << std::endl;
    return 0;
}


int test26(){
    // TEST 26: testing today_add_mmdd() function -> PASS
    // Current time + 1 day

    time_t time_now;
    time_now = std::time(&time_now) + (TIMEZONE * 60 * 60);

    // Add one day in seconds to current time
    time_t time_now_add;
    time_now_add = time_now + 86400;
    
    std::tm* to_struct;
    to_struct = std::gmtime(&time_now_add);

    std::tm struct_time_now_add;
    struct_time_now_add = *to_struct;

    std::string months = (struct_time_now_add.tm_mon < 10) ? 
                         "0" + std::to_string(struct_time_now_add.tm_mon) :
                         std::to_string(struct_time_now_add.tm_mon);  
    std::string days = (struct_time_now_add.tm_mday < 10) ? 
                       "0" + std::to_string(struct_time_now_add.tm_mday) :
                       std::to_string(struct_time_now_add.tm_mday);
        
    time_t ret;
    ret = ts::today_add_mmdd(months + "-" + days);

    to_struct = std::gmtime(&ret);

    std::tm struct_ret;
    struct_ret = *to_struct;

    assert(ret >= time_now);
       
    std::cout << ">> Test 26 done" << std::endl;
    return 0;
}


int main(){
    bool all    = true;
    bool t1     = false;
    bool t2     = false;
    bool t3     = false;
    bool t4     = false;
    bool t5     = false;
    bool t6     = false;
    bool t7     = false;
    bool t8     = false;
    bool t9     = false;
    bool t10     = false;
    bool t11     = false;
    bool t12     = false;
    bool t13     = false;
    bool t14     = false;
    bool t15     = false;
    bool t16     = false;
    bool t17     = false;
    bool t18     = false;
    bool t19     = false;
    bool t20     = false;
    bool t21     = false;
    bool t22     = false;
    bool t23     = false;
    bool t24     = false;
    bool t25     = false;
    bool t26     = false;

    if(t1 || all){
        test1();
    }
    if(t2 || all){
        test2();
    }
    if(t3 || all){
        test3();
    }
    if(t4 || all){
        test4();
    }
    if(t5 || all){
        test5();
    }
    if(t6 || all){
        test6();
    }
    if(t7 || all){
        test7();
    }
    if(t8 || all){
        test8();
    }
    if(t9 || all){
        test9();
    }
    if(t10 || all){
        test10();
    }
    if(t11 || all){
        test11();
    }
    if(t12 || all){
        test12();
    }
    if(t13 || all){
        test13();
    }
    if(t14 || all){
        test14();
    }
    if(t15 || all){
        test15();
    }
    if(t16 || all){
        test16();
    }
    if(t17 || all){
        test17();
    }
    if(t18 || all){
        test18();
    }
    if(t19 || all){
        test19();
    }
    if(t20 || all){
        test20();
    }
    if(t21 || all){
        test21();
    }
    if(t22 || all){
        test22();
    }
    if(t23 || all){
        test23();
    }
    if(t24 || all){
        test24();
    }
    if(t25 || all){
        test25();
    }
    if(t26 || all){
        test26();
    }

    return 0;
}
