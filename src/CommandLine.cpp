#include "CommandLine.hpp"

namespace ts{

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
        this->verb_check(split_cmd_input);
    }
    else if(split_cmd_input[0] == "remove"){
        this->verb_remove(split_cmd_input);
    }
    else if(split_cmd_input[0] == "load"){
        this->verb_load(split_cmd_input);
    }
    else if(split_cmd_input[0] == "update"){
        this->verb_update(split_cmd_input);
    }
    else{
        std::cout << "[ERROR]: unrecognized command. Entered: " << this->cmd_input << std::endl;
    }
}

void CommandLine::verb_check(std::vector<std::string>& split_cmd_input){
    std::string event_message;
    if(split_cmd_input.size() <= 1){
        event_message = "The \"check\" verb requires at least 1 argument. Issue the command \"check help\" for options." ;
        this->event_reporter_ptr->log_event(EventType::WARNING, event_message);
        #ifndef SILENT
        this->event_reporter_ptr->publish_last_event();
        #endif
    }
    std::string option = split_cmd_input[1];
    if(option == "registry"){
        if(split_cmd_input.size() != 2){
            event_message = "The command \"check registry\" does not take any additional arguments." ;
            this->event_reporter_ptr->log_event(EventType::WARNING, event_message);
            #ifndef SILENT
            this->event_reporter_ptr->publish_last_event();
            #endif
        }
        else{
            this->scheduler_ptr->display_registry();
        }
    }
    else if(option == "task"){
        if(split_cmd_input.size() != 3){
            event_message = "The command \"check task <task_name>\" does not take any additional arguments." ;
            this->event_reporter_ptr->log_event(EventType::WARNING, event_message);
            #ifndef SILENT
            this->event_reporter_ptr->publish_last_event();
            #endif
            return;
        }
        else{
            this->scheduler_ptr->display_task(split_cmd_input[2]);
        }
    }
    else if(option == "status"){
        if(split_cmd_input.size() != 2){
            std::cout << "incorrect args number" << std::endl;
            return;
        }
    }
    else{
        std::cout << "incorrect args number" << std::endl;
    }
}

void CommandLine::verb_remove(std::vector<std::string>& split_cmd_input){
    if(split_cmd_input.size() <= 1){
        std::cout << "incorrect args number" << std::endl;
        return;
    }
}

void CommandLine::verb_load(std::vector<std::string>& split_cmd_input){
    if(split_cmd_input.size() <= 1){
        std::cout << "incorrect args number" << std::endl;
        return;
    }
    std::string option = split_cmd_input[1];
}

void CommandLine::verb_update(std::vector<std::string>& split_cmd_input){
    if(split_cmd_input.size() <= 1){
        std::cout << "incorrect args number" << std::endl;
        return;
    }
    std::string option = split_cmd_input[1];
}

void CommandLine::verb_help(std::vector<std::string>& split_cmd_input){
    if(split_cmd_input.size() != 1){
        std::cout << "incorrect args number" << std::endl;
        return;
    }
}

void CommandLine::CommandLine_init(EventReporter* er_ptr, Scheduler* s_ptr){
    this->cmds_issued = 0;
    this->max_cmd_history = 100;
    this->cmd_input = "";
    this->running_cmd = true;
    // Link Event Reporter to Command Line
    this->event_reporter_ptr = er_ptr;
    // Link Scheduler to Command Line
    this->scheduler_ptr = s_ptr;
}

void CommandLine::CommandLine_delete(void){
    this->cmd_history.clear();
    this->max_cmd_history = 0;
    this->cmds_issued = 0;
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

} // namespace ts