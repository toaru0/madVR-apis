// ***************************************************************
//  madTPG.h                     版本：1.6.0  �  日期：2017-09-12
//  -------------------------------------------------------------
//  madTPG 遥控  中文翻译版    译文版本：1.6.0.1  �  日期：2022-11-
//  -------------------------------------------------------------
//  Copyright (C) 2013 - 2017 www.madshi.net, BSD license
//  -------------------------------------------------------------
//  译者：toaru <toaru0@outlook.com> 译文遵循CC 4.0 BY-SA版权协议
// ***************************************************************

//译注：我也不知道“版本”和“日期”中间的“�”是什么。

// 2017-09-12 1.6.0 添加了各种 HDR 相关的 API （API：可编程应用接口）
// 2015-07-19 1.5.0 (1) 添加了 IsFseModeEnabled API （检测是否启用全屏独占模式）
//                  (2) 添加了 Enabled/DisableFseMode APIs （启用/禁用全屏独占模式）
// 2015-06-28 1.4.0 (1) 添加了 IsLocal API （检测 MadTPG 是否在本地）
//                  (2) 添加了 Is/Enter/LeaveFullscreen APIs （检测/进入/退出全屏）
//                  (3) 添加了 Get/SetWindowSize APIs （获取/设置窗口尺寸）
//                  (4) 添加了 (Is)Min/Maximize(d)/Restore(d) APIs （调整 madTPG 窗口状态）
// 2015-01-03 1.3.0 (1) 添加了 GetVersion API （版本获取）
//                  (2) 添加了 Get/SetSelected3dlut APIs （获取/设置选定的3Dlut）
// 2014-12-01 1.2.0 (1) 添加了 Connect（连接），deprecated BindConnect （弃用的绑定连接） and ConnectDialog （连接会话）
//                  (2) 添加了用于获取/设置“置顶”按钮状态的 APIs
//                  (3) 添加了用于获取/设置“全屏”按钮状态的 APIs
//                  (4) 添加了用于获取/设置“禁用OSD”按钮状态的 APIs （OSD：On Screen Display，即调节窗口显示的文字）
//                  (5) 添加了 Get/SetPatternConfig APIs （获取/设置图案配置）
//                  (6) 添加了 ShowRGBEx API （显示 RGBEx）（RGBEx：包括背景色的RGB）
//                  (7) 添加了各种3dlut 转换和导入 APIs
// 2013-11-27 1.1.0 添加了 madVR_GetBlackAndWhiteLevel （获取灰阶设置）
// 2013-06-15 1.0.0 最初版本

// ----------------------------------------------------------------------------

#if !defined(MADTPG_H)
#define MADTPG_H

#ifdef __cplusplus
  extern "C" {
#endif

#include <windows.h>

#pragma pack(1)

// ============================================================================
// I. 简单方式
// ============================================================================

// ----------------------------------------------------------------------------
// 连接 madVR - 两种选择

// (1) "madVR_Connect" 是查找一个用来连接的 madVR 实例的推荐 API。您可以使用该 API
//     查找本地 PC 和/或局域网中已经运行的 madTPG 实例，如果在指定的时间内没有找到任
//     何实例，您可以简单地用该 API 为您在本地 PC 上启动一个新的 madTPG 实例。或者您
//     您可以使用该 API 向用户展示一个对话框，允许用户输入 IP 地址来连接一个已经运行
//     的 madTPG 实例。

const static int CM_ConnectToLocalInstance = 0;  // 在本地 PC 上查找 madTPG，连接第一个找到的实例
const static int CM_ConnectToLanInstance   = 1;  // 在局域网中查找 madTPG，连接第一个找到的实例
const static int CM_StartLocalInstance     = 2;  // 在本地 PC 上启动 madTPG 并连接
const static int CM_ShowListDialog         = 3;  // 在本地 PC 和局域网中查找 madTPG，由用户选择连接的实例
const static int CM_ShowIpAddrDialog       = 4;  // 让用户输入一个运行 madTPG 的 PC 的 IP 地址并连接
const static int CM_Fail                   = 5;  // 失败（fail immediately）

#ifdef __cplusplus
  BOOL madVR_Connect(int method1 = CM_ConnectToLocalInstance, DWORD timeOut1 = 1000,
                     int method2 = CM_ConnectToLanInstance,   DWORD timeOut2 = 3000,
                     int method3 = CM_ShowListDialog,         DWORD timeOut3 = INFINITE,
                     int method4 = CM_Fail,                   DWORD timeOut4 = 0,
                     HWND parentWindow = NULL);
#else
  BOOL madVR_Connect(int method1, DWORD timeOut1,
                     int method2, DWORD timeOut2,
                     int method3, DWORD timeOut3,
                     int method4, DWORD timeOut4,
                     HWND parentWindow);
#endif

// (2) “madVR_ConnectToIp” 可以让您连接一个局域网中已知 IP 的正在运行一个 madTPG
//     实例的 PC 。
// “result=true”  意味着找到了一个 madVR 实例并连接成功。
// “result=false” 意味着没有找到 madVR 实例或者连接失败。
#ifdef __cplusplus
  BOOL madVR_ConnectToIp(LPCSTR ipAddress, DWORD timeOut = 1000);
#else
  BOOL madVR_ConnectToIp(LPCSTR ipAddress, DWORD timeOut       );
#endif

// ----------------------------------------------------------------------------
// 遥控已经连接的 madVR 实例

// “madVR_GetVersion” 检测madVR的版本，返回16进制数。
// 示例：版本v0.87.12.0将会返回0x00871200。使用这种格式允许您像这样检查版本：
// “if (version >= 0x00871200)”。
BOOL madVR_GetVersion(DWORD *version);

// “madVR_IsLocal” 检测连接的 madTPG 实例是否运行在本地 PC 上。
BOOL madVR_IsLocal();

// “madVR_Enter/LeaveFullscreen” 让 madTPG 进入/退出全屏模式。
// 调用该 API 和用户双击 madTPG 窗口有类似的效果。
BOOL madVR_IsFullscreen();
BOOL madVR_EnterFullscreen();
BOOL madVR_LeaveFullscreen();

// “madVR_IsFseModeEnabled” 允许您询问已经全屏的 madTPG 是否可以进入全屏独占
// （Full Screen Exclusive，FSE）模式。只有 FSE 模式支持原生10位输出。
// “madVR_En/DisableFseMode” 覆盖 madVR 中的用户配置来强行启用或禁用 FSE 模式。
BOOL madVR_IsFseModeEnabled();
BOOL madVR_EnableFseMode();
BOOL madVR_DisableFseMode();

// “madVR_Get/SetWindowSize” 读取/修改 madTPG 窗口的尺寸。
BOOL madVR_GetWindowSize(RECT *windowSize);
BOOL madVR_SetWindowSize(RECT *windowSize);

// “madVR_IsMin/Maximized” 和 “madVR_Min/Maximize/Restore” 读取/修改 madTPG
// 窗口的状态（最小化（Minimized），最大化（Maximized），恢复（Restored））。
BOOL madVR_IsMinimized();
BOOL madVR_IsMaximized();
BOOL madVR_IsRestored();
BOOL madVR_Minimize();
BOOL madVR_Maximize();
BOOL madVR_Restore();

// 下列函数允许您读取和设置“置顶”，“全屏”，“禁用 OSD”和“HDR”按钮状态（是否按下）。
BOOL madVR_IsStayOnTopButtonPressed();
BOOL madVR_IsUseFullscreenButtonPressed();
BOOL madVR_IsDisableOsdButtonPressed();
BOOL madVR_IsHdrButtonPressed();
BOOL madVR_SetStayOnTopButton(BOOL pressed);
BOOL madVR_SetUseFullscreenButton(BOOL pressed);
BOOL madVR_SetDisableOsdButton(BOOL pressed);
BOOL madVR_SetHdrButton(BOOL pressed);

// “madVR_SetHdrMetadata”（设置 HDR 元数据）允许您在 madTPG 为 HDR 模式时决定
// 向显示屏发送哪个 SMPTE 2086 元数据。
// minLum，maxLum，madCLL 和 maxFALL 是双精度浮点 Nit 值。
// https://blog.csdn.net/vn9PLgZvnPs1522s82g/article/details/122757411
BOOL madVR_SetHdrMetadata(double rx, double ry, double gx, double gy, double bx, double by, double wx, double wy, double minLum, double maxLum, double maxCLL, double maxFALL);

// "madVR_GetBlackAndWhiteLevel" 检测 madVR 设置的输出级别。
// 示例：如果 madVR 设置为 TV 输出, 将会返回 "blackLevel = 16" 和 "whiteLevel = 235"。
// 询问这些信息将允许您避免抖色（dithering）。如果由 madVR 计算的最终的8位输出是一个整数，
// 抖色将默认被禁用。
// 示例：如果您在 madVR 设置为 PC 输出时使用 “madVR_ShowRGB(0.5, 0.5, 0.5)”，最终的8位
// 输出将是127.5, 这意味着 madVR 不得不使用抖色来确保颜色显示正确。如果您想避免抖色，
// （当您想输出颜色 x 时）输出 “x / (whiteLevel - blackLevel)”。
// 抖色本身无害。它允许 madVR 生成在8位颜色输出中不可能输出的颜色。尽管如此，即使是不需要
// 抖色就能显示的颜色，显示质量也可能会略微提高。抖色的输出甚至有可能比高于 8位的原生输出
// 稍好一点。不过，这是您的选择。
// 译注：这段原文有点奇怪，大意应该就是介绍这个函数的用途————检测 madVR 输出级别，来决定
// 是否使用抖色。然后介绍了抖色的种种优点。
BOOL madVR_GetBlackAndWhiteLevel(int *blackLevel, int *whiteLevel);

// “madVR_Get/SetSelected3dlut” 允许您询问/设置 madTPG 现在使用的 3Dlut。
// (示例：BT.709 vs EBU/PAL)。（译注：3Dlut = 3D 颜色查找表= 3D 色域= 3D 颜色空间）
// 设置 3Dlut 将同时启用 3Dlut（madVR_Enable3dlut）。
// HDR 模式中只支持 BT.709，BT.2020 和 DCI-P3。
// “thr3dlut” 0：BT.709; 1：SMPTE-C；2：EBU/PAL；3：BT.2020；4：DCI-P3
BOOL madVR_GetSelected3dlut (DWORD *thr3dlut);
BOOL madVR_SetSelected3dlut (DWORD  thr3dlut);

// “madVR_En/Disable3dlut” 启用/禁用 3Dlut 处理。
// 3Dlut 保持启用/禁用直到连接关闭。
// 请在校准/配置显示屏前禁用 3Dlut，除非你想在校准前先查看显示效果。
// 如果你想查看最终显示效果，请在校准后启用 3Dlut。
BOOL madVR_Enable3dlut();
BOOL madVR_Disable3dlut();

// “madVR_Get/SetDeviceGammaRamp” 在目标 PC/显示器上调用 win32 API 
// “Get/SetDeviceGammaRamp”（获取/设置设备伽马渐变）。
// 如果 ramp 值为 “NULL”，则使用线性渐变（linear ramp）。
// 当您关闭连接后，渐变将会恢复为默认值。
// 译注：关于 Gamma Ramp 可参考下列文章：
// https://bbs.acgrip.com/thread-9813-1-2.html
#ifdef __cplusplus
  BOOL madVR_GetDeviceGammaRamp(LPVOID ramp);
  BOOL madVR_SetDeviceGammaRamp(LPVOID ramp = NULL);
#else
  BOOL madVR_GetDeviceGammaRamp(LPVOID ramp);
  BOOL madVR_SetDeviceGammaRamp(LPVOID ramp);
#endif

// “madVR_SetOsdText” 将输入的字符串 “text” 显示在视频左上角。
BOOL madVR_SetOsdText(LPCWSTR text);

// “madVR_Get/SetPatternConfig” 让您可以获取/设置 madVR 渲染的窗口中
// 使用测试图样颜色绘制的百分比，以及使用特定背景色绘制的百分比。
// 使用背景色使等离子测量（plasma measurements）有意义。
// 译注：不知道 plasma measurements 有没有更好的翻译。
// patternAreaInPercent（图样所占百分比）：    1-100（%）
// backgroundLevelInPercent（背景所占百分比）: 0-100（%）
// backgroundMode（背景模式）：          0 = constant gray；1 = APL - gamma light；2 = APL - linear light
// blackBorderWidth（黑边宽度）：        0-100（pixels），default：20
// 调用 “madVR_SetPatternConfig” 时，任何参数值不能为-1。
BOOL madVR_GetPatternConfig(int *patternAreaInPercent, int *backgroundLevelInPercent, int *backgroundMode, int *blackBorderWidth);
BOOL madVR_SetPatternConfig(int  patternAreaInPercent, int  backgroundLevelInPercent, int  backgroundMode, int  blackBorderWidth);

// “madVR_ShowProgressBar” 初始化 madVR 进度条。
// 它将在每次调用 “madVR_ShowRGB” 时前进一步（见下文）。
BOOL madVR_ShowProgressBar(int numberOfRgbMeasurements);

// “madVR_SetProgressBarPos” 将 madVR 进度条设置到指定位置。
// 调用该 API 后，进度条将再也不会在调用 “madVR_ShowRGB” 后自动移动。调用该 API
// 意味着您必须手动移动进度条。
BOOL madVR_SetProgressBarPos(int currentPos, int maxPos);

// “madVR_ShowRGB” 显示指定的 RGB 颜色测试图样。
// 颜色值会被伽马矫正（gamma correct）为 “black = 0.0” 和 “white = 1.0”。该值会被
// 自动由 madTPG 转换到 TV 或 PC 输出级别，取决于用户的显示设备设置。
// 您可以通过低于 0.0 或高于 1.0 来实现 BTB/WTW（BTB：Blacker Than Black，即 RGB 0~15；
// WTW：Whiter Than White，即 RGB 236~255）.当然，使用BTB/WTW的测试图样只有在 madVR
// 配置为 TV 输出时有效。
// “madVR_ShowRGB” 在 GPU 完全输出测试图样前将会被锁定。显示速度取决于显示屏的输入延迟，
// madVR 无法控制。
BOOL madVR_ShowRGB(double r, double g, double b);

// “madVR_ShowRGBEx” 和 “ShowRGB” 相似，但是背景色由您决定。
BOOL madVR_ShowRGBEx(double r, double g, double b, double bgR, double bgG, double bgB);

// ----------------------------------------------------------------------------
// 3dlut 的转换和加载

typedef double TEeColor3dlut[ 65][ 65][ 65][3];
typedef WORD     TMadVR3dlut[256][256][256][3];

// “madVR_Convert3dlutFile” 将一个已经存在的 eeColor 3Dlut 文件转换为 madVR 3Dlut
// 文件格式。64^3 3Dlut 将会使用线性 Mitchell 滤镜中间插值为 256^3 格式。
// HDR 模式中只支持 BT.709，BT.2020 和 DCI-P3。
// “gamut” 0：BT.709；1：SMPTE-C；2；EBU/PAL；3：BT.2020；4：DCI-P3
// “sdrOutput” true：3Dlut 伽马输出；false：3Dlut PQ 输出
BOOL madVR_Convert3dlutFile    (LPWSTR eeColor3dlutFile, LPWSTR madVR3dlutFile, int gamut);
BOOL madVR_ConvertHdr3dlutFile (LPWSTR eeColor3dlutFile, LPWSTR madVR3dlutFile, int gamut, BOOL sdrOutput);

// “madVR_Create3dlutFileFromArray65/255” 从一个和 eeColor 3Dlut 文本文件排列
// 相同的数组创建一个 madVR 3Dlut 文件.
// 64^3 3Dlut 将会使用线性 Mitchell 滤镜中间插值为 256^3 格式。
// HDR 模式中只支持 BT.709，BT.2020 和 DCI-P3。
// “gamut” 0：BT.709；1：SMPTE-C；2；EBU/PAL；3：BT.2020；4：DCI-P3
// “sdrOutput” true：3Dlut 伽马输出；false：3Dlut PQ 输出
BOOL madVR_Create3dlutFileFromArray65     (TEeColor3dlut *lutData, LPWSTR madVR3dlutFile, int gamut);
BOOL madVR_Create3dlutFileFromArray256    (  TMadVR3dlut *lutData, LPWSTR madVR3dlutFile, int gamut);
BOOL madVR_CreateHdr3dlutFileFromArray65  (TEeColor3dlut *lutData, LPWSTR madVR3dlutFile, int gamut, BOOL sdrOutput);
BOOL madVR_CreateHdr3dlutFileFromArray256 (  TMadVR3dlut *lutData, LPWSTR madVR3dlutFile, int gamut, BOOL sdrOutput);

// “madVR_Load3dlutFile” 在已连接的 madTPG 实例中加载一个 3Dlut（eeColor 或 madVR 格式）。
// 加载一个 3Dlut 会自动启用 3Dlut（madVR_Enable3dlut）。
// HDR 模式中只支持 BT.709，BT.2020 和 DCI-P3。
// “saveToSettings=false” 意味着 3Dlut 会在 madTPG 关闭前保持加载；“gamut” 会被忽略
// “saveToSettings=true” 意味着 3dlut 会被永久写入 madVR 设置和 “gamut”
// “gamut” 0：BT.709；1：SMPTE-C；2；EBU/PAL；3：BT.2020；4：DCI-P3
// “sdrOutput” true：3Dlut 伽马输出；false：3Dlut PQ 输出
BOOL madVR_Load3dlutFile    (LPWSTR lutFile, BOOL saveToSettings, int gamut);
BOOL madVR_LoadHdr3dlutFile (LPWSTR lutFile, BOOL saveToSettings, int gamut, BOOL sdrOutput);

// "madVR_Load3dlutFromArray65/255" loads a 3dlut into the connected
// madTPG instance.
// Loading a 3dlut automatically enables the 3dlut (madVR_Enable3dlut).
// HDR 模式中只支持 BT.709，BT.2020 和 DCI-P3。
// “saveToSettings=false” 意味着 3Dlut 会在 madTPG 关闭前保持加载；“gamut” 会被忽略
// “saveToSettings=true” 意味着 3dlut 会被永久写入 madVR 设置和 “gamut”
// “gamut” 0：BT.709；1：SMPTE-C；2；EBU/PAL；3：BT.2020；4：DCI-P3
// “sdrOutput” true：3Dlut 伽马输出；false：3Dlut PQ 输出
BOOL madVR_Load3dlutFromArray65     (TEeColor3dlut *lutData, BOOL saveToSettings, int gamut);
BOOL madVR_Load3dlutFromArray256    (  TMadVR3dlut *lutData, BOOL saveToSettings, int gamut);
BOOL madVR_LoadHdr3dlutFromArray65  (TEeColor3dlut *lutData, BOOL saveToSettings, int gamut, BOOL sdrOutput);
BOOL madVR_LoadHdr3dlutFromArray256 (  TMadVR3dlut *lutData, BOOL saveToSettings, int gamut, BOOL sdrOutput);

// ----------------------------------------------------------------------------
// 从 madVR 断开连接

// “madVR_Disconnect” 关闭当前的 madVR 连接。
BOOL madVR_Disconnect();

// “madVR_Quit” 关闭连接的 madTPG 实例。
BOOL madVR_Quit();

// ----------------------------------------------------------------------------
// 检查 madVR 可用性

// “madVR_IsAvailable” 检查是否能找到 madHcNet32.dll。
// 它必须在当前目录或搜索路径中，或者 PC 已经安装 madVR。
BOOL madVR_IsAvailable();

// ----------------------------------------------------------------------------


// ============================================================================
// II. 困难方式
// ============================================================================

// ----------------------------------------------------------------------------
// 在局域网中查找/模拟 madVR 实例

// 下列 APIs 让您自动定位正在运行的 madVR 实例，无论是在本地 PC 上还是在局域网中已验证
// 并连接的远程 PC。
// 每个找到的 madVR 实例会返回下列完整的信息：

typedef struct _TMadVRInstance
{                           // 示例：
  HANDLE    handle;         // 1
  ULONGLONG instance;       // 0x40001000
  LPSTR     ipAddress;      // "192.168.1.1"
  LPWSTR    computerName;   // "HTPC"
  LPWSTR    userName;       // "Walter"
  LPWSTR    os;             // "Windows 8.1"
  ULONG_PTR processId;      // 248
  LPWSTR    processName;    // "madVR Test Pattern Generator"
  LPWSTR    exeFile;        // "madTPG.exe"
  LPWSTR    exeVersion;     // 1.0.0.0
  LPWSTR    madVRVersion;   // 0.87.11.0
  LPWSTR    gpuName;        // "GeForce 750"
  LPWSTR    monitorName;    // "JVC HD-350"
} TMadVRInstance, *PMadVRInstance;

// 通常，网络搜索会在一秒内返回所有运行的实例。但是在特定情况下搜索会持续数秒。因
// 此，您由多种搜索方式。

// （1）同步搜索
// 调用 “madVR_Find”（见下文）并设置 timeOut（时限） 意味着 madVR_Find 将会在搜索完成
// 或者时限结束时返回结果。

// (2) 异步搜索 I
// 调用 "madVR_Find(0)" ，madVR_Find 会立刻返回并在后台开始搜索。
// 您可以在合适时再次调用 madVR_Find（timeOut 可以为任意值）来获取搜索结果。

// (3) 异步搜索 II
// 调用 madVR_Find_Async（见下文）来开始后台网络搜索。
// 每当找到一个新的 madVR 实例（或者一个 madVR 实例被关闭），一个消息将会发送到您选择的
// 窗口。当收到消息时，可以调用 madVR_Find(0) 来更新 madVR 实例列表。

typedef struct _TMadVRInstances
{
  ULONGLONG      count;
  TMadVRInstance items[1];
} TMadVRInstances, *PMadVRInstances;

// 返回所有在网络中找到的 madVR 实例信息记录。
// 内存由 madVR 分配，请不要自行分配或释放。
// 内存仅在下一次 madVR_Find 调用前有效。
PMadVRInstances madVR_Find(DWORD timeOut = 1000);

// “madVR_Find_Async” 搜索 madVR实例，但不会直接返回信息，它会在找到 madVR 实例时向
// 特定窗口发送消息。
// 搜索完成后，“madVR_Find_Async” 仍会持续自动地向您的窗口报告后来启动和关闭的 madVR 实例。
// 如果想停止通知，调用 “madVR_Find_Async(NULL)”。
// wParam：0 = 检测到一个新的 madVR 实例
//         1 = 一个已知的 madVR 实例关闭了
// lParam：新的/关闭的 madVR 实例的“PMadVRInstance”
//         不要释放 PMadVRInstance，该内存由 madVR 管理
BOOL madVR_Find_Async(HWND window, DWORD msg);

// ----------------------------------------------------------------------------
// 连接特定的 madVR 实例

// “madVR_Connect” 连接特定的 madVR 实例。
// 已经存在的连接会被自动关闭。
// 您可以通过 “madVR_Find（Async）” 来获得 “handle” 和 “instance”。
BOOL madVR_ConnectToInstance(HANDLE handle, ULONGLONG instance);

// ----------------------------------------------------------------------------


// ============================================================================
// III. 本地化 GUI
// ============================================================================

// 本地化/自定义所有 madVR_ConnectDialog 使用的文本。
                                                  //默认值：
void Localize_ConnectDialog (LPCWSTR title,       // madTPG selection...
                             LPCWSTR text,        // Please make sure that madTPG is running on the target computer and then select it here:
                             LPCWSTR columns,     // ip address|computer|pid|process|gpu|monitor|os
                             LPCWSTR notListed,   // The madTPG instance I'm looking for is not listed
                             LPCWSTR select,      // Select
                             LPCWSTR cancel       // Cancel
                            );

// 本地化/自定义所有 madVR_IpAddressDialog 使用的文本。
                                                       //默认值：
void Localize_IpAddressDialog (LPCWSTR title,          // find madTPG instance...
                               LPCWSTR text,           // Please enter the IP address of the computer on which madTPG is running:
                               LPCWSTR connect,        // Connect
                               LPCWSTR cancel,         // Cancel
                               LPCWSTR warningTitle,   // Warning...
                               LPCWSTR warningText1,   // There doesn't seem to be any madTPG instance running on that computer.
                               LPCWSTR warningText2    // The target computer does not react.\n\n
                              );                       // Please check if it's turned on and connected to the LAN.\n
                                                       // You may also want to double check your firewall settings.


// ============================================================================
// 弃用的 APIs
// ============================================================================

#ifdef __cplusplus
  BOOL madVR_ConnectDialog(BOOL searchLan = TRUE, HWND parentWindow = NULL);
  BOOL madVR_BlindConnect(BOOL searchLan = TRUE, DWORD timeOut = 3000);
#else
  BOOL madVR_ConnectDialog(BOOL searchLan, HWND parentWindow);
  BOOL madVR_BlindConnect(BOOL searchLan, DWORD timeOut);
#endif

// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------

#ifdef __cplusplus
  }
#endif

#endif
