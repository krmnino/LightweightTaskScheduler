#include <assert.h>
#include <iostream>

#include "../src/Task.hpp"
#include "../src/Scheduler.hpp"

ts::Scheduler* ts::Scheduler::scheduler_ptr = nullptr;

int test1(){
    // TEST 1: testing Task constructor Task(std::string, std::string, std::string, std::string, std::string)
    // Testing methods 
    // get_name()
    // get_description()
    // get_script_name()
    // get_frequency()

    std::string t_name = "Task Name";
    std::string t_description = "A short description for this task";
    std::string t_script_name = "cat_test.sh";
    std::string t_frequency = "Hourly";
    std::string t_input_execution_datetime = "12:00:00"; // ignored because Task is hourly

    ts::Task* t = new ts::Task(t_name, t_description, t_script_name, t_frequency, t_input_execution_datetime);
    
    assert(t->get_name() == "Task Name");
    assert(t->get_description() == "A short description for this task");
    assert(t->get_script_filename() == "cat_test.sh");
    assert(t->get_frequency() == "Hourly");
    assert(t->get_status() == ts::TaskStatus::QUEUED);

    delete t;

    std::cout << ">> Task_constructor: Test 1 done" << std::endl;
    return 0;
}


int test2(){
    // TEST 2: testing Task constructor Task(std::string, std::string, std::string, std::string)
    // Testing methods 
    // get_name()
    // get_description()
    // get_script_name()
    // get_frequency()

    std::string t_name = "Task Name";
    std::string t_description = "A short description for this task";
    std::string t_script_name = "cat_test.sh";
    std::string t_frequency = "Hourly";

    ts::Task* t = new ts::Task(t_name, t_description, t_script_name, t_frequency);
    
    assert(t->get_name() == "Task Name");
    assert(t->get_description() == "A short description for this task");
    assert(t->get_script_filename() == "cat_test.sh");
    assert(t->get_frequency() == "Hourly");
    assert(t->get_status() == ts::TaskStatus::QUEUED);

    delete t;

    std::cout << ">> Task_constructor: Test 2 done" << std::endl;
    return 0;
}


int main(){
    test1();
    test2();
}