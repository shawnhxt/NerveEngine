/* Last update time: 2024/11/2 */
/* Last and ultimate? update time: 2026/7/15 */

#include "HppSet.hpp"

void test(MESSAGE ms){
	// DEBUG::Sucput = false;
	// DEBUG::Errput = false;
	// DEBUG::Output = false;
	DEBUG::SuccessPut("12343251");
	printf("[%s %d %s]\n",
		ms.file.c_str(),
		ms.line,
		ms.func.c_str()
	);
//	AddNerve("abc",5,MS);
	return exit(0);
}
void Initial(){
	printf("\033[1m");
	RootFile = __FILE__;
	while(!RootFile.empty()){
		if( *RootFile.rbegin()=='/' )
		{ RootFile.pop_back(); break; }
		RootFile.pop_back();
	}
	return ;
}

void graph1(){
	AddSet("In","Original",MS,1);
	AddSet("Hid1","Sigmoid",MS,2);
	AddSet("Hid2","Sigmoid",MS,2);
	AddSet("Out","Sigmoid",MS,0);
	
	AddNerve("In",2,MS);
	AddNerve("Hid1",2,MS);
	// AddNerve("Hid2",2,MS);
	AddNerve("Out",1,MS);
	
	srand(time(0));
	for(int i=0;i<=1;i++)
		for(int j=0;j<=1;j++)
			Connect("In",i,"Hid1",j,double(rand()%10000)/10000,MS);
	
	// for(int i=0;i<=1;i++)
	// 	for(int j=0;j<=1;j++)
	// 		Connect("Hid1",i,"Hid2",j,double(rand()%10000)/10000,MS);
	// for(int i=0;i<=1;i++)
	// 	for(int j=0;j<=0;j++)
	// 		Connect("Hid2",i,"Out",j,double(rand()%10000)/10000,MS);
	
	for(int i=0;i<=1;i++)
		for(int j=0;j<=0;j++)
			Connect("Hid1",i,"Out",j,double(rand()%10000)/10000,MS);
	//

	// ANALYSE::SetTarget("Out",1,1.0,MS); // 未报错?

	system("pause");
	for(int T=1;T<=2005;T++){
		int a = rand()%2;
		int b = rand()%2;
		int c = a xor b;
		ModifyWeight(0,0,a);
		ModifyWeight(0,1,b);
		ANALYSE::SetTarget("Out",0,c==0,MS);
		ANALYSE::SetTarget("Out",1,c==1,MS);

		SPREAD::Forward();
		ANALYSE::CalcDiff();
		BACKSPREAD::Backward();
		if( T % 100 == 0 || T > 2000 ){
			if( T <= 2000 ) system("cls");
			printf("----------------------------- %d | %d x %d = %d\n",T,a,b,c);
			NERVES::PrintSet(3);
			if( T > 2000 ) system("pause");
		}
	}
	
	// NERVES::PrintSet(0); // In
	// NERVES::PrintSet(1); // Hid1
	// NERVES::PrintSet(2); // Hid2
	// NERVES::PrintSet(3); // Out
	return ;
}

void graph2(){
	AddSet("In","Original",MS,1);
	AddSet("Hid","Sigmoid",MS,2);
	AddSet("Out","Sigmoid",MS,0);
	AddSet("Bias","Original",MS,1);
	
	AddNerve("In",2,MS);
	AddNerve("Hid",2,MS);
	AddNerve("Out",2,MS);
	AddNerve("Bias",2,MS);
	
	Connect("In",0,"Hid",0,.15,MS);
	Connect("In",0,"Hid",1,.25,MS);
	Connect("In",1,"Hid",0,.20,MS);
	Connect("In",1,"Hid",1,.30,MS);
	
	Connect("Hid",0,"Out",0,.40,MS);
	Connect("Hid",0,"Out",1,.50,MS);
	Connect("Hid",1,"Out",0,.45,MS);
	Connect("Hid",1,"Out",1,.55,MS);
	
	Connect("Bias",0,"Hid",0,1.0,MS);
	Connect("Bias",0,"Hid",1,1.0,MS);

	Connect("Bias",1,"Out",0,1.0,MS);
	Connect("Bias",1,"Out",1,1.0,MS);

	AddSet("Hid","UnexitedType",MS,1);

	ModifyWeight(0,0,.05);
	ModifyWeight(0,1,.10);

	ModifyWeight(3,0,.35);
	ModifyWeight(3,1,.60);

	
	ANALYSE::SetTarget("Out",0,.01,MS);
	ANALYSE::SetTarget("Out",1,.99,MS);

	SPREAD::Forward();
	
	// NERVES::PrintSet(0);
	// NERVES::PrintSet(1);
	// NERVES::PrintSet(2);
	// NERVES::PrintSet(3);
	// printf("-----------------------------\n");

	ANALYSE::CalcDiff();
	BACKSPREAD::Backward();
	
	NERVES::PrintSet(0);
	NERVES::PrintSet(1);
	NERVES::PrintSet(2);
	NERVES::PrintSet(3);

	return ;
}

int main(){
	printf("%s\n",Style("--- started ---","1;35").c_str());
	
	Initial();
	// test(MS);
	
	// graph1();
	graph2();
	
	return 0;
}
