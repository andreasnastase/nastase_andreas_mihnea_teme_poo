#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>

using namespace std;

class Echipa {
private: 
	const int id;
	string denumire;
	int nrJucatori;
	float* vectorSalarii;
public:
	static int nrEchipe;

	Echipa() :id(++nrEchipe) {
		this->denumire = "Default";
		this->nrJucatori = 0;
		this->vectorSalarii = nullptr;
	}

	Echipa(int id, string denumire, int nrJucatori, float* vectorSalarii) :id(id) {
		this->denumire = denumire;
		this->nrJucatori = nrJucatori;
		this->vectorSalarii = new float[this->nrJucatori];
		for (int i = 0;i < this->nrJucatori;i++) {
			this->vectorSalarii[i] = vectorSalarii[i];
		}
		nrEchipe++;
	}

	void afisareEchipa() {
		cout << endl << "Id: " << this->id;
		cout << endl << "Denumire: " << this->denumire;
		cout << endl << "Numar jucatori: " << this->nrJucatori;
		if (this->nrJucatori > 0) {
			cout << endl << "Salariile jucatorilor sunt: ";
			for (int i = 0;i < this->nrJucatori-1;i++) {
				cout << this->vectorSalarii[i] << ", ";
			}
			cout << this->vectorSalarii[this->nrJucatori - 1] << ".";
		}
	}

	Echipa(const Echipa& e) :id(++nrEchipe) {
		this->denumire = e.denumire;
		this->nrJucatori = e.nrJucatori;
		if (e.vectorSalarii != nullptr) {
			this->vectorSalarii = new float[e.nrJucatori];
			for (int i = 0;i < e.nrJucatori;i++) {
				this->vectorSalarii[i] = e.vectorSalarii[i];
			}
		}
		else {
			this->vectorSalarii = nullptr;
		}
	}

	void operator=(const Echipa& e) {
		this->denumire = e.denumire;
		this->nrJucatori = e.nrJucatori;
		if (this->vectorSalarii != nullptr) {
			delete[] this->vectorSalarii;
			this->vectorSalarii = nullptr;
		}
		if (e.vectorSalarii != nullptr) {
			this->vectorSalarii = new float[e.nrJucatori];
			for (int i = 0;i < e.nrJucatori;i++) {
				this->vectorSalarii[i] = e.vectorSalarii[i];
			}
		}
		else {
			this->vectorSalarii = nullptr;
		}

	}

	int getNrJucatori() {
		return this->nrJucatori;
	}

	void setNrJucatori(int nrJucatoriNou) {
		if (nrJucatoriNou >= 0) {
			this->nrJucatori = nrJucatoriNou;
		}
		else {
			throw "Valoare negativa!";
		}
	}

	float* getVectorSalarii() {
		float* vectorSalariiNou = new float[this->nrJucatori];
		for (int i = 0;i < this->nrJucatori;i++) {
			vectorSalariiNou[i] = this->vectorSalarii[i];
		}
		return vectorSalariiNou;
	}

	void setVectorSalarii(float* vector, int nrJ) {
		setNrJucatori(nrJ);
		if (this->vectorSalarii != nullptr) {
			delete[] vectorSalarii;
		}
		this->vectorSalarii = new float[this->nrJucatori];
		for (int i = 0;i < this->nrJucatori;i++) {
			this->vectorSalarii[i] = vector[i];
		}
		delete[] vector;

	}

	~Echipa() {
		if (this->vectorSalarii != nullptr) {
			delete[] this->vectorSalarii;
		}
	}
};

int Echipa::nrEchipe = 0;

int main() {
	Echipa ePetrolul;
	ePetrolul.afisareEchipa();

	ePetrolul.setNrJucatori(4);
	cout << endl << "Noul numar de jucatori este: " << ePetrolul.getNrJucatori();

	ePetrolul.setVectorSalarii(new float[4] {2000, 3000, 4000, 5000}, 4);
	float* vector = ePetrolul.getVectorSalarii();

	cout << endl << "Noile salarii sunt: ";
	for (int i = 0;i < 4;i++) {
		cout << vector[i] << " euro, ";
	}
	ePetrolul.afisareEchipa();

	delete[] vector;

	float* vectorSalarii = new float[4] {1000, 2000, 3000, 4000};

	Echipa* pOtelul = new Echipa(3, "Otelul Galati", 4, vectorSalarii);
	pOtelul->afisareEchipa();

	Echipa eFCSB = *pOtelul;
	eFCSB.afisareEchipa();

	ePetrolul = *pOtelul;
	ePetrolul.afisareEchipa();

	cout << endl << "Am construit " << Echipa::nrEchipe << " echipe!";

	delete pOtelul;
}
