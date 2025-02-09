#!/bin/sh
rm -rf ~/Library/Audio/Plug-Ins/Components/AUv2Lab.component
rm -rf ~/Library/Caches/AudioUnitCache
rm -rf ~/Library/Preferences/com.apple.audio.InfoHelper.plist
killall -9 AudioComponentRegistrar

