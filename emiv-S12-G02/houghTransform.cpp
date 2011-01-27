 
/*
Gruppe: 02
Serie 12
Matthias Boehm, 895778
Hannes Georg, 850360
*/

#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <Segmentation.hh>
#include <Image.hh>
#include <ColorConversion.hh>
#include <StructureTensor.hh>
#include <PrimitiveLine.hh>
#include <HoughTransform.hh>

using namespace std;
using namespace Graphics2D;

// Hilfsfunktion
int Save(const Image &img, const string &filename) {
	// Save image
	int res = img.SavePPM(filename);

	if(res) {
		cerr << "Couldn't write image " << filename << "! " << endl;
		return 1;
	} 

	cout << "Stored " << filename << "! " << endl;

	return 0;
}

int main(int argc, char *argv[]) {

	argc--;
	argv++;
	
	if(argc < 1) {
		cout << "Usage: houghTransform <input image> [resolution (optional)]" << endl;
		return 1;
	}
	
	// Load image
	Image src;
	int result = src.LoadPPM(argv[0]);
	
	if(result != 0) {
		cerr << "Cannot open file! " << endl;
		return 1;
	}

	int resolution = 1;
	if(argc > 1) {
		resolution = atoi(argv[1]);
	}
	
	// convert image if needed
	Image greySrc = src;
	if(src.GetColorModel() != ImageBase::cm_Grey) {
		ColorConversion::ToGrey(src, greySrc);
	} 
	
	// ---------- standard hough transformation ------------
	vector<PrimitiveLine> lines;
	
	HoughTransform ht;
	ht.StandardHoughTransform(greySrc, resolution, lines);

	// save hough space
	FloatImage houghSpace = ht.GetHoughSpace();
	Image tmp;
	houghSpace.GetAsGreyImage(tmp);

	Save(tmp, string(argv[0]) + "_standardht_houghspace.ppm");

	// paint lines
	Image linesImg;

	ColorConversion::ToRGB(greySrc, linesImg);

	for(unsigned int i = 0; i < lines.size(); i++) {
		lines[i].SetColor(Color::red());
		lines[i].Draw(&linesImg);
	}

	Save(linesImg, string(argv[0]) + "_standardht_lines.ppm");

	// ---------- fast hough transformation ------------

	lines.clear();

	StructureTensor J;
	J.SetFromImage(greySrc);

	HoughTransform ht2;
	ht2.FastHoughTransform(J, resolution, lines);

	// save hough space
	houghSpace = ht2.GetHoughSpace();
	houghSpace.GetAsGreyImage(tmp);

	Save(tmp, string(argv[0]) + "_fastht_houghspace.ppm");

	// paint lines
	ColorConversion::ToRGB(greySrc, linesImg);

	for(unsigned int i = 0; i < lines.size(); i++) {
		lines[i].SetColor(Color::blue());
		lines[i].Draw(&linesImg);
	}

	Save(linesImg, string(argv[0]) + "_fastht_lines.ppm");

	cout << "Fertig! " << endl;
	
	return 0;
}
 
