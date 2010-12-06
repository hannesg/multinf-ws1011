 
 
#include <iostream>
#include <Image.hh>
#include <Filter.hh>
#include <ColorConversion.hh>

using namespace std;
using namespace Graphics2D;

int main(int argc, char *argv[]) {
	
	argc--;
	argv++;
	
	if(argc < 2) {
		cout << "Usage: testFilter <input image> <output image>" << endl;
		return 1;
	}
	
	Image src;
	
	// load image
	int res = src.LoadPPM(argv[0]);
	if(res) {
		cerr << "Couldn't read image " << argv[0] << "! " << endl;
		return 1;
	}
	
	// do filtering

	Image dst;
	
	Filter *meanFilter = Filter::CreateMean(7, 7);
	
	Image tmp;

	// ColorConversion::ToGrey(src, tmp);
	// tmp = src;
	ColorConversion::ToHSV(src, tmp);
	
	meanFilter->FilterImage(tmp, dst);

	Image tmp2;

	ColorConversion::ToRGB(dst, tmp2);
	// tmp2 = dst;
	
	// Save image
	
	res = tmp2.SavePPM(argv[1]);
	
	if(res) {
		cerr << "Couldn't write image " << argv[1] << "! " << endl;
		return 1;
	}



	cout << "Fertig! " << endl;
	
	return 0;
}

