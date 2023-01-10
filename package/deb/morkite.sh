#!/usr/bin/env bash

#########################
# Morkite Runner Script #
#########################

# Morkite needs to run in the install directory to have access to the assets and
# scripts. This script will handle that logic and future startup logic.

echo 'Starting the Morkite engine...'

cd /opt/morkite/
./bin/morkite $@