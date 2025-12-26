#pragma once
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>
#ifndef BOARD_H
#define BOARD_H

enum Square {
	A8=56, B8=57, C8=58, D8=59, E8=60, F8=61, G8=62, H8=63,
	A7=48, B7=49, C7=50, D7=51, E7=52, F7=53, G7=54, H7=55,
	A6=40, B6=41, C6=42, D6=43, E6=44, F6=45, G6=46, H6=47,
	A5=32, B5=33, C5=34, D5=35, E5=36, F5=37, G5=38, H5=39,
	A4=24, B4=25, C4=26, D4=27, E4=28, F4=29, G4=30, H4=31,
	A3=16, B3=17, C3=18, D3=19, E3=20, F3=21, G3=22, H3=23,
	A2=8,  B2=9,  C2=10, D2=11, E2=12, F2=13, G2=14, H2=15,
	A1=0,  B1=1,  C1=2,  D1=3,  E1=4,  F1=5,  G1=6,  H1=7,
};

enum Piece {
	WP, WR, WN, WB, WQ, WK,
	BP, BR, BN, BB, BQ, BK,
	PIECE_COUNT,
	NO_PIECE = -1
};

static  const char* pieceStr[] = {
	"wP", "wR", "wN", "wB", "wQ", "wK",
	"bP", "bR", "bN", "bB", "bQ", "bK"
};

class Board
{
public:
	Board();
	~Board();
	
	void printBoard() const;

	void clearPiece(Piece piece, unsigned int bit);
	void setPiece(Piece piece, unsigned int bit);

	bool hasPiece(Piece p, int bit) const;  
	bool movePiece(Piece piece, int fromSq, int toSq);

	Piece getPieceAt(int sq) const;

	uint64_t bitmaps[PIECE_COUNT];

	std::vector<int> allMoveOptions;
	uint64_t selectedPosition = 0x0000000000000000;

	Piece selectedPiece = NO_PIECE;
};

#endif // BOARD_H