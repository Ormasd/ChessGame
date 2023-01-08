#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QLayout>
#include <QPushButton>
#include <QPoint>
#include <QMenu>
#include <QMenuBar>

#include "game.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QMenu *file_;
    QAction *restart_game_;
    QAction *quit_;

    Game* game_;

signals:

};

#endif // MAINWINDOW_H
