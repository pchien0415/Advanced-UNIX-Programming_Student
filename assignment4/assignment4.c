#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

int main() {
    //set the time data type
    time_t current_time; 
    struct tm* timeinfo;
    // use for strftime
    char buffer[64];

    // Display the current time in the "Asia/Taipei" time zone.
    setenv("TZ", "Asia/Taipei", 1);
    tzset();
    
    time(&current_time);
    timeinfo = localtime(&current_time);
    
    strftime(buffer, sizeof(buffer), "%a %b %d %H:%M:%S %Z %Y", timeinfo);
    printf("%s\n", buffer); // Current time in Asia/Taipei: 

    // Change the time zone to "Australia/Sydney" and display the current time.
    setenv("TZ", "Australia/Sydney", 1);
    tzset();
    
    time(&current_time);
    timeinfo = localtime(&current_time);
    memset(buffer, 0, sizeof(buffer));  // Clear the buffer to reuse it.
    
    strftime(buffer, sizeof(buffer), "%a %b %d %H:%M:%S %Z %Y", timeinfo);
    printf("%s\n", buffer); // Current time in Australia/Sydney: 

    return 0;
}
