//
//  General.h
//  MCSFrame
//
//  Created by Hanshang Li on 12/1/16.
//  Copyright (c) 2016 Hanshang Li. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <queue>

#include "math.h"

using namespace std;

#ifndef MCSFrame_General_h
#define MCSFrame_General_h

#define MAX_DELAY 24
#define MAX_DELAY_EXP 24

#define DEFAULT_EXP 0.5

//Exceptions
class NumberInvalidException{
public:
    NumberInvalidException();
};
NumberInvalidException::NumberInvalidException(){
    cout << "Input number is valid, check the documents";
}


//Basic functions

double delayFunction(int time){

    if(time >= 24) return 0;
    else return 1 - (double(time) / 24);
}



// Basic classes


//Time Class
class Time{
private:
    int weekday;
    int hour;
    
public:
    Time();
    Time(int , int );
    int getWeekday();
    int getHour();
    void setWeekday(int );
    void setHour(int );
    int toInt();
    
};

Time::Time(){
    
}

Time::Time(int a, int b){
    if(a > 7 || a < 1 || b < 0 || b > 23) throw NumberInvalidException();
    weekday = a;
    weekday = b;
}

int Time::toInt(){
    return (weekday - 1) * 24 + hour;
}

int Time::getWeekday(){
    return weekday;
}

int Time::getHour(){
    return hour;
}

void Time::setWeekday(int a){
    if(a > 7 || a < 1) throw NumberInvalidException();
    else weekday = a;
}

void Time::setHour(int a){
    if(a > 7 || a < 1) throw NumberInvalidException();
    else hour = a;
}

// Tuple result
struct TupleResult{
    double expected;
    double real;
};

//Time Table


//Basic functions



#endif
