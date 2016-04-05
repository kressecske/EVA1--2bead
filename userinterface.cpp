#include "userinterface.h"
#include "ui_userinterface.h"
#include <iostream>
UserInterface::UserInterface(QWidget *parent) :
    QWidget(parent)
{
    _game = new Game(5);

    _table = new QGridLayout(this);
    printGameTable();
}

void UserInterface::printGameTable(){
    for(int i=0;i<_game->get_size();++i){
        for(int j=0;j<_game->get_size();++j){
            switch(_game->get_gametable_item(i,j) ) {
                case objs::ml:
                    _item = new QLabel("MaciLaci" + QString::number(_game->get_player().get_x()));
                    break;
                case objs::vo:
                    _item = new QLabel("Vadőr");
                    break;
                case objs::pk:
                    _item = new QLabel("Piknik kosár");
                    break;
                case objs::fa:
                    _item = new QLabel("FA");
                    break;
                case objs::cl:
                    _item = new QLabel("Clear");
                    break;
            }
            _table->addWidget(_item,i,j);
        }
    }
}

void UserInterface::keyPressEvent(QKeyEvent *e){
    if(e->key() == Qt::Key_Up){
        _game->movePlayer(0);
    }
    else if(e->key() == Qt::Key_Right){
        _game->movePlayer(1);
    }
    else if(e->key() == Qt::Key_Down){
        _game->movePlayer(2);
    }
    else if(e->key() == Qt::Key_Left){
        _game->movePlayer(3);
    }
    printGameTable();
}

UserInterface::~UserInterface()
{
}

