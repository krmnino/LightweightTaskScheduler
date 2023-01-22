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
    // TEST 1: verify that n_tasks and exec_path data members are set 0 and "" respectively.
    // Check with Scheduler::get_n_tasks() and Scheduler::get_current_path()
    s->Scheduler_init();

    assert(s->get_n_tasks() == 0);
    assert(s->get_current_path() == "");

    s->Scheduler_delete();

    std::cout << ">> Scheduler_methods: 1 done" << std::endl;
    return 0;
}


int test2(ts::Scheduler* s){
    // TEST 2: verify exec_path data member has been updated after Scheduler::obtain_exec_path()
    // Check with Scheduler::get_current_path()
    s->Scheduler_init();

    std::string current_path = std::filesystem::current_path();
    s->obtain_exec_path();
    assert(current_path == s->get_current_path());

    s->Scheduler_delete();

    std::cout << ">> Scheduler_methods: 2 done" << std::endl;
    return 0;
}


int test3(ts::Scheduler* s){
    // TEST 3: load tasks from tasks directory with Scheduler::load_tasks_from_dir()
    // Tasks to be loaded: cat_test.cl and ls_test.cl
    s->Scheduler_init();

    s->obtain_exec_path();
    s->load_tasks_from_dir();
    assert(s->get_n_tasks() == 2);

    s->Scheduler_delete();

    std::cout << ">> Scheduler_methods: 3 done" << std::endl;
    return 0;
}


int test4(ts::Scheduler* s){
    // TEST 4: load a single task from tasks directory with Scheduler::load_task()
    std::string task_config_fn = "cat_test.cl";

    s->Scheduler_init();

    s->obtain_exec_path();
    s->load_task(task_config_fn);
    assert(s->get_n_tasks() == 1);

    s->Scheduler_delete();

    std::cout << ">> Scheduler_methods: 4 done" << std::endl;
    return 0;
}


int test5(ts::Scheduler* s){
    // TEST 5: remove one task from scheduler after loading tasks from tasks directory
    // Tasks to be loaded: cat_test.cl and ls_test.cl
    // Task to be removed: cat
    std::string t_name = "cat";

    s->Scheduler_init();

    s->obtain_exec_path();
    s->load_tasks_from_dir();
    assert(s->get_n_tasks() == 2);

    s->remove_task(t_name);
    assert(s->get_n_tasks() == 1);

    s->Scheduler_delete();

    std::cout << ">> Scheduler_methods: 5 done" << std::endl;
    return 0;
}


int test6(ts::Scheduler* s){
    // TEST 6: remove two tasks from scheduler after loading tasks from tasks directory
    // Tasks to be loaded: cat_test.cl and ls_test.cl
    // Task to be removed: cat and ls
    std::string t_name1 = "cat";
    std::string t_name2 = "ls";

    s->Scheduler_init();

    s->obtain_exec_path();
    s->load_tasks_from_dir();
    assert(s->get_n_tasks() == 2);

    s->remove_task(t_name1);
    assert(s->get_n_tasks() == 1);

    s->remove_task(t_name2);
    assert(s->get_n_tasks() == 0);

    s->Scheduler_delete();

    std::cout << ">> Scheduler_methods: 6 done" << std::endl;
    return 0;
}

int test7(ts::Scheduler* s){
    // TEST 7: TODO

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

    // Add one minute in seconds from current time
    time_now_add = time_now + 2;
    
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
    task_path_fn = "tasks/TestTitle.cl";
    task_filename = "TestTitle.cl";
    t_name = "TestTitle";
    c->add_entry("Name", "TestTitle");
    c->add_entry("Description", "A short description");
    c->add_entry("ScriptFilename", "ls_test.sh");
    c->add_entry("Frequency", "Daily");
    c->add_entry("Datetime", hours + ":" + minutes + ":" + seconds);
    c->save_config(task_path_fn);
    delete c;

    s->Scheduler_init();
    s->obtain_exec_path();
    s->load_task(task_filename);

    assert(s->get_n_tasks() == 1);

    //s->launch_task_thread(t_name);

    s->Scheduler_delete();
    remove(task_path_fn.c_str());

    std::cout << ">> Scheduler_methods: 7 done" << std::endl;
    return 0;
}


int main(int argc, char* argv[]){
    ts::Scheduler* s = ts::Scheduler::Scheduler_get_instance();

    test1(s);
    test2(s);
    test3(s);
    test4(s);
    test5(s);
    test6(s);
    test7(s);

    s->Scheduler_end_instance();
}