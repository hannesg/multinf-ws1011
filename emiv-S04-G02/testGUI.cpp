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

	// avoid warnings
	(void)argc, (void)argv;

	Canvas2D canvas;
	canvas.Init(0, 0, 512, 512);

	Image img(512, 512);

	string imgFile = "wasserturm-small.ppm";

	if(argc > 1) {
		imgFile = argv[1];
	}

	img.LoadPPM(imgFile);
	
	canvas.RegisterImage(&img);
	
	Painter thePainter(img);
	
	canvas.RegisterPainter(&thePainter);
		
	canvas.Start();
}
