#ifndef VADOR_H
#define VADOR_H

#include "coordinate.h"

class VadOr
{
private:
    Coordinate co;
public:
    VadOr(Coordinate c);

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

};

#endif // VADOR_H
