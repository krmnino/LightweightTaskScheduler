#include <assert.h>
#include <iostream>
#include <filesystem>
#include <cstdio>

#include "../src/Task.hpp"
#include "../src/Scheduler.hpp"
#include "../src/EventReporter.hpp"

ts::Scheduler* ts::Scheduler::scheduler_ptr = nullptr;
ts::EventReporter* ts::EventReporter::event_reporter_ptr = nullptr;

int test1(ts::Scheduler* s, ts::EventReporter* e){
    // TEST 1: verify that n_tasks and exec_path data members are set 0 and "" respectively.
    // Check with Scheduler::get_n_tasks() and Scheduler::get_current_path()
    e->EventReporter_init();
    s->Scheduler_init(e);

    assert(s->get_n_tasks() == 0);
    assert(s->get_current_path() == "");

    assert(e->get_n_events() == 0);

    s->Scheduler_delete();
    e->EventReporter_delete();

    std::cout << ">> Scheduler_methods: 1 done" << std::endl;
    return 0;
}


int test2(ts::Scheduler* s, ts::EventReporter* e){
    // TEST 2: verify exec_path data member has been updated after Scheduler::obtain_exec_path()
    // Check with Scheduler::get_current_path()
    e->EventReporter_init();
    s->Scheduler_init(e);

    std::string current_path = std::filesystem::current_path();
    s->obtain_exec_path();
    assert(current_path == s->get_current_path());

    assert(e->get_n_events() == 0);

    s->Scheduler_delete();
    e->EventReporter_delete();

    std::cout << ">> Scheduler_methods: 2 done" << std::endl;
    return 0;
}


int test3(ts::Scheduler* s, ts::EventReporter* e){
    // TEST 3: load tasks from tasks directory with Scheduler::load_tasks_from_dir()
    // Tasks to be loaded: cat_test.cl and ls_test.cl
    e->EventReporter_init();
    s->Scheduler_init(e);

    s->obtain_exec_path();
    s->load_tasks_from_dir();
    assert(s->get_n_tasks() == 2);

    assert(e->get_n_events() == 2);

    s->Scheduler_delete();
    e->EventReporter_delete();

    std::cout << ">> Scheduler_methods: 3 done" << std::endl;
    return 0;
}


int test4(ts::Scheduler* s, ts::EventReporter* e){
    // TEST 4: load a single task from tasks directory with Scheduler::load_task()
    std::string task_config_fn = "cat_test.cl";

    e->EventReporter_init();
    s->Scheduler_init(e);

    s->obtain_exec_path();
    s->load_task(task_config_fn);
    assert(s->get_n_tasks() == 1);

    assert(e->get_n_events() == 1);

    s->Scheduler_delete();
    e->EventReporter_delete();

    std::cout << ">> Scheduler_methods: 4 done" << std::endl;
    return 0;
}


int test5(ts::Scheduler* s, ts::EventReporter* e){
    // TEST 5: remove one task from scheduler after loading tasks from tasks directory
    // Tasks to be loaded: cat_test.cl and ls_test.cl
    // Task to be removed: cat
    std::string t_name = "cat";

    e->EventReporter_init();
    s->Scheduler_init(e);

    s->obtain_exec_path();
    s->load_tasks_from_dir();
    assert(s->get_n_tasks() == 2);
    
    assert(e->get_n_events() == 2);

    s->remove_task(t_name);
    assert(!s->task_exists(t_name));
    assert(s->get_n_tasks() == 1);

    assert(e->get_n_events() == 3);

    s->Scheduler_delete();
    e->EventReporter_delete();

    std::cout << ">> Scheduler_methods: 5 done" << std::endl;
    return 0;
}


int test6(ts::Scheduler* s, ts::EventReporter* e){
    // TEST 6: remove two tasks from scheduler after loading tasks from tasks directory
    // Tasks to be loaded: cat_test.cl and ls_test.cl
    // Task to be removed: cat and ls
    std::string t_name1 = "cat";
    std::string t_name2 = "ls";

    e->EventReporter_init();
    s->Scheduler_init(e);

    s->obtain_exec_path();
    s->load_tasks_from_dir();
    assert(s->get_n_tasks() == 2);

    assert(e->get_n_events() == 2);

    s->remove_task(t_name1);
    assert(!s->task_exists(t_name1));
    assert(s->get_n_tasks() == 1);

    assert(e->get_n_events() == 3);

    s->remove_task(t_name2);
    assert(!s->task_exists(t_name2));
    assert(s->get_n_tasks() == 0);

    assert(e->get_n_events() == 4);

    s->Scheduler_delete();
    e->EventReporter_delete();

    std::cout << ">> Scheduler_methods: 6 done" << std::endl;
    return 0;
}


int test7(ts::Scheduler* s, ts::EventReporter* e){
    // TEST 7: search for a task that does not exist in Scheduler
    std::string t_name = "any_name";

    e->EventReporter_init();
    s->Scheduler_init(e);

    assert(!s->task_exists(t_name));

    assert(e->get_n_events() == 0);

    s->Scheduler_delete();
    e->EventReporter_delete();

    std::cout << ">> Scheduler_methods: 7 done" << std::endl;
    return 0;
}


int test8(ts::Scheduler* s, ts::EventReporter* e){
    // TEST 8: get task from scheduler after loading it
    time_t time_now;
    time_t time_now_add;
    std::tm* to_struct;
    std::tm struct_time_now_add;
    std::string years;
    std::string months_str;
    std::string days;
    std::string wday_full;
    std::string wday_abbr;
    std::string hours;
    std::string minutes;
    std::string seconds;
    std::string task_path_filename;
    std::string task_filename;
    std::string task_name;
    std::string validate_datetime;
    cl::Config* c;
    const ts::Task* ret_task;

    time_now = std::time(&time_now);

    // Add 15 seconds to current time
    time_now_add = time_now + 15;
    
    // time_t to std::tm*
    to_struct = std::gmtime(&time_now_add);

    // std::tm* to std::tm
    struct_time_now_add = *to_struct;

    hours = (struct_time_now_add.tm_hour < 10) ? 
             "0" + std::to_string(struct_time_now_add.tm_hour) :
             std::to_string(struct_time_now_add.tm_hour);
    minutes = (struct_time_now_add.tm_min < 10) ? 
               "0" + std::to_string(struct_time_now_add.tm_min) :
               std::to_string(struct_time_now_add.tm_min);
    seconds = (struct_time_now_add.tm_sec < 10) ? 
               "0" + std::to_string(struct_time_now_add.tm_sec) :
               std::to_string(struct_time_now_add.tm_sec);

    // Create temporary task
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

    // Add timezone offset in seconds to current time
    time_now_add = time_now + 15 + (TIMEZONE * 60 * 60);
    
    // time_t to std::tm*
    to_struct = std::gmtime(&time_now_add);

    // std::tm* to std::tm
    struct_time_now_add = *to_struct;

    years = std::to_string(1900 + struct_time_now_add.tm_year);
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

    validate_datetime = wday_abbr + " " + months_str + " " + days + " " + hours + ":" + minutes + ":" + seconds + " " + years;

    // Get task from scheduler and validate
    ret_task = s->get_task(task_name);

    assert(ret_task->get_name() == task_name);
    assert(ret_task->get_description() == "A short description");
    assert(ret_task->get_script_filename() == "cat_test.sh");
    assert(ret_task->get_frequency() == "Daily");
    assert(ret_task->get_execution_datetime_fmt() == validate_datetime);

    assert(e->get_n_events() == 1);

    s->Scheduler_delete();
    e->EventReporter_delete();

    remove(task_path_filename.c_str());

    std::cout << ">> Scheduler_methods: 8 done" << std::endl;
    return 0;
}


int main(int argc, char* argv[]){
    ts::EventReporter* e = ts::EventReporter::EventReporter_get_instance();
    ts::Scheduler* s = ts::Scheduler::Scheduler_get_instance();

    test1(s, e);
    test2(s, e);
    test3(s, e);
    test4(s, e);
    test5(s, e);
    test6(s, e);
    test7(s, e);
    test8(s, e);

    s->Scheduler_end_instance();
    e->EventReporter_end_instance();
}