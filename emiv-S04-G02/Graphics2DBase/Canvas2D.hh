/*
 * Canvas for drawing of 2d images
 *
 * see Canvas2Dglut.hh or Canvas2Dgtk.hh for public interface
 *
 * @author fkellner, 11/10
 */
#ifndef CANVAS2D_HH_
#define CANVAS2D_HH_

#ifdef GRAPHICS2D_USEGTK
#include <Graphics2DBase/Canvas2Dgtk.hh>
#else
#include <Graphics2DBase/Canvas2Dglut.hh>
#endif

#endif /* CANVAS2D_HH_ */
