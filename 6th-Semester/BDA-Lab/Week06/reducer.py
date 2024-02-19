#!/usr/bin/env python

import sys

total_sum = 0
count = 0

for line in sys.stdin:
    # Split the line into words
    words = line.strip().split()

    if len(words) == 2:
        key, value = words
        if key == "numeric":
            total_sum += float(value)
            count += 1

# Calculate the average
average = total_sum / count if count > 0 else 0

print("Average:", average)
