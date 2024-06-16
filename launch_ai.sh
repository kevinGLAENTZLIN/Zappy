#!/bin/bash

IP="127.0.0.1"
PORT="4242"

launch_ai() {
    ./zappy_ai -p 4242 -n Team1 -h 127.0.0.1
}

for ((i=1; i<=10; i++)); do
    launch_ai &
done
