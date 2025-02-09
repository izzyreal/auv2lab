#include <AudioUnitSDK/MusicDeviceBase.h>
#include <Carbon/Carbon.h>

#include <iostream>

class AUv2Lab : public ausdk::MusicDeviceBase
{
public:
    AUv2Lab(AudioUnit inComponentInstance);
    
    bool ValidFormat(AudioUnitScope inScope, AudioUnitElement inElement,
                     const AudioStreamBasicDescription& inNewFormat) override;
    
    AudioStreamBasicDescription GetStreamFormat(AudioUnitScope inScope, AudioUnitElement inElement) override;
        
    bool CanScheduleParameters() const override;
    
    ComponentResult Render (AudioUnitRenderActionFlags& ioActionFlags,
                            const AudioTimeStamp& inTimeStamp,
                            const UInt32 nFrames) override;
    
    bool StreamFormatWritable (AudioUnitScope scope, AudioUnitElement element) override;
    
    ComponentResult StartNote (MusicDeviceInstrumentID, MusicDeviceGroupID, NoteInstanceID*, UInt32, const MusicDeviceNoteParams&) override;
    
    ComponentResult StopNote (MusicDeviceGroupID, NoteInstanceID, UInt32) override;
    
    std::vector<AudioChannelLayoutTag> GetChannelLayoutTags (AudioUnitScope inScope, AudioUnitElement inElement) override
    {
        if (inScope == kAudioUnitScope_Input)
        {
            if (inElement == 0)
            {
                return {kAudioChannelLayoutTag_Stereo};
            }
        }
        if (inScope == kAudioUnitScope_Output)
        {
            if (inElement == 0)
            {
                return {kAudioChannelLayoutTag_Stereo};
            }
            if (inElement >= 1 && inElement <= 4)
            {
                return {kAudioChannelLayoutTag_Stereo};
            }
            if (inElement >= 5 && inElement <= 12)
            {
                return {kAudioChannelLayoutTag_Mono};
            }
        }
                
        return {kAudioChannelLayoutTag_Unknown | 0};
    }
    
    UInt32 SupportedNumChannels(const AUChannelInfo** outInfo) override {
        static const AUChannelInfo channelInfos[] = {
            {2, 2},   // Stereo in → Stereo out
              {2, 10},  // Stereo in → 5x Stereo out, as well as
                        // Stereo in → 1x Stereo out, 8 Mono out
              {2, 18}   // Stereo in → 5x Stereo out + 8 Mono out
        };

        if (outInfo) *outInfo = channelInfos;
        return 3;
    }

    
    OSStatus SetBusCount(AudioUnitScope inScope, UInt32 inCount) override
    {
        if (IsInitialized()) {
            return kAudioUnitErr_Initialized;
        }
        
        if ((inScope == kAudioUnitScope_Input && inCount != 1) ||
            (inScope == kAudioUnitScope_Output && inCount != 1 && inCount != 5 && inCount != 9))
        {
            return kAudioUnitErr_InvalidParameterValue;
        }

        GetScope(inScope).SetNumberOfElements(inCount);
        return noErr;
    }
    
    OSStatus SetAudioChannelLayout(AudioUnitScope scope, AudioUnitElement element, const AudioChannelLayout* inLayout) override
    {
        std::cout << "SetAudioChannelLayout called - Scope: " << scope
                  << ", Element: " << element
                  << ", LayoutTag: " << (inLayout ? inLayout->mChannelLayoutTag : -1) << std::endl;

        if (scope == kAudioUnitScope_Input && element >= 1)
        {
            return kAudioUnitErr_InvalidElement;
        }
        if (scope == kAudioUnitScope_Output && element >= 13)
        {
            return kAudioUnitErr_InvalidElement;
        }
        
        const auto tag = inLayout->mChannelLayoutTag;
        
        if (scope == kAudioUnitScope_Input && tag != kAudioChannelLayoutTag_Stereo)
        {
            return kAudioUnitErr_InvalidParameterValue;
        }
        
        if (scope == kAudioUnitScope_Output && element <= 4 && tag != kAudioChannelLayoutTag_Stereo)
        {
            return kAudioUnitErr_InvalidParameterValue;
        }
        
        if (scope == kAudioUnitScope_Output && element >= 5 && element <= 12 && tag != kAudioChannelLayoutTag_Mono)
        {
            return kAudioUnitErr_InvalidParameterValue;
        }
        
        return noErr;
    }

    UInt32 GetAudioChannelLayout(AudioUnitScope scope, AudioUnitElement element,
        AudioChannelLayout* outLayoutPtr, bool& outWritable) override
    {
        outWritable = false; // Fixed layouts, host cannot modify

        if (scope == kAudioUnitScope_Input)
        {
            if (element == 0) // Single input bus (Stereo)
            {
                if (!outLayoutPtr) return sizeof(AudioChannelLayout);

                outLayoutPtr->mChannelLayoutTag = kAudioChannelLayoutTag_Stereo;
                outLayoutPtr->mNumberChannelDescriptions = 0;
                return sizeof(AudioChannelLayout);
            }
            return 0; // No other input buses
        }

        if (scope == kAudioUnitScope_Output)
        {
            UInt32 layoutSize = sizeof(AudioChannelLayout);
            AudioChannelLayoutTag layoutTag;

            if (element >= 0 && element <= 4)
                layoutTag = kAudioChannelLayoutTag_Stereo;
            else if (element >= 5 && element <= 12)
                layoutTag = kAudioChannelLayoutTag_Mono;
            else
                return 0; // No valid layout

            if (!outLayoutPtr) return layoutSize;

            outLayoutPtr->mChannelLayoutTag = layoutTag;
            outLayoutPtr->mNumberChannelDescriptions = 0;
            return layoutSize;
        }

        return 0; // Invalid scope
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

            CFBundleRef bundle = CFBundleGetBundleWithIdentifier(CFSTR("nl.izmar.AUv2Lab"));

            info->mCocoaAUViewBundleLocation = CFBundleCopyBundleURL(bundle);
            info->mCocoaAUViewClass[0] = CFStringCreateWithCString(0, "AUv2LabView", kCFStringEncodingUTF8);
            return noErr;
        }

        return MusicDeviceBase::GetProperty(inID, inScope, inElement, outData);
    }
};
