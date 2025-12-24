#include "mainwindow.h"
#include "chessboard.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.boardwidget->setFocus();
}

MainWindow::~MainWindow()
{}

