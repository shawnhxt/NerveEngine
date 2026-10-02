#ifndef used_PreDebug
#define used_PreDebug

#include "../HppSet.hpp"

#define MS MESSAGE(__FILE__,__LINE__,__func__)
string RootFile; // 项目所在文件夹
struct MESSAGE;

namespace DEBUG{
	int ErrState = 0;
	bool Errput = true;
	bool Sucput = true;
		bool Sucput_Connect = true;
		bool Sucput_AddNerve = true;
		bool Sucput_AddSet = true;
	bool Output = true;
}

#endif
/*	\033[37;1;5;40m 将字体颜色设置为白色，高亮字体，闪烁，字体背景设为黑色
字体  背景  颜色
----------------
30    40	黑色
31    41	红色
32    42	绿色
33    43	黄色
34    44	蓝色
35    45  紫红色
36    46  青蓝色
37    47	白色
0 终端默认设置（黑底白字）
1 高亮显示
4 使用下划线
5 闪烁
7 反白显示
8 不可见
\033[2J\033[0;0H 清屏并将光标置顶
（下面的必须要单独一句\033[）
nA	光标上移n行
nB	光标下移n行
nC	光标右移n行
nD	光标左移n行
y;xH 设置光标位置
2J	清屏
K	清除从光标到行尾的内容
s	保存光标位置
u	恢复光标位置
?25l 隐藏光标
?25h 显示光标
*/
