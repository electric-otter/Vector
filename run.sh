#!/bin/bash
read input
if command -v "$input" &>/dev/null; then
exec "$input"
fi
else
echo "Vector input error. What you typed: $input, If you think this is a bug in the vector language dont hesitate to report a issue in our repository."
