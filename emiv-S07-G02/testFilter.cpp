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

// Weitere Hilfsfunktion, uebernommen aus der C GNU Library-Hilfe
/* Subtract the `struct timeval' values X and Y,
storing the result in RESULT.
Return 1 if the difference is negative, otherwise 0.  */
int	timeval_subtract (timeval *result, const timeval *x2, const timeval *y2)
{
	timeval y = *y2;
	timeval x = *x2;

	/* Perform the carry for the later subtraction by updating y. */
	if (x.tv_usec < y.tv_usec) {
		int nsec = (y.tv_usec - x.tv_usec) / 1000000 + 1;
		y.tv_usec -= 1000000 * nsec;
		y.tv_sec += nsec;
	}
	if (x.tv_usec - y.tv_usec > 1000000) {
		int nsec = (x.tv_usec - y.tv_usec) / 1000000;
		y.tv_usec += 1000000 * nsec;
		y.tv_sec -= nsec;
	}

	/* Compute the time remaining to wait.
	tv_usec is certainly positive. */
	result->tv_sec = x.tv_sec - y.tv_sec;
	result->tv_usec = x.tv_usec - y.tv_usec;

	/* Return 1 if result is negative. */
	return x.tv_sec < y.tv_sec;
}

// Hilfsfunktion
void displayPeriod(const timeval &t1, const timeval &t2) {

	timeval period;

	timeval_subtract(&period, &t2, &t1);

	// cout << "t1: " << t1.tv_sec << " " << t1.tv_usec << endl;
	// cout << "t2: " << t2.tv_sec << " " << t2.tv_usec << endl;

	double microSeconds = period.tv_sec * 1000000 + period.tv_usec;

	cout << "Needed " << microSeconds/1000 << " milliseconds. " << endl;
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
	timeval t1, t2;

	cout << "------------------- 1. Binomialfilter -------------------------------" << endl;

	Filter *binomialFilter = Filter::CreateBinomial(7, 7);

	gettimeofday(&t1, NULL);
	binomialFilter->FilterImage(src, dst);
	gettimeofday(&t2, NULL);

	displayPeriod(t1, t2);

	Save(dst, outFilename + "_binomial.ppm");

	cout << "------------------- 2. Mittelwertfilter -------------------------------" << endl;
	
	Filter *meanFilter = Filter::CreateMean(7, 7);
	
	gettimeofday(&t1, NULL);
	meanFilter->FilterImage(src, dst);
	gettimeofday(&t2, NULL);

	displayPeriod(t1, t2);

	Save(dst, outFilename + "_mean.ppm");

	cout << "------------------- 3. Mittelwertfilter, separabel ---------------------" << endl;
	
	Filter *meanFilter1 = Filter::CreateMean(7, 1);
	Filter *meanFilter2 = Filter::CreateMean(1, 7);

	gettimeofday(&t1, NULL);
	meanFilter1->FilterImage(src, tmp);
	meanFilter2->FilterImage(tmp, dst);
	gettimeofday(&t2, NULL);

	displayPeriod(t1, t2);

	Save(dst, outFilename + "_mean_separatable.ppm");

	// ------------------------------------------------------------------------

	cout << "Fertig! " << endl;
	
	return 0;
}

