/*******************************************
Lab 2
03/02/2026 Lekhith Ponnaluru
*******************************************/

#include <stdio.h>
#include <unistd.h>
#include <time.h>
#define FILENAME "time_duration_file.txt"
#define LED_PATH "/sys/class/leds/beaglebone:green:usr1/brightness"
#define NUM_ENTRIES 375

int main() {
    printf("\n LED Flash Start \n");
    FILE *LEDHandle = NULL;
    FILE *timeDurationFile = fopen(FILENAME, "w"); // Open file for writing
    if (timeDurationFile == NULL) {
        printf("Error opening file for writing.\n");
        return 1;
    }
    struct timespec start, end;
    long long time_duration; // Blink the LED and measure time difference for 375 iterations
    for (int i = 0; i < NUM_ENTRIES; i++) {
        clock_gettime(CLOCK_MONOTONIC, &start);
        if ((LEDHandle = fopen(LED_PATH, "r+")) != NULL) {
            fwrite("1", sizeof(char), 1, LEDHandle); // Turn LED on
            fclose(LEDHandle);
        }
        usleep(800000); // Sleep for 800 milliseconds
        if ((LEDHandle = fopen(LED_PATH, "r+")) != NULL) {
            fwrite("0", sizeof(char), 1, LEDHandle); // Turn LED off
            fclose(LEDHandle);
        }
        clock_gettime(CLOCK_MONOTONIC, &end);
        time_duration = (end.tv_sec - start.tv_sec) * 1000000000LL + (end.tv_nsec - start.tv_nsec);
        fprintf(timeDurationFile, "%lld\n", time_duration); // Write time duration to file
    }
    fclose(timeDurationFile); // Close file
    printf("\n LED Flash End \n");
    return 0;
}