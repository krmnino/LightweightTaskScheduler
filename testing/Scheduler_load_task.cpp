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


int test4(ts::Scheduler* s, ts::EventReporter* e){
    // TEST 4: generate task with datetime in the past and attempt to load it
    time_t time_now;
    time_t time_now_add;
    std::tm* to_struct;
    std::tm struct_time_now_add;
    std::string hours;
    std::string minutes;
    std::string seconds;
    std::string task_path_filename;
    std::string task_filename;
    std::string task_name;
    cl::Config* c;

    time_now = std::time(&time_now);

    // Subtract 15 seconds from current time
    time_now_add = time_now - 15;
    
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
    task_path_filename = "tasks/ZZZTestTask.cl";
    task_filename = "ZZZTestTask.cl";
    c->add_entry("Name", "ZZZTestTask");
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

    assert(s->get_n_tasks() == 0);
    assert(e->get_n_events() == 1);

    s->Scheduler_delete();
    e->EventReporter_delete();

    remove(task_path_filename.c_str());
    
    std::cout << ">> Scheduler_load_task: 4 done" << std::endl;
    return 0;
}


int test5(ts::Scheduler* s, ts::EventReporter* e){
    // TEST 5: generate task with duplicate Name and attempt to load it
    std::string task_path_filename;
    std::string task_filename;
    std::string task_name_1;
    std::string task_name_2;
    cl::Config* c;

    // Create temporary task
    c = new cl::Config();
    task_path_filename = "tasks/ZZZTestTask.cl";
    task_name_1 = "cat_test.cl";
    task_name_2 = "ZZZTestTask.cl";
    c->add_entry("Name", "cat");
    c->add_entry("Description", "A short description");
    c->add_entry("ScriptFilename", "cat_test.sh");
    c->add_entry("Frequency", "Daily");
    c->add_entry("Datetime", "23:59:59");
    c->save_config(task_path_filename);
    delete c;

    e->EventReporter_init();
    s->Scheduler_init(e);

    s->obtain_exec_path();

    // Load cat_test.cl
    s->load_task(task_name_1);
    assert(s->get_n_tasks() == 1);
    assert(e->get_n_events() == 1);

    // Load ZZZTestTask.cl
    s->load_task(task_name_2);
    assert(s->get_n_tasks() == 1);
    assert(e->get_n_events() == 2);

    s->Scheduler_delete();
    e->EventReporter_delete();

    remove(task_path_filename.c_str());
    
    std::cout << ">> Scheduler_load_task: 5 done" << std::endl;
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

    s->Scheduler_end_instance();
    e->EventReporter_end_instance();
}