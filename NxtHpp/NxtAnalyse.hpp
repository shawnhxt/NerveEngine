#ifndef used_NxtAnylyse
#define used_NxtAnylyse

#include "../HppSet.hpp"

namespace ANALYSE{
    struct RESULTS{
        int BelongSetId, id; // 关联点（todo 关联点只能在输出层）
        double target; // 目标值
        RESULTS(int a,int b,double c){
            BelongSetId = a;
            id = b; target = c;
            return ;
        }
    };
    void CalcDiff();
    void SetTarget(string,int,double,MESSAGE);
    void SetTarget(int,int,double,MESSAGE);

    vector <RESULTS> results;
    map <pair<int,int>,int> FindResultsId;
}

#endif
