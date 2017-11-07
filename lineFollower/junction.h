//
//  junction.h
//  meshSolverAlgo
//
//  Created by Madhava Dabare on 2016-03-14.
//  Copyright (c) 2016 Madhava Dabare. All rights reserved.
//
#include <arduino.h>
class junction{
private:
    bool l=0,u=0,r=0;
    char turn = 'n';
    char ft[3];
public:
    junction* prev = NULL;
    junction* next = NULL;
    junction(bool L,bool U,bool R);
    char* nextTurn();
};

junction::junction(bool L,bool U,bool R){
    l =L,u=U,r=R;
};

char* junction::nextTurn(){
    ft[0] = turn;
    if(r==true){
        r=false;
        turn = 'r';
        ft[1] = 'r';
    }else if (u == true){
        u = false;
        turn = 'u';
        ft[1] = 'u';
    }else if (l == true){
        l = false;
        turn = 'l';
        ft[1] = 'l';
    }else{
        ft[1] = 'd';
    }
    return ft;
}

