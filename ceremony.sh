#!/bin/sh
./refresh-au.sh
./bump-version.sh

sleep 1

xcodebuild \
    -project ./build-xcode/AUv2Lab.xcodeproj \
    -scheme AUv2Lab \
    -destination 'platform=OS X,arch=arm64'

sleep 1

auval -v aumu IauL Izmr

sleep 1

./refresh-au.sh

sleep 1

xcodebuild \
    -project ./build-xcode/AUv2Lab.xcodeproj \
    -scheme AUv2Lab \
    -destination 'platform=OS X,arch=arm64'

sleep 1

auval -v aumu IauL Izmr

