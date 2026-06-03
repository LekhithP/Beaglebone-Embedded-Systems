# BeagleBone Embedded Systems
A suite of embedded Linux labs written in C for the BeagleBone Black, progressing from basic timing and LED control to multithreaded systems programming. All hardware interfaces are implemented directly through the Linux device filesystem — no abstraction libraries.
# Hardware
- BeagleBone Black (AM335x ARM Cortex-A8)
- Ubuntu Linux, gcc toolchain
- Peripherals: onboard LEDs, GPIO buttons, PWM output
# Labs
Lab 1 — Timing and Mean Computation

Reads 15 integers across two rounds, computes the mean, and timestamps each computation using `CLOCK_MONOTONIC`. Demonstrates custom struct design with embedded `timespec`, fixed-size buffers, and nanosecond-precision timing in C.

Key concepts: `clock_gettime`, `struct timespec`, fixed-size buffers, `scanf`

Lab 2 — LED Blink with Timing Measurement

Blinks a BeagleBone onboard LED 375 times via the Linux LED sysfs interface (`/sys/class/leds/`), measuring the duration of each blink cycle in nanoseconds and writing results to a file. The timing data reveals OS scheduling jitter on the first iteration followed by stable ~800ms cycles.
 
Key concepts: sysfs LED control, `usleep`, `clock_gettime`, file I/O, timing analysis

The graph below shows measured blink durations across all 375 iterations. The spike on iteration 1 reflects first-call OS overhead; subsequent readings stabilize tightly around 800ms.
<img width="2119" height="993" alt="Picture1" src="https://github.com/user-attachments/assets/520ee79d-526c-4d12-a4f3-b01f16f9fd4e" />

Lab 3 — GPIO Button-Controlled PWM
Two GPIO buttons trigger different PWM frequencies on the BeagleBone PWM interface (`/dev/bone/pwm/`). Button 1 plays a 100 Hz tone at 60% duty cycle for 5 seconds; Button 2 plays 1000 Hz at 70% duty cycle. Uses `config-pin` to configure pin modes at runtime.
 
Key concepts: GPIO sysfs, PWM via `/dev/bone/pwm/`, `config-pin`, polling loop, `usleep`
 
Helper scripts:
- `pwm_gen.sh` — configures and enables PWM on P9_14
- `pwm_stop.sh` — disables PWM and restores pin to GPIO mode
 
Lab 4 — GPIO Edge Detection with epoll
Detects 5 rising-edge GPIO events on pin 69 using `epoll` for non-blocking I/O, timestamps each event with `CLOCK_MONOTONIC`, and prints results. Demonstrates interrupt-driven hardware input without busy-waiting.
 
Key concepts: `epoll_create1`, `EPOLLPRI`, `lseek`, GPIO edge configuration via sysfs, `clock_gettime`
 
Lab 5 — Multithreaded Producer-Consumer with GPIO
The most complex lab. Implements a producer-consumer pipeline where an **input thread** detects 50 GPIO rising-edge events via `epoll` and writes timestamped records into a circular buffer, while an **output thread** concurrently reads from the buffer and writes to a file. Thread synchronization is handled with POSIX mutex locks and condition variables.
 
Key concepts: `pthreads`, `pthread_mutex_t`, `pthread_cond_t`, circular buffer, `epoll`, `CLOCK_MONOTONIC`, producer-consumer pattern
 
Output data is saved to `Lekhith_Ponnaluru_data.txt` — each row contains a Unix timestamp (seconds + nanoseconds) and the thread ID of the input thread.
# Building
Each lab compiles with gcc on the BeagleBone Black. A `makefile` is included.
```bash
make lab1
make lab2
# etc.
```
GPIO and PWM operations require root or appropriate group permissions on the target hardware.
# Concepts Covered
|Concept|Labs|
|---|---|
|`clock_gettime`/nanosecond timing|1,2,4,5|
|Linux sysfs GPIO and LED control|2,3,4,5|
|PWM via `/dev/bone/pwm/`|3|
|`epoll` non-blocking I/O|4,5|
|POSIX pthreads|5|
|Mutex+condition variable synchronization|5|
|Producer-consumer circular buffer|5|
|File I/O|2,5|
