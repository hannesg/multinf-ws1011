
#include <fstream>
#include "Image.hh"

using namespace std;

namespace Graphics2D {

Image::Image() : ImageBase() {
}

Image::Image(const Image &other) : ImageBase(other) {
}

Image &Image::operator = (const Image &other) {
	ImageBase::operator =(other);
	return *this;
}

Image::~Image() {
}

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
	
	out.open(filename.c_str());
	
	if(out.bad()) {
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
