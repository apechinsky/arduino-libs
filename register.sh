#!/bin/bash

libs="
ButtonSet
CircularBuffer
Debouncer
DigitalDevice
LICENSE
MZH19
MemoryFree
AtCommandDevice
HttpClient
CsSim800
ThingSpeak
"

for lib in $libs; do

    echo "Registering library '$lib'"
    version=$(jq -r '.version' $lib/library.json)

    echo "packaging $lib/$version"
    pio package pack $lib

    package="$lib-$version.tar.gz"

    echo "publishing $package"
    pio package publish --notify $package

done
