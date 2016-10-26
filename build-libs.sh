#!/usr/bin/env bash

echo -e "\nBuilding C++ libraries with Conan: \n"

BUILD_CMD="conan install . --build=missing"
$BUILD_CMD
if [[ "$?" -ne 0 ]]; then
	echo -e "\n\n  ERROR: Failed to build the required libraries. \n"
	echo -e "  Check the system is configured with the required build tools. \n"
	exit 1
fi


echo -e "\nC++ Libraries were built successfully. \n"
exit 0
