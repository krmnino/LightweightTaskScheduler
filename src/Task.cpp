#include <unistd.h>
#include <array>
#include <memory>
#include <exception>
#include <filesystem>

#include "Task.hpp"

namespace ts{

Task::Task(std::string name, std::string script_filename, std::string frequency){
    this->name = name;
    this->script_filename = script_filename;
    this->output = "";
}

Task::Task(){}

Task::~Task() {}

void Task::launch(){
    pid_t pid = fork();
    if(pid < 0){
        throw std::runtime_error("fork() failed!");
    }
    else if(pid == 0){
        std::array<char, 128> buffer;
        std::string result;
        std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(this->script_filename.c_str(), "r"), pclose);
        if (!pipe) {
            throw std::runtime_error("popen() failed!");
        }
        while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
            this->output += buffer.data();
        }
    }
    this->pid = pid;
}

std::string Task::get_name(void){
    return this->name;
}

std::string Task::get_description(void){
    return this->description;
}

std::string Task::get_frequency(void){
    return this->frequency;
}

//std::string Task::get_datetime(void){
//    return this->datetime;
//}

std::string Task::get_output(void){
    return this->output;
}

TaskValidate validate_task_parms(cl::Config* task_config, std::string scripts_dir){
    // Check if required fields exist
    if(!task_config->key_exists("Name") ||
       !task_config->key_exists("ScriptFilename") ||
       !task_config->key_exists("Frequency") ||
       !task_config->key_exists("Datetime")){
           return TaskValidate::MISSING_REQUIRED_KEYVALS;
    }
    
    std::string value;

    // Check if script file exists
    value = task_config->get_value("ScriptFilename")->get_data<std::string>();
    if(!std::filesystem::exists(scripts_dir + value)){
        return TaskValidate::SCRIPT_NOT_FOUND;
    }

    // Check if frequency value if valid
    value = task_config->get_value("Frequency")->get_data<std::string>();
    if(value != "Once" || value != "Hourly" || value != "Daily" ||
       value != "Weekly" || value != "Monthly" || value != "Yearly"){
           return TaskValidate::BAD_FREQUENCY_VALUE;
    }

    return TaskValidate::OK;
}

} // namespace ts