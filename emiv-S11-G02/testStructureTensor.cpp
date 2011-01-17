 
/*
Gruppe: 02
Serie 11
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
		cout << "Usage: testStructureTensor <input image> [optional: threashold]" << endl;
		
		return 1;
	}

	// set default (best) threshold
	float thres = 0.02;
	if(argc > 1) {
		thres = atof(argv[1]);
	}
	cout << "Threshold: " << thres << endl;
	
	// Load image
	Image src;
	int result = src.LoadPPM(argv[0]);
	
	if(result != 0) {
		cerr << "Cannot open file! " << endl;
		return 1;
	}
	
	// convert image if needed
	Image greySrc = src;
	if(src.GetColorModel() != ImageBase::cm_Grey) {
		ColorConversion::ToGrey(src, greySrc);
	} 
	
	// Initialization of structure tensor
	StructureTensor st;
	
	st.SetFromImage(greySrc);
	
	Image marked = src;

	st.FoerstnerDetector(thres, marked);

	char thresString[10];
	sprintf(thresString, "%.3f", thres);
	Save(marked, string(argv[0]) + string("_") + string(thresString) + string("_foerstner.ppm"));

	cout << "Fertig! " << endl;
	
	return 0;
}
 
