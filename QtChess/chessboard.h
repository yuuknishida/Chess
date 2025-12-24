#pragma once
#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QWidget>
#include "./c"
#include "ui_chessboard.h"

// Chessboard class definition
// Inherits from QWidget Manages the chessboard UI
// and handles resize events using the generated UI class from ui_chessboard.h

// functions:
// - Chessboard(QWidget *parent = nullptr): Constructor that initializes the chessboard UI.
// - ~Chessboard(): Destructor for the chessboard class.
// - void resizeEvent(QResizeEvent* event) override: Handles resize events for the chessboard.
// - void setPiecePixmap(const QString& position, const QPixmap& pixmap): Sets the pixmap for a specific chess piece on the board.
// - QPixmap getPiecePixmap(const QString& position) const: Retrieves the pixmap of a specific chess piece on the board.
// members:

enum Piece {
	WP, WR, WN, WB, WQ, WK,
	BP, BR, BN, BB, BQ, BK,
	PIECE_COUNT,
	NO_PIECE = -1
};

class Chessboard : public QWidget
{
	Q_OBJECT

public:
	explicit Chessboard(QWidget *parent = nullptr);
	~Chessboard();

	void setPixmap();

protected:
	void resizeEvent(QResizeEvent* event) override;

private:
	Ui::ChessboardClass ui;

	QIcon piecePixmaps[PIECE_COUNT];
};

#endif