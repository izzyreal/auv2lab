#!/bin/sh

PLIST_FILE="./build-resources/Info.plist"

CURRENT_VERSION=$(/usr/libexec/PlistBuddy -c "Print :AudioComponents:0:version" "$PLIST_FILE")
NEW_VERSION=$((CURRENT_VERSION + 1))

/usr/libexec/PlistBuddy -c "Set :AudioComponents:0:version $NEW_VERSION" "$PLIST_FILE"

echo "Updated version: $NEW_VERSION"

