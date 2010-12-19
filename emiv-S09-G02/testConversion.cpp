/*
Gruppe: 02
Serie 05
Matthias Boehm, 895778
Hannes Georg, 850360
*/

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <Image.hh>
#include <ColorConversion.hh>


using namespace std;
using namespace Graphics2D;

int main(int argc, char *argv[]) {

	/* erstes Argument (Programmname) ignorieren */
	argc--;
	argv++;

	if(argc == 0) {
		cout << "usage: testConversion <image file> [number of conversions]" << endl;
		return 0;
	}

	/* Bild laden */
	Image img;

	string imgFile = argv[0];

	int result = img.LoadPPM(imgFile);

	if(result) {
		cerr << "Could not load image " << imgFile << "! " << endl;
		return 1;
	}

	int numOfConversions = 1;
	if(argc > 1) {
		numOfConversions = atoi(argv[1]);
	}

	/* Konvertieren des Bildes */

	Image orig = img;

	Image tmp;

	for(int i = 0 ; i < numOfConversions; i++) {
		ColorConversion::ToHSV(img, tmp);
		ColorConversion::ToRGB(tmp, img);
	}

	/* Bestimme Differenzen */
	int r[256], g[256], b[256];
	for(int i = 0; i < 256; i++) {
		r[i] = g[i] = b[i] = 0;
	}

	for(unsigned int x = 0; x < img.GetWidth(); x++) {
		for(unsigned int y = 0; y < img.GetHeight(); y++) {
			int diffr = abs(img.GetPixel(x, y, 0) - orig.GetPixel(x, y, 0));
			int diffg = abs(img.GetPixel(x, y, 1) - orig.GetPixel(x, y, 1));
			int diffb = abs(img.GetPixel(x, y, 2) - orig.GetPixel(x, y, 2));

			r[diffr]++;
			g[diffg]++;
			b[diffb]++;
		}
	}

	int *diff[3] = { r, g, b };

	for(int d = 0; d < 3; d++) {
		cout << "Anzahl von Vorkommen von Differenzen im ";
		switch(d) {
		case 0:
			cout << "Rot-";
			break;
		case 1:
			cout << "Gruen-";
			break;
		case 2:
			cout << "Blau-";
			break;
		}
		cout << "Kanal: " << endl;

		bool notnull = false;
		for(int i = 255; i >= 0; i--) {
			if(diff[d][i] != 0) {
				notnull = true;
			}
			if(notnull) {
				cout << setw(3) << i << ":" << setw(8) << diff[d][i] << "\t" << 
					setw(10) << setiosflags(ios::fixed) << setprecision(2) << 
					diff[d][i]*100.0/(img.GetWidth()*img.GetHeight()) << " %" << endl;
			}
		}
	}
	
	/* Bestimme Differenzbild */
	// Image diff

	/* Speichere Bild */
	/* if(img.SavePPM(argv[OutputFileIndex]) != 0) {
		cerr << "Cannot save file! " << endl;
		return 1;
	} */

	cout << "Fertig! " << endl;

	return 0;
}
