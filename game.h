#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include "chessboard.h"
#include "player.h"

class Game : public QWidget
{
    Q_OBJECT
public:
    explicit Game(QWidget *parent = nullptr);
    ~Game();
    void start();
    void restart_game();

private:
    QHBoxLayout* hlayout_;
    QVBoxLayout* vlayout_;
    ChessBoard* game_board_;
    int step_counter_;
    Player* player_one_;
    Player* player_two_;

    void change_stepcounter();
    void player_change();

signals:
    void step_counter_changed();
};

#endif // GAME_H
