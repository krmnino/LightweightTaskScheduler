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
    static CommandLine* command_line_ptr;
    EventReporter* event_reporter;
    unsigned int max_cmd_history;
    unsigned int cmds_issued;
    bool running_cmd;

    CommandLine() {};
    void parse_command(void);
    void verb_check(std::vector<std::string>&);
    void verb_remove(std::vector<std::string>&);
    void verb_load(std::vector<std::string>&);
    void verb_update(std::vector<std::string>&);
    void verb_help(std::vector<std::string>&);
    
public:
    static CommandLine* CommandLine_get_instance(){
        if(command_line_ptr == nullptr){
            command_line_ptr = new CommandLine();
        }
        return command_line_ptr;
    }

    CommandLine(const CommandLine& cmdline) = delete;
    void CommandLine_init(EventReporter*);
    void CommandLine_delete();
    void start(void);
};

} // namespace ts

#endif // LTS_CMD