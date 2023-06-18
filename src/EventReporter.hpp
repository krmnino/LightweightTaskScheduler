#ifndef LTS_EVENT_REPORTER
#define LTS_EVENT_REPORTER

#include <deque>
#include <iomanip>

#include "Constants.hpp"
#include "ConfigLoader.hpp"

namespace lts{

class Event{
private:
    time_t event_time;
    EventType type;
    std::string message;

public:
    Event();
    Event(time_t, EventType, std::string);
    Event(const Event&);
    ~Event();
    Event& operator=(const Event&);
    const time_t get_event_time();
    EventType get_type();
    std::string& get_message();
};

class EventReporter{
private:
    static EventReporter* event_reporter_ptr;
    std::deque<Event> event_registry;
    unsigned int n_events;

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
    void EventReporter_init();
    void EventReporter_delete();
    void log_event(EventType, std::string&);
    Event get_event_at(unsigned int);
    Event get_last_event(void);
    unsigned int get_n_events(void);
    void publish_last_event(void);
    std::string generate_load_task_msg(ValidationCode, std::string&, cl::Config*);
};

}

#endif