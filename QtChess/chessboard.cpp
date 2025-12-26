#include "chessboard.h"

Chessboard::Chessboard(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	ui.gridLayout->setContentsMargins(0, 0, 0, 0);
	ui.gridLayout->setSpacing(0);

	ui.gridLayout->setAlignment(Qt::AlignCenter);

	setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

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

	// Debug: verify pixmaps loaded
	for (int i = 0; i < PIECE_COUNT; ++i) {
		QPixmap pm = piecePixmaps[i].pixmap(64, 64);
		if (pm.isNull()) {
			std::cerr << "Failed to load pixmap for piece index " << i << std::endl;
		}
	}

	for (int row = 8; row >= 0; row--) {
		for (int column = 8; column >= 0; column--) {
			int bit = row * 8 + column;
			QLayoutItem* item = ui.gridLayout->itemAtPosition(row, column);
			if (!item) continue;

			QWidget* widget = item->widget();
			QPushButton* squareButton = qobject_cast<QPushButton*>(widget);
			
			connect(squareButton, &QPushButton::clicked, this, [this, squareButton]() {
				onButtonClicked(*squareButton);
			});

			if (squareButton) {
				if((row + column) % 2 == 0)
					squareButton->setStyleSheet("background-color: #F0D9B5; border: none;");
				else
					squareButton->setStyleSheet("background-color: #B58863; border: none;");
				squares.append(squareButton);
			}
		}
	}

	adjustSquareSizes();
	setPixmap();
}

// ************************************************************************
//	Destructor
// ************************************************************************
Chessboard::~Chessboard()
{}

// ************************************************************************
// Painting / Icon setting
// - Walks through the gridlayout and sets the appropriate pixmap for each square
// ************************************************************************
void Chessboard::setPixmap()
{
	for (int row = 0; row < 8; row++) {
		for (int column = 0; column < 8; column++) {
			int bit = (7 - row) * 8 + column;

			Piece piece = board.getPieceAt(bit);

			QLayoutItem* item = ui.gridLayout->itemAtPosition(row, column);
			if (!item) continue;

			QWidget* widget = item->widget();
			QPushButton* squareButton = qobject_cast<QPushButton*>(widget);
			squareButton->setContentsMargins(0, 0, 0, 0);
			squareButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
			squareButton->setMinimumSize(30, 30);
			squareButton->setCheckable(true);
			if (!squareButton) continue;

			if (piece != NO_PIECE) {
				squareButton->setIcon(piecePixmaps[piece]);
			}
			else {
				squareButton->setIcon(QIcon());
			}
		}
	}
	for (int i = 0; i < 8; ++i) {
		ui.gridLayout->setRowStretch(i, 1);
		ui.gridLayout->setColumnStretch(i, 1);
	}
}

// ************************************************************************
//	Debug Borders
// ************************************************************************
void Chessboard::setDebugBorders(bool enabled)
{
	if (m_debugBorders == enabled) return;
	m_debugBorders = enabled;
	setPixmap();
}

bool Chessboard::debugBorders() const
{
	return m_debugBorders;
}

// ************************************************************************
//	Piece Selection API
// ************************************************************************
void Chessboard::setPieceSelected(bool selected, int squareIndex)
{
// Arg:
// - selected: true if a piece is selected, false if selection is cleared
// - squareIndex: index of the square where the piece is selected (0-63), -1 if clearing selection
	if (selected) {
		if (isPieceSelected) {
			moveSelected(squareIndex);
			return;
		}
		pieceSelected(squareIndex);
	}
	else if (!selected) {
		pieceSelectionCleared();
	}

}

void Chessboard::pieceSelected(int squareIndex)
{
	isPieceSelected = true;
	board.selectedPiece = board.getPieceAt(squareIndex);
	board.selectedPosition = 1ull << squareIndex;
	setHighlightedSquares(squareIndex, true);
	qDebug() << "Piece selected at square index:" << squareIndex;
	qDebug() << "Selected piece:" << pieceStr[board.selectedPiece];
}


void Chessboard::pieceSelectionCleared()
{
	isPieceSelected = false;
	board.selectedPiece = NO_PIECE;
	board.selectedPosition = 0x0000000000000000;
	setHighlightedSquares(getSquareIndexFromButton(*chosenSquare), false);
	qDebug() << "Piece selection cleared.";
}

void Chessboard::moveSelected(int toSquareIndex)
{
	return;
}

// ************************************************************************
//	Button Click Handling
// - Identifies which button was clicked and manages piece selection and move making
// ************************************************************************
void Chessboard::onButtonClicked(QPushButton& button)
{
	// if a button is clicked, identify which one
	// - if button is clicked enable isPieceSelected
	// - if isPieceSelected is true, make the move
	uint64_t sqIndex = getSquareIndexFromButton(button);
	if (sqIndex < 0) return;
	
	if (isPieceSelected && chosenSquare != &button) {
		// A piece is already selected, so this click is a move
	}
	else if (!isPieceSelected) {
		// No piece is selected, so this click selects a piece
		chosenSquare = &button;
		setPieceSelected(true, sqIndex);
	}
	else if (chosenSquare == &button) {
		// Clicked the same square again, clear selection
		chosenSquare = nullptr;
		setPieceSelected(false);
	}
	else {
		// Clicked a different square, change selection
		chosenSquare = &button;
		setPieceSelected(true, sqIndex);
	}
}

// ************************************************************************
//	Resize Event Handling
// - Adjusts square sizes and resets pixmaps on resize
// ************************************************************************
void Chessboard::resizeEvent(QResizeEvent * event)
{
	QWidget::resizeEvent(event);

	adjustSquareSizes();

	setPixmap();
}

QSize Chessboard::sizeHint() const
{
	int parentSide = 400;
	if (parentWidget()) {
		parentSide = std::min(parentWidget()->width(), parentWidget()->height());
	}
	int defaultMax = (m_maxBoardSize > 0) ? m_maxBoardSize : 400;
	int s = std::min(parentSide, defaultMax);
	s = std::max(s, 200);
	return QSize(s, s);
}

int Chessboard::heightForWidth(int w) const
{
	int side = w;
	if (m_maxBoardSize > 0) side = std::min(side, m_maxBoardSize);
	return side;
}

void Chessboard::adjustSquareSizes()
{
	int side = std::min(width(), height());
	if (m_maxBoardSize > 0) side = std::min(side, m_maxBoardSize);

	int squareSide = side / 8;

	const int iconPadding = 6;
	int iconSize = std::max(0, squareSide - iconPadding);

	for (int i = 0; i < squares.size(); ++i) {
		QPushButton* square = squares.at(i);

		square->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
		square->setFixedSize(squareSide, squareSide);
		square->setIconSize(QSize(iconSize, iconSize));
	}
}

void Chessboard::setHighlightedSquares(int sqIndex, bool selected)
{
	const int row = sqIndex / 8;
	const int column = sqIndex % 8;
	bool isLightSquare = (row + column) % 2 == 0;

	const QString darkSquare = "#B58863;";
	const QString lightSquare = "#F0D9B5;";
	const QString selectedColor = "#FFFF00;";
	const QString moveOptionColor = "#00FF00;";
	if (selected) {
		// Highlight the square at sqIndex
		// Change square colors of selected square and move options
		if (sqIndex == getSquareIndexFromButton(*chosenSquare)) {
			// Selected square
			squares.at(sqIndex)->setStyleSheet(QString("background-color: %1 border: none;").arg(selectedColor));
		}
		else {
			// Move option square
			squares.at(sqIndex)->setStyleSheet(QString("background-color: %1 border: none;").arg(moveOptionColor));
		}
	}
	else {
		// Clear Highlights
		// Restore original square colors
		squares.at(sqIndex)->setStyleSheet(QString("background-color: %1 border: none;").arg(isLightSquare ? lightSquare : darkSquare));
	}
}

int Chessboard::getSquareIndexFromButton(const QPushButton& button) const
{
	for (int i = 0; i < squares.size(); ++i) {
		if (squares.at(i) == &button) {
			return i;
		}
	}
	return -1; // Not found
}


