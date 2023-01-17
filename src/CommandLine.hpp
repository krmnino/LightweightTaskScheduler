#ifndef LTS_CMD
#define LTS_CMD

#include <vector>
#include <string>

#include "Scheduler.hpp"

namespace ts{

class CommandLine{
private:
    static CommandLine* command_line_ptr;
    std::vector<std::string> cmd_history;
    unsigned int max_cmd_history;
    unsigned int cmds_issued;
    std::string cmd_input;
    bool running_cmd;

    CommandLine() {};
    void parse_command(void);
public:
    static CommandLine* CommandLine_get_instance(){
        if(command_line_ptr == nullptr){
            command_line_ptr = new CommandLine();
        }
        return command_line_ptr;
    }

    CommandLine(const CommandLine& cmdline) = delete;
    void CommandLine_init();
    void CommandLine_delete();
    void start(void);
};

}

#endif // LTS_CMD