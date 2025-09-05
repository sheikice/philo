#!/bin/bash

clear
echo "./philo 5 1000 200 200 20"
echo "No philo should die"
sleep 1
valgrind --tool=helgrind ./philo 5 1000 200 200 20
