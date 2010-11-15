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

void Painter::Draw() {
}

string Painter::GetColorString() {
	return "";
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
}

}