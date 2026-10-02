#ifndef used_RunEdge
#define used_RunEdge

#include "../HppSet.hpp"

using namespace ACTIVE;
using namespace CHECK;
using namespace DEBUG;
using namespace NERVES;
using namespace SPREAD;
namespace EDGES{
	// { sBelongSet , sNerveId } -> { tBelongSet , tNerveId }
	void Connect(int sBelongSetId,int sNerveId,int tBelongSetId,int tNerveId,double value,MESSAGE ms){
		if( sBelongSetId >= (int)NerveSets.size() || sBelongSetId < 0 ) // 如果 NerveSets 中不存在 sBelongSet
			ErroutPut(false,"%s %s{ %s:%s } [%s|%d|%s]",
				Style("Connect(int,int,int,int,double)","35","37").c_str(),Style("Can't find that set","31","37").c_str(),
				Style("sBelongSetId","33","37").c_str(),Style(sBelongSetId,"36","37").c_str(),
				ms.file.c_str(),ms.line,ms.func.c_str()
			);
		if( tBelongSetId >= (int)NerveSets.size() || tBelongSetId < 0 ) // 如果 NerveSets 中不存在 tBelongSet
			ErroutPut(false,"%s %s{ %s:%s } [%s|%d|%s]",
				Style("Connect(int,int,int,int,double)","35","37").c_str(),Style("Can't find that set","31","37").c_str(),
				Style("tBelongSetId","33","37").c_str(),Style(tBelongSetId,"36","37").c_str(),
				ms.file.c_str(),ms.line,ms.func.c_str()
			);
		ErrEnd();
		
		if( sNerveId >= (int)NerveSets[ sBelongSetId ].Nerves.size() || sNerveId < 0 ) // 如果 sBelongSet 中不存在 sNerveId
			ErroutPut(false,"%s %s{ %s:%s, %s:%s, %s:%s } [%s|%d|%s]",
				Style("Connect(int,int,int,int,double)","35","37").c_str(),Style("Can't find that nerve","31","37").c_str(),
				Style("sBelongSetName","33","37").c_str(),Style(NerveSets[sBelongSetId].name,"36","37").c_str(),
				Style("SetSize","33","37").c_str(),Style(NerveSets[sBelongSetId].Nerves.size(),"36","37").c_str(),
				Style("sNerveId","33","37").c_str(),Style(sNerveId,"36","37").c_str(),
				ms.file.c_str(),ms.line,ms.func.c_str()
			);
		if( tNerveId >= (int)NerveSets[ tBelongSetId ].Nerves.size() || tNerveId < 0 ) // 如果 tBelongSet 中不存在 tNerveId
			ErroutPut(false,"%s %s{ %s:%s, %s:%s, %s:%s } [%s|%d|%s]",
				Style("Connect(int,int,int,int,double)","35","37").c_str(),Style("Can't find that nerve","31","37").c_str(),
				Style("tBelongSetName","33","37").c_str(),Style(NerveSets[tBelongSetId].name,"36","37").c_str(),
				Style("SetSize","33","37").c_str(),Style(NerveSets[tBelongSetId].Nerves.size(),"36","37").c_str(),
				Style("tNerveId","33","37").c_str(),Style(tNerveId,"36","37").c_str(),
				ms.file.c_str(),ms.line,ms.func.c_str()
			);
		if( sBelongSetId == tBelongSetId ) // 如果 sBelongSet 与 tBelongSet 是同一个点集
			ErroutPut(false,"%s %s{ %s:%s, %s:%s } [%s|%d|%s]",
				Style("Connect(int,int,int,int,double)","35","37").c_str(),Style("The connected nerves can't belong to the same set","31","37").c_str(),
				Style("SetName","33","37").c_str(),Style(NerveSets[sBelongSetId].name,"36","37").c_str(),
				Style("SetName","33","37").c_str(),Style(sBelongSetId,"36","37").c_str(),
				ms.file.c_str(),ms.line,ms.func.c_str()
			);
		ErrEnd();
		
		// todo 记录边权
		NERVE *sNerve = &NerveSets[ sBelongSetId ].Nerves[ sNerveId ];
		sNerve->outEdgeId.push_back({ tBelongSetId, tNerveId, value });
		
		NERVE *tNerve = &NerveSets[ tBelongSetId ].Nerves[ tNerveId ];
		tNerve->inEdgeId.push_back({ sBelongSetId, sNerveId, value });
		tNerve->inEdgeId_outId.push_back( sNerve->outEdgeId.size()-1 );

		if( Sucput_Connect == true )
			SuccessPut("%s{ %s:%s, %s:%s } -> { %s:%s, %s:%s } [%s|%d|%s]",
				Style("Connect","34","37").c_str(),
				Style("sBelongSet","33","37").c_str(),Style(NerveSets[sBelongSetId].name,"36","37").c_str(),
				Style("sNerveId","33","37").c_str(),Style(sNerveId,"36","37").c_str(),
				Style("tBelongSet","33","37").c_str(),Style(NerveSets[tBelongSetId].name,"36","37").c_str(),
				Style("tNerveId","33","37").c_str(),Style(tNerveId,"36","37").c_str(),
				ms.file.c_str(),ms.line,ms.func.c_str()
			);
		
		return ;
	}
	
	void Connect(string sBelongSetName,int sNerveId,string tBelongSetName,int tNerveId,double value,MESSAGE ms){
		map <string,int>::iterator sBelongSetId = FindSetId.find( sBelongSetName );
		map <string,int>::iterator tBelongSetId = FindSetId.find( tBelongSetName );
		if( sBelongSetId == FindSetId.end() )
			ErroutPut(false,"%s %s{ %s:%s } [%s|%d|%s]",
				Style("Connect(string,int,string,int,double)","35","37").c_str(),Style("Can't find that set","31","37").c_str(),
				Style("sBelongSetName","33","37").c_str(),Style(sBelongSetName,"36","37").c_str(),
				ms.file.c_str(),ms.line,ms.func.c_str()
			);
		if( tBelongSetId == FindSetId.end() )
			ErroutPut(false,"%s %s{ %s:%s } [%s|%d|%s]",
				Style("Connect(string,int,string,int,double)","35","37").c_str(),Style("Can't find that set","31","37").c_str(),
				Style("tBelongSetName","33","37").c_str(),Style(tBelongSetName,"36","37").c_str(),
				ms.file.c_str(),ms.line,ms.func.c_str()
			);
		if( sBelongSetName == tBelongSetName ) // 如果 sBelongSet 与 tBelongSet 是同一个点集
			ErroutPut(false,"%s %s{ %s:%s, %s:%s } [%s|%d|%s]",
				Style("Connect(string,int,string,int,double)","35","37").c_str(),Style("The nerves connected can't belong to the same set","31","37").c_str(),
				Style("SetName","33","37").c_str(),Style(sBelongSetName,"36","37").c_str(),
				Style("SetName","33","37").c_str(),Style(FindSetId[sBelongSetName],"36","37").c_str(),
				ms.file.c_str(),ms.line,ms.func.c_str()
				);
		ErrEnd();
		return Connect( sBelongSetId->second, sNerveId, tBelongSetId->second, tNerveId, value, ms );
	}
}

#endif
