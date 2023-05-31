#include <assert.h>
#include <iostream>

#include "../src/Task.hpp"
#include "../src/Scheduler.hpp"

ts::Scheduler* ts::Scheduler::scheduler_ptr = nullptr;

int test1(){
    // TEST 1: testing method get_creation_datetime()

    time_t time_now = std::time(&time_now);

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
    time_t ret_creation_datetime;
    std::string ret_creation_datetime_fmt;
    std::string ret_execution_datetime_fmt;

    // Add 5 seconds to current time
    time_now_add = time_now + 5;
    to_struct = std::gmtime(&time_now_add);
    struct_time_now_add = *to_struct;
    
    years = std::to_string(1900 + struct_time_now_add.tm_year);
    months = (struct_time_now_add.tm_mon + 1 < 10) ? 
              "0" + std::to_string(struct_time_now_add.tm_mon + 1) :
              std::to_string(struct_time_now_add.tm_mon + 1);  
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
    // HH:MM:SS format
    datetime_str = hours + ":" + minutes + ":" + seconds;

    std::string t_name = "Task Name";
    std::string t_description = "A short description for this task";
    std::string t_script_name = "cat_test.sh";
    std::string t_frequency = "Monthly";
    std::string t_input_execution_datetime = datetime_str; // HH:MM:SS format
    std::string t_config_filename = "config.cl";

    ts::Task* t = new ts::Task(t_name, t_description, t_script_name, t_frequency, t_input_execution_datetime, t_config_filename);

    ret_creation_datetime = t->get_creation_datetime(false);
    assert(time_now == ret_creation_datetime);

    delete t;

    std::cout << ">> Task_methods: Test 1 done" << std::endl;
    return 0;
}


int test2(){
    // TEST 2: testing method get_execution_datetime()

    time_t time_now = std::time(&time_now);

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
    std::string ret_creation_datetime_fmt;
    time_t ret_execution_datetime;
    std::string ret_execution_datetime_fmt;

    // Add 5 seconds to current time
    time_now_add = time_now + 5;
    to_struct = std::gmtime(&time_now_add);
    struct_time_now_add = *to_struct;
    
    years = std::to_string(1900 + struct_time_now_add.tm_year);
    months = (struct_time_now_add.tm_mon + 1 < 10) ? 
              "0" + std::to_string(struct_time_now_add.tm_mon + 1) :
              std::to_string(struct_time_now_add.tm_mon + 1);  
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
    // HH:MM:SS format
    datetime_str = hours + ":" + minutes + ":" + seconds;

    std::string t_name = "Task Name";
    std::string t_description = "A short description for this task";
    std::string t_script_name = "cat_test.sh";
    std::string t_frequency = "Monthly";
    std::string t_input_execution_datetime = datetime_str; // HH:MM:SS format
    std::string t_config_filename = "config.cl";

    ts::Task* t = new ts::Task(t_name, t_description, t_script_name, t_frequency, t_input_execution_datetime, t_config_filename);

    ret_execution_datetime = t->get_execution_datetime(false);
    assert(time_now_add == ret_execution_datetime);

    delete t;

    std::cout << ">> Task_methods: Test 2 done" << std::endl;
    return 0;
}


int test3(){
    // TEST 3: testing methods get_creation_datetime_fmt() 

    time_t time_now = std::time(&time_now);

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
    std::string ret_creation_datetime_fmt;
    std::string ret_execution_datetime_fmt;

    // Add 5 seconds to current time
    time_now_add = time_now + 5;
    to_struct = std::gmtime(&time_now_add);
    struct_time_now_add = *to_struct;
    
    years = std::to_string(1900 + struct_time_now_add.tm_year);
    months = (struct_time_now_add.tm_mon + 1 < 10) ? 
              "0" + std::to_string(struct_time_now_add.tm_mon + 1) :
              std::to_string(struct_time_now_add.tm_mon + 1);  
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
    // HH:MM:SS format
    datetime_str = hours + ":" + minutes + ":" + seconds;

    std::string t_name = "Task Name";
    std::string t_description = "A short description for this task";
    std::string t_script_name = "cat_test.sh";
    std::string t_frequency = "Monthly";
    std::string t_input_execution_datetime = datetime_str; // HH:MM:SS format
    std::string t_config_filename = "config.cl";

    ts::Task* t = new ts::Task(t_name, t_description, t_script_name, t_frequency, t_input_execution_datetime, t_config_filename);

    ret_creation_datetime_fmt = t->get_creation_datetime_fmt();
    // Add timezone offset to current time
    time_now_add = time_now + (TIMEZONE * 60 * 60);
    to_struct = std::gmtime(&time_now_add);
    struct_time_now_add = *to_struct;
    
    years = std::to_string(1900 + struct_time_now_add.tm_year);
    switch (struct_time_now_add.tm_mon)
    {
    case JANUARY:
        months = "Jan";
        break;
    case FEBRUARY:
        months = "Feb";
        break;
    case MARCH:
        months = "Mar";
        break;
    case APRIL:
        months = "Apr";
        break;
    case MAY:
        months = "May";
        break;
    case JUNE:
        months = "Jun";
        break;
    case JULY:
        months = "Jul";
        break;
    case AUGUST:
        months = "Aug";
        break;
    case SEPTEMBER:
        months = "Sep";
        break;
    case OCTOBER:
        months = "Oct";
        break;
    case NOVEMBER:
        months = "Nov";
        break;
    case DECEMBER:
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

    assert(ret_creation_datetime_fmt.find(datetime_str) != std::string::npos);

    delete t;

    std::cout << ">> Task_methods: Test 3 done" << std::endl;
    return 0;
}


int test4(){
    // TEST 4: testing methods get_execution_datetime_fmt() 

    time_t time_now = std::time(&time_now);

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
    std::string ret_creation_datetime_fmt;
    std::string ret_execution_datetime_fmt;

    // Add 5 seconds to current time
    time_now_add = time_now + 5;
    to_struct = std::gmtime(&time_now_add);
    struct_time_now_add = *to_struct;
    
    years = std::to_string(1900 + struct_time_now_add.tm_year);
    months = (struct_time_now_add.tm_mon + 1 < 10) ? 
              "0" + std::to_string(struct_time_now_add.tm_mon + 1) :
              std::to_string(struct_time_now_add.tm_mon + 1);  
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
    // HH:MM:SS format
    datetime_str = hours + ":" + minutes + ":" + seconds;

    std::string t_name = "Task Name";
    std::string t_description = "A short description for this task";
    std::string t_script_name = "cat_test.sh";
    std::string t_frequency = "Monthly";
    std::string t_input_execution_datetime = datetime_str; // HH:MM:SS format
    std::string t_config_filename = "config.cl";

    ts::Task* t = new ts::Task(t_name, t_description, t_script_name, t_frequency, t_input_execution_datetime, t_config_filename);

    ret_execution_datetime_fmt = t->get_execution_datetime_fmt();
    // Add 5 seconds and timezone offset to current time
    time_now_add = time_now + 5 + (TIMEZONE * 60 * 60);
    to_struct = std::gmtime(&time_now_add);
    struct_time_now_add = *to_struct;
    
    years = std::to_string(1900 + struct_time_now_add.tm_year);
    switch (struct_time_now_add.tm_mon)
    {
    case JANUARY:
        months = "Jan";
        break;
    case FEBRUARY:
        months = "Feb";
        break;
    case MARCH:
        months = "Mar";
        break;
    case APRIL:
        months = "Apr";
        break;
    case MAY:
        months = "May";
        break;
    case JUNE:
        months = "Jun";
        break;
    case JULY:
        months = "Jul";
        break;
    case AUGUST:
        months = "Aug";
        break;
    case SEPTEMBER:
        months = "Sep";
        break;
    case OCTOBER:
        months = "Oct";
        break;
    case NOVEMBER:
        months = "Nov";
        break;
    case DECEMBER:
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
    
    assert(ret_execution_datetime_fmt.find(datetime_str) != std::string::npos);

    delete t;

    std::cout << ">> Task_methods: Test 4 done" << std::endl;
    return 0;
}


int test5(){
    // TEST 5: testing methods get_execution_datetime_format_attr()

    time_t time_now = std::time(&time_now);

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
    std::string ret_creation_datetime_fmt;
    std::string ret_execution_datetime_fmt;
    ts::DatetimeFormat ret_execution_datetime_format_attr;

    // Add 5 seconds to current time
    time_now_add = time_now + 5;
    to_struct = std::gmtime(&time_now_add);
    struct_time_now_add = *to_struct;
    
    years = std::to_string(1900 + struct_time_now_add.tm_year);
    months = (struct_time_now_add.tm_mon + 1 < 10) ? 
              "0" + std::to_string(struct_time_now_add.tm_mon + 1) :
              std::to_string(struct_time_now_add.tm_mon + 1);  
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
    // HH:MM:SS format
    datetime_str = hours + ":" + minutes + ":" + seconds;

    std::string t_name = "Task Name";
    std::string t_description = "A short description for this task";
    std::string t_script_name = "cat_test.sh";
    std::string t_frequency = "Monthly";
    std::string t_input_execution_datetime = datetime_str; // HH:MM:SS format
    std::string t_config_filename = "config.cl";

    ts::Task* t = new ts::Task(t_name, t_description, t_script_name, t_frequency, t_input_execution_datetime, t_config_filename);

    ret_execution_datetime_format_attr = t->get_execution_datetime_format_attr();
    assert(ret_execution_datetime_format_attr == ts::DatetimeFormat::HHMMSS);

    delete t;

    std::cout << ">> Task_methods: Test 5 done" << std::endl;
    return 0;
}


int test6(){
    // TEST 6: testing methods 
    // set_id()
    // get_id()
    // set_status()
    // get_status()

    std::string t_name = "Task Name";
    std::string t_description = "A short description for this task";
    std::string t_script_name = "scripts/cat_test.sh";
    std::string t_frequency = "Hourly";
    std::string t_input_execution_datetime = "12:00:00";
    std::string t_config_filename = "config.cl";

    ts::Task* t = new ts::Task(t_name, t_description, t_script_name, t_frequency, t_input_execution_datetime, t_config_filename);
    
    t->set_id(12345);
    assert(t->get_id() == 12345);

    t->set_status(ts::TaskStatus::QUEUED);
    assert(t->get_status() == ts::TaskStatus::QUEUED);

    delete t;

    std::cout << ">> Task_methods: Test 6 done" << std::endl;
    return 0;
}


int test7(){
    // TEST 7: testing run_task() and get_output() methods -> PASS

    std::string t_name = "Task Name";
    std::string t_description = "A short description for this task";
    std::string t_script_name = "cat_test.sh";
    std::string t_frequency = "Hourly";
    std::string t_input_execution_datetime = "12:00:00";
    std::string t_config_filename = "config.cl";

    ts::Task* t = new ts::Task(t_name, t_description, t_script_name, t_frequency, t_input_execution_datetime, t_config_filename);
    
    t->run_task();

    assert(t->get_output() == "ls -l");

    delete t;

    std::cout << ">> Task_methods: Test 7 done" << std::endl;
    return 0;
}


int test8(){
    // TEST 8: testing method get_config_filename()

    std::string t_name = "Task Name";
    std::string t_description = "A short description for this task";
    std::string t_script_name = "scripts/cat_test.sh";
    std::string t_frequency = "Hourly";
    std::string t_input_execution_datetime = "12:00:00";
    std::string t_config_filename = "config.cl";

    ts::Task* t = new ts::Task(t_name, t_description, t_script_name, t_frequency, t_input_execution_datetime, t_config_filename);
    
    assert(t->get_config_filename() == t_config_filename);

    delete t;

    std::cout << ">> Task_methods: Test 8 done" << std::endl;
    return 0;
}

int main(){
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
    test8();
}