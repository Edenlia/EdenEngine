# Vulkan初始化过程

## 1. 创建Vulkan实例 (VkInstance)
首先需要创建Vulkan实例，这是与Vulkan API交互的入口点。

```cpp
void WindowsDisplay::createVulkanInstance()
```
- 设置应用程序信息（名称、版本等）
- 启用必要的扩展（VK_KHR_SURFACE_EXTENSION_NAME和VK_KHR_WIN32_SURFACE_EXTENSION_NAME）
- 创建Vulkan实例

## 2. 创建窗口表面 (VkSurfaceKHR)
创建与Windows窗口关联的Vulkan表面。

```cpp
void WindowsDisplay::createSurface()
```
- 使用Windows窗口句柄（HWND）创建Vulkan表面
- 将表面与Vulkan实例关联

## 3. 选择物理设备 (VkPhysicalDevice)
枚举并选择可用的物理设备（GPU）。

```cpp
void WindowsDisplay::pickPhysicalDevice()
```
- 枚举所有可用的物理设备
- 选择支持所需功能的设备（这里选择独立GPU）
- 检查设备是否支持所需的扩展

## 4. 创建设备和队列 (VkDevice)
创建逻辑设备并获取图形和呈现队列。

```cpp
void WindowsDisplay::createLogicalDevice()
```
- 设置队列创建信息
- 启用设备扩展（VK_KHR_SWAPCHAIN_EXTENSION_NAME）
- 创建设备
- 获取图形和呈现队列

## 5. 创建交换链 (VkSwapchainKHR)
创建用于在窗口上显示图像的交换链。

```cpp
void WindowsDisplay::createSwapchain()
```
- 获取表面能力
- 设置交换链创建信息（格式、颜色空间、呈现模式等）
- 创建交换链
- 获取交换链图像

## 6. 创建图像视图 (VkImageView)
为交换链图像创建图像视图。

```cpp
void WindowsDisplay::createImageViews()
```
- 为每个交换链图像创建图像视图
- 设置图像视图参数（格式、组件映射等）

## 7. 创建渲染通道 (VkRenderPass)
定义渲染操作的框架。

```cpp
void WindowsDisplay::createRenderPass()
```
- 设置颜色附件描述
- 创建子通道
- 创建渲染通道

## 8. 创建帧缓冲 (VkFramebuffer)
为每个交换链图像创建帧缓冲。

```cpp
void WindowsDisplay::createFramebuffers()
```
- 为每个交换链图像视图创建帧缓冲
- 将渲染通道与帧缓冲关联

## 9. 创建命令池和命令缓冲
创建用于记录命令的命令池和命令缓冲。

```cpp
void WindowsDisplay::createCommandPool()
void WindowsDisplay::createCommandBuffer()
```
- 创建命令池
- 分配命令缓冲

## 10. 创建同步对象
创建用于同步渲染操作的信号量和栅栏。

```cpp
void WindowsDisplay::createSyncObjects()
```
- 创建图像可用信号量
- 创建渲染完成信号量
- 创建栅栏

## 11. 记录命令缓冲
记录渲染命令。

```cpp
void WindowsDisplay::recordCommandBuffer(uint32_t imageIndex)
```
- 开始记录命令
- 开始渲染通道
- 清除颜色附件
- 结束渲染通道
- 结束记录命令

## 12. 渲染循环
在窗口消息循环中执行渲染。

```cpp
void WindowsDisplay::Run()
```
- 等待前一帧完成
- 获取下一帧图像
- 记录命令缓冲
- 提交命令缓冲
- 呈现图像

## 13. 清理资源
在程序结束时清理所有Vulkan资源。

```cpp
void WindowsDisplay::~WindowsDisplay()
void WindowsDisplay::cleanupSwapchain()
```
- 等待设备空闲
- 清理交换链相关资源
- 销毁表面
- 销毁设备
- 销毁实例 