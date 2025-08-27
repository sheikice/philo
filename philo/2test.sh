#!/bin/bash

clear
echo "./philo 5 800 200 200"
echo "No philo should die"
sleep 1
valgrind --tool=helgrind ./philo 5 800 200 200 50
