#!/bin/bash

# Check if the program is provided
if [ -z "$1" ]; then
    echo "Usage: $0 <program> [runs]"
    exit 1
fi

# Name of the compiled program
PROGRAM="$1"

# Number of times to run the program (default to 20 if not provided)
RUNS=${2:-20}

# Log file
LOGFILE="$1.log"

# Clear the log file
> $LOGFILE

# Run the program and log the output
for ((i = 1; i <= RUNS; i++)); do
    echo "Run #$i" 
    $PROGRAM | tee -a $LOGFILE
done