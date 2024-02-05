#ifndef used_Edge
#define used_Edge

#include <iostream>
#include <vector>

#include "Debug.hpp"
#include "Nerves.hpp"

namespace EDGES{
	// { sBelongSet , sNerveId } -> { tBelongSet , tNerveId }
	void connect(int sBelongSetId,int sNerveId,int tBelongSetId,int tNerveId,double value)
	{
		if( sBelongSetId >= NERVES::NerveSets.size() || sBelongSetId < 0 ) // 如果 NerveSets 中不存在 sBelongSet
			DEBUG::ErroutPut(false,"In EDGES::connet(int,int,int,int,double)  can't find the sBelongSet[%d]", sBelongSetId );
		if( tBelongSetId >= NERVES::NerveSets.size() || tBelongSetId < 0 ) // 如果 NerveSets 中不存在 tBelongSet
			DEBUG::ErroutPut(false,"In EDGES::connet(int,int,int,int,double)  can't find the tBelongSet[%d]", tBelongSetId );
		DEBUG::ErrEnd();
		
		if( sNerveId >= NERVES::NerveSets[ sBelongSetId ].Nerves.size() || sNerveId < 0 ) // 如果 sBelongSet 中不存在 sNerveId
			DEBUG::ErroutPut(false,"In EDGES::connet(int,int,int,int,double)  can't find the sNerve[%d] in the NerveSet[%d]", sNerveId , sBelongSetId );
		if( tNerveId >= NERVES::NerveSets[ tBelongSetId ].Nerves.size() || tNerveId < 0 ) // 如果 tBelongSet 中不存在 tNerveId
			DEBUG::ErroutPut(false,"In EDGES::connet(int,int,int,int,double)  can't find the tNerve[%d] in the NerveSet[%d]", tNerveId , tBelongSetId );
		
		if( sBelongSetId == tBelongSetId ) // 如果 sBelongSet 与 tBelongSet 是同一个点集
			DEBUG::ErroutPut(false,"In EDGES::connet(int,int,int,int,double)  sBelongSetId[%d] can't equal to tBelongSetId[%d]", sBelongSetId , tBelongSetId );
		DEBUG::ErrEnd();
		
		// function
		NERVES::NerveSets[ sBelongSetId ].Nerves[ sNerveId ].outEdgeId.push_back({ tBelongSetId , tNerveId });
		NERVES::NerveSets[ tBelongSetId ].Nerves[ tNerveId ].inEdgeId.push_back({ sBelongSetId , sNerveId });
		
		DEBUG::SuccessPut("\033[1;36mconnet\033[1;37m { sBelongSet:%s , sNerveId:%d } -> { tBelongSet:%s , tNerveId:%d }", NERVES::NerveSets[ sBelongSetId ].name.c_str() , sNerveId , NERVES::NerveSets[ tBelongSetId ].name.c_str() , tNerveId );
		
		return ;
	}
	void connect(std::string sBelongSetName,int sNerveId,std::string tBelongSetName,int tNerveId,double value)
	{
		std::map <std::string,int>::iterator sBelongSetIt = NERVES::FindSetId.find( sBelongSetName );
		std::map <std::string,int>::iterator tBelongSetIt = NERVES::FindSetId.find( tBelongSetName );
		if( sBelongSetIt == NERVES::FindSetId.end() )
			DEBUG::ErroutPut(false,"In EDES::connet(string,int,string,int,double)  can't find { sBelongSet:%s } in NerveSets",sBelongSetName.c_str());
		if( tBelongSetIt == NERVES::FindSetId.end() )
			DEBUG::ErroutPut(false,"In EDES::connet(string,int,string,int,double)  can't find { sBelongSet:%s } in NerveSets",tBelongSetName.c_str());
		DEBUG::ErrEnd();
		return connect( sBelongSetIt->second , sNerveId , tBelongSetIt->second , tNerveId , value );
	}
}

#endif