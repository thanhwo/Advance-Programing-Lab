#!/bin/bash

read -p "Enter file name: " filename
read -p "Enter keyword: " keyword

if [ -f "$filename" ]; then
    if grep -q "$keyword" "$filename"; then
        # Count the number of lines containing the keyword
        line_count=$(grep -c "$keyword" "$filename")
        echo "Total lines containing the keyword: $line_count"
        
        # Display the lines containing the keyword
        echo "Lines containing the keyword:"
        grep -n "$keyword" "$filename"
        
        # Save all results to a new file
        output_file="search_result.txt"
        grep -n "$keyword" "$filename" > "$output_file"
        echo "Results saved to $output_file"
    else
        echo "Keyword not found in the file."
    fi
else
    echo "File does not exist."
fi
