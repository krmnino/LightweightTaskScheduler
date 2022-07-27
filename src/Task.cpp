#include <unistd.h>
#include <array>
#include <memory>

#include "Task.hpp"

namespace BTS{
Task::Task(){
    
}

Task::Task(std::string title, std::string script_path){
    this->title = title;
    this->script_path = script_path;
    this->output = "";
}

Task::~Task() {}

void Task::launch(){
    pid_t pid = fork();
    if(pid < 0){
        throw std::runtime_error("fork() failed!");
    }
    else if(pid == 0){
        std::array<char, 128> buffer;
        std::string result;
        std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(this->script_path.c_str(), "r"), pclose);
        if (!pipe) {
            throw std::runtime_error("popen() failed!");
        }
        while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
            this->output += buffer.data();
        }
    }
    this->pid = pid;
}
} // namespace BTS