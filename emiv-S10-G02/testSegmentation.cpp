 
#include <iostream>
#include <string>
#include <Segmentation.hh>
#include <Image.hh>

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
		cout << "Usage: testSegmentation <input image>" << endl;
		cout << "Creates files tannenbaum_labeled.ppm, tannenbaum_labeled_and_closed" << endl 
			<< "and tannenbaum_contours.ppm" << endl;
		return 1;
	}
	
	Image src;
	
	// load image
	int res = src.LoadPPM(argv[0]);
	if(res) {
		cerr << "Couldn't read image " << argv[0] << "! " << endl;
		return 1;
	}
	
	// Aufgabe 1 a
	Segmentation s(src);
	
	// Tannenbaum
	s.AddHueSegment(80, 80, 86);
	// Mond
	s.AddHueSegment(160, 40, 44);
	// Geschenk
	s.AddHueSegment(240, 210, 215);
	s.AddHueSegment(240, 125, 130);
	
	Image result1;
	s.GetLabelImage(result1);
	
	Save(result1, "tannenbaum_labeled.ppm");

	// Aufgabe 1 b
	Segmentation s2(result1);
	s2.ClosingOperation();
	
	Image result2;
	s2.GetLabelImage(result2);
	Save(result2, "tannenbaum_labeled_and_closed.ppm");
	

	// Aufgabe 2
	string labels[] = { "Tree", "Moon", "Present" };
	
	vector<int> freemanCode[3];
	Coordinate firstPixel[3];
	Color colors[] = { Color::yellow(), Color::red(), Color::black() };
	
	for(int i = 80; i <= 240; i+= 80) {
		
		int area;
		Coordinate center;
		s.GetCenterAndArea(i, center, area);
		
		cout << labels[i/80-1] << " is located at (" 
				<< center.GetX() << ", " << center.GetY() << ") with area " 
				<< area << endl;
		
		// b und c
		s.GetFreemanCode(i, firstPixel[i/80-1], freemanCode[i/80-1]);

		// debugging
		/* for(unsigned int j = 0; j < freemanCode[i/80-1].size(); j++) {
			cout << freemanCode[i/80-1][j] << " ";
		}
		cout << endl; */

		s.DrawContourFreeman(firstPixel[i/80-1], freemanCode[i/80-1], colors[i/80-1], 
			src);
		
		// Aufgabe 9.1
		float circumference = s.GetCircumference(freemanCode[i/80-1]);
		float roundness = pow(circumference, 2)/area;
		
		float rectMin = 15.5;
		float rectMax = 19.0;
	
		float circleMin = 13.5;
		float circleMax = 14.3;
	
		float treeMin = 40;
		float treeMax = 70;
	
		cout << "Object is a ";
		if(rectMin <= roundness && roundness <= rectMax) {
			cout << "rectangle";
		} else if(circleMin <= roundness && roundness <= circleMax) {
			cout << "circle"; 
		} else if(treeMin <= roundness && roundness <= treeMax) {
			cout << "tree";
		} else {
			cout << "unknown";
		}
		cout << endl;
		cout << "Features: Circumference " << circumference << 
				" Roundness: " << roundness << endl;
	}

	Save(src, "tannenbaum_contours.ppm");
	
	
	
 	return 0;
}
