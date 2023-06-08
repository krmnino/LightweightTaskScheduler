#include <assert.h>
#include <iostream>
#include <filesystem>
#include <cstdio>

#include "../src/Task.hpp"
#include "../src/Scheduler.hpp"
#include "../src/EventReporter.hpp"

lts::Scheduler* lts::Scheduler::scheduler_ptr = nullptr;
lts::EventReporter* lts::EventReporter::event_reporter_ptr = nullptr;

int test1(lts::Scheduler* s, lts::EventReporter* e){
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
    std::string task_path_filename;
    std::string task_filename;
    std::string task_name;
    cl::Config* c;
    const lts::Task* ret_task;

    time_now = std::time(&time_now);

    // Add one second to current time
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
    task_path_filename = "tasks/TestTask.cl";
    task_filename = "TestTask.cl";
    task_name = "TestTask";
    c->add_entry("Name", "TestTask");
    c->add_entry("Description", "A short description");
    c->add_entry("ScriptFilename", "cat_test.sh");
    c->add_entry("Frequency", "Once");
    c->add_entry("Datetime", hours + ":" + minutes + ":" + seconds);
    c->save_config(task_path_filename);
    delete c;

    e->EventReporter_init();
    s->Scheduler_init(e);

    s->obtain_exec_path();
    s->load_task(task_filename);

    assert(s->get_n_tasks() == 1);
    assert(e->get_n_events() == 1);

    // Sleep for 2 seconds to let task run
    sleep(2); 

    ret_task = s->get_task(task_name);

    assert(s->get_n_tasks() == 1);
    assert(s->task_exists(task_name));
    assert(ret_task->get_output() == "ls -l");
    assert(ret_task->get_status() == lts::TaskStatus::FINISHED);

    assert(e->get_n_events() == 3);

    s->Scheduler_delete();
    e->EventReporter_delete();

    remove(task_path_filename.c_str());

    std::cout << ">> Scheduler_Task_run_task: 1 done" << std::endl;
    return 0;
}


int test2(lts::Scheduler* s, lts::EventReporter* e){
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
    std::string task_path_filename;
    std::string task_filename;
    std::string task_name;
    cl::Config* c;
    const lts::Task* ret_task;

    time_now = std::time(&time_now);

    // Add one second to current time
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
    task_path_filename = "tasks/TestTask.cl";
    task_filename = "TestTask.cl";
    task_name = "TestTask";
    c->add_entry("Name", "TestTask");
    c->add_entry("Description", "A short description");
    c->add_entry("ScriptFilename", "cat_test.sh");
    c->add_entry("Frequency", "Daily");
    c->add_entry("Datetime", hours + ":" + minutes + ":" + seconds);
    c->save_config(task_path_filename);
    delete c;

    e->EventReporter_init();
    s->Scheduler_init(e);

    s->obtain_exec_path();
    s->load_task(task_filename);

    assert(s->get_n_tasks() == 1);
    assert(e->get_n_events() == 1);

    ret_task = s->get_task(task_name);
    ret_datetime_str = ret_task->get_execution_datetime_fmt();

    // Sleep for 2 seconds to let task run
    sleep(2); 

    ret_task = s->get_task(task_name);
    assert(s->get_n_tasks() == 1);
    assert(s->task_exists(task_name));
    assert(ret_task->get_output() == "ls -l");
    assert(ret_task->get_status() == lts::TaskStatus::QUEUED);

    assert(e->get_n_events() == 3);

    s->Scheduler_delete();
    e->EventReporter_delete();

    remove(task_path_filename.c_str());

    std::cout << ">> Scheduler_Task_run_task: 2 done" << std::endl;
    return 0;
}


int test3(lts::Scheduler* s, lts::EventReporter* e){
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
    std::string task_path_filename;
    std::string task_filename;
    std::string task_name;
    cl::Config* c;
    const lts::Task* ret_task;

    time_now = std::time(&time_now);

    // Add one second to current time
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
    task_path_filename = "tasks/TestTask.cl";
    task_filename = "TestTask.cl";
    task_name = "TestTask";
    c->add_entry("Name", "TestTask");
    c->add_entry("Description", "A short description");
    c->add_entry("ScriptFilename", "cat_test.sh");
    c->add_entry("Frequency", "Weekly");
    c->add_entry("Datetime", hours + ":" + minutes + ":" + seconds);
    c->save_config(task_path_filename);
    delete c;

    e->EventReporter_init();
    s->Scheduler_init(e);

    s->obtain_exec_path();
    s->load_task(task_filename);

    assert(s->get_n_tasks() == 1);
    assert(e->get_n_events() == 1);

    // Sleep for 2 seconds to let task run
    sleep(2); 

    ret_task = s->get_task(task_name);
    assert(s->get_n_tasks() == 1);
    assert(s->task_exists(task_name));
    assert(ret_task->get_output() == "ls -l");
    assert(ret_task->get_status() == lts::TaskStatus::QUEUED);

    assert(e->get_n_events() == 3);

    s->Scheduler_delete();
    e->EventReporter_delete();

    remove(task_path_filename.c_str());

    std::cout << ">> Scheduler_Task_run_task: 3 done" << std::endl;
    return 0;
}


int test4(lts::Scheduler* s, lts::EventReporter* e){
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
    std::string task_name;
    cl::Config* c;
    const lts::Task* ret_task;

    time_now = std::time(&time_now);

    // Add one second to current time
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
    task_name = "TestTask";
    c->add_entry("Name", "TestTask");
    c->add_entry("Description", "A short description");
    c->add_entry("ScriptFilename", "cat_test.sh");
    c->add_entry("Frequency", "Monthly");
    c->add_entry("Datetime", hours + ":" + minutes + ":" + seconds);
    c->save_config(task_path_fn);
    delete c;

    e->EventReporter_init();
    s->Scheduler_init(e);

    s->obtain_exec_path();
    s->load_task(task_filename);

    assert(s->get_n_tasks() == 1);
    assert(e->get_n_events() == 1);

    // Sleep for 2 seconds to let task run
    sleep(2); 

    ret_task = s->get_task(task_name);
    assert(s->get_n_tasks() == 1);
    assert(s->task_exists(task_name));
    assert(ret_task->get_output() == "ls -l");
    assert(ret_task->get_status() == lts::TaskStatus::QUEUED);

    assert(e->get_n_events() == 3);

    s->Scheduler_delete();
    e->EventReporter_delete();

    remove(task_path_fn.c_str());

    std::cout << ">> Scheduler_Task_run_task: 4 done" << std::endl;
    return 0;
}


int test5(lts::Scheduler* s, lts::EventReporter* e){
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
    std::string task_name;
    cl::Config* c;
    const lts::Task* ret_task;

    time_now = std::time(&time_now);

    // Add one second to current time
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
    task_name = "TestTask";
    c->add_entry("Name", "TestTask");
    c->add_entry("Description", "A short description");
    c->add_entry("ScriptFilename", "cat_test.sh");
    c->add_entry("Frequency", "Yearly");
    c->add_entry("Datetime", years + "-" + months + "-" + days + " " + hours + ":" + minutes + ":" + seconds);
    c->save_config(task_path_fn);
    delete c;

    e->EventReporter_init();
    s->Scheduler_init(e);
    
    s->obtain_exec_path();
    s->load_task(task_filename);

    assert(s->get_n_tasks() == 1);
    assert(e->get_n_events() == 1);

    // Sleep for 2 seconds to let task run
    sleep(2); 

    ret_task = s->get_task(task_name);
    assert(s->get_n_tasks() == 1);
    assert(s->task_exists(task_name));
    assert(ret_task->get_output() == "ls -l");
    assert(ret_task->get_status() == lts::TaskStatus::QUEUED);

    assert(e->get_n_events() == 3);

    s->Scheduler_delete();
    e->EventReporter_delete();

    remove(task_path_fn.c_str());

    std::cout << ">> Scheduler_Task_run_task: 5 done" << std::endl;
    return 0;
}


int main(int argc, char* argv[]){
    lts::EventReporter* e = lts::EventReporter::EventReporter_get_instance();
    lts::Scheduler* s = lts::Scheduler::Scheduler_get_instance();

    test1(s, e);
    test2(s, e);
    test3(s, e);
    test4(s, e);
    test5(s, e);

    s->Scheduler_end_instance();
    e->EventReporter_end_instance();
}