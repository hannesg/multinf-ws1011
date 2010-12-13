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
#include <sys/time.h>
#include <cstdlib>

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
		cout << "Usage: testFilter <input image> [rank]" << endl;
		cout << "Creates files, that have as name the filename without extension of the " << endl;
		cout << "input image, plus some different text. " << endl;
		return 1;
	}
	
	int rank = 4;
	
	if(argc > 1) {
		rank = atoi(argv[1]);
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
	
	cout << "-------- Median-Filter -----------" << endl;
	
	Filter *meanFilter = Filter::CreateMean(7, 7);
	
	meanFilter->FilterImage(src, dst);

	Save(dst, outFilename + "_mean3x3.ppm");
	
	cout << "-------- Rank-Filter -----------" << endl;
	
	Filter::Rank3x3(src, dst, rank);
	
	char rankStr[10];
	sprintf(rankStr, "%i", rank);
	
	Save(dst, outFilename + "_rank_" + rankStr + "_3x3.ppm");

	cout << "------ GradX ----------- " << endl;
	
	Filter *gradXFilter = Filter::CreateGradX();
	
	gradXFilter->FilterImage(src, dst);
	
	Save(dst, outFilename + "_gradx.ppm");
	
	cout << "Fertig! " << endl;
	
	return 0;
}

