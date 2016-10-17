#!/usr/bin/env bash

echo -e "\nStarting Dependencies Build: \n"


conan install . --build=missing
if [[ "$?" -ne 0 ]]; then
	echo -e "\n\n  ERROR: Failed to install prerequisites. See https://www.conan.io/ for more info. \n"
	exit 1
fi


echo -e "\nBuild completed successfully. \n"
exit 0
