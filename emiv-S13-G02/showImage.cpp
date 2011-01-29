#include <iostream>
#include <vector>
#include <Graphics2DBase/Canvas2D.hh>
#include <Graphics2D/Image.hh>
#include <Graphics2D/PrimitiveLine.hh>
#include <Graphics2D/Coordinate.hh>

using namespace std;
using namespace Graphics2D;

/**
 * 
 * example program just showing an image
 * @author fkellner 11/10
 */
int main(int argc, char **argv) {
  
  if (argc!=2) {
    cout << "usage: " << argv[0] << " background.ppm" << endl;
    return 0;
  }
  
  Image image;
  image.LoadPPM(argv[1]);

  // create 2d window
  Canvas2D c2d;
  c2d.Init(100,100,image.GetWidth(), image.GetHeight());
  
  // use image in window
  c2d.RegisterImage(&image);
  
  // start 2d window draw application
  c2d.Start();
  
	return 0;
}

