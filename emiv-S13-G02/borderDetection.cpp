 
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
		cout << "Usage: borderDetection <input image>" << endl;
		return 1;
	}

	// set default (best) threshold
	float thres2 = 0.00005;
	/* if(argc > 2) {
		thres2 = atof(argv[2]);
	} */

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
	
	// ------------------- a ----------------------
	// Initialization of structure tensor J for each pixel of src
	StructureTensor st;
	
	st.SetFromImage(greySrc);
	
	// detect points and borders (harris corner)
	// Image marked = src;
	// st.HarrisCornerDetector(thres2, marked);
	
	vector<Coordinate> corners;
	st.HarrisCornerDetector(thres2, corners);
	
	// print corners
	cout << corners.size() << " corners found! " << endl;
	
	for(unsigned int i = 0; i < corners.size(); i++) {
		cout << "    (" << corners[i].GetX() << ", " << corners[i].GetY() << ")" << endl;
	}

	cout << "Fertig Harris! " << endl;
	
	// the following commented stuff is for debugging
	/* Image label = st.GetLabelCornerImage();
	
	Save(label, "tmp_label.ppm");
	*/

	// save greyscale harris corner image
	/* Image greyHC;
	FloatImage hc = st.GetHarrisCornerImage();

	hc.GetAsGreyImage(greyHC);

	Save(greyHC, string(argv[0]) + string("_hc.ppm"));

	// save rgb picture
	Save(marked, string(argv[0]) + string("_marked.ppm"));
	*/
	
	// ------------------- b ----------------------

	cout << "Fertig! " << endl;
	
	return 0;
}
 
