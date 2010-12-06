 
 
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

	// test working of filtering in general

	Image dst;
	
	Filter *meanFilter = Filter::CreateMean(7, 7);
	
	Image tmp;

	// ColorConversion::ToGrey(src, tmp);
	tmp = src;
	
	meanFilter->FilterImage(tmp, dst);

	// Save image
	
	res = dst.SavePPM(argv[1]);
	
	if(res) {
		cerr << "Couldn't write image " << argv[1] << "! " << endl;
		return 1;
	}



	cout << "Fertig! " << endl;
	
	return 0;
}

