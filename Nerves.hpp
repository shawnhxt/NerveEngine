#ifndef used_Nerves
#define used_Nerves

#include <iostream>
#include <stdio.h>
#include <vector>
#include <map>

#include "Debug.hpp"
#include "Active.hpp"

namespace NERVES{
	// 存连边另一端所指向的点的信息
	struct TONERVE{
		// BelongSetId: 连边另一端所指向的点所在的点集
		// id: 连边另一端所指向的点所在其点集的编号
		int BelongSetId,id;
	};
    bool operator <(TONERVE A,TONERVE B)
    {
        if( A.BelongSetId != B.BelongSetId )
            return A.BelongSetId < B.BelongSetId;
        return A.id < B.id;
    }
	struct NERVE{
		// BelongSetId: 所属点集
		// id: 在所属点集的编号
		// inEdgeId: 入边集合
		// outEdgeId: 出边集合
		int BelongSetId,id;
		std::vector <TONERVE> inEdgeId;
		std::vector <TONERVE> outEdgeId;
	};
	
	// ID 0 to siz-1 
	struct SET{
		// name: 点集名称
		// activeType: 点集所用激活函数
		// Nerves: 点集内每个点的编号及信息
		std::string name; // 与 50 行冗杂了 删了 ，注意要把 EDGE.hpp 中 33 打印也修改一下
		int activeType;
		std::vector <NERVE> Nerves;
	};
	// NerveSets: 点集的集合
	std::vector <SET> NerveSets;
	
	// FindSetId: 根据点集名称查找点集编号
	// FindSetName: 根据点集编号查找点集名称
	std::map <std::string,int> FindSetId;
	std::map <int,std::string> FindSetName;
}

namespace NERVES{
	int AddSet(std::string name,int activeType)
	{
		if( FindSetId.find( name ) != FindSetId.end() )
			DEBUG::ErroutPut(true,"In NERVES::AddSet(string,int)  there already have the set[%d] of the name[%s]", FindSetId.find( name )->second ,name.c_str());
		NerveSets.push_back(SET());
		NerveSets[ NerveSets.size()-1 ].name = name;
		NerveSets[ NerveSets.size()-1 ].activeType = activeType;
		FindSetId[ name ] = NerveSets.size()-1;
		FindSetName[ NerveSets.size()-1 ] = name;
		DEBUG::SuccessPut("\033[1;36mAddSet\033[1;37m { name:%s , active:%s }",name.c_str(),ACTIVE::FindActiveName[activeType].c_str());
		return NerveSets.size()-1;
	}
	int AddSet(std::string name,std::string actType)
	{
		if( FindSetId.find( name ) != FindSetId.end() )
			DEBUG::ErroutPut(false,"In NERVES::AddSet(string,string)  there already have the set { Id:%d , Name:%s }", FindSetId.find( name )->second ,name.c_str());
		std::map <std::string,int>::iterator ActiveIt = ACTIVE::FindActiveId.find(actType);
		if( ActiveIt == ACTIVE::FindActiveId.end() )
			DEBUG::ErroutPut(false,"In NERVES::AddSet(string,string)  can't find the activion called [%s]",actType.c_str());
		DEBUG::ErrEnd();
		return AddSet( name , ActiveIt->second );
	}
	
	int AddNerve(int SetId)
	{
		if( SetId >= FindSetId.size() )
			DEBUG::ErroutPut(true,"In NERVES::AddNerve(int)  can't find a SetId with %d",SetId);
		NERVE key;
		key.BelongSetId = SetId;
		key.id = NerveSets[ SetId ].Nerves.size();
		NerveSets[ SetId ].Nerves.push_back( key );
		DEBUG::SuccessPut("\033[1;36mAddNerve\033[1;37m { SetName:%s , NerveId:%d }",FindSetName[SetId].c_str(),key.id);
		return 0;
	}
	int AddNerve(std::string SetName)
	{
		if( FindSetId.find( SetName ) == FindSetId.end() )
			DEBUG::ErroutPut(true,"In EERVES::AddNerve(string)  can't find any Set which has the name[%s]",SetName.c_str());
		return AddNerve( FindSetId.find( SetName )->second );
	}
}

#endif