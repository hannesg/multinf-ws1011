
ADD_LIBRARY(Graphics2D 
    Image.cpp 
    Image.hh
	Coordinate.cpp
	Coordinate.hh
	Color.cpp
	Color.hh
	Painter.cpp
        Painter.hh
	
	# Primitives
	PrimitivePoint.cpp
	PrimitivePoint.hh
	PrimitiveLine.cpp
	PrimitiveLine.hh
	BackgroundImage.cpp
	BackgroundImage.hh
	
	# Modus controllers
	ModusController.cpp
	ModusController.hh
	PointModusController.cpp
	PointModusController.hh
	LineModusController.cpp
	LineModusController.hh
	BoxModusController.cpp
	BoxModusController.hh
	PolygonModusController.cpp
	PolygonModusController.hh
    )

target_link_libraries(Graphics2D Graphics2DBase)