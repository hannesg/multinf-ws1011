/*
Gruppe: 02
Serie 04
Matthias Boehm, 895778
Hannes Georg, 850360
*/

#include <iostream>
#include "Painter.hh"

using namespace std;

namespace Graphics2D {

Painter::Painter() {
	currentColor_ = Color::black();
}

void Painter::Draw() {
}

string Painter::GetColorString() {
	return currentColor_.GetName();
}

string Painter::GetString() {
	return "";
}

void Painter::MouseDown(int x, int y) {
	cerr << "MouseDown " << x << " " << y << endl;
}

void Painter::MouseUp(int x, int y) {
	cerr << "MouseUp " << x << " " << y << endl;
}

void Painter::MouseMove(int x, int y) {
	cerr << "MouseMove " << x << " " << y << endl;
}

void Painter::KeyPressed(unsigned char ch, int x, int y) {
	cerr << "KeyPressed " << ch << " " << x << " " << y << endl;
	switch(ch) {
	case '1':
		currentColor_ = Color::black();
		break;
	case '2':
		currentColor_ = Color::red();
		break;
	case '3':
		currentColor_ = Color::green();
		break;
	case '4':
		currentColor_ = Color::blue();
		break;
	default:
		break;
	}
}

}