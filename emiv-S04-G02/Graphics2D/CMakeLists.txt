
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
	Painter.cpp
	Painter.hh
    )

target_link_libraries(Graphics2D Graphics2DBase)