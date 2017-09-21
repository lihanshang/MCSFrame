//
//  Participant.h
//  MCSFrame
//
//  Created by Hanshang Li on 12/1/16.
//  Copyright (c) 2016 Hanshang Li. All rights reserved.
//

#include "General.h"

#ifndef MCSFrame_Participant_h
#define MCSFrame_Participant_h


//Basic Classes
////////////////////////////////////////////////////////////////////
// Participant
class Participant{
private:
    int par_id;
    vector<int> loc_set;
    unordered_map<int, double> prob;

public:
    void set_ID(int );
    int get_ID();
    
};

void Participant::set_ID(int a){
    if(a < 0) throw NumberInvalidException();
    par_id = a;
}

int Participant::get_ID(){
    return par_id;
}

//Child class of Participant
class ParticipantA: public Participant{
private:
    double cur_pro;
    double real_pro;
    double cur_delay;
    double cur_exp;
    int real_delay;
    int frequency;
    int success;
    double success_exp;
    int delay;
    int cost;
public:
    
    ParticipantA(){};
    ParticipantA(int, double, int);
    
    
    void setCost(int);
    double getRealPro(){return real_pro;};
    void setRealPro(double p){real_pro = p;};
    
    double getCurPro(){return cur_pro;};
    void setCurPro(double p){cur_pro = p;};
    
    double getCurDelay(){return cur_delay;};
    int getRealDelay(){return real_delay;};
    
    void increaseExp(double exp){success_exp += exp;};
    double getCurExp(){return cur_exp;};
    
    void increaseFreq(){frequency++;};
    int getFreq(){return frequency;};
    
    void increaseSuccess(){success++;};
    int getSuccess(){return success;};
    
    void increaseDelay(int d){delay += d;};
    
    int getDelay(){return delay;};
    
    int getCost(){return cost;};
    
    void update();
};

ParticipantA::ParticipantA(int i, double rpro, int rdl){
    set_ID(i);
    //cur_pro = double(rand() % 100) / 100 / 4;
    cur_pro = 1;
    real_pro = rpro;
    
    //cur_delay = rand() % 24;
    cur_delay = 0;
    real_delay = rdl;
    
    cur_exp = 1;
    
    frequency = 1;
    success = cur_pro * frequency;
    success_exp = 1;
    delay = 0;
    cost = 1;
}



void ParticipantA::setCost(int c){
    cost = c;
}


void ParticipantA::update(){
    frequency++;
    cur_pro = double(success) / frequency;
    cur_delay = double(delay) / frequency;
    cur_exp = double(success_exp) / frequency;
}

//Participant Set
class ParticipantSet{
private:
    int size;
public:
    int getSize();
    
};

int ParticipantSet::getSize(){
    return size;
}

//Child Class of Participant
class ParticipantSetA: public ParticipantSet{
private:
    vector<ParticipantA> par_set;
public:
    ParticipantSetA(){};
    ParticipantSetA(vector<ParticipantA> v_ps){par_set = v_ps;};
    ParticipantA getParticipant(int);
    ParticipantA* getParticiantP(int);
    int getSize();
    
    void readSet();
};

ParticipantA ParticipantSetA::getParticipant(int n){
    return par_set[n];
}

ParticipantA* ParticipantSetA::getParticiantP(int n){
    ParticipantA* res = new ParticipantA();
    res = &par_set[n];
    return res;
}


int ParticipantSetA::getSize(){
    return par_set.size();
}

void ParticipantSetA::readSet(){
    ifstream in("/Users/Harry/Documents/UNCC/MCSFrame/participant250.txt");
    while(!in.eof()){
        int tmp_id, tmp_dly;
        double tmp_pro;
        in >> tmp_id >> tmp_pro >> tmp_dly;
        //cout << tmp_id << " " << tmp_pro << " " << tmp_dly << endl;
        ParticipantA tmp_p(tmp_id, tmp_pro, tmp_dly);
        par_set.push_back(tmp_p);
    }
}


#endif
