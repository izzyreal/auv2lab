#!/bin/sh

PLIST_FILE="../build-resources/AUv3/Info.plist"

for i in 0 1; do
    CURRENT_VERSION=$(/usr/libexec/PlistBuddy -c "Print :NSExtension:NSExtensionAttributes:AudioComponents:${i}:version" "$PLIST_FILE")
    NEW_VERSION=$((CURRENT_VERSION + 1))
    /usr/libexec/PlistBuddy -c "Set :NSExtension:NSExtensionAttributes:AudioComponents:${i}:version $NEW_VERSION" "$PLIST_FILE"
    echo "Updated version component ${i}: $NEW_VERSION"
done
