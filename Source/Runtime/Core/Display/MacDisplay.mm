#include "MacDisplay.h"
#include <Cocoa/Cocoa.h>

@interface MacDisplayDelegate : NSObject {
    NSWindow* window;
}
- (void)applicationDidFinishLaunching:(NSNotification*)notification;
- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication*)sender;
@end

@implementation MacDisplayDelegate

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
    
    // Make the window activatable
    [window setAcceptsMouseMovedEvents:YES];
    [window setIgnoresMouseEvents:NO];
}

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication*)sender {
    return YES;
}

@end

MacDisplay::MacDisplay() : delegate(nil), application(nil) {}

MacDisplay::~MacDisplay() {
    // Cleanup if needed
}

void MacDisplay::Initialize() {
    // Create the application delegate
    delegate = [[MacDisplayDelegate alloc] init];
    
    // Create and set up the application
    application = [NSApplication sharedApplication];
    [application setDelegate:delegate];
    
    // Set activation policy to regular
    [application setActivationPolicy:NSApplicationActivationPolicyRegular];
}

void MacDisplay::Run() {
    [application run];
}
