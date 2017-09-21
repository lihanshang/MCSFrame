//
//  Task.h
//  MCSFrame
//
//  Created by Hanshang Li on 12/1/16.
//  Copyright (c) 2016 Hanshang Li. All rights reserved.
//

#include "General.h"



#ifndef MCSFrame_Task_h
#define MCSFrame_Task_h




//Basic Classes
////////////////////////////////////////////////////////////////////

// Task Class
class Task{
private:
    int task_id;
    Time time;
    int loc;
    bool assigned;
    bool completed;
public:
    
    Task();
    int getID();
    Time getTime();
    int getLoc();
    
    void setID(int );
    void setTime(Time );
    void setLoc(int );
    void setAssign(bool);
    void setComp(bool);
    
};

Task::Task(){
    
}

int Task::getID(){
    return task_id;
}

Time Task::getTime(){
    return time;
}

int Task::getLoc(){
    return loc;
}

void Task::setID(int a){
    task_id = a;
}

void Task::setTime(Time a){
    time = a;
}

void Task::setLoc(int a){
    loc = a;
}

void Task::setAssign(bool as){
    assigned = as;
}

void Task::setComp(bool com){
    completed = com;
}



//Child Classes
////////////////////////////////////////////////////////////////////

class Task_A:public Task{
private:
    bool tag;
public:
    bool getTag();
    Task_A();
    Task_A(int, Time, int, bool, bool, bool);
};
Task_A :: Task_A(){
    
}

Task_A :: Task_A(int a, Time t, int l, bool d, bool e, bool tag){
    setID(a);
    setTime(t);
    setLoc(l);
    
}

//TaskSet Class

class TaskSet{
private:
    int size;
    unordered_map<int, int> taskmap;
public:
    TaskSet();
    int getSize();
    void sizePlus(int a);
    
};

TaskSet::TaskSet(){
    size = 0;
}


int TaskSet::getSize(){
    return size;
}

void TaskSet::sizePlus(int a){
    size += a;
}



//TaskSetA Class
class TaskSetA: public TaskSet{
private:
    int size;
    vector<Task_A> taskset;
public:
    //TaskSetA();
    void push(Task_A);
    TaskSetA();
    TaskSetA(vector<Task_A> );
};

TaskSetA::TaskSetA(){
    
}

TaskSetA::TaskSetA(vector<Task_A> v){
    size = v.size();
    taskset = v;
}


void TaskSetA::push(Task_A a){
    taskset.push_back(a);
    size++;
}



#endif
