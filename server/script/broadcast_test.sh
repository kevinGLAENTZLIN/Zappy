#!/bin/bash

IP="127.0.0.1"
PORT="4242"

{
    echo "Team1"

    sleep 1
    while true; do
        echo "Broadcast `cat /dev/urandom | head -n 8000`"
    done
} | ncat $IP $PORT -C
