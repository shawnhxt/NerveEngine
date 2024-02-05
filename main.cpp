#include <iostream>
#include <stdio.h>

#include "Debug.hpp"
#include "Edge.hpp"
#include "Active.hpp"
#include "Nerves.hpp"
#include "Check.hpp"

// 每种 succ yanse

using namespace std;
int main()
{
	printf("\033[1;35m warning \033[37m\n\n");

//	DEBUG::Sucput = false;
//	DEBUG::Errput = false;
//	DEBUG::Output = false;

	NERVES::AddSet("InNerves","Relu");
	NERVES::AddNerve("InNerves");

	// NERVES::AddNerve(3);
	
	NERVES::AddSet("OutNerves","Sigmoid");
	NERVES::AddNerve("OutNerves");
	NERVES::AddNerve("OutNerves");
	
	DEBUG::output("afuafu");
	
	DEBUG::output("%d %.3lf %c",1,3.1415,97);
	
	DEBUG::output("%d %lf %c",1,2.0,'3');

	// EDGES::connect( "InNeves", 0, "OtNerves", 0 , 3.0 );
	
	EDGES::connect( "InNerves", 0, "OutNerves", 0 , 3.0 );
	EDGES::connect( "InNerves", 0, "OutNerves", 1 , 3.0 );
	// EDGES::connect( "OutNerves", 1, "InNerves", 0 , 3.0 );

	CHECK::check();
	
	return 0;
}