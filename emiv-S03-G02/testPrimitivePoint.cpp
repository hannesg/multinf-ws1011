
#include <iostream>
#include <Image.hh>
#include <PrimitivePoint.hh>

using namespace std;
using namespace Graphics2D;

/* Konstanten fuer leeres Image */
const int WIDTH = 200;
const int HEIGHT = 100;

void paintSomePoints(Image &img) {

	/* Liste von Test-Punkten */
	PrimitivePoint ps[] = {
		PrimitivePoint(0, 0, Color::black()), 
		PrimitivePoint(1, 1, Color::white()), 
		PrimitivePoint(10, 10, Color::red()), 
		PrimitivePoint(20, 10, Color::green()), 
		PrimitivePoint(10, 20, Color::blue()), 
		PrimitivePoint(5, 5, Color::black()), 
		PrimitivePoint(5, 5, Color::yellow()), 
		PrimitivePoint(img.GetWidth()-1, img.GetHeight()-1, Color::black()), 
		/* testen, was passiert, wenn Punkt nicht im Bild! */
		PrimitivePoint(img.GetWidth(), 0, Color::black())
	};

	/* Testpunkte zeichnen */
	for(int i = 0; i < sizeof(ps)/sizeof(PrimitivePoint); i++) {
		try {
			ps[i].Draw(&img);
		} catch(exception e) {
			cerr << "Point " << ps[i] << " not in image! " << endl;
		}
	}


}

int main(int argc, char *argv[]) {

	/* erstes Argument (Programmname) ignorieren */
	argc--;
	argv++;

	if(argc == 0) {
		cout << "Usage: " << endl << "testPrimitivePoint <Output-File> " << endl;
		cout << " loads an empty picture and paints some points, stores result in <Output-File> " << endl;
		cout << " or " << endl;
		cout << "testPrimitivePoint <Input-File> <Output-File> " << endl;
		cout << " loads <Input-File>, paints some points, stores result in <Output-File> " << endl;
		return 1;
	}

	Image img;
	int OutputFileIndex;
	
	if(argc == 1) {
		/* Leeres Bild */
		img.Init(WIDTH, HEIGHT);

		/* Weiss machen */
		for(int i = 0; i < img.GetWidth(); i++) {
			for(int j = 0; j < img.GetHeight(); j++) {
				img.SetPixel(i, j, 0, 255);
				img.SetPixel(i, j, 1, 255);
				img.SetPixel(i, j, 2, 255);
			}
		}
		
		OutputFileIndex = 0;
		
	} else if(argc > 1) {
		/* Lade Bild */
		if(img.LoadPPM(argv[0]) != 0) {
			cerr << "Cannot open file! " << endl;
			return 1;
		}
		OutputFileIndex = 1;
	}

	paintSomePoints(img);

	if(img.SavePPM(argv[OutputFileIndex]) != 0) {
		cerr << "Cannot save file! " << endl;
		return 1;
	}

	return 0;
}