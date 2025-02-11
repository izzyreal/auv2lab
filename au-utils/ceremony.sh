#!/bin/bash

if [[ "$1" != "aumu" && "$1" != "aumf" ]]; then
    echo "Usage: $0 <AU_TYPE>"
    echo "Available types: aumu, aumf"
    exit 1
fi

AU_TYPE="$1"
AU_SUBTYPE="Ia3I"
[[ "$AU_TYPE" == "aumf" ]] && AU_SUBTYPE="Ia3F"

AU_MANUFACTURER="Izmr"
XCODE_PROJECT="../build-xcode/AUv3Lab.xcodeproj"
XCODE_TARGET="AUv3Lab"

./refresh-au.sh
./bump-version.sh

sleep 1

xcodebuild -project $XCODE_PROJECT -scheme $XCODE_TARGET -destination 'platform=OS X,arch=arm64'

open -a "$(pwd)/../build-xcode/Debug/AUv3LabApp.app"

sleep 1

auval -v $AU_TYPE $AU_SUBTYPE $AU_MANUFACTURER

sleep 1

./refresh-au.sh

sleep 1

xcodebuild -project $XCODE_PROJECT -scheme $XCODE_TARGET -destination 'platform=OS X,arch=arm64'

open -a "$(pwd)/../build-xcode/Debug/AUv3LabApp.app"

sleep 1

auval -v $AU_TYPE $AU_SUBTYPE $AU_MANUFACTURER

