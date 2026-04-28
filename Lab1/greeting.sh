#!/bin/sh

#Duy Thanh
#greeting.sh
#Display user and system info

echo "Hello +$USER"

uname -a

id -g

date

ls

echo "TERM + $TRM"
echo "PATH + $PATH"
echo "HOME + $HOME"

echo "Goodbye +$(date +%T)"
