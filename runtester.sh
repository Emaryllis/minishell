#!/usr/bin/env bash

log_file_name=$(date +'%Y.%m.%d-%H.%M.%S').log

set -euo pipefail
DIR=$(pwd)
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

if [ $# -gt 0 ]; then
    args="$@"
else
    args="-a"
fi
mkdir -p ../logs
cd "$SCRIPT_DIR/tester"
echo "Running tests with arguments: $args"
python3 minitester.py "$args" > "../logs/$log_file_name"
cd "$DIR"
echo "Test log saved to logs/$log_file_name"