
#include "Image.hh"
#include <fstream>

namespace Graphics2D {

using namespace std;

void Image::FillZero() {
	for(int i = 0; i < width_; i++) {
		for(int j = 0; j < height_; j++) {
			SetPixel(i, j, 0, 0);
			SetPixel(i, j, 1, 0);
			SetPixel(i, j, 2, 0);
		}
	}
}

inline void Image::SetPixel(const int &x, const int &y, const int &ch, const unsigned char &value) {
	data_[(width_*y + x)*3+ch] = value;
}

inline unsigned char Image::GetPixel(const int &x, const int &y, const int &ch) const {
	return data_[(width_*y + x)*3+ch];
}

int Image::LoadPPM(const std::string &filename) {
	
	
	return 0;
}

int Image::SavePPM(const std::string &filename) {
	
	ofstream out;
	
	out.open(filename);
	
	if(!out.is_open()) {
		return 1;
	}
	
	out << "P6" << endl;
	
	out << width_ << endl;
	out << height_ << endl;
	out << "255" << endl;
	
	
	
	out.close();
	
	return 0;
}

} 
