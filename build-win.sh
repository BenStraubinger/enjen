#!/usr/bin/env bash

echo -e "\nSetting Up Windows Build: \n"


./build-libs.sh
if [[ "$?" -ne 0 ]]; then
	exit 1
fi


cmake -G "Visual Studio 14 2015 Win64" .
if [[ "$?" -ne 0 ]]; then
	echo -e "\n\n  ERROR: Failed to generate Visual Studio project files. \n"
	echo -e "  Check the system is configured with the required build tools. \n"
	exit 2
fi


echo -e "\nWindows build files were created successfully. \n"


echo -e "\nBuilding: \n"

MSBUILD_PATH="/cygdrive/c/Program Files (x86)/MSBuild/14.0/Bin/amd64/MSBuild.exe"
"$MSBUILD_PATH" enjen.sln
if [[ "$?" -ne 0 ]]; then
	echo -e "\n\n  ERROR: Windows build failed. \n"
	exit 3
fi


echo -e "\nWindows build completed successfully. \n"
exit 0
