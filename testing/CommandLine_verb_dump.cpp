#include <assert.h>
#include <iostream>
#include <fstream>
#include <unistd.h>

#include "../src/Scheduler.hpp"
#include "../src/EventReporter.hpp"
#include "../src/CommandLine.hpp"

lts::Scheduler* lts::Scheduler::scheduler_ptr = nullptr;
lts::EventReporter* lts::EventReporter::event_reporter_ptr = nullptr;
lts::CommandLine* lts::CommandLine::command_line_ptr = nullptr;

int test1(lts::EventReporter* e, lts::Scheduler* s, lts::CommandLine* c){
    // TEST 1: Issue the command "dump" and verify event warning.
    std::string ret_cmd_output;
    lts::Event ret_event;
    time_t time_now;

    e->EventReporter_init();
    s->Scheduler_init(e);
    c->CommandLine_init(e, s);

    s->obtain_exec_path();
    s->load_all_tasks();

    c->set_cmd_input("dump");
    c->parse_command();
    ret_event = e->get_last_event();
    std::time(&time_now);

    assert(s->get_n_tasks() == 2);
    assert(e->get_n_events() == 3);
    assert(c->get_cmds_issued() == 0);
    assert(ret_event.get_event_time() == time_now);
    assert(ret_event.get_type() == lts::EventType::WARNING);
    assert(ret_event.get_message() == "The \"dump\" verb requires at least 1 argument. Issue the command \"help dump\" for options.");

    c->CommandLine_delete();
    s->Scheduler_delete();
    e->EventReporter_delete();

    std::cout << ">> CommandLine_verb_dump: 1 done" << std::endl;
    return 0;
}


int test2(lts::EventReporter* e, lts::Scheduler* s, lts::CommandLine* c){
    // TEST 2: Issue the command "dump output ls invalid" and verify event warning.
    std::string ret_cmd_output;
    lts::Event ret_event;
    time_t time_now;

    e->EventReporter_init();
    s->Scheduler_init(e);
    c->CommandLine_init(e, s);

    s->obtain_exec_path();
    s->load_all_tasks();

    c->set_cmd_input("dump output ls invalid");
    c->parse_command();
    ret_event = e->get_last_event();
    std::time(&time_now);

    assert(s->get_n_tasks() == 2);
    assert(e->get_n_events() == 3);
    assert(c->get_cmds_issued() == 0);
    assert(ret_event.get_event_time() == time_now);
    assert(ret_event.get_type() == lts::EventType::WARNING);
    assert(ret_event.get_message() == "The command \"dump output <name>\" does not take any additional arguments.");

    c->CommandLine_delete();
    s->Scheduler_delete();
    e->EventReporter_delete();

    std::cout << ">> CommandLine_verb_dump: 2 done" << std::endl;
    return 0;
}


int test3(lts::EventReporter* e, lts::Scheduler* s, lts::CommandLine* c){
    // TEST 3: Dump output of one task by issuing the command "dump output ZZZTestTask".
    std::string ret_cmd_output;
    lts::Event ret_event;
    std::string task_name;
    std::string task_filename;
    std::string task_path_filename;
    time_t time_now;
    std::tm struct_time_now;
    std::string years;
    std::string months;
    std::string days;
    std::string hours;
    std::string minutes;
    std::string seconds;
    cl::Config* config;
    std::ifstream verify_output_file;
    std::string verify_output;
    std::string line;
    std::string output_file_contents;
    std::string task_output_filename;
    std::string verify_event_message;

    time_now = std::time(&time_now);

    // Add 2 seconds to current time
    time_now = time_now + 1;
    
    // std::tm to time_t
    struct_time_now = *std::gmtime(&time_now);

    hours = (struct_time_now.tm_hour < 10) ? 
             "0" + std::to_string(struct_time_now.tm_hour) :
             std::to_string(struct_time_now.tm_hour);
    minutes = (struct_time_now.tm_min < 10) ? 
               "0" + std::to_string(struct_time_now.tm_min) :
               std::to_string(struct_time_now.tm_min);
    seconds = (struct_time_now.tm_sec < 10) ? 
               "0" + std::to_string(struct_time_now.tm_sec) :
               std::to_string(struct_time_now.tm_sec);

    // Create temporary task
    config = new cl::Config();
    task_name = "ZZZTestTask";
    task_filename = "ZZZTestTask.cl";
    task_path_filename = "tasks/ZZZTestTask.cl";
    config->add_entry("Name", task_name);
    config->add_entry("Description", "A short description");
    config->add_entry("ScriptFilename", "cat_test.sh");
    config->add_entry("Frequency", "Daily");
    config->add_entry("Datetime", hours + ":" + minutes + ":" + seconds);
    config->save_config(task_path_filename);
    delete config;

    e->EventReporter_init();
    s->Scheduler_init(e);
    c->CommandLine_init(e, s);

    s->obtain_exec_path();
    s->load_task(task_filename);

    // Sleep for 2 seconds to let task run
    sleep(2); 

    c->set_cmd_input("dump output ZZZTestTask");
    c->parse_command();

    time_now = std::time(&time_now);

    // Add timezone offset to current time
    time_now += (TIMEZONE * 60 * 60);
    
    // time_t to std::tm
    struct_time_now = *std::gmtime(&time_now);

    years = std::to_string(1900 + struct_time_now.tm_year);
    months = (struct_time_now.tm_mon + 1 < 10) ? 
              "0" + std::to_string(struct_time_now.tm_mon + 1) :
              std::to_string(struct_time_now.tm_mon + 1);  
    days = (struct_time_now.tm_mday < 10) ? 
            "0" + std::to_string(struct_time_now.tm_mday) :
            std::to_string(struct_time_now.tm_mday);
    hours = (struct_time_now.tm_hour < 10) ? 
             "0" + std::to_string(struct_time_now.tm_hour) :
             std::to_string(struct_time_now.tm_hour);
    minutes = (struct_time_now.tm_min < 10) ? 
               "0" + std::to_string(struct_time_now.tm_min) :
               std::to_string(struct_time_now.tm_min);
    seconds = (struct_time_now.tm_sec < 10) ? 
               "0" + std::to_string(struct_time_now.tm_sec) :
               std::to_string(struct_time_now.tm_sec);

    // Get current time to verify event
    time_now = std::time(&time_now);

    task_output_filename += task_name + "_";
    task_output_filename += years + "-" + months + "-" + days + "_" + hours + "-" + minutes + "-" + seconds;
    task_output_filename += ".dat";
    verify_event_message = "Saved task \"" + task_name + "\" output in \"dumps/" + task_output_filename + "\".";
    ret_event = e->get_last_event();

    assert(s->get_n_tasks() == 1);
    assert(e->get_n_events() == 4);
    assert(c->get_cmds_issued() == 1);
    assert(ret_event.get_event_time() == time_now);
    assert(ret_event.get_type() == lts::EventType::INFO);
    assert(ret_event.get_message() == verify_event_message);

    // Read output file and verify its contents
    verify_output_file.open("dumps/" + task_output_filename);
    verify_output = "ls -l";
    while (std::getline(verify_output_file, line)){
        output_file_contents += line;
    }
    verify_output_file.close();
    assert(output_file_contents == verify_output);

    c->CommandLine_delete();
    s->Scheduler_delete();
    e->EventReporter_delete();

    remove(("dumps/" + task_output_filename).c_str());
    remove(task_path_filename.c_str());

    std::cout << ">> CommandLine_verb_dump: 3 done" << std::endl;
    return 0;
}


int test4(lts::EventReporter* e, lts::Scheduler* s, lts::CommandLine* c){
    // TEST 4: Issue the command "dump output invalid" and verify event error.
    std::string ret_cmd_output;
    lts::Event ret_event;
    time_t time_now;

    e->EventReporter_init();
    s->Scheduler_init(e);
    c->CommandLine_init(e, s);

    s->obtain_exec_path();
    s->load_all_tasks();

    c->set_cmd_input("dump output invalid");
    c->parse_command();
    ret_event = e->get_last_event();
    std::time(&time_now);

    assert(s->get_n_tasks() == 2);
    assert(e->get_n_events() == 3);
    assert(c->get_cmds_issued() == 1);
    assert(ret_event.get_event_time() == time_now);
    assert(ret_event.get_type() == lts::EventType::ERROR);
    assert(ret_event.get_message() == "The task \"invalid\" does not exist in the scheduler.");

    c->CommandLine_delete();
    s->Scheduler_delete();
    e->EventReporter_delete();

    std::cout << ">> CommandLine_verb_dump: 4 done" << std::endl;
    return 0;
}


int test5(lts::EventReporter* e, lts::Scheduler* s, lts::CommandLine* c){
    // TEST 5: Issue the command "dump outputs" and verify event warning.
    std::string ret_cmd_output;
    lts::Event ret_event;
    time_t time_now;

    e->EventReporter_init();
    s->Scheduler_init(e);
    c->CommandLine_init(e, s);

    s->obtain_exec_path();
    s->load_all_tasks();

    c->set_cmd_input("dump outputs");
    c->parse_command();
    ret_event = e->get_last_event();
    std::time(&time_now);

    assert(s->get_n_tasks() == 2);
    assert(e->get_n_events() == 3);
    assert(c->get_cmds_issued() == 0);
    assert(ret_event.get_event_time() == time_now);
    assert(ret_event.get_type() == lts::EventType::WARNING);
    assert(ret_event.get_message() == "The command \"dump outputs <name1, name2, ...>\" requires at least one task name.");

    c->CommandLine_delete();
    s->Scheduler_delete();
    e->EventReporter_delete();

    std::cout << ">> CommandLine_verb_dump: 5 done" << std::endl;
    return 0;
}


int test6(lts::EventReporter* e, lts::Scheduler* s, lts::CommandLine* c){
    // TEST 6: Dump output of two tasks by issuing the command "dump outputs ZZZTestTask1 ZZZTestTask2".
    std::string ret_cmd_output;
    lts::Event ret_event;
    std::string task_name_1;
    std::string task_filename_1;
    std::string task_path_filename_1;
    std::string task_name_2;
    std::string task_filename_2;
    std::string task_path_filename_2;
    time_t time_now;
    std::tm struct_time_now;
    std::string years;
    std::string months;
    std::string days;
    std::string hours;
    std::string minutes;
    std::string seconds;
    cl::Config* config;
    std::ifstream verify_output_file;
    std::string verify_output;
    std::string line;
    std::string output_file_contents;
    bool matching_event_msg;
    std::string task_output_filename_1;
    std::string task_output_filename_2;
    std::string verify_event_message;
    lts::EventType verify_event_type;

    time_now = std::time(&time_now);

    // Add 2 seconds to current time
    time_now = time_now + 1;
    
    // std::tm to time_t
    struct_time_now = *std::gmtime(&time_now);

    hours = (struct_time_now.tm_hour < 10) ? 
             "0" + std::to_string(struct_time_now.tm_hour) :
             std::to_string(struct_time_now.tm_hour);
    minutes = (struct_time_now.tm_min < 10) ? 
               "0" + std::to_string(struct_time_now.tm_min) :
               std::to_string(struct_time_now.tm_min);
    seconds = (struct_time_now.tm_sec < 10) ? 
               "0" + std::to_string(struct_time_now.tm_sec) :
               std::to_string(struct_time_now.tm_sec);

    // Create temporary task 1
    config = new cl::Config();
    task_name_1 = "ZZZTestTask1";
    task_filename_1 = "ZZZTestTask1.cl";
    task_path_filename_1 = "tasks/ZZZTestTask1.cl";
    config->add_entry("Name", task_name_1);
    config->add_entry("Description", "A short description");
    config->add_entry("ScriptFilename", "cat_test.sh");
    config->add_entry("Frequency", "Daily");
    config->add_entry("Datetime", hours + ":" + minutes + ":" + seconds);
    config->save_config(task_path_filename_1);
    delete config;

    // Create temporary task 2
    config = new cl::Config();
    task_name_2 = "ZZZTestTask2";
    task_filename_2 = "ZZZTestTask2.cl";
    task_path_filename_2 = "tasks/ZZZTestTask2.cl";
    config->add_entry("Name", task_name_2);
    config->add_entry("Description", "A short description");
    config->add_entry("ScriptFilename", "cat_test.sh");
    config->add_entry("Frequency", "Daily");
    config->add_entry("Datetime", hours + ":" + minutes + ":" + seconds);
    config->save_config(task_path_filename_2);
    delete config;

    e->EventReporter_init();
    s->Scheduler_init(e);
    c->CommandLine_init(e, s);

    s->obtain_exec_path();
    s->load_task(task_filename_1);
    s->load_task(task_filename_2);

    // Sleep for 2 seconds to let task run
    sleep(2); 

    c->set_cmd_input("dump outputs ZZZTestTask1 ZZZTestTask2");
    c->parse_command();

    time_now = std::time(&time_now);

    // Add timezone offset to current time
    time_now += (TIMEZONE * 60 * 60);
    
    // time_t to std::tm
    struct_time_now = *std::gmtime(&time_now);

    years = std::to_string(1900 + struct_time_now.tm_year);
    months = (struct_time_now.tm_mon + 1 < 10) ? 
              "0" + std::to_string(struct_time_now.tm_mon + 1) :
              std::to_string(struct_time_now.tm_mon + 1);  
    days = (struct_time_now.tm_mday < 10) ? 
            "0" + std::to_string(struct_time_now.tm_mday) :
            std::to_string(struct_time_now.tm_mday);
    hours = (struct_time_now.tm_hour < 10) ? 
             "0" + std::to_string(struct_time_now.tm_hour) :
             std::to_string(struct_time_now.tm_hour);
    minutes = (struct_time_now.tm_min < 10) ? 
               "0" + std::to_string(struct_time_now.tm_min) :
               std::to_string(struct_time_now.tm_min);
    seconds = (struct_time_now.tm_sec < 10) ? 
               "0" + std::to_string(struct_time_now.tm_sec) :
               std::to_string(struct_time_now.tm_sec);

    // Get current time to verify events
    time_now = std::time(&time_now);

    task_output_filename_1 += task_name_1 + "_";
    task_output_filename_1 += years + "-" + months + "-" + days + "_" + hours + "-" + minutes + "-" + seconds;
    task_output_filename_1 += ".dat";
    
    task_output_filename_2 += task_name_2 + "_";
    task_output_filename_2 += years + "-" + months + "-" + days + "_" + hours + "-" + minutes + "-" + seconds;
    task_output_filename_2 += ".dat";

    ret_event = e->get_last_event();

    assert(s->get_n_tasks() == 2);
    assert(e->get_n_events() == 8);
    assert(c->get_cmds_issued() == 1);

    // Verify task event for first event
    verify_event_message = "Saved task \"" + task_name_1 + "\" output in \"dumps/" + task_output_filename_1 + "\".";
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
    
    // Verify task event for second event
    verify_event_message = "Saved task \"" + task_name_2 + "\" output in \"dumps/" + task_output_filename_2 + "\".";
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

    // Read output files and verify the contents of each
    verify_output_file.open("dumps/" + task_output_filename_1);
    verify_output = "ls -l";
    output_file_contents = "";
    while (std::getline(verify_output_file, line)){
        output_file_contents += line;
    }
    verify_output_file.close();
    assert(output_file_contents == verify_output);
    
    verify_output_file.open("dumps/" + task_output_filename_2);
    verify_output = "ls -l";
    output_file_contents = "";
    while (std::getline(verify_output_file, line)){
        output_file_contents += line;
    }
    verify_output_file.close();
    assert(output_file_contents == verify_output);

    c->CommandLine_delete();
    s->Scheduler_delete();
    e->EventReporter_delete();

    remove(("dumps/" + task_output_filename_1).c_str());
    remove(("dumps/" + task_output_filename_2).c_str());
    remove(task_path_filename_1.c_str());
    remove(task_path_filename_2.c_str());

    std::cout << ">> CommandLine_verb_dump: 6 done" << std::endl;
    return 0;
}


int main(int argc, char* argv[]){
    lts::EventReporter* e = lts::EventReporter::EventReporter_get_instance();
    lts::CommandLine* c = lts::CommandLine::CommandLine_get_instance();
    lts::Scheduler* s = lts::Scheduler::Scheduler_get_instance();

    test1(e, s, c);
    test2(e, s, c);
    test3(e, s, c);
    test4(e, s, c);
    test5(e, s, c);
    test6(e, s, c);

    e->EventReporter_end_instance();
    c->CommandLine_end_instance();
    s->Scheduler_end_instance();
}