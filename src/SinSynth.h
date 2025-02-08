/*
 Copyright (C) 2016 Apple Inc. All Rights Reserved.
 See LICENSE.txt for this sample’s licensing information
 
 Abstract:
 Instrument AU
 */

#include <AudioUnitSDK/MusicDeviceBase.h>
#include <Carbon/Carbon.h>

class SinSynth : public ausdk::MusicDeviceBase
{
public:
    SinSynth(AudioUnit inComponentInstance);
        
    bool CanScheduleParameters() const override;
    
    ComponentResult Render (AudioUnitRenderActionFlags& ioActionFlags,
                            const AudioTimeStamp& inTimeStamp,
                            const UInt32 nFrames) override;
    
    bool StreamFormatWritable (AudioUnitScope scope, AudioUnitElement element) override;
    
    ComponentResult StartNote (MusicDeviceInstrumentID, MusicDeviceGroupID, NoteInstanceID*, UInt32, const MusicDeviceNoteParams&) override;
    
    ComponentResult StopNote (MusicDeviceGroupID, NoteInstanceID, UInt32) override;
    
    std::vector<AudioChannelLayoutTag> GetChannelLayoutTags (AudioUnitScope inScope, AudioUnitElement inElement) override
    {
        return {};
    }

    OSStatus SetAudioChannelLayout (AudioUnitScope scope, AudioUnitElement element, const AudioChannelLayout* inLayout) override
    {
        return noErr;
    }
    
    UInt32 GetAudioChannelLayout(AudioUnitScope scope,
                                 AudioUnitElement element,
                                 AudioChannelLayout* outLayoutPtr,
                                 bool& outWritable) override
    {
        if (scope != kAudioUnitScope_Output) return 0;
        if (!outLayoutPtr) return sizeof(AudioChannelLayout);

        *outLayoutPtr = {};
        outLayoutPtr->mChannelLayoutTag = kAudioChannelLayoutTag_Stereo;
        outLayoutPtr->mChannelBitmap = 0;
        outLayoutPtr->mNumberChannelDescriptions = 0;
        outWritable = false;

        return sizeof(AudioChannelLayout);
    }
    
    UInt32 SupportedNumChannels (const AUChannelInfo** outInfo) override
    {
        if (outInfo != nullptr)
            *outInfo = channelInfo.data();

        return (UInt32) channelInfo.size();
    }
    
    ComponentResult GetPropertyInfo(AudioUnitPropertyID inID,
                                    AudioUnitScope inScope,
                                    AudioUnitElement inElement,
                                    UInt32& outDataSize,
                                    bool& outWritable) override
    {
        if (inScope == kAudioUnitScope_Global && inID == kAudioUnitProperty_CocoaUI)
        {
            outDataSize = sizeof(AudioUnitCocoaViewInfo);
            outWritable = true;
            return noErr;
        }
        
        return MusicDeviceBase::GetPropertyInfo(inID, inScope, inElement, outDataSize, outWritable);
    }
    
    ComponentResult GetProperty(AudioUnitPropertyID inID,
                                AudioUnitScope inScope,
                                AudioUnitElement inElement,
                                void* outData) override
    {
        if (inScope == kAudioUnitScope_Global && inID == kAudioUnitProperty_CocoaUI)
        {
            AudioUnitCocoaViewInfo* info = (AudioUnitCocoaViewInfo*)outData;

            CFBundleRef bundle = CFBundleGetBundleWithIdentifier(CFSTR("nl.izmar.auv2lab"));

            info->mCocoaAUViewBundleLocation = CFBundleCopyBundleURL(bundle);
            info->mCocoaAUViewClass[0] = CFStringCreateWithCString(0, "SinSynthView", kCFStringEncodingUTF8);
            return noErr;
        }

        return MusicDeviceBase::GetProperty(inID, inScope, inElement, outData);
    }
    
private:
    std::vector<AUChannelInfo> channelInfo {{2,2}};
};
