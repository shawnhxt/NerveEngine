#ifndef used_RunAnylyse
#define used_RunAnylyse

#include "../HppSet.hpp"

namespace ANALYSE{
    void CalcDiff(){
        for(SET &resetSetId:NerveSets){
            for(NERVE &resetNerveId:resetSetId.Nerves)
                resetNerveId.diff = 0.0;
        }
        NERVE *nerve;
        for(RESULTS &x:results){
            nerve = &NerveSets[x.BelongSetId].Nerves[x.id];
            nerve->diff = ( nerve->weight - x.target ); // 求的是偏导，不平方
        }
        return ;
    }

    void SetTarget(int BelongSetId,int NerveId,double target,MESSAGE ms){
        if( BelongSetId >= (int)NerveSets.size() || BelongSetId < 0 )
			ErroutPut(true,"%s %s{ %s:%s } [%s|%d|%s]",
				Style("SetTarget(int,int)","35","37").c_str(),Style("Can't find that set","31","37").c_str(),
				Style("BelongSetId","33","37").c_str(),Style(BelongSetId,"36","37").c_str(),
				ms.file.c_str(),ms.line,ms.func.c_str()
			);
        map <pair<int,int>,int>::iterator resultsId = FindResultsId.find(pair(BelongSetId,NerveId));
        if( resultsId == FindResultsId.end() ){
            results.push_back(RESULTS(BelongSetId,NerveId,target));
            FindResultsId.insert(pair(pair(BelongSetId,NerveId),(int)results.size()-1));
        }
        else{
            results[resultsId->second].BelongSetId = BelongSetId;
            results[resultsId->second].id = NerveId;
            results[resultsId->second].target = target;
        }
        return ;
    }

    void SetTarget(string BelongSetName,int NerveId,double target,MESSAGE ms){
		map <string,int>::iterator BelongSetId = FindSetId.find( BelongSetName );
		if( BelongSetId == FindSetId.end() )
			ErroutPut(true,"%s %s{ %s:%s } [%s|%d|%s]",
				Style("SetTarget(string,int)","35","37").c_str(),Style("Can't find that set","31","37").c_str(),
				Style("BelongSetName","33","37").c_str(),Style(BelongSetName,"36","37").c_str(),
				ms.file.c_str(),ms.line,ms.func.c_str()
			);
        return SetTarget( BelongSetId->second, NerveId, target, ms );
    }
}

#endif
