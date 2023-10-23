#!/bin/sh

# kill Camera streaming
sudo kill $(ps -ef | grep 'python3 stream.py' | awk '{print $2}')
