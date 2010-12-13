/*
Gruppe: 02
Serie 07
Matthias Boehm, 895778
Hannes Georg, 850360
*/

#include <stdexcept>
#include <cassert>
#include <cmath>
#include <list>
#include "Filter.hh"
#include "ColorConversion.hh"

using namespace std;

namespace Graphics2D {

// Hilfsfunktion zur Berechnung von Binomialkoeffizienten
int binkoeff(int n, int k) {

	if(k == 0 || k == n) {
		return 1;
	} else {
		return binkoeff(n-1, k-1) + binkoeff(n-1, k);
	}
}


Filter::Filter(const vector<vector <int> > &mask, int scale = 1) {

	mask_ = mask;
	
	scale_ = scale;
	offset_ = 0;
	
	height_ = mask.size();
	
	// Fehler! 
	if(height_ == 0) {
		throw out_of_range("height 0");
	}
	
	width_ = mask[0].size();
	
	if(width_ == 0) {
		throw out_of_range("width 0");
	}
	
	// ungerade Hoehe/Breite notwendig!
	if(height_ % 2 != 1 || width_ % 2 != 1) {
		throw out_of_range("height/width even");
	}
	
	// Summe ermitteln
	sum_ = 0;
	
	int min = 0;
	int max = 0;
	
	for(unsigned int i = 0; i < height_; i++) {
		const vector<int> &row = mask[i];
		
		// all rows must have the same width
		if(row.size() != width_) {
			throw out_of_range("No matrix");
		}
		
		for(unsigned int j = 0; j < width_; j++) {
			sum_ += mask_[i][j];
			
			if(mask_[i][j] < 0) {
				min += mask_[i][j];
			} 
			if(mask_[i][j] > 0) {
				max += mask_[i][j];
			}
		}
	}
	
	min *= 255;
	max *= 255;
	
	offset_ = -min;
	
	

	// printFilter();
}

Filter *Filter::CreateMean(int width, int height) {

	assert(width % 2 == 1 && height % 2 == 1);

	vector<int> row;
	vector<vector <int> > matrix;
	
	// Einen Zeilenvektor erstellen
	for(int i = 0; i < width; i++) {
		row.push_back(1);
	}
	
	// Zeilenvektor kopieren
	for(int j = 0; j < height; j++) {
		matrix.push_back(row);
	}
	
	return new Filter(matrix);
}

Filter *Filter::CreateIdentity(int width, int height) {

	assert(width % 2 == 1 && height % 2 == 1);

	vector <vector <int> > result;

	for(int i = 0;  i < height; i++) {
		vector <int> row;
		
		for(int j = 0; j < width; j++) {

			/* Nur eine einzelne 1 in der Mitte, sonst nur 
			 * Nullen 
			 */
			if(i == (height-1)/2 && j == (width-1)/2) {
				row.push_back(1);
			} else {
				row.push_back(0);
			}
		}

		result.push_back(row);
	}

	return new Filter(result);
}

Filter *Filter::CreateGradX() {
	vector<int> row;
	
	row.push_back(-1);
	row.push_back(0);
	row.push_back(1);
	
	vector <vector<int> > matrix;
	matrix.push_back(row);
	
	return new Filter(matrix, 2);
}

Filter *Filter::CreateBinomial(int width) {

	assert(width % 2 == 1);

	// Die erste Zeile/Spalte erstellen
	vector<int> firstRow;

	for(int i = 0; i < width; i++) {
		firstRow.push_back(binkoeff(width-1, i));
	}

	vector< vector<int> > result;

	for(int j = 0; j < width; j++) {

		vector<int> row;

		// "Matrix-Multiplikation", um die inneren Werte zu ermitteln
		for(int i = 0; i < width; i++) {
			row.push_back(firstRow[i]*firstRow[j]);
		}

		result.push_back(row);
	}

	return new Filter(result);
}

void Filter::printFilter() const {

	cout << width_ << " " << height_ << " " << sum_ << endl;

	for(unsigned int j = 0; j < height_; j++) {
		for(unsigned int i = 0; i < width_; i++) {
			cout << mask_[j][i] << "\t";
		}
		cout << endl;
	}
}

void Filter::FilterImage(const Image &src, Image &dst) const {

	if(src.GetColorModel() == ImageBase::cm_HSV) {
		throw out_of_range("This color model is not supported! ");
	}
	
	// Abstand von Rahmen
	/*unsigned */int dx = (width_-1)/2;
	/*unsigned */int dy = (height_-1)/2;
	
	assert(dx >= 0 && dy >= 0);
	
	dst.Init(src.GetWidth(), src.GetHeight());
	dst.SetColorModel(src.GetColorModel());
	dst.FillZero();

	// je nachdem, ob Grau- oder Buntbild, nur einen Channel betrachten (Graubild)
	// oder alle 3 (Buntbild)
	int c;
	int maxChannel = -1;

	switch(src.GetColorModel()) {
	case ImageBase::cm_Grey:
		c = 0; 
		maxChannel = 1;
		break;
	case ImageBase::cm_RGB:
		c = 0;
		maxChannel = 3;
		break;
	case ImageBase::cm_HSV:
		c = 2;
		maxChannel = 3;
		break;
	}

	// Channel durchgehen 
	for(; c < maxChannel; c++) {

		// Bild durchgehen
		for(unsigned int x = dx; x < src.GetWidth()-dx; x++) {
			for(unsigned int y = dy; y < src.GetHeight() - dy; y++) {

				// Filter anwenden
				int sum = 0;
			
				for(int i = -dx; i <= dx; i++) {
				
					for(int j = -dy; j <= dy; j++) {
						sum += mask_[j+dy][i+dx]*src.GetPixel(x+i, y+j, c);
					}
				}
		
				if(sum_ != 0) {
					sum /= sum_;
				}
				
				sum += offset_;
				sum /= scale_;
			
				// je nachdem, ob Grau oder Bunt, einen oder drei channel wegschreiben
				switch(src.GetColorModel()) {
				case ImageBase::cm_Grey:
					dst.SetPixel(x, y, 0, sum);
					dst.SetPixel(x, y, 1, sum);
					dst.SetPixel(x, y, 2, sum);
					break;
				case ImageBase::cm_RGB:
					dst.SetPixel(x, y, c, sum);
					break;
				case ImageBase::cm_HSV:
					dst.SetPixel(x, y, 2, sum);
					dst.SetPixel(x, y, 0, src.GetPixel(x, y, 0));
					dst.SetPixel(x, y, 1, src.GetPixel(x, y, 1));
					break; 
				}
			}
		} /* Ende Bild durchgehen */
	} /* Ende channels durchgehen */
}

void Filter::MeanRecursive(const Image &src, Image &dst, unsigned int width, unsigned int height) {

	if(width % 2 != 1 || height % 2 != 1) {
		throw out_of_range("width/height even! ");
	}

	dst.Init(src.GetWidth(), src.GetHeight());
	dst.SetColorModel(src.GetColorModel());
	dst.FillZero();

	// Bild zu klein?
	if(src.GetWidth() < width || src.GetHeight() < height) {
		return;
	}

	int dx = (width-1)/2;
	int dy = (height-1)/2;

	// je nachdem, ob Grau- oder Buntbild, nur einen Channel betrachten (Graubild)
	// oder alle 3 (Buntbild)
	int c;
	int maxChannel = -1;

	switch(src.GetColorModel()) {
	case ImageBase::cm_Grey:
		c = 0; 
		maxChannel = 1;
		break;
	case ImageBase::cm_RGB:
		c = 0;
		maxChannel = 3;
		break;
	case ImageBase::cm_HSV:
		c = 2;
		maxChannel = 3;
		break;
	}

	// Channel durchgehen 
	for(; c < maxChannel; c++) {

		Image tmp;
		tmp.Init(src.GetWidth(), src.GetHeight());
		tmp.SetColorModel(src.GetColorModel());
		tmp.FillZero();

		// ------------ Horizontal filtern --------------
		for(unsigned int y = 0; y < src.GetHeight(); y++) {

			int sum = 0;

			// Startwert ermitteln
			for(unsigned int xs = 0; xs < width; xs++) {
				sum += src.GetPixel(xs, y, c);
			}

			// Zeile durchgehen
			for(unsigned int x = dx; x < src.GetWidth()-dx; x++) {

				// Filterwert berechnen
				int value = sum/width;

				// je nachdem, ob Grau oder Bunt, einen oder drei channel wegschreiben
				switch(src.GetColorModel()) {
				case ImageBase::cm_Grey:
					tmp.SetPixel(x, y, 0, value);
					tmp.SetPixel(x, y, 1, value);
					tmp.SetPixel(x, y, 2, value);
					break;
				case ImageBase::cm_RGB:
					tmp.SetPixel(x, y, c, value);
					break;
				case ImageBase::cm_HSV:
					tmp.SetPixel(x, y, 2, value);
					tmp.SetPixel(x, y, 0, src.GetPixel(x, y, 0));
					tmp.SetPixel(x, y, 1, src.GetPixel(x, y, 1));
					break; 
				}

				// Rekursion
				sum -= src.GetPixel(x-dx, y, c);
				// Ende beachten!
				if(x + dx + 1 < src.GetWidth()) {
					sum += src.GetPixel((x+dx+1) , y, c);
				}
			}
		} /* Ende horizontal filtern */

		// --------------- Vertikal filtern --------------------
		for(unsigned int x = 0; x < tmp.GetWidth(); x++) {

			int sum = 0;

			// Startwert ermitteln
			for(unsigned int ys = 0; ys < height; ys++) {
				sum += tmp.GetPixel(x, ys, c);
			}

			// Spalte durchgehen
			for(unsigned int y = dy; y < tmp.GetHeight()-dy; y++) {

				// Filterwert berechnen
				int value = sum/height;

				// je nachdem, ob Grau oder Bunt, einen oder drei channel wegschreiben
				switch(tmp.GetColorModel()) {
				case ImageBase::cm_Grey:
					dst.SetPixel(x, y, 0, value);
					dst.SetPixel(x, y, 1, value);
					dst.SetPixel(x, y, 2, value);
					break;
				case ImageBase::cm_RGB:
					dst.SetPixel(x, y, c, value);
					break;
				case ImageBase::cm_HSV:
					dst.SetPixel(x, y, 2, value);
					dst.SetPixel(x, y, 0, tmp.GetPixel(x, y, 0));
					dst.SetPixel(x, y, 1, tmp.GetPixel(x, y, 1));
					break; 
				}

				// Rekursion
				sum -= tmp.GetPixel(x, y-dy, c);
				// Ende beachten!
				if(y + dy + 1 < tmp.GetHeight()) {
					sum += tmp.GetPixel(x, y+dy+1, c);
				}
			}
		} /* Ende Vertikal filtern */

	} /* Ende channel durchgehen */

}

void Filter::Rank3x3(const Image &src2, Image &dst, int rank = 4) {
	
	int dx = 1;
	int dy = 1;
	
	if(rank < 0 || rank > 8) {
		throw out_of_range("rank");
	}
	
	Image src;
	
	if(src2.GetColorModel() == ImageBase::cm_RGB) {
		ColorConversion::ToGrey(src2, src);
	} else if(src2.GetColorModel() == ImageBase::cm_HSV) {
		throw exception();
	} else {
		src = src2;
	}
	
	dst.Init(src.GetWidth(), src.GetHeight());
	dst.SetColorModel(src.GetColorModel());
	dst.FillZero();
	
	vector<int> numbers;
	numbers.resize(9);
	
	for(unsigned int x = dx; x < src.GetWidth()-dx; x++) {
		for(unsigned int y = dy; y < src.GetHeight()-dy; y++) {
			
			numbers.clear();
			
			for(int i = -1; i <= 1; i++) {
				for(int j = -1; j <= 1; j++) {
					
					numbers.push_back(src.GetPixel(x+i, y+j, 0));
					
				}
			}
			
			sort(numbers.begin(), numbers.end());
			
			dst.SetPixel(x, y, 0, numbers[rank]);
			dst.SetPixel(x, y, 1, numbers[rank]);
			dst.SetPixel(x, y, 2, numbers[rank]);
			
		}
	}
	
}


}












