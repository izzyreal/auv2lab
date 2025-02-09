#import <Cocoa/Cocoa.h>
#import <AudioUnit/AUCocoaUIView.h>

@interface AUv2LabView : NSObject <AUCocoaUIBase>
@end

@implementation AUv2LabView

- (unsigned)interfaceVersion {
    return 0;
}

- (NSView *)uiViewForAudioUnit:(AudioUnit)inAudioUnit withSize:(NSSize)inPreferredSize {
    NSLog(@"\n\n=================== AUv2LabViewFactory::uiViewForAudioUnit called ==================\n\n");
    return [[NSView alloc] initWithFrame:NSMakeRect(0, 0, inPreferredSize.width, inPreferredSize.height)];
}

@end

extern "C" void* AUv2Lab_CreateCocoaView() {
    return [[AUv2LabView alloc] init];
}
