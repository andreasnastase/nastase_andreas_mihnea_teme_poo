#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>

using namespace std;

enum Zona { IN_ORAS = 1, IN_AFARA_ORASULUI = 2 };

class Fabrica {
private:
	const int id;
	string denumire;
	Zona zona;
	int nrAngajati;
	float* vectorSalarii;
public:
	static int nrFabrici;

	Fabrica() :id(++nrFabrici) {
		this->denumire = "Default";
		this->zona = IN_AFARA_ORASULUI;
		this->nrAngajati = 0;
		this->vectorSalarii = nullptr;
	}

	Fabrica(int id, string denumire, Zona zona, int nrAngajati, float* vectorSalarii) :id(id) {
		this->denumire = denumire;
		this->zona = zona;
		this->nrAngajati = nrAngajati;
		this->vectorSalarii = new float[nrAngajati];
		for (int i = 0;i < this->nrAngajati;i++) {
			this->vectorSalarii[i] = vectorSalarii[i];
		}
		nrFabrici++;
	}

	Fabrica(const Fabrica& f) :id(++nrFabrici) {
		this->denumire = f.denumire;
		this->zona = f.zona;
		this->nrAngajati = f.nrAngajati;
		if (f.vectorSalarii != nullptr) {
			this->vectorSalarii = new float[f.nrAngajati];
			for (int i = 0;i < f.nrAngajati;i++) {
				this->vectorSalarii[i] = f.vectorSalarii[i];
			}
		}
		else {
			this->vectorSalarii = nullptr;
		}
	}

	void operator=(const Fabrica& f) {
		this->denumire = f.denumire;
		this->zona = f.zona;
		this->nrAngajati = f.nrAngajati;
		if (this->vectorSalarii != nullptr) {
			delete[] this->vectorSalarii;
			this->vectorSalarii = nullptr;
		}
		if (f.vectorSalarii != nullptr) {
			this->vectorSalarii = new float[f.nrAngajati];
			for (int i = 0;i < f.nrAngajati;i++) {
				this->vectorSalarii[i] = f.vectorSalarii[i];
			}
		}
		else {
			this->vectorSalarii = nullptr;
		}
	}

	void afisareFabrica() {
		cout << endl << "Id: " << this->id;
		cout << endl << "Denumire: " << this->denumire;
		cout << endl << "Zona: ";
		if (this->zona == 1) {
			cout << IN_ORAS;
		}
		else {
			cout << IN_AFARA_ORASULUI;
		}
		cout << endl << "Numar angajati: " << this->nrAngajati;
		if (this->nrAngajati > 0) {
			cout << endl << "Salariile angajatilor: ";
			for (int i = 0;i < this->nrAngajati-1;i++) {
				cout << this->vectorSalarii[i] << ", ";
			}
			cout << this->vectorSalarii[this->nrAngajati - 1] << ".";
		}
	}

	int getNrAngajati() {
		return this->nrAngajati;
	}

	void setNrAngajati(int nrAngajatiNou) {
		if (nrAngajatiNou >= 0) {
			this->nrAngajati = nrAngajatiNou;
		}
		else {
			throw "Valoare negativa!";
		}
	}

	float* getVectorSalarii() {
		float* vectorSalariiNou = new float[this->nrAngajati];
		for (int i = 0;i < this->nrAngajati;i++) {
			vectorSalariiNou[i] = this->vectorSalarii[i];
		}
		return vectorSalariiNou;
	}

	void setVectorSalarii(float* vector, int nrA) {
		setNrAngajati(nrA);
		if (this->vectorSalarii != nullptr) {
			delete[] vectorSalarii;
		}

		this->vectorSalarii = new float[this->nrAngajati];
		for (int i = 0;i < this->nrAngajati;i++) {
			this->vectorSalarii[i] = vector[i];

		}
		delete[] vector;
	}

	~Fabrica() {
		if (this->vectorSalarii != nullptr) {
			delete[] this->vectorSalarii;
		}
	}

};

int Fabrica::nrFabrici = 0;

int main() {
	Fabrica fAstra;
	fAstra.afisareFabrica();

	fAstra.setNrAngajati(4);
	cout << endl << "Noul numar de angajati este: " << fAstra.getNrAngajati();

	fAstra.setVectorSalarii(new float[4] {4000, 4500, 5000, 5500}, 4);
	float* vector = fAstra.getVectorSalarii();
	cout << endl << "Noile preturi sunt: ";
	for (int i = 0;i < 4;i++) {
		cout << vector[i] << " lei, ";
	}
	fAstra.afisareFabrica();
	delete[] vector;

	float* vectorSalarii = new float[4] {5000, 5500, 6000, 6500};
	Fabrica* pUzuc = new Fabrica(5, "Uzuc S.A.", IN_ORAS, 4, vectorSalarii);
	pUzuc->afisareFabrica();

	Fabrica fLukoil = *pUzuc;
	fLukoil.afisareFabrica();

	fAstra = *pUzuc;
	fAstra.afisareFabrica();

	cout << endl << "Am construit " << Fabrica::nrFabrici << " fabrici!";

	delete pUzuc;
}
