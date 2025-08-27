#!/bin/bash

clear
echo "./philo 4 410 200 200"
echo "No philo should die"
sleep 1
valgrind --tool=helgrind ./philo 4 410 200 200 50
