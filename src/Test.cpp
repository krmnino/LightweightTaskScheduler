#include <iostream>
#include <iomanip>

#define TIMEZONE -4

time_t init_day(){
    std::time_t time_now;
    std::tm* struct_time_now;

    // Get current time
    std::time(&time_now);
    // Convert to struct
    struct_time_now = std::gmtime(&time_now);

    // Get hours, minutes, and seconds. Convert to seconds 
    int hrs_2_sec = (struct_time_now->tm_hour + TIMEZONE) * 60 * 60;
    int min_2_sec = struct_time_now->tm_min * 60;
    int sec = struct_time_now->tm_sec;

    // Add converted hours and minutes to total seconds
    sec += hrs_2_sec + min_2_sec;

    std::cout << ctime(&time_now) << std::endl;

    // Subtract time
    time_now -= sec;

    std::cout << ctime(&time_now) << std::endl;

    return time_now;
}

time_t time_now_add_hms(std::string hms){
    std::tm time_input_hms;
    std::istringstream hms_ss(hms.c_str());
    hms_ss >> std::get_time(&time_input_hms, "%H:%M:%S");

    std::time_t time_hms = mktime(&time_input_hms);

    // Get hours, minutes, and seconds. Convert to seconds 
    int hrs_2_sec = time_input_hms.tm_hour * 60 * 60;
    int min_2_sec = time_input_hms.tm_min * 60;
    int sec = time_input_hms.tm_sec;

    // Add converted hours and minutes to total seconds
    sec += hrs_2_sec + min_2_sec;

    std::time_t time_now = init_day();

    time_now += sec;

    std::cout << ctime(&time_now) << std::endl;

    return time_now;
}

int main(){
    init_day();
    time_now_add_hms("12:34:90");
    /*
    // get current time
    std::time_t tm_now;
    std::time(&tm_now);

    struct std::tm tm;
    std::istringstream ss("12:00:00");
    ss >> std::get_time(&tm, "%H:%M:%S"); // or just %T in this case

    int sec_hours = tm.tm_hour * 60 * 60;
    int sec_minutes = tm.tm_min * 60;
    int seconds = tm.tm_sec;
    int total = sec_hours + sec_minutes + seconds;

    //std::cout << total << std::endl;

    std::time_t time = mktime(&tm);
    std::time_t new_time = tm_now - total;

    std::gmtime(&tm_now);
    std::gmtime(&new_time);

    //std::cout << ctime(&time);
    //std::cout << ctime(&tm_now);
    std::cout << ctime(&new_time);


    std::cout << tm.tm_hour << std::endl;
    */
    return 0;
}