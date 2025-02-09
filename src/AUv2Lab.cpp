#include "AUv2Lab.h"
#include <thread>
#include <iostream>
#include <AudioUnitSDK/AUPlugInDispatch.h>

#pragma mark AUv2Lab Methods

extern "C" void* AUv2LabFactory (AudioComponentDescription* inDesc);
AUSDK_EXPORT extern "C" void* AUv2LabFactory (AudioComponentDescription* inDesc)
{
    return ausdk::AUMusicDeviceFactory<AUv2Lab>::Factory (inDesc);
}

AUv2Lab::AUv2Lab(AudioUnit inComponentInstance)
: ausdk::MusicDeviceBase(inComponentInstance, 1, 1)
{
    printf("============ AUv2Lab constructor =========\n");
    CreateElements();
}

ComponentResult AUv2Lab::Render (AudioUnitRenderActionFlags& ioActionFlags,
                        const AudioTimeStamp& inTimeStamp,
                        const UInt32 nFrames)
{
    return noErr;
}

bool AUv2Lab::CanScheduleParameters() const
{
    return false;
}

bool AUv2Lab::StreamFormatWritable (AudioUnitScope scope, AudioUnitElement element) {
    return false;
}

ComponentResult AUv2Lab::StartNote (MusicDeviceInstrumentID, MusicDeviceGroupID, NoteInstanceID*, UInt32, const MusicDeviceNoteParams&) { return noErr; }

ComponentResult AUv2Lab::StopNote (MusicDeviceGroupID, NoteInstanceID, UInt32)
{
    return noErr;
}
