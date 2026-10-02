#ifndef used_RunNerves
#define used_RunNerves

#include "../HppSet.hpp"

namespace NERVES{
	/*	@brief
			新建点集
		@param
			name 新建点集名称
		@param
			actType 新建点集使用的激活函数的编号
		@return
			新建点集编号 */
	int AddSet(string name,int activeType,MESSAGE ms,int typ=2){
		if( FindSetId.find( name ) != FindSetId.end() ) // 如果存在已创建的同名点集，报错
			ErroutPut(false,"%s %s{ %s:%s, %s:%s } [%s|%d|%s]",
				Style("AddSet(string,int)","35","37").c_str(),Style("There already has a set","31","37"),
				Style("Id","33","37").c_str(),Style(FindSetId.find( name )->second,"36","37").c_str(),
				Style("Name","33","37").c_str(),Style(name,"36","37").c_str(),
				ms.file.c_str(),ms.line,ms.func.c_str()
			);
		if( FindActiveName.find(activeType) == FindActiveName.end() ) // 如果没有编号为 actType 的激活函数，报错
			ErroutPut(false,"%s %s{ %s:%s } [%s|%d|%s]",
				Style("AddSet(string,int)","35","37").c_str(),Style("Can't find the activion","31","37"),
				Style("ActiveId","33","37").c_str(),Style(activeType,"36","37").c_str(),
				ms.file.c_str(),ms.line,ms.func.c_str()
			);
		ErrEnd();
		
		NerveSets.push_back(SET()); // 向储存点集的集合中新加入一个点集
		
		// 设置所建点集的信息
		NerveSets[ NerveSets.size()-1 ].name = name;
		NerveSets[ NerveSets.size()-1 ].activeType = activeType;
		if( typ == 0 ) OutSet.push_back( NerveSets.size()-1 );
		else if( typ == 1 ) InSet.push_back( NerveSets.size()-1 );
		
		FindSetId[ name ] = NerveSets.size()-1; // 通过 所建点集的名称 找到 所建点集在储存点集集合中的编号
		
		// 报告成功新建点集
		if( Sucput_AddSet == true )
			SuccessPut("%s{ %s:%s, %s:%s } [%s|%d|%s]",
				Style("AddSet","34","37").c_str(),
				Style("Name","33","37").c_str(),Style(name,"36","37").c_str(),
				Style("Active","33","37").c_str(),Style(FindActiveName[activeType],"36","37").c_str(),
				ms.file.c_str(),ms.line,ms.func.c_str()
			);
		return NerveSets.size()-1; // 返回新建点集在储存点集集合中的编号
	}
	
	/*	@brief
			新建点集
		@param
			name 新建点集名称
		@param
			actType 新建点集使用的激活函数的编号
		@param
			typ 1:用于输入 ; 0:用于输出 ; 2:隐藏层
		@return
			新建点集编号 */
	int AddSet(string name,string activeType,MESSAGE ms,int typ=2){
		if( FindSetId.find(name) != FindSetId.end() ) // 如果存在已创建的同名点集，报错
			ErroutPut(false,"%s %s{ %s:%s, %s:%s } [%s|%d|%s]",
				Style("AddSet(string,string)","35","37").c_str(),Style("There already has the set","31","37").c_str(),
				Style("Name","33","37").c_str(),Style(name,"36","37").c_str(),
				Style("Id","33","37").c_str(),Style(FindSetId.find(name)->second,"36","37").c_str(),
				ms.file.c_str(),ms.line,ms.func.c_str()
			);
		if( FindActiveId.find(activeType) == FindActiveId.end() ) // 如果没有叫 actType 的激活函数，报错
			ErroutPut(false,"%s %s{ %s:%s } [%s|%d|%s]",
				Style("AddSet(string,string)","35","37").c_str(),Style("Can't find the activion","31","37").c_str(),
				Style("ActiveName","33","37").c_str(),Style(activeType,"36","37").c_str(),
				ms.file.c_str(),ms.line,ms.func.c_str()
			);
		ErrEnd();
		return AddSet( name, FindActiveId.find(activeType)->second, ms, typ );
	}
	
	/*	@brief
			在指定点集中新建结点
		@param
			SetId 新建结点所属点集编号
		@return
			新建结点在所属点集中的编号 */
	void AddNerve(int SetId,int Times,MESSAGE ms){
		// [AddNerve] todo: 这里使用NerveSets效率更高
		if( SetId >= (int)FindSetId.size() ) // 如果不存在为此编号的点集，报错
			ErroutPut(true,"%s %s{ %s:%s } [%s|%d|%s]",
				Style("AddNerve(int)","35","37").c_str(),Style("Can't find the set","31","37").c_str(),
				Style("SetId","33","37").c_str(),Style(SetId,"36","37").c_str(),
				ms.file.c_str(),ms.line,ms.func.c_str()
			);
		for(int i=0;i<Times;i++) // 向指定编号点集中加入此点
			NerveSets[SetId].Nerves.push_back( NERVE( SetId, NerveSets[SetId].Nerves.size() ) );
		// 报告成功向指定点集中新建结点
		if( Sucput_AddNerve == true )
			SuccessPut("%s{ %s:%s, %s:%s }*%s [%s|%d|%s]",
				Style("AddNerve","34","37").c_str(),
				Style("SetName","33","37").c_str(),Style(NerveSets[SetId].name,"36","37").c_str(),
				Style("NerveMaxId","33","37").c_str(),Style((int)NerveSets[SetId].Nerves.size()-1,"36","37").c_str(),
				Style(Times,"36","37").c_str(),
				ms.file.c_str(),ms.line,ms.func.c_str()
			);
		return ;
	}
	
	/*	@brief
			在指定点集中新建结点
		@param
			SetName 新建结点所在点集名称
		@return
			新建结点在所属点集中的编号 */
	void AddNerve(string SetName,int Times,MESSAGE ms){
		if( FindSetId.find( SetName ) == FindSetId.end() ) // 如果不存在为此名称的点集，报错
			ErroutPut(true,"%s %s{ %s:%s } [%s|%d|%s]",
				Style("AddNerve(string)","35","37").c_str(),Style("Can't find the set","31","37").c_str(),
				Style("SetName","33","37").c_str(),Style(SetName,"36","37").c_str(),
				ms.file.c_str(),ms.line,ms.func.c_str()
			);
		return AddNerve( FindSetId.find( SetName )->second, Times, ms );
	}
	
	/**
	 * 
	 * 
	 * 
	 */
	void ModifyWeight(int SetId,int NerveId,double weight){
		if( SetId >= (int)NerveSets.size() )
			ErroutPut(true,"Can't find the set ModifyWeight()");
		if( NerveId >= (int)NerveSets[SetId].Nerves.size() )
			ErroutPut(true,"Can't find the Nerve ModifyWeight()");
		NerveSets[SetId].Nerves[NerveId].weight = weight;
		// printf("| ModifyWeight SetId:%d NerveId:%d -> weight:%.3lf\n",
		// 	SetId,NerveId,weight);
		// for(TONERVE &Edge:NerveSets[SetId].Nerves[NerveId].outEdgeId)
		// 	printf("\ttoSet:%d toNerve:%d weight:%.3lf\n",Edge.BelongSetId,Edge.id,Edge.weight);
		return ;
	}
	
	/** 
	 * [PrintSet] todo 存储标记点，并可以选择打印指定标记点信息
	 * 
	 * @brief
	 * 		打印指定点集的信息
	 * @param 
	 * 
	 */
	void PrintSet(int SetId){
		if( SetId >= (int)NerveSets.size() ) // todo 可以用把check写成函数，要不然每次都要写一遍
			ErroutPut(true,"Can't find the set PrintSet()");
		printf("\n> SetName:%s SetId:%d\n",NerveSets[SetId].name.c_str(),SetId);
		for(NERVE &nerve:NerveSets[SetId].Nerves){
			printf("\tNerveId:%d weight:%.5lf diff:%5lf\n",nerve.id,nerve.weight,nerve.diff);
			for(TONERVE &Edge:nerve.outEdgeId)
				printf("\t\ttoSet:%d toNerve:%d weight:%.5lf\n",Edge.BelongSetId,Edge.id,Edge.weight);
		}
		puts("");
		return ;
	}
}

#endif
