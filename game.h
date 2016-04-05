#ifndef GAME_H
#define GAME_H

#include "coordinate.h"
#include "macilaci.h"
#include "vador.h"
#include <QMessageBox>
#include <QVector>

enum class objs { ml,vo,pk,fa,cl };

class Game
{
private:

    int size;
    MaciLaci player;
    QVector< QVector<objs> > gametable;



public:
    Game(){}
    Game(int size){
        player = MaciLaci(Coordinate(0,0));
        this->size=size;

        update_gametable();
    }

    void update_gametable(){
        gametable.clear();
        for(int i=0;i<size;++i){
            QVector<objs> line;
            for(int j=0;j<size;++j){
                Coordinate p = Coordinate(i,j);
                if(p.x() == player.get_x() && p.y() == player.get_y()){
                    line.push_back(objs::ml);
                }
                else{
                    line.push_back(objs::cl);
                }
            }
            gametable.push_back(line);
        }
    }

    objs get_gametable_item(int i, int j){
        return gametable.at(i).at(j);
    }

    MaciLaci get_player(){
        return player;
    }
    int get_size(){
        return gametable.size();
    }

    void movePlayer(int d){
        switch(d){
            case 0://UP
                if(player.get_x() != 0){
                    player.set_co(player.get_x()-1,player.get_y());

                }
                break;
            case 1://RIGHT
                if(player.get_y() != size){
                    player.set_co(player.get_x(),player.get_y()+1);
                }
                break;
            case 2://Down
                if(player.get_x() != size){
                    player.set_co(player.get_x()+1,player.get_y());
                }
                break;
            case 3://Left
                if(player.get_y() != 0){
                    player.set_co(player.get_x(),player.get_y()-1);
                }
                break;
        }
        update_gametable();


    }
};

#endif // GAME_H
