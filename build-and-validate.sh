#!/bin/bash
AU_TYPE="${1:-aumu}"
AU_SUBTYPE="Ia3I"

if [[ "$AU_TYPE" != "aumu" && "$AU_TYPE" != "aumf" ]]; then
    echo "Usage: $0 [AU_TYPE]"
    echo "Available types: aumu, aumf (default: aumu)"
    exit 1
fi

[[ "$AU_TYPE" == "aumf" ]] && AU_SUBTYPE="Ia3F"

AU_MANUFACTURER="Izmr"
XCODE_PROJECT="./build-xcode/AUv3Lab.xcodeproj"
XCODE_TARGET="AUv3Lab"

cmake -B build-xcode -G Xcode

./refresh-au.sh

xcodebuild -project $XCODE_PROJECT -scheme $XCODE_TARGET -destination 'platform=OS X,arch=arm64'

auval -v $AU_TYPE $AU_SUBTYPE $AU_MANUFACTURER

