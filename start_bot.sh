#!/bin/sh

if ! pgrep fototrak > /dev/null 2>&1; then
    /home/ec2-user/fototrak_bot/fototrak
fi
