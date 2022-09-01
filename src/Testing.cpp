#include <assert.h>
#include <iostream>

#include "Task.hpp"

int test1(){
    std::string t_name = "Task Name";
    std::string t_description = "A short description for this task";
    std::string t_script_name = "cat_test.sh";
    std::string t_frequency = "Once";

    ts::Task* t = new ts::Task(t_name, t_description, t_script_name, t_frequency);
    
    assert(t->get_name() == "Task Name");
    assert(t->get_description() == "A short description for this task");
    assert(t->get_script_filename() == "cat_test.sh");
    assert(t->get_frequency() == "Once");

    delete t;

    std::cout << ">> Test 1 done" << std::endl;

    return 0;
}


int test2(){
    std::string t_name = "Task Name";
    std::string t_description = "A short description for this task";
    std::string t_script_name = "cat_test.sh";
    std::string t_frequency = "Hourly";
    std::string t_input_execution_datetime = "12:00:00";

    ts::Task* t = new ts::Task(t_name, t_description, t_script_name, t_frequency, t_input_execution_datetime);
    
    assert(t->get_name() == "Task Name");
    assert(t->get_description() == "A short description for this task");
    assert(t->get_script_filename() == "cat_test.sh");
    assert(t->get_frequency() == "Hourly");
    assert(t->get_input_execution_datetime() == "12:00:00");

    delete t;

    std::cout << ">> Test 2 done" << std::endl;

    return 0;
}


int test3(){
    std::string t_name = "Task Name";
    std::string t_description = "A short description for this task";
    std::string t_script_name = "cat_test.sh";
    std::string t_frequency = "Hourly";
    std::string t_input_execution_datetime = "12:00:00";

    ts::Task* t = new ts::Task(t_name, t_description, t_script_name, t_frequency, t_input_execution_datetime);
    
    std::string execution_datetime_fmt = t->get_execution_datetime_fmt();
    std::string creation_datetime_fmt = t->get_creation_datetime_fmt();
    std::cout << execution_datetime_fmt << std::endl;

    delete t;

    std::cout << ">> Test 3 done" << std::endl;

    return 0;
}


int main(){
    bool all    = true;
    bool t1     = false;
    bool t2     = false;
    bool t3     = false;

    if(t1 || all){
        test1();
    }
    if(t2 || all){
        test2();
    }
    if(t3 || all){
        test3();
    }
}