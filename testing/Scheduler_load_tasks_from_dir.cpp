#include <assert.h>
#include <iostream>
#include <filesystem>

#include "../src/Task.hpp"
#include "../src/Scheduler.hpp"
#include "../src/CommandLine.hpp"

ts::Scheduler* ts::Scheduler::scheduler_ptr = nullptr;
ts::CommandLine* ts::CommandLine::command_line_ptr = nullptr;

int test1(ts::Scheduler* s){
    // TEST 1: load tasks from tasks directory
    // Tasks to be loaded: cat_test.cl and ls_test.cl
    // Validate tasks' name, decription, script name, frequency, and output
    ts::Task t_deref;
    std::string t_name;
    std::string t_description;
    std::string t_script_filename;
    std::string t_frequency;

    s->Scheduler_init();

    s->obtain_exec_path();
    s->load_tasks_from_dir();
    
    assert(s->get_n_tasks() == 2);

    t_name = "cat";
    t_description = "Test task: call command cat";
    t_script_filename = "cat_test.sh";
    t_frequency = "Once";
    t_deref = *s->get_task(t_name);
    assert(t_deref.get_name() == t_name);
    assert(t_deref.get_description() == t_description);
    assert(t_deref.get_script_filename() == t_script_filename);
    assert(t_deref.get_frequency() == t_frequency);
    assert(t_deref.get_output() == "");

    t_name = "ls";
    t_description = "Test task: call command ls";
    t_script_filename = "ls_test.sh";
    t_frequency = "Once";
    t_deref = *s->get_task(t_name);
    assert(t_deref.get_name() == t_name);
    assert(t_deref.get_description() == t_description);
    assert(t_deref.get_script_filename() == t_script_filename);
    assert(t_deref.get_frequency() == t_frequency);
    assert(t_deref.get_output() == "");

    s->Scheduler_delete();

    std::cout << ">> Scheduler_load_tasks_from_dir: 1 done" << std::endl;
    return 0;
}


int main(int argc, char* argv[]){
    ts::Scheduler* s = ts::Scheduler::Scheduler_get_instance();

    test1(s);

    s->Scheduler_end_instance();
}