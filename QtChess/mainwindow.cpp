#include "mainwindow.h"
#include "chessboard.h"
#include <QScrollBar>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	ui.verticalLayout_2->setContentsMargins(0, 0, 0, 0);
	ui.verticalLayout_2->setSpacing(0);

	ui.gridLayout->setContentsMargins(0, 0, 0, 0);
	ui.gridLayout->setSpacing(9);

	ui.gridLayout->removeWidget(ui.topwidget);
	ui.gridLayout->addWidget(ui.topwidget, 0, 0, 1, 3);

	ui.gridLayout->removeWidget(ui.movelistwidget);
	ui.gridLayout->addWidget(ui.movelistwidget, 1, 0);

	ui.gridLayout->removeWidget(ui.boardwidget);
	ui.gridLayout->addWidget(ui.boardwidget, 1, 1);

	ui.gridLayout->removeWidget(ui.analysiswidget);
	ui.gridLayout->addWidget(ui.analysiswidget, 1, 2);

	ui.gridLayout->setColumnStretch(0, 1);
	ui.gridLayout->setColumnStretch(1, 2);
	ui.gridLayout->setColumnStretch(2, 1);

	ui.gridLayout->setRowStretch(1, 1);

	ui.movelistwidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	ui.verticalLayout_3->setContentsMargins(4, 4, 4, 4);
	ui.verticalLayout_3->setAlignment(Qt::AlignTop);
	ui.verticalLayout_3->setSpacing(2);
	ui.movelistwidget->setStyleSheet("border: 1px solid rgba(255, 0, 0, 160);");

	ui.movetableview->horizontalHeader()->setStretchLastSection(true);
	ui.movetableview->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	ui.movetableview->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui.movetableview->setEditTriggers(QAbstractItemView::NoEditTriggers);

	ui.analysiswidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	ui.verticalLayout_4->setContentsMargins(4, 4, 4, 4);
	ui.analysiswidget->setStyleSheet("border: 1px solid rgba(255, 0, 0, 160);");

	ui.analysistable->horizontalHeader()->setStretchLastSection(true);
	ui.analysistable->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	ui.analysistable->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui.analysistable->setEditTriggers(QAbstractItemView::NoEditTriggers);

	ui.topwidget->setStyleSheet("border: 1px solid rgba(255, 0, 0, 160);");
	ui.boardwidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

MainWindow::~MainWindow()
{}

