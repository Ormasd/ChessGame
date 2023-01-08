#include "chessboard.h"
#include <cmath>

ChessBoard::ChessBoard(QWidget *parent) : QWidget(parent)
{
    piece_images_ = new QPixmap("pieces.png");
    is_reversed_board_ = false;
    board_layout_ = new QGridLayout(this);
    board_layout_->setSpacing(0);
    setLayout(board_layout_);

    for(int row = 0; row < BOARDSIZE; ++row)
        for(int column = 0; column < BOARDSIZE; ++column)
        {
            board_[row][column] = new Cell();
            board_[row][column]->set_parameters(row,column);
            board_[row][column]->set_piece(piece_images_);
            board_[row][column]->set_board(this);
            board_[row][column]->setFixedSize(100,100);
            connect(board_[row][column], &Cell::self_emission, this, &ChessBoard::activation_cell);
            board_layout_->addWidget(board_[row][column],row,column);
        }
}

ChessBoard::~ChessBoard()
{
    for(int row = 0; row < BOARDSIZE; ++row)
            for(int column = 0; column < BOARDSIZE; ++column)
            {
                delete board_[row][column];
                board_[row][column] = nullptr;
            }
    delete piece_images_;
    delete board_layout_;
}

void ChessBoard::reset_board()
{

    for(int row = 0; row < BOARDSIZE; ++row)
        for(int column = 0; column < BOARDSIZE; ++column)
        {
            board_[row][column]->set_piece(piece_images_);
        }
    if(is_reversed_board_)
        reverse_viewboard();
    return;
}

void ChessBoard::reverse_viewboard()
{
    for(int row = 0; row < BOARDSIZE; ++row)
        for(int column = 0; column < BOARDSIZE; ++column)
            board_layout_->removeWidget(board_[row][column]);
    if(!is_reversed_board_)
        for(int row = 0; row < BOARDSIZE; ++row)
            for(int column = 0; column < BOARDSIZE; ++column){
                board_layout_->addWidget(board_[row][column], BOARDSIZE-1-row, BOARDSIZE-1-column);
                is_reversed_board_ = true;
            }
    else
        for(int row = 0; row < BOARDSIZE; ++row)
            for(int column = 0; column < BOARDSIZE; ++column){
                board_layout_->addWidget(board_[row][column], row, column);
                is_reversed_board_ = false;
            }
    return;
}

void ChessBoard::activation_cell(Cell *cell)
{
    emit emission_active_cell(cell);
}

bool ChessBoard::is_free_way(Cell* begin, Cell* end)
{
    if(begin->get_piece()->get_piece_name() == PieceName::KNIGHT)
        return true;

    int step_row = end->get_position().x() - begin->get_position().x();
    if(step_row)
        step_row /= std::abs(end->get_position().x() - begin->get_position().x());

    int step_column = end->get_position().y() - begin->get_position().y();
    if(step_column)
        step_column /= std::abs(end->get_position().y() - begin->get_position().y());

    int row = begin->get_position().x() + step_row;
    int column = begin->get_position().y() + step_column;
    while(board_[row][column] != end)
    {
        if(board_[row][column]->get_piece())
            return false;
        else
        {
            row += step_row;
            column += step_column;
        }
    }

    return true;
}




