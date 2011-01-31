 
/*
Gruppe: 02
Serie 13
Hannes Georg, 850360
Matthias Boehm, 895778
*/

#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <map>
#include <cassert>
#include <Segmentation.hh>
#include <Image.hh>
#include <ColorConversion.hh>
#include <StructureTensor.hh>
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

// Hilfsklassen
class lessCoordinate {

public:
	bool operator() (const Coordinate &c1, const Coordinate &c2) {

		if(c1.GetYAsFloat() == c2.GetYAsFloat()) {
			return c1.GetXAsFloat() < c2.GetXAsFloat();
		} else {
			return c1.GetYAsFloat() < c2.GetYAsFloat();
		}
	}
};

class lessLine {

public:
	bool operator () (const PrimitiveLine &l1, const PrimitiveLine &l2) {

		lessCoordinate lc;

		if(l1.GetStartingPoint() == l2.GetStartingPoint()) {
			return lc (l1.GetEndingPoint(), l2.GetEndingPoint());
		} else {
			return lc (l1.GetStartingPoint(), l2.GetStartingPoint());
		}
	}

};

int main(int argc, char *argv[]) {

	argc--;
	argv++;
	
	if(argc < 1) {
		cout << "Usage: borderDetection <input image>" << endl;
		return 1;
	}

	// enables debugging messages
	const bool debugging = true;

	// set default (best) threshold
	const float thres2 = 0.00005;
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
		// Punkte blau faerben
		src.SetPixel(corners[i].GetX(), corners[i].GetY(), 0, Color::blue().GetR());
		src.SetPixel(corners[i].GetX(), corners[i].GetY(), 1, Color::blue().GetG());
		src.SetPixel(corners[i].GetX(), corners[i].GetY(), 2, Color::blue().GetB());
	}

	cout << "Fertig Harris! " << endl;
	
	//-----------------------------------------------
	// the following commented stuff is for debugging

	/* Image label = st.GetLabelCornerImage();
	
	Save(label, "tmp_label.ppm");
	*/

	// save greyscale harris corner image
	/* Image greyHC;
	FloatImage hc = st.GetHarrisCornerImage();

	hc.GetAsGreyImage(greyHC);

	Save(greyHC, string(argv[0]) + string("_hc.ppm"));
	*/

	// save rgb picture
	/* Image marked = src;
	st.HarrisCornerDetector(thres2, marked);
	Save(marked, string(argv[0]) + string("_corners_marked.ppm")); *
	*/
	//-----------------------------------------------
	
	// ------------------- b ----------------------

	HoughTransform ht;
	vector<PrimitiveLine> lines;
	ht.StandardHoughTransform(greySrc, 1, lines);

	for(vector<PrimitiveLine>::iterator it = lines.begin(); it != lines.end(); it++) {
		it->SetColor(Color::red());
		it->Draw(&src);
	}

	// ------------------- c + d ----------------------

	typedef map<Coordinate, vector<PrimitiveLine>, lessCoordinate > clines;
	typedef map<PrimitiveLine, vector<Coordinate>, lessLine > linesc;

	clines cornerLines;
	linesc lineCorners;

	// Gehe alle Ecken und Linien durch
	for(unsigned int i = 0; i < corners.size(); i++) {
		for(unsigned int j = 0; j < lines.size(); j++) {

			float dist = lines[j].Distance(corners[i]);

			// print distance
			if(debugging) {
				cout << "Distance corner " << i << ", line " << j << ": " << dist << endl;
			}

			if(dist < 10.0) {
				// do association
				cornerLines[corners[i]].push_back(lines[j]);
				lineCorners[lines[j]].push_back(corners[i]);
			}

		}
		cout << endl;

	}

	if(debugging) {
		// Print associations point -> line
		cout << "associations: " << endl;
		for(clines::iterator it = cornerLines.begin(); it != cornerLines.end(); it++) {
			cout << "Point " << it->first << ": " << endl;
			for(unsigned int i = 0; i < it->second.size(); i++) {
				cout << "    Line: " << it->second[i] << endl;
			}
		}

		cout << endl;
		// Print associations line -> point
		for(linesc::iterator it = lineCorners.begin(); it != lineCorners.end(); it++) {
			cout << "Line " << it->first;
			for(unsigned int i = 0; i < it->second.size(); i++) {
				cout << "    Point: " << it->second[i] << endl;
			}
		}
	}

	// ------------------------- e -----------------------------

	cout << "Kantenschnittpunkte: " << endl;
	for(clines::iterator it = cornerLines.begin(); it != cornerLines.end(); it++) {
		assert(it->second.size() == 2);

		PrimitiveLine l1 = it->second[0];
		PrimitiveLine l2 = it->second[1];
		Coordinate c;

		bool res = l1.Intersection(l2, c);

		if(!res) {
			cerr << "Warning! Lines are parallel! " << endl;
		} else {
			cout << "Intersection: " << c;
		}

		float distance = (it->first - c).length();

		cout << "\tDistance to edge: " << distance << endl;
	}

	// ---------------------------------------------------------------------

	// Save image
	Save(src, string(argv[0]) + "_new.ppm");

	cout << "Fertig! " << endl;
	
	return 0;
}
 
