#ifndef LTS_CMD
#define LTS_CMD

#include <vector>
#include <string>

#include "Scheduler.hpp"

class CommandLine{
    private:
    std::vector<std::string> cmd_history;
    unsigned int max_cmd_history;

    public:
    CommandLine();
    ~CommandLine();
    void parse_command(void);
};

#endif // LTS_CMD