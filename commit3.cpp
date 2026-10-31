#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>

using namespace std;

enum Zona { CENTRALA, PERIFERICA};

class Mall {
private:
	const int id;
	string denumire;
	Zona zona;
	int nrMagazine;
	float* vanzariZilnice;
public:
	static int nrMalluri;
	Mall() :id(++nrMalluri) {
		this->denumire = "Default";
		this->zona = PERIFERICA;
		this->nrMagazine = 0;
		this->vanzariZilnice = nullptr;
	}
	Mall(int id, string denumire, Zona zona, int nrMagazine, float* vanzariZilnice) :id(id) {
		this->denumire = denumire;
		this->zona = zona;
		this->nrMagazine = nrMagazine;
		this->vanzariZilnice = new float[nrMagazine];
		for (int i = 0; i < nrMagazine; i++) {
			this->vanzariZilnice[i] = vanzariZilnice[i];
		}
		nrMalluri++;
	}

	Mall(const Mall& m) :id(++nrMalluri) {
		this->denumire = m.denumire;
		this->zona = m.zona;
		this->nrMagazine = m.nrMagazine;

		if (m.vanzariZilnice != nullptr) {
			this->vanzariZilnice = new float[m.nrMagazine];
			for (int i = 0; i < m.nrMagazine; i++) {
				this->vanzariZilnice[i] = m.vanzariZilnice[i];
			}
		}
		else {
			this->vanzariZilnice = nullptr;
		}
	}

	void operator=(const Mall& m) {
		this->denumire = m.denumire;
		this->zona = m.zona;
		this->nrMagazine = m.nrMagazine;

		if (this->vanzariZilnice != nullptr) {
			delete[] this->vanzariZilnice;
			this->vanzariZilnice = nullptr;
		}

		if (m.vanzariZilnice != nullptr) {
			this->vanzariZilnice = new float[m.nrMagazine];
			for (int i = 0; i < m.nrMagazine; i++) {
				this->vanzariZilnice[i] = m.vanzariZilnice[i];
			}
		}
		else {
			this->vanzariZilnice = nullptr;
		}
	}

	void afisareMall() {
		cout << endl << "Id: " << this->id;
		cout << endl << "Denumire: " << this->denumire;
		cout << endl << "Zona: " << this->zona;
		if (this->zona == 0) {
			cout << "CENTRALA";
		}
		else {
			cout << "PERIFERICA";
		}
		cout << endl << "Numar Magazine: " << this->nrMagazine;
		if (this->nrMagazine > 0) {
			cout << endl << "Vanzarile zilnice ale magazinelor: ";
			for (int i = 0;i < this->nrMagazine - 1;i++) {
				cout << this->vanzariZilnice[i]<<", ";
			}
			cout << vanzariZilnice[this->nrMagazine - 1] << ".";
		}
		
	}

	~Mall() {
		if (this->vanzariZilnice != nullptr) {
			delete[] this->vanzariZilnice;
		}
	}

	bool operator<(const Mall& m) {
		return this->nrMagazine < m.nrMagazine;
	}
};

int Mall::nrMalluri;

void main() {
	Mall mAfi;
	mAfi.afisareMall();

	float* vanzariZilnice = new float[4] {5000, 6000, 7000, 8000};
	Mall* pWestMall = new Mall(3, "West Mall", PERIFERICA, 4, vanzariZilnice);
	pWestMall->afisareMall();

	Mall mMegaMall = *pWestMall;
	mMegaMall.afisareMall();

	mAfi = *pWestMall;
	mAfi.afisareMall();

	cout << endl << "Am construit " << Mall::nrMalluri << " malluri!";

	if (mAfi < mMegaMall) {
		cout << endl << "Mallul Afi are mai putine locuri!";
	}
	else {
		cout << endl << "Mallul Mega Mall are mai putine locuri!";
	}

	delete pWestMall;
}
