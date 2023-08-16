#!/bin/bash
echo build begin
rm -rf ./build
cmake -S ./cmake -B build
cmake --build build
echo build end

