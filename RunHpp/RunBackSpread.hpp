#ifndef used_RunBackSpread
#define used_RunBackSpread

#include "../HppSet.hpp"

namespace BACKSPREAD{
    const double SPEED = 0.5;
    void Backward(){
        CheckAnnulation();
        queue <simpleTONERVE> Que;
        for(int OutSetId:OutSet){
            for(int i=0;i<(int)NerveSets[OutSetId].Nerves.size();i++)
                Que.push(simpleTONERVE(OutSetId,i));
        }
        // printf(">>> OutSet size: %d\n",(int)InSet.size());
        // printf(">>> Que size: %d\n",(int)Que.size());
        NERVE *nerve, *toNerve;
        while(!Que.empty()){
            int SetId = Que.front().BelongSetId;
            int NerveId = Que.front().id;
            Que.pop();
            nerve = &NerveSets[SetId].Nerves[NerveId];
            // printf("\n>>> [SetId:%s,NerveId:%d] \n",NerveSets[SetId].name.c_str(),NerveId);
            for(int i=0;i<(int)nerve->inEdgeId.size();i++){ // 遍历反边
                int ToSetId = nerve->inEdgeId[i].BelongSetId;
                int ToNerveId = nerve->inEdgeId[i].id;
                int EdgeId = nerve->inEdgeId_outId[i];
                toNerve = &NerveSets[ ToSetId ].Nerves[ ToNerveId ];

                double diff = nerve->diff
                            * dActiveWeight( NerveSets[ SetId ].activeType , nerve->weight )
                            * toNerve->weight;
                
                toNerve->diff += nerve->diff
                            * dActiveWeight( NerveSets[ SetId ].activeType , nerve->weight )
                            * toNerve->outEdgeId[ EdgeId ].weight;

                toNerve->outEdgeId[ EdgeId ].weight -= diff * SPEED; //!!!
                
//                 printf("\t|+| [ToSetId:%s,ToNerveId:%d]\n\
// \t\t |-| nerve->diff:%.5lf\n\
// \t\t |-| dActiveWeight:%.5lf\n\
// \t\t |-| toNerve->weight:%.5lf\n\
// \t\t [x] diff:%.5lf\n\
// \t\t [x] toNerve->EdgeWeight:%.5lf\n",
//                     NerveSets[ToSetId].name.c_str(),ToNerveId,
//                     nerve->diff,
//                     dActiveWeight( NerveSets[ SetId ].activeType , nerve->weight ),
//                     toNerve->weight,
//                     diff,
//                     toNerve->outEdgeId[ EdgeId ].weight
//                 );

                toNerve->cnt++;
                if( toNerve->cnt == (int)toNerve->outEdgeId.size() ){
                    Que.push(simpleTONERVE(toNerve->BelongSetId,toNerve->id));
                }
            }
            nerve->cnt = 0;
        }
        return ;
    }

}

#endif