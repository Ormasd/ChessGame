#include "player.h"

Player::Player(QObject *parent) : QObject(parent)
{
    first_cell_ = nullptr;
    color_pieces_ = Qt::white;
}

Player::~Player()
{
    delete first_cell_;
}

void Player::set_move(Cell *cell)
{
    if(!first_cell_)
    {
       if(cell->get_piece() && cell->get_piece()->get_color() == color_pieces_)
           first_cell_ = cell;
       return;
    }
    else
    {
        if(cell->get_piece())
        {
            if(cell->get_piece()->get_color() == color_pieces_)
                return;
            else
            {
                first_cell_->capture_piece(cell);
                first_cell_ = nullptr;
                emit move_made();
            }
        }
        else
        {
            if(first_cell_->swap_pieces(cell))
                emit move_made();
            first_cell_ = nullptr;

        }
    }
        return;
}

void Player::set_color_pieces(QColor color)
{
    color_pieces_ = color;
    return;
}
