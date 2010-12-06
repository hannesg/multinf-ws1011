 
#include <stdexcept> 
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
}

Filter *Filter::CreateMean(int width, int height) {
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

void Filter::FilterImage(const Image &src, Image &dst) const {
	
	// Abstand von Rahmen
	unsigned int dx = (width_-1)/2;
	unsigned int dy = (height_-1)/2;
	
	dst.Init(src.GetWidth(), src.GetHeight());
	
	int channel = 0;
	
	for(unsigned int x = dx; x < src.GetWidth()-dx; x++) {
		for(unsigned int y = dy; y < src.GetHeight() - dy; y++) {
			
			int sum = 0;
			
			for(int i = -dx; i <= dx; i++) {
				
				for(int j = -dy; j <= dy; j++) {
					sum += mask_[j][i]*src.GetPixel(i+x, j+y, channel);
				}
			}
			
			sum /= sum_;
			
			dst.SetPixel(x, y, sum, channel);
			
		}
	}
}

}












