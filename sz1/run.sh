#!/bin/sh

while true; do
  current_time=$(date +"%H %M %S.%1N")
  echo "$current_time" | ./a.out
  sleep 0.1  # Sleep for 300 milliseconds
done

