#!/bin/sh

if [ -z "$1" ]; then
    echo "Please provide a decimal number."
    exit 1
fi


echo "Hexadecimal value:"
echo "obase=16; $1" | bc
