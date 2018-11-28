# conctrl
## 简介
&emsp;&emsp;这个库提供一系列的函数来简化对Windows控制台窗口的输入输出（主要是输出）控制。通过它，你可以将窗口分割为不同的窗格，你也可以创建分隔线来分隔它们。而不管是窗口、窗格还是分隔线，你可以随时修改它们的大小和位置。

## 特性
&emsp;&emsp;你可以将控制台窗口分割为若干个**窗格**，窗格之间可创建**分割线**来区别它们。每个窗格拥有一个行缓存，包含若干**行**。你可以改变行缓存的大小。

&emsp;&emsp;你可以动态地为**窗格**增加**行**，仅需要向窗格添加文本，窗格将自动把文本分割为适应的行，改变窗格大小它也将自动更新。

&emsp;&emsp;你可以为每一**行**设定字符格式，字符格式由Windows的一些<a href="#constant">常量</a>定义。

## 开发环境
&emsp;&emsp;Windows，Visual Studio 2017

## 说明
&emsp;&emsp;需要注意的是，窗格只是逻辑意义上的窗格，它们属于同一个控制台窗口，共享输入缓冲区，因此这个库仅**适用于需要多个窗格用于输出**而不超过1个窗格同时用来输入。

&emsp;&emsp;构建这个库的初衷是为了方便某些高级语言操作控制台，因此将它的导出函数的参数都设定为简单的数值型和字符串，避免在高级语言中额外定义数据类型，方便使用。

&emsp;&emsp;此库通过调用Windows API实现，因此仅适用于Windows系统。

## 缺陷
* 对用户输入的控制比较无力
* 只能对整行设定字符样式
* 其他

## 使用示例
* ### C/C++
    
* ### 其他语言



## 函数列表



## 辅助资料
<a name="constant"> </a>

### Windows控制台字符样式常量
```C
#define FOREGROUND_BLUE      0x0001 // text color contains blue.
#define FOREGROUND_GREEN     0x0002 // text color contains green.
#define FOREGROUND_RED       0x0004 // text color contains red.
#define FOREGROUND_INTENSITY 0x0008 // text color is intensified.
#define BACKGROUND_BLUE      0x0010 // background color contains blue.
#define BACKGROUND_GREEN     0x0020 // background color contains green.
#define BACKGROUND_RED       0x0040 // background color contains red.
#define BACKGROUND_INTENSITY 0x0080 // background color is intensified.
#define COMMON_LVB_LEADING_BYTE    0x0100 // Leading Byte of DBCS
#define COMMON_LVB_TRAILING_BYTE   0x0200 // Trailing Byte of DBCS
#define COMMON_LVB_GRID_HORIZONTAL 0x0400 // DBCS: Grid attribute: top horizontal.
#define COMMON_LVB_GRID_LVERTICAL  0x0800 // DBCS: Grid attribute: left vertical.
#define COMMON_LVB_GRID_RVERTICAL  0x1000 // DBCS: Grid attribute: right vertical.
#define COMMON_LVB_REVERSE_VIDEO   0x4000 // DBCS: Reverse fore/back ground attribute.
#define COMMON_LVB_UNDERSCORE      0x8000 // DBCS: Underscore.
#define COMMON_LVB_SBCSDBCS        0x0300 // SBCS or DBCS flag.
```

## 项目地址
[https://github.com/mattuy/conctrl.git](https://github.com/mattuy/conctrl.git)