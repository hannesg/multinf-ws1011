/*
Gruppe: 02
Serie 05
Matthias Boehm, 895778
Hannes Georg, 850360
*/

#include <cstdlib>
#include <vector>
#include <list>
#include <algorithm>
#include "PrimitivePolygon.hh"
#include "PrimitiveLine.hh"

using namespace std;

namespace Graphics2D {

void PrimitivePolygon::Draw(ImageBase *img) const
{
	// Fuellen
	ScanlineFill(img);

	// Zeichnen der Kanten sollte trotz obigen Fuellens durchgefuehrt werden, da 
	// in einigen Faellen das Ergebnis besser aussieht

	// Linien erstellen (Zeiger werden benoetigt, da dynamisch 
	// erzeugt wird)
	unsigned int countLines = points_.size();
	PrimitiveLine *lines = new PrimitiveLine[countLines];

	for(unsigned int i = 0; i < countLines; i++) {
		lines[i].SetStartingPoint(points_[i]);
		lines[i].SetEndingPoint(points_[(i+1)%countLines]);
		
		lines[i].SetColor(GetColor());
	}
	
	// Die erzeugten Linien, aus denen das Polygon besteht, zeichnen!
	for(unsigned int i = 0; i < countLines; i++) {
		lines[i].Draw(img);
	}

	// aufraeumen
	delete [] lines;
	
}

// Hilfsfunktion, Ausgabeoperator fuer PrimitiveLine (fuers Debuggen)
ostream &operator << (ostream &o, const PrimitiveLine &l) {
	o << "(" << l.GetStartingPoint().GetX() << ", " << l.GetStartingPoint().GetY() << 
		"), (" << l.GetEndingPoint().GetX() << ", " << l.GetEndingPoint().GetY() << ")" << endl;
	return o;
}

// Hilfsfunktion, gibt true zurueck, wenn Edge table leer
bool isEmpty(vector<PrimitiveLine> *et, unsigned int count) 
{
	for(unsigned int i = 0; i < count; i++) {
		if(!et[i].empty()) {
			return false;
		}
	}
	return true;
}

// Hilfsfunktion, gibt Anzahl der Kanten in Edge table zurueck
unsigned int size(vector<PrimitiveLine> *et, unsigned int count) {

	unsigned int s = 0;
	for(unsigned int i = 0; i < count; i++) {
		s += et[i].size();
	}
	return s;
}

void PrimitivePolygon::ScanlineFill(ImageBase *img) const
{
	// ermittele höchste und niedrigste y-Koordinaten
	int y_globalmax;
	int y_globalmin;
	int global_y_diff;

	y_globalmax = points_[0].GetY();
	y_globalmin = points_[0].GetY();

	for(unsigned int i = 1; i < points_.size(); i++) {
		int currentY = points_[i].GetY();
		if(currentY > y_globalmax) {
			y_globalmax = currentY;
		}
		if(currentY < y_globalmin) {
			y_globalmin = currentY;
		}
	}

	// Die Anzahl von zu betrachtenden y-Koordinaten bestimmen
	global_y_diff = y_globalmax - y_globalmin + 1;

	// **************************************************************

	// Edges erstellen
	vector<PrimitiveLine> edges;

	unsigned int countLines = points_.size();

	for(unsigned int i = 0; i < countLines; i++) {
		PrimitiveLine e(points_[i], points_[(i+1)%countLines]);
		edges.push_back(e);
	}

	// **************************************************************

	// Edgetable erstellen

	vector<PrimitiveLine> *et = new vector<PrimitiveLine>[global_y_diff];

	for(int y = y_globalmin; y <= y_globalmax; y++) {
		for(unsigned int j = 0; j < countLines; j++) {
			// Nur hinzufuegen, falls nicht horizontal!
			if(edges[j].GetYMin() == y && edges[j].GetYMax() != edges[j].GetYMin()) {

				et[y-y_globalmin].push_back(edges[j]);
			}
		}
	}

	// **************************************************************

	// Determine first y coordinate that has edges
	list<PrimitiveLine> aet;

	int y;

	for(y = y_globalmin; y <= y_globalmax; y++) {
		if(!et[y-y_globalmin].empty()) {
			break;
		}
	} 

	// y is now set to the first coordinate that has edges

	// **************************************************************

	// Algorithmus durchfuehren und Zeichnen

	// Abkuerzung fuer iterator verwenden
	typedef list<PrimitiveLine>::iterator iter;

	while(!(aet.empty() && isEmpty(et, global_y_diff))) {

		// Algorithm point 1
		// Nehme edges in active edge table auf
		
		for(unsigned int i = 0; i < et[y-y_globalmin].size(); i++) {
			aet.push_back(et[y-y_globalmin][i]);
		}

		// Loesche Edges aus Edge table
		et[y-y_globalmin].clear();

		// Algorithm point 3
		// Loesche nicht mehr benoetigte Kanten

		iter it = aet.begin();

		while(it != aet.end()) {
			if(it->GetYMax() == y) {
				aet.erase(it);
				it = aet.begin();
			} 
			else {
				it++;
			}
		}

		// Algorithm point 2
		// Determine x values (Schnittpunkte)

		vector<int> xs;

		for(iter it = aet.begin(); it != aet.end(); it++) {
			xs.push_back(it->getXValue(y));
		}

		// Schnittpunkte sortieren
		sort(xs.begin(), xs.end());

		// Darauf achten, dass gerade Anzahl von Schnittpunkten vorkommt!
		if(xs.size() % 2 == 0) {

			for(unsigned int i = 0; i < xs.size()/2; i++) {

				// Bereich zwischen jeweils zwei Schnittpunkten fuellen
				for(int x = xs[2*i]; x <= xs[2*i+1]; x++) {
					if(img->isInImage(x, y)) {
						img->SetPixel(x, y, 0, GetColor().GetR());
						img->SetPixel(x, y, 1, GetColor().GetG());
						img->SetPixel(x, y, 2, GetColor().GetB());
					}
				}
			}
		}
		else {
			cerr << "Fehler! xs muss gerade Anzahl von Punkten haben! " << endl;
		}

		// algorithm point 4
		y++;
	}

	delete [] et;
}

void PrimitivePolygon::SetCoordinates(const vector<Coordinate> &points) 
{
	// Check whether we really have a polygon
	if(points.size() < 4) {
		return;
	}

	if(points[0] != points[points.size()-1]) {
		return;
	}

	points_ = points;

	// delete last point
	points_.pop_back();

}

}
