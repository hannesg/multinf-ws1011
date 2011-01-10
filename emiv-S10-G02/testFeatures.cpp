 
#include <iostream>
#include <string>
#include <cmath>
#include <Segmentation.hh>
#include <Image.hh>
#include <ColorConversion.hh>

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
		cout << "Usage: testFeatures <input image>" << endl;
		
		return 1;
	}
	
	Image src;
	int result = src.LoadPPM(argv[0]);
	
	if(result != 0) {
		cerr << "Cannot open file! " << endl;
		return 1;
	}
	
	if(src.GetColorModel() != ImageBase::cm_Grey) {
		Image tmp;
		ColorConversion::ToGrey(src, tmp);
		
		src = tmp;
	}
	
	Segmentation s(src);
	
	int area;
	Coordinate center;
	
	s.GetCenterAndArea(255, center, area);
	
	vector<int> freemanCode;
	Coordinate firstPoint;
	
	s.GetFreemanCode(255, firstPoint, freemanCode);
	
	float circumference = s.GetCircumference(freemanCode);
	
	float roundness = pow(circumference, 2)/area;
	
	// Ausgabe
	
	cout << "Object has its center at " << center.GetX() << ", " << center.GetY() 
			<< " with area " << area << endl;
	cout << "Object has roundness of " << roundness << endl;
	cout << "Object has circumference of " << circumference << endl;
	
	
	return 0;
}
 
