#import <AudioToolbox/AudioToolbox.h>

@interface AUv3LabAudioUnit : AUAudioUnit

@property AUAudioFrameCount maximumFramesToRender;

- (void)setupAudioBuses;
@end
