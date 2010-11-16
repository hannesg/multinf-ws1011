
ADD_LIBRARY(Graphics2D 
    Image.cpp 
    Image.hh
	Coordinate.cpp
	Coordinate.hh
	Color.cpp
	Color.hh
	PrimitiveBase.cpp
	PrimitiveBase.hh
	PrimitivePoint.cpp
	PrimitivePoint.hh
	PrimitiveLine.cpp
	PrimitiveLine.hh
	BackgroundImage.cpp
	BackgroundImage.hh
	Painter.cpp
	Painter.hh
	
	# Modus controller
	ModusController.cpp
	ModusController.hh
	PointModusController.cpp
	PointModusController.hh
	
	
    )

target_link_libraries(Graphics2D Graphics2DBase)