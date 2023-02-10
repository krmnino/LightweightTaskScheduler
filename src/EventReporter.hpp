#ifndef LTS_EVENT_REPORTER
#define LTS_EVENT_REPORTER

#include <string>
#include <deque>
#include <iomanip>

#include "Constants.hpp"
#include "ConfigLoader.hpp"

namespace ts{

class Event{
private:
    const time_t event_time;
    EventType type;
    std::string message;

public:
    Event(time_t, EventType, std::string);
    Event(const Event&);
    ~Event();
    const time_t get_event_time();
    EventType get_type();
    std::string& get_message();
};

class EventReporter{
private:
    static EventReporter* event_reporter_ptr;
    std::deque<Event> event_registry;
    unsigned int events_recorded;

    EventReporter() {}

public:
    static EventReporter* EventReporter_get_instance(void){
        if(event_reporter_ptr == nullptr){
            event_reporter_ptr = new EventReporter();
        }
        return event_reporter_ptr;
    }

    static void EventReporter_end_instance(void){
        delete event_reporter_ptr;
    }

    EventReporter(const EventReporter& s) = delete;
    void log_event(EventType, std::string&);
    Event get_last_event(void);
    void publish_last_event(void);
};

}

#endif