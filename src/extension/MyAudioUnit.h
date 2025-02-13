#import <AudioToolbox/AudioToolbox.h>

extern const AudioUnitParameterID myParam1;

@interface MyAudioUnit : AUAudioUnit
- (void)setupAudioBuses;
- (void)setupParameterTree;
- (void)setupParameterCallbacks;
@end
