#if defined(__APPLE__)
#include <Cocoa/Cocoa.h>
#include "Core/Display/MacDisplay.h"
#elif defined(_WIN32)
#include "Core/Display/WindowsDisplay.h"
#endif

#if defined(__APPLE__)
@interface AppDelegate : NSObject {
    NSWindow* window;
}
- (void)applicationDidFinishLaunching:(NSNotification*)notification;
- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication*)sender;
@end

@implementation AppDelegate

- (void)applicationDidFinishLaunching:(NSNotification*)notification {
    // Create and configure the main window
    window = [[NSWindow alloc] 
        initWithContentRect:NSMakeRect(200, 200, 800, 600)
        styleMask:NSWindowStyleMaskTitled |
                 NSWindowStyleMaskClosable |
                 NSWindowStyleMaskMiniaturizable |
                 NSWindowStyleMaskResizable
        backing:NSBackingStoreBuffered
        defer:NO];
    
    [window setTitle:@"Eden Engine"];
    [window center];
    [window makeKeyAndOrderFront:nil];
}

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication*)sender {
    return YES;
}

@end
#endif

int main(int argc, const char* argv[]) {
#if defined(__APPLE__)
    MacDisplay display;
    display.Initialize();
    display.Run();
#elif defined(_WIN32)
    WindowsDisplay display;
    display.Initialize();
    display.Run();
#endif
    
    return 0;
} 