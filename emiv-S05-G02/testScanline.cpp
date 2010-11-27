/*
Gruppe: 02
Serie 05
Matthias Boehm, 895778
Hannes Georg, 850360
*/

#include <iostream>
#include <Image.hh>
#include <PrimitivePoint.hh>
#include <PrimitiveLine.hh>
#include <PrimitivePolygon.hh>
#include <PrimitiveBox.hh>

using namespace std;
using namespace Graphics2D;

/* Konstanten fuer leeres Image */
const int WIDTH = 200;
const int HEIGHT = 100;

void paintSomePolygons(Image &img) {

	PrimitivePolygon p1, p2;
	vector<Coordinate> cs1;
	cs1.push_back(Coordinate(4, 4));
	cs1.push_back(Coordinate(7, 6));
	cs1.push_back(Coordinate(13, 5));
	cs1.push_back(Coordinate(11, 13));
	cs1.push_back(Coordinate(7, 9));
	cs1.push_back(Coordinate(2, 13));
	cs1.push_back(Coordinate(4, 4));

	for(unsigned int i = 0; i < cs1.size(); i++) {
		cs1[i] *= 3;
	}

	p1.SetCoordinates(cs1);

	p1.Draw(&img);
}

int main(int argc, char *argv[]) {

	/* erstes Argument (Programmname) ignorieren */
	argc--;
	argv++;

	if(argc == 0) {
		cout << "Usage: " << endl << "testScanline <Output-File> " << endl;
		cout << " loads an empty picture and paints some points, stores result in <Output-File> " << endl;
		cout << " or " << endl;
		cout << "testScanline <Input-File> <Output-File> " << endl;
		cout << " loads <Input-File>, paints some points, stores result in <Output-File> " << endl;
		return 1;
	}

	Image img;
	int OutputFileIndex = 0;
	
	if(argc == 1) {
		/* Leeres Bild */
		img.Init(WIDTH, HEIGHT);

		/* Weiss machen */
		for(unsigned int i = 0; i < img.GetWidth(); i++) {
			for(unsigned int j = 0; j < img.GetHeight(); j++) {
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

	/* Fuere Tests durch */
	paintSomePolygons(img);

	cout << "Fertig! " << endl;	

	/* Speichere Bild */
	if(img.SavePPM(argv[OutputFileIndex]) != 0) {
		cerr << "Cannot save file! " << endl;
		return 1;
	}

	return 0;
}
