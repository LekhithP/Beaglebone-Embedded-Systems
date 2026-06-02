#!/bin/bash
config-pin P9_14 pwm
sleep 1
echo 0 > /sys/class/pwm/pwmchip4/pwm-4:0/enable
echo 1000000000 > /sys/class/pwm/pwmchip4/pwm-4:0/period
echo 500000000 > /sys/class/pwm/pwmchip4/pwm-4:0/duty_cycle
echo 1 > /sys/class/pwm/pwmchip4/pwm-4:0/enable