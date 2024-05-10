#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

struct konyv {
	string cim;
	int kiadev;
	int ar;
	int eladottdb;
};

class konnyvvasar {
private: int db;
	   konyv* k;

public: konnyvvasar(string filename) {
		ifstream be(filename);

		if (!be.is_open()) {
			cout << "Nem sikerult megnyitni a fajlt!\n";
			exit(1);
		}

		string line = "";
		db = 0;
		while (getline(be, line)) {
			db++;
		}

		k = new konyv[db];

		be.clear();
		be.seekg(0, ios::beg);

		int i = 0;

		while (getline(be, line)) {
			stringstream stream(line);
			getline(stream, k[i].cim, ';');
			stream >> k[i].kiadev;
			stream.ignore();
			stream >> k[i].ar;
			stream.ignore();
			stream >> k[i].eladottdb;
			i++;
		}
	be.close();
}

	  ~konnyvvasar() {
			delete[] k;
		}
	
	  int darabszam() {
				cout << "A konyvek szama: " << db << endl;
	  			return db;	
	  }

	  double Osszbevetel() {
		  double osszeg = 0;
		  for (int i = 0; i < db; i++) {
			  osszeg += k[i].ar * k[i].eladottdb;
		  }
		  cout << setprecision(8) << "Az osszbevetel: " << osszeg << endl;
		  return osszeg;
	  }

	  string legkevesebbeladas() {
		  int min = 0;
		  
		  for (int i = 1; i < db; i++) {
			  if (k[i].eladottdb < k[min].eladottdb) {
				  min = i;
			
			  }
		  }
		  
		  return  k[min].cim;
	  }

	  konyv Legujjabkiadas() {
		  int max = 0;
		  for (int i = 1; i < db; i++) {
			  if (k[i].kiadev > k[max].kiadev) {
				  max = i;
			  }
		  }
		  return k[max];
	  }

	  double atlagar() {
		  double osszeg = 0;
		  for (int i = 0; i < db; i++) {
			  osszeg += k[i].ar * k[i].eladottdb;
		  }

		  return osszeg / db;
	  }

	  void Lista()
	  {
		  for (int i = 0; i < db; i++)
		  {
			  if (k[i].ar < 2000) {
				  cout << k[i].cim << " " << k[i].kiadev << " " << k[i].ar << " " << k[i].eladottdb << endl;
			  }
		  }
	  }

	  void kiir() {
		  cout.setf(ios::left);
		  for (int i = 0; i < db; i++)
		  {
			  cout << setw(10) << i+1 << setw(5) << k[i].cim << setw(5) <<" "<< k[i].kiadev << setw(5) << " " << k[i].ar << setw(5) << " " << k[i].eladottdb << endl;
		  }
	  }


};


int main()
{
    konnyvvasar k("bolt.csv");
	k.darabszam();
	k.Osszbevetel();
	konyv kstruct = k.Legujjabkiadas();
	cout << "A legkevesebbet eladott konyv: " << k.legkevesebbeladas() << endl;
	cout << "A legujabb kiadasu konyv: " << kstruct.cim << " " << k.Legujjabkiadas().kiadev << " " << k.Legujjabkiadas().ar << " " << k.Legujjabkiadas().eladottdb << endl;
	cout << "A bevetel atlaga: " << k.atlagar() << endl;
	cout << "Az 2000 Ft alatti konyvek: " << endl;
	k.Lista();
	cout << "A konyvek adatai: " << endl;
	k.kiir();
	return 0;
}

