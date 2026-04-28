#!/bin/bash

echo "Enter n:"
read n

if [ "$n" -lt 0 ]; then
    echo "n > 0, Try again!"
    exit 1
fi

a=0
b=1

 for ((i=0; i<=n; i++))
 do
	echo -n "$a "
        temp=$((a + b))
        a=$b
	b=$temp
done
echo
