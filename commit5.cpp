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
	float restanteSalarii;
public:
	static int nrEchipe;

	Echipa() :id(++nrEchipe) {
		this->denumire = "Default";
		this->nrJucatori = 0;
		this->vectorSalarii = nullptr;
		this->restanteSalarii = 0;
	}

	Echipa(int id, string denumire, int nrJucatori, float* vectorSalarii, float restanteSalarii) :id(id) {
		this->denumire = denumire;
		this->nrJucatori = nrJucatori;
		this->vectorSalarii = new float[this->nrJucatori];
		for (int i = 0;i < this->nrJucatori;i++) {
			this->vectorSalarii[i] = vectorSalarii[i];
		}
		this->restanteSalarii = restanteSalarii;
		nrEchipe++;
	}

	void afisareEchipa() {
		cout << endl << "Id: " << this->id;
		cout << endl << "Denumire: " << this->denumire;
		cout << endl << "Numar jucatori: " << this->nrJucatori;
		if (this->nrJucatori > 0) {
			cout << endl << "Salariile jucatorilor sunt: ";
			for (int i = 0;i < this->nrJucatori - 1;i++) {
				cout << this->vectorSalarii[i] << ", ";
			}
			cout << this->vectorSalarii[this->nrJucatori - 1] << ".";
		}
		cout << endl << "Restante salariale: " << this->restanteSalarii;
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
		this->restanteSalarii = e.restanteSalarii;
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
		this->restanteSalarii = e.restanteSalarii;

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

	bool operator<(const Echipa& e) {
		return this->nrJucatori < e.nrJucatori;
	}

	void operator+=(float datorii) {
		this->restanteSalarii += datorii;
	}

	bool operator!() {
		return this->restanteSalarii > 0;
	}

	float operator()(float restanteNoi) {
		return this->restanteSalarii + restanteNoi;
	}

	float& operator[](int index) {
		if (index >= 0 && index < this->nrJucatori) {
			return this->vectorSalarii[index];
		}
		else {
			throw exception();
		}
	}

	friend void operator<<(ostream& out, Echipa ec) {
		out << endl << "Operator de afisare: ";
		out << endl << "Id: " << ec.id;
		out << endl << "Denumire: " << ec.denumire;
		out << endl << "Restante Salarii: " << ec.restanteSalarii;
		out << endl << "Nr Jucatori: " << ec.nrJucatori;
		if (ec.vectorSalarii != nullptr) {
			out << "Vector salarii: ";
			for (int i = 0; i < ec.nrJucatori - 1;i++) {
				out << ec.vectorSalarii[i] << " lei, ";
			}
			out << ec.vectorSalarii[ec.nrJucatori - 1] << " lei. ";
		}
	}

	friend void operator>>(istream& in, Echipa& ec);

	Echipa operator++(int) {
		Echipa copie = *this;
		this->restanteSalarii++;

		return copie;
	}

	Echipa operator++() {
		this->restanteSalarii++;
		return *this;
	}

	explicit operator int() {
		return this->nrJucatori;
	}
};

int Echipa::nrEchipe = 0;

void operator>>(istream& in, Echipa& ec) {
	cout << endl << "Restante: ";
	in >> ec.restanteSalarii;
	cout << endl << "Denumire: ";
	in >> ec.denumire;
	cout << endl << "Nr Jucatori: ";
	in >> ec.nrJucatori;
	cout << endl << "Vector salarii: ";
	if (ec.vectorSalarii != nullptr) {
		delete[] ec.vectorSalarii;
		ec.vectorSalarii = nullptr;
	}

	ec.vectorSalarii = new float[ec.nrJucatori];
	for (int i = 0;i < ec.nrJucatori;i++) {
		cout << endl << "vectorSalarii[" << i << "]: ";
		in >> ec.vectorSalarii[i];
	}
}

int main() {
	Echipa ePetrolul;
	
	Echipa e1 = ePetrolul++;

	cout << e1;
	cout << ePetrolul;

	Echipa e2 = ++ePetrolul;

	cout << e2;
	cout << ePetrolul;

	

	float* vectorSalarii = new float[4] {1000, 2000, 3000, 4000};

	Echipa* pOtelul = new Echipa(3, "Otelul Galati", 4, vectorSalarii, 1000);
	pOtelul->afisareEchipa();

	if (ePetrolul < *pOtelul) {
		cout << endl << "Echipa Petrolul are mai putini jucatori";
	}
	else {
		cout << endl << "Echipa Otelul are mai putini jucatori";
	}

	(*pOtelul)[0] = 1000;
	cout << endl << "Apel operator index: " << (*pOtelul)[0];


	cout << endl << "Am construit " << Echipa::nrEchipe << " echipe!";

	cout << (int)(*pOtelul);

	cout << ePetrolul;

	delete pOtelul;
}
