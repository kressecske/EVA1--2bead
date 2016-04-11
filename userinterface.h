#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QPushButton>
#include <QPixmap>
#include "game.h"
class UserInterface : public QWidget
{
    Q_OBJECT
public slots:
    void newGameButton();
    void pauseButton();
    void Over(bool b,int p);
    void printGameTable();
    void chooseMap();
public:
    explicit UserInterface(QWidget *parent = 0);
    ~UserInterface();
    QVBoxLayout *_mainLayout;
    QHBoxLayout *_menuLayout;
    QPushButton *_newGame;
    QPushButton *_chooseMap;
    QPushButton *_pause;
    QPushButton *_exit;
    QGridLayout *_table;
    QLabel *_points;
    Game *_game;
    QString _map;

    QVector<QLabel*> elemnts;

    void keyPressEvent(QKeyEvent *e);
private:
};

#endif // USERINTERFACE_H
