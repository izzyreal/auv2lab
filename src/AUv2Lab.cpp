#include "AUv2Lab.h"
#include <thread>
#include <iostream>
#include <AudioUnitSDK/AUPlugInDispatch.h>

#pragma mark AUv2Lab Methods

#define ENABLE_LOG 0

extern "C" void* AUv2LabFactory (AudioComponentDescription* inDesc);
AUSDK_EXPORT extern "C" void* AUv2LabFactory (AudioComponentDescription* inDesc)
{
    return ausdk::AUMusicDeviceFactory<AUv2Lab>::Factory (inDesc);
}

AUv2Lab::AUv2Lab(AudioUnit inComponentInstance)
: ausdk::MusicDeviceBase(inComponentInstance, 1, 13)
{
#if ENABLE_LOG == 1
    printf("============ AUv2Lab constructor =========\n");
#endif
    CreateElements();
}

AudioStreamBasicDescription AUv2Lab::GetStreamFormat(AudioUnitScope inScope, AudioUnitElement inElement)
{
#if ENABLE_LOG == 1
    const auto r = MusicDeviceBase::GetStreamFormat(inScope, inElement);
    printf("Desired format -> ID: %u, Flags: 0x%08X, SampleRate: %.2f, Channels: %u, BitsPerChannel: %u, "
           "BytesPerFrame: %u, BytesPerPacket: %u, FramesPerPacket: %u, Reserved: %u\n",
           r.mFormatID, r.mFormatFlags, r.mSampleRate, r.mChannelsPerFrame, r.mBitsPerChannel,
           r.mBytesPerFrame, r.mBytesPerPacket, r.mFramesPerPacket, r.mReserved);
#endif

    AudioStreamBasicDescription format = {0};
    
    if (inScope != kAudioUnitScope_Input && inScope != kAudioUnitScope_Output)
    {
        return format;
    }
    
    if (inScope == kAudioUnitScope_Input && inElement >= 1)
    {
        return format;
    }
    
    if (inScope == kAudioUnitScope_Output && inElement >= 13)
    {
        return format;
    }

    format.mSampleRate = 44100;
    format.mFormatID = kAudioFormatLinearPCM;
    format.mFormatFlags = kAudioFormatFlagIsFloat | kAudioFormatFlagIsPacked | kAudioFormatFlagIsNonInterleaved;
    format.mBitsPerChannel = 32;
    format.mChannelsPerFrame = (inElement >= 0 && inElement <= 4) ? 2 : 1;

    // We don't multiply by number of channels, because the stream is non-interleaved.
    // See https://developer.apple.com/documentation/coreaudiotypes/
    //     audiostreambasicdescription/mbytesperframe?language=objc
    format.mBytesPerFrame = format.mBitsPerChannel / 8;
    format.mBytesPerPacket = format.mBytesPerFrame;
    format.mFramesPerPacket = 1;
    format.mReserved = 0;

#if ENABLE_LOG == 1
    printf("Actual format -> ID: %u, Flags: 0x%08X, SampleRate: %.2f, Channels: %u, BitsPerChannel: %u, "
           "BytesPerFrame: %u, BytesPerPacket: %u, FramesPerPacket: %u, Reserved: %u\n",
           format.mFormatID, format.mFormatFlags, format.mSampleRate, format.mChannelsPerFrame, format.mBitsPerChannel,
           format.mBytesPerFrame, format.mBytesPerPacket, format.mFramesPerPacket, format.mReserved);
#endif

    return format;
}

bool AUv2Lab::StreamFormatWritable (AudioUnitScope scope, AudioUnitElement element)
{
    return true;
}

bool AUv2Lab::ValidFormat(AudioUnitScope inScope, AudioUnitElement inElement,
    const AudioStreamBasicDescription& inNewFormat)
{
    if (inScope != kAudioUnitScope_Output && inScope != kAudioUnitScope_Input)
    {
        return false;
    }
    
    if (inScope == kAudioUnitScope_Input)
    {
        return inElement == 0 && inNewFormat.mChannelsPerFrame == 2;
    }
    
    return (inElement >= 0 && inElement <= 4 && inNewFormat.mChannelsPerFrame == 2) ||
           (inElement >= 5 && inElement <= 12 && inNewFormat.mChannelsPerFrame == 1);
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

ComponentResult AUv2Lab::StartNote (MusicDeviceInstrumentID, MusicDeviceGroupID, NoteInstanceID*, UInt32, const MusicDeviceNoteParams&) { return noErr; }

ComponentResult AUv2Lab::StopNote (MusicDeviceGroupID, NoteInstanceID, UInt32)
{
    return noErr;
}
