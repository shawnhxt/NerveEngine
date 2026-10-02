#ifndef used_RunDebug
#define used_RunDebug

#include "../HppSet.hpp"

using namespace ACTIVE;
using namespace CHECK;
using namespace EDGES;
using namespace NERVES;
using namespace SPREAD;
namespace DEBUG{
	/*	颜色打印
		str 被打印字符串
		Bstyle 字符串颜色
		Estyle 字符串打印结束后恢复的打印颜色 */
	string Style(string str,string Bstyle,string Estyle="37"){
		return "\033["+Bstyle+"m" + str + "\033["+Estyle+"m";
	}
	
	string ItoS(int Inter){
		string str;
		while(Inter){
			str += Inter%10 + '0';
			Inter /= 10;
		}
		if( str == "" )
			return "0";
		reverse(str.begin(),str.end());
		return str;
	}
	
	string Style(int Inter,string Bstyle,string Estyle){
		string str = ItoS(Inter);
		return "\033["+Bstyle+"m" + str + "\033["+Estyle+"m";
	}
	
	void ErrEnd(){
		if( !ErrState )
			return ;
		if( Errput )
			printf("%s",Style("| Error End.\n\n","31","37").c_str());
		return exit(0);
	}
	
	void BaiscPut(string &Message,va_list &v){
		for(int it=0;it<(int)Message.size();){
			if( Message[it] == '%' ){
				string s = "";
				while( it+1 < (int)Message.size() && Message[it] != 'd' && Message[it] != 'f' && Message[it] != 'c' && Message[it] != 's' )
					s += Message[it++];
				s += Message[it++];
				if( s[s.size()-1] == 'd' || s[s.size()-1] == 'c' ) printf(s.c_str(),va_arg(v,int));
				else if( s[s.size()-2] == 'l' && s[s.size()-1] == 'f' ) printf(s.c_str(),va_arg(v,double));
				// else if( s[s.size()-1] == 'f' ) printf(s.c_str(),va_arg(v,float));
				else if( s[s.size()-1] == 's' ) printf(s.c_str(),va_arg(v,char*));
			}
			else putchar(Message[it++]);
		}
		puts("");
		return ;
	}
	
	void ErroutPut(bool _exit_,string Message,...){
		++ErrState;
		if( Errput ){
			printf("\033[1;31m| Error%d |\033[37m ",ErrState);
			va_list v; va_start(v,Message);
			BaiscPut(Message,v);
			va_end(v);
		}
		if( _exit_ )
			ErrEnd();
		return ;
	}
	
	void SuccessPut(string Message,...){
		if( Sucput ){
			printf("\033[1;32m| Succes |\033[37m ");
			va_list v; va_start(v,Message);
			BaiscPut(Message,v);
			va_end(v);
		}
		return ;
	}
	
	void output(string Message,...){
		if( Output )
		{
			printf("\033[1;30m| output |\033[37m ");
			va_list v; va_start(v,Message);
			BaiscPut(Message,v);
			va_end(v);
		}
		return ;
	}
}

#endif
