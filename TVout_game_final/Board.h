/*
 * Board.h
 *
 * Created: 2014.10.16 16:24:34
 *  Author: Justas
 */ 

#ifndef BOARD_H_
#define BOARD_H_
#include <TVout.h>
#include "Drawable.h"
#include "Piece.h"

class Board : public Drawable{
	protected:
		int boardSize;
		TVout* TV;
		const float hresProcent;
		const float vresProcent;
		const int squareSizeProc;
		const int boardSizeProc;
		const int offset;
		bool active;
		int activeColumn;
		int activeRow;
		Piece board[5][5];
				
		void drawX(int column, int row);
		void drawO(int column, int row);
	public:
		Board(TVout* TV, int boardSize);
		//draw boardSize x boardSize board
		void draw();
		void setActive(int column, int row);
		void untoActive();
		//select column and row from 1 till boardSize to draw X
		void setX(int column, int row);
		//select column and row from 1 till boardSize to draw O
		void setO(int column, int row);
		//get what piece is place located at column, row.
		Piece getPiece(int column, int row);
		int getActiveColumn();
		int getActiveRow();
		int getBoardSize();
};



#endif /* BOARD_H_ */