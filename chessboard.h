#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <array>
#include <QWidget>
#include <QPixmap>
#include <QGridLayout>
#include <QPainter>
#include "cell.h"

#define BOARDSIZE 8

class ChessBoard : public QWidget
{
    Q_OBJECT
public:
    explicit ChessBoard(QWidget *parent = nullptr);
    ~ChessBoard();
    void reset_board();
    void reverse_viewboard();
    void activation_cell(Cell* cell);
    bool is_free_way(Cell* begin, Cell* end);
private:
    std::array<std::array<Cell*, BOARDSIZE>, BOARDSIZE> board_;
    QPixmap* piece_images_;
    QGridLayout* board_layout_;
    bool is_reversed_board_;
signals:
    void emission_active_cell(Cell* cell);
};

#endif // CHESSBOARD_H
