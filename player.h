#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include "cell.h"

class Player : public QObject
{
    Q_OBJECT
public:
    explicit Player(QObject *parent = nullptr);
    ~Player();
    void set_move(Cell* cell);
    void set_color_pieces(QColor color);
private:
    Cell* first_cell_;
    QColor color_pieces_;
signals:
    void move_made();
};

#endif // PLAYER_H
