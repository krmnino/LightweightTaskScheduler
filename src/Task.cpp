#include "Task.hpp"

namespace ts{

Task::Task(std::string name, 
           std::string description,
           std::string script_filename,
           std::string frequency,
           std::string execution_datetime_str,
           std::string config_filename){
    this->name = name;
    this->description = description;
    this->script_filename = script_filename;
    this->frequency = frequency;
    this->config_filename = config_filename;
    this->running_thread_flag = false;
    
    ts::DatetimeFormat format;
    if(this->frequency == "Once"){
        // Get datetime format, no validation performed at this step
        format = compute_datetime_format(execution_datetime_str);
        // Datetime string validation occurs at Scheduler constructor
        switch ((int)format){
        case (int)DatetimeFormat::HHMMSS:
            this->execution_datetime = today_add_hms(execution_datetime_str);
            break;
        case (int)DatetimeFormat::YYYYMMDD_HHMMSS:
            this->execution_datetime = today_add_yyyymmdd_hms(execution_datetime_str);
            break;
        case (int)DatetimeFormat::WDAY_HHMMSS:
            this->execution_datetime = today_add_wday_hms(execution_datetime_str);
            break;
        case (int)DatetimeFormat::YYYYMMDD:
            this->execution_datetime = today_add_yyyymmdd(execution_datetime_str);
            break;
        default:
            this->execution_datetime = 0;
            this->status = TaskStatus::INIT_ERROR;
            break;
        }
    }
    else if(this->frequency == "Hourly"){
        // Get datetime format, no validation performed at this step
        format = compute_datetime_format(execution_datetime_str);
        // Datetime string validation occurs at Scheduler constructor
        switch ((int)format){
        case (int)DatetimeFormat::HHMMSS:
            this->execution_datetime = today_add_hms(execution_datetime_str);
            break;
        case (int)DatetimeFormat::YYYYMMDD_HHMMSS:
            this->execution_datetime = today_add_yyyymmdd_hms(execution_datetime_str);
            break;
        default:
            this->execution_datetime = 0;
            this->status = TaskStatus::INIT_ERROR;
            break;
        }
    }
    else if(this->frequency == "Daily"){
        // Get datetime format, no validation performed at this step
        format = compute_datetime_format(execution_datetime_str);
        // Datetime string validation occurs at Scheduler constructor
        switch ((int)format){
        case (int)DatetimeFormat::HHMMSS:
            this->execution_datetime = today_add_hms(execution_datetime_str);
            break;
        case (int)DatetimeFormat::YYYYMMDD_HHMMSS:
            this->execution_datetime = today_add_yyyymmdd_hms(execution_datetime_str);
            break;
        case (int)DatetimeFormat::WDAY_HHMMSS:
            this->execution_datetime = today_add_wday_hms(execution_datetime_str);
            break;
        default:
            this->execution_datetime = 0;
            this->status = TaskStatus::INIT_ERROR;
            break;
        }
    }
    else if(this->frequency == "Weekly"){
        // Get datetime format, no validation performed at this step
        format = compute_datetime_format(execution_datetime_str);
        // Datetime string validation occurs at Scheduler constructor
        switch ((int)format){
        case (int)DatetimeFormat::HHMMSS:
            this->execution_datetime = today_add_hms(execution_datetime_str);
            break;
        case (int)DatetimeFormat::YYYYMMDD_HHMMSS:
            this->execution_datetime = today_add_yyyymmdd_hms(execution_datetime_str);
            break;
        case (int)DatetimeFormat::WDAY_HHMMSS:
            this->execution_datetime = today_add_wday_hms(execution_datetime_str);
            break;
        case (int)DatetimeFormat::YYYYMMDD:
            this->execution_datetime = today_add_yyyymmdd(execution_datetime_str);
            break;
        default:
            this->execution_datetime = 0;
            this->status = TaskStatus::INIT_ERROR;
            break;
        }
    }
    else if(this->frequency == "Monthly"){
        // Get datetime format, no validation performed at this step
        format = compute_datetime_format(execution_datetime_str);
        // Datetime string validation occurs at Scheduler constructor
        switch ((int)format){
        case (int)DatetimeFormat::HHMMSS:
            this->execution_datetime = today_add_hms(execution_datetime_str);
            break;
        case (int)DatetimeFormat::YYYYMMDD_HHMMSS:
            this->execution_datetime = today_add_yyyymmdd_hms(execution_datetime_str);
            break;
        case (int)DatetimeFormat::YYYYMMDD:
            this->execution_datetime = today_add_yyyymmdd(execution_datetime_str);
            break;
        default:
            this->execution_datetime = 0;
            this->status = TaskStatus::INIT_ERROR;
            break;
        }
    }
    else if(this->frequency == "Yearly"){
        // Get datetime format, no validation performed at this step
        format = compute_datetime_format(execution_datetime_str);
        // Datetime string validation occurs at Scheduler constructor
        switch ((int)format){
        case (int)DatetimeFormat::YYYYMMDD_HHMMSS:
            this->execution_datetime = today_add_yyyymmdd_hms(execution_datetime_str);
            break;
        case (int)DatetimeFormat::YYYYMMDD:
            this->execution_datetime = today_add_yyyymmdd(execution_datetime_str);
            break;
        default:
            this->execution_datetime = 0;
            this->status = TaskStatus::INIT_ERROR;
            break;
        }
    }
    else{
        this->status = TaskStatus::INIT_ERROR;
    }

    // Save datetime format
    this->execution_datetime_fmt = format;

    // Set initial execution datetime struct
    std::tm* exec_time_struct = std::gmtime(&this->execution_datetime);
    this->initial_execution_datetime.year = 1900 + exec_time_struct->tm_year;
    this->initial_execution_datetime.month = exec_time_struct->tm_mon;
    this->initial_execution_datetime.wday = exec_time_struct->tm_wday;
    this->initial_execution_datetime.day =  exec_time_struct->tm_mday;
    this->initial_execution_datetime.hour =  exec_time_struct->tm_hour;
    this->initial_execution_datetime.minute = exec_time_struct->tm_min;
    this->initial_execution_datetime.second = exec_time_struct->tm_sec;

    // Store task creation datetime
    std::time(&this->creation_datetime);
    this->creation_datetime = this->creation_datetime;

    this->output = "";
    if(this->status != TaskStatus::INIT_ERROR){
        this->thr = std::thread(&Task::launch_thread, this);
        this->running_thread_flag = true;
        this->status = TaskStatus::QUEUED;
    }
}

Task::Task(){}

Task::~Task(){
    // If thread is not running, then no need to stop it
    if(this->running_thread_flag){
        this->stop_thread();
    }
}

void Task::run_task(void){
    std::array<char, 128> buffer;
    std::string result;
    std::string script_path = "scripts/" + this->script_filename;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(script_path.c_str(), "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        this->output += buffer.data();
    }
}

void Task::stop_thread(void){
    std::unique_lock<std::mutex> lock(this->mtx);
    this->running_thread_flag = false;
    lock.unlock();
    this->cv.notify_one();
    this->thr.join();
}

void Task::update_execution_datetime(void){
    if(this->frequency == "Hourly"){
        // Add 1 hour in seconds to current execution time
        this->execution_datetime = this->execution_datetime + 3600;
    }
    else if(this->frequency == "Daily"){
        // Add 24 hours in seconds to current execution time
        this->execution_datetime = this->execution_datetime + (24 * 3600);
    }
    else if(this->frequency == "Weekly"){
        // Add 7 days in seconds to current execution time
        this->execution_datetime = this->execution_datetime + (7 * 24 * 3600);
    }
    else if(this->frequency == "Monthly"){
        // Add necessary days until nth day of next month
        std::string year;
        std::string month;
        std::string day;
        std::string hour;
        std::string minute;
        std::string second;
        std::string updated_datetime_str;
        unsigned long updated_year;
        unsigned long updated_month;
        unsigned long updated_day;

        time_t execution_datetime_timezone = this->execution_datetime + (TIMEZONE * 60 * 60);
        std::tm* exec_date_struct = std::gmtime(&execution_datetime_timezone);

        // If current execution month is december, we need to roll back to January and set next year
        if(exec_date_struct->tm_mon == DECEMBER){
            updated_year = 1900 + exec_date_struct->tm_year + 1;
            updated_month = JANUARY; 
        }
        else{
            updated_year = 1900 + exec_date_struct->tm_year;
            updated_month = exec_date_struct->tm_mon + 1;
        }

        // String-ify datetime values
        year = std::to_string(updated_year);
        month = (updated_month + 1 < 10) ? 
                "0" + std::to_string(updated_month + 1) :
                std::to_string(updated_month + 1);
        hour = (this->initial_execution_datetime.hour < 10) ? 
                "0" + std::to_string(this->initial_execution_datetime.hour) :
                std::to_string(this->initial_execution_datetime.hour);
        minute = (this->initial_execution_datetime.minute < 10) ? 
                 "0" + std::to_string(this->initial_execution_datetime.minute) :
                 std::to_string(this->initial_execution_datetime.minute);
        second = (this->initial_execution_datetime.second < 10) ? 
                 "0" + std::to_string(this->initial_execution_datetime.second) :
                 std::to_string(this->initial_execution_datetime.second);

        // Check for the appropiate day of the month for the next month
        // If a month has less number than the initial execution datetime, then pick the very last day of the next month
        // No need to subtract month value here
        switch(updated_month)
        {
        case JANUARY:
            // January has max day count of 31
            day = (this->initial_execution_datetime.day < 10) ? 
                   "0" + std::to_string(this->initial_execution_datetime.day) :
                   std::to_string(this->initial_execution_datetime.day);
            break;
        case FEBRUARY:
            // Check if we are currently on a leap year
            if(this->initial_execution_datetime.day > FEBRUARY_DAYS){
                if(1900 + exec_date_struct->tm_year % 4 == 0){
                    day = std::to_string(FEBRUARY_DAYS + 1);
                }
                else{
                    day = std::to_string(FEBRUARY_DAYS);
                }
            }
            else{
                day = (this->initial_execution_datetime.day < 10) ? 
                       "0" + std::to_string(this->initial_execution_datetime.day) :
                       std::to_string(this->initial_execution_datetime.day);
            }
            break;
        case MARCH:
            // March has max day count of 31
            day = (this->initial_execution_datetime.day < 10) ? 
                   "0" + std::to_string(this->initial_execution_datetime.day) :
                   std::to_string(this->initial_execution_datetime.day);
            break;
        case APRIL:
            if(this->initial_execution_datetime.day > APRIL_DAYS){
                day = std::to_string(APRIL_DAYS);
            }
            else{
                day = (this->initial_execution_datetime.day < 10) ? 
                       "0" + std::to_string(this->initial_execution_datetime.day) :
                       std::to_string(this->initial_execution_datetime.day);
            }
            break;
        case MAY:
            // May has max day count of 31
            day = (this->initial_execution_datetime.day < 10) ? 
                   "0" + std::to_string(this->initial_execution_datetime.day) :
                   std::to_string(this->initial_execution_datetime.day);
            break;
        case JUNE:
            // June has max day count of 30
            if(this->initial_execution_datetime.day > JUNE_DAYS){
                day = std::to_string(JUNE_DAYS);
            }
            else{
                day = (this->initial_execution_datetime.day < 10) ? 
                       "0" + std::to_string(this->initial_execution_datetime.day) :
                       std::to_string(this->initial_execution_datetime.day);
            }
            break;
        case JULY:
            // July has max day count of 31
            day = (this->initial_execution_datetime.day < 10) ? 
                   "0" + std::to_string(this->initial_execution_datetime.day) :
                   std::to_string(this->initial_execution_datetime.day);
            break;
        case AUGUST:
            // August has max day count of 31
            day = (this->initial_execution_datetime.day < 10) ? 
                   "0" + std::to_string(this->initial_execution_datetime.day) :
                   std::to_string(this->initial_execution_datetime.day);
            break;
        case SEPTEMBER:
            if(this->initial_execution_datetime.day > SEPTEMBER_DAYS){
                day = std::to_string(SEPTEMBER_DAYS);
            }
            else{
                day = (this->initial_execution_datetime.day < 10) ? 
                       "0" + std::to_string(this->initial_execution_datetime.day) :
                       std::to_string(this->initial_execution_datetime.day);
            }
            break;
        case OCTOBER:
            // October has max day count of 31
            day = (this->initial_execution_datetime.day < 10) ? 
                   "0" + std::to_string(this->initial_execution_datetime.day) :
                   std::to_string(this->initial_execution_datetime.day);
            break;
        case NOVEMBER:
            if(this->initial_execution_datetime.day > NOVEMBER_DAYS){
                day = std::to_string(NOVEMBER_DAYS);
            }
            else{
                day = (this->initial_execution_datetime.day < 10) ? 
                       "0" + std::to_string(this->initial_execution_datetime.day) :
                       std::to_string(this->initial_execution_datetime.day);
            }
            break;
        case DECEMBER:
            // December has max day count of 31
            day = (this->initial_execution_datetime.day < 10) ? 
                   "0" + std::to_string(this->initial_execution_datetime.day) :
                   std::to_string(this->initial_execution_datetime.day);
            break;
        default:
            month = "";
            break;
        }
        this->execution_datetime = today_add_yyyymmdd_hms(year + "-" + month + "-" + day + " " + hour + ":" + minute + ":" + second);
    }
    else if(this->frequency == "Yearly"){
        // Add necessary days until nth day of next year
        time_t execution_datetime_timezone = this->execution_datetime + (TIMEZONE * 60 * 60);
        std::tm* exec_date_struct = std::gmtime(&execution_datetime_timezone);
        // Edge case if case is scheduled to run on February 29th
        // If next year is not a leap year, then run on the 28th (see else statement)
        if(this->initial_execution_datetime.month == FEBRUARY && 
           this->initial_execution_datetime.day == 29 && 
           (1900 + exec_date_struct->tm_year + 1) % 4 == 0){
            this->execution_datetime = this->execution_datetime + (366 * 24 * 60 * 60);
        }
        // Else if next year is a leap year and task is scheduled after February 28th, then add 366 days
        else if((1900 + exec_date_struct->tm_year + 1) % 4 == 0 && 
           (exec_date_struct->tm_mon >= FEBRUARY || 
           (exec_date_struct->tm_mon == FEBRUARY && exec_date_struct->tm_mday >= 28))){
            this->execution_datetime = this->execution_datetime + (366 * 24 * 60 * 60);
        }
        else{
            this->execution_datetime = this->execution_datetime + (365 * 24 * 60 * 60);
        }
    }
    return; // Else, Frequency is Once so no update occurs 
}

std::string Task::get_name(void) const{
    return this->name;
}

std::string Task::get_description(void) const{
    return this->description;
}

std::string Task::get_script_filename(void) const{
    return this->script_filename;
}

std::string Task::get_frequency(void) const{
    return this->frequency;
}

std::string Task::get_output(void) const{
    return this->output;
}

time_t Task::get_creation_datetime(bool add_timezone){
    if(add_timezone){
        return this->creation_datetime + (TIMEZONE * 60 * 60);
    }
    return this->creation_datetime;
}

time_t Task::get_execution_datetime(bool add_timezone){
    if(add_timezone){
        return this->execution_datetime + (TIMEZONE * 60 * 60);
    }
    return this->execution_datetime;
}

std::string Task::get_creation_datetime_fmt(void) const{
    std::string years;
    std::string month;
    std::string days;
    std::string wday;
    std::string hours;
    std::string minutes;
    std::string seconds;
    time_t time_offset_timezone = this->creation_datetime + (TIMEZONE * 60 * 60);
    std::tm* creat_time_struct = std::gmtime(&time_offset_timezone);

    years = std::to_string(1900 + creat_time_struct->tm_year);
    switch (creat_time_struct->tm_mon)
    {
    case JANUARY:
        month = "Jan";
        break;
    case FEBRUARY:
        month = "Feb";
        break;
    case MARCH:
        month = "Mar";
        break;
    case APRIL:
        month = "Apr";
        break;
    case MAY:
        month = "May";
        break;
    case JUNE:
        month = "Jun";
        break;
    case JULY:
        month = "Jul";
        break;
    case AUGUST:
        month = "Aug";
        break;
    case SEPTEMBER:
        month = "Sep";
        break;
    case OCTOBER:
        month = "Oct";
        break;
    case NOVEMBER:
        month = "Nov";
        break;
    case DECEMBER:
        month = "Dec";
        break;
    default:
        month = "";
        break;
    }
    switch (creat_time_struct->tm_wday)
    {
    case SUNDAY:
        wday = "Sun";
        break;
    case MONDAY:
        wday = "Mon";
        break;
    case TUESDAY:
        wday = "Tue";
        break;
    case WEDNESDAY:
        wday = "Wed";
        break;
    case THURSDAY:
        wday = "Thu";
        break;
    case FRIDAY:
        wday = "Fri";
        break;
    case SATURDAY:
        wday = "Sat";
        break;
    default:
        wday = "";
        break;
    }
    days = (creat_time_struct->tm_mday < 10) ? 
            "0" + std::to_string(creat_time_struct->tm_mday) :
            std::to_string(creat_time_struct->tm_mday);
    hours = (creat_time_struct->tm_hour < 10) ? 
            "0" + std::to_string(creat_time_struct->tm_hour) :
            std::to_string(creat_time_struct->tm_hour);    
    minutes = (creat_time_struct->tm_min < 10) ? 
               "0" + std::to_string(creat_time_struct->tm_min) :
               std::to_string(creat_time_struct->tm_min);
    seconds = (creat_time_struct->tm_sec < 10) ? 
               "0" + std::to_string(creat_time_struct->tm_sec) :
               std::to_string(creat_time_struct->tm_sec);

    return wday + " " + month + " " + days + " " + hours + ":" + minutes + ":" + seconds + " " + years;
}

std::string Task::get_execution_datetime_fmt(void) const{
    std::string years;
    std::string month;
    std::string days;
    std::string wday;
    std::string hours;
    std::string minutes;
    std::string seconds;
    time_t time_offset_timezone = this->execution_datetime + (TIMEZONE * 60 * 60);
    std::tm* exec_time_struct = std::gmtime(&time_offset_timezone);

    years = std::to_string(1900 + exec_time_struct->tm_year);
    switch (exec_time_struct->tm_mon)
    {
    case JANUARY:
        month = "Jan";
        break;
    case FEBRUARY:
        month = "Feb";
        break;
    case MARCH:
        month = "Mar";
        break;
    case APRIL:
        month = "Apr";
        break;
    case MAY:
        month = "May";
        break;
    case JUNE:
        month = "Jun";
        break;
    case JULY:
        month = "Jul";
        break;
    case AUGUST:
        month = "Aug";
        break;
    case SEPTEMBER:
        month = "Sep";
        break;
    case OCTOBER:
        month = "Oct";
        break;
    case NOVEMBER:
        month = "Nov";
        break;
    case DECEMBER:
        month = "Dec";
        break;
    default:
        month = "";
        break;
    }
    switch (exec_time_struct->tm_wday)
    {
    case SUNDAY:
        wday = "Sun";
        break;
    case MONDAY:
        wday = "Mon";
        break;
    case TUESDAY:
        wday = "Tue";
        break;
    case WEDNESDAY:
        wday = "Wed";
        break;
    case THURSDAY:
        wday = "Thu";
        break;
    case FRIDAY:
        wday = "Fri";
        break;
    case SATURDAY:
        wday = "Sat";
        break;
    default:
        wday = "";
        break;
    }
    days = (exec_time_struct->tm_mday < 10) ? 
            "0" + std::to_string(exec_time_struct->tm_mday) :
            std::to_string(exec_time_struct->tm_mday);
    hours = (exec_time_struct->tm_hour < 10) ? 
            "0" + std::to_string(exec_time_struct->tm_hour) :
            std::to_string(exec_time_struct->tm_hour);    
    minutes = (exec_time_struct->tm_min < 10) ? 
               "0" + std::to_string(exec_time_struct->tm_min) :
               std::to_string(exec_time_struct->tm_min);
    seconds = (exec_time_struct->tm_sec < 10) ? 
               "0" + std::to_string(exec_time_struct->tm_sec) :
               std::to_string(exec_time_struct->tm_sec);

    return wday + " " + month + " " + days + " " + hours + ":" + minutes + ":" + seconds + " " + years;
}

TaskStatus Task::get_status(void) const{
    return this->status;
}

int Task::get_id(void) const{
    return this->id;
}

DatetimeFormat Task::get_execution_datetime_format_attr(void){
    return this->execution_datetime_fmt;
}

std::string Task::get_config_filename(void){
    return this->config_filename;
}

void Task::set_status(TaskStatus status){
    this->status = status;
}

void Task::set_id(int id){
    this->id = id;
}

void Task::set_event_reporter_ptr(ts::EventReporter* er_ptr){
    this->event_reporter_ptr = er_ptr;
}

ValidationCode validate_hms(std::string hms){
    if(hms.length() != 8){
        return ValidationCode::BAD_HMS_LENGTH;
    }
    unsigned int num;
    unsigned int hours;
    unsigned int minutes;
    unsigned int seconds;
    num = hms.at(0);
    if(num < '0' | num > '9'){
        return ValidationCode::BAD_NUMBER_CHARACTER;
    }
    num = hms.at(1);
    if(num < '0' | num > '9'){
        return ValidationCode::BAD_NUMBER_CHARACTER;
    }
    // Validate range of hour
    hours = ((hms.at(0) & 0x0F) * 10) + 
             (hms.at(1) & 0x0F);
    if(hours < 0 | hours > 23){
        return ValidationCode::HOURS_OUT_OF_RANGE;
    }
    if(hms.at(2) != ':'){
        return ValidationCode::MISSING_DATETIME_COLON;
    }
    num = hms.at(3);
    if(num < '0' | num > '9'){
        return ValidationCode::BAD_NUMBER_CHARACTER;
    }
    num = hms.at(4);
    if(num < '0' | num > '9'){
        return ValidationCode::BAD_NUMBER_CHARACTER;
    }
    // Validate range of minute
    minutes = ((hms.at(3) & 0x0F) * 10) + 
               (hms.at(4) & 0x0F);
    if(minutes < 0 | minutes > 59){
        return ValidationCode::MINUTES_OUT_OF_RANGE;
    }
    if(hms.at(5) != ':'){
        return ValidationCode::MISSING_DATETIME_COLON;
    }
    num = hms.at(6);
    if(num < '0' | num > '9'){
        return ValidationCode::BAD_NUMBER_CHARACTER;
    }
    num = hms.at(7);
    if(num < '0' | num > '9'){
        return ValidationCode::BAD_NUMBER_CHARACTER;
    }
    // Validate range of second
    seconds = ((hms.at(6) & 0x0F) * 10) + 
               (hms.at(7) & 0x0F);
    if(seconds < 0 | seconds > 59){
        return ValidationCode::SECONDS_OUT_OF_RANGE;
    }
    return ValidationCode::OK;
}

ValidationCode validate_wday(std::string wday){
    if(wday != "Mon" && wday != "Monday" && 
       wday != "Tue" && wday != "Tuesday" &&
       wday != "Wed" && wday != "Wednesday" &&
       wday != "Thu" && wday != "Thursday" &&
       wday != "Fri" && wday != "Friday" &&
       wday != "Sat" && wday != "Saturday" &&
       wday != "Sun" && wday != "Sunday"){
        return ValidationCode::BAD_WDAY;
    }
    return ValidationCode::OK;
}

ValidationCode validate_wday_hms(std::string wday_hms){
    int space_idx = wday_hms.find(" ");
    if(space_idx < 0){
        return ValidationCode::MISSING_DATETIME_SPACE;
    }
    std::string date = wday_hms.substr(0, space_idx);
    std::string time = wday_hms.substr(space_idx + 1, wday_hms.length());
    ValidationCode ret;
    ret = validate_wday(date);
    if(ret != ValidationCode::OK){
        return ret;
    }
    ret = validate_hms(time);
    if(ret != ValidationCode::OK){
        return ret;
    }
    return ValidationCode::OK;
}

ValidationCode validate_yyyymmdd(std::string yyyymmdd){
    if(yyyymmdd.length() != 10){
        return ValidationCode::BAD_YYYYMMDD_LENGTH;
    }
    unsigned int num;
    unsigned int year;
    unsigned int month;
    unsigned int day;
    // Validate year individual digits
    num = yyyymmdd.at(0);
    if(num < '0' | num > '9'){
        return ValidationCode::BAD_NUMBER_CHARACTER;
    }
    num = yyyymmdd.at(1);
    if(num < '0' | num > '9'){
        return ValidationCode::BAD_NUMBER_CHARACTER;
    }
    num = yyyymmdd.at(2);
    if(num < '0' | num > '9'){
        return ValidationCode::BAD_NUMBER_CHARACTER;
    }
    num = yyyymmdd.at(3);
    if(num < '0' | num > '9'){
        return ValidationCode::BAD_NUMBER_CHARACTER;
    }
    // Validate range of year
    year = ((yyyymmdd.at(0) & 0x0F) * 1000) + 
           ((yyyymmdd.at(1) & 0x0F) * 100) + 
           ((yyyymmdd.at(2) & 0x0F) * 10) + 
            (yyyymmdd.at(3) & 0x0F);
    if(year < 0 | year > 9999){
        return ValidationCode::YEAR_OUT_OF_RANGE;
    }
    // Check if dash delimiter exists
    if(yyyymmdd.at(4) != '-'){
        return ValidationCode::MISSING_DATETIME_DASH;
    }
    // Validate month individual characters
    num = yyyymmdd.at(5);
    if(num < '0' | num > '9'){
        return ValidationCode::BAD_NUMBER_CHARACTER;
    }
    num = yyyymmdd.at(6);
    if(num < '0' | num > '9'){
        return ValidationCode::BAD_NUMBER_CHARACTER;
    }
    // Validate range of months
    month = ((yyyymmdd.at(5) & 0x0F) * 10) + 
             (yyyymmdd.at(6) & 0x0F);
    if(month < 1 | month > 12){
        return ValidationCode::MONTH_OUT_OF_RANGE;
    }
    // Subtract 1 from month to match the std::tm format
    month = month - 1;
    // Check if dash delimiter exists
    if(yyyymmdd.at(7) != '-'){
        return ValidationCode::MISSING_DATETIME_DASH;
    }
    // Validate day individual characters
    num = yyyymmdd.at(8);
    if(num < '0' | num > '9'){
        return ValidationCode::BAD_NUMBER_CHARACTER;
    }
    num = yyyymmdd.at(9);
    if(num < '0' | num > '9'){
        return ValidationCode::BAD_NUMBER_CHARACTER;
    }
    // Validate range of days by month
    day = ((yyyymmdd.at(8) & 0x0F) * 10) + 
           (yyyymmdd.at(9) & 0x0F);
    switch (month){
    case JANUARY:
        if(day < 1 || day > 31){
            return ValidationCode::DAY_OUT_OF_RANGE;
        }
        break;
    case FEBRUARY:
        // If year is a leap year, then up to 29 days
        if(year % 4 == 0){
            if(day < 1 || day > 29){
                return ValidationCode::DAY_OUT_OF_RANGE;
            }
        }
        else{
            if(day < 1 || day > 28){
                return ValidationCode::DAY_OUT_OF_RANGE;
            }
        }
        break;
    case MARCH:
        if(day < 1 || day > 31){
            return ValidationCode::DAY_OUT_OF_RANGE;
        }
        break;
    case APRIL:
        if(day < 1 || day > 30){
            return ValidationCode::DAY_OUT_OF_RANGE;
        }
        break;
    case MAY:
        if(day < 1 || day > 31){
            return ValidationCode::DAY_OUT_OF_RANGE;
        }
        break;
    case JUNE:
        if(day < 1 || day > 30){
            return ValidationCode::DAY_OUT_OF_RANGE;
        }
        break;
    case JULY:
        if(day < 1 || day > 31){
            return ValidationCode::DAY_OUT_OF_RANGE;
        }    
        break;
    case AUGUST:
        if(day < 1 || day > 31){
            return ValidationCode::DAY_OUT_OF_RANGE;
        }       
        break;
    case SEPTEMBER:
        if(day < 1 || day > 30){
            return ValidationCode::DAY_OUT_OF_RANGE;
        }    
        break;
    case OCTOBER:
        if(day < 1 || day > 31){
            return ValidationCode::DAY_OUT_OF_RANGE;
        }    
        break;
    case NOVEMBER:
        if(day < 1 || day > 30){
            return ValidationCode::DAY_OUT_OF_RANGE;
        }    
        break;
    case DECEMBER:
        if(day < 1 || day > 31){
            return ValidationCode::DAY_OUT_OF_RANGE;
        }    
        break;
    default:
        return ValidationCode::MONTH_OUT_OF_RANGE;
        break;
    }
    return ValidationCode::OK;
}

ValidationCode validate_yyyymmdd_hms(std::string yyyymmdd_hms){
    int space_idx = yyyymmdd_hms.find(" ");
    if(space_idx < 0){
        return ValidationCode::MISSING_DATETIME_SPACE;
    }
    std::string date = yyyymmdd_hms.substr(0, space_idx);
    std::string time = yyyymmdd_hms.substr(space_idx + 1, yyyymmdd_hms.length());
    ValidationCode ret;
    ret = validate_yyyymmdd(date);
    if(ret != ValidationCode::OK){
        return ret;
    }
    ret = validate_hms(time);
    if(ret != ValidationCode::OK){
        return ret;
    }
    return ValidationCode::OK;
}

time_t init_today(void){
    time_t time_now;
    std::tm* struct_time_now;

    // Get current time
    std::time(&time_now);
    // Convert to struct
    struct_time_now = std::gmtime(&time_now);

    // Get hours, minutes, and seconds. Convert to seconds 
    int hrs_2_sec = (struct_time_now->tm_hour) * 60 * 60;
    int min_2_sec = struct_time_now->tm_min * 60;
    int sec = struct_time_now->tm_sec;

    // Add converted hours and minutes to total seconds
    sec += hrs_2_sec + min_2_sec;

    // Subtract time
    time_now -= sec;

    return time_now;
}

time_t init_year(void){
    time_t time_now;
    std::tm* struct_time_now;

    // Get current time
    std::time(&time_now);
    // Convert to struct
    struct_time_now = std::gmtime(&time_now);

    // Get days, hours, minutes, and seconds. Convert to seconds 
    unsigned long days_2_sec = (struct_time_now->tm_yday) * 24 * 60 * 60;
    int hrs_2_sec = (struct_time_now->tm_hour) * 60 * 60;
    int min_2_sec = struct_time_now->tm_min * 60;
    int sec = struct_time_now->tm_sec;

    // Add converted days, hours, and minutes to total seconds
    sec += days_2_sec + hrs_2_sec + min_2_sec;

    // Subtract time
    time_now -= sec;

    return time_now;
}

time_t today_add_hrs(int hrs){
    if(hrs < 0){
        return 0;
    }

    // Get current time
    time_t time_now;
    std::time(&time_now);

    // Add hours parameter in seconds
    time_t added_time = time_now + (hrs * 3600);
   
    return added_time;
}

time_t today_add_hms(std::string hms){
    if(validate_hms(hms) != ValidationCode::OK){
        return 0;
    }
    // Get time at start of current day
    time_t time_start_day = init_today();
    
    // Convert huors and minutes to seconds and add them together
    unsigned long hours = ((hms.at(0) & 0x0F) * 10) + 
                           (hms.at(1) & 0x0F);
    unsigned long minutes = ((hms.at(3) & 0x0F) * 10) + 
                             (hms.at(4) & 0x0F);
    unsigned long seconds = ((hms.at(6) & 0x0F) * 10) + 
                             (hms.at(7) & 0x0F);
    seconds += (hours * 60 * 60) + (minutes * 60);
    time_t added_time = time_start_day + seconds;
    
    // Get current time and check for past time
    time_t time_now;
    std::time(&time_now);
    if(time_now >= added_time){
        return 0;
    }

    return added_time;
}

time_t today_add_dhms(int d, std::string hms){
    if(validate_hms(hms) != ValidationCode::OK | d < 0){
        return 0;
    }
    // Get time at start of current day
    time_t time_start_day = init_today();
    
    // Convert hours and minutes to seconds and add them together
    unsigned long hours = ((hms.at(0) & 0x0F) * 10) + 
                           (hms.at(1) & 0x0F);
    unsigned long minutes = ((hms.at(3) & 0x0F) * 10) + 
                             (hms.at(4) & 0x0F);
    unsigned long seconds = ((hms.at(6) & 0x0F) * 10) + 
                             (hms.at(7) & 0x0F);
    seconds += (d * 24 * 60 * 60) + (hours * 60 * 60) + (minutes * 60);
    time_t added_time = time_start_day + seconds;

    // Get current time and check for past time
    time_t time_now;
    std::time(&time_now);
    if(time_now >= added_time){
        return 0;
    }

    return added_time;
}

time_t today_add_wday_hms(std::string wday_hms){
    if(validate_wday_hms(wday_hms) != ValidationCode::OK){
        return 0;
    }
   
    // Get current time and convert to struct
    time_t time_now = init_today();
    std::tm* time_now_struct;
    time_now_struct = gmtime(&time_now);

    std::tm time_input_whms;
    std::istringstream whms_ss(wday_hms.c_str());
    whms_ss >> std::get_time(&time_input_whms, "%a %H:%M:%S");

    // Obtain hours, minutes, seconds part of the input string
    int space_idx = wday_hms.find(" ");
    std::string hms = wday_hms.substr(space_idx + 1, wday_hms.length());

    // Calculate days until desired weekday
    int diff_day;
    if(time_now_struct->tm_wday == time_input_whms.tm_wday){
        time_t now;
        time_t now_add_hms = today_add_hms(hms);
        std::time(&now);
        if(now < now_add_hms){
            time_now = now_add_hms;
        }
        else{
            time_now = today_add_dhms(DAYS_IN_WEEK, hms);
        }
    }
    else if(time_now_struct->tm_wday > time_input_whms.tm_wday){
        diff_day = time_now_struct->tm_wday - time_input_whms.tm_wday;
        diff_day = DAYS_IN_WEEK - diff_day;
        time_now = today_add_dhms(diff_day, hms);
    }
    else{
        diff_day = time_input_whms.tm_wday - time_now_struct->tm_wday;
        time_now = today_add_dhms(diff_day, hms);
    }
    return time_now;
}

time_t today_add_yyyymmdd(std::string yyyymmdd){
    if(validate_yyyymmdd(yyyymmdd) != ValidationCode::OK){
        return 0;
    }

    // Get time at start of current year
    time_t time_start_year = init_year();
    std::tm* time_start_year_struct;
    time_start_year_struct = gmtime(&time_start_year);

    // Convert hours and minutes to seconds and add them together
    unsigned long years = ((yyyymmdd.at(0) & 0x0F) * 1000) + 
                          ((yyyymmdd.at(1) & 0x0F) * 100) + 
                          ((yyyymmdd.at(2) & 0x0F) * 10) + 
                           (yyyymmdd.at(3) & 0x0F);
    unsigned long months = ((yyyymmdd.at(5) & 0x0F) * 10) + 
                           (yyyymmdd.at(6) & 0x0F);
    unsigned long days = ((yyyymmdd.at(8) & 0x0F) * 10) + 
                          (yyyymmdd.at(9) & 0x0F) - 1;

    // Since tm_year counts years since 1900, add 1900
    time_t current_year = time_start_year_struct->tm_year + 1900;

    // Get delta years and a check if less than 0
    unsigned long diff_years = years - current_year;
    if(diff_years < 0){
        return 0;
    }

    // Accumulate day count in year plus day in month
    unsigned long acc_days = 0;
    switch (months - 1)
    {
    case JANUARY:
        acc_days += days;
        break;
    case FEBRUARY:
        acc_days += JANUARY_DAYS + days;
        break;
    case MARCH:
        acc_days += JANUARY_DAYS +
                    FEBRUARY_DAYS + days;
        break;
    case APRIL:
        acc_days += JANUARY_DAYS +
                    FEBRUARY_DAYS +
                    MARCH_DAYS + days;
        break;
    case MAY:
        acc_days += JANUARY_DAYS +
                    FEBRUARY_DAYS +
                    MARCH_DAYS +
                    APRIL_DAYS + days;
        break;
    case JUNE:
        acc_days += JANUARY_DAYS +
                    FEBRUARY_DAYS +
                    MARCH_DAYS +
                    APRIL_DAYS + 
                    MAY_DAYS + days;
        break;
    case JULY:
        acc_days += JANUARY_DAYS +
                    FEBRUARY_DAYS +
                    MARCH_DAYS +
                    APRIL_DAYS + 
                    MAY_DAYS +
                    JUNE_DAYS + days;   
        break;
    case AUGUST:
        acc_days += JANUARY_DAYS +
                    FEBRUARY_DAYS +
                    MARCH_DAYS +
                    APRIL_DAYS + 
                    MAY_DAYS +
                    JUNE_DAYS +
                    JULY_DAYS + days;      
        break;
    case SEPTEMBER:
        acc_days += JANUARY_DAYS +
                    FEBRUARY_DAYS +
                    MARCH_DAYS +
                    APRIL_DAYS + 
                    MAY_DAYS +
                    JUNE_DAYS +
                    JULY_DAYS +
                    AUGUST_DAYS + days;  
        break;
    case OCTOBER:
        acc_days += JANUARY_DAYS +
                    FEBRUARY_DAYS +
                    MARCH_DAYS +
                    APRIL_DAYS + 
                    MAY_DAYS +
                    JUNE_DAYS +
                    JULY_DAYS +
                    AUGUST_DAYS + 
                    SEPTEMBER_DAYS + days;   
        break;
    case NOVEMBER:
        acc_days += JANUARY_DAYS +
                    FEBRUARY_DAYS +
                    MARCH_DAYS +
                    APRIL_DAYS + 
                    MAY_DAYS +
                    JUNE_DAYS +
                    JULY_DAYS +
                    AUGUST_DAYS + 
                    SEPTEMBER_DAYS +
                    OCTOBER_DAYS + days;      
        break;
    case DECEMBER:
        acc_days += JANUARY_DAYS +
                    FEBRUARY_DAYS +
                    MARCH_DAYS +
                    APRIL_DAYS + 
                    MAY_DAYS +
                    JUNE_DAYS +
                    JULY_DAYS +
                    AUGUST_DAYS + 
                    SEPTEMBER_DAYS +
                    OCTOBER_DAYS +
                    NOVEMBER_DAYS + days;    
        break;
    default:
        return 0;
        break;
    }

    // Loop through the years checking for leap years. If a leap year
    // is found, then increase the counter.
    unsigned long february_29s = 0;
    for(unsigned long y = current_year; y < years + 1; y++){
        // Check if current iterating year is a leap year AND is not the
        // last year to iterate through
        if(y % 4 == 0 && y != years){
            february_29s++;
        }
        // If the task is scheduled to run on February 29th
        else if(y % 4 == 0 && y == years && months - 1 == FEBRUARY && days + 1 > FEBRUARY_DAYS){
            february_29s++;
        }
        // If the task is scheduled beyond February on a leap year
        else if(y % 4 == 0 && y == years && months - 1 > FEBRUARY){
            february_29s++;
        }
    }

    time_t added_time = time_start_year + (diff_years * 365 * 24 * 60 * 60) +
                        ((acc_days + february_29s) * 24 * 60 * 60);

    // Get current time and check for past time
    time_t time_now;
    std::time(&time_now);
    if(time_now >= added_time){
        return 0;
    }    

    return added_time;
}

time_t today_add_yyyymmdd_hms(std::string yyyymmdd_hms){
    if(validate_yyyymmdd_hms(yyyymmdd_hms) != ValidationCode::OK){
        return 0;
    }

    // Get time at start of current year
    time_t time_start_year = init_year();
    std::tm* time_start_year_struct;
    time_start_year_struct = gmtime(&time_start_year);

    // Convert hours and minutes to seconds and add them together
    unsigned long years = ((yyyymmdd_hms.at(0) & 0x0F) * 1000) + 
                          ((yyyymmdd_hms.at(1) & 0x0F) * 100) + 
                          ((yyyymmdd_hms.at(2) & 0x0F) * 10) + 
                          (yyyymmdd_hms.at(3) & 0x0F);
    unsigned long months = ((yyyymmdd_hms.at(5) & 0x0F) * 10) + 
                            (yyyymmdd_hms.at(6) & 0x0F);
    unsigned long days = ((yyyymmdd_hms.at(8) & 0x0F) * 10) + 
                          (yyyymmdd_hms.at(9) & 0x0F) - 1;
    unsigned long hours = ((yyyymmdd_hms.at(11) & 0x0F) * 10) + 
                           (yyyymmdd_hms.at(12) & 0x0F);
    unsigned long minutes = ((yyyymmdd_hms.at(14) & 0x0F) * 10) + 
                             (yyyymmdd_hms.at(15) & 0x0F);
    unsigned long seconds = ((yyyymmdd_hms.at(17) & 0x0F) * 10) + 
                             (yyyymmdd_hms.at(18) & 0x0F);                          

    // Since tm_year counts years since 1900, add 1900
    time_t current_year = time_start_year_struct->tm_year + 1900;

    // Get delta years and a check if less than 0
    unsigned long diff_years = years - current_year;
    if(diff_years < 0){
        return 0;
    }

    // Accumulate day count in year plus day in month
    unsigned long acc_days = 0;
    switch (months - 1)
    {
    case JANUARY:
        acc_days += days;
        break;
    case FEBRUARY:
        acc_days += JANUARY_DAYS + days;
        break;
    case MARCH:
        acc_days += JANUARY_DAYS +
                    FEBRUARY_DAYS + days;
        break;
    case APRIL:
        acc_days += JANUARY_DAYS +
                    FEBRUARY_DAYS +
                    MARCH_DAYS + days;
        break;
    case MAY:
        acc_days += JANUARY_DAYS +
                    FEBRUARY_DAYS +
                    MARCH_DAYS +
                    APRIL_DAYS + days;
        break;
    case JUNE:
        acc_days += JANUARY_DAYS +
                    FEBRUARY_DAYS +
                    MARCH_DAYS +
                    APRIL_DAYS + 
                    MAY_DAYS + days;
        break;
    case JULY:
        acc_days += JANUARY_DAYS +
                    FEBRUARY_DAYS +
                    MARCH_DAYS +
                    APRIL_DAYS + 
                    MAY_DAYS +
                    JUNE_DAYS + days;   
        break;
    case AUGUST:
        acc_days += JANUARY_DAYS +
                    FEBRUARY_DAYS +
                    MARCH_DAYS +
                    APRIL_DAYS + 
                    MAY_DAYS +
                    JUNE_DAYS +
                    JULY_DAYS + days;      
        break;
    case SEPTEMBER:
        acc_days += JANUARY_DAYS +
                    FEBRUARY_DAYS +
                    MARCH_DAYS +
                    APRIL_DAYS + 
                    MAY_DAYS +
                    JUNE_DAYS +
                    JULY_DAYS +
                    AUGUST_DAYS + days;  
        break;
    case OCTOBER:
        acc_days += JANUARY_DAYS +
                    FEBRUARY_DAYS +
                    MARCH_DAYS +
                    APRIL_DAYS + 
                    MAY_DAYS +
                    JUNE_DAYS +
                    JULY_DAYS +
                    AUGUST_DAYS + 
                    SEPTEMBER_DAYS + days;   
        break;
    case NOVEMBER:
        acc_days += JANUARY_DAYS +
                    FEBRUARY_DAYS +
                    MARCH_DAYS +
                    APRIL_DAYS + 
                    MAY_DAYS +
                    JUNE_DAYS +
                    JULY_DAYS +
                    AUGUST_DAYS + 
                    SEPTEMBER_DAYS +
                    OCTOBER_DAYS + days;      
        break;
    case DECEMBER:
        acc_days += JANUARY_DAYS +
                    FEBRUARY_DAYS +
                    MARCH_DAYS +
                    APRIL_DAYS + 
                    MAY_DAYS +
                    JUNE_DAYS +
                    JULY_DAYS +
                    AUGUST_DAYS + 
                    SEPTEMBER_DAYS +
                    OCTOBER_DAYS +
                    NOVEMBER_DAYS + days;    
        break;
    default:
        return 0;
        break;
    }

    // Loop through the years checking for leap years. If a leap year
    // is found, then increase the counter.
    unsigned long february_29s = 0;
    for(unsigned long y = current_year; y < years + 1; y++){
        // Check if current iterating year is a leap year AND is not the
        // last year to iterate through
        if(y % 4 == 0 && y != years){
            february_29s++;
        }
        // If the task is scheduled to run on February 29th
        else if(y % 4 == 0 && y == years && months - 1 == FEBRUARY && days + 1 > FEBRUARY_DAYS){
            february_29s++;
        }
        // If the task is scheduled beyond February on a leap year
        else if(y % 4 == 0 && y == years && months - 1 > FEBRUARY){
            february_29s++;
        }
    }

    time_t added_time = time_start_year + (diff_years * 365 * 24 * 60 * 60) +
                        ((acc_days + february_29s) * 24 * 60 * 60) + 
                        (hours * 60 * 60) + (minutes * 60) + seconds;

    // Get current time and check for past time
    time_t time_now;
    std::time(&time_now);
    if(time_now >= added_time){
        return 0;
    }    
    
    return added_time;
}

DatetimeFormat compute_datetime_format(std::string dt){
    DatetimeFormat dt_format = DatetimeFormat::INVALID_DATE_FORMAT;
    char c;
    unsigned int i = 0;
    
    if(dt.length() == 0){
        return dt_format;
    }
    c = dt.at(i);
    if(isdigit(c)){
        i++;
        goto P1;
    }
    else if(isalpha(c)){
        i++;
        goto P2;
    }
    return dt_format;
    P1:
    while(true){
        if(i >= dt.length()){
            break;
        }
        c = dt.at(i);
        if(c == '-'){
            c = dt.at(++i);
            goto P3;
        }
        else if(c == ':'){
            i++;
            goto P4;
        }
        i++;
    }
    return dt_format;
    P2:
    while(true){
        if(i >= dt.length()){
            break;
        }
        c = dt.at(i);
        if(c == ' '){
            i++;
            goto P5;
        }
        i++;
    }
    return dt_format;
    P3:
    while(true){
        if(i >= dt.length()){
            break;
        }
        c = dt.at(i);
        if(c == '-'){
            i++;
            goto P6;
        }
        i++;
    }
    return dt_format;
    P4:
    while(true){
        if(i >= dt.length()){
            break;
        }
        c = dt.at(i);
        if(c == ':'){
            i++;
            goto P7;
        }
        i++;
    }
    return dt_format;
    P5:
    while(true){
        if(i >= dt.length()){
            break;
        }
        c = dt.at(i);
        if(c == ':'){
            i++;
            goto P8;
        }
        i++;
    }
    return dt_format;
    P6:
    while(true){
        if(i >= dt.length()){
            dt_format = DatetimeFormat::YYYYMMDD;
            break;
        }
        c = dt.at(i);
        if(c == ' '){
            i++;
            goto P9;
        }
        i++;
    }
    return dt_format;
    P7:
    while(true){
        if(i >= dt.length()){
            dt_format = DatetimeFormat::HHMMSS;
            break;
        }
        i++;
    }
    return dt_format;
    P8:
    while(true){
        if(i >= dt.length()){
            break;
        }
        c = dt.at(i);
        if(c == ':'){
            i++;
            goto P10;
        }
        i++;
    }
    return dt_format;
    P9:
    while(true){
        if(i >= dt.length()){
            break;
        }
        c = dt.at(i);
        if(c == ':'){
            i++;
            goto P11;
        }
        i++;
    }
    return dt_format;
    P10:
    while(true){
        if(i >= dt.length()){
            dt_format = DatetimeFormat::WDAY_HHMMSS;
            break;
        }
        c = dt.at(i);
        i++;
    }
    return dt_format;
    P11:
    while(true){
        if(i >= dt.length()){
            break;
        }
        c = dt.at(i);
        if(c == ':'){
            i++;
            goto P12;
        }
        i++;
    }
    return dt_format;
    P12:
    while(true){
        if(i >= dt.length()){
            dt_format = DatetimeFormat::YYYYMMDD_HHMMSS;
            break;
        }
        c = dt.at(i);
        i++;
    }
    return dt_format;
}

ValidationCode validate_task_parms(cl::Config* task_config, std::string scripts_dir){
    ValidationCode ret_datetime_validate;
    DatetimeFormat format;
    time_t schedule_datetime;
    std::string value;
    std::string datetime_value;

    // Check if required fields exist
    if(!task_config->key_exists("Name")){
        return ValidationCode::MISSING_NAME_KEYVAL;
    }
    if(!task_config->key_exists("ScriptFilename")){
        return ValidationCode::MISSING_SCRIPTFN_KEYVAL;
    }
    if(!task_config->key_exists("Frequency")){
        return ValidationCode::MISSING_FREQUENCY_KEYVAL;
    }
    if(!task_config->key_exists("Datetime")){
        return ValidationCode::MISSING_DATETIME_KEYVAL;
    }

    // Check if name exceeds 16 characters in length
    value = task_config->get_value("Name")->get_data<std::string>();
    if(value.length() > TASK_NAME_FIELD_MAX_LEN){
        return ValidationCode::INVALID_NAME_LENGTH;
    }

    // Check if script file exists
    value = task_config->get_value("ScriptFilename")->get_data<std::string>();
    if(!std::filesystem::exists(scripts_dir + value)){
        return ValidationCode::SCRIPT_NOT_FOUND;
    }

    // Check if frequency value if valid
    value = task_config->get_value("Frequency")->get_data<std::string>();
    if(value != "Once" && value != "Hourly" && value != "Daily" &&
       value != "Weekly" && value != "Monthly" && value != "Yearly"){
           return ValidationCode::BAD_FREQUENCY_VALUE;
    }

    // Validate datetime depending on frequency value
    datetime_value = task_config->get_value("Datetime")->get_data<std::string>();
    if(value == "Once"){
        // Get datetime format, no validation performed at this step
        format = compute_datetime_format(datetime_value);
        switch ((int)format){
        case (int)DatetimeFormat::HHMMSS:
            ret_datetime_validate = validate_hms(datetime_value);
            if(ret_datetime_validate != ValidationCode::OK){
                return ret_datetime_validate;
            }
            schedule_datetime = today_add_hms(datetime_value);
            break;
        case (int)DatetimeFormat::YYYYMMDD_HHMMSS:
            ret_datetime_validate = validate_yyyymmdd_hms(datetime_value);
            if(ret_datetime_validate != ValidationCode::OK){
                return ret_datetime_validate;
            }
            schedule_datetime = today_add_yyyymmdd_hms(datetime_value);
            break;
        case (int)DatetimeFormat::WDAY_HHMMSS:
            ret_datetime_validate = validate_wday_hms(datetime_value);
            if(ret_datetime_validate != ValidationCode::OK){
                return ret_datetime_validate;
            }
            schedule_datetime = today_add_wday_hms(datetime_value);
            break;
        case (int)DatetimeFormat::YYYYMMDD:
            ret_datetime_validate = validate_yyyymmdd(datetime_value);
            if(ret_datetime_validate != ValidationCode::OK){
                return ret_datetime_validate;
            }
            schedule_datetime = today_add_yyyymmdd(datetime_value);
            break;
        default:
            return ValidationCode::INCOMPATIBLE_ONCE_FREQ_DATETIME_FORMAT;
        }
    }
    else if(value == "Hourly"){
        // Get datetime format, no validation performed at this step
        format = compute_datetime_format(datetime_value);
        switch ((int)format){
        case (int)DatetimeFormat::HHMMSS:
            ret_datetime_validate = validate_hms(datetime_value);
            if(ret_datetime_validate != ValidationCode::OK){
                return ret_datetime_validate;
            }
            schedule_datetime = today_add_hms(datetime_value);
            break;
        case (int)DatetimeFormat::YYYYMMDD_HHMMSS:
            ret_datetime_validate = validate_yyyymmdd_hms(datetime_value);
            if(ret_datetime_validate != ValidationCode::OK){
                return ret_datetime_validate;
            }
            schedule_datetime = today_add_yyyymmdd_hms(datetime_value);
            break;
        default:
            return ValidationCode::INCOMPATIBLE_ONCE_FREQ_DATETIME_FORMAT;
        }
    }
    else if(value == "Daily"){
        if(!task_config->key_exists("Datetime")){
           return ValidationCode::MISSING_DATETIME_KEYVAL;
        }
        // Get datetime format, no validation performed at this step
        format = compute_datetime_format(datetime_value);
        switch ((int)format){
        case (int)DatetimeFormat::HHMMSS:
            ret_datetime_validate = validate_hms(datetime_value);
            if(ret_datetime_validate != ValidationCode::OK){
                return ret_datetime_validate;
            }
            schedule_datetime = today_add_hms(datetime_value);
            break;
        case (int)DatetimeFormat::YYYYMMDD_HHMMSS:
            ret_datetime_validate = validate_yyyymmdd_hms(datetime_value);
            if(ret_datetime_validate != ValidationCode::OK){
                return ret_datetime_validate;
            }
            schedule_datetime = today_add_yyyymmdd_hms(datetime_value);
            break;
        case (int)DatetimeFormat::WDAY_HHMMSS:
            ret_datetime_validate = validate_wday_hms(datetime_value);
            if(ret_datetime_validate  != ValidationCode::OK){
                return ret_datetime_validate;
            }
            schedule_datetime = today_add_wday_hms(datetime_value);
            break;
        default:
            return ValidationCode::INCOMPATIBLE_DAILY_FREQ_DATETIME_FORMAT;
        }
    }
    else if(value == "Weekly"){
        if(!task_config->key_exists("Datetime")){
           return ValidationCode::MISSING_DATETIME_KEYVAL;
        }
        // Get datetime format, no validation performed at this step
        format = compute_datetime_format(datetime_value);
        switch ((int)format){
        case (int)DatetimeFormat::HHMMSS:
            ret_datetime_validate = validate_hms(datetime_value);
            if(ret_datetime_validate != ValidationCode::OK){
                return ret_datetime_validate;
            }
            schedule_datetime = today_add_hms(datetime_value);
            break;
        case (int)DatetimeFormat::YYYYMMDD_HHMMSS:
            ret_datetime_validate = validate_yyyymmdd_hms(datetime_value);
            if(ret_datetime_validate != ValidationCode::OK){
                return ret_datetime_validate;
            }
            schedule_datetime = today_add_yyyymmdd_hms(datetime_value);
            break;
        case (int)DatetimeFormat::WDAY_HHMMSS:
            ret_datetime_validate = validate_wday_hms(datetime_value);
            if(ret_datetime_validate != ValidationCode::OK){
                return ret_datetime_validate;
            }
            schedule_datetime = today_add_wday_hms(datetime_value);
            break;
        case (int)DatetimeFormat::YYYYMMDD:
            ret_datetime_validate = validate_yyyymmdd(datetime_value);
            if(ret_datetime_validate != ValidationCode::OK){
                return ret_datetime_validate;
            }
            schedule_datetime = today_add_yyyymmdd(datetime_value);
            break;
        default:
            return ValidationCode::INCOMPATIBLE_WEEKLY_FREQ_DATETIME_FORMAT;
        }
    }
    else if(value == "Monthly"){
        if(!task_config->key_exists("Datetime")){
           return ValidationCode::MISSING_DATETIME_KEYVAL;
        }
        // Get datetime format, no validation performed at this step
        format = compute_datetime_format(datetime_value);
        switch ((int)format){
        case (int)DatetimeFormat::HHMMSS:
            ret_datetime_validate = validate_hms(datetime_value);
            if(ret_datetime_validate != ValidationCode::OK){
                return ret_datetime_validate;
            }
            schedule_datetime = today_add_hms(datetime_value);
            break;
        case (int)DatetimeFormat::YYYYMMDD_HHMMSS:
            ret_datetime_validate = validate_yyyymmdd_hms(datetime_value);
            if(ret_datetime_validate != ValidationCode::OK){
                return ret_datetime_validate;
            }
            schedule_datetime = today_add_yyyymmdd_hms(datetime_value);
            break;
        case (int)DatetimeFormat::YYYYMMDD:
            ret_datetime_validate = validate_yyyymmdd(datetime_value);
            if(ret_datetime_validate != ValidationCode::OK){
                return ret_datetime_validate;
            }
            schedule_datetime = today_add_yyyymmdd(datetime_value);
            break;
        default:
            return ValidationCode::INCOMPATIBLE_MONTHLY_FREQ_DATETIME_FORMAT;
        }
    }
    else if(value == "Yearly"){
        if(!task_config->key_exists("Datetime")){
           return ValidationCode::MISSING_DATETIME_KEYVAL;
        }
        // Get datetime format, no validation performed at this step
        format = compute_datetime_format(datetime_value);
        switch ((int)format){
        case (int)DatetimeFormat::YYYYMMDD_HHMMSS:
            ret_datetime_validate = validate_yyyymmdd_hms(datetime_value);
            if(ret_datetime_validate != ValidationCode::OK){
                return ret_datetime_validate;
            }
            schedule_datetime = today_add_yyyymmdd_hms(datetime_value);
            break;
        case (int)DatetimeFormat::YYYYMMDD:
            ret_datetime_validate = validate_yyyymmdd(datetime_value);
            if(ret_datetime_validate != ValidationCode::OK){
                return ret_datetime_validate;
            }
            schedule_datetime = today_add_yyyymmdd(datetime_value);
            break;
        default:
            return ValidationCode::INCOMPATIBLE_YEARLY_FREQ_DATETIME_FORMAT;
        }
    }

    // Check if datetime is in the past
    if(schedule_datetime <= 0){
        return ValidationCode::PASSED_DATETIME;
    }
    return ValidationCode::OK;
}

} // namespace ts