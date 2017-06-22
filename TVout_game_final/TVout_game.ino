#include "StartScreen.h"
#include <TVout.h>
#include "Board.h"
#include <fontALL.h>
#define UP	4
#define DOWN 5
#define LEFT 6
#define RIGHT 7
#define SET 8
#define BACK 9
#define DEBOUNCE 50
#define NONE -1

#define START 50
#define BOARD 51
#define WIN	 52

#define FIRST 101
#define SECOND 102

TVout TV;
Board* board;
StartScreen* startscrn;
int previousState[] = {LOW, LOW, LOW, LOW, LOW};
//int currState[] = {HIGH, HIGH, HIGH, HIGH, HIGH};
int time[] = {0, 0, 0, 0, 0};
int button = NONE;
int reading;
int selected;
int screen = START;
int activeColumn;
int activeRow;
int player = FIRST;
int win = NONE;

bool testWin(int piece){
	activeColumn = board->getActiveColumn();
	activeRow = board->getActiveRow();
	int prieceCount = 0;
	for(int row = 1; row <= board->getBoardSize(); row++){
		if(board->getPiece(activeColumn, row) == piece){
			prieceCount++;
		}
	}
	if(prieceCount != board->getBoardSize()){
		prieceCount = 0;
		for(int column = 1; column <= board->getBoardSize(); column++){
			if(board->getPiece(column, activeRow) == piece){
				prieceCount++;
			}
		}
		if(prieceCount != board->getBoardSize()){
			prieceCount = 0;
			for(int i = 1; i <= board->getBoardSize(); i++){
				if(board->getPiece(i, i) == piece){
					prieceCount++;
				}
			}
			if(prieceCount != board->getBoardSize()){
				prieceCount = 0;
				int size = board->getBoardSize();
				for(int i = 1; i <= size; i++){
					if(board->getPiece((size+1) - i, i) == piece){
						prieceCount++;
					}
				}
				if(prieceCount != board->getBoardSize()){
					return false;
				}else{
					return true;
				}
				
			} else {
				return true;
			}
		} else {
			return true;
		}
	} else {
		return true;
	}
	return false;	
}
void setup()  {
	Serial.begin(9600);
	TV.begin(_PAL, 120, 96);
	
	startscrn = new StartScreen(&TV);
	for(int i = 4; i <= 9; i++){
		pinMode(i, INPUT_PULLUP);
	}
	TV.clear_screen();
	startscrn->draw();
}
void buttons(){
	static int i = 4;

	reading = digitalRead(i);
	if(reading == HIGH && previousState[i] == LOW && millis() - time[i] > DEBOUNCE){ //check if led state changed
		button = i;
		time[i] = millis(); // indicate time after state change
	}
	previousState[i] = reading; // indicate current state as previous
	i++;
	if(i >= 10){
		i = 4;
	}
}
void loop() {
	buttons();
	if(screen == START){
		switch(button){
			case LEFT:
				selected = startscrn->getSelected();
				if(selected != 3){
					startscrn->select(selected-1);
				}
				startscrn->draw();
				button = NONE;
				break;
			case RIGHT:
				selected = startscrn->getSelected();
				if(selected != 5){
					startscrn->select(selected+1);
				}
				startscrn->draw();
				button = NONE;
				break;
			case SET:
				board = new Board(&TV, startscrn->getSelected());
				board->draw();
				screen = BOARD;
				button = NONE;
				break; 
		}
	}else if(screen == BOARD){
		switch(button){
			case UP:
				activeColumn = board->getActiveColumn();
				activeRow = board->getActiveRow();
				if(activeRow != 1){
					board->setActive(activeColumn, activeRow-1);
					board->draw();
				}
				button = NONE;
			break;
			case DOWN:
				activeColumn = board->getActiveColumn();
				activeRow = board->getActiveRow();
				if(activeRow != board->getBoardSize() ){
					board->setActive(activeColumn, activeRow+1);
					board->draw();
				}
				button = NONE;
			break;
			case LEFT:
				activeColumn = board->getActiveColumn();
				activeRow = board->getActiveRow();
				if(activeColumn != 1 ){
					board->setActive(activeColumn-1, activeRow);
					board->draw();
				}
				button = NONE;			
			break;
			case RIGHT:
				activeColumn = board->getActiveColumn();
				activeRow = board->getActiveRow();
				if(activeColumn != board->getBoardSize() ){
					board->setActive(activeColumn+1, activeRow);
					board->draw();
				}
				button = NONE;
			break;
			case SET:
				if(player == FIRST){
					activeColumn = board->getActiveColumn();
					activeRow = board->getActiveRow();
					if(board->getPiece(activeColumn, activeRow) == _EMPTY){
						board->setX(activeColumn, activeRow);
						if(testWin(_X)){
							screen = WIN;
						}else{
							board->draw();
							player = SECOND;
						}
						
					}
				}else if(player == SECOND){
					activeColumn = board->getActiveColumn();
					activeRow = board->getActiveRow();
					if(board->getPiece(activeColumn, activeRow) == _EMPTY){
						board->setO(activeColumn, activeRow);
						player = FIRST;
						if(testWin(_O)){
							screen = WIN;
						}else{
							board->draw();
							player = FIRST;
						}
					}
				}
				button = NONE;
			break;
			case BACK:
				button = NONE;
			break;
		}
		
	}else if(screen == WIN){
		switch(player){
			case FIRST:
				TV.clear_screen();
				TV.print(0, 0, "first player win");
				button = NONE;
				player = -1;
				break;
			case SECOND:
				TV.clear_screen();
				TV.print(0, 0, "second player win");
				button = NONE;
				player = -1;
				break;
		}
	}
}
