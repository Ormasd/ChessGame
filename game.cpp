#include "game.h"

Game::Game(QWidget *parent) : QWidget(parent)
{
    step_counter_ = 0;

    hlayout_ = new QHBoxLayout(this);
    vlayout_ = new QVBoxLayout(this);
    hlayout_->setSpacing(10);

    game_board_ = new ChessBoard(this);

    hlayout_->addWidget(game_board_);
    hlayout_->addLayout(vlayout_);
    setLayout(hlayout_);

    player_one_ = new Player();
    player_one_->set_color_pieces(Qt::white);
    player_two_ = new Player();
    player_two_->set_color_pieces(Qt::black);
}

Game::~Game()
{
    delete player_one_;
    delete player_two_;
    delete game_board_;
    delete vlayout_;
    delete hlayout_;
}

void Game::start()
{
    connect(game_board_, &ChessBoard::emission_active_cell, player_one_, &Player::set_move);
    connect(player_one_, &Player::move_made, this, &Game::change_stepcounter);
    connect(player_two_, &Player::move_made, this, &Game::change_stepcounter);
    connect(this, &Game::step_counter_changed, this, &Game::player_change);
    return;
}

void Game::restart_game()
{
    game_board_->reset_board();
    step_counter_ = 0;
    disconnect(game_board_, &ChessBoard::emission_active_cell, player_two_, &Player::set_move);
    connect(game_board_, &ChessBoard::emission_active_cell, player_one_, &Player::set_move);
}

void Game::change_stepcounter()
{
    ++step_counter_;
    emit step_counter_changed();
    return;
}

void Game::player_change()
{
    if(step_counter_ % 2)
    {
        disconnect(game_board_, &ChessBoard::emission_active_cell, player_one_, &Player::set_move);
        connect(game_board_, &ChessBoard::emission_active_cell, player_two_, &Player::set_move);
    }
    else
    {
        disconnect(game_board_, &ChessBoard::emission_active_cell, player_two_, &Player::set_move);
        connect(game_board_, &ChessBoard::emission_active_cell, player_one_, &Player::set_move);
    }
    game_board_->reverse_viewboard();
    return;
}
