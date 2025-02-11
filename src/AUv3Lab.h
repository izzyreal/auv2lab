#import <AudioToolbox/AudioToolbox.h>
#import <AVFoundation/AVFoundation.h>

@interface AUv3Lab : AUAudioUnit

@property (nonatomic, readonly) AUAudioUnitBusArray *inputBusses;
@property (nonatomic, readonly) AUAudioUnitBusArray *outputBusses;
@property (nonatomic, readonly) AUParameterTree *parameterTree;

@end
