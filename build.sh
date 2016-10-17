#!/usr/bin/env bash

echo -e "\nStarting Build: \n"


conan install . --build=missing
if [[ "$?" -ne 0 ]]; then
	echo -e "\n\n  ERROR: Failed to install prerequisites. See https://www.conan.io/ for more info. \n"
	exit 1
fi


cmake -G "Unix Makefiles" 
if [[ "$?" -ne 0 ]]; then
	echo -e "\n\n  ERROR: Failed to generate Makefile. \n"
	exit 2
fi


make
if [[ "$?" -ne 0 ]]; then
	echo -e "\n\n  ERROR: Failed to build. \n"
	exit 3
fi


echo -e "\nBuild completed successfully. \n"


bash ./run.sh
if [[ "$?" -ne 0 ]]; then
	echo -e "\n\n  ERROR: Failed to run the build. \n"
	exit 4
fi


exit 0
