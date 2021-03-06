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

	Image img;

	string imgFile = "wasserturm-small.ppm";

	if(argc > 1) {
		imgFile = argv[1];
	}

	int result = img.LoadPPM(imgFile);

	if(result) {
		cerr << "Warning: Could not load image " << imgFile << "! " << endl;
		img.Init(512, 512);
		img.FillColor(Color(200, 200, 200));
	}

	Canvas2D canvas;
	canvas.Init(0, 0, img.GetWidth(), img.GetHeight());
	
	canvas.RegisterImage(&img);
	
	Painter thePainter(img);
	
	canvas.RegisterPainter(&thePainter);
		
	canvas.Start();
}
