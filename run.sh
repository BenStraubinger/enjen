#!/usr/bin/env bash

echo -e "\nRunning: \n"


BIN_PATH="bin/enjen"


if [[ ! -f "$BIN_PATH" ]]; then
	echo -e "\n  ERROR: Could not find binary: $BIN_PATH \n"
	exit 1
fi


pushd ./install_root/ 2>&1 >> /dev/null

../$BIN_PATH
RV=$?

popd 2>&1 >> /dev/null


echo -e "\nRun completed successfully. \n"
exit $RV
