
#include "Board.h"
#include <Arduino.h>
Board::Board(TVout* TV, int boardSize) 
	:	hresProcent(TV->hres()/100.0), 
		vresProcent(TV->vres()/100.0), 
		squareSizeProc(18), 
		boardSizeProc(boardSize*squareSizeProc),
		offset((100-boardSizeProc)/2)
{
	if(boardSize<=5 && boardSize >=3){
		this->boardSize = boardSize;
	}else if(boardSize<3){
		this->boardSize = 3;
	}else{
		this->boardSize = 5;
	}
	this->TV = TV;
	active = true;
	activeColumn = activeRow = 1;
	
	
	for(int i = 0; i < 5; i++){
		for(int j = 0; j < 5; j++){
			board[i][j] = _EMPTY;
		}
	}
	
}
void Board::draw(){
	TV->clear_screen();
	for(int xProc = offset; xProc <= offset+boardSizeProc; xProc+=squareSizeProc ){
		TV->draw_line(xProc*hresProcent, offset*vresProcent, xProc*hresProcent, (offset+boardSizeProc)*vresProcent, 1);
	}
	for(int yProc = offset; yProc <= offset+boardSizeProc; yProc+=squareSizeProc ){
		TV->draw_line(offset*hresProcent, yProc*vresProcent, (offset+boardSizeProc)*hresProcent, yProc*vresProcent, 1);
	}
	
	if(active){
		int xProcOffset = offset+(activeColumn-1)*squareSizeProc;
		int yProcOffset = offset+(activeRow-1)*squareSizeProc;
		const float margin = 0.2f;
		TV->draw_rect((xProcOffset + squareSizeProc*margin)*hresProcent,
					(yProcOffset + squareSizeProc*margin)*vresProcent,
					(squareSizeProc - 2*squareSizeProc*margin)*hresProcent,
					 (squareSizeProc -2*squareSizeProc*margin)*vresProcent, 1);
					
		/*TV->draw_box((xProcOffset + squareSizeProc*0.3f)*hresProcent, 
					(yProcOffset + squareSizeProc*0.3f)*vresProcent,
					(xProcOffset + squareSizeProc - squareSizeProc*0.3f)*hresProcent, 
					(yProcOffset + squareSizeProc  - squareSizeProc*0.3f)*vresProcent,1,0,0,1);*/
	
	}
	for(int row = 0; row < boardSize; row++){
		for(int column = 0; column < boardSize; column++){
			if(board[row][column] == _O){
				drawO(column+1, row+1);
			}else if(board[row][column] == _X){
				drawX(column+1, row+1);
			}
		}
	}
	
}
void Board::drawX(int column, int row){
	float margin = 0.1f;
	if(column >=1 && column <= boardSize && row >=1 && row <= boardSize){
		int xProcOffset = offset+(column-1)*squareSizeProc;
		int yProcOffset = offset+(row-1)*squareSizeProc;
		TV->draw_line((xProcOffset+squareSizeProc*margin)*hresProcent, (yProcOffset+squareSizeProc*margin)*vresProcent,
		(xProcOffset+squareSizeProc-squareSizeProc*margin)*hresProcent, (yProcOffset+squareSizeProc-squareSizeProc*margin)*vresProcent, 1);
		
		TV->draw_line((xProcOffset+squareSizeProc-squareSizeProc*margin)*hresProcent, (yProcOffset+squareSizeProc*margin)*vresProcent,
		(xProcOffset+squareSizeProc*margin)*hresProcent, (yProcOffset+squareSizeProc-squareSizeProc*margin)*vresProcent, 1);
	
	}
}
void Board::drawO(int column, int row){
	if(column >=1 && column <= boardSize && row >=1 && row <= boardSize){
		int xCenter = (offset+(column-1)*squareSizeProc + squareSizeProc/2)*hresProcent;
		int yCenter = (offset+(row-1)*squareSizeProc + squareSizeProc/2)*vresProcent;
		int radius;
		float margin = 0.1f;
		if(vresProcent < hresProcent){
			radius = vresProcent*(squareSizeProc/2 - squareSizeProc*margin);
		}else{
			radius = hresProcent*(squareSizeProc/2 - squareSizeProc*margin);
		}
		TV->draw_circle(xCenter, yCenter, radius, 1);
	}
}
void Board::setActive(int column, int row){
	//Serial.println(row);
	if(column >=1 && column <= boardSize && row >=1 && row <= boardSize){
		active = true;
		activeColumn = column;
		activeRow = row;
	}
}
void Board::untoActive(){
	active = false;
}
void Board::setX(int column, int row){
	if(column >=1 && column <= boardSize && row >=1 && row <= boardSize){
		board[row-1][column-1] = _X;
	}
}
void Board::setO(int column, int row){
	if(column >=1 && column <= boardSize && row >=1 && row <= boardSize){
		board[row-1][column-1] = _O;
	}
}
Piece Board::getPiece(int column, int row){
	if(column >=1 && column <= boardSize && row >=1 && row <= boardSize){
		return board[row-1][column-1];
	}
}
int Board::getActiveColumn(){
	return activeColumn;
}
int Board::getActiveRow(){
	return activeRow;
}
int Board::getBoardSize(){
	return boardSize;
}



