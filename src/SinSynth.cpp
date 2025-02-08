#include "SinSynth.h"
#include <thread>
#include <iostream>
#include <AudioUnitSDK/AUPlugInDispatch.h>

#pragma mark SinSynth Methods

extern "C" void* SinSynthFactory (AudioComponentDescription* inDesc);
AUSDK_EXPORT extern "C" void* SinSynthFactory (AudioComponentDescription* inDesc)
{
    return ausdk::AUMusicDeviceFactory<SinSynth>::Factory (inDesc);
}

SinSynth::SinSynth(AudioUnit inComponentInstance)
: ausdk::MusicDeviceBase(inComponentInstance, 1, 1)
{
    printf("============ SinSynth constructor =========\n");
    CreateElements();
}

ComponentResult SinSynth::Render (AudioUnitRenderActionFlags& ioActionFlags,
                        const AudioTimeStamp& inTimeStamp,
                        const UInt32 nFrames)
{
    return noErr;
}

bool SinSynth::CanScheduleParameters() const
{
    return false;
}

bool SinSynth::StreamFormatWritable (AudioUnitScope scope, AudioUnitElement element) {
    return false;
}

ComponentResult SinSynth::StartNote (MusicDeviceInstrumentID, MusicDeviceGroupID, NoteInstanceID*, UInt32, const MusicDeviceNoteParams&) { return noErr; }

ComponentResult SinSynth::StopNote (MusicDeviceGroupID, NoteInstanceID, UInt32)
{
    return noErr;
}
