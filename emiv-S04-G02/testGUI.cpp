/*
Gruppe: 02
Serie 04
Matthias Boehm, 895778
Hannes Georg, 850360
*/

#include <iostream>
#include <Image.hh>
#include <Canvas2D.hh>
#include <Painter.hh>

using namespace Graphics2D;

int main(int argc, char *argv[]) {

	Canvas2D canvas;
	canvas.Init(0, 0, 512, 512);

	Image img(512, 512);

	img.LoadPPM("wasserturm-small.ppm");
	
	canvas.RegisterImage(&img);
	
	Painter thePainter;
	
	canvas.RegisterPainter(&thePainter);
	
	// painter.AddPrimitive(...); 
	
	
	canvas.Start();
}
