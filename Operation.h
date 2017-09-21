//
//  Operation.h
//  MCSFrame
//
//  Created by Hanshang Li on 3/3/17.
//  Copyright (c) 2017 Hanshang Li. All rights reserved.
//

#include <iostream>
#include "General.h"
#include "Task.h"
#include "Participant.h"
#include "Platform.h"

#ifndef MCSFrame_Operation_h
#define MCSFrame_Operation_h


//Generate participant
void genParticipantA(int n){
    ofstream out("/Users/Harry/Documents/UNCC/MCSFrame/participant.txt");
    for(int i = 0; i < n; i ++){
        double tmp_rpro = double(rand() % 100) / 100 / 4;
        int tmp_rdl = rand() % 24;
        ParticipantA tmp_p(i, tmp_rpro, tmp_rdl);
        
        out << i << " " << tmp_rpro << " " << tmp_rdl << endl;
        //cout << i << " " << tmp_rpro << " " << tmp_rdl << endl;
    }
    
}

void genParticipantA_step(int n){
    ofstream out("/Users/Harry/Documents/UNCC/MCSFrame/participant50.txt");
    ofstream out_1("/Users/Harry/Documents/UNCC/MCSFrame/participant100.txt");
    ofstream out_2("/Users/Harry/Documents/UNCC/MCSFrame/participant150.txt");
    ofstream out_3("/Users/Harry/Documents/UNCC/MCSFrame/participant200.txt");
    ofstream out_4("/Users/Harry/Documents/UNCC/MCSFrame/participant250.txt");
    for(int i = 0; i < n; i ++){
        double tmp_rpro = double(rand() % 100) / 100 / 4;
        int tmp_rdl = rand() % 24;
        if(tmp_rpro > 0.2) tmp_rdl = rand() % 1 + 12;
        ParticipantA tmp_p(i, tmp_rpro, tmp_rdl);
        
        if(i < 50){
            out << i << " " << tmp_rpro << " " << tmp_rdl << endl;
            out_1 << i << " " << tmp_rpro << " " << tmp_rdl << endl;
            out_2 << i << " " << tmp_rpro << " " << tmp_rdl << endl;
            out_3 << i << " " << tmp_rpro << " " << tmp_rdl << endl;
            out_4 << i << " " << tmp_rpro << " " << tmp_rdl << endl;
        }
        else if(i < 100){
            out_1 << i << " " << tmp_rpro << " " << tmp_rdl << endl;
            out_2 << i << " " << tmp_rpro << " " << tmp_rdl << endl;
            out_3 << i << " " << tmp_rpro << " " << tmp_rdl << endl;
            out_4 << i << " " << tmp_rpro << " " << tmp_rdl << endl;
        }
        else if(i < 150){
            out_2 << i << " " << tmp_rpro << " " << tmp_rdl << endl;
            out_3 << i << " " << tmp_rpro << " " << tmp_rdl << endl;
            out_4 << i << " " << tmp_rpro << " " << tmp_rdl << endl;
        }
        else if(i < 200){
            out_3 << i << " " << tmp_rpro << " " << tmp_rdl << endl;
            out_4 << i << " " << tmp_rpro << " " << tmp_rdl << endl;
        }
        else{
            out_4 << i << " " << tmp_rpro << " " << tmp_rdl << endl;
        }
        //out << i << " " << tmp_rpro << " " << tmp_rdl << endl;
        //cout << i << " " << tmp_rpro << " " << tmp_rdl << endl;
    }
}


#endif
