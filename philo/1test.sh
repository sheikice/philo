#!/bin/bash

clear
echo "./philo 1 800 200 200 50"
echo "Philo shouldnt eat and die"
sleep 1
valgrind --tool=helgrind ./philo 1 800 200 200 50
