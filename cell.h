#ifndef CELL_H
#define CELL_H


#include <QWidget>
#include <QGridLayout>
#include <QPainter>
#include "piece.h"

class ChessBoard;

class Cell : public QWidget
{
    Q_OBJECT
public:
    explicit Cell(QWidget *parent = nullptr);
    ~Cell();

    void set_parameters(qint8 row, quint8 column);
    void set_piece(QPixmap *pmap);
    void set_board(ChessBoard* board);

    QColor get_color();
    Piece* get_piece();
    QPoint get_position();

    void remove_piece(Piece* piece);
    void add_piece(Piece* piece);
    bool swap_pieces(Cell* other_cell);
    void capture_piece(Cell* other_cell);
    void forward_piece();

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
private:
    void painting_cell();
    quint8 row_pos_;
    quint8 column_pos_;
    QColor color_;
    Piece* piece_;
    QGridLayout* box_cell_;
    ChessBoard* board_;

signals:
    void self_emission(Cell* cell);
};

#endif // CELL_H
