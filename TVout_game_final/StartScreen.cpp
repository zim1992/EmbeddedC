// 
// 
// 

#include "StartScreen.h"
#include "start_img.h"

StartScreen::StartScreen(TVout *TV)
	:	TV(TV),
		hresProcent(TV->hres()/100.0),
		vresProcent(TV->vres()/100.0)
{
	char temp1[] = "Ultimate";
	char temp2[] = "Tic-Tac-Toe";
	textLine1Size = sizeof(temp1);
	textLine2Size = sizeof(temp2);
	for(int i = 0; i < textLine1Size; i++){
		textLine1[i] = temp1[i];
	}
	for(int i = 0; i < textLine2Size; i++){
		textLine2[i] = temp2[i];
	}
	boardSize = 3;
}

void StartScreen::draw(){
	TV->clear_screen();
	TV->select_font(font8x8);
	const int line1WidthPixels = 8*textLine1Size;
	const int line2WidthPixels = 8*textLine2Size;
	const int line1Offset = (TV->hres()-line1WidthPixels)/2;
	const int line2Offset = (TV->hres()-line2WidthPixels)/2;
	//TV->print_str(line1Offset, 0, textLine1);
	//TV->print_str(line2Offset, 16, textLine2);
	TV->print(line1Offset, 0, textLine1);
	TV->print(line2Offset, 9, textLine2);
	
	const int imgWidth = start_img[0];
	const int imgHeight = start_img[1];
	const int xImgOffset = (TV->hres() - imgWidth)/2;
	const int yImgOffset = 18;
	
	int xCount = xImgOffset;
	int yCount = yImgOffset;
	TV->bitmap(xImgOffset, yImgOffset, start_img);

	char str3x3[] = "3x3";
	char str4x4[] = "4x4"; 
	char str5x5[] = "5x5";
	const int yTotalPixels = yImgOffset+imgHeight;
	const int xStr3x3 = 10*hresProcent;
	const int xStr4x4 = 40*hresProcent;
	const int xStr5x5 = 70*hresProcent;
	const int yStr = yTotalPixels +15;
	TV->print(xStr3x3, yStr , str3x3);
	TV->print(xStr4x4, yStr , str4x4);
	TV->print(xStr5x5, yStr , str5x5);
	int yRectOffset = yTotalPixels +10;
	int xRectOffset;
	switch(boardSize){
		case 3:
			xRectOffset = xStr3x3 - 5;
		break;
		case 4:
			xRectOffset = xStr4x4 - 5;
		break;
		case 5:
			xRectOffset = xStr5x5 - 5;
		break;
	}
	const int rectWidth = 8*3+ 10;
	const int rectHeight = 8 + 10;
	TV->draw_rect(xRectOffset, yRectOffset, rectWidth, rectHeight, 1);
	
	

}
void StartScreen::select(int boardSize){
	if(boardSize >=3 && boardSize<=5){
		this->boardSize = boardSize;
	}
}
int StartScreen::getSelected(){
	 return boardSize;
}



