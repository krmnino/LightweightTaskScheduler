#include <assert.h>
#include <iostream>
#include <filesystem>

#include "../src/Task.hpp"
#include "../src/Scheduler.hpp"
#include "../src/EventReporter.hpp"

lts::Scheduler* lts::Scheduler::scheduler_ptr = nullptr;
lts::EventReporter* lts::EventReporter::event_reporter_ptr = nullptr;

int test1(lts::Scheduler* s, lts::EventReporter* e){
    // TEST 1: load tasks from tasks directory
    // Tasks to be loaded: cat_test.cl and ls_test.cl
    // Validate tasks' name, description, script name, frequency, and output
    const lts::Task* ret_task;
    std::string t_name;
    std::string t_description;
    std::string t_script_filename;
    std::string t_frequency;
    lts::Event ret_event;
    std::string verify_event_message;
    lts::EventType verify_event_type;

    e->EventReporter_init();
    s->Scheduler_init(e);

    s->obtain_exec_path();
    s->load_all_tasks();
    
    assert(s->get_n_tasks() == 2);
    assert(e->get_n_events() == 2);

    s->reload_all_tasks();

    assert(s->get_n_tasks() == 2);
    assert(e->get_n_events() == 4);
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
    assert(ret_task->get_status() == lts::TaskStatus::QUEUED);
    ret_event = e->get_event_at(1);
    verify_event_message = "Successfully reloaded task \"cat\".";
    verify_event_type = lts::EventType::INFO;
    assert(ret_event.get_message() == verify_event_message);
    assert(ret_event.get_type() == verify_event_type);
    
    t_name = "ls";
    t_description = "Test task: call command ls";
    t_script_filename = "ls_test.sh";
    t_frequency = "Once";
    ret_task = s->get_task(t_name);
    assert(ret_task->get_name() == t_name);
    assert(ret_task->get_description() == t_description);
    assert(ret_task->get_script_filename() == t_script_filename);
    assert(ret_task->get_frequency() == t_frequency);
    assert(ret_task->get_output() == "");
    assert(ret_task->get_status() == lts::TaskStatus::QUEUED);
    ret_event = e->get_event_at(0);
    verify_event_message = "Successfully reloaded task \"ls\".";
    verify_event_type = lts::EventType::INFO;
    assert(ret_event.get_message() == verify_event_message);
    assert(ret_event.get_type() == verify_event_type);

    s->Scheduler_delete();
    e->EventReporter_delete();

    std::cout << ">> Scheduler_reload_all_tasks: 1 done" << std::endl;
    return 0;
}


int test2(lts::Scheduler* s, lts::EventReporter* e){
    // TEST 2: try to reload tasks from directory when tasks directory does not exist
    std::string original_dir_name = "tasks/";
    std::string rename_dir_name = "original_tasks/";
    lts::Event ret_event;
    std::string verify_event_message;
    lts::EventType verify_event_type;

    e->EventReporter_init();
    s->Scheduler_init(e);

    s->obtain_exec_path();
    s->load_all_tasks();

    // Temporarily change tasks directory name so the Scheduler can't find it
    rename(original_dir_name.c_str(), rename_dir_name.c_str());

    s->reload_all_tasks();

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
    
    std::cout << ">> Scheduler_reload_all_tasks: 2 done" << std::endl;
    return 0;
}


int test3(lts::Scheduler* s, lts::EventReporter* e){
    // TEST 3: try to reload tasks from directory when scripts directory does not exist
    std::string original_dir_name = "scripts/";
    std::string rename_dir_name = "original_tasks/";
    lts::Event ret_event;
    std::string verify_event_message;
    lts::EventType verify_event_type;

    e->EventReporter_init();
    s->Scheduler_init(e);

    s->obtain_exec_path();
    s->load_all_tasks();

    // Temporarily change scripts directory name so the Scheduler can't find it
    rename(original_dir_name.c_str(), rename_dir_name.c_str());

    s->reload_all_tasks();

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
    
    std::cout << ">> Scheduler_reload_all_tasks: 3 done" << std::endl;
    return 0;
}


int test4(lts::Scheduler* s, lts::EventReporter* e){
    // TEST 4: try to reload all tasks with one of the configuration files missing
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
    bool matching_event_msg;
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
    s->load_all_tasks();

    assert(s->get_n_tasks() == 3);
    assert(e->get_n_events() == 3);
    
    remove(("tasks/" + task_config_filename).c_str());

    s->reload_all_tasks();

    assert(s->get_n_tasks() == 3);
    assert(e->get_n_events() == 6);

    // Verify that cat reloaded successfully
    t_name = "cat";
    task_config_filename = "cat_test.cl";
    verify_event_message = "Successfully reloaded task \"" + t_name + "\".";
    verify_event_type = lts::EventType::INFO;
    matching_event_msg = false;
    // Look through all events and see if one matches the verification event message
    for(size_t i = 0; i < e->get_n_events(); i++){
        ret_event = e->get_event_at(i);
        if(ret_event.get_message().find(verify_event_message) != std::string::npos){
            matching_event_msg = true;
            break;
        }
    }
    assert(matching_event_msg);
    assert(ret_event.get_type() == verify_event_type);
    assert(ret_event.get_event_time() == time_now);

    // Verify that ls reloaded successfully
    t_name = "ls";
    task_config_filename = "ls_test.cl";
    verify_event_message = "Successfully reloaded task \"" + t_name + "\".";
    verify_event_type = lts::EventType::INFO;
    matching_event_msg = false;
    // Look through all events and see if one matches the verification event message
    for(size_t i = 0; i < e->get_n_events(); i++){
        ret_event = e->get_event_at(i);
        if(ret_event.get_message().find(verify_event_message) != std::string::npos){
            matching_event_msg = true;
            break;
        }
    }
    assert(matching_event_msg);
    assert(ret_event.get_type() == verify_event_type);
    assert(ret_event.get_event_time() == time_now);

    // Verify that ZZZTestTask failed to reload
    t_name = "ZZZTestTask";
    task_config_filename = "ZZZTestTask.cl";
    verify_event_message = "The task file configuration file \"" + task_config_filename + 
                            "\" corresponding to task \"" + t_name +"\" could not be found.";
    verify_event_type = lts::EventType::ERROR;
    matching_event_msg = false;
    // Look through all events and see if one matches the verification event message
    for(size_t i = 0; i < e->get_n_events(); i++){
        ret_event = e->get_event_at(i);
        if(ret_event.get_message().find(verify_event_message) != std::string::npos){
            matching_event_msg = true;
            break;
        }
    }
    assert(matching_event_msg);
    assert(ret_event.get_type() == verify_event_type);
    assert(ret_event.get_event_time() == time_now);

    s->Scheduler_delete();
    e->EventReporter_delete();
    
    std::cout << ">> Scheduler_reload_all_tasks: 4 done" << std::endl;
    return 0;
}


int test5(lts::Scheduler* s, lts::EventReporter* e){
    // TEST 5: try to reload all tasks with an invalid attribute inside one of the configuration files
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
    bool matching_event_msg;
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
    s->load_all_tasks();

    assert(s->get_n_tasks() == 3);
    assert(e->get_n_events() == 3);
    
    remove(("tasks/" + task_config_filename).c_str());

    // Create temporary task with invalid attribute
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

    s->reload_all_tasks();

    assert(s->get_n_tasks() == 3);
    assert(e->get_n_events() == 6);

    // Verify that cat reloaded successfully
    t_name = "cat";
    task_config_filename = "cat_test.cl";
    verify_event_message = "Successfully reloaded task \"" + t_name + "\".";
    verify_event_type = lts::EventType::INFO;
    matching_event_msg = false;
    // Look through all events and see if one matches the verification event message
    for(size_t i = 0; i < e->get_n_events(); i++){
        ret_event = e->get_event_at(i);
        if(ret_event.get_message().find(verify_event_message) != std::string::npos){
            matching_event_msg = true;
            break;
        }
    }
    assert(matching_event_msg);
    assert(ret_event.get_type() == verify_event_type);
    assert(ret_event.get_event_time() == time_now);

    // Verify that ls reloaded successfully
    t_name = "ls";
    task_config_filename = "ls_test.cl";
    verify_event_message = "Successfully reloaded task \"" + t_name + "\".";
    verify_event_type = lts::EventType::INFO;
    matching_event_msg = false;
    // Look through all events and see if one matches the verification event message
    for(size_t i = 0; i < e->get_n_events(); i++){
        ret_event = e->get_event_at(i);
        if(ret_event.get_message().find(verify_event_message) != std::string::npos){
            matching_event_msg = true;
            break;
        }
    }
    assert(matching_event_msg);
    assert(ret_event.get_type() == verify_event_type);
    assert(ret_event.get_event_time() == time_now);

    // Verify that ZZZTestTask failed to reload
    t_name = "ZZZTestTask";
    task_config_filename = "ZZZTestTask.cl";
    t_frequency = "Anything";
    verify_event_message = "An invalid frequency value of \"" + t_frequency + 
                           "\" was specified in the configuration file \"" +
                           task_config_filename + "\".";
    verify_event_type = lts::EventType::ERROR;
    matching_event_msg = false;
    // Look through all events and see if one matches the verification event message
    for(size_t i = 0; i < e->get_n_events(); i++){
        ret_event = e->get_event_at(i);
        if(ret_event.get_message().find(verify_event_message) != std::string::npos){
            matching_event_msg = true;
            break;
        }
    }
    assert(matching_event_msg);
    assert(ret_event.get_type() == verify_event_type);
    assert(ret_event.get_event_time() == time_now);

    remove(("tasks/" + task_config_filename).c_str());

    s->Scheduler_delete();
    e->EventReporter_delete();
    
    std::cout << ">> Scheduler_reload_all_tasks: 5 done" << std::endl;
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