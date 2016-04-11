#include "userinterface.h"
#include "ui_userinterface.h"
#include <iostream>
#include <QFileDialog>

UserInterface::UserInterface(QWidget *parent) :
    QWidget(parent)
{
    setWindowTitle(trUtf8("Maci Laci!"));
    _map = "map.txt";
    _game = new Game(_map);
    _mainLayout = new QVBoxLayout(this);

    _points = new QLabel();
    _gameTime = new QLabel();
    _table = new QGridLayout();

    _newGame = new QPushButton();
    _newGame->setText("NewGame");
    _newGame->setFocusPolicy(Qt::NoFocus);
    _chooseMap = new QPushButton();
    _chooseMap->setText("Choose Map File!");
    _chooseMap->setFocusPolicy(Qt::NoFocus);

    _pause = new QPushButton();
    _pause->setText("Pause");
    _pause->setFocusPolicy(Qt::NoFocus);
    _exit = new QPushButton();
    _exit->setText("Exit");
    _exit->setFocusPolicy(Qt::NoFocus);

    connect(_game,SIGNAL(tableChanged()),this,SLOT(printGameTable()));
    connect(_game,SIGNAL(gameOver(bool,int,int)),this,SLOT(Over(bool,int,int)));
    connect(_game,SIGNAL(gameTimeChanged(int)),this,SLOT(gameTimePrint(int)));
    connect(_chooseMap,SIGNAL(clicked()),this,SLOT(chooseMap()));
    connect(_exit,SIGNAL(clicked()),QApplication::instance(),SLOT(quit()));
    connect(_newGame,SIGNAL(clicked()),this,SLOT(newGameButton()));
    connect(_pause, SIGNAL(clicked()), this, SLOT(pauseButton()));

    _menuLayout = new QHBoxLayout();
    _menuLayout->addWidget(_newGame);
    _menuLayout->addWidget(_chooseMap);
    _menuLayout->addWidget(_pause);
    _menuLayout->addWidget(_exit);
    _mainLayout->addLayout(_menuLayout);
    QHBoxLayout *_gamePoints = new QHBoxLayout();
    _gamePoints->addWidget(_points);
    _gamePoints->addWidget(_gameTime);
    _mainLayout->addLayout(_gamePoints);
    _mainLayout->addLayout(_table);

    newGameButton();
}
void UserInterface::chooseMap(){
    QString fn = QFileDialog::getOpenFileName(this,
       tr("Open Map"), "", tr("Map txt Files (*.txt)"));
    if (!fn.isNull()){
        _map=fn;
        newGameButton();
    }

}
void UserInterface::Over(bool b,int p,int t){
    if(b){
        QMessageBox::information(this, trUtf8("Játék vége"),
                                 "Nyertél, összegyűjtötted az összes piknik kosarat\n Pontjaid: " +
                                 QString::number(p)+".\n Időd: " + QString::number(t)+" mp.");
    }else{
        QMessageBox::information(this, trUtf8("Játék vége"),
                                 "Vesztettél, elkapott egy vadőr.\n Pontjaid: " +
                                 QString::number(p) +".\n Időd: " + QString::number(t) + " mp.");
    }
}
void UserInterface::newGameButton(){
    _game->newGame(_map);
    _points->setText("Points: " + QString::number(_game->get_player().get_points()));
    _gameTime->setText("Time: " + QString::number(_game->get_gameTime()));
    _pause->setText("Pause");
    printGameTable();
}
void UserInterface::pauseButton(){
    if(_pause->text() == "Pause"){
        _game->set_pause(true);
        _pause->setText("Unpause");
    }else if(_pause->text() == "Unpause"){
        _game->set_pause(false);
        _pause->setText("Pause");
    }
}
void UserInterface::printGameTable(){

    foreach(QLabel* label, elemnts)
    {
        _table->removeWidget(label);
        delete label;
    }

    elemnts.clear();

    for(int i=0;i<_game->get_size();++i){
        for(int j=0;j<_game->get_size();++j){
            QLabel *_item;
            switch(_game->get_gametable_item(i,j) ) {
                case objs::ml:
                    _item = new QLabel("MaciLaci");
                    break;
                case objs::vo:
                    _item = new QLabel("Vadőr");
                    break;
                case objs::pk:
                    _item = new QLabel("Pkosár");
                    break;
                case objs::fa:
                    _item = new QLabel("FA");
                    break;
                case objs::cl:
                    _item = new QLabel("");
                    break;
            }
            elemnts.append(_item);
            _item->setFixedWidth(40);
            _item->setFixedHeight(40);
            _table->addWidget(_item,i,j);
        }
    }
}
void UserInterface::gameTimePrint(int gt){
    _gameTime->setText("Time: " + QString::number(gt));
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
    _points->setText("Points: " + QString::number(_game->get_player().get_points()));
}

UserInterface::~UserInterface()
{
    delete _game;
}

