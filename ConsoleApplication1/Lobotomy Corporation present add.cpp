#include <windows.h>
#include <iostream>
#include <vector> 
#include <algorithm>
using namespace std;

//定义要粘贴的文本向量
vector<string> texts = { "rimi agent present df 1023", "rimi agent present df 400004", "rimi agent present df 400065", "rimi agent present df 400035", "rimi agent present df 400015", "rimi agent present df 400046", "rimi agent present df 400103", "rimi agent present df 400104", "rimi agent present df 400032", "rimi agent present df 400033", "rimi agent present df 400038", "rimi agent present df 400039", "rimi agent present df 400020" };

//定义索引变量
int index = 0; //从0开始

//定义目标窗口名称
LPCWSTR window_name = L"lobotomy";

//定义按键延迟时间（毫秒）
int delay_time = 500;

//定义退出循环的按键
#define EXIT_KEY VK_ESCAPE

int main()
{   
    //定义变量d，并从用户那里获取它
    char d; //声明一个字符串类型的变量d
    cout << "Please enter a string for d， 输入员工编号d: "; //输出一句提示信息
    cin >> d; //使用cin对象从键盘读取用户输入的值，并赋给d

    //定义变量f，并从用户那里获取它
    char f; //声明一个字符串类型的变量f
    cout << "Please enter a string for f， 输入员工编号f: "; //输出一句提示信息
    cin >> f; //使用cin对象从键盘读取用户输入的值，并赋给f

    //遍历文本向量，用输入的数替换d
    for (auto& text : texts) {
        std::replace(text.begin(), text.end(), 'd', d); //在此替换
    }
    //遍历文本向量，用输入的数替换f
    for (auto& text : texts) {
        std::replace(text.begin(), text.end(), 'f', f); //在此替换
    }
    //查找目标窗口句柄
    HWND hWnd = FindWindow(NULL, window_name);

    //如果找到了目标窗口
    if (hWnd != NULL)
    {
        //循环执行操作
        while (true)
        {
            //获取当前要粘贴的文本
            string text = texts[index]; //使用方括号访问向量元素

            //将文本复制到剪切板
            OpenClipboard(NULL);
            EmptyClipboard();
            HGLOBAL hText = GlobalAlloc(GMEM_MOVEABLE, text.size() + 1);
            memcpy(GlobalLock(hText), text.c_str(), text.size() + 1);
            GlobalUnlock(hText);
            SetClipboardData(CF_TEXT, hText);
            CloseClipboard();
            
            //模拟按下~键
            keybd_event(VK_OEM_3, 0, 0, 0);
            //模拟释放~键
            keybd_event(VK_OEM_3, 0, KEYEVENTF_KEYUP, 0);
            //延迟一定时间
            Sleep(delay_time);
            //模拟按下回车键
            keybd_event(VK_RETURN, 0, 0, 0);
            //模拟释放回车键
            keybd_event(VK_RETURN, 0, KEYEVENTF_KEYUP, 0);
            //延迟一定时间
            Sleep(delay_time);
            //模拟按下Ctrl+Shift+V组合键
            keybd_event(VK_CONTROL | VK_SHIFT, 0, 0, 0); //同时按下Ctrl键和Shift键
            keybd_event('V', 0, 0, 0); //按下V键
            keybd_event('V', 0, KEYEVENTF_KEYUP, 0); //释放V键
            keybd_event(VK_CONTROL | VK_SHIFT, 0, KEYEVENTF_KEYUP, 0); //同时释放Ctrl键和Shift键
            //延迟一定时间
            Sleep(delay_time);

            //模拟按下回车键
            keybd_event(VK_RETURN, 0, 0, 0);
            //模拟释放回车键
            keybd_event(VK_RETURN, 0, KEYEVENTF_KEYUP, 0);
            //延迟一定时间
            Sleep(delay_time);

            //将索引变量加一，并使用取模运算符计算新的值，避免越界错误
            index = (index + 1) % texts.size();

            //检测是否按下了退出按键
            if (GetAsyncKeyState(EXIT_KEY))
            {
                //退出循环
                break;
            }
        }
    }
    else
    {
        //如果没有找到目标窗口，输出错误信息
        cout << "Cannot find the window." << endl;
    }
    return 0;
}

