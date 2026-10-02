#ifndef used_NxtNerves
#define used_NxtNerves

#include "../HppSet.hpp"

namespace NERVES{
	// 储存所连边的另一端所指向的点的信息
	struct TONERVE{
		// BelongSetId: 所连边的另一端所指向的点所在的点集
		// id: 连边另一端所指向的点所在其点集的编号
		int BelongSetId, id;
		double weight;
	};
	// 用 map 需要这个来确定元素间的大小关系
	bool operator <(TONERVE A,TONERVE B){
		if( A.BelongSetId != B.BelongSetId )
			return A.BelongSetId < B.BelongSetId;
		return A.id < B.id;
	}
	struct simpleTONERVE{
		int BelongSetId, id;
		simpleTONERVE(int a,int b){
			BelongSetId = a;
			id = b;
			return ;
		}
	};
	bool operator <(simpleTONERVE A,simpleTONERVE B){
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
		double weight; // todo 点权名应叫 value
		double diff; // 误差
		
		vector <TONERVE> inEdgeId; // todo 这个名字不应该有Id呀，应该指的是边的信息（下同）
		vector <int> inEdgeId_outId;

		vector <TONERVE> outEdgeId;
		
		int cnt; // 用于拓扑遍历计数
		NERVE(int bl,int i){
			BelongSetId = bl; id = i;
			cnt = 0; weight = 0.0; diff = 0.0;
			return ;
		}
	};
	
	// ID 0 to siz-1 
	struct SET{
		string name; // 点集名称
		int activeType; // 点集所用激活函数
		vector <NERVE> Nerves; // 点集内每个点的编号及信息
	};
	// NerveSets: 点集的集合
	vector <SET> NerveSets;
	
	// FindSetId: 根据点集名称查找点集编号
	map <string,int> FindSetId; // todo 效率低... 可以用字典树优化
	
	vector <int> InSet; // 入口点集，前向传播用
	vector <int> OutSet; // 出口点集，反向传播用

	int AddSet(string,int,MESSAGE,int);
	int AddSet(string,string,MESSAGE,int);
	void AddNerve(int,int,MESSAGE);
	void AddNerve(string,int,MESSAGE);
}

#endif
