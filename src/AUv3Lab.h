#import <AudioToolbox/AudioToolbox.h>
#import <AVFoundation/AVFoundation.h>

@interface AUv3Lab : AUAudioUnit

@property (NS_NONATOMIC_IOSONLY, readonly) AUAudioUnitBusArray *inputBusses;
@property (NS_NONATOMIC_IOSONLY, readonly) AUAudioUnitBusArray *outputBusses;
@property (NS_NONATOMIC_IOSONLY, readonly) AUParameterTree *parameterTree;

@end
