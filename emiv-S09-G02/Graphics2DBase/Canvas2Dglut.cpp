/*
 * a glut window drawing a registered image to screen.
 * a 2d painter can be registered to paint primitives
 * @author fkellner, 10/10
 */

#include <iostream>
#include <cstdlib>
#include <GL/glut.h>
#include <Graphics2DBase/Canvas2D.hh>

namespace Graphics2D {
  Canvas2D *Canvas2D::instance_ = NULL;

  Canvas2D::Canvas2D() {
    painter_ = NULL;
    image_ = NULL;
  }
  
  int Canvas2D::Init(int posx, int posy, int width, int height) {
    if (instance_ != NULL) {
      std::cout << "Only one canvas can be opened" << std::endl;
      return -1;
    }
    instance_ = this;
    width_ = width;
    height_= height;
	wreshape_ = 1.0f;
    hreshape_ = 1.0f;
    posx_ = posx;
    posy_ = posy;
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

  Canvas2D::~Canvas2D() {

  }
  
  void Canvas2D::Start() {
    int argc=0;char **argv = NULL;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    glutInitWindowPosition(posx_,posy_);
    glutInitWindowSize(width_,height_);
    glutCreateWindow("Glut Window");
    glutDisplayFunc(Render);
    glutMouseFunc(MouseButtonEvents);
    glutMotionFunc(MouseMotionEvents);
    glutPassiveMotionFunc(MouseMotionEvents);
    glutKeyboardFunc(KeyboardEvents);
	glutReshapeFunc(Reshape);
    glutTimerFunc(40, OnTimer, 1);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    glOrtho (0, width_, height_, 0, 0, 1);
    glDisable(GL_DEPTH_TEST);
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity();
    glClearColor(0, 0, 0, 0);
    
    // init texture
    glEnable (GL_TEXTURE_2D);
    glGenTextures( 1, &texId_ );
    glBindTexture( GL_TEXTURE_2D, texId_ );
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    
    glutMainLoop();
  }
  
  void Canvas2D::Render() {
    glClear(GL_COLOR_BUFFER_BIT);
    if (instance_->painter_ != NULL)
      instance_->painter_->Draw();
    
    if (instance_->image_->Valid()) {
      unsigned int w,h;
      w = instance_->image_->GetWidth();
      h = instance_->image_->GetHeight();
      glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, w,h, 0, GL_RGB, GL_UNSIGNED_BYTE, instance_->image_->GetData());
    }

    glBindTexture (GL_TEXTURE_2D, instance_->texId_);
    glBegin(GL_QUADS);
      glTexCoord2f(0.0, 0.0);
      glVertex2f(0,0);
      glTexCoord2f(1.0, 0.0);
      glVertex2f(instance_->width_,0);
      glTexCoord2f(1.0, 1.0);
      glVertex2f(instance_->width_,instance_->height_);
      glTexCoord2f(0.0, 1.0);
      glVertex2f(0,instance_->height_);
    glEnd();

    if (instance_->painter_ != NULL) {
      glDisable(GL_TEXTURE_2D);
      glColor3f(1,1,1);
      std::string text = "Primitive: "+instance_->painter_->GetString()+" - Color: "+instance_->painter_->GetColorString();
      int pos=10;
      for (unsigned int i=0;i<text.length();i++) {
        glRasterPos2d(pos, instance_->height_ - 20);
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
        pos += glutBitmapWidth(GLUT_BITMAP_HELVETICA_18, text[i])+2;
      }
      glEnable(GL_TEXTURE_2D);
    }
  }
  
  void Canvas2D::OnTimer(int value) {
    glutPostRedisplay();
    glutSwapBuffers();
    glutTimerFunc(40, OnTimer, value+1);
  }

  void Canvas2D::MouseButtonEvents(int button, int state, int x, int y) {
    if (instance_->painter_ == NULL) { return; }
	x = (int) (float(x)*instance_->wreshape_);
    y = (int) (float(y)*instance_->hreshape_);
    if (button == GLUT_LEFT_BUTTON) {
      if (state == GLUT_DOWN) {
        instance_->painter_->MouseDown(x,y);
      }
      if (state == GLUT_UP) {
        instance_->painter_->MouseUp(x,y);
      }
    }
    // glutPostRedisplay();
    // glutSwapBuffers();
  }

  void Canvas2D::MouseMotionEvents(int x, int y) {
    if (instance_->painter_ == NULL) { return; }
	x = (int) (float(x)*instance_->wreshape_);
    y = (int) (float(y)*instance_->hreshape_);
    instance_->painter_->MouseMove(x,y);
    // glutPostRedisplay();
    // glutSwapBuffers();
  }
  
  void Canvas2D::KeyboardEvents(unsigned char ch, int x, int y) {
    if (instance_->painter_ == NULL) { return; }
	x = (int) (float(x)*instance_->wreshape_);
    y = (int) (float(y)*instance_->hreshape_);
    instance_->painter_->KeyPressed(ch,x,y);
    // glutPostRedisplay();
    // glutSwapBuffers();
  }
  
  void Canvas2D::Reshape(int x, int y) {
    instance_->wreshape_ = float(instance_->width_) / float(x); 
    instance_->hreshape_ = float(instance_->height_) / float(y);
    glViewport(0,0,x,y);
  }
}
