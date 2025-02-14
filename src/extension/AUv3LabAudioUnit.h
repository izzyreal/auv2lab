#import <AudioToolbox/AudioToolbox.h>

extern const AudioUnitParameterID myParam1;

@interface AUv3LabAudioUnit : AUAudioUnit

@property AUAudioFrameCount maximumFramesToRender;
@property (nonatomic, readonly) AUAudioUnitBus *inputBus;
@property (nonatomic, readonly) AUAudioUnitBus *outputBus;

- (void)setupAudioBuses;
- (void)setupParameterTree;
- (void)setupParameterCallbacks;
@end
