#include "Board.h"

Board::Board()
{
	for (int i = 0; i < PIECE_COUNT; ++i) {
		bitmaps[i] = 0ull;
	}
	bitmaps[WP] = 0x000000000000FF00ull;
	bitmaps[WR] = 0x0000000000000081ull;
	bitmaps[WN] = 0x0000000000000042ull;
	bitmaps[WB] = 0x0000000000000024ull;
	bitmaps[WQ] = 0x0000000000000010ull;
	bitmaps[WK] = 0x0000000000000008ull;

	bitmaps[BP] = 0x00FF000000000000ull;
	bitmaps[BR] = 0x8100000000000000ull;
	bitmaps[BN] = 0x4200000000000000ull;
	bitmaps[BB] = 0x2400000000000000ull;
	bitmaps[BQ] = 0x1000000000000000ull;
	bitmaps[BK] = 0x0800000000000000ull;
}

Board::~Board() {}

// ************************************************************************
//	Printing piece on board presentation
// ************************************************************************
void Board::printBoard() const
{
	for (int row = 0; row < 8; ++row) {
		for (int column = 0; column < 8; ++column) {
			int bit = (row * 8) + column;

			Piece p = getPieceAt(bit);
			if (p != NO_PIECE) { std::cout << pieceStr[p] << " "; }
			else std::cout << "  ";

		}
		std::cout << "\n";
	}
}
// ************************************************************************
// ************************************************************************



// ************************************************************************
//	Setting, Clearing
// ************************************************************************
void Board::clearPiece(Piece piece, unsigned int bit)
{
	bitmaps[piece] &= ~(1ull << bit);
}

void Board::setPiece(Piece piece, unsigned int bit)
{
	bitmaps[piece] |= (1ull << bit);
}
// ************************************************************************
// ************************************************************************



// ************************************************************************
//	Checking pieces set on board
// ************************************************************************
inline bool Board::hasPiece(Piece p, int bit) const
{
	return (bitmaps[p] & (1ull << bit));
}

Piece Board::getPieceAt(int sq) const
{
	for (int i = 0; i < PIECE_COUNT; i++) {
		if (bitmaps[i] & (1ull << sq)) {
			return static_cast<Piece>(i);
		}
	}
	return NO_PIECE;
}

// ************************************************************************
// ************************************************************************