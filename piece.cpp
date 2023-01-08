#include "piece.h"
#include "cell.h"



Piece::Piece(QWidget* parent) : QWidget(parent){
    piece_name_ = PieceName::EMPTY;
    piece_color_ = QColor(0,0,0,0);
    notation_ = "";
    image_ = nullptr;

}

Piece::~Piece()
{
    delete image_;
    delete piece_box_;
}

void Piece::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    emit piece_to_cell();
}

bool Piece::is_movable(Cell* begin, Cell* end)
{
    return false;
}

bool Piece::can_capture(Cell* begin, Cell* end)
{
    return is_movable(begin, end);
}

void Piece::set_color(QColor color)
{
    piece_color_ = color;
    return;
}

void Piece::set_images(QPixmap *pmap)
{
    int width = pmap->width()/6;                      // 6 - number of columns on parent QPixmap
    int height = pmap->height()/2;                    // 2 - number of rows on parent QPixmap

    if(piece_name_ != PieceName::EMPTY){
        image_ = new QLabel(this);
        switch(piece_name_){
        case PieceName::KING:
            image_->setPixmap(pmap->copy(width*0,(piece_color_ == Qt::white ? 0 : height), width, height));
            break;
        case PieceName::QUEEN:
            image_->setPixmap(pmap->copy(width*1,(piece_color_ == Qt::white ? 0 : height), width, height));
            break;
        case PieceName::BISHOP:
            image_->setPixmap(pmap->copy(width*2,(piece_color_ == Qt::white ? 0 : height), width, height));
            break;
        case PieceName::KNIGHT:
            image_->setPixmap(pmap->copy(width*3,(piece_color_ == Qt::white ? 0 : height), width, height));
            break;
        case PieceName::ROOK:
            image_->setPixmap(pmap->copy(width*4,(piece_color_ == Qt::white ? 0 : height), width, height));
            break;
        case PieceName::PAWN:
            image_->setPixmap(pmap->copy(width*5,(piece_color_ == Qt::white ? 0 : height), width, height));
            break;
        }
    image_->setCursor(Qt::PointingHandCursor);
    image_->setToolTip(notation_);
    image_->setScaledContents(true);
    piece_box_ = new QGridLayout(this);
    setLayout(piece_box_);
    piece_box_->addWidget(image_);
    }
    return;
}

PieceName Piece::get_piece_name()
{
    return piece_name_;
}

QLabel *Piece::get_piece_image()
{
    return image_;
}

QColor Piece::get_color()
{
    return piece_color_;
}







Pawn::Pawn(Piece* parent) : Piece(parent)
{
    notation_ = "";
    piece_name_ = PieceName::PAWN;
    is_moved_ = false;
}

bool Pawn::is_movable(Cell* begin, Cell* end)
{
    auto result_x = begin->get_position().x() - end->get_position().x();
    if(begin->get_position().y() == end->get_position().y())
        switch (result_x)
        {
        case 2: if(is_moved_) return false;
        case 1: if(get_color() == Qt::white)
            {
                is_moved_ = true;
                return true;
            }
            break;
        case -2: if(is_moved_) return false;
        case -1: if(get_color() == Qt::black)
            {
                is_moved_ = true;
                return true;
            }
            break;
        }
    return false;
}

bool Pawn::can_capture(Cell* begin, Cell* end)
{
    if(!end->get_piece()) return false;
    auto result_x = begin->get_position().x()-end->get_position().x();
    auto result_y = std::abs(begin->get_position().y()-end->get_position().y());
    if(result_y == 1)
    {
    if(result_x == -1 && get_color() == Qt::black) return true;
    if(result_x == 1 && get_color() == Qt::white) return true;
    }
    return false;
}

Knight::Knight(Piece* parent) : Piece(parent)
{
    notation_ = "N";
    piece_name_ = PieceName::KNIGHT;
}

bool Knight::is_movable(Cell* begin, Cell* end)
{
    auto result_x = std::abs(begin->get_position().x()-end->get_position().x());
    auto result_y = std::abs(begin->get_position().y()-end->get_position().y());
    if(result_x == 2)
        return result_y == 1 ? true : false;
    if(result_y == 2)
        return result_x == 1 ? true : false;
    return false;
}

Bishop::Bishop(Piece* parent) : Piece(parent)
{
    notation_ = "B";
    piece_name_ = PieceName::BISHOP;
}

bool Bishop::is_movable(Cell* begin, Cell* end)
{
    auto result_x = std::abs(begin->get_position().x()-end->get_position().x());
    auto result_y = std::abs(begin->get_position().y()-end->get_position().y());
    return result_x == result_y ? true : false;
}

Rook::Rook(Piece* parent) : Piece(parent)
{
    notation_ = "R";
    piece_name_ = PieceName::ROOK;
}

bool Rook::is_movable(Cell* begin, Cell* end)
{
    auto result_x = std::abs(begin->get_position().x()-end->get_position().x());
    auto result_y = std::abs(begin->get_position().y()-end->get_position().y());
    return (result_x == 0 || result_y == 0) ? true : false;
}

King::King(Piece* parent) : Piece(parent)
{
    notation_ = "K";
    piece_name_ = PieceName::KING;
}

bool King::is_movable(Cell* begin, Cell* end)
{
    auto result_x = std::abs(begin->get_position().x()-end->get_position().x());
    auto result_y = std::abs(begin->get_position().y()-end->get_position().y());
    return (result_x > 1 || result_y > 1) ? false : true;
}

Queen::Queen(Piece* parent) : Piece(parent)
{
    notation_ = "R";
    piece_name_ = PieceName::QUEEN;
}

bool Queen::is_movable(Cell* begin, Cell* end)
{
    auto result_x = std::abs(begin->get_position().x()-end->get_position().x());
    auto result_y = std::abs(begin->get_position().y()-end->get_position().y());
    return (result_x == 0 || result_y == 0 || result_x == result_y) ? true : false;
}
