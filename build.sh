#!/usr/bin/env bash

conan install . --build=missing
cmake -G "Unix Makefiles" 
make
bash ./run.sh
