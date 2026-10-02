#ifndef used_NxtActive
#define used_NxtActive

#include "../HppSet.hpp"

namespace ACTIVE{
	double sigmoid(double);
	double dsigmoid(double);
	double Relu(double);
	double dRelu(double);
	double ActiveWeight(int,int);
	double pow2(double);
	map <std::string,int> FindActiveId{
		{ "Null", 0 },
		{ "Sigmoid", 1 },
		{ "Relu", 2 },
		{ "Base xxx", 3 },
		{ "Original", 4 }
	};
	map <int,std::string> FindActiveName{
		{ 0, "Null" },
		{ 1, "Sigmoid" },
		{ 2, "Relu" },
		{ 3, "Base xxx" },
		{ 4, "Original" }
	};
}

#endif
