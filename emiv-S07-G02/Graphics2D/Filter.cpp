 
 
#include "Filter.hh"

namespace Graphics2D {


Filter::Filter(const vector<vector <int> > &mask) {

	mask_ = mask;
	
	height_ = mask.size();
	
	// Fehler! 
	if(height_ == 0) {
		throw exception();
	}
	
	width_ = mask[0].size();
	
	if(width_ == 0) {
		throw exception();
	}
	
	// Summe ermitteln
	sum_ = 0;
	
	for(unsigned int i = 0; i < height_; i++) {
		const vector<int> &row = mask[i];
		
		if(row.size() != width_) {
			throw exception();
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
	
	dst = src;
	
}

}












