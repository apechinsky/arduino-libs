#!/bin/bash

libs="
ButtonSet
CircularBuffer
Debouncer
DigitalDevice
MHZ19
MemoryFree
AtCommandDevice
HttpClient
CsSim800
ThingSpeak
"

scriptDir=$(cd $(dirname $0); pwd)

buildDir="$scriptDir/build"

mkdir -p "$buildDir" 

for lib in $libs; do

    echo "Registering library '$lib'"
    version=$(jq -r '.version' $lib/library.json)

    echo "packaging $lib/$version"
    # pio package pack $lib
    pio package pack -o "$buildDir" $lib 

    package="$buildDir/$lib-$version.tar.gz"

    echo "publishing $package"
    pio package publish --notify $package

done
