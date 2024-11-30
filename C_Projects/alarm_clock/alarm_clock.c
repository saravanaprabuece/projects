#include <stdio.h>
#include <time.h>
#include <unistd.h> // For sleep()

int main() {
    int alarm_hour, alarm_minute;
    int current_hour, current_minute, current_second;

    printf("Enter alarm time (HH MM): ");
    scanf("%d %d", &alarm_hour, &alarm_minute);

    if (alarm_hour < 0 || alarm_hour > 23 || alarm_minute < 0 || alarm_minute > 59) {
        printf("Invalid time format! Please enter a valid time (HH: 0-23, MM: 0-59).\n");
        return 1;
    }

    printf("Alarm set for %02d:%02d\n", alarm_hour, alarm_minute);

    while (1) {
        // Get current time
        time_t now = time(NULL);
        struct tm *local = localtime(&now);

        current_hour = local->tm_hour;
        current_minute = local->tm_min;
        current_second = local->tm_sec;

        // Display the current time
        printf("Current time: %02d:%02d:%02d\r", current_hour, current_minute, current_second);
        fflush(stdout);

        // Check if it's time for the alarm
        if (current_hour == alarm_hour && current_minute == alarm_minute) {
            printf("\n\n*** ALARM! Time to wake up! ***\n");
            break;
        }

        // Wait for a second before updating the time
        sleep(1);
    }
    getch();
    return 0;
}
