#include "slider.h"

slider::slider(string _name, int _x, int _y) {
	name = _name;
	x = _x;
	y = _y;
	
	// defaults
	w = 60;
	h = 300;
	faderX = x + 5;
	faderY = 0; // does nothing
	faderW = 50;
	faderH = 10;
	selected = 0;
	value = 0.0;
}

void slider::draw() {
	
	ofSetColor(50, 50, 50);
	ofRect(x, y, w, h);
	
	ofSetColor(255, 255, 255);
	ofDrawBitmapString( name, x + 10, y + 15 );
	
	ofSetColor(255, 255, 255);
	faderY = h * ( 1 - value) / 2.0;
	ofRect(faderX, faderY, faderW, faderH);

}

bool slider::mouseInsideFader(int mouseX, int mouseY) {
	if (mouseX > x and mouseX <= x + w and mouseY > y and mouseY <= y + h) {
		return true;
	} else {
		return false;
	}
}

void slider::setValue(float _value) {
	if (_value <= 1.0 and _value >= -1.0) {
		value = _value;
	}
}

void slider::setValueFromMouse(int mouseY) {
	float old_value = value;
	float new_value = (((float) (h - mouseY)) / (h / 2)) - 1.0;
	setValue(new_value);
}

float slider::getValue() {
	return value;
}

void slider::setSelected(int val) {
	selected = val;
}

bool slider::isSelected() {
	if (selected == 1) {
		return true;
	} else {
		return false;
	}
}