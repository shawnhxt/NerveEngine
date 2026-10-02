#ifndef used_RunSpread
#define used_RunSpread

#include "../HppSet.hpp"

using namespace ACTIVE;
using namespace CHECK;
using namespace DEBUG;
using namespace EDGES;
using namespace NERVES;
namespace SPREAD{
	map <simpleTONERVE,int> Map; // 复杂度偏高
//	vector <TONERVE> cnt; // 线性，需要映射TONERVE信息到存在cnt上的编号
	queue <simpleTONERVE> Que;
	void Forward(){
		CheckAnnulation(); // 检查是否为DAG图
		for(int i=0;i<(int)NerveSets.size();i++){ // 遍历图上每一个点，入队
			[](SET &Set,int &kthSet)->void{
				for(int i=0;i<(int)Set.Nerves.size();i++){
					if( Set.Nerves[i].inEdgeId.empty() )
						Que.push({ kthSet, i });
					else Set.Nerves[i].weight = 0.0;
				}
			}(NerveSets[i],i);
		}
        NERVE *nerve, *toNerve;
		while(!Que.empty()){
			SetId = Que.front().BelongSetId;
			NerveId = Que.front().id;
			Que.pop();
			// printf("\t[%d] %d %.3lf\n",SetId,NerveId,NerveSets[SetId].Nerves[NerveId].weight);
			nerve = &NerveSets[SetId].Nerves[NerveId];
			nerve->weight = ActiveWeight(SetId,NerveId); // 结点内最终存的值为已经过激活函数运算的值
			// 广搜，枚举出边
			for(int i=0;i<(int)nerve->outEdgeId.size();i++){
				int ToSetId = nerve->outEdgeId[i].BelongSetId, // todo 太长了，写指针 | have done.
					ToNerveId = nerve->outEdgeId[i].id;
				double EdgeWeight = nerve->outEdgeId[i].weight;
				toNerve = &NerveSets[ToSetId].Nerves[ToNerveId];
				if( ++Map[{ ToSetId, ToNerveId }] == (int)toNerve->inEdgeId.size())
					Que.push({ ToSetId, ToNerveId });
				toNerve->weight += nerve->weight * EdgeWeight;
				// printf("\t\tedge to[%d,%d] weight:%.3lf nowWeight:%.3lf\n",ToSetId,ToNerveId,EdgeWeight,
				// 	NerveSets[ToSetId].Nerves[ToNerveId].weight );
			}
			
		}
		Map.clear();
		// DEBUG::SuccessPut("Forward() Have spread.");
		return ;
	}
}

#endif
