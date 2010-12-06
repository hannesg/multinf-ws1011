/*
Gruppe: 02
Serie 07
Matthias Boehm, 895778
Hannes Georg, 850360
*/

#include <stdexcept>
#include <cassert>
#include <cmath>
#include "Filter.hh"

using namespace std;

namespace Graphics2D {


Filter::Filter(const vector<vector <int> > &mask) {

	mask_ = mask;
	
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
	
	for(unsigned int i = 0; i < height_; i++) {
		const vector<int> &row = mask[i];
		
		if(row.size() != width_) {
			throw out_of_range("No matrix");
		}
		
		for(unsigned int j = 0; j < width_; j++) {
			sum_ += mask_[i][j];
		}
	}

	printFilter();
}

Filter *Filter::CreateMean(int width, int height) {

	assert(width % 2 == 1 && height % 2 == 1);

	vector<int> row;
	vector<vector <int> > matrix;
	
	for(int i = 0; i < width; i++) {
		row.push_back(1);
	}
	
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

	// je nachdem, ob Grau- oder Buntbild, nur einen Channel betrachten (Graubild)
	// oder alle 3 (Buntbild)
	int c;
	int maxChannel;

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

	for(; c < maxChannel; c++) {

		for(unsigned int x = dx; x < src.GetWidth()-dx; x++) {
			for(unsigned int y = dy; y < src.GetHeight() - dy; y++) {

				int sum = 0;
			
				for(int i = -dx; i <= dx; i++) {
				
					for(int j = -dy; j <= dy; j++) {
						sum += mask_[j+dy][i+dx]*src.GetPixel(x+i, y+j, c);
					}
				}
		
				sum /= sum_;
			
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
		}
	}
}

}












