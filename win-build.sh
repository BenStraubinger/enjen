#!/usr/bin/env bash

echo -e "\nSetting Up Windows Build: \n"


conan install . --build=missing
if [[ "$?" -ne 0 ]]; then
	echo -e "\n\n  ERROR: Failed to install prerequisites. See https://www.conan.io/ for more info. \n"
	exit 1
fi


cmake -G "Visual Studio 14 2015 Win64" .
if [[ "$?" -ne 0 ]]; then
	echo -e "\n\n  ERROR: Failed to generate Visual Studio project files. \n"
	exit 2
fi


exit 0
