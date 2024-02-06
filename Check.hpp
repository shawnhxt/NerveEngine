#ifndef used_Check
#define used_Check

#include <iostream>
#include <stdio.h>

#include "Debug.hpp"
#include "Nerves.hpp"

#include <set>

namespace CHECK{
    using namespace NERVES;
    std::set <TONERVE> vist,inque;
    // 深搜检查是否存在环
    void dfs(TONERVE sNerve)
    {
        if( vist.find(sNerve) != vist.end() )
            return ;
        vist.insert(sNerve);

        inque.insert(sNerve);
        for(TONERVE tNerve:NerveSets[sNerve.BelongSetId].Nerves[sNerve.id].inEdgeId)
        {
            if( inque.find(tNerve) != inque.end() )
                DEBUG::ErroutPut(false,"In CHECK::check() Edge:{ sBelongSet:%s , sNerveId:%d } -> { tBelongSet:%s , tNerveId:%d } will make the Nerve graph become annulated",NERVES::FindSetName[ sNerve.BelongSetId ].c_str(),sNerve.id,NERVES::FindSetName[ tNerve.BelongSetId ].c_str(),tNerve.id);
            else dfs(tNerve);
        }
        inque.erase(sNerve);
        return ;
    }
    void check()
    {
        vist.clear();
        for(int i=0;i<NerveSets.size();i++)
        {
            [](SET &Set)->void{
                for(int i=0;i<Set.Nerves.size();i++)
                    dfs({ Set.Nerves[i].BelongSetId , Set.Nerves[i].id } );
            }(NerveSets[i]);
        }
        DEBUG::ErrEnd();
    }
}

#endif