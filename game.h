#ifndef GAME_H
#define GAME_H

#include "coordinate.h"
#include "macilaci.h"
#include "vador.h"
#include <QMessageBox>
#include <QVector>
#include <QTime>
#include <QString>
#include <QObject>
#include <QTimer>
#include <QFile>
#include <QTextStream>
enum objs { ml,vo,pk,fa,cl };

class Game : public QObject
{
    Q_OBJECT
private:

    int size;
    MaciLaci player;
    QVector <VadOr*> vadorok;
    QVector <Coordinate> fak;
    QVector <Coordinate*> piknikkosarak;
    QVector< QVector<objs> > gametable;
    QTimer *_timer;
    bool end;
    bool pause;
    int gameTime;
    QTimer *_gameTimer;
signals:
    void gameOver(bool,int,int);
    void tableChanged();
    void gameTimeChanged(int);
public slots:
    void moveVador(){

        if(end || pause) return;
        foreach(VadOr* vador, vadorok){
            int d = vador->get_d();
            switch(d){
                case 0://UP
                    if(vador->get_x() != 0){
                        if(!is_next_fa(vador->get_x(),vador->get_y(),0))
                            {vador->set_co(vador->get_x()-1,vador->get_y());}
                        else {vador->set_d(2);
                                vador->set_co(vador->get_x()+1,vador->get_y());}
                    }else{ vador->set_d(2);
                            vador->set_co(vador->get_x()+1,vador->get_y());}
                    break;
                case 1://RIGHT
                    if(vador->get_y() != size-1){
                        if(!is_next_fa(vador->get_x(),vador->get_y(),1))
                            {vador->set_co(vador->get_x(),vador->get_y()+1);}
                        else {vador->set_d(3);
                            vador->set_co(vador->get_x(),vador->get_y()-1);}
                    }else {vador->set_d(3);
                            vador->set_co(vador->get_x(),vador->get_y()-1);}
                    break;
                case 2://Down
                    if(vador->get_x() != size-1){
                        if(!is_next_fa(vador->get_x(),vador->get_y(),2))
                            {vador->set_co(vador->get_x()+1,vador->get_y());}
                        else{ vador->set_d(0);
                            vador->set_co(vador->get_x()-1,vador->get_y());
                        }
                    }else {vador->set_d(0);
                            vador->set_co(vador->get_x()-1,vador->get_y());
                    }
                    break;
                case 3://Left
                    if(vador->get_y() != 0){
                        if(!is_next_fa(vador->get_x(),vador->get_y(),3))
                            {vador->set_co(vador->get_x(),vador->get_y()-1);}
                        else {
                            vador->set_d(1);
                            vador->set_co(vador->get_x(),vador->get_y()+1);
                            }
                    }else {vador->set_d(1);vador->set_co(vador->get_x(),vador->get_y()+1);}
                    break;
            }
            update_gametable();
        }
        check_game_end();
    }
    void addGameTime(){
        gameTime++;
        emit gameTimeChanged(gameTime);
    }
public:
    Game(QString loc){
        _timer = new QTimer();
        _gameTimer = new QTimer();
        _timer->setInterval(750);
        _gameTimer->setInterval(1000);
        connect(_timer, SIGNAL(timeout()), this, SLOT(moveVador()));
        connect(_gameTimer, SIGNAL(timeout()), this, SLOT(addGameTime()));
        newGame(loc);

    }
    ~Game(){
        foreach(VadOr* v, vadorok){
            delete v;
        }
        vadorok.clear();
        foreach(Coordinate* c, piknikkosarak){
            delete c;
        }
        piknikkosarak.clear();
    }
    void newGame(QString loc){
        if (_timer->isActive())
            _timer->stop(); // időzítő leáll

        foreach(VadOr* v, vadorok){
            delete v;
        }
        vadorok.clear();
        foreach(Coordinate* c, piknikkosarak){
            delete c;
        }
        fak.clear();
        piknikkosarak.clear();
        gametable.clear();
        gameTime = 0;

        QFile file(loc);
        if(!file.open(QIODevice::ReadOnly)) {
            QMessageBox::information(0, "error", file.errorString());
        }else{
            QTextStream in(&file);


            QString line = in.readLine(); //Méret beolvasás
            this->size = line.toInt();

            line = in.readLine();
            QStringList cords = line.split("\t");    //Maci Laci beolvasás
            player = MaciLaci(Coordinate(cords[0].toInt(),cords[1].toInt()));

            line = in.readLine();
            int n = line.toInt();
            line = in.readLine();
            for(int i=0;i<n;i++){
                QStringList cords = line.split("\t");    //Fák coordinátáinak beolvasás
                fak.append(Coordinate(cords[0].toInt(),cords[1].toInt()));
                line = in.readLine();
            }
            n = line.toInt();
            line = in.readLine();
            for(int i=0;i<n;i++){
                QStringList cords = line.split("\t");    //Vadőrők beolvasás
                vadorok.append(new VadOr(Coordinate(cords[0].toInt(),cords[1].toInt()),cords[2].toInt()));
                line = in.readLine();
            }
            n = line.toInt();
            line = in.readLine();
            for(int i=0;i<n;i++){
                QStringList cords = line.split("\t");    //Piknikkosarak beolvasás
                piknikkosarak.append(new Coordinate(cords[0].toInt(),cords[1].toInt()));
                line = in.readLine();
            }
            end = false;
            pause = false;
            _timer->start();
            _gameTimer->start();
            update_gametable();

        }




    }



    void set_end(bool e){
        end = e;
    }
    void set_pause(bool p){
        if(end) return;
        if(p){
            _timer->stop();
            _gameTimer->stop();
        }else{
            _timer->start();
            _gameTimer->start();
        }
        pause = p;
    }


    void update_gametable(){
        if(end || pause) return;
        gametable.clear();
        for(int i=0;i<size;++i){
            QVector<objs> line;
            for(int j=0;j<size;++j){
                Coordinate p = Coordinate(i,j);
                bool done = false;
                if(p.x() == player.get_x() && p.y() == player.get_y() && !done){
                    line.push_back(objs::ml);
                    done = true;
                }
                foreach(Coordinate fa, fak)
                {
                    if(fa.x() == p.x() && fa.y() == p.y() && !done){
                        line.push_back(objs::fa);
                        done = true;
                    }
                }
                foreach(VadOr *vador, vadorok)
                {
                    if(vador->get_x() == p.x() && vador->get_y() == p.y() && !done){
                        line.push_back(objs::vo);
                        done = true;
                    }
                }
                foreach(Coordinate *kosar, piknikkosarak)
                {
                    if(kosar->x() == p.x() && kosar->y() == p.y() && !done){
                        line.push_back(objs::pk);
                        done = true;
                    }
                }
                if(!done){
                    line.push_back(objs::cl);
                }
            }
            gametable.push_back(line);
        }
        emit tableChanged();
    }

    objs get_gametable_item(int i, int j){
        return gametable.at(i).at(j);
    }

    MaciLaci get_player(){
        return player;
    }
    QVector<VadOr*> get_vadors(){
        return vadorok;
    }

    int get_size(){
        return gametable.size();
    }
    bool get_pause(){
        return pause;
    }
    bool get_end(){
        return end;
    }
    int get_gameTime(){
        return gameTime;
    }
    bool is_next_fa(int x,int y,int d){
        switch(d){
            case 0: //UP
                foreach(Coordinate fa, fak)
                {
                    if(fa.x() == x-1 && fa.y() == y){
                        return true;
                    }
                }
            break;
            case 1: //RIGHT
                foreach(Coordinate fa, fak)
                {
                    if(fa.x() == x && fa.y() == y+1){
                        return true;
                    }
                }
            break;
            case 2: //DOWN
                foreach(Coordinate fa, fak)
                {
                    if(fa.x() == x+1 && fa.y() == y){
                        return true;
                    }
                }
            break;
            case 3: //LEFT
                foreach(Coordinate fa, fak)
                {
                    if(fa.x() == x && fa.y() == y-1){
                        return true;
                    }
                }
            break;
        }
        return false;
    }
    void is_on_kosar(int x,int y){
        foreach(Coordinate* kosar, piknikkosarak)
        {
            if(kosar->x() == x && kosar->y() == y){
                player.add_point();
                piknikkosarak.removeOne(kosar);
                delete kosar;
            }
        }
    }

    void movePlayer(int d){
        if(end || pause) return;
        switch(d){
            case 0://UP
                if(player.get_x() != 0){
                    if(!is_next_fa(player.get_x(),player.get_y(),0))
                    {
                        player.set_co(player.get_x()-1,player.get_y());
                    }

                }
                break;
            case 1://RIGHT
                if(player.get_y() != size-1){
                    if(!is_next_fa(player.get_x(),player.get_y(),1))
                    {
                        player.set_co(player.get_x(),player.get_y()+1);
                    }
                }
                break;
            case 2://Down
                if(player.get_x() != size-1){
                    if(!is_next_fa(player.get_x(),player.get_y(),2))
                    {
                        player.set_co(player.get_x()+1,player.get_y());
                    }
                }
                break;
            case 3://Left
                if(player.get_y() != 0){
                    if(!is_next_fa(player.get_x(),player.get_y(),3))
                    {
                        player.set_co(player.get_x(),player.get_y()-1);
                    }
                }
                break;
        }
        is_on_kosar(player.get_x(),player.get_y());
        update_gametable();
        check_game_end();
    }
    void check_game_end(){
        if(piknikkosarak.length() == 0){
            end = true;
            _timer->stop();
            _gameTimer->stop();
            emit gameOver(true,player.get_points(),gameTime);
        }
        foreach(VadOr* v,vadorok){
            if( qAbs(v->get_x() - player.get_x()) <=1 && qAbs(v->get_y() - player.get_y()) <=1 ){
                end = true;
                _timer->stop();
                _gameTimer->stop();
                emit gameOver(false,player.get_points(),gameTime);
            }
        }
    }

};

#endif // GAME_H
