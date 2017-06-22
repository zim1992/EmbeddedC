// StartScreen.h

#ifndef _STARTSCREEN_h
#define _STARTSCREEN_h
#include "Drawable.h"
#include <TVout.h>
#include <fontALL.h>

class StartScreen : public Drawable{
	protected:
		char textLine1[20];
		char textLine2[20];
		int textLine1Size;
		int textLine2Size;
		TVout *TV;
		const float hresProcent;
		const float vresProcent;
		int boardSize;
	public:
		StartScreen(TVout *TV);
		void draw();
		void select(int boardSize);
		int getSelected();
};


#endif

