#ifndef LTS_CMD
#define LTS_CMD

#include <vector>

#include <string>

#include "Constants.hpp"
#include "Scheduler.hpp"
#include "EventReporter.hpp"

namespace ts{

class CommandLine{
private:
    std::vector<std::string> cmd_history;
    std::string cmd_input;
    std::string cmd_output;
    static CommandLine* command_line_ptr;
    EventReporter* event_reporter_ptr;
    Scheduler* scheduler_ptr;
    unsigned int max_cmd_history;
    unsigned int cmds_issued;
    bool running_cmd;

    CommandLine() {};
    void parse_command(void);
    void verb_check(std::vector<std::string>&);
    void verb_remove(std::vector<std::string>&);
    void verb_load(std::vector<std::string>&);
    void verb_help(std::vector<std::string>&);
    std::string help_msg(void);
    std::string help_check_msg(void);
    std::string help_remove_msg(void);
    std::string help_load_msg(void);
    
public:
    static CommandLine* CommandLine_get_instance(){
        if(command_line_ptr == nullptr){
            command_line_ptr = new CommandLine();
        }
        return command_line_ptr;
    }

    static void CommandLine_end_instance(void){
        delete command_line_ptr;
    }

    CommandLine(const CommandLine& cmdline) = delete;
    void CommandLine_init(EventReporter*, Scheduler*);
    void CommandLine_delete(void);
    void start(void);
};

} // namespace ts

#endif // LTS_CMD