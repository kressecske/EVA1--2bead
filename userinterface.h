#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QKeyEvent>
#include "game.h"
class UserInterface : public QWidget
{
    Q_OBJECT

public:
    explicit UserInterface(QWidget *parent = 0);
    ~UserInterface();
    QGridLayout *_table;
    QLabel *_item;
    Game *_game;
    void printGameTable();

    void keyPressEvent(QKeyEvent *e);

private:
};

#endif // USERINTERFACE_H
