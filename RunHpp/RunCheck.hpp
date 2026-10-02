#ifndef used_RunCheck
#define used_RunCheck

#include "../HppSet.hpp"

namespace CHECK{
    // 深搜检查是否存在环
    void dfs(TONERVE sNerve){
        if( vist.find(sNerve) != vist.end() )
            return ;
        vist.insert(sNerve);

        inque.insert(sNerve);
        for(TONERVE &tNerve:NerveSets[sNerve.BelongSetId].Nerves[sNerve.id].inEdgeId){
            if( inque.find(tNerve) != inque.end() )
                DEBUG::ErroutPut(false,"Check() { sBelongSet:%s, sNerveId:%d } -> { tBelongSet:%s, tNerveId:%d } will make the Nerve graph have annulation.",
					NerveSets[ sNerve.BelongSetId ].name.c_str(),sNerve.id,NerveSets[ tNerve.BelongSetId ].name.c_str(),tNerve.id);
            else dfs(tNerve);
        }
        inque.erase(sNerve);
        return ;
    }
    void CheckAnnulation(){
        for(int i=0;i<(int)NerveSets.size();i++){
            [](SET &Set)->void{
                for(int i=0;i<(int)Set.Nerves.size();i++)
                    dfs({ Set.Nerves[i].BelongSetId , Set.Nerves[i].id });
            }(NerveSets[i]);
        }
		vist.clear();
        DEBUG::ErrEnd();
		// DEBUG::SuccessPut("CheckAnnulation() The Nerve grapth have not annulation.");
    }
}

#endif
