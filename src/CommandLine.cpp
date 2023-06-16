#include "CommandLine.hpp"

namespace lts{

void CommandLine::verb_check(std::vector<std::string>& split_cmd_input){
    std::string event_message;
    std::string option;

    if(split_cmd_input.size() <= 1){
        event_message = "The \"check\" verb requires at least 1 argument. Issue the command \"help check\" for options.";
        this->event_reporter_ptr->log_event(EventType::WARNING, event_message);
        #ifndef SILENT
        this->event_reporter_ptr->publish_last_event();
        #endif
        return;
    }
    option = split_cmd_input[1];
    if(option == "registry"){
        if(split_cmd_input.size() != 2){
            event_message = "The command \"check registry\" does not take any additional arguments.";
            this->event_reporter_ptr->log_event(EventType::WARNING, event_message);
            #ifndef SILENT
            this->event_reporter_ptr->publish_last_event();
            #endif
        }
        else{
            this->cmd_output = this->scheduler_ptr->display_registry();
            this->cmds_issued++;
            #ifndef SILENT
            std::cout << this->cmd_output;
            #endif
        }
    }
    else if(option == "task"){
        if(split_cmd_input.size() < 3){
            event_message = "The command \"check task <task_name>\" requires a task name for the third parameter.";
            this->event_reporter_ptr->log_event(EventType::WARNING, event_message);
            #ifndef SILENT
            this->event_reporter_ptr->publish_last_event();
            #endif
        }
        else if(split_cmd_input.size() != 3){
            event_message = "The command \"check task <task_name>\" does not take any additional arguments.";
            this->event_reporter_ptr->log_event(EventType::WARNING, event_message);
            #ifndef SILENT
            this->event_reporter_ptr->publish_last_event();
            #endif
        }
        else{
            this->cmd_output = this->scheduler_ptr->display_task(split_cmd_input[2]);
            this->cmds_issued++;
            #ifndef SILENT
            std::cout << this->cmd_output;
            #endif
        }
    }
    else if(option == "status"){
        if(split_cmd_input.size() != 2){
            event_message = "The command \"check status\" does not take any additional arguments.";
            this->event_reporter_ptr->log_event(EventType::WARNING, event_message);
            #ifndef SILENT
            this->event_reporter_ptr->publish_last_event();
            #endif
        }
        else{
            this->cmd_output = this->scheduler_ptr->display_scheduler_status();
            this->cmds_issued++;
            #ifndef SILENT
            std::cout << this->cmd_output;
            #endif
        }
    }
    else if(option == "output"){
        if(split_cmd_input.size() < 3){
            event_message = "The command \"check output <task_name>\" requires a task name for the third parameter.";
            this->event_reporter_ptr->log_event(EventType::WARNING, event_message);
            #ifndef SILENT
            this->event_reporter_ptr->publish_last_event();
            #endif
        }
        else if(split_cmd_input.size() != 3){
            event_message = "The command \"check output <task_name>\" does not take any additional arguments.";
            this->event_reporter_ptr->log_event(EventType::WARNING, event_message);
            #ifndef SILENT
            this->event_reporter_ptr->publish_last_event();
            #endif
        }
        else{
            this->cmd_output = this->scheduler_ptr->display_task_output(split_cmd_input[2]);
            this->cmds_issued++;
            #ifndef SILENT
            std::cout << this->cmd_output;
            #endif
        }
    }
    else{
        event_message = "An invalid argument was passed for the the \"check\" verb. Issue the command \"help check\" for options.";
        this->event_reporter_ptr->log_event(EventType::WARNING, event_message);
        #ifndef SILENT
        this->event_reporter_ptr->publish_last_event();
        #endif
    }
}

void CommandLine::verb_remove(std::vector<std::string>& split_cmd_input){
    std::string event_message;
    std::string option;

    if(split_cmd_input.size() <= 1){
        event_message = "The \"remove\" verb requires at least 1 argument. Issue the command \"help remove\" for options.";
        this->event_reporter_ptr->log_event(EventType::WARNING, event_message);
        #ifndef SILENT
        this->event_reporter_ptr->publish_last_event();
        #endif
        return;
    }
    option = split_cmd_input[1];
    if(option == "task"){
        if(split_cmd_input.size() != 3){
            event_message = "The command \"remove task <task_name>\" does not take any additional arguments.";
            this->event_reporter_ptr->log_event(EventType::WARNING, event_message);
            #ifndef SILENT
            this->event_reporter_ptr->publish_last_event();
            #endif
        }
        else{
            this->scheduler_ptr->remove_task(split_cmd_input[2]);
            this->cmds_issued++;
        }
    }
    else if(option == "tasks"){
        if(split_cmd_input.size() < 3){
            event_message = "The command \"remove tasks <name1, name2, ...>\" requires at least one task name.";
            this->event_reporter_ptr->log_event(EventType::WARNING, event_message);
            #ifndef SILENT
            this->event_reporter_ptr->publish_last_event();
            #endif
        }
        else{
            for(size_t i = 2; i < split_cmd_input.size(); i++){
                this->scheduler_ptr->remove_task(split_cmd_input[i]);
            }
            this->cmds_issued++;
        }
    }
    else{
        event_message = "An invalid argument was passed for the the \"remove\" verb. Issue the command \"help remove\" for options.";
        this->event_reporter_ptr->log_event(EventType::WARNING, event_message);
        #ifndef SILENT
        this->event_reporter_ptr->publish_last_event();
        #endif
    }
}

void CommandLine::verb_load(std::vector<std::string>& split_cmd_input){
    std::string event_message;
    std::string option;

    if(split_cmd_input.size() <= 1){
        event_message = "The \"load\" verb requires at least 1 argument. Issue the command \"help load\" for options.";
        this->event_reporter_ptr->log_event(EventType::WARNING, event_message);
        #ifndef SILENT
        this->event_reporter_ptr->publish_last_event();
        #endif
        return;
    }
    option = split_cmd_input[1];
    if(option == "task"){
        if(split_cmd_input.size() != 3){
            event_message = "The command \"load task <config_name>\" does not take any additional arguments.";
            this->event_reporter_ptr->log_event(EventType::WARNING, event_message);
            #ifndef SILENT
            this->event_reporter_ptr->publish_last_event();
            #endif
        }
        else{
            this->scheduler_ptr->load_task(split_cmd_input[2]);
            this->cmds_issued++;
        }
    }
    else if(option == "tasks"){
        if(split_cmd_input.size() < 3){
            event_message = "The command \"load tasks <config_name1, config_name2, ...>\" requires at least one task configuration filename.";
            this->event_reporter_ptr->log_event(EventType::WARNING, event_message);
            #ifndef SILENT
            this->event_reporter_ptr->publish_last_event();
            #endif
        }
        else{
            for(size_t i = 2; i < split_cmd_input.size(); i++){
                this->scheduler_ptr->load_task(split_cmd_input[i]);
            }
            this->cmds_issued++;
        }
    }
    else if(option == "all"){
        if(split_cmd_input.size() != 2){
            event_message = "The command \"load all\" does not take any additional arguments.";
            this->event_reporter_ptr->log_event(EventType::WARNING, event_message);
            #ifndef SILENT
            this->event_reporter_ptr->publish_last_event();
            #endif
        }
        else{
            this->scheduler_ptr->load_all_tasks();
            this->cmds_issued++;
        }
    }
    else{
        event_message = "An invalid argument was passed for the the \"load\" verb. Issue the command \"help load\" for options.";
        this->event_reporter_ptr->log_event(EventType::WARNING, event_message);
        #ifndef SILENT
        this->event_reporter_ptr->publish_last_event();
        #endif
    }
}

void CommandLine::verb_reload(std::vector<std::string>& split_cmd_input){
    std::string event_message;
    std::string option;

    if(split_cmd_input.size() <= 1){
        event_message = "The \"reload\" verb requires at least 1 argument. Issue the command \"help reload\" for options.";
        this->event_reporter_ptr->log_event(EventType::WARNING, event_message);
        #ifndef SILENT
        this->event_reporter_ptr->publish_last_event();
        #endif
        return;
    }
    option = split_cmd_input[1];
    if(option == "task"){
        if(split_cmd_input.size() != 3){
            event_message = "The command \"reload task <name>\" does not take any additional arguments.";
            this->event_reporter_ptr->log_event(EventType::WARNING, event_message);
            #ifndef SILENT
            this->event_reporter_ptr->publish_last_event();
            #endif
        }
        else{
            this->scheduler_ptr->reload_task(split_cmd_input[2]);
            this->cmds_issued++;
        }
    }
    else if(option == "tasks"){
        if(split_cmd_input.size() < 3){
            event_message = "The command \"reload tasks <name1, name2, ...>\" requires at least one task name.";
            this->event_reporter_ptr->log_event(EventType::WARNING, event_message);
            #ifndef SILENT
            this->event_reporter_ptr->publish_last_event();
            #endif
        }
        else{
            for(size_t i = 2; i < split_cmd_input.size(); i++){
                this->scheduler_ptr->reload_task(split_cmd_input[i]);
            }
            this->cmds_issued++;
        }
    }
    else if(option == "all"){
        if(split_cmd_input.size() != 2){
            event_message = "The command \"reload all\" does not take any additional arguments.";
            this->event_reporter_ptr->log_event(EventType::WARNING, event_message);
            #ifndef SILENT
            this->event_reporter_ptr->publish_last_event();
            #endif
        }
        else{
            this->scheduler_ptr->reload_all_tasks();
            this->cmds_issued++;
        }
    }
    else{
        event_message = "An invalid argument was passed for the the \"reload\" verb. Issue the command \"help reload\" for options.";
        this->event_reporter_ptr->log_event(EventType::WARNING, event_message);
        #ifndef SILENT
        this->event_reporter_ptr->publish_last_event();
        #endif
    }
}

void CommandLine::verb_help(std::vector<std::string>& split_cmd_input){
    std::string event_message;
    std::string option;
    std::string out_str = "";
    
    if(split_cmd_input.size() == 1){
        out_str += this->help_msg();
        out_str += this->help_check_msg();
        out_str += this->help_remove_msg();
        out_str += this->help_load_msg();
        out_str += this->help_reload_msg();
        this->cmd_output = out_str;
        this->cmds_issued++;
        #ifndef SILENT
        std::cout << this->cmd_output;
        #endif
    }
    else if(split_cmd_input.size() == 2){
        option = split_cmd_input[1];
        if(option == "check"){
            out_str += this->help_check_msg();
            this->cmd_output = out_str;
            this->cmds_issued++;
            #ifndef SILENT
            std::cout << this->cmd_output;
            #endif
        }
        else if(option == "remove"){
            out_str += this->help_remove_msg();
            this->cmd_output = out_str;
            this->cmds_issued++;
            #ifndef SILENT
            std::cout << this->cmd_output;
            #endif
        }
        else if(option == "load"){
            out_str += this->help_load_msg();
            this->cmd_output = out_str;
            this->cmds_issued++;
            #ifndef SILENT
            std::cout << this->cmd_output;
            #endif
        }
        else if(option == "reload"){
            out_str += this->help_reload_msg();
            this->cmd_output = out_str;
            this->cmds_issued++;
            #ifndef SILENT
            std::cout << this->cmd_output;
            #endif
        }
        else{
            event_message = "An invalid argument was passed for the the \"help\" verb. Issue the command \"help\" for options.";
            this->event_reporter_ptr->log_event(EventType::WARNING, event_message);
            #ifndef SILENT
            this->event_reporter_ptr->publish_last_event();
            #endif
        }
    }
    else{
        event_message = "An invalid argument was passed for the the \"help\" verb. Issue the command \"help\" for options.";
        this->event_reporter_ptr->log_event(EventType::WARNING, event_message);
        #ifndef SILENT
        this->event_reporter_ptr->publish_last_event();
        #endif
    }
}

std::string CommandLine::help_msg(void){
    std::string out_str = ""; 
    out_str += "- help: Displays this dialog.\n";
    out_str += "- help check: Displays usage for the \"check\" verb only.\n";
    out_str += "- help remove: Displays usage for the \"remove\" verb only.\n";
    out_str += "- help load: Displays usage for the \"load\" verb only.\n";
    out_str += "- help reload: Displays usage for the \"reload\" verb only.\n";
    out_str += "- close: Terminates the scheduler program.\n";
    return out_str;
}

std::string CommandLine::help_check_msg(void){
    std::string out_str = ""; 
    out_str += "- check registry: Displays relevant information about the tasks loaded in the scheduler.\n";
    out_str += "- check task <task_name>: Displays the full information about the specified task.\n";
    out_str += "- check status: Displays operational information about the scheduler.\n";
    out_str += "- check output <task_name>: Displays output of a specific task.\n";
    return out_str;
}

std::string CommandLine::help_remove_msg(void){
    std::string out_str = ""; 
    out_str += "- remove task <task_name>: Removes the specified task from the scheduler.\n";
    out_str += "- remove tasks <name1, name2, ...>: Remove multiple tasks in scheduler from specified list of task name attributes.\n";
    return out_str;
}

std::string CommandLine::help_load_msg(void){
    std::string out_str = "";
    out_str += "- load task <config_name>: Load task in scheduler from specified configuration filename.\n";
    out_str += "- load tasks <config_name1, config_name2...>: Load multiple tasks in scheduler from specified list of configuration filenames.\n";
    out_str += "- load all: Load all tasks defined in \"tasks\" directory.\n";
    return out_str;
}

std::string CommandLine::help_reload_msg(void){
    std::string out_str = "";
    out_str += "- reload task <name>: Reload task in scheduler from specified task name attribute.\n";
    out_str += "- reload tasks <name1, name2...>: Reload multiple tasks in scheduler from specified list of task name attributes.\n";
    out_str += "- reload all: Reload all tasks loaded in the Scheduler.\n";
    return out_str;
}

void CommandLine::CommandLine_init(EventReporter* er_ptr, Scheduler* s_ptr){
    this->cmds_issued = 0;
    this->cmd_input = "";
    this->cmd_output = "";
    this->running_cmd = true;
    // Link Event Reporter to Command Line
    this->event_reporter_ptr = er_ptr;
    // Link Scheduler to Command Line
    this->scheduler_ptr = s_ptr;
}

void CommandLine::CommandLine_delete(void){
    this->cmds_issued = 0;
    this->cmd_input = "";
    this->cmd_output = "";
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
    std::string event_message;

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
    else if(split_cmd_input[0] == "help"){
        this->verb_help(split_cmd_input);
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
    else if(split_cmd_input[0] == "reload"){
        this->verb_reload(split_cmd_input);
    }
    else{
        event_message = "Unrecognized command. Entered: " + this->cmd_input;
        this->event_reporter_ptr->log_event(EventType::WARNING, event_message);
        #ifndef SILENT
        this->event_reporter_ptr->publish_last_event();
        #endif
    }
}

std::string& CommandLine::get_cmd_input(void){
    return this->cmd_input;
}

std::string& CommandLine::get_cmd_output(void){
    return this->cmd_output;
}

unsigned int CommandLine::get_cmds_issued(void){
    return this->cmds_issued;
}

void CommandLine::set_cmd_input(std::string in_cmd_input){
    this->cmd_input = in_cmd_input;
}

} // namespace ts