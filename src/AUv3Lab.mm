#import "AUv3Lab.h"

@implementation AUv3Lab {
    AUAudioUnitBusArray *_inputBusses;
    AUAudioUnitBusArray *_outputBusses;
    AUParameterTree *_parameterTree;
}

- (instancetype)initWithComponentDescription:(AudioComponentDescription)desc options:(AudioComponentInstantiationOptions)options error:(NSError **)outError {
    self = [super initWithComponentDescription:desc options:options error:outError];
    if (self) {
        AVAudioFormat *format = [[AVAudioFormat alloc] initStandardFormatWithSampleRate:44100 channels:2];
        AUAudioUnitBus *inputBus = [[AUAudioUnitBus alloc] initWithFormat:format error:nil];
        AUAudioUnitBus *outputBus = [[AUAudioUnitBus alloc] initWithFormat:format error:nil];
        
        _inputBusses = [[AUAudioUnitBusArray alloc] initWithAudioUnit:self busType:AUAudioUnitBusTypeInput busses:@[inputBus]];
        _outputBusses = [[AUAudioUnitBusArray alloc] initWithAudioUnit:self busType:AUAudioUnitBusTypeOutput busses:@[outputBus]];
        
        _parameterTree = [AUParameterTree createTreeWithChildren:@[]];
    }
    return self;
}

- (AUAudioUnitBusArray *)inputBusses {
    return _inputBusses;
}

- (AUAudioUnitBusArray *)outputBusses {
    return _outputBusses;
}

- (AUParameterTree *)parameterTree {
    return _parameterTree;
}

@end
