#pragma once

// Forward declaration of Objective-C classes
#ifdef __OBJC__
@class MacDisplayDelegate;
@class NSApplication;
#else
typedef struct objc_object MacDisplayDelegate;
typedef struct objc_object NSApplication;
#endif

class MacDisplay {
private:
    MacDisplayDelegate* delegate;
    NSApplication* application;
    
public:
    MacDisplay();
    ~MacDisplay();
    
    void Initialize();
    void Run();
};
