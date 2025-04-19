#pragma once

// Forward declarations for Objective-C classes
#ifdef __OBJC__
@class MacDisplayDelegate;
@class NSApplication;
#else
typedef void* MacDisplayDelegate;
typedef void* NSApplication;
#endif

class MacDisplay {
public:
    MacDisplay();
    ~MacDisplay();
    
    void Initialize();
    void Run();
    
    void InitializeMetal();
    void Render();
    void SetClearColor(float r, float g, float b, float a);
    
    // Metal访问方法
    void* GetMetalDevice();
    void* GetCommandQueue();
    void* GetMetalLayer();
    
private:
    MacDisplayDelegate* delegate;
    NSApplication* application;
    
    // Metal设备相关（不暴露具体类型，使用void*存储）
    void* metalDevice;    // 对应id<MTLDevice>
    void* commandQueue;   // 对应id<MTLCommandQueue>
    void* metalLayer;     // 对应CAMetalLayer*
    float clearColor[4];  // RGBA清屏颜色
};
