#!/bin/bash

# File to store the results
output_file="result.txt"

# Clear the output file if it already exists
>"${output_file}"

# Check if at least one mask is provided
if [[ $# -eq 0 ]]; then
	echo "Usage: $0 <file/directory mask> [additional masks...]"
	exit 1
fi

# Temporary file to store the list of found files
temp_file_list=$(mktemp)

# Iterate over each mask provided as an argument
for mask in "$@"; do
	# Find files matching the mask and append to the temporary file
	find . -type f -name "${mask}" >>"${temp_file_list}"
done

# Sort the list of files
sort "${temp_file_list}" | while read -r file; do
	# Output the file path
	echo "File: ${file}" >>"${output_file}"
	echo "Contents:" >>"${output_file}"
	# Output the file contents
	cat "${file}" >>"${output_file}"
	# Add a separator
	echo -e "\n---\n" >>"${output_file}"
done

# Clean up the temporary file
rm "${temp_file_list}"

echo "Results have been written to ${output_file}."
