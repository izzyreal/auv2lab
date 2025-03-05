#import "AudioUnitViewController.h"
#import "AUv3LabAudioUnit.h"

@interface AudioUnitViewController ()

@end

@implementation AudioUnitViewController {
    AUAudioUnit *audioUnit;
}

- (void)loadView {
    self.view = [[NSView alloc] initWithFrame:NSMakeRect(0, 0, 500, 500)];
    self.view.wantsLayer = YES;

    NSButton *shareButton = [[NSButton alloc] initWithFrame:NSMakeRect(0, 0, 150, 30)];
    [shareButton setTitle:@"Share"];
    [shareButton setTarget:self];
    [shareButton setAction:@selector(shareAction:)];
    [self.view addSubview:shareButton];
}

- (void) viewDidLoad {
    [super viewDidLoad];
    
    if (!audioUnit) {
        return;
    }
}

- (void)shareAction:(id)sender {
    NSURL *fileURL = [NSURL fileURLWithPath:[@"~/Desktop/test.txt" stringByExpandingTildeInPath]];
    NSSharingServicePicker *picker = [[NSSharingServicePicker alloc] initWithItems:@[fileURL]];
    [picker showRelativeToRect:[(NSButton *)sender frame] ofView:self.view preferredEdge:NSRectEdgeMinY];
}

- (AUAudioUnit *)createAudioUnitWithComponentDescription:(AudioComponentDescription)desc error:(NSError **)error {
    audioUnit = [[AUv3LabAudioUnit alloc] initWithComponentDescription:desc error:error];
    
    return audioUnit;
}

@end
