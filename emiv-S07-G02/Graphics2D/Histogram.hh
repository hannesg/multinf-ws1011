/*
Gruppe: 02
Serie 06
Matthias Boehm, 895778
Hannes Georg, 850360
*/

#ifndef HISTOGRAM_HH_
#define HISTOGRAM_HH_

#include <vector>
#include "PrimitiveBase.hh"
#include "Image.hh"
#include "ImageBase.hh"
#include "ColorConversion.hh"
#include "PrimitiveBox.hh"

namespace Graphics2D {

class Histogram : public PrimitiveBase {
public:
	/* constructors */
	Histogram();
	Histogram(const Coordinate &c1, const Coordinate &c2, const Color &c);

	virtual ~Histogram();

	/* Histogramm von Image image und channel channel erstellen */
	int FromImage(const Image& image, const int channel);

	/* Gibt die erste Position von hinten gesehen im Histogramm an, ab der ein Wert != 0 ist*/
	int Max() const;
	/* Gibt die erste Position im Histogramm an, an der der Wert != 0 ist */
	int Min() const;

	/* Gibt das Maximum aller Werte im Histogramm an */
	int MaxValue() const;
	/* Gibt das Minimum aller Werte im Histogramm an */
	int MinValue() const;

	/* überschriebene Zeichenfunktion */
	virtual void Draw(Graphics2D::ImageBase* image) const;

	/* stellt den Kontrast von src optimal ein */
	static void Autocontrast(const Image &src, Image &dest);

protected:
	/* speichert das Histogramm */
	std::vector<int> histogram_;

	/* Anzahl der erlaubten Punkte */
	virtual int GetNumberOfPointsAllowed() const { return 2; }

private:
	/* Initialisation function */
	void Init(const Coordinate &c1, const Coordinate &c2, const Color &c);
};

}

#endif /* HISTOGRAM_HH_ */
