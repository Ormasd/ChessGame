#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setFixedSize(sizeHint());

    file_ = menuBar()->addMenu("&File");

    game_ = new Game();
    setCentralWidget(game_);
    game_->start();

    restart_game_ = new QAction("&Restart game", this);
    connect(restart_game_, &QAction::triggered, game_, &Game::restart_game);
    file_->addAction(restart_game_);

    quit_ = new QAction("&Quit", this);
    connect(quit_, &QAction::triggered, qApp, QApplication::quit);
    file_->addAction(quit_);
}

MainWindow::~MainWindow()
{
    delete game_;
    delete quit_;
    delete restart_game_;
}
