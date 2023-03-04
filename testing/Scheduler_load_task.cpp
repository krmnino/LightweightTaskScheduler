#include <assert.h>
#include <iostream>
#include <filesystem>

#include "../src/Task.hpp"
#include "../src/Scheduler.hpp"
#include "../src/EventReporter.hpp"

ts::Scheduler* ts::Scheduler::scheduler_ptr = nullptr;
ts::EventReporter* ts::EventReporter::event_reporter_ptr = nullptr;

int test1(ts::Scheduler* s, ts::EventReporter* e){
    // TEST 1: load task "cat_test.cl" from task directory
    // Validate tasks' name, description, script name, frequency, and output
    const ts::Task* ret_task;
    std::string t_name;
    std::string t_description;
    std::string t_script_filename;
    std::string t_frequency;
    std::string task_path_filename;

    e->EventReporter_init();
    s->Scheduler_init(e);

    s->obtain_exec_path();
    
    task_path_filename = "cat_test.cl";
    s->load_task(task_path_filename);
    
    assert(s->get_n_tasks() == 1);
    assert(e->get_n_events() == 1);
    
    t_name = "cat";
    t_description = "Test task: call command cat";
    t_script_filename = "cat_test.sh";
    t_frequency = "Once";
    ret_task = s->get_task(t_name);

    assert(ret_task->get_name() == t_name);
    assert(ret_task->get_description() == t_description);
    assert(ret_task->get_script_filename() == t_script_filename);
    assert(ret_task->get_frequency() == t_frequency);
    assert(ret_task->get_output() == "");
    assert(ret_task->get_status() == ts::TaskStatus::QUEUED);

    s->Scheduler_delete();
    e->EventReporter_delete();

    std::cout << ">> Scheduler_load_task: 1 done" << std::endl;
    return 0;
}


int test2(ts::Scheduler* s, ts::EventReporter* e){
    // TEST 2: try to load task from directory when tasks directory does not exist
    std::string original_task_dir_name = "tasks/";
    std::string rename_task_dir_name = "original_tasks/";
    std::string task_filename = "cat_test.cl";

    e->EventReporter_init();
    s->Scheduler_init(e);
    // Temporarily change tasks directory name so the Scheduler can't find it
    rename(original_task_dir_name.c_str(), rename_task_dir_name.c_str());

    s->obtain_exec_path();
    s->load_task(task_filename);

    assert(s->get_n_tasks() == 0);
    assert(e->get_n_events() == 1);
    
    // Rename it back to tasks
    rename(rename_task_dir_name.c_str(), original_task_dir_name.c_str());
    s->Scheduler_delete();
    e->EventReporter_delete();

    std::cout << ">> Scheduler_load_task: 2 done" << std::endl;
    return 0;
}


int test3(ts::Scheduler* s, ts::EventReporter* e){
    // TEST 2: try to load task from directory when scripts directory does not exist
    std::string original_scripts_dir_name = "scripts/";
    std::string rename_scripts_dir_name = "original_scripts/";
    std::string task_filename = "cat_test.cl";

    e->EventReporter_init();
    s->Scheduler_init(e);
    // Temporarily change tasks directory name so the Scheduler can't find it
    rename(original_scripts_dir_name.c_str(), rename_scripts_dir_name.c_str());

    s->obtain_exec_path();
    s->load_task(task_filename);

    assert(s->get_n_tasks() == 0);
    assert(e->get_n_events() == 1);
    
    // Rename it back to tasks
    rename(rename_scripts_dir_name.c_str(), original_scripts_dir_name.c_str());
    s->Scheduler_delete();
    e->EventReporter_delete();

    std::cout << ">> Scheduler_load_task: 3 done" << std::endl;
    return 0;
}


int main(int argc, char* argv[]){
    ts::EventReporter* e = ts::EventReporter::EventReporter_get_instance();
    ts::Scheduler* s = ts::Scheduler::Scheduler_get_instance();

    test1(s, e);
    test2(s, e);
    test3(s, e);

    s->Scheduler_end_instance();
    e->EventReporter_end_instance();
}