//
//  Platform.h
//  MCSFrame
//
//  Created by Hanshang Li on 12/1/16.
//  Copyright (c) 2016 Hanshang Li. All rights reserved.
//

#include "General.h"
#include "Task.h"
#include "Participant.h"
#include "math.h"

#ifndef MCSFrame_Platform_h
#define MCSFrame_Platform_h

struct PUPair{
    int par_id;
    double utility;
    double real_utility;
};

struct cmp {
    bool operator()(PUPair a, PUPair b){
        return a.utility < b.utility;
    }
    
};




//Basic Classes
////////////////////////////////////////////////////////////////////
class Platform{
private:
    int plat_id;  //platform ID for multiple platforms
    
public:
    void setID(int );
    void setParticipant(ParticipantSet);
    
};


void Platform::setID(int a){
    plat_id = a;
}



//Child Classes of Platform
////////////////////////////////////////////////////////////////////

class PlatformCMAB : public Platform{
private:
    int cur_time;
    TaskSetA t_set;
    ParticipantSetA p_set;
    vector<int> cur_selected;
public:
    PlatformCMAB();
    PlatformCMAB(ParticipantSetA);
    PlatformCMAB(TaskSetA, ParticipantSetA);
    void setTime(Time);
    Time getTime();
    double getParticipantPro(int);
    double getParticipantProReal(int);
    int getParticipantDelay(int);
    int getParticipantDelayReal(int);
    void select(int);
    TupleResult selectUtility(int);
    TupleResult selectUtility_Neg(int);
    TupleResult selectUtility_Exp(int);
    
    void update();
    void updateAll();
    
    ParticipantSetA* getParticipantSet();
    
    int getParticipantFreq(int n){return p_set.getParticipant(n).getFreq();};
    
    
};

PlatformCMAB::PlatformCMAB(){
    
}

PlatformCMAB::PlatformCMAB(ParticipantSetA ps){
    cur_time = 250;
    p_set = ps;
}

PlatformCMAB::PlatformCMAB(TaskSetA ts, ParticipantSetA ps){
    cur_time = 250;
    t_set = ts;
    p_set = ps;
}

/*
void PlatformCMAB::setTime(Time t){
    cur_time = t;
}

Time PlatformCMAB::getTime(){
    return cur_time;
}
*/
double PlatformCMAB::getParticipantProReal(int n){
    return p_set.getParticipant(n).getRealPro();
}

double PlatformCMAB::getParticipantPro(int n){
    return p_set.getParticipant(n).getCurPro();
}

int PlatformCMAB::getParticipantDelayReal(int n){
    return p_set.getParticipant(n).getRealDelay();
}

int PlatformCMAB::getParticipantDelay(int n){
    return p_set.getParticipant(n).getCurDelay();
}


ParticipantSetA* PlatformCMAB::getParticipantSet(){
    ParticipantSetA* res = &p_set;
    return res;
}


void PlatformCMAB::select(int m){
    double exp_ut = 1;
    double real_ut = 1;
    priority_queue<PUPair, vector<PUPair>, cmp> pair_que;
    int n = p_set.getSize();
    for(int i = 0; i < n; i++){
        PUPair pair;
        ParticipantA tmp_p = p_set.getParticipant(i);
        pair.par_id = tmp_p.get_ID();
        
        //cout << tmp_p.getCurPro() * delayFunction(tmp_p.getCurDelay()) << " " << sqrt(3 * log(double(cur_time)) / 2 / tmp_p.getFreq()) << endl;
        pair.real_utility = tmp_p.getCurPro() * delayFunction(tmp_p.getCurDelay());
        double ut = pair.real_utility + sqrt(3 * log(double(cur_time)) / 2 / tmp_p.getFreq());
        
        
        if(ut > 1) ut = 1;
        int cost = tmp_p.getCost();
        pair.utility = ut / cost;
        pair.real_utility /= cost;
        //cout << pair.utility << endl;
        
        pair_que.push(pair);
    }
    for(int i = 0; i < m; i++){
        if(!pair_que.empty()){
            int tmp_id = pair_que.top().par_id;
            //cout << pair_que.top().utility << endl;
            exp_ut *= 1 - pair_que.top().utility;
            real_ut *= 1 - pair_que.top().real_utility;
            cur_selected.push_back(tmp_id);
            pair_que.pop();
        }
        
    }
    //cout << "Expected utility is " << 1 - exp_ut << endl;
    cout << cur_time << " " << "Real expected utility is " << 1 - real_ut << endl;
}

//Select Utility with fix value
TupleResult PlatformCMAB::selectUtility(int m){
    TupleResult result;
    double exp_ut = 1;
    double real_ut = 1;
    priority_queue<PUPair, vector<PUPair>, cmp> pair_que;
    int n = p_set.getSize();
    for(int i = 0; i < n; i++){
        PUPair pair;
        ParticipantA tmp_p = p_set.getParticipant(i);
        pair.par_id = tmp_p.get_ID();
        
        //cout << tmp_p.getCurPro() * delayFunction(tmp_p.getCurDelay()) << " " << sqrt(3 * log(double(cur_time)) / 2 / tmp_p.getFreq()) << endl;
        pair.real_utility = tmp_p.getCurPro() * delayFunction(tmp_p.getCurDelay());
        //cout << tmp_p.getCurDelay() << endl;
        //cout << sqrt(3 * log(double(cur_time)) / 2 / tmp_p.getFreq()) << endl;
        double ut = pair.real_utility + sqrt(3 * log(double(cur_time)) / 2 / tmp_p.getFreq());
        ut = pair.real_utility;
        
        if(ut > 1) ut = 1;
        int cost = tmp_p.getCost();
        pair.utility = ut / cost;
        //pair.real_utility /= cost;
        
        //Here is using real utility
        pair.real_utility = tmp_p.getRealPro() * delayFunction(tmp_p.getRealDelay());
//        cout << endl << " " << tmp_p.getRealPro() << " " << tmp_p.getRealDelay();
//        cout << endl << pair.par_id << " "  << pair.real_utility << endl;
//        cout << pair.par_id << " " << pair.utility << endl;
        
        pair_que.push(pair);
    }
    for(int i = 0; i < m; i++){
        if(!pair_que.empty()){
            int tmp_id = pair_que.top().par_id;
            //cout << pair_que.top().par_id << " " << pair_que.top().utility << " " << pair_que.top().real_utility << endl;
            //cout << tmp_id << " ";
            //cout << pair_que.top().utility << endl;
            exp_ut *= 1 - pair_que.top().utility;
            real_ut *= 1 - pair_que.top().real_utility;
            cur_selected.push_back(tmp_id);
            //cout << endl << tmp_id << " " << pair_que.top().real_utility << " ";
            pair_que.pop();
            
        }
        
    }
//    for(int i = 0; i < cur_selected.size(); i++) cout << cur_selected[i] << " ";
    //cout << "Expected utility is " << 1 - exp_ut << endl;
    
    result.expected = 1 - exp_ut;
    result.real = 1 - real_ut;
    
    return result;
}

//Select Utility without fix value
TupleResult PlatformCMAB::selectUtility_Neg(int m){
    TupleResult result;
    double exp_ut = 1.0;
    double real_ut = 1.0;
    priority_queue<PUPair, vector<PUPair>, cmp> pair_que;
    int n = p_set.getSize();
    for(int i = 0; i < n; i++){
        PUPair pair;
        ParticipantA tmp_p = p_set.getParticipant(i);
        pair.par_id = tmp_p.get_ID();
        
        //cout << tmp_p.getCurPro() * delayFunction(tmp_p.getCurDelay()) << " " << sqrt(3 * log(double(cur_time)) / 2 / tmp_p.getFreq()) << endl;
        pair.real_utility = tmp_p.getCurPro() * delayFunction(tmp_p.getCurDelay());
        double ut = pair.real_utility;
        //cout << ut << " ";
        
        if(ut > 1) ut = 1;
        int cost = tmp_p.getCost();
        pair.utility = ut / cost;
        pair.real_utility /= cost;
        //cout << pair.utility << endl;
        
        pair.real_utility = tmp_p.getRealPro() * delayFunction(tmp_p.getRealDelay());
        
        pair_que.push(pair);
    }
    for(int i = 0; i < m; i++){
        if(!pair_que.empty()){
            int tmp_id = pair_que.top().par_id;
            //cout << pair_que.top().utility << endl;
            exp_ut *= 1 - pair_que.top().utility;
            //cout << pair_que.top().real_utility << " ";
            //cout << endl;
            real_ut *= 1 - pair_que.top().real_utility;
            //cout << real_ut << endl;
            cur_selected.push_back(tmp_id);
            pair_que.pop();
        }
        
    }
    //for(int i = 0; i < cur_selected.size(); i++) cout << cur_selected[i] << " ";
    //cout << "Expected utility is " << 1 - exp_ut << endl;
    result.expected = 1 - exp_ut;
    result.real = 1 - real_ut;
    
    return result;
}

//Select Utility with EXP
TupleResult PlatformCMAB::selectUtility_Exp(int m){
    TupleResult result;
    double exp_ut = 1;
    double real_ut = 1;
    priority_queue<PUPair, vector<PUPair>, cmp> pair_que;
    int n = p_set.getSize();
    for(int i = 0; i < n; i++){
        PUPair pair;
        ParticipantA tmp_p = p_set.getParticipant(i);
        pair.par_id = tmp_p.get_ID();
        
        //cout << tmp_p.getCurPro() * delayFunction(tmp_p.getCurDelay()) << " " << sqrt(3 * log(double(cur_time)) / 2 / tmp_p.getFreq()) << endl;
        pair.real_utility = tmp_p.getCurExp();
        double ut = pair.real_utility;
        
        
        if(ut > 1) ut = 1;
        int cost = tmp_p.getCost();
        pair.utility = ut / cost;
        pair.real_utility /= cost;
        //cout << pair.utility << endl;
        
        pair.real_utility = tmp_p.getRealPro() * delayFunction(tmp_p.getRealDelay());
        //pair.real_utility = tmp_p.getRealPro() * (1 - tmp_p.getRealPro());
        
        pair_que.push(pair);
    }
    for(int i = 0; i < m; i++){
        if(!pair_que.empty()){
            int tmp_id = pair_que.top().par_id;
            //cout << pair_que.top().par_id << " " << pair_que.top().utility << " " << pair_que.top().real_utility << endl;
            exp_ut *= 1 - pair_que.top().utility;
            real_ut *= 1 - pair_que.top().real_utility;
            cur_selected.push_back(tmp_id);
            pair_que.pop();
        }
        
    }
    //for(int i = 0; i < cur_selected.size(); i++) cout << cur_selected[i] << " " <<  ;
    //cout << "Expected utility is " << 1 - exp_ut << endl;
    
    result.expected = 1 - exp_ut;
    result.real = 1 - real_ut;
    
    return result;
}


void PlatformCMAB::update(){
    
    cur_time++;
    double ut = 1;
    int n = cur_selected.size();
    ParticipantSetA* par_set = getParticipantSet();
    vector<double> utility;
    for(int i = 0; i < n; i++){
        int cur_par = cur_selected[i];
        ParticipantA* par = par_set -> getParticiantP(cur_par);
        
        //Upadate Probability
        double cur_pro_real = getParticipantProReal(cur_par);
        double cur_pro = getParticipantPro(cur_par);
        bool visit = (double(rand() % 100) / 100) > cur_pro_real ? false : true;
        if(visit) par -> increaseSuccess();
        
        //Update Delay
        int cur_delay_real = getParticipantDelayReal(cur_par);
//        int delay = cur_delay_real == 0? 0 : (rand() % 2 == 0? (cur_delay_real - rand() % cur_delay_real) : (cur_delay_real + rand() % cur_delay_real));
        int delay = cur_delay_real == 0? 0 : (rand() % 2 == 0? (cur_delay_real - 1) : (cur_delay_real + 1));

        double delayf = delayFunction(delay);
        par -> increaseDelay(delay);
        //if(visit && delay < MAX_DELAY_EXP) par -> increaseDelay(delay);
        //else if(visit && delay >= MAX_DELAY_EXP) par -> increaseDelay(MAX_DELAY_EXP);
        
        par -> update();
        
        utility.push_back(visit * delayf);
        ut *= (1 - utility.back());
        
    }
    cur_selected.clear();
    //cout << "Current Utility is " << 1 - ut << endl;
}


void PlatformCMAB::updateAll(){
    cur_time++;
    double ut = 1;
    int n = cur_selected.size();
    ParticipantSetA* par_set = getParticipantSet();
    vector<double> utility;
    for(int i = 0; i < n; i++){
        int cur_par = cur_selected[i];
        ParticipantA* par = par_set -> getParticiantP(cur_par);
        
        //Upadate Probability
        double cur_pro_real = getParticipantProReal(cur_par);
        double cur_pro = getParticipantPro(cur_par);
        bool visit = (double(rand() % 100) / 100) > cur_pro_real ? false : true;
        //if(visit) par -> increaseSuccess();
    
        //Update Delay
        int cur_delay_real = getParticipantDelayReal(cur_par);
//        int delay = cur_delay_real == 0? 0 : (rand() % 2 == 0? (cur_delay_real - rand() % cur_delay_real) : (cur_delay_real + rand() % cur_delay_real));
        int delay = cur_delay_real == 0? 0 : (rand() % 2 == 0? (cur_delay_real - 1) : (cur_delay_real + 1));
        
        //if(delay >= 12) cout << delay << endl;
        
        if (visit && delay < MAX_DELAY_EXP) par -> increaseExp(delayFunction(delay));
        
        par -> update();
        //utility.push_back(visit * delayf);
        //ut *= (1 - utility.back());
        
    }
}



#endif
