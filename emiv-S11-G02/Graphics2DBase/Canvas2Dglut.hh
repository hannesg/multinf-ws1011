/*
 * a glut window drawing a registered image to screen.
 * a 2d painter can be registered to paint primitives
 * @author fkellner, 10/10
 */
#ifndef CANVAS2DGLUT_HH_
#define CANVAS2DGLUT_HH_

#include <Graphics2DBase/ImageBase.hh>
#include <Graphics2DBase/PainterBase.hh>

namespace Graphics2D {

  class Canvas2D {
    public:
      // constructor, sets members to null
      Canvas2D();
      
      // destructor leaves registered instances alone, must be destroyed elsewhere 
      virtual ~Canvas2D();
      
      // setup window, upper left corner (posx,posy), size (width, height)
      int Init(int posx, int posy, int width, int height);

      // register an instance of painter with this canvas.
      // on each frame, painter->draw is executed
      int RegisterPainter(PainterBase *painter);
      
      // register an image instance that is shown in the canvas
      // image must be of same dimensions as canvas
      int RegisterImage(ImageBase *image);
      
      // show window and run mainloop
      void Start();
      
      
      
    protected:
      // singleton instance of canvas2d, can be accessed by static functions
      static Canvas2D *instance_;
      // draw method
      static void Render();
      // redraw on timer
      static void OnTimer(int value);
      // mouse events, will call painter->mouseevents
      static void MouseButtonEvents(int button, int state, int x, int y);
      static void MouseMotionEvents(int x, int y);
      // keyboard events, will call painter->keybordevents
      static void KeyboardEvents(unsigned char ch, int x, int y);
      
      static void Reshape(int x, int y);
    private:
      int posx_, posy_, width_, height_;
      float wreshape_, hreshape_;
      unsigned int texId_;
      ImageBase *image_;
      PainterBase *painter_;
      
  };

}

#endif /* CANVAS2DGLUT_HH_ */
