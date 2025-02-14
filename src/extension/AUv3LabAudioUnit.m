#import "AUv3LabAudioUnit.h"

#import <AVFoundation/AVFoundation.h>

const AudioUnitParameterID myParam1 = 0;

@interface AUv3LabAudioUnit () {
    AUAudioFrameCount _maximumFramesToRender;
}

@property (nonatomic, readwrite) AUParameterTree *parameterTree;
@property AUAudioUnitBusArray *inputBusArray;
@property AUAudioUnitBusArray *outputBusArray;
@end

@implementation AUv3LabAudioUnit
@synthesize parameterTree = _parameterTree;

- (instancetype)initWithComponentDescription:(AudioComponentDescription)componentDescription options:(AudioComponentInstantiationOptions)options error:(NSError **)outError {
    _maximumFramesToRender = 512;
    self = [super initWithComponentDescription:componentDescription options:options error:outError];
    
    if (self == nil) { return nil; }

  [self setupAudioBuses];
  [self setupParameterTree];
  [self setupParameterCallbacks];
    return self;
}

#pragma mark - AUAudioUnit Setup

- (void)setupAudioBuses {
    AVAudioFormat *format = [[AVAudioFormat alloc] initStandardFormatWithSampleRate:44100 channels:2];
    
    _inputBus = [[AUAudioUnitBus alloc] initWithFormat:format error:nil];
    _inputBus.maximumChannelCount = 8;
    _outputBus = [[AUAudioUnitBus alloc] initWithFormat:format error:nil];
    _outputBus.maximumChannelCount = 8;
    
  _inputBusArray  = [[AUAudioUnitBusArray alloc] initWithAudioUnit:self
                               busType:AUAudioUnitBusTypeInput
                                busses: @[_inputBus]];
  _outputBusArray = [[AUAudioUnitBusArray alloc] initWithAudioUnit:self
                               busType:AUAudioUnitBusTypeOutput
                                busses: @[_outputBus]];
}

- (void)setupParameterTree {
    // Create parameter objects.
    AUParameter *param1 = [AUParameterTree createParameterWithIdentifier:@"param1"
                                  name:@"Parameter 1"
                                 address:myParam1
                                   min:0
                                   max:100
                                  unit:kAudioUnitParameterUnit_Percent
                                unitName:nil
                                   flags:kAudioUnitParameterFlag_IsWritable | kAudioUnitParameterFlag_IsReadable
                              valueStrings:nil
                           dependentParameters:nil];

    param1.value = 0.5;

    _parameterTree = [AUParameterTree createTreeWithChildren:@[ param1 ]];
}

- (void)setupParameterCallbacks {
  _parameterTree.implementorStringFromValueCallback = ^(AUParameter *param, const AUValue *__nullable valuePtr) {
    AUValue value = valuePtr == nil ? param.value : *valuePtr;

    return [NSString stringWithFormat:@"%.f", value];
  };
}

#pragma mark - AUAudioUnit Overrides

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

- (BOOL)allocateRenderResourcesAndReturnError:(NSError **)outError {
  if (_outputBus.format.channelCount != _inputBus.format.channelCount) {
    if (outError) {
      *outError = [NSError errorWithDomain:NSOSStatusErrorDomain code:kAudioUnitErr_FailedInitialization userInfo:nil];
    }
    self.renderResourcesAllocated = NO;

    return NO;
  }

  [super allocateRenderResourcesAndReturnError:outError];
    self.renderResourcesAllocated = YES;
  return YES;
}

- (void)deallocateRenderResources {
    [super deallocateRenderResources];
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

