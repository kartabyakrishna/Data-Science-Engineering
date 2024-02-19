#!/usr/bin/env python

import sys

for line in sys.stdin:
    # Split the line into words
    words = line.strip().split()

    # Iterate through words and emit (key, value) pairs for numeric values
    for word in words:
        try:
            value = float(word)
            print("numeric", value)
        except ValueError:
            pass  # Ignore non-numeric values
