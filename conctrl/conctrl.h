// ConsoleController
// 2018-11-28
// By Mattuy
#ifndef _HEAD_CONSOLE_CONTROLLER_
#define _HEAD_CONSOLE_CONTROLLER_
class ConsoleWindow;
class Pannel;
class Spliter;
/**
 * ��������̨������
 * @return value, ָ��ǰ����̨�Ŀ���̨���������ָ�룬��Ϊ���������Ĳ�������ͨ��������
 *				    ����̨��ʧ�ܷ���0
 * @param width,  ����̨���ڿ�ȣ���Ч��Χ(5, 32767)��Ĭ��80
 * @param height, ����̨���ڸ߶ȣ���Ч��Χ(5, 32767)��Ĭ��40
 */
ConsoleWindow* CreateConsoleWindow(int width = 80, int height = 40);
//�������ô��ںͻ�������С
bool ResizeConsoleWindow(ConsoleWindow* window, int width, int height);
/**
 * ���ÿ���̨���ڱ���
 * @param window, Ҫ���ñ���Ĵ���
 * @param title,  Ҫ���õı���
 * @param utf8,   �Ƿ�utf8���롣UTF-8����Ϊ��0��������ANSI����
 */
bool SetConsoleWindowTitle(char* title, bool utf8 = false);
/**
 * ����һ������
 * @return value, ָ��һ�������ָ��
 * @param window, ������������
 * @param left,   ������Դ��ڵ�ˮƽƫ�ƣ���Ч��Χ(5, 32767)
 * @param top,    ������Դ��ڵ���ֱƫ�ƣ���Ч��Χ(5, 32767)
 * @param width,  ����Ŀ�ȣ���Ч��Χ(5, 32767)
 * @param height, ����ĸ߶ȣ���Ч��Χ(5, 32767)
 */
Pannel* CreatePannel(ConsoleWindow* window, int left, int top, int width, int height);
//ɾ������
void DestroyPannel(ConsoleWindow* window, Pannel* pannel);
//���ô����л����С��������
bool SetlMaxLineCache(Pannel* pannel, int lineCount);
/**
 * ��Pannel������ı�������л���������һ�в��ǻ��з���β����á�AddPannelLine��������ӵģ���
 *    �ı����ϲ�����һ�С�ԭ�ı�����Ҳ�ᱻ���ǡ�
 * @param window, ������������
 * @param text,   Ҫ��ӵ��ַ���
 * @param utf8,   �Ƿ�utf8���롣��֧��ANSI�����UTF-8���룬����UTF-8����Ҳ����ת��ΪANSI
 *                ���롣Ĭ��Ϊfalse
 * @param attribute, ���ı����ԣ���Windows����Ŀ���̨������Ĭ�Ϻڵװ���
 */
void AddPannelText(Pannel* pannel, const char* text, bool utf8 = false, int attribute = 7);
//��AddTextΨһ�Ĳ�ͬ�ǣ�����ַ��������Ի��з���β�����Զ����뻻�з�
void AddPannelLine(Pannel* pannel, const char* text, bool utf8 = false, int attribute = 7);
//���Pannel���⽫ͬʱ���pannel���л�����
void ClearPannel(Pannel* pannel);
//�ƶ���ı�Pannel��С������ͬ��CreatePannel�����������������Ч���÷���������ı�
bool MovePannel(Pannel* pannel, int left, int top, int width, int height);
/**
 * ��ǰ������
 * @return value,    �������ǰ�Ѵ�������false�����򷵻�true
 * @param pannel,    Ҫ�����Ĵ���
 * @param lineCount, Ҫ���������������С��0����һ������Դ���
 */
bool ScrollPannelBackward(Pannel* pannel, int lineCount);
//��������
bool ScrollPannelForward(Pannel* pannel, int lineCount);
//�������ض��С�����к�С��0������󣬷�������к���Ч����false
bool ScrollPannelTo(Pannel* pannel, int lineTo);
/**
 * ��������õ�������ض�λ�á�
 * @return value,     ���offset��������Χ������ʧ��
 * @param pannel,     Ҫ���ù�����ڵĴ���
 * @param offsetLeft, �����Դ������Ͻǵ�ˮƽƫ�ƣ�Ĭ��Ϊ0
 * @param offsetTop,  �����Դ������ϽǵĴ�ֱƫ�ƣ�Ĭ��Ϊ0
 */
bool FocusOnPannel(Pannel* pannel, int offsetLeft = 0, int offsetTop = 0);
/**
 * ����һ���ָ��ߡ�
 * @return value,    ָ��һ���ָ��ߵ�ָ��
 * @param window,    ���������Ĵ���
 * @param left,      �ָ�����Դ��ڵ�ˮƽƫ�ƣ���Ч��Χ(5, 32767)
 * @param top,       �ָ�����Դ��ڵ���ֱƫ�ƣ���Ч��Χ(5, 32767)
 * @param length,    �ָ��ߵĳ��Ȼ��ȡ���ǰ�߻��Ǻ���ȡ����@param verticle
 * @param verticle,  ��ˮƽ�ָ��߻�����ֱ�ָ��ߡ�0Ϊˮƽ����0Ϊ��ֱ
 * @param attribute, �ָ��ߵ��ı����ԣ���Windows����Ŀ���̨������Ĭ�Ϻڵװ���
 */
Spliter* CreateSpliter(ConsoleWindow* window, int left, int top, int length, bool verticle, int attribute = 7);
//ɾ���ָ���
void DestroySpliter(Spliter* spliter);
/**
 * �ƶ��������趨�ָ��ߵĳ���
 * @param left, ��Դ����ˮƽƫ�ƣ����С��0�򲻸ı�
 * @param top,  ��Դ��ڵĴ�ֱƫ�ƣ����С��0�򲻸ı�
 * @param len,  �µĳ���/�߶ȡ����С��0�򲻸ı�
 */
bool MoveSpliter(int left, int top, int len);
#endif // !_HEAD_CONSOLE_CONTROLLER_
