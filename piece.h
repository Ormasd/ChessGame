#ifndef PIECE_H
#define PIECE_H

#include <QColor>
#include <QWidget>
#include <QPixmap>
#include <QLabel>
#include <QGridLayout>
#include <QMouseEvent>

class Cell;

enum class PieceName{
    EMPTY,
    PAWN,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING,
};

class Piece : public QWidget
{
    Q_OBJECT
public:
    Piece(QWidget* parent = nullptr);
    virtual ~Piece();

    void set_color(QColor color);
    virtual void set_images(QPixmap* pmap);
    virtual bool is_movable(Cell* begin, Cell* end);
    virtual bool can_capture(Cell* begin, Cell* end);


    PieceName get_piece_name();
    QLabel* get_piece_image();
    QColor get_color();



protected:
    void mousePressEvent(QMouseEvent *event);


protected:
    QColor piece_color_;
    PieceName piece_name_;
    QString notation_;
    QLabel* image_;
    QGridLayout* piece_box_;

signals:
    void piece_to_cell();
};



class Pawn : public Piece
{
public:
    Pawn(Piece* parent = nullptr);
    bool is_movable(Cell* begin, Cell* end) override;
    bool can_capture(Cell* begin, Cell* end) override;
private:
    bool is_moved_;
};

class Knight : public Piece
{
public:
    Knight(Piece* parent = nullptr);
    bool is_movable(Cell* begin, Cell* end) override;
};

class Bishop : public Piece
{
public:
    Bishop(Piece* parent = nullptr);
    bool is_movable(Cell* begin, Cell* end) override;
};

class Rook : public Piece
{
public:
    Rook(Piece* parent = nullptr);
    bool is_movable(Cell* begin, Cell* end) override;
};

class King : public Piece
{
public:
    King(Piece* parent = nullptr);
    bool is_movable(Cell* begin, Cell* end) override;
};

class Queen : public Piece
{
public:
    Queen(Piece* parent = nullptr);
    bool is_movable(Cell* begin, Cell* end) override;
};
#endif // PIECE_H
