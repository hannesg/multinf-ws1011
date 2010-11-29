
ADD_LIBRARY(Graphics2D 
    Image.cpp 
    Image.hh
	Coordinate.cpp
	Coordinate.hh
	Color.cpp
	Color.hh
	Painter.cpp
        Painter.hh
	ColorConversion.cpp
	ColorConversion.hh
	
	# Primitives
	PrimitivePoint.cpp
	PrimitivePoint.hh
	PrimitiveLine.cpp
	PrimitiveLine.hh
	PrimitivePolygon.cpp
	PrimitivePolygon.hh
	PrimitiveBox.cpp
	PrimitiveBox.hh
	BackgroundImage.cpp
	BackgroundImage.hh
	PrimitiveStar.cpp
	PrimitiveStar.hh
	
	# Modus controllers
	Controller/ModusController.cpp
	Controller/ModusController.hh
	Controller/PointModusController.cpp
	Controller/PointModusController.hh
	Controller/LineModusController.cpp
	Controller/LineModusController.hh
	Controller/BoxModusController.cpp
	Controller/BoxModusController.hh
	Controller/PolygonModusController.cpp
	Controller/PolygonModusController.hh
	Controller/StarModusController.cpp
	Controller/StarModusController.hh
    )

target_link_libraries(Graphics2D Graphics2DBase)