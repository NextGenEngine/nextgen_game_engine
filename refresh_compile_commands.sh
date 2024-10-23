#!/usr/bin/env bash

# Name of the command to run
COMMAND="bazel run @hedron_compile_commands//:refresh_all"

# Path to the PID file (store it in the project directory)
PID_FILE="./.refresh_compile_commands.pid"

# Function to check if a PID corresponds to our command
is_process_running() {
	local pid=$1
	if [ -z "$pid" ]; then
		return 1 # PID is empty
	fi

	# Check if the process is running
	if ps -p "$pid" >/dev/null 2>&1; then
		# Get the command line of the process
		cmdline=$(ps -p "$pid" -o command=)
		if [[ $cmdline == *"$COMMAND"* ]]; then
			return 0 # Process is running and matches our command
		fi
	fi
	return 1 # Process not running or doesn't match
}

# Check if the PID file exists
if [ -f "$PID_FILE" ]; then
	# Read the PID from the file
	OLD_PID=$(cat "$PID_FILE")
	if is_process_running "$OLD_PID"; then
		echo "Terminating existing process: $OLD_PID"
		kill -TERM "$OLD_PID"
		# Wait for the process to terminate
		while is_process_running "$OLD_PID"; do
			sleep 0.1
		done
		echo "Process $OLD_PID terminated."
	else
		echo "No running process found with PID $OLD_PID."
	fi
fi

echo "Starting new process..."
# Start the command in the background
$COMMAND &
# Save its PID
NEW_PID=$!
echo "$NEW_PID" >"$PID_FILE"
echo "New process started with PID $NEW_PID."
