#!/bin/bash

# Check if a file is provided as an argument
if [ $# -ne 1 ]; then
    echo "Usage: $0 <input_file>"
    exit 1
fi

input_file="$1"
output_file="${input_file%.txt}_formatted.txt"

# Use sed to replace multiple consecutive whitespaces with a single tab
sed -E 's/[[:space:]]+/	/g' "$input_file" > "$output_file"

echo "Formatted text saved to $output_file"
