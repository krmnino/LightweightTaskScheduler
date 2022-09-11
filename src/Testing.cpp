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

    return 0;
}
