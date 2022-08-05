#include <iostream>
#include <iomanip>

#define DAYS_IN_WEEK 7
#define TIMEZONE -4

bool validate_hms(std::string hms){
    if(hms.length() != 8){
        return false;
    }
    unsigned int num;
    num = hms.at(0) & 0x0F;
    if(num < 0 | num > 2){
        return false;
    }
    num = hms.at(1) & 0x0F;
    if(num < 0 | num > 9){
        return false;
    }
    if(hms.at(2) != ':'){
        return false;
    }
    num = hms.at(3) & 0x0F;
    if(num < 0 | num > 5){
        return false;
    }
    num = hms.at(4) & 0x0F;
    if(num < 0 | num > 9){
        return false;
    }
    if(hms.at(5) != ':'){
        return false;
    }
    num = hms.at(6) & 0x0F;
    if(num < 0 | num > 5){
        return false;
    }
    num = hms.at(7) & 0x0F;
    if(num < 0 | num > 9){
        return false;
    }
    return true;
}

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

    // Subtract time
    time_now -= sec;

    return time_now;
}

time_t init_day_add_hms(std::string hms){
    if(!validate_hms(hms)){
        return 0;
    }
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

    return time_now;
}

time_t init_day_add_dhms(int d, std::string hms){
    if(!validate_hms(hms) | d < 0){
        return 0;
    }
    std::tm time_input_hms;
    std::istringstream hms_ss(hms.c_str());
    hms_ss >> std::get_time(&time_input_hms, "%H:%M:%S");

    std::time_t time_hms = mktime(&time_input_hms);


    // Get hours, minutes, and seconds. Convert to seconds 
    time_t days_2_sec = d * 24 * 60 * 60;
    int hrs_2_sec = time_input_hms.tm_hour * 60 * 60;
    int min_2_sec = time_input_hms.tm_min * 60;
    int sec = time_input_hms.tm_sec;

    // Add converted days, hours, and minutes to total seconds
    sec += days_2_sec + hrs_2_sec + min_2_sec;

    std::time_t time_now = init_day();

    time_now += sec;

    return time_now;
}

time_t init_day_add_wdhms(std::string wday, std::string hms){
    if(wday != "Mon" && wday != "Monday" && 
       wday != "Tue" && wday != "Tuesday" &&
       wday != "Wed" && wday != "Wednesday" &&
       wday != "Thr" && wday != "Thursday" &&
       wday != "Fri" && wday != "Friday" &&
       wday != "Sat" && wday != "Saturday" &&
       wday != "Sun" && wday != "Sunday"){
        return 0;
    }
    if(!validate_hms(hms)){
        return 0;
    }
    // Concatenate wday with hms
    wday += " " + hms;
    std::tm time_input_whms;
    std::istringstream whms_ss(wday.c_str());
    whms_ss >> std::get_time(&time_input_whms, "%a %H:%M:%S");
    
    // Get current time and convert to struct
    std::time_t time_now = init_day();
    std::tm* time_now_struct;
    time_now_struct = gmtime(&time_now);

    // Calculate days until desired weekday
    int diff_day;
    if(time_now_struct->tm_wday == time_input_whms.tm_wday){
        std::time_t now;
        std::time_t now_add_hms = init_day_add_hms(hms);
        std::time(&now);
        if(now < now_add_hms){
            time_now = now_add_hms;
        }
        else{
            time_now = init_day_add_dhms(DAYS_IN_WEEK, hms);
        }
    }
    else if(time_now_struct->tm_wday > time_input_whms.tm_wday){
        diff_day = time_now_struct->tm_wday - time_input_whms.tm_wday;
        diff_day = DAYS_IN_WEEK - diff_day;
        time_now = init_day_add_dhms(diff_day, hms);
    }
    else{
        diff_day = time_input_whms.tm_wday - time_now_struct->tm_wday;
        time_now = init_day_add_dhms(diff_day, hms);
    }
    return time_now;
    
    /*
    std::time_t time_hms = mktime(&time_input_whms);

    // Get hours, minutes, and seconds. Convert to seconds 
    int hrs_2_sec = time_input_whms.tm_hour * 60 * 60;
    int min_2_sec = time_input_whms.tm_min * 60;
    int sec = time_input_whms.tm_sec;

    // Add converted days, hours, and minutes to total seconds
    sec += hrs_2_sec + min_2_sec;

    std::time_t time_now = init_day();

    time_now += sec;
    */
}

int main(){
    time_t ret;
    
    //ret = init_day();
    //std::cout << ctime(&ret) << std::endl;

    //ret = time_now_add_hms("09:34:00");
    //std::cout << ctime(&ret) << std::endl;
    //
    //ret = time_now_add_dhms(1, "01:34:00");
    //std::cout << ctime(&ret) << std::endl;
    //
    //ret = time_now_add_dhms(9000, "01:34:00");
    //std::cout << ctime(&ret) << std::endl;
    //
    //bool v = validate_hms("01:34:00");
    //std::cout << v << std::endl;

    ret = init_day_add_wdhms("Sun", "01:34:00"); 
    std::cout << ctime(&ret) << std::endl;
    ret = init_day_add_wdhms("Mon", "01:34:00"); 
    std::cout << ctime(&ret) << std::endl;
    ret = init_day_add_wdhms("Tue", "01:34:00"); 
    std::cout << ctime(&ret) << std::endl;
    ret = init_day_add_wdhms("Wed", "01:34:00"); 
    std::cout << ctime(&ret) << std::endl;
    ret = init_day_add_wdhms("Thr", "01:34:00"); 
    std::cout << ctime(&ret) << std::endl;
    ret = init_day_add_wdhms("Fri", "01:34:00"); 
    std::cout << ctime(&ret) << std::endl;
    ret = init_day_add_wdhms("Sat", "01:34:00"); 
    std::cout << ctime(&ret) << std::endl;

    return 0;
}