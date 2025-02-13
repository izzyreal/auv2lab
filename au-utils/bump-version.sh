#!/bin/sh

PLIST_FILE="../src/extension/Info.plist"

for i in 0 0; do
    CURRENT_VERSION=$(/usr/libexec/PlistBuddy -c "Print :NSExtension:NSExtensionAttributes:AudioComponents:${i}:version" "$PLIST_FILE")
    NEW_VERSION=$((CURRENT_VERSION + 1))
    /usr/libexec/PlistBuddy -c "Set :NSExtension:NSExtensionAttributes:AudioComponents:${i}:version $NEW_VERSION" "$PLIST_FILE"
    echo "Updated version component ${i}: $NEW_VERSION"
done
