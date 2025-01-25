#!/bin/bash

read input
if command -v "$input" &>/dev/null; then
    exec "$input"
else
    echo "Vector input error. What you typed: $input, If you think this is a bug in the vector language, don't hesitate to report an issue in our repository."
fi
