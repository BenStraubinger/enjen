#!/usr/bin/env bash

echo -e "\nStarting Cleanup: \n"


echo -e "  Cleaning up CMake files..."
rm -rf CMakeCache.txt CMakeFiles/ Makefile cmake_install.cmake
echo "  Done."

echo -e "\n  Cleaning up Conan build files..."
rm -rf conanbuildinfo.* conaninfo.txt
echo "  Done."

if [[ -f enjen.sln ]]; then
	echo -e "\n  Cleaning up Visual Studio project files..."
	rm -rf enjen.sln *.vcxproj* *.VC.db lib/ x64/ enjen.dir
	echo "  Done."
fi

echo -e "\n  Cleaning up binary files..."
rm -rf bin/
echo "  Done."


echo -e "\nCleanup completed successfully. \n"
exit 0
