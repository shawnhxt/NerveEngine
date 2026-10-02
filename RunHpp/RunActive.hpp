#ifndef used_RunActive
#define used_RunActive

#include "../HppSet.hpp"

namespace ACTIVE{

	inline double sigmoid(double x)
	{ return 1.0/(1.0+pow(e,-x)); }
	inline double dsigmoid(double x)
	// { return sigmoid(x)*(1-sigmoid(x)); }
	{ return x*(1.0-x); }

	inline double Relu(double x)
	{ return x >= 0.0 ? x : 0.5 * x; }
	inline double dRelu(double x)
	{ return x >= 0.0 ? 1 : 0.5; }

	inline double ActiveWeight(int SetId,int NerveId){
		int activeType = NerveSets[SetId].activeType;
		if( activeType == 1 )
			return sigmoid( NerveSets[SetId].Nerves[NerveId].weight );
		if( activeType == 2 )
			return Relu( NerveSets[SetId].Nerves[NerveId].weight );
		if( activeType == 3 )
			return NerveSets[SetId].Nerves[NerveId].weight;
		if( activeType == 4 )
			return NerveSets[SetId].Nerves[NerveId].weight;
		ErroutPut(true,"| Error | Active function not find. %d", activeType);
		return 0;
	}
	inline double dActiveWeight(int ActiveType,double Weight){
		if( ActiveType == 1 )
			return dsigmoid(Weight);
		if( ActiveType == 2 )
			return dRelu(Weight);
		// if( ActiveType == 3 )
		// 	return Weight;
		if( ActiveType == 4 )
			return 1;
		ErroutPut(true,"| Error | dActive function not find.");
		return 0;
	}

	inline double pow2(double x)
	{ return x*x; }
}

#endif
