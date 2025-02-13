#import "AudioUnitViewController.h"
#import "MyAudioUnit.h"

@interface AudioUnitViewController ()

@end

@implementation AudioUnitViewController {
    AUAudioUnit *audioUnit;
}

- (void)viewDidLoad {
    printf("\n\n============ AudioUnitViewController loaded\n");
    fflush(stdout);

    [super viewDidLoad];
    
    
    if (!audioUnit) {
        printf("No audio unit available\n");
        return;
    }
    
    printf("Audio unit exists, setting up UI sync\n");
}

- (AUAudioUnit *)createAudioUnitWithComponentDescription:(AudioComponentDescription)desc error:(NSError **)error {
    printf("Creating AudioUnit...\n");
    audioUnit = [[MyAudioUnit alloc] initWithComponentDescription:desc error:error];
    
    if (!audioUnit) {
        printf("Failed to create AudioUnit\n");
    } else {
        printf("AudioUnit created successfully\n");
    }
    
    return audioUnit;
}

@end
