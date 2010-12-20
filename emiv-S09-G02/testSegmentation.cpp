 
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

	return 0;
}

int main(int argc, char *argv[]) {

	argc--;
	argv++;
	
	if(argc < 1) {
		cout << "Usage: testSegmentation <input image>" << endl;
		cout << "Creates files, that have as name the filename without extension of the " << endl;
		cout << "input image, plus some different text. " << endl;
		return 1;
	}
	
	Image src;
	
	// load image
	int res = src.LoadPPM(argv[0]);
	if(res) {
		cerr << "Couldn't read image " << argv[0] << "! " << endl;
		return 1;
	}
	
	Segmentation s(src);
	
	// Tannenbaum
	s.AddHueSegment(80, 80, 86);
	// Mond
	s.AddHueSegment(160, 40, 44);
	// Geschenk
	s.AddHueSegment(240, 210, 215);
	s.AddHueSegment(240, 125, 130);
	
	s.ClosingOperation();
	
	Image result1;
	
	s.GetLabelImage(result1);
	
	Save(result1, "tannenbaum_labeled.ppm");
	
	string labels[] = { "Tannenbaum", "Mond", "Geschenk" };
	
	for(int i = 80; i <= 240; i+= 80) {
		
		int area;
		Coordinate center;
		s.GetCenterAndArea(i, center, area);
		
		cout << labels[i/80-1] << " is located at " 
				<< center.GetX() << " " << center.GetY() << " with area " 
				<< area << endl;
	}
	
 	return 0;
}
