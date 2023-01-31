#ifndef LTS_EVENT_REPORTER
#define LTS_EVENT_REPORTER

#include <string>
#include <vector>

namespace ts{

enum class EventType{
    INFO,
    WARNING,
    ERROR
};

struct Event{
    time_t event_time;
    EventType type;
    std::string message;
};

class EventReporter{
private:
    static EventReporter* event_reporter_ptr;
    std::vector<Event> event_collection;
    unsigned int n_events;

    EventReporter() {}

public:
    EventReporter(const EventReporter& s) = delete;
    void EventReporter_init(void);
    void EventReporter_delete(void);
};

}

#endif