#include "chessboard.h"

Chessboard::Chessboard(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	
	piecePixmaps[WP] = QIcon(QPixmap("./assets/PawnW.png"));
	piecePixmaps[WR] = QIcon(QPixmap("./assets/RookW.png"));
	piecePixmaps[WN] = QIcon(QPixmap("./assets/KnightW.png"));
	piecePixmaps[WB] = QIcon(QPixmap("./assets/BishopW.png"));
	piecePixmaps[WQ] = QIcon(QPixmap("./assets/QueenW.png"));
	piecePixmaps[WK] = QIcon(QPixmap("./assets/KingW.png"));

	piecePixmaps[BP] = QIcon(QPixmap("./assets/PawnB.png"));
	piecePixmaps[BR] = QIcon(QPixmap("./assets/RookB.png"));
	piecePixmaps[BN] = QIcon(QPixmap("./assets/KnightB.png"));
	piecePixmaps[BB] = QIcon(QPixmap("./assets/BishopB.png"));
	piecePixmaps[BQ] = QIcon(QPixmap("./assets/QueenB.png"));
	piecePixmaps[BK] = QIcon(QPixmap("./assets/KingB.png"));
}

Chessboard::~Chessboard()
{}

void Chessboard::setPixmap()
{
	for (int row = 0; row < 8; ++row) {
		for (int column = 0; column < 8; ++column) {
			int bit = row * 8 + column;


		}
	}
}

void Chessboard::resizeEvent(QResizeEvent * event)
{
	QWidget::resizeEvent(event);
	update();
}

