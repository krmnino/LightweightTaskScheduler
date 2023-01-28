#include <assert.h>
#include <iostream>
#include <filesystem>
#include <cstdio>

#include "../src/Task.hpp"
#include "../src/Scheduler.hpp"
#include "../src/CommandLine.hpp"

ts::Scheduler* ts::Scheduler::scheduler_ptr = nullptr;
ts::CommandLine* ts::CommandLine::command_line_ptr = nullptr;

int test1(ts::Scheduler* s){
    // TEST 1: generate new task to be executed in the next second. Check for the output after it runs.
    // Task Frequency: Once

    time_t time_now;
    time_t time_now_add;
    std::tm* to_struct;
    std::tm struct_time_now_add;
    std::string years;
    std::string months;
    std::string months_str;
    std::string days;
    std::string wday_full;
    std::string wday_abbr;
    std::string hours;
    std::string minutes;
    std::string seconds;
    std::string verify_datetime_str;
    std::string ret_datetime_str;
    std::string task_path_fn;
    std::string task_filename;
    std::string t_name;
    cl::Config* c;

    time_now = std::time(&time_now);

    // Add one second from current time
    time_now_add = time_now + 1;
    
    // time_t to std::tm*
    to_struct = std::gmtime(&time_now_add);

    // std::tm* to std::tm
    struct_time_now_add = *to_struct;

    years = std::to_string(1900 + struct_time_now_add.tm_year);
    months = (struct_time_now_add.tm_mon + 1 < 10) ? 
              "0" + std::to_string(struct_time_now_add.tm_mon + 1) :
              std::to_string(struct_time_now_add.tm_mon + 1);
    switch (struct_time_now_add.tm_mon)
    {
    case JANUARY:
        months_str = "Jan";
        break;
    case FEBRUARY:
        months_str = "Feb";
        break;
    case MARCH:
        months_str = "Mar";
        break;
    case APRIL:
        months_str = "Apr";
        break;
    case MAY:
        months_str = "May";
        break;
    case JUNE:
        months_str = "Jun";
        break;
    case JULY:
        months_str = "Jul";
        break;
    case AUGUST:
        months_str = "Aug";
        break;
    case SEPTEMBER:
        months_str = "Sep";
        break;
    case OCTOBER:
        months_str = "Oct";
        break;
    case NOVEMBER:
        months_str = "Nov";
        break;
    case DECEMBER:
        months_str = "Dec";
        break;
    default:
        months_str = "";
        break;
    }  
    days = (struct_time_now_add.tm_mday < 10) ? 
            "0" + std::to_string(struct_time_now_add.tm_mday) :
            std::to_string(struct_time_now_add.tm_mday);
    switch (struct_time_now_add.tm_wday)
    {
    case SUNDAY:
        wday_full = "Sunday";
        wday_abbr = "Sun";
        break;
    case MONDAY:
        wday_full = "Monday";
        wday_abbr = "Mon";
        break;
    case TUESDAY:
        wday_full = "Tuesday";
        wday_abbr = "Tue";
        break;
    case WEDNESDAY:
        wday_full = "Wednesday";
        wday_abbr = "Wed";
        break;
    case THURSDAY:
        wday_full = "Thursday";
        wday_abbr = "Thu";
        break;
    case FRIDAY:
        wday_full = "Friday";
        wday_abbr = "Fri";
        break;
    case SATURDAY:
        wday_full = "Saturday";
        wday_abbr = "Sat";
        break;
    default:
        break;
    }
    hours = (struct_time_now_add.tm_hour < 10) ? 
             "0" + std::to_string(struct_time_now_add.tm_hour) :
             std::to_string(struct_time_now_add.tm_hour);
    minutes = (struct_time_now_add.tm_min < 10) ? 
               "0" + std::to_string(struct_time_now_add.tm_min) :
               std::to_string(struct_time_now_add.tm_min);
    seconds = (struct_time_now_add.tm_sec < 10) ? 
               "0" + std::to_string(struct_time_now_add.tm_sec) :
               std::to_string(struct_time_now_add.tm_sec);

    c = new cl::Config();
    task_path_fn = "tasks/TestTask.cl";
    task_filename = "TestTask.cl";
    t_name = "TestTask";
    c->add_entry("Name", "TestTask");
    c->add_entry("Description", "A short description");
    c->add_entry("ScriptFilename", "cat_test.sh");
    c->add_entry("Frequency", "Once");
    c->add_entry("Datetime", hours + ":" + minutes + ":" + seconds);
    c->save_config(task_path_fn);
    delete c;

    s->Scheduler_init();
    s->obtain_exec_path();
    s->load_task(task_filename);

    assert(s->get_n_tasks() == 1);

    // Sleep for 2 seconds to let task run
    sleep(2); 

    ts::Task* t = s->get_task(t_name);
    assert(s->get_n_tasks() == 1);
    assert(s->task_exists(t_name));
    //assert(t->get_output() == "ls -l");
    assert(t->get_status() == ts::TaskStatus::FINISHED);

    s->Scheduler_delete();
    remove(task_path_fn.c_str());

    std::cout << ">> Scheduler_Task_run_task: 1 done" << std::endl;
    return 0;
}


int test2(ts::Scheduler* s){
    // TEST 2: generate new task to be executed in the next second. Check for the output after it runs.
    // Task Frequency: Daily

    time_t time_now;
    time_t time_now_add;
    std::tm* to_struct;
    std::tm struct_time_now_add;
    std::string years;
    std::string months;
    std::string months_str;
    std::string days;
    std::string wday_full;
    std::string wday_abbr;
    std::string hours;
    std::string minutes;
    std::string seconds;
    std::string verify_datetime_str;
    std::string ret_datetime_str;
    std::string task_path_fn;
    std::string task_filename;
    std::string t_name;
    cl::Config* c;

    time_now = std::time(&time_now);

    // Add one second from current time
    time_now_add = time_now + 1;
    
    // time_t to std::tm*
    to_struct = std::gmtime(&time_now_add);

    // std::tm* to std::tm
    struct_time_now_add = *to_struct;

    years = std::to_string(1900 + struct_time_now_add.tm_year);
    months = (struct_time_now_add.tm_mon + 1 < 10) ? 
              "0" + std::to_string(struct_time_now_add.tm_mon + 1) :
              std::to_string(struct_time_now_add.tm_mon + 1);
    switch (struct_time_now_add.tm_mon)
    {
    case JANUARY:
        months_str = "Jan";
        break;
    case FEBRUARY:
        months_str = "Feb";
        break;
    case MARCH:
        months_str = "Mar";
        break;
    case APRIL:
        months_str = "Apr";
        break;
    case MAY:
        months_str = "May";
        break;
    case JUNE:
        months_str = "Jun";
        break;
    case JULY:
        months_str = "Jul";
        break;
    case AUGUST:
        months_str = "Aug";
        break;
    case SEPTEMBER:
        months_str = "Sep";
        break;
    case OCTOBER:
        months_str = "Oct";
        break;
    case NOVEMBER:
        months_str = "Nov";
        break;
    case DECEMBER:
        months_str = "Dec";
        break;
    default:
        months_str = "";
        break;
    }  
    days = (struct_time_now_add.tm_mday < 10) ? 
            "0" + std::to_string(struct_time_now_add.tm_mday) :
            std::to_string(struct_time_now_add.tm_mday);
    switch (struct_time_now_add.tm_wday)
    {
    case SUNDAY:
        wday_full = "Sunday";
        wday_abbr = "Sun";
        break;
    case MONDAY:
        wday_full = "Monday";
        wday_abbr = "Mon";
        break;
    case TUESDAY:
        wday_full = "Tuesday";
        wday_abbr = "Tue";
        break;
    case WEDNESDAY:
        wday_full = "Wednesday";
        wday_abbr = "Wed";
        break;
    case THURSDAY:
        wday_full = "Thursday";
        wday_abbr = "Thu";
        break;
    case FRIDAY:
        wday_full = "Friday";
        wday_abbr = "Fri";
        break;
    case SATURDAY:
        wday_full = "Saturday";
        wday_abbr = "Sat";
        break;
    default:
        break;
    }
    hours = (struct_time_now_add.tm_hour < 10) ? 
             "0" + std::to_string(struct_time_now_add.tm_hour) :
             std::to_string(struct_time_now_add.tm_hour);
    minutes = (struct_time_now_add.tm_min < 10) ? 
               "0" + std::to_string(struct_time_now_add.tm_min) :
               std::to_string(struct_time_now_add.tm_min);
    seconds = (struct_time_now_add.tm_sec < 10) ? 
               "0" + std::to_string(struct_time_now_add.tm_sec) :
               std::to_string(struct_time_now_add.tm_sec);

    c = new cl::Config();
    task_path_fn = "tasks/TestTask.cl";
    task_filename = "TestTask.cl";
    t_name = "TestTask";
    c->add_entry("Name", "TestTask");
    c->add_entry("Description", "A short description");
    c->add_entry("ScriptFilename", "cat_test.sh");
    c->add_entry("Frequency", "Daily");
    c->add_entry("Datetime", hours + ":" + minutes + ":" + seconds);
    c->save_config(task_path_fn);
    delete c;

    s->Scheduler_init();
    s->obtain_exec_path();
    s->load_task(task_filename);

    assert(s->get_n_tasks() == 1);

    // Sleep for 2 seconds to let task run
    sleep(2); 

    ts::Task* t = s->get_task(t_name);
    assert(s->get_n_tasks() == 1);
    assert(s->task_exists(t_name));
    assert(t->get_output() == "ls -l");
    assert(t->get_status() == ts::TaskStatus::QUEUED);

    s->Scheduler_delete();
    remove(task_path_fn.c_str());

    std::cout << ">> Scheduler_Task_run_task: 2 done" << std::endl;
    return 0;
}


int test3(ts::Scheduler* s){
    // TEST 3: generate new task to be executed in the next second. Check for the output after it runs.
    // Task Frequency: Weekly

    time_t time_now;
    time_t time_now_add;
    std::tm* to_struct;
    std::tm struct_time_now_add;
    std::string years;
    std::string months;
    std::string months_str;
    std::string days;
    std::string wday_full;
    std::string wday_abbr;
    std::string hours;
    std::string minutes;
    std::string seconds;
    std::string verify_datetime_str;
    std::string ret_datetime_str;
    std::string task_path_fn;
    std::string task_filename;
    std::string t_name;
    cl::Config* c;

    time_now = std::time(&time_now);

    // Add one second from current time
    time_now_add = time_now + 1;
    
    // time_t to std::tm*
    to_struct = std::gmtime(&time_now_add);

    // std::tm* to std::tm
    struct_time_now_add = *to_struct;

    years = std::to_string(1900 + struct_time_now_add.tm_year);
    months = (struct_time_now_add.tm_mon + 1 < 10) ? 
              "0" + std::to_string(struct_time_now_add.tm_mon + 1) :
              std::to_string(struct_time_now_add.tm_mon + 1);
    switch (struct_time_now_add.tm_mon)
    {
    case JANUARY:
        months_str = "Jan";
        break;
    case FEBRUARY:
        months_str = "Feb";
        break;
    case MARCH:
        months_str = "Mar";
        break;
    case APRIL:
        months_str = "Apr";
        break;
    case MAY:
        months_str = "May";
        break;
    case JUNE:
        months_str = "Jun";
        break;
    case JULY:
        months_str = "Jul";
        break;
    case AUGUST:
        months_str = "Aug";
        break;
    case SEPTEMBER:
        months_str = "Sep";
        break;
    case OCTOBER:
        months_str = "Oct";
        break;
    case NOVEMBER:
        months_str = "Nov";
        break;
    case DECEMBER:
        months_str = "Dec";
        break;
    default:
        months_str = "";
        break;
    }  
    days = (struct_time_now_add.tm_mday < 10) ? 
            "0" + std::to_string(struct_time_now_add.tm_mday) :
            std::to_string(struct_time_now_add.tm_mday);
    switch (struct_time_now_add.tm_wday)
    {
    case SUNDAY:
        wday_full = "Sunday";
        wday_abbr = "Sun";
        break;
    case MONDAY:
        wday_full = "Monday";
        wday_abbr = "Mon";
        break;
    case TUESDAY:
        wday_full = "Tuesday";
        wday_abbr = "Tue";
        break;
    case WEDNESDAY:
        wday_full = "Wednesday";
        wday_abbr = "Wed";
        break;
    case THURSDAY:
        wday_full = "Thursday";
        wday_abbr = "Thu";
        break;
    case FRIDAY:
        wday_full = "Friday";
        wday_abbr = "Fri";
        break;
    case SATURDAY:
        wday_full = "Saturday";
        wday_abbr = "Sat";
        break;
    default:
        break;
    }
    hours = (struct_time_now_add.tm_hour < 10) ? 
             "0" + std::to_string(struct_time_now_add.tm_hour) :
             std::to_string(struct_time_now_add.tm_hour);
    minutes = (struct_time_now_add.tm_min < 10) ? 
               "0" + std::to_string(struct_time_now_add.tm_min) :
               std::to_string(struct_time_now_add.tm_min);
    seconds = (struct_time_now_add.tm_sec < 10) ? 
               "0" + std::to_string(struct_time_now_add.tm_sec) :
               std::to_string(struct_time_now_add.tm_sec);

    c = new cl::Config();
    task_path_fn = "tasks/TestTask.cl";
    task_filename = "TestTask.cl";
    t_name = "TestTask";
    c->add_entry("Name", "TestTask");
    c->add_entry("Description", "A short description");
    c->add_entry("ScriptFilename", "cat_test.sh");
    c->add_entry("Frequency", "Weekly");
    c->add_entry("Datetime", hours + ":" + minutes + ":" + seconds);
    c->save_config(task_path_fn);
    delete c;

    s->Scheduler_init();
    s->obtain_exec_path();
    s->load_task(task_filename);

    assert(s->get_n_tasks() == 1);

    // Sleep for 2 seconds to let task run
    sleep(2); 

    ts::Task* t = s->get_task(t_name);
    assert(s->get_n_tasks() == 1);
    assert(s->task_exists(t_name));
    assert(t->get_output() == "ls -l");
    assert(t->get_status() == ts::TaskStatus::QUEUED);

    s->Scheduler_delete();
    remove(task_path_fn.c_str());

    std::cout << ">> Scheduler_Task_run_task: 3 done" << std::endl;
    return 0;
}


int test4(ts::Scheduler* s){
    // TEST 4: generate new task to be executed in the next second. Check for the output after it runs.
    // Task Frequency: Monthly

    time_t time_now;
    time_t time_now_add;
    std::tm* to_struct;
    std::tm struct_time_now_add;
    std::string years;
    std::string months;
    std::string months_str;
    std::string days;
    std::string wday_full;
    std::string wday_abbr;
    std::string hours;
    std::string minutes;
    std::string seconds;
    std::string verify_datetime_str;
    std::string ret_datetime_str;
    std::string task_path_fn;
    std::string task_filename;
    std::string t_name;
    cl::Config* c;

    time_now = std::time(&time_now);

    // Add one second from current time
    time_now_add = time_now + 1;
    
    // time_t to std::tm*
    to_struct = std::gmtime(&time_now_add);

    // std::tm* to std::tm
    struct_time_now_add = *to_struct;

    years = std::to_string(1900 + struct_time_now_add.tm_year);
    months = (struct_time_now_add.tm_mon + 1 < 10) ? 
              "0" + std::to_string(struct_time_now_add.tm_mon + 1) :
              std::to_string(struct_time_now_add.tm_mon + 1);
    switch (struct_time_now_add.tm_mon)
    {
    case JANUARY:
        months_str = "Jan";
        break;
    case FEBRUARY:
        months_str = "Feb";
        break;
    case MARCH:
        months_str = "Mar";
        break;
    case APRIL:
        months_str = "Apr";
        break;
    case MAY:
        months_str = "May";
        break;
    case JUNE:
        months_str = "Jun";
        break;
    case JULY:
        months_str = "Jul";
        break;
    case AUGUST:
        months_str = "Aug";
        break;
    case SEPTEMBER:
        months_str = "Sep";
        break;
    case OCTOBER:
        months_str = "Oct";
        break;
    case NOVEMBER:
        months_str = "Nov";
        break;
    case DECEMBER:
        months_str = "Dec";
        break;
    default:
        months_str = "";
        break;
    }  
    days = (struct_time_now_add.tm_mday < 10) ? 
            "0" + std::to_string(struct_time_now_add.tm_mday) :
            std::to_string(struct_time_now_add.tm_mday);
    switch (struct_time_now_add.tm_wday)
    {
    case SUNDAY:
        wday_full = "Sunday";
        wday_abbr = "Sun";
        break;
    case MONDAY:
        wday_full = "Monday";
        wday_abbr = "Mon";
        break;
    case TUESDAY:
        wday_full = "Tuesday";
        wday_abbr = "Tue";
        break;
    case WEDNESDAY:
        wday_full = "Wednesday";
        wday_abbr = "Wed";
        break;
    case THURSDAY:
        wday_full = "Thursday";
        wday_abbr = "Thu";
        break;
    case FRIDAY:
        wday_full = "Friday";
        wday_abbr = "Fri";
        break;
    case SATURDAY:
        wday_full = "Saturday";
        wday_abbr = "Sat";
        break;
    default:
        break;
    }
    hours = (struct_time_now_add.tm_hour < 10) ? 
             "0" + std::to_string(struct_time_now_add.tm_hour) :
             std::to_string(struct_time_now_add.tm_hour);
    minutes = (struct_time_now_add.tm_min < 10) ? 
               "0" + std::to_string(struct_time_now_add.tm_min) :
               std::to_string(struct_time_now_add.tm_min);
    seconds = (struct_time_now_add.tm_sec < 10) ? 
               "0" + std::to_string(struct_time_now_add.tm_sec) :
               std::to_string(struct_time_now_add.tm_sec);

    c = new cl::Config();
    task_path_fn = "tasks/TestTask.cl";
    task_filename = "TestTask.cl";
    t_name = "TestTask";
    c->add_entry("Name", "TestTask");
    c->add_entry("Description", "A short description");
    c->add_entry("ScriptFilename", "cat_test.sh");
    c->add_entry("Frequency", "Monthly");
    c->add_entry("Datetime", hours + ":" + minutes + ":" + seconds);
    c->save_config(task_path_fn);
    delete c;

    s->Scheduler_init();
    s->obtain_exec_path();
    s->load_task(task_filename);

    assert(s->get_n_tasks() == 1);

    // Sleep for 2 seconds to let task run
    sleep(2); 

    ts::Task* t = s->get_task(t_name);
    assert(s->get_n_tasks() == 1);
    assert(s->task_exists(t_name));
    assert(t->get_output() == "ls -l");
    assert(t->get_status() == ts::TaskStatus::QUEUED);

    s->Scheduler_delete();
    remove(task_path_fn.c_str());

    std::cout << ">> Scheduler_Task_run_task: 4 done" << std::endl;
    return 0;
}


int test5(ts::Scheduler* s){
    // TEST 5: generate new task to be executed in the next second. Check for the output after it runs.
    // Task Frequency: Yearly

    time_t time_now;
    time_t time_now_add;
    std::tm* to_struct;
    std::tm struct_time_now_add;
    std::string years;
    std::string months;
    std::string months_str;
    std::string days;
    std::string wday_full;
    std::string wday_abbr;
    std::string hours;
    std::string minutes;
    std::string seconds;
    std::string verify_datetime_str;
    std::string ret_datetime_str;
    std::string task_path_fn;
    std::string task_filename;
    std::string t_name;
    cl::Config* c;

    time_now = std::time(&time_now);

    // Add one second from current time
    time_now_add = time_now + 1;
    
    // time_t to std::tm*
    to_struct = std::gmtime(&time_now_add);

    // std::tm* to std::tm
    struct_time_now_add = *to_struct;

    years = std::to_string(1900 + struct_time_now_add.tm_year);
    months = (struct_time_now_add.tm_mon + 1 < 10) ? 
              "0" + std::to_string(struct_time_now_add.tm_mon + 1) :
              std::to_string(struct_time_now_add.tm_mon + 1);
    switch (struct_time_now_add.tm_mon)
    {
    case JANUARY:
        months_str = "Jan";
        break;
    case FEBRUARY:
        months_str = "Feb";
        break;
    case MARCH:
        months_str = "Mar";
        break;
    case APRIL:
        months_str = "Apr";
        break;
    case MAY:
        months_str = "May";
        break;
    case JUNE:
        months_str = "Jun";
        break;
    case JULY:
        months_str = "Jul";
        break;
    case AUGUST:
        months_str = "Aug";
        break;
    case SEPTEMBER:
        months_str = "Sep";
        break;
    case OCTOBER:
        months_str = "Oct";
        break;
    case NOVEMBER:
        months_str = "Nov";
        break;
    case DECEMBER:
        months_str = "Dec";
        break;
    default:
        months_str = "";
        break;
    }  
    days = (struct_time_now_add.tm_mday < 10) ? 
            "0" + std::to_string(struct_time_now_add.tm_mday) :
            std::to_string(struct_time_now_add.tm_mday);
    switch (struct_time_now_add.tm_wday)
    {
    case SUNDAY:
        wday_full = "Sunday";
        wday_abbr = "Sun";
        break;
    case MONDAY:
        wday_full = "Monday";
        wday_abbr = "Mon";
        break;
    case TUESDAY:
        wday_full = "Tuesday";
        wday_abbr = "Tue";
        break;
    case WEDNESDAY:
        wday_full = "Wednesday";
        wday_abbr = "Wed";
        break;
    case THURSDAY:
        wday_full = "Thursday";
        wday_abbr = "Thu";
        break;
    case FRIDAY:
        wday_full = "Friday";
        wday_abbr = "Fri";
        break;
    case SATURDAY:
        wday_full = "Saturday";
        wday_abbr = "Sat";
        break;
    default:
        break;
    }
    hours = (struct_time_now_add.tm_hour < 10) ? 
             "0" + std::to_string(struct_time_now_add.tm_hour) :
             std::to_string(struct_time_now_add.tm_hour);
    minutes = (struct_time_now_add.tm_min < 10) ? 
               "0" + std::to_string(struct_time_now_add.tm_min) :
               std::to_string(struct_time_now_add.tm_min);
    seconds = (struct_time_now_add.tm_sec < 10) ? 
               "0" + std::to_string(struct_time_now_add.tm_sec) :
               std::to_string(struct_time_now_add.tm_sec);

    c = new cl::Config();
    task_path_fn = "tasks/TestTask.cl";
    task_filename = "TestTask.cl";
    t_name = "TestTask";
    c->add_entry("Name", "TestTask");
    c->add_entry("Description", "A short description");
    c->add_entry("ScriptFilename", "cat_test.sh");
    c->add_entry("Frequency", "Yearly");
    c->add_entry("Datetime", years + "-" + months + "-" + days + " " + hours + ":" + minutes + ":" + seconds);
    c->save_config(task_path_fn);
    delete c;

    s->Scheduler_init();
    s->obtain_exec_path();
    s->load_task(task_filename);

    assert(s->get_n_tasks() == 1);

    // Sleep for 2 seconds to let task run
    sleep(2); 

    ts::Task* t = s->get_task(t_name);
    assert(s->get_n_tasks() == 1);
    assert(s->task_exists(t_name));
    assert(t->get_output() == "ls -l");
    assert(t->get_status() == ts::TaskStatus::QUEUED);

    s->Scheduler_delete();
    remove(task_path_fn.c_str());

    std::cout << ">> Scheduler_Task_run_task: 5 done" << std::endl;
    return 0;
}


int main(int argc, char* argv[]){
    ts::Scheduler* s = ts::Scheduler::Scheduler_get_instance();

    test1(s);
    test2(s);
    test3(s);
    test4(s);
    test5(s);

    s->Scheduler_end_instance();
}