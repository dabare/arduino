//
//  path.h
//  meshSolverAlgo
//
//  Created by Madhava Dabare on 2016-03-14.
//  Copyright (c) 2016 Madhava Dabare. All rights reserved.
//


// 0)EOP    1) |    2) |    3)-|-   4) |    5)DESTINATION  6)No_Obstacles
//            -|       |-      |      -|-
//             |       |       |       |
//

#include "junction.h" 

#include <arduino.h>
class path{
private:
    junction* head = NULL;
    junction* tail = NULL;
    junction* tmp = NULL;
    int count  = 0;
    char ctmp = 'n';
    char* c;
    bool rturn = false;
public:
    path();
    void add(bool L,bool U,bool R);
    junction* pop();
    char next_turn();
    char action(int place);
};

path::path(){
    count = 0;
};

void path::add(bool L, bool U, bool R){
    if(count==0){
        head = new junction(L,U,R);
        tail = head;
    }else{
        tmp = new junction(L,U,R);
        tmp->prev = head;
        head->next = tmp;
        head = tmp;
    }
    count+=1;
};

junction* path::pop(){
    if(count>0){
        tmp = head;
        if(count>1){
            head = head->prev;
            head->next = NULL;
            tmp->prev = NULL;
        }
        count-=1;
        return tmp;
    }else{
        return NULL;
    }
}

char path::next_turn(){
    c = head->nextTurn();
    //std::cout <<c[0]; std::cout << ' '; std::cout <<c[1]; std::cout << '\n';
    if(c[0]=='n'){
        ctmp = c[1];
    }else if (c[0]=='u'){
        if (c[1]=='l') {
            ctmp ='r';
        }else if (c[1]=='d'){
            ctmp ='u';
            rturn = true;
            pop();
        }
    }else if (c[0]=='r'){
        if (c[1]=='u') {
            ctmp ='r';
        }else if (c[1]=='l'){
            ctmp ='u';
        }
    }else if (c[0]=='l' && c[1]=='d'){
        ctmp ='r';
        rturn = true;
        pop();
    }
    return ctmp;
}

char path::action(int place){       //R-return u-up l-left r-right p-park
    if(place == 0){
        return 'R';
        rturn = true;
    }else if (place == 1){
        if(rturn){
            return next_turn();
        }else{
            rturn = false;
            add(true, true, false);
            return next_turn();
        }
    }else if (place == 2){
        if(rturn){
            return next_turn();
        }else{
            rturn = false;
            add(false, true, true);
            return next_turn();
        }
    }else if (place == 3){
        if(rturn){
            return next_turn();
        }else{
            rturn = false;
            add(true, false, true);
            return next_turn();
        }
    }else if (place == 4){
        if(rturn){
            return next_turn();
        }else{
            rturn = false;
            add(true, true, true);
            return next_turn();
        }
    }else if (place == 5){
        return 'p';
    }else if(place == 6){
        return 'u';
    }
    return 's';
}
