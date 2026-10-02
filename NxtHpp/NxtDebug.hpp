#ifndef used_NxtDebug
#define used_NxtDebug

#include "../HppSet.hpp"

struct MESSAGE{
	/*	file 代码所在文件及其位置
	line 代码在其文件中第几行
	func 代码所在函数名称 */
	string file,func;
	int line;
	MESSAGE(string fi,int li,string fu){
		if( fi.find(RootFile) == 0 ) // 去除项目文件夹前面的文件夹索引字符串，减少打印量，便于快速纠错
			fi = fi.substr( fi.find(RootFile)+RootFile.size() , fi.size()-RootFile.size() );
		file = fi, line = li, func = fu;
		return ;
	}
};

namespace DEBUG{
	string Style(string,string,string);
	string ItoS(int);
	string Style(int,string,string);
	void ErrEnd();
	void BaiscPut(string&,va_list&);
	void ErroutPut(bool,string,...);
	void SuccessPut(string,...);
	void output(string,...);
};

#endif