#!/bin/bash

IP="127.0.0.1"
PORT="4242"

launch_client()
{
    {
        echo "Team1"

        sleep 1
        while true; do
            echo "Forward"
            # echo "Broadcast `cat /dev/urandom | head -n 8000`"
        done
    } | ncat $IP $PORT -C
}
for ((i=1; i<=1000; i++)); do
    launch_client &
done