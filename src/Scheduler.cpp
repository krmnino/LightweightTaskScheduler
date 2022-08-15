#include <filesystem>

#include "Scheduler.hpp"

namespace ts{

Scheduler::Scheduler(std::string& top_level_dir, std::string& tasks_dir, std::string& scripts_dir){
    this->top_level_dir = top_level_dir;
    this->tasks_dir = tasks_dir;
    this->scripts_dir = scripts_dir;

    cl::Config* task_config;
    bool valid_task;
    std::string task_name;
    std::string task_description;
    std::string task_script_name;
    std::string task_frequency;
    std::string task_execution_datetime;
    Task* t;
    for(const auto & file : std::filesystem::directory_iterator(this->top_level_dir + this->tasks_dir)){
        task_config = new cl::Config(file.path());
        if(ts::validate_task_parms(task_config, this->top_level_dir + this->scripts_dir) != TaskValidate::OK){
            std::cout << "invalid config" << std::endl;
        }
        task_name = task_config->get_value("Name")->get_data<std::string>();
        task_description = task_config->get_value("Description")->get_data<std::string>();
        task_frequency = task_config->get_value("Frequency")->get_data<std::string>();
        if(task_config->key_exists("Datetime")){
            task_execution_datetime = task_frequency = task_config->get_value("Datetime")->get_data<std::string>();
        }
        delete task_config;
        
        if(task_frequency == "Hourly"){
            t = new Task(task_name, task_description, task_frequency, task_frequency);
        }
        else{
            t = new Task(task_name, task_description, task_frequency, task_frequency, task_execution_datetime);
        }
        delete t;
    }
}

Scheduler::Scheduler(){
    this->top_level_dir = "";
    this->tasks_dir = "";
    this->scripts_dir = "";
}

Scheduler::~Scheduler(){
    // delete tasks from task registry
}

void Scheduler::load_task(){

}

void Scheduler::run(){
    std::string input;
    while(true){
        std::cout << ">> ";
        std::cin >> input;
        if(input == "exit"){
            break;
        }
        else if(input == "help"){
            break;
        }
    }
}

void Scheduler::help(){
    std::cout << "exit: Close the program." << std::endl;
    std::cout << "help: Display this menu." << std::endl;
}

} // namespace ts