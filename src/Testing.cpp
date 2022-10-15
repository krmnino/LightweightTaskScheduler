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
    std::string t_input_execution_datetime = "12:00:00"; // ignored because Task is hourly

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
    std::string t_input_execution_datetime = "12:00:00"; // ignored because Task is hourly

    ts::Task* t = new ts::Task(t_name, t_description, t_script_name, t_frequency, t_input_execution_datetime);
    
    std::string execution_datetime_fmt = t->get_execution_datetime_fmt();
    std::string creation_datetime_fmt = t->get_creation_datetime_fmt();
    time_t creation_datetime = t->get_creation_datetime(); 
    time_t execution_datetime = t->get_execution_datetime();

    std::tm* to_struct;
    to_struct = std::gmtime(&creation_datetime);

    std::tm struct_time_now_add;
    struct_time_now_add = *to_struct;

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
    // TEST 14: testing today_add_hms() function -> PASS
    // Add one minute in seconds to current time

    time_t time_now = std::time(&time_now) + (TIMEZONE * 60 * 60);
    
    // Add one minute in seconds to current time
    time_t time_now_add = time_now + 60;

    // time_t to std::tm*
    std::tm* to_struct;
    to_struct = std::gmtime(&time_now_add);
    
    // std::tm* to std::tm
    std::tm struct_time_now_add = *to_struct;

    std::string hours = (struct_time_now_add.tm_hour < 10) ? 
                        "0" + std::to_string(struct_time_now_add.tm_hour) :
                        std::to_string(struct_time_now_add.tm_hour);
    std::string minutes = (struct_time_now_add.tm_min < 10) ? 
                          "0" + std::to_string(struct_time_now_add.tm_min) :
                          std::to_string(struct_time_now_add.tm_min);
    std::string seconds = (struct_time_now_add.tm_sec < 10) ? 
                          "0" + std::to_string(struct_time_now_add.tm_sec) :
                          std::to_string(struct_time_now_add.tm_sec);
                          
    time_t ret = ts::today_add_hms(hours + ":" + minutes + ":" + seconds);

    assert(ret >= time_now);

    to_struct = std::gmtime(&ret);
    std::tm struct_ret = *to_struct;
      
    std::cout << ">> Test 14 done" << std::endl;
    return 0;
}


int test15(){
    // TEST 15: testing today_add_hms() function -> FAIL
    // Invalid time. Current time minus 1 minute

    time_t time_now = std::time(&time_now) + (TIMEZONE * 60 * 60);
    
    // Add minus one minute in seconds to current time
    time_t time_now_add = time_now + (-60);
    
    // time_t to std::tm*
    std::tm* to_struct;
    to_struct = std::gmtime(&time_now_add);

    // std::tm* to std::tm
    std::tm struct_time_now_add = *to_struct;

    std::string hours = (struct_time_now_add.tm_hour < 10) ? 
                        "0" + std::to_string(struct_time_now_add.tm_hour) :
                        std::to_string(struct_time_now_add.tm_hour);
    std::string minutes = (struct_time_now_add.tm_min < 10) ? 
                          "0" + std::to_string(struct_time_now_add.tm_min) :
                          std::to_string(struct_time_now_add.tm_min);
    std::string seconds = (struct_time_now_add.tm_sec < 10) ? 
                          "0" + std::to_string(struct_time_now_add.tm_sec) :
                          std::to_string(struct_time_now_add.tm_sec);

    time_t ret = ts::today_add_hms(hours + ":" + minutes + ":" + seconds);

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
    // TEST 17: testing today_add_dhms() function -> PASS
    // Add one minute in seconds to current time

    time_t time_now = std::time(&time_now) + (TIMEZONE * 60 * 60);

    // Add one minute in seconds to current time
    time_t time_now_add = time_now + 60;

    // time_t to std::tm*
    std::tm* to_struct;
    to_struct = std::gmtime(&time_now_add);
    
    // std::tm* to std::tm
    std::tm struct_time_now_add = *to_struct;

    std::string hours = (struct_time_now_add.tm_hour < 10) ? 
                        "0" + std::to_string(struct_time_now_add.tm_hour) :
                        std::to_string(struct_time_now_add.tm_hour);
    std::string minutes = (struct_time_now_add.tm_min < 10) ? 
                          "0" + std::to_string(struct_time_now_add.tm_min) :
                          std::to_string(struct_time_now_add.tm_min);
    std::string seconds = (struct_time_now_add.tm_sec < 10) ? 
                          "0" + std::to_string(struct_time_now_add.tm_sec) :
                          std::to_string(struct_time_now_add.tm_sec);

    time_t ret = ts::today_add_dhms(1, hours + ":" + minutes + ":" + seconds);

    assert(ret >= time_now);
       
    std::cout << ">> Test 17 done" << std::endl;
    return 0;
}


int test18(){
    // TEST 18: testing today_add_dhms() function -> FAIL
    // Invalid time. Current time minus 1 minute

    time_t time_now = std::time(&time_now) + (TIMEZONE * 60 * 60);

    // Add minus one minute in seconds to current time
    time_t time_now_add = time_now + (-60);

    // time_t to std::tm*
    std::tm* to_struct;
    to_struct = std::gmtime(&time_now_add);

    // std::tm* to std::tm
    std::tm struct_time_now_add;    
    struct_time_now_add = *to_struct;
    
    std::string hours = (struct_time_now_add.tm_hour < 10) ? 
                        "0" + std::to_string(struct_time_now_add.tm_hour) :
                        std::to_string(struct_time_now_add.tm_hour);
    std::string minutes = (struct_time_now_add.tm_min < 10) ? 
                          "0" + std::to_string(struct_time_now_add.tm_min) :
                          std::to_string(struct_time_now_add.tm_min);
    std::string seconds = (struct_time_now_add.tm_sec < 10) ? 
                          "0" + std::to_string(struct_time_now_add.tm_sec) :
                          std::to_string(struct_time_now_add.tm_sec);

    time_t ret = ts::today_add_dhms(0, hours + ":" + minutes + ":" + seconds);

    assert(ret == 0);
       
    std::cout << ">> Test 18 done" << std::endl;
    return 0;
}


int test19(){
    // TEST 19: testing today_add_dhms() function -> FAIL
    // Invalid value for day parameter

    time_t time_now = std::time(&time_now) + (TIMEZONE * 60 * 60);

    // Add one minute in seconds to current time
    time_t time_now_add = time_now + 60;
    
    // time_t to std::tm*
    std::tm* to_struct;
    to_struct = std::gmtime(&time_now_add);

    // std::tm* to std::tm
    std::tm struct_time_now_add = *to_struct;

    std::string hours = (struct_time_now_add.tm_hour < 10) ? 
                        "0" + std::to_string(struct_time_now_add.tm_hour) :
                        std::to_string(struct_time_now_add.tm_hour);
    std::string minutes = (struct_time_now_add.tm_min < 10) ? 
                          "0" + std::to_string(struct_time_now_add.tm_min) :
                          std::to_string(struct_time_now_add.tm_min);
    std::string seconds = (struct_time_now_add.tm_sec < 10) ? 
                          "0" + std::to_string(struct_time_now_add.tm_sec) :
                          std::to_string(struct_time_now_add.tm_sec);
    
    time_t ret = ts::today_add_dhms(-15, hours + ":" + minutes + ":" + seconds);

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
    time_t time_now_add = time_now + 60;
    
    // time_t to std::tm*
    std::tm* to_struct;
    to_struct = std::gmtime(&time_now_add);

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

    assert(ret >= time_now);
       
    std::cout << ">> Test 21 done" << std::endl;
    return 0;
}


int test22(){
    // TEST 22: testing today_add_wday_hms() function -> PASS
    // Using abbreviated weekday substrings

    time_t time_now = std::time(&time_now) + (TIMEZONE * 60 * 60);

    // Add one minute in seconds to current time
    time_t time_now_add = time_now + 60;
    
    // time_t to std::tm*
    std::tm* to_struct;
    to_struct = std::gmtime(&time_now_add);
    
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

    assert(ret >= time_now);
       
    std::cout << ">> Test 22 done" << std::endl;
    return 0;
}


int test23(){
    // TEST 23: testing today_add_wday_hms() function -> PASS
    // Attempt setting input weekday to previous weekday (i.e. Sun -> Sat)

    time_t time_now = std::time(&time_now) + (TIMEZONE * 60 * 60);

    // Add one minute in seconds to current time
    time_t time_now_add = time_now + 60;
    
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
        wday = "Thursday";
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

    time_t time_now = std::time(&time_now) + (TIMEZONE * 60 * 60);

    // Add one day in seconds to current time
    time_t time_now_add = time_now + 86400;
    
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
        
    time_t ret = ts::today_add_mmdd(months + "-" + days);

    assert(ret >= time_now);
       
    std::cout << ">> Test 26 done" << std::endl;
    return 0;
}


int test27(){
    // TEST 27: testing today_add_mmdd() function -> FAIL
    // Current time - 1 day

    time_t time_now = std::time(&time_now) + (TIMEZONE * 60 * 60);

    // Add minus one day in seconds to current time
    time_t time_now_add = time_now + (-86400);
    
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
        
    time_t ret = ts::today_add_mmdd(months + "-" + days);

    assert(ret == 0);
       
    std::cout << ">> Test 27 done" << std::endl;
    return 0;
}


int test28(){
    // TEST 28: testing today_add_mmdd() function -> FAIL
    // Invalid months-days subtring

    time_t ret;
    ret = ts::today_add_mmdd("0212");

    assert(ret == 0);
       
    std::cout << ">> Test 28 done" << std::endl;
    return 0;
}


int test29(){
    // TEST 29: testing today_add_mmdd_hms() function -> PASS
    // Current time + 1 day

    time_t time_now = std::time(&time_now) + (TIMEZONE * 60 * 60);

    // Add one day in seconds to current time
    time_t time_now_add = time_now + 86400;
    
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
    std::string hours = (struct_time_now_add.tm_hour < 10) ? 
                        "0" + std::to_string(struct_time_now_add.tm_hour) :
                        std::to_string(struct_time_now_add.tm_hour);
    std::string minutes = (struct_time_now_add.tm_min < 10) ? 
                          "0" + std::to_string(struct_time_now_add.tm_min) :
                          std::to_string(struct_time_now_add.tm_min);
    std::string seconds = (struct_time_now_add.tm_sec < 10) ? 
                          "0" + std::to_string(struct_time_now_add.tm_sec) :
                          std::to_string(struct_time_now_add.tm_sec);
    
    time_t ret = ts::today_add_mmdd_hms(months + "-" + days + " " + hours + ":" + minutes + ":" + seconds);

    to_struct = std::gmtime(&ret);

    assert(ret >= time_now);
       
    std::cout << ">> Test 29 done" << std::endl;
    return 0;
}


int test30(){
    // TEST 30: testing today_add_mmdd_hms() function -> PASS
    // Current time + 30 days

    time_t time_now = std::time(&time_now) + (TIMEZONE * 60 * 60);

    // Add 30 days in seconds to current time
    time_t time_now_add = time_now + 2592000;
    
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
    std::string hours = (struct_time_now_add.tm_hour < 10) ? 
                        "0" + std::to_string(struct_time_now_add.tm_hour) :
                        std::to_string(struct_time_now_add.tm_hour);
    std::string minutes = (struct_time_now_add.tm_min < 10) ? 
                          "0" + std::to_string(struct_time_now_add.tm_min) :
                          std::to_string(struct_time_now_add.tm_min);
    std::string seconds = (struct_time_now_add.tm_sec < 10) ? 
                          "0" + std::to_string(struct_time_now_add.tm_sec) :
                          std::to_string(struct_time_now_add.tm_sec);
    
    time_t ret = ts::today_add_mmdd_hms(months + "-" + days + " " + hours + ":" + minutes + ":" + seconds);

    assert(ret >= time_now);
       
    std::cout << ">> Test 30 done" << std::endl;
    return 0;
}


int test31(){
    // TEST 31: testing today_add_mmdd_hms() function -> FAIL
    // Current time - 1 day

    time_t time_now = std::time(&time_now) + (TIMEZONE * 60 * 60);

    // Add minus one day in seconds to current time
    time_t time_now_add = time_now + (-86400);
    
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
    std::string hours = (struct_time_now_add.tm_hour < 10) ? 
                        "0" + std::to_string(struct_time_now_add.tm_hour) :
                        std::to_string(struct_time_now_add.tm_hour);
    std::string minutes = (struct_time_now_add.tm_min < 10) ? 
                          "0" + std::to_string(struct_time_now_add.tm_min) :
                          std::to_string(struct_time_now_add.tm_min);
    std::string seconds = (struct_time_now_add.tm_sec < 10) ? 
                          "0" + std::to_string(struct_time_now_add.tm_sec) :
                          std::to_string(struct_time_now_add.tm_sec);
    
    time_t ret = ts::today_add_mmdd_hms(months + "-" + days + " " + hours + ":" + minutes + ":" + seconds);

    to_struct = std::gmtime(&ret);

    std::tm struct_ret;
    struct_ret = *to_struct;

    assert(ret == 0);
       
    std::cout << ">> Test 31 done" << std::endl;
    return 0;
}


int test32(){
    // TEST 32: testing today_add_mmdd_hms() function -> FAIL
    // Invalid months-days subtring

    time_t ret;
    ret = ts::today_add_mmdd("0212 12:00:00");

    assert(ret == 0);
       
    std::cout << ">> Test 32 done" << std::endl;
    return 0;
}


int test33(){
    // TEST 33: testing today_add_mmdd_hms() function -> FAIL
    // Invalid hours-minutes-seconds subtring

    time_t ret;
    ret = ts::today_add_mmdd("02-12 120000");

    assert(ret == 0);
       
    std::cout << ">> Test 33 done" << std::endl;
    return 0;
}


int test34(){
    // TEST 34: testing today_add_yyyymmdd() function -> PASS
    // Current time + 1 day

    time_t time_now = std::time(&time_now) + (TIMEZONE * 60 * 60);

    // Add one day in seconds to current time
    time_t time_now_add = time_now + 86400;
    
    std::tm* to_struct;
    to_struct = std::gmtime(&time_now_add);

    std::tm struct_time_now_add;
    struct_time_now_add = *to_struct;

    std::string years = std::to_string(1900 + struct_time_now_add.tm_year);
    std::string months = (struct_time_now_add.tm_mon < 10) ? 
                         "0" + std::to_string(struct_time_now_add.tm_mon) :
                         std::to_string(struct_time_now_add.tm_mon);  
    std::string days = (struct_time_now_add.tm_mday < 10) ? 
                       "0" + std::to_string(struct_time_now_add.tm_mday) :
                       std::to_string(struct_time_now_add.tm_mday);
        
    time_t ret = ts::today_add_yyyymmdd(years + "-" + months + "-" + days);

    assert(ret >= time_now);
       
    std::cout << ">> Test 34 done" << std::endl;
    return 0;
}


int test35(){
    // TEST 35: testing today_add_yyyymmdd() function -> PASS
    // Current time + 30 days

    time_t time_now = std::time(&time_now) + (TIMEZONE * 60 * 60);

    // Add 30 days in seconds to current time
    time_t time_now_add = time_now + 2592000;
    
    std::tm* to_struct;
    to_struct = std::gmtime(&time_now_add);

    std::tm struct_time_now_add;
    struct_time_now_add = *to_struct;

    std::string years = std::to_string(1900 + struct_time_now_add.tm_year);
    std::string months = (struct_time_now_add.tm_mon < 10) ? 
                         "0" + std::to_string(struct_time_now_add.tm_mon) :
                         std::to_string(struct_time_now_add.tm_mon);  
    std::string days = (struct_time_now_add.tm_mday < 10) ? 
                       "0" + std::to_string(struct_time_now_add.tm_mday) :
                       std::to_string(struct_time_now_add.tm_mday);
        
    time_t ret = ts::today_add_yyyymmdd(years + "-" + months + "-" + days);

    assert(ret >= time_now);
       
    std::cout << ">> Test 35 done" << std::endl;
    return 0;
}


int test36(){
    // TEST 36: testing today_add_yyyymmdd() function -> PASS
    // Current time + 365 days

    time_t time_now = std::time(&time_now) + (TIMEZONE * 60 * 60);

    // Add 30 days in seconds to current time
    time_t time_now_add = time_now + 31536000;
    
    std::tm* to_struct;
    to_struct = std::gmtime(&time_now_add);

    std::tm struct_time_now_add;
    struct_time_now_add = *to_struct;

    std::string years = std::to_string(1900 + struct_time_now_add.tm_year);
    std::string months = (struct_time_now_add.tm_mon < 10) ? 
                         "0" + std::to_string(struct_time_now_add.tm_mon) :
                         std::to_string(struct_time_now_add.tm_mon);  
    std::string days = (struct_time_now_add.tm_mday < 10) ? 
                       "0" + std::to_string(struct_time_now_add.tm_mday) :
                       std::to_string(struct_time_now_add.tm_mday);
        
    time_t ret = ts::today_add_yyyymmdd(years + "-" + months + "-" + days);

    assert(ret >= time_now);
       
    std::cout << ">> Test 36 done" << std::endl;
    return 0;
}


int test37(){
    // TEST 37: testing today_add_yyyymmdd() function -> FAIL
    // Current time - 1 day

    time_t time_now = std::time(&time_now) + (TIMEZONE * 60 * 60);

    // Add minus one day in seconds to current time
    time_t time_now_add = time_now + (-86400);
    
    std::tm* to_struct;
    to_struct = std::gmtime(&time_now_add);

    std::tm struct_time_now_add;
    struct_time_now_add = *to_struct;

    std::string years = std::to_string(1900 + struct_time_now_add.tm_year);
    std::string months = (struct_time_now_add.tm_mon < 10) ? 
                         "0" + std::to_string(struct_time_now_add.tm_mon) :
                         std::to_string(struct_time_now_add.tm_mon);  
    std::string days = (struct_time_now_add.tm_mday < 10) ? 
                       "0" + std::to_string(struct_time_now_add.tm_mday) :
                       std::to_string(struct_time_now_add.tm_mday);
        
    time_t ret = ts::today_add_yyyymmdd(years + "-" + months + "-" + days);

    assert(ret == 0);
       
    std::cout << ">> Test 37 done" << std::endl;
    return 0;
}


int test38(){
    // TEST 38: testing today_add_yyyymmdd() function -> FAIL
    // Invalid years-months-days subtring

    time_t ret;
    ret = ts::today_add_mmdd("20220212");

    assert(ret == 0);
       
    std::cout << ">> Test 38 done" << std::endl;
    return 0;
}


int test39(){
    // TEST 39: testing today_add_yyyymmdd_hms() function -> PASS
    // Current time + 1 day

    time_t time_now = std::time(&time_now) + (TIMEZONE * 60 * 60);

    // Add one day in seconds to current time
    time_t time_now_add = time_now + 86400;
    
    std::tm* to_struct;
    to_struct = std::gmtime(&time_now_add);

    std::tm struct_time_now_add;
    struct_time_now_add = *to_struct;

    std::string years = std::to_string(1900 + struct_time_now_add.tm_year);
    std::string months = (struct_time_now_add.tm_mon < 10) ? 
                         "0" + std::to_string(struct_time_now_add.tm_mon) :
                         std::to_string(struct_time_now_add.tm_mon);  
    std::string days = (struct_time_now_add.tm_mday < 10) ? 
                       "0" + std::to_string(struct_time_now_add.tm_mday) :
                       std::to_string(struct_time_now_add.tm_mday);
    std::string hours = (struct_time_now_add.tm_hour < 10) ? 
                        "0" + std::to_string(struct_time_now_add.tm_hour) :
                        std::to_string(struct_time_now_add.tm_hour);
    std::string minutes = (struct_time_now_add.tm_min < 10) ? 
                          "0" + std::to_string(struct_time_now_add.tm_min) :
                          std::to_string(struct_time_now_add.tm_min);
    std::string seconds = (struct_time_now_add.tm_sec < 10) ? 
                          "0" + std::to_string(struct_time_now_add.tm_sec) :
                          std::to_string(struct_time_now_add.tm_sec);
        
    time_t ret = ts::today_add_yyyymmdd_hms(years + "-" + months + "-" + days + " " + hours + ":" + minutes + ":" + seconds);

    assert(ret >= time_now);
       
    std::cout << ">> Test 39 done" << std::endl;
    return 0;
}


int test40(){
    // TEST 40: testing today_add_yyyymmdd_hms() function -> PASS
    // Current time + 30 days

    time_t time_now = std::time(&time_now) + (TIMEZONE * 60 * 60);

    // Add 30 days in seconds to current time
    time_t time_now_add = time_now + 2592000;
    
    std::tm* to_struct;
    to_struct = std::gmtime(&time_now_add);

    std::tm struct_time_now_add;
    struct_time_now_add = *to_struct;

    std::string years = std::to_string(1900 + struct_time_now_add.tm_year);
    std::string months = (struct_time_now_add.tm_mon < 10) ? 
                         "0" + std::to_string(struct_time_now_add.tm_mon) :
                         std::to_string(struct_time_now_add.tm_mon);  
    std::string days = (struct_time_now_add.tm_mday < 10) ? 
                       "0" + std::to_string(struct_time_now_add.tm_mday) :
                       std::to_string(struct_time_now_add.tm_mday);
    std::string hours = (struct_time_now_add.tm_hour < 10) ? 
                        "0" + std::to_string(struct_time_now_add.tm_hour) :
                        std::to_string(struct_time_now_add.tm_hour);
    std::string minutes = (struct_time_now_add.tm_min < 10) ? 
                          "0" + std::to_string(struct_time_now_add.tm_min) :
                          std::to_string(struct_time_now_add.tm_min);
    std::string seconds = (struct_time_now_add.tm_sec < 10) ? 
                          "0" + std::to_string(struct_time_now_add.tm_sec) :
                          std::to_string(struct_time_now_add.tm_sec);                       
        
    time_t ret = ts::today_add_yyyymmdd_hms(years + "-" + months + "-" + days + " " + hours + ":" + minutes + ":" + seconds);

    assert(ret >= time_now);
       
    std::cout << ">> Test 40 done" << std::endl;
    return 0;
}


int test41(){
    // TEST 41: testing today_add_yyyymmdd_hms() function -> PASS
    // Current time + 365 days

    time_t time_now = std::time(&time_now) + (TIMEZONE * 60 * 60);

    // Add 30 days in seconds to current time
    time_t time_now_add = time_now + 31536000;
    
    std::tm* to_struct;
    to_struct = std::gmtime(&time_now_add);

    std::tm struct_time_now_add;
    struct_time_now_add = *to_struct;

    std::string years = std::to_string(1900 + struct_time_now_add.tm_year);
    std::string months = (struct_time_now_add.tm_mon < 10) ? 
                         "0" + std::to_string(struct_time_now_add.tm_mon) :
                         std::to_string(struct_time_now_add.tm_mon);  
    std::string days = (struct_time_now_add.tm_mday < 10) ? 
                       "0" + std::to_string(struct_time_now_add.tm_mday) :
                       std::to_string(struct_time_now_add.tm_mday);
    std::string hours = (struct_time_now_add.tm_hour < 10) ? 
                        "0" + std::to_string(struct_time_now_add.tm_hour) :
                        std::to_string(struct_time_now_add.tm_hour);
    std::string minutes = (struct_time_now_add.tm_min < 10) ? 
                          "0" + std::to_string(struct_time_now_add.tm_min) :
                          std::to_string(struct_time_now_add.tm_min);
    std::string seconds = (struct_time_now_add.tm_sec < 10) ? 
                          "0" + std::to_string(struct_time_now_add.tm_sec) :
                          std::to_string(struct_time_now_add.tm_sec);                       
        
    time_t ret = ts::today_add_yyyymmdd_hms(years + "-" + months + "-" + days + " " + hours + ":" + minutes + ":" + seconds);

    assert(ret >= time_now);
       
    std::cout << ">> Test 41 done" << std::endl;
    return 0;
}


int test42(){
    // TEST 42: testing today_add_yyyymmdd_hms() function -> PASS
    // Current time + 1 minute

    time_t time_now = std::time(&time_now) + (TIMEZONE * 60 * 60);

    // Add one minute in seconds to current time
    time_t time_now_add = time_now + 60;
    
    std::tm* to_struct;
    to_struct = std::gmtime(&time_now_add);

    std::tm struct_time_now_add;
    struct_time_now_add = *to_struct;

    std::string years = std::to_string(1900 + struct_time_now_add.tm_year);
    std::string months = (struct_time_now_add.tm_mon < 10) ? 
                         "0" + std::to_string(struct_time_now_add.tm_mon) :
                         std::to_string(struct_time_now_add.tm_mon);  
    std::string days = (struct_time_now_add.tm_mday < 10) ? 
                       "0" + std::to_string(struct_time_now_add.tm_mday) :
                       std::to_string(struct_time_now_add.tm_mday);
    std::string hours = (struct_time_now_add.tm_hour < 10) ? 
                        "0" + std::to_string(struct_time_now_add.tm_hour) :
                        std::to_string(struct_time_now_add.tm_hour);
    std::string minutes = (struct_time_now_add.tm_min < 10) ? 
                          "0" + std::to_string(struct_time_now_add.tm_min) :
                          std::to_string(struct_time_now_add.tm_min);
    std::string seconds = (struct_time_now_add.tm_sec < 10) ? 
                          "0" + std::to_string(struct_time_now_add.tm_sec) :
                          std::to_string(struct_time_now_add.tm_sec);                       
        
    time_t ret = ts::today_add_yyyymmdd_hms(years + "-" + months + "-" + days + " " + hours + ":" + minutes + ":" + seconds);

    assert(ret >= time_now);
    
    std::cout << ">> Test 42 done" << std::endl;
    return 0;
}


int test43(){
    // TEST 43: testing today_add_yyyymmdd_hms() function -> FAIL
    // Current time - 1 day

    time_t time_now = std::time(&time_now) + (TIMEZONE * 60 * 60);

    // Add one day in seconds to current time
    time_t time_now_add = time_now + (-86400);
    
    std::tm* to_struct;
    to_struct = std::gmtime(&time_now_add);

    std::tm struct_time_now_add;
    struct_time_now_add = *to_struct;

    std::string years = std::to_string(1900 + struct_time_now_add.tm_year);
    std::string months = (struct_time_now_add.tm_mon < 10) ? 
                         "0" + std::to_string(struct_time_now_add.tm_mon) :
                         std::to_string(struct_time_now_add.tm_mon);  
    std::string days = (struct_time_now_add.tm_mday < 10) ? 
                       "0" + std::to_string(struct_time_now_add.tm_mday) :
                       std::to_string(struct_time_now_add.tm_mday);
    std::string hours = (struct_time_now_add.tm_hour < 10) ? 
                        "0" + std::to_string(struct_time_now_add.tm_hour) :
                        std::to_string(struct_time_now_add.tm_hour);
    std::string minutes = (struct_time_now_add.tm_min < 10) ? 
                          "0" + std::to_string(struct_time_now_add.tm_min) :
                          std::to_string(struct_time_now_add.tm_min);
    std::string seconds = (struct_time_now_add.tm_sec < 10) ? 
                          "0" + std::to_string(struct_time_now_add.tm_sec) :
                          std::to_string(struct_time_now_add.tm_sec);                       
        
    time_t ret = ts::today_add_yyyymmdd_hms(years + "-" + months + "-" + days + " " + hours + ":" + minutes + ":" + seconds);

    assert(ret == 0);
    
    std::cout << ">> Test 43 done" << std::endl;
    return 0;
}


int test44(){
    // TEST 44: testing today_add_yyyymmdd_hms() function -> FAIL
    // Invalid years-months-days subtring

    time_t ret;
    ret = ts::today_add_mmdd("20220212 12:00:00");

    assert(ret == 0);
       
    std::cout << ">> Test 44 done" << std::endl;
    return 0;
}


int test45(){
    // TEST 45: testing today_add_yyyymmdd_hms() function -> FAIL
    // Invalid hours-minutes-seconds subtring

    time_t ret;
    ret = ts::today_add_mmdd("2022-02-12 120000");

    assert(ret == 0);
       
    std::cout << ">> Test 45 done" << std::endl;
    return 0;
}


int test46(){
    // TEST 46: testing get_datetime_format() function -> PASS
    // Datetime format HH:MM:SS
    
    std::string datetime = "12:00:00";
    ts::DatetimeFormat ret = ts::get_datetime_format(datetime);

    assert(ret == ts::DatetimeFormat::HHMMSS);

    std::cout << ">> Test 46 done" << std::endl;
    return 0;
}


int test47(){
    // TEST 47: testing get_datetime_format() function -> PASS
    // Datetime format abbreviated weekday + HH:MM:SS
    
    ts::DatetimeFormat ret;
    std::string datetime;

    datetime = "Sun 20:00:00";
    ret = ts::get_datetime_format(datetime);
    assert(ret == ts::DatetimeFormat::WDAY_HHMMSS);

    datetime = "Mon 20:00:00";
    ret = ts::get_datetime_format(datetime);
    assert(ret == ts::DatetimeFormat::WDAY_HHMMSS);

    datetime = "Tue 20:00:00";
    ret = ts::get_datetime_format(datetime);
    assert(ret == ts::DatetimeFormat::WDAY_HHMMSS);

    datetime = "Wed 20:00:00";
    ret = ts::get_datetime_format(datetime);
    assert(ret == ts::DatetimeFormat::WDAY_HHMMSS);

    datetime = "Thu 20:00:00";
    ret = ts::get_datetime_format(datetime);
    assert(ret == ts::DatetimeFormat::WDAY_HHMMSS);

    datetime = "Fri 20:00:00";
    ret = ts::get_datetime_format(datetime);
    assert(ret == ts::DatetimeFormat::WDAY_HHMMSS);

    datetime = "Sat 20:00:00";
    ret = ts::get_datetime_format(datetime);
    assert(ret == ts::DatetimeFormat::WDAY_HHMMSS);

    std::cout << ">> Test 47 done" << std::endl;
    return 0;
}


int test48(){
    // TEST 48: testing get_datetime_format() function -> PASS
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

    std::cout << ">> Test 48 done" << std::endl;
    return 0;
}


int test49(){
    // TEST 49: testing get_datetime_format() function -> PASS
    // Datetime format MM-DD
    
    std::string datetime = "02-22";
    ts::DatetimeFormat ret = ts::get_datetime_format(datetime);

    assert(ret == ts::DatetimeFormat::MMDD);

    std::cout << ">> Test 49 done" << std::endl;
    return 0;
}


int test50(){
    // TEST 50: testing get_datetime_format() function -> PASS
    // Datetime format MM-DD
    
    std::string datetime = "02-22";
    ts::DatetimeFormat ret = ts::get_datetime_format(datetime);

    assert(ret == ts::DatetimeFormat::MMDD);

    std::cout << ">> Test 50 done" << std::endl;
    return 0;
}


int test51(){
    // TEST 51: testing get_datetime_format() function -> PASS
    // Datetime format MM-DD HH:MM:SS
    
    std::string datetime = "02-22 13:00:00";
    ts::DatetimeFormat ret = ts::get_datetime_format(datetime);

    assert(ret == ts::DatetimeFormat::MMDD_HHMMSS);

    std::cout << ">> Test 51 done" << std::endl;
    return 0;
}


int test52(){
    // TEST 52: testing get_datetime_format() function -> PASS
    // Datetime format YYYY-MM-DD
    
    std::string datetime = "2022-02-22";
    ts::DatetimeFormat ret = ts::get_datetime_format(datetime);

    assert(ret == ts::DatetimeFormat::YYYYMMDD);

    std::cout << ">> Test 52 done" << std::endl;
    return 0;
}


int test53(){
    // TEST 53: testing get_datetime_format() function -> PASS
    // Datetime format YYYY-MM-DD HH:MM:SS
    
    std::string datetime = "2022-02-22 13:00:00";
    ts::DatetimeFormat ret = ts::get_datetime_format(datetime);

    assert(ret == ts::DatetimeFormat::YYYYMMDD_HHMMSS);

    std::cout << ">> Test 53 done" << std::endl;
    return 0;
}


int test54(){
    // TEST 54: testing validate_task_parms() function -> PASS
    // Pass mandatory task parameters only

    time_t time_now = std::time(&time_now) + (TIMEZONE * 60 * 60);

    // Add five minutes in seconds to current time
    time_t time_now_add = time_now + 300;
    
    std::tm* to_struct;
    to_struct = std::gmtime(&time_now_add);

    std::tm struct_time_now_add;
    struct_time_now_add = *to_struct;

    std::string hours = (struct_time_now_add.tm_hour < 10) ? 
                        "0" + std::to_string(struct_time_now_add.tm_hour) :
                        std::to_string(struct_time_now_add.tm_hour);
    std::string minutes = (struct_time_now_add.tm_min < 10) ? 
                          "0" + std::to_string(struct_time_now_add.tm_min) :
                          std::to_string(struct_time_now_add.tm_min);
    std::string seconds = (struct_time_now_add.tm_sec < 10) ? 
                          "0" + std::to_string(struct_time_now_add.tm_sec) :
                          std::to_string(struct_time_now_add.tm_sec);                       
        
    std::string time_now_str =  hours + ":" + minutes + ":" + seconds;

    cl::Config* c = new cl::Config();
    c->add_entry("Name", "Test 54");
    c->add_entry("ScriptFilename", "ls_test.sh");
    c->add_entry("Frequency", "Once");
    c->add_entry("Datetime", time_now_str);

    ts::TaskValidate ret = ts::validate_task_parms(c, "../scripts/");

    assert(ret == ts::TaskValidate::OK);

    delete c;

    std::cout << ">> Test 54 done" << std::endl;
    return 0;
}


int test55(){
    // TEST 55: testing validate_task_parms() function -> PASS
    // Pass mandatory task parameters only

    time_t time_now = std::time(&time_now) + (TIMEZONE * 60 * 60);

    // Add five minutes in seconds to current time
    time_t time_now_add = time_now + 300;
    
    std::tm* to_struct;
    to_struct = std::gmtime(&time_now_add);

    std::tm struct_time_now_add;
    struct_time_now_add = *to_struct;

    std::string hours = (struct_time_now_add.tm_hour < 10) ? 
                        "0" + std::to_string(struct_time_now_add.tm_hour) :
                        std::to_string(struct_time_now_add.tm_hour);
    std::string minutes = (struct_time_now_add.tm_min < 10) ? 
                          "0" + std::to_string(struct_time_now_add.tm_min) :
                          std::to_string(struct_time_now_add.tm_min);
    std::string seconds = (struct_time_now_add.tm_sec < 10) ? 
                          "0" + std::to_string(struct_time_now_add.tm_sec) :
                          std::to_string(struct_time_now_add.tm_sec);                       
        
    std::string time_now_str =  hours + ":" + minutes + ":" + seconds;

    cl::Config* c = new cl::Config();
    c->add_entry("Name", "Test 55");
    c->add_entry("Description", "A short description");
    c->add_entry("ScriptFilename", "ls_test.sh");
    c->add_entry("Frequency", "Once");
    c->add_entry("Datetime", time_now_str);

    ts::TaskValidate ret = ts::validate_task_parms(c, "../scripts/");

    assert(ret == ts::TaskValidate::OK);

    delete c;

    std::cout << ">> Test 55 done" << std::endl;
    return 0;
}


int test56(){
    // TEST 56: testing validate_task_parms() function -> FAIL
    // Missing Name parameter

    cl::Config* c = new cl::Config();
    c->add_entry("Description", "A short description");
    c->add_entry("ScriptFilename", "ls_test.sh");
    c->add_entry("Frequency", "Once");
    c->add_entry("Datetime", "12:00:00");

    ts::TaskValidate ret = ts::validate_task_parms(c, "../scripts/");

    assert(ret == ts::TaskValidate::MISSING_REQUIRED_KEYVALS);

    delete c;

    std::cout << ">> Test 56 done" << std::endl;
    return 0;
}


int test57(){
    // TEST 57: testing validate_task_parms() function -> FAIL
    // Missing Description parameter

    cl::Config* c = new cl::Config();
    c->add_entry("Name", "Test 57");
    c->add_entry("Description", "A short description");
    c->add_entry("Frequency", "Once");
    c->add_entry("Datetime", "12:00:00");

    ts::TaskValidate ret = ts::validate_task_parms(c, "../scripts/");

    assert(ret == ts::TaskValidate::MISSING_REQUIRED_KEYVALS);

    delete c;

    std::cout << ">> Test 57 done" << std::endl;
    return 0;
}


int test58(){
    // TEST 58: testing validate_task_parms() function -> FAIL
    // Missing Frequency parameter

    cl::Config* c = new cl::Config();
    c->add_entry("Name", "Test 58");
    c->add_entry("Description", "A short description");
    c->add_entry("ScriptFilename", "ls_test.sh");
    c->add_entry("Datetime", "12:00:00");

    ts::TaskValidate ret = ts::validate_task_parms(c, "../scripts/");

    assert(ret == ts::TaskValidate::MISSING_REQUIRED_KEYVALS);

    delete c;

    std::cout << ">> Test 58 done" << std::endl;
    return 0;
}


int test59(){
    // TEST 59: testing validate_task_parms() function -> FAIL
    // Missing Datetime parameter

    cl::Config* c = new cl::Config();
    c->add_entry("Name", "Test 59");
    c->add_entry("Description", "A short description");
    c->add_entry("ScriptFilename", "ls_test.sh");
    c->add_entry("Frequency", "Once");

    ts::TaskValidate ret = ts::validate_task_parms(c, "../scripts/");

    assert(ret == ts::TaskValidate::MISSING_REQUIRED_KEYVALS);

    delete c;

    std::cout << ">> Test 59 done" << std::endl;
    return 0;
}


int test60(){
    // TEST 60: testing validate_task_parms() function -> FAIL
    // Script file not found

    cl::Config* c = new cl::Config();
    c->add_entry("Name", "Test 60");
    c->add_entry("Description", "A short description");
    c->add_entry("ScriptFilename", "fakename");
    c->add_entry("Frequency", "Once");
    c->add_entry("Datetime", "12:00:00");

    ts::TaskValidate ret = ts::validate_task_parms(c, "../scripts/");

    assert(ret == ts::TaskValidate::SCRIPT_NOT_FOUND);

    delete c;

    std::cout << ">> Test 60 done" << std::endl;
    return 0;
}


int test61(){
    // TEST 61: testing validate_task_parms() function -> FAIL
    // Bad frequency value

    cl::Config* c = new cl::Config();
    c->add_entry("Name", "Test 61");
    c->add_entry("Description", "A short description");
    c->add_entry("ScriptFilename", "ls_test.sh");
    c->add_entry("Frequency", "Bad value");
    c->add_entry("Datetime", "12:00:00");

    ts::TaskValidate ret = ts::validate_task_parms(c, "../scripts/");

    assert(ret == ts::TaskValidate::BAD_FREQUENCY_VALUE);

    delete c;

    std::cout << ">> Test 61 done" << std::endl;
    return 0;
}


int test62(){
    // TEST 62: testing validate_task_parms() function -> FAIL
    // Pass bad HH:MM:SS datetime value with Frequency = Once

    cl::Config* c = new cl::Config();
    c->add_entry("Name", "Test 62");
    c->add_entry("Description", "A short description");
    c->add_entry("ScriptFilename", "ls_test.sh");
    c->add_entry("Frequency", "Once");
    c->add_entry("Datetime", "12:80:00");

    ts::TaskValidate ret = ts::validate_task_parms(c, "../scripts/");

    assert(ret == ts::TaskValidate::BAD_DATETIME_VALUE);

    delete c;

    std::cout << ">> Test 62 done" << std::endl;
    return 0;
}


int test63(){
    // TEST 63: testing validate_task_parms() function -> FAIL
    // Pass bad MM-DD HH:MM:SS datetime value with Frequency = Once

    cl::Config* c = new cl::Config();
    c->add_entry("Name", "Test 63");
    c->add_entry("Description", "A short description");
    c->add_entry("ScriptFilename", "ls_test.sh");
    c->add_entry("Frequency", "Once");
    c->add_entry("Datetime", "02-61 12:00:00");

    ts::TaskValidate ret = ts::validate_task_parms(c, "../scripts/");

    assert(ret == ts::TaskValidate::BAD_DATETIME_VALUE);

    delete c;

    std::cout << ">> Test 63 done" << std::endl;
    return 0;
}


int test64(){
    // TEST 64: testing validate_task_parms() function -> FAIL
    // Pass bad YYYY-MM-DD HH:MM:SS datetime value with Frequency = Once

    cl::Config* c = new cl::Config();
    c->add_entry("Name", "Test 64");
    c->add_entry("Description", "A short description");
    c->add_entry("ScriptFilename", "ls_test.sh");
    c->add_entry("Frequency", "Once");
    c->add_entry("Datetime", "2022-02-01 62:00:00");

    ts::TaskValidate ret = ts::validate_task_parms(c, "../scripts/");

    assert(ret == ts::TaskValidate::BAD_DATETIME_VALUE);

    delete c;

    std::cout << ">> Test 64 done" << std::endl;
    return 0;
}


int test65(){
    // TEST 65: testing validate_task_parms() function -> FAIL
    // Pass bad WDAY HH:MM:SS datetime value with Frequency = Once

    cl::Config* c = new cl::Config();
    c->add_entry("Name", "Test 65");
    c->add_entry("Description", "A short description");
    c->add_entry("ScriptFilename", "ls_test.sh");
    c->add_entry("Frequency", "Once");
    c->add_entry("Datetime", "Saturdxy 12:00:00");

    ts::TaskValidate ret = ts::validate_task_parms(c, "../scripts/");

    assert(ret == ts::TaskValidate::BAD_DATETIME_VALUE);

    delete c;

    std::cout << ">> Test 65 done" << std::endl;
    return 0;
}


int test66(){
    // TEST 66: testing validate_task_parms() function -> FAIL
    // Pass bad MM-DD datetime value with Frequency = Once

    cl::Config* c = new cl::Config();
    c->add_entry("Name", "Test 66");
    c->add_entry("Description", "A short description");
    c->add_entry("ScriptFilename", "ls_test.sh");
    c->add_entry("Frequency", "Once");
    c->add_entry("Datetime", "02-82");

    ts::TaskValidate ret = ts::validate_task_parms(c, "../scripts/");

    assert(ret == ts::TaskValidate::BAD_DATETIME_VALUE);

    delete c;

    std::cout << ">> Test 66 done" << std::endl;
    return 0;
}


int test67(){
    // TEST 67: testing validate_task_parms() function -> FAIL
    // Pass bad YYYY-MM-DD datetime value with Frequency = Once

    cl::Config* c = new cl::Config();
    c->add_entry("Name", "Test 67");
    c->add_entry("Description", "A short description");
    c->add_entry("ScriptFilename", "ls_test.sh");
    c->add_entry("Frequency", "Once");
    c->add_entry("Datetime", "2022-92-22");

    ts::TaskValidate ret = ts::validate_task_parms(c, "../scripts/");

    assert(ret == ts::TaskValidate::BAD_DATETIME_VALUE);

    delete c;

    std::cout << ">> Test 67 done" << std::endl;
    return 0;
}


int test68(){
    // TEST 68: testing validate_task_parms() function -> FAIL
    // Pass bad datetime value with Frequency = Once

    cl::Config* c = new cl::Config();
    c->add_entry("Name", "Test 68");
    c->add_entry("Description", "A short description");
    c->add_entry("ScriptFilename", "ls_test.sh");
    c->add_entry("Frequency", "Once");
    c->add_entry("Datetime", "Something");

    ts::TaskValidate ret = ts::validate_task_parms(c, "../scripts/");

    assert(ret == ts::TaskValidate::BAD_DATETIME_VALUE);

    delete c;

    std::cout << ">> Test 68 done" << std::endl;
    return 0;
}


int test69(){
    // TEST 69: testing validate_task_parms() function -> FAIL
    // Pass HH:MM:SS datetime value in the past with Frequency = Once

    time_t time_now = std::time(&time_now) + (TIMEZONE * 60 * 60);

    // Add minus one minute in seconds to current time
    time_t time_now_add = time_now + (-60);
    
    std::tm* to_struct;
    to_struct = std::gmtime(&time_now_add);

    std::tm struct_time_now_add;
    struct_time_now_add = *to_struct;

    std::string hours = (struct_time_now_add.tm_hour < 10) ? 
                        "0" + std::to_string(struct_time_now_add.tm_hour) :
                        std::to_string(struct_time_now_add.tm_hour);
    std::string minutes = (struct_time_now_add.tm_min < 10) ? 
                          "0" + std::to_string(struct_time_now_add.tm_min) :
                          std::to_string(struct_time_now_add.tm_min);
    std::string seconds = (struct_time_now_add.tm_sec < 10) ? 
                          "0" + std::to_string(struct_time_now_add.tm_sec) :
                          std::to_string(struct_time_now_add.tm_sec);                       
        
    std::string time_now_str =  hours + ":" + minutes + ":" + seconds;

    cl::Config* c = new cl::Config();
    c->add_entry("Name", "Test 69");
    c->add_entry("Description", "A short description");
    c->add_entry("ScriptFilename", "ls_test.sh");
    c->add_entry("Frequency", "Once");
    c->add_entry("Datetime", time_now_str);

    ts::TaskValidate ret = ts::validate_task_parms(c, "../scripts/");

    assert(ret == ts::TaskValidate::BAD_DATETIME_VALUE);

    delete c;

    std::cout << ">> Test 69 done" << std::endl;
    return 0;
}


int test70(){
    // TEST 70: testing validate_task_parms() function -> PASS
    // Ignored datetime value with Frequency = Hourly

    cl::Config* c = new cl::Config();
    c->add_entry("Name", "Test 70");
    c->add_entry("Description", "A short description");
    c->add_entry("ScriptFilename", "ls_test.sh");
    c->add_entry("Frequency", "Hourly");
    c->add_entry("Datetime", "Any value");

    ts::TaskValidate ret = ts::validate_task_parms(c, "../scripts/");

    assert(ret == ts::TaskValidate::OK);

    delete c;

    std::cout << ">> Test 70 done" << std::endl;
    return 0;
}


int test71(){
    // TEST 71: testing validate_task_parms() function -> FAIL
    // Pass bad HH:MM:SS datetime value with Frequency = Daily

    cl::Config* c = new cl::Config();
    c->add_entry("Name", "Test 71");
    c->add_entry("Description", "A short description");
    c->add_entry("ScriptFilename", "ls_test.sh");
    c->add_entry("Frequency", "Daily");
    c->add_entry("Datetime", "12:90:00");

    ts::TaskValidate ret = ts::validate_task_parms(c, "../scripts/");

    assert(ret == ts::TaskValidate::BAD_DATETIME_VALUE);

    delete c;

    std::cout << ">> Test 71 done" << std::endl;
    return 0;
}


int test72(){
    // TEST 72: testing validate_task_parms() function -> FAIL
    // Pass bad datetime value with Frequency = Daily

    cl::Config* c = new cl::Config();
    c->add_entry("Name", "Test 72");
    c->add_entry("Description", "A short description");
    c->add_entry("ScriptFilename", "ls_test.sh");
    c->add_entry("Frequency", "Daily");
    c->add_entry("Datetime", "Something");

    ts::TaskValidate ret = ts::validate_task_parms(c, "../scripts/");

    assert(ret == ts::TaskValidate::BAD_DATETIME_VALUE);

    delete c;

    std::cout << ">> Test 72 done" << std::endl;
    return 0;
}


int test73(){
    // TEST 73: testing validate_task_parms() function -> FAIL
    // Pass HH:MM:SS datetime value in the past with Frequency = Daily

    time_t time_now = std::time(&time_now) + (TIMEZONE * 60 * 60);

    // Add minus one minute in seconds to current time
    time_t time_now_add = time_now + (-60);
    
    std::tm* to_struct;
    to_struct = std::gmtime(&time_now_add);

    std::tm struct_time_now_add;
    struct_time_now_add = *to_struct;

    std::string hours = (struct_time_now_add.tm_hour < 10) ? 
                        "0" + std::to_string(struct_time_now_add.tm_hour) :
                        std::to_string(struct_time_now_add.tm_hour);
    std::string minutes = (struct_time_now_add.tm_min < 10) ? 
                          "0" + std::to_string(struct_time_now_add.tm_min) :
                          std::to_string(struct_time_now_add.tm_min);
    std::string seconds = (struct_time_now_add.tm_sec < 10) ? 
                          "0" + std::to_string(struct_time_now_add.tm_sec) :
                          std::to_string(struct_time_now_add.tm_sec);                       
        
    std::string time_now_str =  hours + ":" + minutes + ":" + seconds;

    cl::Config* c = new cl::Config();
    c->add_entry("Name", "Test 73");
    c->add_entry("Description", "A short description");
    c->add_entry("ScriptFilename", "ls_test.sh");
    c->add_entry("Frequency", "Daily");
    c->add_entry("Datetime", time_now_str);

    ts::TaskValidate ret = ts::validate_task_parms(c, "../scripts/");

    assert(ret == ts::TaskValidate::BAD_DATETIME_VALUE);

    delete c;

    std::cout << ">> Test 73 done" << std::endl;
    return 0;
}


int test74(){
    // TEST 74: testing validate_task_parms() function -> FAIL
    // Pass bad HH:MM:SS datetime value with Frequency = Weekly

    cl::Config* c = new cl::Config();
    c->add_entry("Name", "Test 74");
    c->add_entry("Description", "A short description");
    c->add_entry("ScriptFilename", "ls_test.sh");
    c->add_entry("Frequency", "Weekly");
    c->add_entry("Datetime", "12:80:00");

    ts::TaskValidate ret = ts::validate_task_parms(c, "../scripts/");

    assert(ret == ts::TaskValidate::BAD_DATETIME_VALUE);

    delete c;

    std::cout << ">> Test 74 done" << std::endl;
    return 0;
}


int test75(){
    // TEST 75: testing validate_task_parms() function -> FAIL
    // Pass bad MM-DD HH:MM:SS datetime value with Frequency = Weekly

    cl::Config* c = new cl::Config();
    c->add_entry("Name", "Test 75");
    c->add_entry("Description", "A short description");
    c->add_entry("ScriptFilename", "ls_test.sh");
    c->add_entry("Frequency", "Weekly");
    c->add_entry("Datetime", "02-61 12:00:00");

    ts::TaskValidate ret = ts::validate_task_parms(c, "../scripts/");

    assert(ret == ts::TaskValidate::BAD_DATETIME_VALUE);

    delete c;

    std::cout << ">> Test 75 done" << std::endl;
    return 0;
}


int test76(){
    // TEST 76: testing validate_task_parms() function -> FAIL
    // Pass bad YYYY-MM-DD HH:MM:SS datetime value with Frequency = Weekly

    cl::Config* c = new cl::Config();
    c->add_entry("Name", "Test 76");
    c->add_entry("Description", "A short description");
    c->add_entry("ScriptFilename", "ls_test.sh");
    c->add_entry("Frequency", "Weekly");
    c->add_entry("Datetime", "2022-02-01 62:00:00");

    ts::TaskValidate ret = ts::validate_task_parms(c, "../scripts/");

    assert(ret == ts::TaskValidate::BAD_DATETIME_VALUE);

    delete c;

    std::cout << ">> Test 76 done" << std::endl;
    return 0;
}


int test77(){
    // TEST 77: testing validate_task_parms() function -> FAIL
    // Pass bad WDAY HH:MM:SS datetime value with Frequency = Weekly

    cl::Config* c = new cl::Config();
    c->add_entry("Name", "Test 77");
    c->add_entry("Description", "A short description");
    c->add_entry("ScriptFilename", "ls_test.sh");
    c->add_entry("Frequency", "Weekly");
    c->add_entry("Datetime", "Saturdxy 12:00:00");

    ts::TaskValidate ret = ts::validate_task_parms(c, "../scripts/");

    assert(ret == ts::TaskValidate::BAD_DATETIME_VALUE);

    delete c;

    std::cout << ">> Test 77 done" << std::endl;
    return 0;
}


int test78(){
    // TEST 78: testing validate_task_parms() function -> FAIL
    // Pass bad MM-DD datetime value with Frequency = Weekly

    cl::Config* c = new cl::Config();
    c->add_entry("Name", "Test 78");
    c->add_entry("Description", "A short description");
    c->add_entry("ScriptFilename", "ls_test.sh");
    c->add_entry("Frequency", "Weekly");
    c->add_entry("Datetime", "02-82");

    ts::TaskValidate ret = ts::validate_task_parms(c, "../scripts/");

    assert(ret == ts::TaskValidate::BAD_DATETIME_VALUE);

    delete c;

    std::cout << ">> Test 78 done" << std::endl;
    return 0;
}


int test79(){
    // TEST 79: testing validate_task_parms() function -> FAIL
    // Pass bad YYYY-MM-DD datetime value with Frequency = Weekly

    cl::Config* c = new cl::Config();
    c->add_entry("Name", "Test 79");
    c->add_entry("Description", "A short description");
    c->add_entry("ScriptFilename", "ls_test.sh");
    c->add_entry("Frequency", "Weekly");
    c->add_entry("Datetime", "2022-92-22");

    ts::TaskValidate ret = ts::validate_task_parms(c, "../scripts/");

    assert(ret == ts::TaskValidate::BAD_DATETIME_VALUE);

    delete c;

    std::cout << ">> Test 79 done" << std::endl;
    return 0;
}


int test80(){
    // TEST 80: testing validate_task_parms() function -> FAIL
    // Pass bad datetime value with Frequency = Weekly

    cl::Config* c = new cl::Config();
    c->add_entry("Name", "Test 80");
    c->add_entry("Description", "A short description");
    c->add_entry("ScriptFilename", "ls_test.sh");
    c->add_entry("Frequency", "Weekly");
    c->add_entry("Datetime", "Something");

    ts::TaskValidate ret = ts::validate_task_parms(c, "../scripts/");

    assert(ret == ts::TaskValidate::BAD_DATETIME_VALUE);

    delete c;

    std::cout << ">> Test 80 done" << std::endl;
    return 0;
}


int test81(){
    // TEST 81: testing validate_task_parms() function -> FAIL
    // Pass HH:MM:SS datetime value in the past with Frequency = Weekly

    time_t time_now = std::time(&time_now) + (TIMEZONE * 60 * 60);

    // Add minus one minute in seconds to current time
    time_t time_now_add = time_now + (-60);
    
    std::tm* to_struct;
    to_struct = std::gmtime(&time_now_add);

    std::tm struct_time_now_add;
    struct_time_now_add = *to_struct;

    std::string hours = (struct_time_now_add.tm_hour < 10) ? 
                        "0" + std::to_string(struct_time_now_add.tm_hour) :
                        std::to_string(struct_time_now_add.tm_hour);
    std::string minutes = (struct_time_now_add.tm_min < 10) ? 
                          "0" + std::to_string(struct_time_now_add.tm_min) :
                          std::to_string(struct_time_now_add.tm_min);
    std::string seconds = (struct_time_now_add.tm_sec < 10) ? 
                          "0" + std::to_string(struct_time_now_add.tm_sec) :
                          std::to_string(struct_time_now_add.tm_sec);                       
        
    std::string time_now_str =  hours + ":" + minutes + ":" + seconds;

    cl::Config* c = new cl::Config();
    c->add_entry("Name", "Test 81");
    c->add_entry("Description", "A short description");
    c->add_entry("ScriptFilename", "ls_test.sh");
    c->add_entry("Frequency", "Weekly");
    c->add_entry("Datetime", time_now_str);

    ts::TaskValidate ret = ts::validate_task_parms(c, "../scripts/");

    assert(ret == ts::TaskValidate::BAD_DATETIME_VALUE);

    delete c;

    std::cout << ">> Test 81 done" << std::endl;
    return 0;
}


int test82(){
    // TEST 74: testing validate_task_parms() function -> FAIL
    // Pass bad HH:MM:SS datetime value with Frequency = Monthly

    cl::Config* c = new cl::Config();
    c->add_entry("Name", "Test 82");
    c->add_entry("Description", "A short description");
    c->add_entry("ScriptFilename", "ls_test.sh");
    c->add_entry("Frequency", "Monthly");
    c->add_entry("Datetime", "12:80:00");

    ts::TaskValidate ret = ts::validate_task_parms(c, "../scripts/");

    assert(ret == ts::TaskValidate::BAD_DATETIME_VALUE);

    delete c;

    std::cout << ">> Test 82 done" << std::endl;
    return 0;
}


int test83(){
    // TEST 83: testing validate_task_parms() function -> FAIL
    // Pass bad MM-DD HH:MM:SS datetime value with Frequency = Monthly

    cl::Config* c = new cl::Config();
    c->add_entry("Name", "Test 83");
    c->add_entry("Description", "A short description");
    c->add_entry("ScriptFilename", "ls_test.sh");
    c->add_entry("Frequency", "Monthly");
    c->add_entry("Datetime", "02-61 12:00:00");

    ts::TaskValidate ret = ts::validate_task_parms(c, "../scripts/");

    assert(ret == ts::TaskValidate::BAD_DATETIME_VALUE);

    delete c;

    std::cout << ">> Test 83 done" << std::endl;
    return 0;
}


int test84(){
    // TEST 84: testing validate_task_parms() function -> FAIL
    // Pass bad YYYY-MM-DD HH:MM:SS datetime value with Frequency = Monthly

    cl::Config* c = new cl::Config();
    c->add_entry("Name", "Test 84");
    c->add_entry("Description", "A short description");
    c->add_entry("ScriptFilename", "ls_test.sh");
    c->add_entry("Frequency", "Monthly");
    c->add_entry("Datetime", "2022-02-01 62:00:00");

    ts::TaskValidate ret = ts::validate_task_parms(c, "../scripts/");

    assert(ret == ts::TaskValidate::BAD_DATETIME_VALUE);

    delete c;

    std::cout << ">> Test 84 done" << std::endl;
    return 0;
}


int test85(){
    // TEST 85: testing validate_task_parms() function -> FAIL
    // Pass bad WDAY HH:MM:SS datetime value with Frequency = Monthly

    cl::Config* c = new cl::Config();
    c->add_entry("Name", "Test 85");
    c->add_entry("Description", "A short description");
    c->add_entry("ScriptFilename", "ls_test.sh");
    c->add_entry("Frequency", "Monthly");
    c->add_entry("Datetime", "Saturdxy 12:00:00");

    ts::TaskValidate ret = ts::validate_task_parms(c, "../scripts/");

    assert(ret == ts::TaskValidate::BAD_DATETIME_VALUE);

    delete c;

    std::cout << ">> Test 85 done" << std::endl;
    return 0;
}


int test86(){
    // TEST 86: testing validate_task_parms() function -> FAIL
    // Pass bad MM-DD datetime value with Frequency = Monthly

    cl::Config* c = new cl::Config();
    c->add_entry("Name", "Test 86");
    c->add_entry("Description", "A short description");
    c->add_entry("ScriptFilename", "ls_test.sh");
    c->add_entry("Frequency", "Monthly");
    c->add_entry("Datetime", "02-82");

    ts::TaskValidate ret = ts::validate_task_parms(c, "../scripts/");

    assert(ret == ts::TaskValidate::BAD_DATETIME_VALUE);

    delete c;

    std::cout << ">> Test 86 done" << std::endl;
    return 0;
}


int test87(){
    // TEST 87: testing validate_task_parms() function -> FAIL
    // Pass bad YYYY-MM-DD datetime value with Frequency = Monthly

    cl::Config* c = new cl::Config();
    c->add_entry("Name", "Test 87");
    c->add_entry("Description", "A short description");
    c->add_entry("ScriptFilename", "ls_test.sh");
    c->add_entry("Frequency", "Monthly");
    c->add_entry("Datetime", "2022-92-22");

    ts::TaskValidate ret = ts::validate_task_parms(c, "../scripts/");

    assert(ret == ts::TaskValidate::BAD_DATETIME_VALUE);

    delete c;

    std::cout << ">> Test 87 done" << std::endl;
    return 0;
}


int test88(){
    // TEST 88: testing validate_task_parms() function -> FAIL
    // Pass bad datetime value with Frequency = Monthly

    cl::Config* c = new cl::Config();
    c->add_entry("Name", "Test 88");
    c->add_entry("Description", "A short description");
    c->add_entry("ScriptFilename", "ls_test.sh");
    c->add_entry("Frequency", "Monthly");
    c->add_entry("Datetime", "Something");

    ts::TaskValidate ret = ts::validate_task_parms(c, "../scripts/");

    assert(ret == ts::TaskValidate::BAD_DATETIME_VALUE);

    delete c;

    std::cout << ">> Test 88 done" << std::endl;
    return 0;
}


int test89(){
    // TEST 89: testing validate_task_parms() function -> FAIL
    // Pass HH:MM:SS datetime value in the past with Frequency = Monthly

    time_t time_now = std::time(&time_now) + (TIMEZONE * 60 * 60);

    // Add minus one minute in seconds to current time
    time_t time_now_add = time_now + (-60);
    
    std::tm* to_struct;
    to_struct = std::gmtime(&time_now_add);

    std::tm struct_time_now_add;
    struct_time_now_add = *to_struct;

    std::string hours = (struct_time_now_add.tm_hour < 10) ? 
                        "0" + std::to_string(struct_time_now_add.tm_hour) :
                        std::to_string(struct_time_now_add.tm_hour);
    std::string minutes = (struct_time_now_add.tm_min < 10) ? 
                          "0" + std::to_string(struct_time_now_add.tm_min) :
                          std::to_string(struct_time_now_add.tm_min);
    std::string seconds = (struct_time_now_add.tm_sec < 10) ? 
                          "0" + std::to_string(struct_time_now_add.tm_sec) :
                          std::to_string(struct_time_now_add.tm_sec);                       
        
    std::string time_now_str =  hours + ":" + minutes + ":" + seconds;

    cl::Config* c = new cl::Config();
    c->add_entry("Name", "Test 89");
    c->add_entry("Description", "A short description");
    c->add_entry("ScriptFilename", "ls_test.sh");
    c->add_entry("Frequency", "Monthly");
    c->add_entry("Datetime", time_now_str);

    ts::TaskValidate ret = ts::validate_task_parms(c, "../scripts/");

    assert(ret == ts::TaskValidate::BAD_DATETIME_VALUE);

    delete c;

    std::cout << ">> Test 89 done" << std::endl;
    return 0;
}


int test90(){
    // TEST 90: testing validate_task_parms() function -> FAIL
    // Pass bad MM-DD HH:MM:SS datetime value with Frequency = Yearly

    cl::Config* c = new cl::Config();
    c->add_entry("Name", "Test 90");
    c->add_entry("Description", "A short description");
    c->add_entry("ScriptFilename", "ls_test.sh");
    c->add_entry("Frequency", "Yearly");
    c->add_entry("Datetime", "02-61 12:00:00");

    ts::TaskValidate ret = ts::validate_task_parms(c, "../scripts/");

    assert(ret == ts::TaskValidate::BAD_DATETIME_VALUE);

    delete c;

    std::cout << ">> Test 90 done" << std::endl;
    return 0;
}


int test91(){
    // TEST 91: testing validate_task_parms() function -> FAIL
    // Pass bad YYYY-MM-DD HH:MM:SS datetime value with Frequency = Yearly

    cl::Config* c = new cl::Config();
    c->add_entry("Name", "Test 91");
    c->add_entry("Description", "A short description");
    c->add_entry("ScriptFilename", "ls_test.sh");
    c->add_entry("Frequency", "Yearly");
    c->add_entry("Datetime", "2022-02-01 62:00:00");

    ts::TaskValidate ret = ts::validate_task_parms(c, "../scripts/");

    assert(ret == ts::TaskValidate::BAD_DATETIME_VALUE);

    delete c;

    std::cout << ">> Test 91 done" << std::endl;
    return 0;
}


int test92(){
    // TEST 92: testing validate_task_parms() function -> FAIL
    // Pass bad MM-DD datetime value with Frequency = Yearly

    cl::Config* c = new cl::Config();
    c->add_entry("Name", "Test 92");
    c->add_entry("Description", "A short description");
    c->add_entry("ScriptFilename", "ls_test.sh");
    c->add_entry("Frequency", "Yearly");
    c->add_entry("Datetime", "02-82");

    ts::TaskValidate ret = ts::validate_task_parms(c, "../scripts/");

    assert(ret == ts::TaskValidate::BAD_DATETIME_VALUE);

    delete c;

    std::cout << ">> Test 92 done" << std::endl;
    return 0;
}


int test93(){
    // TEST 93: testing validate_task_parms() function -> FAIL
    // Pass bad YYYY-MM-DD datetime value with Frequency = Yearly

    cl::Config* c = new cl::Config();
    c->add_entry("Name", "Test 93");
    c->add_entry("Description", "A short description");
    c->add_entry("ScriptFilename", "ls_test.sh");
    c->add_entry("Frequency", "Yearly");
    c->add_entry("Datetime", "2022-92-22");

    ts::TaskValidate ret = ts::validate_task_parms(c, "../scripts/");

    assert(ret == ts::TaskValidate::BAD_DATETIME_VALUE);

    delete c;

    std::cout << ">> Test 93 done" << std::endl;
    return 0;
}


int test94(){
    // TEST 94: testing validate_task_parms() function -> FAIL
    // Pass bad datetime value with Frequency = Yearly

    cl::Config* c = new cl::Config();
    c->add_entry("Name", "Test 94");
    c->add_entry("Description", "A short description");
    c->add_entry("ScriptFilename", "ls_test.sh");
    c->add_entry("Frequency", "Yearly");
    c->add_entry("Datetime", "Something");

    ts::TaskValidate ret = ts::validate_task_parms(c, "../scripts/");

    assert(ret == ts::TaskValidate::BAD_DATETIME_VALUE);

    delete c;

    std::cout << ">> Test 94 done" << std::endl;
    return 0;
}


int test95(){
    // TEST 95: testing validate_task_parms() function -> FAIL
    // Pass HH:MM:SS datetime value in the past with Frequency = Yearly

    time_t time_now = std::time(&time_now) + (TIMEZONE * 60 * 60);

    // Add minus one minute in seconds to current time
    time_t time_now_add = time_now + (-60);
    
    std::tm* to_struct;
    to_struct = std::gmtime(&time_now_add);

    std::tm struct_time_now_add;
    struct_time_now_add = *to_struct;

    std::string hours = (struct_time_now_add.tm_hour < 10) ? 
                        "0" + std::to_string(struct_time_now_add.tm_hour) :
                        std::to_string(struct_time_now_add.tm_hour);
    std::string minutes = (struct_time_now_add.tm_min < 10) ? 
                          "0" + std::to_string(struct_time_now_add.tm_min) :
                          std::to_string(struct_time_now_add.tm_min);
    std::string seconds = (struct_time_now_add.tm_sec < 10) ? 
                          "0" + std::to_string(struct_time_now_add.tm_sec) :
                          std::to_string(struct_time_now_add.tm_sec);                       
        
    std::string time_now_str =  hours + ":" + minutes + ":" + seconds;

    cl::Config* c = new cl::Config();
    c->add_entry("Name", "Test 95");
    c->add_entry("Description", "A short description");
    c->add_entry("ScriptFilename", "ls_test.sh");
    c->add_entry("Frequency", "Yearly");
    c->add_entry("Datetime", time_now_str);

    ts::TaskValidate ret = ts::validate_task_parms(c, "../scripts/");

    assert(ret == ts::TaskValidate::BAD_DATETIME_VALUE);

    delete c;

    std::cout << ">> Test 95 done" << std::endl;
    return 0;
}


int test96(){
    // TEST 96: testing Task::update_execution_datetime() 
    // Frequency: Hourly
    // Datetime format: n/a

    time_t time_now = std::time(&time_now) + (TIMEZONE * 60 * 60);

    time_t time_now_add;
    std::tm* to_struct;
    std::tm struct_time_now_add;
    std::string years;
    std::string months;
    std::string days;
    std::string hours;
    std::string minutes;
    std::string seconds;
    std::string datetime_str;

    // Add two hours in seconds to current time
    time_now_add = time_now + (2 * 3600);
    to_struct = std::gmtime(&time_now_add);
    struct_time_now_add = *to_struct;

    years = std::to_string(1900 + struct_time_now_add.tm_year);
    months = (struct_time_now_add.tm_mon < 10) ? 
                         "0" + std::to_string(struct_time_now_add.tm_mon) :
                         std::to_string(struct_time_now_add.tm_mon);  
    days = (struct_time_now_add.tm_mday < 10) ? 
                       "0" + std::to_string(struct_time_now_add.tm_mday) :
                       std::to_string(struct_time_now_add.tm_mday);
    hours = (struct_time_now_add.tm_hour < 10) ? 
                        "0" + std::to_string(struct_time_now_add.tm_hour) :
                        std::to_string(struct_time_now_add.tm_hour);
    minutes = (struct_time_now_add.tm_min < 10) ? 
                          "0" + std::to_string(struct_time_now_add.tm_min) :
                          std::to_string(struct_time_now_add.tm_min);
    seconds = (struct_time_now_add.tm_sec < 10) ? 
                          "0" + std::to_string(struct_time_now_add.tm_sec) :
                          std::to_string(struct_time_now_add.tm_sec);
    datetime_str =  hours + ":" + minutes + ":" + seconds;

    std::string t_name = "Task Name";
    std::string t_description = "A short description for this task";
    std::string t_script_name = "cat_test.sh";
    std::string t_frequency = "Hourly";

    ts::Task* t = new ts::Task(t_name, t_description, t_script_name, t_frequency);
    
    t->update_execution_datetime();
    std::string ret = t->get_execution_datetime_fmt();
    assert(ret.find(datetime_str) != std::string::npos);
    delete t;

    std::cout << ">> Test 96 done" << std::endl;
    return 0;
}


int test97(){
    // TEST 97: testing Task::update_execution_datetime() 
    // Frequency: Daily
    // Datetime format: HH:MM:SS

    time_t time_now = std::time(&time_now) + (TIMEZONE * 60 * 60);

    time_t time_now_add;
    std::tm* to_struct;
    std::tm struct_time_now_add;
    std::string years;
    std::string months;
    std::string days;
    std::string hours;
    std::string minutes;
    std::string seconds;
    std::string datetime_str;

    // Add one hour in seconds to current time
    time_now_add = time_now + (1 * 3600);
    to_struct = std::gmtime(&time_now_add);
    struct_time_now_add = *to_struct;
    
    years = std::to_string(1900 + struct_time_now_add.tm_year);
    months = (struct_time_now_add.tm_mon < 10) ? 
                         "0" + std::to_string(struct_time_now_add.tm_mon) :
                         std::to_string(struct_time_now_add.tm_mon);  
    days = (struct_time_now_add.tm_mday < 10) ? 
                       "0" + std::to_string(struct_time_now_add.tm_mday) :
                       std::to_string(struct_time_now_add.tm_mday);
    hours = (struct_time_now_add.tm_hour < 10) ? 
                        "0" + std::to_string(struct_time_now_add.tm_hour) :
                        std::to_string(struct_time_now_add.tm_hour);
    minutes = (struct_time_now_add.tm_min < 10) ? 
                          "0" + std::to_string(struct_time_now_add.tm_min) :
                          std::to_string(struct_time_now_add.tm_min);
    seconds = (struct_time_now_add.tm_sec < 10) ? 
                          "0" + std::to_string(struct_time_now_add.tm_sec) :
                          std::to_string(struct_time_now_add.tm_sec);
    datetime_str =  hours + ":" + minutes + ":" + seconds;

    std::string t_name = "Task Name";
    std::string t_description = "A short description for this task";
    std::string t_script_name = "cat_test.sh";
    std::string t_frequency = "Daily";
    std::string t_datetime = datetime_str;

    ts::Task* t = new ts::Task(t_name, t_description, t_script_name, t_frequency, t_datetime);
    
    t->update_execution_datetime();
    std::string ret = t->get_execution_datetime_fmt();

    // Add one day and one hour in seconds to current time after calling update_execution_datetime()
    time_now_add = time_now + 90000;
    to_struct = std::gmtime(&time_now_add);
    struct_time_now_add = *to_struct;

    years = std::to_string(1900 + struct_time_now_add.tm_year);      
    switch (struct_time_now_add.tm_mon)
    {
    case 0:
        months = "Jan";
        break;
    case 1:
        months = "Feb";
        break;
    case 2:
        months = "Mar";
        break;
    case 3:
        months = "Apr";
        break;
    case 4:
        months = "May";
        break;
    case 5:
        months = "Jun";
        break;
    case 6:
        months = "Jul";
        break;
    case 7:
        months = "Aug";
        break;
    case 8:
        months = "Sep";
        break;
    case 9:
        months = "Oct";
        break;
    case 10:
        months = "Nov";
        break;
    case 11:
        months = "Dec";
        break;
    default:
        months = "";
        break;
    }
    days = (struct_time_now_add.tm_mday < 10) ? 
                       "0" + std::to_string(struct_time_now_add.tm_mday) :
                       std::to_string(struct_time_now_add.tm_mday);
    hours = (struct_time_now_add.tm_hour < 10) ? 
                        "0" + std::to_string(struct_time_now_add.tm_hour) :
                        std::to_string(struct_time_now_add.tm_hour);
    minutes = (struct_time_now_add.tm_min < 10) ? 
                          "0" + std::to_string(struct_time_now_add.tm_min) :
                          std::to_string(struct_time_now_add.tm_min);
    seconds = (struct_time_now_add.tm_sec < 10) ? 
                          "0" + std::to_string(struct_time_now_add.tm_sec) :
                          std::to_string(struct_time_now_add.tm_sec);
    datetime_str =  months + " " + days + " " + hours + ":" + minutes + ":" + seconds + " " + years;

    assert(ret.find(datetime_str) != std::string::npos);
    delete t;

    std::cout << ">> Test 97 done" << std::endl;
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
    bool t27     = false;
    bool t28     = false;
    bool t29     = false;
    bool t30     = false;
    bool t31     = false;
    bool t32     = false;
    bool t33     = false;
    bool t34     = false;
    bool t35     = false;
    bool t36     = false;
    bool t37     = false;
    bool t38     = false;
    bool t39     = false;
    bool t40     = false;
    bool t41     = false;
    bool t42     = false;
    bool t43     = false;
    bool t44     = false;
    bool t45     = false;
    bool t46     = false;
    bool t47     = false;
    bool t48     = false;
    bool t49     = false;
    bool t50     = false;
    bool t51     = false;
    bool t52     = false;
    bool t53     = false;
    bool t54     = false;
    bool t55     = false;
    bool t56     = false;
    bool t57     = false;
    bool t58     = false;
    bool t59     = false;
    bool t60     = false;
    bool t61     = false;
    bool t62     = false;
    bool t63     = false;
    bool t64     = false;
    bool t65     = false;
    bool t66     = false;
    bool t67     = false;
    bool t68     = false;
    bool t69     = false;
    bool t70     = false;
    bool t71     = false;
    bool t72     = false;
    bool t73     = false;
    bool t74     = false;
    bool t75     = false;
    bool t76     = false;
    bool t77     = false;
    bool t78     = false;
    bool t79     = false;
    bool t80     = false;
    bool t81     = false;
    bool t82     = false;
    bool t83     = false;
    bool t84     = false;
    bool t85     = false;
    bool t86     = false;
    bool t87     = false;
    bool t88     = false;
    bool t89     = false;
    bool t90     = false;
    bool t91     = false;
    bool t92     = false;
    bool t93     = false;
    bool t94     = false;
    bool t95     = false;
    bool t96     = true;
    bool t97     = true;

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
    if(t27 || all){
        test27();
    }
    if(t28 || all){
        test28();
    }
    if(t29 || all){
        test29();
    }
    if(t30 || all){
        test30();
    }
    if(t31 || all){
        test31();
    }
    if(t32 || all){
        test32();
    }
    if(t33 || all){
        test33();
    }
    if(t34 || all){
        test34();
    }
    if(t35 || all){
        test35();
    }
    if(t36 || all){
        test36();
    }
    if(t37 || all){
        test37();
    }
    if(t38 || all){
        test38();
    }
    if(t39 || all){
        test39();
    }
    if(t40 || all){
        test40();
    }
    if(t41 || all){
        test41();
    }
    if(t42 || all){
        test42();
    }
    if(t43 || all){
        test43();
    }
    if(t44 || all){
        test44();
    }
    if(t45 || all){
        test45();
    }
    if(t46 || all){
        test46();
    }
    if(t47 || all){
        test47();
    }
    if(t48 || all){
        test48();
    }
    if(t49 || all){
        test49();
    }
    if(t50 || all){
        test50();
    }
    if(t51 || all){
        test51();
    }
    if(t52 || all){
        test52();
    }
    if(t53 || all){
        test53();
    }
    if(t54 || all){
        test54();
    }
    if(t55 || all){
        test55();
    }
    if(t56 || all){
        test56();
    }
    if(t57 || all){
        test57();
    }
    if(t58 || all){
        test58();
    }
    if(t59 || all){
        test59();
    }
    if(t60 || all){
        test60();
    }
    if(t61 || all){
        test61();
    }
    if(t62 || all){
        test62();
    }
    if(t63 || all){
        test63();
    }
    if(t64 || all){
        test64();
    }
    if(t65 || all){
        test65();
    }
    if(t66 || all){
        test66();
    }
    if(t67 || all){
        test67();
    }
    if(t68 || all){
        test68();
    }
    if(t69 || all){
        test69();
    }
    if(t70 || all){
        test70();
    }
    if(t71 || all){
        test71();
    }
    if(t72 || all){
        test72();
    }
    if(t73 || all){
        test73();
    }
    if(t74 || all){
        test74();
    }
    if(t75 || all){
        test75();
    }
    if(t76 || all){
        test76();
    }
    if(t77 || all){
        test77();
    }
    if(t78 || all){
        test78();
    }
    if(t79 || all){
        test79();
    }
    if(t80 || all){
        test80();
    }
    if(t81 || all){
        test81();
    }
    if(t82 || all){
        test82();
    }
    if(t83 || all){
        test83();
    }
    if(t84 || all){
        test84();
    }
    if(t85 || all){
        test85();
    }
    if(t86 || all){
        test86();
    }
    if(t87 || all){
        test87();
    }
    if(t88 || all){
        test88();
    }
    if(t89 || all){
        test89();
    }
    if(t90 || all){
        test90();
    }
    if(t91 || all){
        test91();
    }
    if(t92 || all){
        test92();
    }
    if(t93 || all){
        test93();
    }
    if(t94 || all){
        test94();
    }
    if(t95 || all){
        test95();
    }
    if(t96 || all){
        test96();
    }
    if(t97 || all){
        test97();
    }

    return 0;
}
