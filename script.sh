#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <file>"
    exit 1
fi

input_file="$1"
output_file="${input_file%.txt}_tabs.txt"

# Use sed to replace consecutive whitespace characters with a single tab
sed 's/[[:space:]]\{1,\}/\t/g' "$input_file" > "$output_file"

echo "Whitespace in $input_file replaced with tabs and saved as $output_file"
