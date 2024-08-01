#!/bin/bash

while getopts L:G: flag
do
    case "${flag}" in
        L) logging=${OPTARG};;
        G) group=${OPTARG};;
    esac
done

FLIP_DIR="/home/mstasiaknordic/workspace/dacflip"
echo "------ BUILDING SAMPLE ------"
west build -p -b flipdk/flip/cpuapp

cp build/zephyr/zephyr.elf $FLIP_DIR
cd $FLIP_DIR
echo "------ GENERATING SAMPLES ------"
python3 generate_dacSamples.py
cd build
echo "------ BUILDING FLIP ------"
cmake ../ -G Ninja -DDEVELOPER=ON
ninja -j$(nproc)
cd ..
echo "------ RUNNING FLIP ------"
./flip -L $logging -G $group
