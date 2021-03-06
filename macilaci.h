#ifndef MACILACI_H
#define MACILACI_H

#include "coordinate.h"

class MaciLaci
{
private:
    Coordinate co;
    int points;
public:
    MaciLaci(){}
    MaciLaci(Coordinate c);

    void set_co(int x,int y){
        co.set_x(x);
        co.set_y(y);
    }
    int get_x(){
        return co.x();
    }
    int get_y(){
        return co.y();
    }
    int get_points(){
        return points;
    }
    void add_point(){
        points+=1;
    }
};

#endif // MACILACI_H
