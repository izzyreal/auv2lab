//
//  AUv3LabAudioUnit.h
//  AUv3Lab
//
//  Created by Izmar on 13/02/2025.
//

#import <AudioToolbox/AudioToolbox.h>
#import "Helpers/AUv3LabDSPKernelAdapter.h"

// Define parameter addresses.
extern const AudioUnitParameterID myParam1;

@interface AUv3LabAudioUnit : AUAudioUnit

@property (nonatomic, readonly) AUv3LabDSPKernelAdapter *kernelAdapter;
- (void)setupAudioBuses;
- (void)setupParameterTree;
- (void)setupParameterCallbacks;
@end
