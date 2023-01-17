#include "CommandLine.hpp"

namespace ts{

void CommandLine::CommandLine_init(void){
    this->cmds_issued = 0;
    this->max_cmd_history = 100;
    this->cmd_input = "";
    this->running_cmd = true;
}

void CommandLine::CommandLine_delete(void){
    delete command_line_ptr;
}

void CommandLine::start(void){
    while(this->running_cmd){
        std::cout << ">> ";
        std::getline(std::cin, this->cmd_input);
        if(this->cmd_input.length() == 0){
            continue;
        }
        this->parse_command();
    }
}

void CommandLine::parse_command(void){
    size_t base_idx = 0;
    std::vector<std::string> split_cmd_input;
    for (size_t i = 0; i < this->cmd_input.length(); i++) {
        if (this->cmd_input.at(i) == ' ') {
            split_cmd_input.push_back(this->cmd_input.substr(base_idx, i - base_idx));
            base_idx = i + 1;
        }
        else if (i == this->cmd_input.length() - 1) {
            split_cmd_input.push_back(this->cmd_input.substr(base_idx, i + 1 - base_idx));
            base_idx = i + 1;
        }
    }

    if(split_cmd_input[0] == "close" && split_cmd_input.size() == 1){
        this->running_cmd = false;
        std::cout << "[INFO]: ending Light-weight Task Scheduler process..." <<  std::endl;
    }
    else if(split_cmd_input[0] == "check"){
        // TODO: call check method
        std::cout << "CHECK()" <<  std::endl;
    }
    else if(split_cmd_input[0] == "delete"){
        // TODO: call delete method 
        std::cout << "DELETE()" <<  std::endl;
    }
    else if(split_cmd_input[0] == "load"){
        // TODO: call load method 
        std::cout << "LOAD()" <<  std::endl;
    }
    else if(split_cmd_input[0] == "update"){
        // TODO: call update method 
        std::cout << "UPDATE()" <<  std::endl;
    }
    else{
        std::cout << "[ERROR]: unrecognized command. Entered: " << this->cmd_input << std::endl;
    }
}

} // namespace ts