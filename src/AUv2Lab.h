#include <AudioUnitSDK/MusicDeviceBase.h>
#include <Carbon/Carbon.h>

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
        return {};
    }

    OSStatus SetAudioChannelLayout (AudioUnitScope scope, AudioUnitElement element, const AudioChannelLayout* inLayout) override
    {
        return noErr;
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
