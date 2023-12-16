#!/bin/bash
pid_max=$(cat /proc/sys/kernel/pid_max)
echo "MAXIMUM PID VALUE: $pid_max"
