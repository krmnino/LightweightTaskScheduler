#include <assert.h>
#include <iostream>
#include <filesystem>

#include "../src/Task.hpp"
#include "../src/Scheduler.hpp"
#include "../src/EventReporter.hpp"

ts::Scheduler* ts::Scheduler::scheduler_ptr = nullptr;
ts::EventReporter* ts::EventReporter::event_reporter_ptr = nullptr;

int test1(ts::Scheduler* s, ts::EventReporter* e){
    // TEST 1: load tasks from tasks directory
    // Tasks to be loaded: cat_test.cl and ls_test.cl
    // Validate tasks' name, decription, script name, frequency, and output
    ts::Task* t_ret;
    std::string t_name;
    std::string t_description;
    std::string t_script_filename;
    std::string t_frequency;

    s->Scheduler_init(e);

    s->obtain_exec_path();
    s->load_tasks_from_dir();
    
    assert(s->get_n_tasks() == 2);

    t_name = "cat";
    t_description = "Test task: call command cat";
    t_script_filename = "cat_test.sh";
    t_frequency = "Once";
    t_ret = s->get_task(t_name);
    assert(t_ret->get_name() == t_name);
    assert(t_ret->get_description() == t_description);
    assert(t_ret->get_script_filename() == t_script_filename);
    assert(t_ret->get_frequency() == t_frequency);
    assert(t_ret->get_output() == "");
    assert(t_ret->get_status() == ts::TaskStatus::QUEUED);

    t_name = "ls";
    t_description = "Test task: call command ls";
    t_script_filename = "ls_test.sh";
    t_frequency = "Once";
    t_ret = s->get_task(t_name);
    assert(t_ret->get_name() == t_name);
    assert(t_ret->get_description() == t_description);
    assert(t_ret->get_script_filename() == t_script_filename);
    assert(t_ret->get_frequency() == t_frequency);
    assert(t_ret->get_output() == "");
    assert(t_ret->get_status() == ts::TaskStatus::QUEUED);

    s->Scheduler_delete();

    std::cout << ">> Scheduler_load_tasks_from_dir: 1 done" << std::endl;
    return 0;
}


int test2(ts::Scheduler* s, ts::EventReporter* e){
    // TEST 2: load tasks from tasks directory
    // Tasks to be loaded: cat_test.cl and ls_test.cl
    // Validate tasks' name, decription, script name, frequency, and output
    // !!! TODO !!!
    s->Scheduler_init(e);

    s->load_tasks_from_dir();


    s->Scheduler_delete();
    
    std::cout << ">> Scheduler_load_tasks_from_dir: 2 done" << std::endl;
    return 0;
}


int main(int argc, char* argv[]){
    ts::EventReporter* e = ts::EventReporter::EventReporter_get_instance();
    ts::Scheduler* s = ts::Scheduler::Scheduler_get_instance();

    test1(s, e);
    test2(s, e);

    s->Scheduler_end_instance();
    e->EventReporter_end_instance();
}