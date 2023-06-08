#include <assert.h>
#include <iostream>
#include <filesystem>

#include "../src/Task.hpp"
#include "../src/Scheduler.hpp"
#include "../src/EventReporter.hpp"

lts::Scheduler* lts::Scheduler::scheduler_ptr = nullptr;
lts::EventReporter* lts::EventReporter::event_reporter_ptr = nullptr;

int test1(lts::Scheduler* s, lts::EventReporter* e){
    // TEST 1: create and load task "ZZZTestTask.cl" from task directory and then reload it
    // Validate tasks' name, description, script name, frequency, and output before and after reloading
    const lts::Task* ret_task;
    time_t time_now;
    time_t time_now_add;
    std::tm* to_struct;
    std::tm struct_time_now_add;
    std::string hours;
    std::string minutes;
    std::string seconds;
    cl::Config* c;
    std::string t_name;
    std::string t_description;
    std::string t_script_filename;
    std::string t_frequency;
    std::string task_config_filename;
    lts::Event ret_event;
    std::string verify_event_message;
    lts::EventType verify_event_type;

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
    t_name = "ZZZTestTask";
    t_description = "A short description";
    t_script_filename = "cat_test.sh";
    t_frequency = "Daily";
    task_config_filename = "ZZZTestTask.cl";
    c->add_entry("Name", t_name);
    c->add_entry("Description", t_description);
    c->add_entry("ScriptFilename", t_script_filename);
    c->add_entry("Frequency", t_frequency);
    c->add_entry("Datetime", hours + ":" + minutes + ":" + seconds);
    c->save_config("tasks/" + task_config_filename);
    delete c;
    
    e->EventReporter_init();
    s->Scheduler_init(e);

    s->obtain_exec_path();
    s->load_task(task_config_filename);
    ret_task = s->get_task(t_name);

    assert(s->get_n_tasks() == 1);
    assert(e->get_n_events() == 1);
    assert(ret_task->get_name() == t_name);
    assert(ret_task->get_description() == t_description);
    assert(ret_task->get_script_filename() == t_script_filename);
    assert(ret_task->get_frequency() == t_frequency);
    assert(ret_task->get_output() == "");
    assert(ret_task->get_status() == lts::TaskStatus::QUEUED);
    ret_event = e->get_event_at(0);
    verify_event_message = "Successfully loaded task \"ZZZTestTask\" from \"ZZZTestTask.cl\".";
    verify_event_type = lts::EventType::INFO;
    assert(ret_event.get_message() == verify_event_message);
    assert(ret_event.get_type() == verify_event_type);

    remove(("tasks/" + task_config_filename).c_str());

    // Create another task with the same name but different attributes
    c = new cl::Config();
    t_name = "ZZZTestTask";
    t_description = "A new description for the task";
    t_script_filename = "ls_test.sh";
    t_frequency = "Hourly";
    task_config_filename = "ZZZTestTask.cl";
    c->add_entry("Name", t_name);
    c->add_entry("Description", t_description);
    c->add_entry("ScriptFilename", t_script_filename);
    c->add_entry("Frequency", t_frequency);
    c->add_entry("Datetime", hours + ":" + minutes + ":" + seconds);
    c->save_config("tasks/" + task_config_filename);
    delete c;

    s->reload_task(t_name);
    ret_task = s->get_task(t_name);

    assert(s->get_n_tasks() == 1);
    assert(e->get_n_events() == 2);
    assert(ret_task->get_name() == t_name);
    assert(ret_task->get_description() == t_description);
    assert(ret_task->get_script_filename() == t_script_filename);
    assert(ret_task->get_frequency() == t_frequency);
    assert(ret_task->get_output() == "");
    assert(ret_task->get_status() == lts::TaskStatus::QUEUED);
    ret_event = e->get_event_at(0);
    verify_event_message = "Successfully reloaded task \"ZZZTestTask\".";
    verify_event_type = lts::EventType::INFO;
    assert(ret_event.get_message() == verify_event_message);
    assert(ret_event.get_type() == verify_event_type);

    remove(("tasks/" + task_config_filename).c_str());

    s->Scheduler_delete();
    e->EventReporter_delete();

    std::cout << ">> Scheduler_reload_task: 1 done" << std::endl;
    return 0;
}


int test2(lts::Scheduler* s, lts::EventReporter* e){
    // TEST 2: attempt to reload a task that is not in the scheduler
    std::string t_name;
    lts::Event ret_event;
    std::string verify_event_message;
    lts::EventType verify_event_type;

    e->EventReporter_init();
    s->Scheduler_init(e);

    s->obtain_exec_path();
    s->load_all_tasks();

    t_name = "ZZZTaskName";
    s->reload_task(t_name);

    assert(s->get_n_tasks() == 2);
    assert(e->get_n_events() == 3);
    ret_event = e->get_event_at(0);
    verify_event_message = "The task \"" + t_name + "\" does not exist in the scheduler.";
    verify_event_type = lts::EventType::ERROR;
    assert(ret_event.get_message() == verify_event_message);
    assert(ret_event.get_type() == verify_event_type);

    s->Scheduler_delete();
    e->EventReporter_delete();

    std::cout << ">> Scheduler_reload_task: 2 done" << std::endl;
    return 0;
}


int test3(lts::Scheduler* s, lts::EventReporter* e){
    // TEST 3: try to reload task from directory when tasks directory does not exist
    std::string original_dir_name;
    std::string rename_dir_name;
    std::string task_filename;
    std::string task_name;
    lts::Event ret_event;
    std::string verify_event_message;
    lts::EventType verify_event_type;

    original_dir_name = "tasks/";
    rename_dir_name = "original_tasks/";
    task_filename = "cat_test.cl";
    task_name = "cat";

    e->EventReporter_init();
    s->Scheduler_init(e);

    s->obtain_exec_path();
    s->load_all_tasks();
    
    // Temporarily change tasks directory name so the Scheduler can't find it
    rename(original_dir_name.c_str(), rename_dir_name.c_str());

    s->reload_task(task_name);

    assert(s->get_n_tasks() == 2);
    assert(e->get_n_events() == 3);
    ret_event = e->get_event_at(0);
    verify_event_message = "Could not find tasks directory.";
    verify_event_type = lts::EventType::ERROR;
    assert(ret_event.get_message() == verify_event_message);
    assert(ret_event.get_type() == verify_event_type);
    
    // Rename it back to tasks
    rename(rename_dir_name.c_str(), original_dir_name.c_str());

    s->Scheduler_delete();
    e->EventReporter_delete();

    std::cout << ">> Scheduler_reload_task: 3 done" << std::endl;
    return 0;
}


int test4(lts::Scheduler* s, lts::EventReporter* e){
    // TEST 4: try to reload task from directory when tasks directory does not exist
    std::string original_dir_name;
    std::string rename_dir_name;
    std::string task_filename;
    std::string task_name;
    lts::Event ret_event;
    std::string verify_event_message;
    lts::EventType verify_event_type;

    original_dir_name = "scripts/";
    rename_dir_name = "original_scripts/";
    task_filename = "cat_test.cl";
    task_name = "cat";

    e->EventReporter_init();
    s->Scheduler_init(e);

    s->obtain_exec_path();
    s->load_all_tasks();
    
    // Temporarily change scripts directory name so the Scheduler can't find it
    rename(original_dir_name.c_str(), rename_dir_name.c_str());

    s->reload_task(task_name);

    assert(s->get_n_tasks() == 2);
    assert(e->get_n_events() == 3);
    ret_event = e->get_event_at(0);
    verify_event_message = "Could not find scripts directory.";
    verify_event_type = lts::EventType::ERROR;
    assert(ret_event.get_message() == verify_event_message);
    assert(ret_event.get_type() == verify_event_type);
    
    // Rename it back to scripts
    rename(rename_dir_name.c_str(), original_dir_name.c_str());

    s->Scheduler_delete();
    e->EventReporter_delete();

    std::cout << ">> Scheduler_reload_task: 4 done" << std::endl;
    return 0;
}


int test5(lts::Scheduler* s, lts::EventReporter* e){
    // TEST 5: rename a loaded task's configuration file and attempt to reload it
    // TEST 3: try to reload task from directory when tasks directory does not exist
    time_t time_now;
    time_t time_now_add;
    std::tm* to_struct;
    std::tm struct_time_now_add;
    std::string hours;
    std::string minutes;
    std::string seconds;
    cl::Config* c;
    std::string t_name;
    std::string t_description;
    std::string t_script_filename;
    std::string t_frequency;
    std::string task_config_filename;
    lts::Event ret_event;
    std::string verify_event_message;
    lts::EventType verify_event_type;

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
    t_name = "ZZZTestTask";
    t_description = "A short description";
    t_script_filename = "cat_test.sh";
    t_frequency = "Daily";
    task_config_filename = "ZZZTestTask.cl";
    c->add_entry("Name", t_name);
    c->add_entry("Description", t_description);
    c->add_entry("ScriptFilename", t_script_filename);
    c->add_entry("Frequency", t_frequency);
    c->add_entry("Datetime", hours + ":" + minutes + ":" + seconds);
    c->save_config("tasks/" + task_config_filename);
    delete c;

    e->EventReporter_init();
    s->Scheduler_init(e);

    s->obtain_exec_path();
    s->load_task(task_config_filename);

    remove(("tasks/" + task_config_filename).c_str());

    s->reload_task(t_name);

    assert(s->get_n_tasks() == 1);
    assert(e->get_n_events() == 2);
    ret_event = e->get_event_at(0);
    verify_event_message = "The task file configuration file \"" + task_config_filename + 
                            "\" corresponding to task \"" + t_name +"\" could not be found.";
    verify_event_type = lts::EventType::ERROR;
    assert(ret_event.get_message() == verify_event_message);
    assert(ret_event.get_type() == verify_event_type);

    s->Scheduler_delete();
    e->EventReporter_delete();

    std::cout << ">> Scheduler_reload_task: 5 done" << std::endl;
    return 0;
}


int test6(lts::Scheduler* s, lts::EventReporter* e){
    // TEST 6: Load task, update configuration task file with an invalid attribute and attempt to reload
    const lts::Task* ret_task;
    time_t time_now;
    time_t time_now_add;
    std::tm* to_struct;
    std::tm struct_time_now_add;
    std::string hours;
    std::string minutes;
    std::string seconds;
    cl::Config* c;
    std::string t_name;
    std::string t_description;
    std::string t_script_filename;
    std::string t_frequency;
    std::string task_config_filename;
    lts::Event ret_event;
    std::string verify_event_message;
    lts::EventType verify_event_type;

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
    t_name = "ZZZTestTask";
    t_description = "A short description";
    t_script_filename = "cat_test.sh";
    t_frequency = "Daily";
    task_config_filename = "ZZZTestTask.cl";
    c->add_entry("Name", t_name);
    c->add_entry("Description", t_description);
    c->add_entry("ScriptFilename", t_script_filename);
    c->add_entry("Frequency", t_frequency);
    c->add_entry("Datetime", hours + ":" + minutes + ":" + seconds);
    c->save_config("tasks/" + task_config_filename);
    delete c;

    e->EventReporter_init();
    s->Scheduler_init(e);

    s->obtain_exec_path();
    s->load_task(task_config_filename);
    ret_task = s->get_task(t_name);

    assert(s->get_n_tasks() == 1);
    assert(e->get_n_events() == 1);
    assert(ret_task->get_name() == t_name);
    assert(ret_task->get_description() == t_description);
    assert(ret_task->get_script_filename() == t_script_filename);
    assert(ret_task->get_frequency() == t_frequency);
    assert(ret_task->get_output() == "");
    assert(ret_task->get_status() == lts::TaskStatus::QUEUED);
    ret_event = e->get_event_at(0);
    verify_event_message = "Successfully loaded task \"ZZZTestTask\" from \"ZZZTestTask.cl\".";
    verify_event_type = lts::EventType::INFO;
    assert(ret_event.get_message() == verify_event_message);
    assert(ret_event.get_type() == verify_event_type);

    remove(("tasks/" + task_config_filename).c_str());

    // Create another task with invalid Frequency attribute
    c = new cl::Config();
    t_name = "ZZZTestTask";
    t_description = "A new description for the task";
    t_script_filename = "ls_test.sh";
    t_frequency = "Anything";
    task_config_filename = "ZZZTestTask.cl";
    c->add_entry("Name", t_name);
    c->add_entry("Description", t_description);
    c->add_entry("ScriptFilename", t_script_filename);
    c->add_entry("Frequency", t_frequency);
    c->add_entry("Datetime", hours + ":" + minutes + ":" + seconds);
    c->save_config("tasks/" + task_config_filename);
    delete c;

    s->reload_task(t_name);
    ret_task = s->get_task(t_name);

    assert(s->get_n_tasks() == 1);
    assert(e->get_n_events() == 2);
    ret_event = e->get_event_at(0);
    verify_event_message = "An invalid frequency value of \"" + t_frequency + 
                           "\" was specified in the configuration file \"" +
                           task_config_filename + "\".";
    verify_event_type = lts::EventType::ERROR;
    assert(ret_event.get_message() == verify_event_message);
    assert(ret_event.get_type() == verify_event_type);

    remove(("tasks/" + task_config_filename).c_str());

    s->Scheduler_delete();
    e->EventReporter_delete();

    std::cout << ">> Scheduler_reload_task: 6 done" << std::endl;
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
    test6(s, e);

    s->Scheduler_end_instance();
    e->EventReporter_end_instance();
}