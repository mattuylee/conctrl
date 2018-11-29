// ConsoleController
// 2018-11-28
// By Mattuy
#ifndef _HEAD_CONSOLE_CONTROLLER_
#define _HEAD_CONSOLE_CONTROLLER_
class ConsoleWindow;
class Pannel;
class Spliter;
/**
 * 创建控制台控制器
 * @return value, 指向当前控制台的控制台操作对象的指针，作为其他函数的参数，以通过它控制
 *				    控制台。失败返回0
 * @param width,  控制台窗口宽度，有效范围(5, 32767)，默认80
 * @param height, 控制台窗口高度，有效范围(5, 32767)，默认40
 */
ConsoleWindow* CreateConsoleWindow(int width = 80, int height = 40);
//重新设置窗口和缓冲区大小
bool ResizeConsoleWindow(ConsoleWindow* window, int width, int height);
/**
 * 设置控制台窗口标题
 * @param window, 要设置标题的窗口
 * @param title,  要设置的标题
 * @param utf8,   是否utf8编码。UTF-8请设为非0，否则当作ANSI处理
 */
bool SetConsoleWindowTitle(char* title, bool utf8 = false);
/**
 * 创建一个窗格。
 * @return value, 指向一个窗格的指针
 * @param window, 窗格所属窗口
 * @param left,   窗格相对窗口的水平偏移，有效范围(5, 32767)
 * @param top,    窗格相对窗口的竖直偏移，有效范围(5, 32767)
 * @param width,  窗格的宽度，有效范围(5, 32767)
 * @param height, 窗格的高度，有效范围(5, 32767)
 */
Pannel* CreatePannel(ConsoleWindow* window, int left, int top, int width, int height);
//删除窗格
void DestroyPannel(ConsoleWindow* window, Pannel* pannel);
//设置窗格行缓存大小（行数）
bool SetlMaxLineCache(Pannel* pannel, int lineCount);
/**
 * 向Pannel中添加文本。如果行缓冲区中上一行不是换行符结尾或调用【AddPannelLine】函数添加的，新
 *    文本将合并到上一行。原文本属性也会被覆盖。
 * @param window, 窗格所属窗口
 * @param text,   要添加的字符串
 * @param utf8,   是否utf8编码。仅支持ANSI编码和UTF-8编码，并且UTF-8编码也将被转换为ANSI
 *                编码。默认为false
 * @param attribute, 行文本属性，由Windows定义的控制台常量，默认黑底白字
 */
void AddPannelText(Pannel* pannel, const char* text, bool utf8 = false, int attribute = 7);
//与AddText唯一的不同是，如果字符串不是以换行符结尾，将自动插入换行符
void AddPannelLine(Pannel* pannel, const char* text, bool utf8 = false, int attribute = 7);
//清空Pannel。这将同时清除pannel的行缓冲区
void ClearPannel(Pannel* pannel);
//移动或改变Pannel大小，参数同【CreatePannel】。如果参数分量无效，该分量将不会改变
bool MovePannel(Pannel* pannel, int left, int top, int width, int height);
/**
 * 向前滚屏。
 * @return value,    如果滚动前已触顶返回false，否则返回true
 * @param pannel,    要滚动的窗格
 * @param lineCount, 要滚动的行数，如果小于0滚动一屏（相对窗格）
 */
bool ScrollPannelBackward(Pannel* pannel, int lineCount);
//向后滚屏。
bool ScrollPannelForward(Pannel* pannel, int lineCount);
//滚动到特定行。如果行号小于0滚到最后，否则如果行号无效返回false
bool ScrollPannelTo(Pannel* pannel, int lineTo);
/**
 * 将光标设置到窗格的特定位置。
 * @return value,     如果offset超出窗格范围则设置失败
 * @param pannel,     要设置光标所在的窗格
 * @param offsetLeft, 光标相对窗格左上角的水平偏移，默认为0
 * @param offsetTop,  光标相对窗格左上角的垂直偏移，默认为0
 */
bool FocusOnPannel(Pannel* pannel, int offsetLeft = 0, int offsetTop = 0);
/**
 * 创建一条分隔线。
 * @return value,    指向一条分隔线的指针
 * @param window,    窗格所属的窗口
 * @param left,      分隔线相对窗口的水平偏移，有效范围(5, 32767)
 * @param top,       分隔线相对窗口的竖直偏移，有效范围(5, 32767)
 * @param length,    分割线的长度或宽度。是前者还是后者取决于@param verticle
 * @param verticle,  是水平分隔线还是竖直分隔线。0为水平，非0为竖直
 * @param attribute, 分割线的文本属性，由Windows定义的控制台常量，默认黑底白字
 */
Spliter* CreateSpliter(ConsoleWindow* window, int left, int top, int length, bool verticle, int attribute = 7);
//删除分隔线
void DestroySpliter(Spliter* spliter);
/**
 * 移动或重新设定分隔线的长度
 * @param left, 相对窗格的水平偏移，如果小于0则不改变
 * @param top,  相对窗口的垂直偏移，如果小于0则不改变
 * @param len,  新的长度/高度。如果小于0则不改变
 */
bool MoveSpliter(int left, int top, int len);
#endif // !_HEAD_CONSOLE_CONTROLLER_
