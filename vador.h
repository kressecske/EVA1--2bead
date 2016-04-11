#ifndef VADOR_H
#define VADOR_H

#include "coordinate.h"
#include <QTimer>
#include <QTime>
#include <QTimerEvent>

class VadOr
{
private:
    Coordinate co;
    int direction;
    QTimer *_timer;

public:
    VadOr(Coordinate c,int d);

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
    int get_d(){
        return direction;
    }
    void set_d(int d){
        direction = d;
    }

};

#endif // VADOR_H
