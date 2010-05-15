#ifndef _SLIDER
#define _SLIDER

#include <string>
#include "ofMain.h"

class slider {
	
public:
	slider(string _name, int _x, int _y);
	void draw();
	bool mouseInsideFader(int mouseX, int mouseY);
	void setValue(float _value);
	void setValueFromMouse(int mouseY);
	float getValue();
	void setSelected(int val);
	bool isSelected();
	
	ofTrueTypeFont TTF;
	string name;
	
	int x;
	int y;
	int h;
	int w;
	
	int faderX;
	int faderY;
	int faderW;
	int faderH;
	
	float value;
	int selected;
	
};

#endif	
