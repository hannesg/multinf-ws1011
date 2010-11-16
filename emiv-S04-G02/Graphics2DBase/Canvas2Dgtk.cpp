/*
 * a gtk window drawing a registered image to screen.
 * a 2d painter can be registered to paint primitives
 * @author fkellner, 11/10
 */

#include <Graphics2DBase/Canvas2Dgtk.hh>
#include <gtk/gtk.h>

namespace Graphics2D {
  
  Canvas2D::Canvas2D *Canvas2D::instance_ = NULL;


  // constructor, sets members to null
  Canvas2D::Canvas2D() {
    buttonDown_ = false;
    painter_ = NULL;
    image_ = NULL;
  }
  
  // destructor leaves registered instances alone, must be destroyed elsewhere 
  Canvas2D::~Canvas2D() {
    gdk_font_unref(gdkFont_);
    // gtk will handle deletion of gtk stuff
  }
  
  // setup window, upper left corner (posx,posy) (ignored for gtk), size (width, height)
  int Canvas2D::Init(int /*posx*/, int /*posy*/, int width, int height) {
    if (instance_ != NULL) {
      std::cout << "Only one canvas can be opened" << std::endl;
      return -1;
    }
    instance_ = this;
    width_ = width;
    height_= height;
    return 0;
  }

  int Canvas2D::RegisterImage(ImageBase *image) {
    if ((int)image->GetWidth() == width_ && (int)image->GetHeight() == height_) {
      image_ = image;
      return 0;
    } else {
      std::cout << "image dimensions do not match canvas size" << std::endl;
      return -1;
    }
  }

  int Canvas2D::RegisterPainter(PainterBase *painter) {
    if (painter != NULL) {
      if (image_ != NULL) {
        painter_ = painter;
        painter_->SetImage(image_);
      } else {
        std::cout << "RegisterImage first" << std::endl;
        return -1;
      }
    } else {
      std::cout << "no painter instance found. (painter == null)" << std::endl;
      return -1;
    }
    return 0;
  }

  // show window and run mainloop
  void Canvas2D::Start() {

    int argc=0; char **argv = NULL;
    gtk_init(&argc, &argv);

    gtkWindow_ = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(gtkWindow_), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(gtkWindow_), width_, height_);
    gtk_window_set_title(GTK_WINDOW(gtkWindow_), "GTK Window");
    gtk_window_set_resizable(GTK_WINDOW(gtkWindow_), FALSE);
    gtk_widget_add_events(gtkWindow_, GDK_BUTTON_PRESS_MASK | GDK_BUTTON_RELEASE_MASK | GDK_POINTER_MOTION_MASK | GDK_KEY_PRESS_MASK);

    gtk_container_set_border_width(GTK_CONTAINER(gtkWindow_), 0);
    
    gtkDrawingArea_ = gtk_drawing_area_new ();
    gtk_widget_set_size_request (gtkDrawingArea_, width_, height_);

    gtk_container_add(GTK_CONTAINER(gtkWindow_), gtkDrawingArea_);

    g_signal_connect_swapped(G_OBJECT(gtkWindow_), "destroy",
          G_CALLBACK(gtk_main_quit), G_OBJECT(gtkWindow_));
    
    g_signal_connect(G_OBJECT(gtkWindow_), "button-press-event",
        G_CALLBACK(Canvas2D::MouseButtonEvents), NULL);

    g_signal_connect(G_OBJECT(gtkWindow_), "button-release-event",
        G_CALLBACK(Canvas2D::MouseButtonEvents), NULL);

    g_signal_connect(G_OBJECT(gtkWindow_), "motion-notify-event",
        G_CALLBACK(Canvas2D::MouseMotionEvents), NULL);

    g_signal_connect(G_OBJECT(gtkWindow_), "key-press-event",
        G_CALLBACK(Canvas2D::KeyboardEvents), NULL);

    g_signal_connect(gtkDrawingArea_, "expose-event",
        G_CALLBACK(Canvas2D::Render), NULL);

    g_timeout_add(40, (GSourceFunc) Canvas2D::OnTimer, (gpointer) gtkWindow_);

    Canvas2D::OnTimer(gtkWindow_);

    gtk_widget_show_all(gtkWindow_);

//    gdkFont_ = gdk_font_load("-*-helvetica-medium-r-normal-*-30-*-*-*-*-*-*-*");
    gdkFont_ = gdk_font_load("-*-courier-medium-r-normal-*-18-*-*-*-*-*-*-*");

    gtk_main();

  }
  
  // draw method
  int Canvas2D::Render(GtkWidget* /*widget*/, GdkEventExpose* /*event*/) {
	std::string text = "no painter registered";
    if (instance_->painter_ != NULL) {
      instance_->painter_->Draw();
      text = "Primitive: "+instance_->painter_->GetString()+" - Color: "+instance_->painter_->GetColorString();
    }
    if (instance_->image_->Valid()) {
      gdk_draw_rgb_image (instance_->gtkDrawingArea_->window, instance_->gtkDrawingArea_->style->fg_gc[GTK_STATE_NORMAL],
          0,0,instance_->width_, instance_->height_, 
          GDK_RGB_DITHER_NONE, (guchar*)instance_->image_->GetData(), instance_->width_*3);

      gdk_draw_text(instance_->gtkDrawingArea_->window, instance_->gdkFont_, instance_->gtkDrawingArea_->style->white_gc, 
          5, (int)instance_->height_-10, text.c_str(), text.length());
    }
    return 0;
  }
    
  int Canvas2D::OnTimer(GtkWidget *widget) {
	if (widget->window == NULL) return 0;
    gtk_widget_queue_draw(widget);
    return 1;
  }

  int Canvas2D::MouseButtonEvents (GtkWidget* /*widget*/, GdkEventButton* event) {
	if (instance_->painter_ == NULL) { return 0; }
	if (event->type == GDK_BUTTON_PRESS) {
      if (event->button == 1) {
        instance_->painter_->MouseDown( (int) event->x, (int) event->y);
        instance_->buttonDown_ = true;
      }
    }
    if (event->type == GDK_BUTTON_RELEASE) {
      if (event->button == 1) {
        instance_->painter_->MouseUp( (int) event->x, (int) event->y);
        instance_->buttonDown_ = false;
      }
    }

    return 0;
  }

  
  int Canvas2D::MouseMotionEvents (GtkWidget* /*widget*/, GdkEventMotion* event) {
    if (instance_->painter_ == NULL) { return 0; }
	  if (instance_->buttonDown_) {
      instance_->painter_->MouseMove( (int) event->x, (int) event->y);
    }
    return 0;
  }

  int Canvas2D::KeyboardEvents (GtkWidget* /*widget*/, GdkEventKey* event) {
	if (instance_->painter_ == NULL) { return 0; }
    instance_->painter_->KeyPressed( (unsigned char) event->keyval, 0, 0);
    return 0;
  }

}
