#pragma once
#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QWidget>
#include <QVector>
#include <string>
#include <ostream>
#include <iostream>
#include "../chess_logic/Board.h"
#include "ui_chessboard.h"

// Chessboard class definition
// Inherits from QWidget Manages the chessboard UI
// and handles resize events using the generated UI class from ui_chessboard.h

class Chessboard : public QWidget
{
	Q_OBJECT

public:
	explicit Chessboard(QWidget *parent = nullptr);
	~Chessboard();

	void setPixmap();
	void setDebugBorders(bool enabled);
	bool debugBorders() const;

	void setPieceSelected(bool selected, int squareIndex = -1);

	void pieceSelected(int squareIndex);	// emit when a piece becomes selected. squareindex is the index of the selected square
	void pieceSelectionCleared();	// emit when piece selection is cleared
	void moveSelected(int toSquareIndex); // emit when a move is selected. toSquareIndex is the index of the target square

protected:
	void resizeEvent(QResizeEvent* event) override;
	QSize sizeHint() const override;

	bool hasHeightForWidth() const override { return true; }
	int heightForWidth(int w) const override;

private slots:
	void onButtonClicked(QPushButton& button);

private:
	Ui::Chessboard ui;

	QIcon piecePixmaps[PIECE_COUNT];
	QVector<QPushButton*> squares;
	QPushButton* chosenSquare = nullptr;

	int getSquareIndexFromButton(const QPushButton& button) const;

	Board board;
	
	int m_maxBoardSize = 800;

	bool m_debugBorders = false;
	bool isPieceSelected = false;

	void adjustSquareSizes();

	void setHighlightedSquares(int sqIndex, bool selected);
};

#endif