#include "MacDisplay.h"
#include <Cocoa/Cocoa.h>
#include <Metal/Metal.h>
#include <QuartzCore/CAMetalLayer.h>

@interface MacDisplayDelegate : NSObject<NSApplicationDelegate> {
    NSWindow* window;
    MacDisplay* display;
}
- (id)initWithDisplay:(MacDisplay*)inDisplay;
- (void)applicationDidFinishLaunching:(NSNotification*)notification;
- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication*)sender;
- (NSWindow*)window;
@end

@implementation MacDisplayDelegate

- (id)initWithDisplay:(MacDisplay*)inDisplay {
    self = [super init];
    if (self) {
        display = inDisplay;
    }
    return self;
}

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
    
    // Create a view for content
    NSView* contentView = [[NSView alloc] initWithFrame:NSMakeRect(0, 0, 800, 600)];
    contentView.wantsLayer = YES;
    window.contentView = contentView;
    
    // Make the window activatable
    [window makeKeyAndOrderFront:nil];
    [window setAcceptsMouseMovedEvents:YES];
    [window setIgnoresMouseEvents:NO];
    
    // 初始化Metal和渲染设置
    display->InitializeMetal();
    
    // 设置Metal层
    CAMetalLayer* metalLayer = (__bridge CAMetalLayer*)display->GetMetalLayer();
    metalLayer.frame = contentView.bounds;
    [contentView.layer addSublayer:metalLayer];
    
    // 创建渲染定时器
    [NSTimer scheduledTimerWithTimeInterval:1.0/60.0
                                     target:self 
                                   selector:@selector(timerFired:)
                                   userInfo:nil
                                    repeats:YES];
}

- (void)timerFired:(NSTimer*)timer {
    display->Render();
}

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication*)sender {
    return YES;
}

- (NSWindow*)window {
    return window;
}

@end

MacDisplay::MacDisplay() 
    : delegate(nil), application(nil), metalDevice(nullptr), 
      commandQueue(nullptr), metalLayer(nullptr) {
    // 默认设置蓝色清屏颜色
    clearColor[0] = 0.0f;  // R
    clearColor[1] = 0.5f;  // G
    clearColor[2] = 1.0f;  // B
    clearColor[3] = 1.0f;  // A
}

MacDisplay::~MacDisplay() {
    // 释放Metal相关资源
    if (metalLayer) {
        CAMetalLayer* layer = (__bridge_transfer CAMetalLayer*)metalLayer;
        metalLayer = nullptr;
    }
    
    // 释放Command Queue和Device不需要显式操作，由ARC处理
    commandQueue = nullptr;
    metalDevice = nullptr;
}

void MacDisplay::Initialize() {
    // Create the application delegate
    MacDisplayDelegate* macDelegate = [[MacDisplayDelegate alloc] initWithDisplay:this];
    delegate = macDelegate;
    
    // Create and set up the application
    application = [NSApplication sharedApplication];
    [(__bridge NSApplication*)application setDelegate:(__bridge id)delegate];
    
    // Set activation policy to regular
    [(__bridge NSApplication*)application setActivationPolicy:NSApplicationActivationPolicyRegular];
}

void MacDisplay::Run() {
    [(__bridge NSApplication*)application run];
}

void MacDisplay::InitializeMetal() {
    // 创建Metal设备
    id<MTLDevice> device = MTLCreateSystemDefaultDevice();
    if (!device) {
        NSLog(@"Metal is not supported on this device");
        return;
    }
    metalDevice = (__bridge_retained void*)device;
    
    // 创建Command Queue
    id<MTLCommandQueue> queue = [device newCommandQueue];
    commandQueue = (__bridge_retained void*)queue;
    
    // 创建Metal Layer
    CAMetalLayer* layer = [[CAMetalLayer alloc] init];
    layer.device = device;
    layer.pixelFormat = MTLPixelFormatBGRA8Unorm;
    layer.framebufferOnly = YES;
    metalLayer = (__bridge_retained void*)layer;
}

void MacDisplay::Render() {
    CAMetalLayer* layer = (__bridge CAMetalLayer*)metalLayer;
    id<MTLCommandQueue> queue = (__bridge id<MTLCommandQueue>)commandQueue;
    
    // 获取下一个drawable
    id<CAMetalDrawable> drawable = [layer nextDrawable];
    if (!drawable) return;
    
    // 创建渲染通道描述符
    MTLRenderPassDescriptor* renderPassDescriptor = [MTLRenderPassDescriptor renderPassDescriptor];
    renderPassDescriptor.colorAttachments[0].texture = drawable.texture;
    renderPassDescriptor.colorAttachments[0].loadAction = MTLLoadActionClear;
    renderPassDescriptor.colorAttachments[0].clearColor = MTLClearColorMake(
        clearColor[0], clearColor[1], clearColor[2], clearColor[3]
    );
    renderPassDescriptor.colorAttachments[0].storeAction = MTLStoreActionStore;
    
    // 创建命令缓冲区
    id<MTLCommandBuffer> commandBuffer = [queue commandBuffer];
    
    // 创建渲染命令编码器
    id<MTLRenderCommandEncoder> renderEncoder = [commandBuffer renderCommandEncoderWithDescriptor:renderPassDescriptor];
    [renderEncoder endEncoding];
    
    // 显示drawable
    [commandBuffer presentDrawable:drawable];
    
    // 提交命令缓冲区
    [commandBuffer commit];
}

void MacDisplay::SetClearColor(float r, float g, float b, float a) {
    clearColor[0] = r;
    clearColor[1] = g;
    clearColor[2] = b;
    clearColor[3] = a;
}

void* MacDisplay::GetMetalDevice() {
    return metalDevice;
}

void* MacDisplay::GetCommandQueue() {
    return commandQueue;
}

void* MacDisplay::GetMetalLayer() {
    return metalLayer;
}
