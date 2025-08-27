#!/bin/bash

clear
echo "./philo 5 800 200 200 7"
echo "No philo should die and simulation stop for 7 times eat"
sleep 1
valgrind --tool=helgrind ./philo 5 800 200 200 7
