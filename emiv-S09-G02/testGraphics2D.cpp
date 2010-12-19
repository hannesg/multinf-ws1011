/*
Gruppe: 02
Serie 02
Matthias Boehm, 895778
Hannes Georg, 850360
*/

#include <iostream>
#include "Image.hh"

using namespace std;

int main(int argc, char *argv[])
{
	/*cout << "Hello, world! " << endl;
	cout << "What is your name? " << endl;
	
	string name;
	cin >> name;
	
	cout << "Hello " << name << "! " << endl;*/

	Graphics2D::Image img;

	if( argc != 3 ){
		cout << "Benutzung: testGraphics2D <quelle> <ziel>" << endl;
		cout << "Wandelt die PPM-Datei <quelle> in eine P6 PPM-Datei <ziel> um." << endl;
		return -1;
	}

    if( img.LoadPPM(std::string(argv[1])) ){
    	cout << "Konnte die Quelldatei nicht laden." << endl;
    	return 1;
    }

    if( img.SavePPM(std::string(argv[2])) ){
		cout << "Konnte die Zieldatei nicht speichern." << endl;
		return 2;
	}

    cout << "Erfolgreich gespeichert." << endl;

	return 0;
}
