 
/*
Gruppe: 02
Serie 12
Matthias Boehm, 895778
Hannes Georg, 850360
*/

#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <sys/time.h>
#include <Segmentation.hh>
#include <Image.hh>
#include <ColorConversion.hh>
#include <StructureTensor.hh>
#include <PrimitiveLine.hh>
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

// Hilsfunktion um Zeit zwischen zwei Zeitpunkten zu messen
/* Subtract the `struct timeval' values X and Y,
storing the result in RESULT.
Return 1 if the difference is negative, otherwise 0.  */
int	timeval_subtract (timeval *result, timeval *x, timeval *y)
{
	/* Perform the carry for the later subtraction by updating y. */
	if (x->tv_usec < y->tv_usec) {
		int nsec = (y->tv_usec - x->tv_usec) / 1000000 + 1;
		y->tv_usec -= 1000000 * nsec;
		y->tv_sec += nsec;
	}
	if (x->tv_usec - y->tv_usec > 1000000) {
		int nsec = (x->tv_usec - y->tv_usec) / 1000000;
		y->tv_usec += 1000000 * nsec;
		y->tv_sec -= nsec;
	}

	/* Compute the time remaining to wait.
	tv_usec is certainly positive. */
	result->tv_sec = x->tv_sec - y->tv_sec;
	result->tv_usec = x->tv_usec - y->tv_usec;

	/* Return 1 if result is negative. */
	return x->tv_sec < y->tv_sec;
}


int main(int argc, char *argv[]) {

	argc--;
	argv++;
	
	if(argc < 1) {
		cout << "Usage: houghTransform <input image> [resolution (optional)]" << endl;
		return 1;
	}
	
	// Load image
	Image src;
	int result = src.LoadPPM(argv[0]);
	
	if(result != 0) {
		cerr << "Cannot open file! " << endl;
		return 1;
	}

	int resolution = 1;
	if(argc > 1) {
		resolution = atoi(argv[1]);
	}
	
	// convert image if needed
	Image greySrc = src;
	if(src.GetColorModel() != ImageBase::cm_Grey) {
		ColorConversion::ToGrey(src, greySrc);
	} 

	// times
	timeval startStandard;
	timeval endStandard;
	timeval start1Fast;
	timeval start2Fast;
	timeval endFast;
	
	// ---------- standard hough transformation ------------
	vector<PrimitiveLine> lines;
	
	HoughTransform ht;
	gettimeofday(&startStandard, NULL);
	ht.StandardHoughTransform(greySrc, resolution, lines);
	gettimeofday(&endStandard, NULL);

	// save hough space
	FloatImage houghSpace = ht.GetHoughSpace();
	Image tmp;
	houghSpace.GetAsGreyImage(tmp);

	Save(tmp, string(argv[0]) + "_standardht_houghspace.ppm");

	// paint lines
	Image linesImg;

	ColorConversion::ToRGB(greySrc, linesImg);

	for(unsigned int i = 0; i < lines.size(); i++) {
		lines[i].SetColor(Color::red());
		lines[i].Draw(&linesImg);
	}

	Save(linesImg, string(argv[0]) + "_standardht_lines.ppm");

	// ---------- fast hough transformation ------------
	cout << endl;

	lines.clear();

	StructureTensor J;
	gettimeofday(&start1Fast, NULL);
	J.SetFromImage(greySrc);

	HoughTransform ht2;
	gettimeofday(&start2Fast, NULL);
	ht2.FastHoughTransform(J, resolution, lines);
	gettimeofday(&endFast, NULL);

	// save hough space
	houghSpace = ht2.GetHoughSpace();
	houghSpace.GetAsGreyImage(tmp);

	Save(tmp, string(argv[0]) + "_fastht_houghspace.ppm");

	// paint lines
	ColorConversion::ToRGB(greySrc, linesImg);

	for(unsigned int i = 0; i < lines.size(); i++) {
		lines[i].SetColor(Color::blue());
		lines[i].Draw(&linesImg);
	}

	Save(linesImg, string(argv[0]) + "_fastht_lines.ppm");

	// ---------- Ausgabe benoetigte Zeit -------------

	timeval standard;
	timeval fast1, fast2;

	timeval_subtract(&standard, &endStandard, &startStandard);
	timeval_subtract(&fast1, &endFast, &start1Fast);
	timeval_subtract(&fast2, &endFast, &start2Fast);

	long msecStandard = standard.tv_sec *1000 + standard.tv_usec/1000;
	long msecFast1 = fast1.tv_sec *1000 + fast1.tv_usec/1000;
	long msecFast2 = fast2.tv_sec *1000 + fast2.tv_usec/1000;

	cout << endl << endl;
	cout << "Standard hough transformation: " << msecStandard << " msec" << endl;
	cout << "Fast hough transformation (with Structure Tensor calculation): " << msecFast1 << " msec" << endl;
	cout << "Fast hough transformation (without Structure Tensor calculation): " << msecFast2 << " msec" << endl;

	cout << "Fertig! " << endl;
	
	return 0;
}
 
