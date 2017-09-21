//
//  main.cpp
//  MCSFrame
//
//  Created by Hanshang Li on 12/1/16.
//  Copyright (c) 2016 Hanshang Li. All rights reserved.
//

#include <iostream>
#include "General.h"
#include "Task.h"
#include "Participant.h"
#include "Platform.h"
#include "Operation.h"

using namespace std;



int main(int argc, const char * argv[]) {
    // insert code here...
    srand(int(time(0)));
    cout << "Hello, World!\n";
    
    //genParticipantA_step(250);
    
    
    ifstream in("/Users/Harry/Documents/UNCC/MCSFrame/participant50.txt");
    ParticipantSetA p_set;
    p_set.readSet();
    PlatformCMAB pl(p_set);
    PlatformCMAB pl_exp(p_set);
    int round = 1;
    ofstream out("/Users/Harry/Documents/UNCC/MCSFrame/p50.txt");
//    ofstream out_exp("/Users/Harry/Documents/UNCC/MCSFrame/p250_exp_8.txt");
//    
//    ofstream out_learn_all("/Users/Harry/Documents/UNCC/MCSFrame/p250_8_all.txt");
//    ofstream out_learn_one("/Users/Harry/Documents/UNCC/MCSFrame/p250_8_one.txt");
//    
//    ofstream out_exp_learn_all("/Users/Harry/Documents/UNCC/MCSFrame/p250_exp_8_all.txt");
//    ofstream out_exp_learn_one("/Users/Harry/Documents/UNCC/MCSFrame/p250_exp_8_one.txt");
    
    for(int i = 0; i < 500; i++){
        //out << round++ << endl;
        TupleResult result = pl.selectUtility(10);
        TupleResult result_exp = pl_exp.selectUtility_Exp(10);
        
        out << " " << result.real - 0.115 << endl;
        cout << i << " " << result.real - 0.115 << endl;
        
//        out_exp << " " << result_exp.real << endl;
//        cout << i << " " << result_exp.real << endl;
//        
//        out_learn_all << " " << result.expected << endl;
//        cout << i << " " << result.expected << endl;
//        
//        out_exp_learn_all << " " << result_exp.expected << endl;
//        cout << i << " " << result_exp.expected << endl;
//        
//        out_learn_one << " " << pl.getParticipantSet() -> getParticiantP(47) -> getCurPro() * delayFunction(pl.getParticipantSet() -> getParticiantP(47) -> getCurDelay()) << endl;
//        cout << i << " " << pl.getParticipantSet() -> getParticiantP(47) -> getCurPro() * delayFunction(pl.getParticipantSet() -> getParticiantP(47) -> getCurDelay()) << endl;
//        
//        out_exp_learn_one << " " << pl_exp.getParticipantSet() -> getParticiantP(47) -> getCurExp() << endl;
//        cout << i << " " << pl_exp.getParticipantSet() -> getParticiantP(47) -> getCurExp() << endl;
        
        pl.update();
        pl_exp.updateAll();
    }
    
    /*
    ifstream in("/Users/Harry/Documents/UNCC/MCSFrame/participant200.txt");
    ParticipantSetA p_set;
    p_set.readSet();
    PlatformCMAB pl(p_set);
    int round = 1;
    ofstream out("/Users/Harry/Documents/UNCC/MCSFrame/p200_n.txt");
    for(int i = 0; i < 500; i++){
        //out << round++ << endl;
        out << " " << pl.selectUtility_Neg(10) << endl;
        pl.update();
    }
    */
    /*
    ifstream in("/Users/Harry/Documents/UNCC/MCSFrame/participant150.txt");
    ParticipantSetA p_set;
    p_set.readSet();
    PlatformCMAB pl(p_set);
    int round = 1;
    ofstream out("/Users/Harry/Documents/UNCC/MCSFrame/p150_1.txt");
    for(int i = 0; i < 500; i++){
        //cout << round++ << " " << pl.selectUtility(10) << endl;
        //out << round++ << " " << pl.selectUtility(25) << endl;
        out << pl.selectUtility(1) << endl;
        pl.update();
    }
    */
    /*
    ofstream out("/Users/Harry/Documents/UNCC/MCSFrame/random250.txt");
    for(int i = 0; i < 500; i++){
        out << double(rand() % 100) / 100 * (0.868540 - 0.392328) + 0.392328 << endl;

    }
    */
    /*
    ifstream in("/Users/Harry/Documents/UNCC/MCSFrame/participant250.txt");
    ParticipantSetA p_set;
    p_set.readSet();
    PlatformCMAB pl(p_set);
    int round = 1;
    ofstream out("/Users/Harry/Documents/UNCC/MCSFrame/p250_exp_8.txt");
    for(int i = 0; i < 500; i++){
        //out << round++ << endl;
        out << " " << pl.selectUtility_Exp(10) << endl;
        pl.updateAll();
    }
    */
    return 0;
}
