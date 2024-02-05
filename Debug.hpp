#ifndef used_Debug
#define used_Debug

#include <iostream>
#include <stdio.h>

// #include <windows.h>
#include <stdarg.h>

namespace DEBUG{
	int ErrState = 0;
	bool Errput = true;
	bool Sucput = true;
	bool Output = true;
	void ErrEnd()
	{
		if( !ErrState )
			return ;
		if( Errput )
		{
			// SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0C );
			printf("\033[1;31m");
			printf("| Error End.\n\n");
			// SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07 );
			printf("\033[m");
		}
		return exit(0);
	}
	void BaiscPut(std::string &Message,va_list &v)
	{
		for(int it=0;it<Message.size();)
		{
			if( Message[it] == '%' )
			{
				std::string s = "";
				while( it+1 < Message.size() && Message[it] != 'd' && Message[it] != 'f' && Message[it] != 'c' && Message[it] != 's' )
					s += Message[it++];
				s += Message[it++];
				if( s[s.size()-1] == 'd' || s[s.size()-1] == 'c' ) printf(s.c_str(),va_arg(v,int));
				else if( s[s.size()-2] == 'l' && s[s.size()-1] == 'f' ) printf(s.c_str(),va_arg(v,double));
				// else if( s[s.size()-1] == 'f' ) printf(s.c_str(),va_arg(v,float));
				else if( s[s.size()-1] == 's' ) printf(s.c_str(),va_arg(v,char*));
			}
			else putchar(Message[it++]);
		}
		puts(""),puts("");
		return ;
	}
	void ErroutPut(bool _exit_,std::string Message,...)
	{
		if( Errput )
		{
			// SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0C );
			
			printf("\033[1;31m| Error%d |\033[33m ",++ErrState);
			
			va_list v; va_start(v,Message);
			BaiscPut(Message,v);
			va_end(v);
			
			// SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07 );
			printf("\033[37m");
		}
		
		// ErrState = true;
		
		if( _exit_ )
			ErrEnd();
		
		return ;
	}
	void SuccessPut(std::string Message,...)
	{
		if( Sucput )
		{
			// SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0A );
			
			printf("\033[1;32m| Succes |\033[1;37m ");
			
			va_list v; va_start(v,Message);
			BaiscPut(Message,v);
			va_end(v);
			
			// SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07 );
			printf("\033[37m");
		}
		
		return ;
	}
	void output(std::string Message,...)
	{
		if( Output )
		{
			// SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F );
			
			printf("\033[1;30m| output |\033[1;37m ");
			
			va_list v; va_start(v,Message);
			BaiscPut(Message,v);
			va_end(v);
			
			// SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07 );
			printf("\033[m");
		}
		return ;
	}
}

#endif