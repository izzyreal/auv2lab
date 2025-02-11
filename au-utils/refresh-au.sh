#!/bin/sh
find ~/git/auv3lab/build-xcode -type d -name "AUv3Lab.app" -exec rm -rf {} +
rm -rf ~/Library/Caches/AudioUnitCache
rm -rf ~/Library/Preferences/com.apple.audio.InfoHelper.plist
killall -9 AudioComponentRegistrar

