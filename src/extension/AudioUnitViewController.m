//
//  AudioUnitViewController.m
//  AUv3Lab
//
//  Created by Izmar on 13/02/2025.
//

#import "AudioUnitViewController.h"
#import "AUv3LabAudioUnit.h"

@interface AudioUnitViewController ()

@end

@implementation AudioUnitViewController {
    AUAudioUnit *audioUnit;
}

- (void) viewDidLoad {
    [super viewDidLoad];
    
    if (!audioUnit) {
        return;
    }
    
    // Get the parameter tree and add observers for any parameters that the UI needs to keep in sync with the AudioUnit
}

- (AUAudioUnit *)createAudioUnitWithComponentDescription:(AudioComponentDescription)desc error:(NSError **)error {
    audioUnit = [[AUv3LabAudioUnit alloc] initWithComponentDescription:desc error:error];
    
    return audioUnit;
}

@end
