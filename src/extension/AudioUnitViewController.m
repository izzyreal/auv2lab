//
//  AudioUnitViewController.m
//  extension
//
//  Created by Izmar on 13/02/25.
//  Copyright © 2025 Izmar. All rights reserved.
//

#import "AudioUnitViewController.h"
#import "MyAudioUnit.h"

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
    audioUnit = [[MyAudioUnit alloc] initWithComponentDescription:desc error:error];
    
    return audioUnit;
}

@end
