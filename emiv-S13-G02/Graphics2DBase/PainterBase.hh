/*
 * Painter Base Class
 * @author fkellner, 10/10
 */
#ifndef PAINTERBASE_HH_
#define PAINTERBASE_HH_

#include <Graphics2DBase/ImageBase.hh>
#include <string.h>

namespace Graphics2D {

  /**
   * a base class for painting anything onto an image.
   * intended use in this exercise is the implementation of PainterBase
   * such that a Painter has a vector of Primitives that are drawn
   * one after another onto the image (it is a container for primitives)
   * 
   * the painter also reacts on events from the canvas2d class
   */
  class PainterBase {
    public:
      
      /// draws a vector of primitives
      virtual void Draw() = 0;
      
      /// helpers for the canvas2d class. currently selected color and primitive name (see keypressed)
      virtual std::string GetColorString() = 0;
      virtual std::string GetString() = 0;
      
      /// this function is called when a user presses a mouse button in the gui at (x,y)
      virtual void MouseDown(int x, int y) = 0;
      
      /// this function is called when a user releases a mouse button in the gui at (x,y)
      virtual void MouseUp(int x, int y) = 0;
      
      /// this function is called when a user holds a mouse button in the gui at (x,y)
      virtual void MouseMove(int x, int y) = 0;
      
      /// this function is called when a user presses a key in the gui. ch is the key pressed.
      /// keys '1' to '4' select different colors
      /// key 'p' for 'draw points', 'l' for 'draw lines' etc.
      /// key 'h' prints help to console
      virtual void KeyPressed(unsigned char ch, int x, int y) = 0;
      
      /// sets the image this painter paints on. this is called by canvas2d
      void SetImage(ImageBase *im) {
        image_ = im;
      }
    protected:
      ImageBase *image_;
  };

}

#endif /* PAINTERBASE_HH_ */
