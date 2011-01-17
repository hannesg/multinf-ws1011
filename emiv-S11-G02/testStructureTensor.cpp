 
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
		cout << "Usage: testStructureTensor <input image> [optional: threashold foerstner] [optional: threshold harris corner]" << endl;
		cout << " If threshold not specified, uses best threshold" << endl;
		return 1;
	}

	// set default (best) threshold
	float thres1 = 0.02;
	if(argc > 1) {
		thres1 = atof(argv[1]);
	}
	cout << "Foerster Threshold: " << thres1 << endl;

	// set default (best) threshold
	float thres2 = 0.0;
	if(argc > 2) {
		thres2 = atof(argv[2]);
	}

	cout << "Harris Corner Threshold: " << thres2 << endl;
	
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
	
	// Initialization of structure tensor J for each pixel of src
	StructureTensor st;
	
	st.SetFromImage(greySrc);
	
	// detect points and borders (foerstner)
	Image marked = src;

	st.FoerstnerDetector(thres1, marked);

	cout << "Fertig foerestner! " << endl;

	// detect points and borders (harris corner)
	
	st.HarrisCornerDetector(thres2, marked);

	cout << "Fertig Harris! " << endl;

	// save picture
	char thresString[30];
	sprintf(thresString, "_%.3f_%.3f", thres1, thres2);
	Save(marked, string(argv[0]) + string(thresString) + string("_marked.ppm"));

	
	return 0;
}
 
