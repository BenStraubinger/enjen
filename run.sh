#!/usr/bin/env bash

echo -e "\n\nRunning: ./bin/enjen \nFrom: ./install_root/ \n"
pushd ./install_root/
../bin/enjen
echo -e "\nDone.\n"
popd
