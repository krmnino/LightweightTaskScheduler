#include <filesystem>

#include "Scheduler.hpp"

namespace ts{

Scheduler::Scheduler(std::string& top_level_dir, std::string& tasks_dir, std::string& scripts_dir){
    this->top_level_dir = top_level_dir;
    this->tasks_dir = tasks_dir;
    this->scripts_dir = scripts_dir;

    cl::Config* task_config;
    bool valid_task;
    for(const auto & file : std::filesystem::directory_iterator(this->top_level_dir + this->tasks_dir)){
        task_config = new cl::Config(file.path());
        if(ts::validate_task_parms(task_config, this->top_level_dir + this->scripts_dir) != TaskValidate::OK)
            throw std::runtime_error("invalid config");
        delete task_config;
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