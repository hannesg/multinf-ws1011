
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
	PrimitiveBase.cpp
	PrimitiveBase.hh
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
	
    )

target_link_libraries(Graphics2D Graphics2DBase)