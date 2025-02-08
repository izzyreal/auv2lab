#import <Cocoa/Cocoa.h>
#import <AudioUnit/AUCocoaUIView.h>

@interface SinSynthView : NSObject <AUCocoaUIBase>
@end

@implementation SinSynthView

- (unsigned)interfaceVersion {
    return 0;
}

- (NSView *)uiViewForAudioUnit:(AudioUnit)inAudioUnit withSize:(NSSize)inPreferredSize {
    NSLog(@"\n\n=================== SinSynthViewFactory::uiViewForAudioUnit called ==================\n\n");
    return [[NSView alloc] initWithFrame:NSMakeRect(0, 0, inPreferredSize.width, inPreferredSize.height)];
}

@end

extern "C" void* SinSynth_CreateCocoaView() {
    return [[SinSynthView alloc] init];
}
