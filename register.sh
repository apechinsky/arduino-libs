#!/bin/bash

baseUrl=https://raw.githubusercontent.com/apechinsky/arduino-libs/master

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
    pio package publish $baseUrl/$lib/library.json

done
