#!/bin/sh

# kill Camera streaming
sudo kill $(ps -ef | grep 'python3 camera/stream.py' | awk '{print $2}')
