#import "AUv3LabAudioUnit.h"

#import <AVFoundation/AVFoundation.h>

@interface AUv3LabAudioUnit () {
    AUAudioFrameCount _maximumFramesToRender;
}

@property AUAudioUnitBusArray *inputBusArray;
@property AUAudioUnitBusArray *outputBusArray;
@end

@implementation AUv3LabAudioUnit

- (instancetype)initWithComponentDescription:(AudioComponentDescription)componentDescription options:(AudioComponentInstantiationOptions)options error:(NSError **)outError {
    _maximumFramesToRender = 512;
    self = [super initWithComponentDescription:componentDescription options:options error:outError];
    
    if (self == nil) { return nil; }

    [self setupAudioBuses];
    return self;
}

#pragma mark - AUAudioUnit Setup

- (void)setupAudioBuses {
    AVAudioFormat *stereoFormat = [[AVAudioFormat alloc] initStandardFormatWithSampleRate:44100 channels:2];
    AVAudioFormat *monoFormat = [[AVAudioFormat alloc] initStandardFormatWithSampleRate:44100 channels:1];

    NSMutableArray *outputBuses = [NSMutableArray array];

    for (int i = 0; i < 5; i++) {
        AUAudioUnitBus *stereoBus = [[AUAudioUnitBus alloc] initWithFormat:stereoFormat error:nil];
        stereoBus.maximumChannelCount = 2;
        [outputBuses addObject:stereoBus];
    }

    for (int i = 0; i < 8; i++) {
        AUAudioUnitBus *monoBus = [[AUAudioUnitBus alloc] initWithFormat:monoFormat error:nil];
        monoBus.maximumChannelCount = 1;
        [outputBuses addObject:monoBus];
    }

    _inputBusArray = [[AUAudioUnitBusArray alloc] initWithAudioUnit:self
                                                            busType:AUAudioUnitBusTypeInput
                                                             busses:@[[[AUAudioUnitBus alloc] initWithFormat:stereoFormat error:nil]]];

    _outputBusArray = [[AUAudioUnitBusArray alloc] initWithAudioUnit:self
                                                             busType:AUAudioUnitBusTypeOutput
                                                              busses:outputBuses];
}

#pragma mark - AUAudioUnit Overrides

- (BOOL)shouldChangeToFormat:(AVAudioFormat *)format forBus:(AUAudioUnitBus *)bus {
    if (bus.busType == AUAudioUnitBusTypeInput) {
        return (bus.index == 0 && format.channelCount == 2);
    }

    if (bus.busType == AUAudioUnitBusTypeOutput) {
        NSInteger busIndex = bus.index;
        return (busIndex >= 0 && busIndex <= 4 && format.channelCount == 2) ||
               (busIndex >= 5 && busIndex <= 12 && format.channelCount == 1);
    }

    return NO;
}

- (AUAudioFrameCount)maximumFramesToRender {
  return _maximumFramesToRender;
}

- (void)setMaximumFramesToRender:(AUAudioFrameCount)maximumFramesToRender {
    _maximumFramesToRender = maximumFramesToRender;
}

- (AUAudioUnitBusArray *)inputBusses {
  return _inputBusArray;
}

- (AUAudioUnitBusArray *)outputBusses {
  return _outputBusArray;
}

#pragma mark - AUAudioUnit (AUAudioUnitImplementation)

- (AUInternalRenderBlock)internalRenderBlock {
    return ^AUAudioUnitStatus(AudioUnitRenderActionFlags                 *actionFlags,
                              const AudioTimeStamp                       *timestamp,
                              AVAudioFrameCount                           frameCount,
                              NSInteger                                   outputBusNumber,
                              AudioBufferList                            *outputData,
                              const AURenderEvent                        *realtimeEventListHead,
                              AURenderPullInputBlock __unsafe_unretained pullInputBlock) {
        return noErr;
    };
}
@end

