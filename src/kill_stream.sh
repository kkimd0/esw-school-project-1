#!/bin/sh

# kill Camera streaming
sudo kill $(ps -ef | grep 'python3 src/stream.py' | awk '{print $2}')
