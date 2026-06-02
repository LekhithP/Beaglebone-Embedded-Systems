/*******************************************
Lab 1
02/19/2026 Lekhith Ponnaluru
*******************************************/
#include <stdio.h>
#include <time.h>
#define BUF_SIZE 15
struct Measure {
    struct timespec timestamp;
    int mean;
};
void read(int buffer[]) {
    printf("Enter 15 different numbers:\n");
    for (int i = 0; 
    i < BUF_SIZE; 
    ++i) {
        printf("Number %d: ", i + 1);
        scanf("%d", &buffer[i]);
    }
}
struct Measure MeanAndTime(int buffer[]) {
    struct Measure result;
    clock_gettime(CLOCK_MONOTONIC, &result.timestamp);
    int sum = 0;
    for (int i = 0; 
    i < BUF_SIZE; 
    ++i) {
        sum += buffer[i];
    }
    result.mean = sum / BUF_SIZE;
    return result;
}
int main() {
    int buffer[BUF_SIZE];
    struct Measure measure;
    for (int round = 0; 
    round < 2; 
    ++round) {
        read(buffer);
        measure = MeanAndTime(buffer);
        printf("(Round %d) Timestamp: %ld.%09ld, Mean: %d\n",
               round + 1,
               measure.timestamp.tv_sec,
               measure.timestamp.tv_nsec,
               measure.mean);
    }
    return 0;
}