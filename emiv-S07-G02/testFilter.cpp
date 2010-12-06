/*
Gruppe: 02
Serie 07
Matthias Boehm, 895778
Hannes Georg, 850360
*/ 
 
#include <iostream>
#include <Image.hh>
#include <Filter.hh>
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

	return 0;
}

int main(int argc, char *argv[]) {
	
	argc--;
	argv++;
	
	if(argc < 1) {
		cout << "Usage: testFilter <input image>" << endl;
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
	
	// do filtering

	string outFilename = argv[0];
	// remove ".ppm"
	outFilename.erase(outFilename.rfind("."));

	Image dst;
	Image tmp;

	// ------------------- 1. Binomialfilter -------------------------------

	Filter *binomialFilter = Filter::CreateBinomial(7, 7);

	binomialFilter->FilterImage(src, dst);

	Save(dst, outFilename + "_binomial.ppm");

	// ------------------- 2. Mittelwertfilter -------------------------------
	
	
	Filter *meanFilter = Filter::CreateMean(7, 7);
		
	meanFilter->FilterImage(src, dst);

	Save(dst, outFilename + "_mean.ppm");

	// ------------------- 3. Mittelwertfilter, separabel ---------------------
	
	Filter *meanFilter1 = Filter::CreateMean(7, 1);
	Filter *meanFilter2 = Filter::CreateMean(1, 7);

	meanFilter1->FilterImage(src, tmp);
	meanFilter2->FilterImage(tmp, dst);

	Save(dst, outFilename + "_mean_separatable.ppm");

	// ------------------------------------------------------------------------

	cout << "Fertig! " << endl;
	
	return 0;
}

