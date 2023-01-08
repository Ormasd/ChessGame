#include "cell.h"
#include "chessboard.h"

Cell::Cell(QWidget *parent) : QWidget(parent){
    row_pos_ = 0;
    column_pos_ = 0;
    piece_ = nullptr;
    color_ = QColor(0,0,0,0);
    box_cell_ = new QGridLayout(this);
    setLayout(box_cell_);
    board_ = nullptr;
}

Cell::~Cell()
{
    delete piece_;
    delete box_cell_;
}

void Cell::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    painting_cell();
    return;
}

void Cell::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    emit self_emission(this);
}


void Cell::painting_cell()
{
    QPainter qp(this);
    qp.setBrush(color_ == Qt::black ? Qt::Dense3Pattern :Qt::Dense6Pattern);
    if(color_ == Qt::green)
        qp.setBrush(Qt::Dense2Pattern);
    qp.drawRect(0,0,width(),height());
    return;
}



void Cell::set_parameters(qint8 row, quint8 column)
{
    row_pos_ = row;
    column_pos_ = column;
    color_ =  (row+column) %2 ? Qt::black : Qt::white;
}

void Cell::set_piece(QPixmap *pmap)
{
    if(piece_)
        delete piece_;
    if(row_pos_ == 1 || row_pos_ == 6){
        piece_ = new Piece(this);
        piece_ = new Pawn(piece_);
    } else if(row_pos_ == 0 || row_pos_ == 7)
    {
        piece_ = new Piece(this);
        switch(column_pos_)
        {
        case 0:
        case 7: piece_ = new Rook(piece_);   break;
        case 1:
        case 6: piece_ = new Knight(piece_); break;
        case 2:
        case 5: piece_ = new Bishop(piece_); break;
        case 3: piece_ = new Queen(piece_);  break;
        case 4: piece_ = new King(piece_);   break;
        }
    } else
    {
        piece_ = nullptr;
    }
    if(piece_){
        piece_->set_color(row_pos_ <= 3 ? Qt::black : Qt::white);
        piece_->set_images(pmap);
        add_piece(piece_);

    }
    return;
}

void Cell::set_board(ChessBoard *board)
{
    board_ = board;
    return;
}



QColor Cell::get_color()
{
    return color_;
}

Piece* Cell::get_piece()
{
    return piece_;
}

QPoint Cell::get_position()
{
    return QPoint(row_pos_, column_pos_);
}

void Cell::remove_piece(Piece *piece)
{
    if(piece)
    {
        box_cell_->removeWidget(piece);
        disconnect(piece_,&Piece::piece_to_cell, this, &Cell::forward_piece);
    }
}

void Cell::add_piece(Piece *piece)
{
    if(piece)
        box_cell_->addWidget(piece);
    connect(piece_,&Piece::piece_to_cell, this, &Cell::forward_piece);
}

bool Cell::swap_pieces(Cell* other_cell)
{
    if((piece_->is_movable(this, other_cell) && board_->is_free_way(this, other_cell)) ||
            piece_->can_capture(this, other_cell) && board_->is_free_way(this, other_cell))
    {
            remove_piece(piece_);
            other_cell->remove_piece(other_cell->piece_);

            Piece* temp_piece = other_cell->piece_;
            other_cell->piece_ = piece_;
            piece_ = temp_piece;

            add_piece(piece_);
            other_cell->add_piece(other_cell->piece_);
            return true;
    }
    return false;
}

void Cell::capture_piece(Cell *other_cell)
{
    if(swap_pieces(other_cell)){
        remove_piece(piece_);
        delete piece_;
        piece_ = nullptr;
    }
    return;
}

void Cell::forward_piece()
{
    emit self_emission(this);
}
