#include <assert.h>
#include <iostream>
#include <filesystem>
#include <fstream>

#include "../src/Task.hpp"
#include "../src/Scheduler.hpp"
#include "../src/EventReporter.hpp"

lts::Scheduler* lts::Scheduler::scheduler_ptr = nullptr;
lts::EventReporter* lts::EventReporter::event_reporter_ptr = nullptr;

int test1(lts::Scheduler* s, lts::EventReporter* e){
    // TEST 1: load tasks from tasks directory
    // Tasks to be loaded: cat_test.cl and ls_test.cl
    // Validate tasks' name, description, script name, frequency, and output
    time_t time_now;
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
    std::time(&time_now);
    
    assert(s->get_n_tasks() == 2);
    assert(e->get_n_events() == 2);

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
    verify_event_message = "Successfully loaded task \"cat\" from \"cat_test.cl\".";
    verify_event_type = lts::EventType::INFO;
    assert(ret_event.get_message() == verify_event_message);
    assert(ret_event.get_type() == verify_event_type);
    assert(ret_event.get_event_time() == time_now);
    
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
    verify_event_message = "Successfully loaded task \"ls\" from \"ls_test.cl\".";
    verify_event_type = lts::EventType::INFO;
    assert(ret_event.get_message() == verify_event_message);
    assert(ret_event.get_type() == verify_event_type);
    assert(ret_event.get_event_time() == time_now);

    s->Scheduler_delete();
    e->EventReporter_delete();

    std::cout << ">> Scheduler_load_all_tasks: 1 done" << std::endl;
    return 0;
}


int test2(lts::Scheduler* s, lts::EventReporter* e){
    // TEST 2: try to load task from directory when tasks directory does not exist
    time_t time_now;
    std::string original_dir_name = "tasks/";
    std::string rename_dir_name = "original_tasks/";
    lts::Event ret_event;
    std::string verify_event_message;
    lts::EventType verify_event_type;

    e->EventReporter_init();
    s->Scheduler_init(e);

    // Temporarily change tasks directory name so the Scheduler can't find it
    rename(original_dir_name.c_str(), rename_dir_name.c_str());

    s->obtain_exec_path();
    s->load_all_tasks();
    std::time(&time_now);

    assert(s->get_n_tasks() == 0);
    assert(e->get_n_events() == 1);
    ret_event = e->get_event_at(0);
    verify_event_message = "Could not find tasks directory.";
    verify_event_type = lts::EventType::ERROR;
    assert(ret_event.get_message() == verify_event_message);
    assert(ret_event.get_type() == verify_event_type);
    assert(ret_event.get_event_time() == time_now);

    // Rename it back to tasks
    rename(rename_dir_name.c_str(), original_dir_name.c_str());
    
    s->Scheduler_delete();
    e->EventReporter_delete();
    
    std::cout << ">> Scheduler_load_all_tasks: 2 done" << std::endl;
    return 0;
}


int test3(lts::Scheduler* s, lts::EventReporter* e){
    // TEST 3: try to load task from directory when scripts directory does not exist
    time_t time_now;
    std::string original_scripts_dir_name = "scripts/";
    std::string rename_scripts_dir_name = "original_scripts/";
    lts::Event ret_event;
    std::string verify_event_message;
    lts::EventType verify_event_type;

    e->EventReporter_init();
    s->Scheduler_init(e);
    
    // Temporarily change tasks directory name so the Scheduler can't find it
    rename(original_scripts_dir_name.c_str(), rename_scripts_dir_name.c_str());

    s->obtain_exec_path();
    s->load_all_tasks();
    std::time(&time_now);

    assert(s->get_n_tasks() == 0);
    assert(e->get_n_events() == 1);
    ret_event = e->get_event_at(0);
    verify_event_message = "Could not find scripts directory.";
    verify_event_type = lts::EventType::ERROR;
    assert(ret_event.get_message() == verify_event_message);
    assert(ret_event.get_type() == verify_event_type);
    assert(ret_event.get_event_time() == time_now);

    // Rename it back to tasks
    rename(rename_scripts_dir_name.c_str(), original_scripts_dir_name.c_str());

    s->Scheduler_delete();
    e->EventReporter_delete();
    
    std::cout << ">> Scheduler_load_all_tasks: 3 done" << std::endl;
    return 0;
}


int test4(lts::Scheduler* s, lts::EventReporter* e){
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
    lts::Event ret_event;
    std::string verify_event_message;
    lts::EventType verify_event_type;

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
    s->load_all_tasks();
    std::time(&time_now);

    assert(s->get_n_tasks() == 2);
    assert(e->get_n_events() == 3);
    ret_event = e->get_event_at(1);
    verify_event_type = lts::EventType::ERROR;
    verify_event_message = "The configuration file \"ZZZTestTask.cl\" specifies a datetime value of";
    assert(ret_event.get_message().find(verify_event_message) != std::string::npos);
    verify_event_message = "that is in the past.";
    assert(ret_event.get_message().find(verify_event_message) != std::string::npos);
    assert(ret_event.get_type() == verify_event_type);
    assert(ret_event.get_event_time() == time_now);

    s->Scheduler_delete();
    e->EventReporter_delete();

    remove(task_path_filename.c_str());
    
    std::cout << ">> Scheduler_load_all_tasks: 4 done" << std::endl;
    return 0;
}


int test5(lts::Scheduler* s, lts::EventReporter* e){
    // TEST 5: generate task with duplicate Name and attempt to load it
    time_t time_now;
    std::string task_path_filename;
    std::string task_filename;
    std::string task_name;
    cl::Config* c;
    lts::Event ret_event;
    std::string verify_event_message;
    lts::EventType verify_event_type;

    // Create temporary task
    c = new cl::Config();
    task_path_filename = "tasks/ZZZTestTask.cl";
    task_filename = "ZZZTestTask.cl";
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
    s->load_all_tasks();
    std::time(&time_now);

    assert(s->get_n_tasks() == 2);
    assert(e->get_n_events() == 3);
    ret_event = e->get_event_at(1);
    verify_event_message = "A task with the name \"cat\" already exists in the scheduler.";
    verify_event_type = lts::EventType::ERROR;
    assert(ret_event.get_message().find(verify_event_message) != std::string::npos);
    assert(ret_event.get_type() == verify_event_type);
    assert(ret_event.get_event_time() == time_now);

    s->Scheduler_delete();
    e->EventReporter_delete();

    remove(task_path_filename.c_str());
    
    std::cout << ">> Scheduler_load_all_tasks: 5 done" << std::endl;
    return 0;
}


int test6(lts::Scheduler* s, lts::EventReporter* e){
    // TEST 6: generate task temporary task with invalid configuration file (missing semicolons)
    std::ofstream temp_task;
    std::string temp_task_contents;
    std::string task_path_filename;
    std::string task_filename;
    std::string task_name;
    lts::Event ret_event;
    bool matching_event_msg;
    time_t time_now;
    std::string verify_event_message;
    lts::EventType verify_event_type;

    // Create temporary task
    task_path_filename = "tasks/ZZZTestTask.cl";
    temp_task.open(task_path_filename);
    temp_task_contents += "Name = cat\n";
    temp_task_contents += "Description = A short description\n";
    temp_task_contents += "ScriptFilename = cat_test.sh\n";
    temp_task_contents += "Frequency = Daily\n";
    temp_task_contents += "Datetime = 23:59:59\n";
    temp_task << temp_task_contents;
    temp_task.close();

    e->EventReporter_init();
    s->Scheduler_init(e);

    s->obtain_exec_path();
    s->load_all_tasks();
    std::time(&time_now);

    assert(s->get_n_tasks() == 2);
    assert(e->get_n_events() == 3);
    // Verify that ls reloaded successfully
    verify_event_message = "Failed to parse \"ZZZTestTask.cl\": Missing semicolon in config file.";
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

    remove(task_path_filename.c_str());
    
    std::cout << ">> Scheduler_load_all_tasks: 6 done" << std::endl;
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