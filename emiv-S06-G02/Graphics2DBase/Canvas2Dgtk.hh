/*
 * a gtk window drawing a registered image to screen.
 * a 2d painter can be registered to paint primitives
 * @author fkellner, 11/10
 */

#ifndef CANVAS2DGTK_HH_
#define CANVAS2DGTK_HH_

#include <Graphics2DBase/ImageBase.hh>
#include <Graphics2DBase/PainterBase.hh>

// forward declarations so we do not need gtk include path for graphics2d library
struct _GtkWidget;
struct _GdkEventButton;
struct _GdkEventMotion;
struct _GdkEventKey;
struct _GdkFont;
struct _GdkEventExpose;

namespace Graphics2D {

  class Canvas2D {
    public:
      // constructor, sets members to null
      Canvas2D();
      
      // destructor leaves registered instances alone, must be destroyed elsewhere 
      virtual ~Canvas2D();
      
      // setup window, upper left corner (posx,posy), size (width, height)
      // Position is ignored for GTK!
      int Init(int /*posx*/, int /*posy*/, int width, int height);

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
      static int Render(_GtkWidget* /*widget*/, _GdkEventExpose* /*event*/);
      static int OnTimer(_GtkWidget *widget);

      // mouse events, will call painter->mouseevents
      static int MouseButtonEvents (_GtkWidget* /*widget*/, _GdkEventButton* event);

      static int MouseMotionEvents (_GtkWidget* /*widget*/, _GdkEventMotion* event);

      // keyboard events, will call painter->keybordevents
      static int KeyboardEvents (_GtkWidget* /*widget*/, _GdkEventKey * event);
      
    private:
      int width_, height_;
      ImageBase *image_;
      PainterBase *painter_;
      _GtkWidget *gtkDrawingArea_;
      _GtkWidget *gtkWindow_;
      _GdkFont *gdkFont_;
      bool buttonDown_;
  };
}

#endif /* CANVAS2DGTK_HH_ */
