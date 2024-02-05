#ifndef used_Active
#define used_Active

#include <map>
#include <math.h>
const double e = 2.718281828;
namespace ACTIVE{
	std::map <std::string,int> FindActiveId{
		{ "Sigmoid" , 1 },
		{ "Relu" , 2 }
	};
	std::map <int,std::string> FindActiveName{
		{ 1 , "Sigmoid" },
		{ 2 , "Relu" }
	};
	
	double sigmoid(double x)
	{ return 1.0/(1.0+pow(e,-x)); }
	double dsigmoid(double x)
	{ return sigmoid(x)*(1-sigmoid(x)); }
	double Relu(double x)
	{ return x >= 0.0 ? x : 0.5 * x; }
	double dRelu(double x)
	{ return x >= 0.0 ? 1 : 0.5; }
}

#endif