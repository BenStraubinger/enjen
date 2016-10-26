#!/usr/bin/env bash

echo -e "\nSetting Up OSX Build: \n"


./build-libs.sh
if [[ "$?" -ne 0 ]]; then
	exit 1
fi


cmake -G "Unix Makefiles" 
if [[ "$?" -ne 0 ]]; then
	echo -e "\n\n  ERROR: Failed to generate Makefile. \n"
	exit 2
fi

echo -e "\nOSX build files were created successfully. \n"


echo -e "\nBuilding: \n"

make
if [[ "$?" -ne 0 ]]; then
	echo -e "\n\n  ERROR: OSX build failed. \n"
	exit 3
fi


echo -e "\nOSX build completed successfully. \n"
exit 0
