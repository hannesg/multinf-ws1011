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

	ScanlineFill(img);
}

bool compareLines(const PrimitiveLine &l1, const PrimitiveLine &l2) {
	return l1.GetXMin() < l2.GetXMin(); 
}

ostream &operator << (ostream &o, const PrimitiveLine &l) {
	o << "(" << l.GetStartingPoint().GetX() << ", " << l.GetStartingPoint().GetY() << 
		"), (" << l.GetEndingPoint().GetX() << ", " << l.GetEndingPoint().GetY() << ")" << endl;
	return o;
}

bool isEmpty(vector<PrimitiveLine> *et, unsigned int count) 
{
	for(unsigned int i = 0; i < count; i++) {
		if(!et[i].empty()) {
			return false;
		}
	}
	return true;
}

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

	global_y_diff = y_globalmax - y_globalmin + 1;

	cout << "min: " << y_globalmin << " max: " << y_globalmax << " diff: " << global_y_diff << endl;

	// **************************************************************

	// Edges erstellen
	vector<PrimitiveLine> edges;

	unsigned int countLines = points_.size();

	for(unsigned int i = 0; i < countLines; i++) {
		PrimitiveLine e(points_[i], points_[(i+1)%countLines]);
		edges.push_back(e);
		cout << e;
	}

	cout << "********************" << endl;

	// Edgetable erstellen

	vector<PrimitiveLine> *et = new vector<PrimitiveLine>[global_y_diff];

	for(int y = y_globalmin; y <= y_globalmax; y++) {
		for(unsigned int j = 0; j < countLines; j++) {
			// Nur hinzufuegen, falls nicht horizontal!
			if(edges[j].GetYMin() == y && edges[j].GetYMax() != edges[j].GetYMin()) {

				et[y-y_globalmin].push_back(edges[j]);
			}
		}

		// Ausgabe
		/* cout << "Line " << y << endl;
		for(unsigned int j = 0; j < et[y-y_globalmin].size(); j++) {
			cout << et[y-y_globalmin][j];
		} */
	}

	// *********************************


	// Determine first y coordinate that has edges
	list<PrimitiveLine> aet;

	int y;

	for(y = y_globalmin; y <= y_globalmax; y++) {
		if(!et[y-y_globalmin].empty()) {
			break;
		}
	} 

	typedef list<PrimitiveLine>::iterator iter;

	// y is the first coordinate, that has edges

	while(!(aet.empty() && isEmpty(et, global_y_diff))) {

		cout << "===== Line " << y << " ============================" << endl;

		// Algorithm point 1
		// copy(et[y-y_globalmin].begin(), et[y-y_globalmin].end(), aet.end());
		for(unsigned int i = 0; i < et[y-y_globalmin].size(); i++) {
			// if(et[y-y_globalmin][i].ymin == y) {
				aet.push_back(et[y-y_globalmin][i]);
			// }
		}

		et[y-y_globalmin].clear();

		aet.sort(compareLines);

		cout << "aet size: " << aet.size() << endl;
		cout << "et size: " << size(et, global_y_diff) << endl;
		/* for(iter it = aet.begin(); it != aet.end(); it++) {
			cout << *it;
		} */

		// Algorithm point 2
		// Determine x values

		vector<int> xs;

		for(iter it = aet.begin(); it != aet.end(); it++) {
			xs.push_back(it->getXValue(y));

			cout << it->getXValue(y) << " " ;
		}
		cout << endl;

		sort(xs.begin(), xs.end());

		if(xs.size() % 2 != 0) {
			cerr << "Fehler! xs muss gerade Anzahl von Punkten haben! " << endl;
			return;
		}

		for(unsigned int i = 0; i < xs.size()/2; i++) {

			for(int x = xs[2*i]; x <= xs[2*i+1]; x++) {
				img->SetPixel(x, y, 0, GetColor().GetR());
				img->SetPixel(x, y, 1, GetColor().GetG());
				img->SetPixel(x, y, 2, GetColor().GetB());
			}

		}

		// Algorithm point 3

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

		/* cout << "aet size: " << aet.size() << endl;
		cout << "et size: " << size(et, global_y_diff) << endl;
		for(iter it = aet.begin(); it != aet.end(); it++) {
			it->print();
		} */

		// algorithm point 4
		y++;

		// algorithm point 5
	}

	delete [] et;

	cout << "Fertig! " << endl;
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
