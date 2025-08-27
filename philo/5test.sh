#!/bin/bash

clear
echo "./philo 4 310 100 200"
echo "One philo should die"
sleep 1
valgrind --tool=helgrind ./philo 4 310 200 100 50
