#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>

using namespace std;

class ExceptieCustom :public exception {
public:
	ExceptieCustom(const char* mesaj) : exception(mesaj) {}
};

class JocVideo {
protected:
	const int id;
	string denumire;
	float pret;

public:
	static const float PRET_MINIM;
	JocVideo() : id(0), denumire("Gta6"), pret(400) {}

	JocVideo(int idJ, string denumireJ, float pretJ)
		: id(idJ), denumire(denumireJ), pret(pretJ) {
		if (pret < PRET_MINIM) {
			throw ExceptieCustom("Pret prea mic!");
		}
	}

	virtual void afisare() {
		cout << endl << "Id: " << this->id;
		cout << endl << "Denumire: " << this->denumire;
		cout << endl << "Pret: " << this->pret;
	}

	~JocVideo() {

	}

	virtual float getProcentReducere() = 0;

};

const float JocVideo::PRET_MINIM = 1;

class JocMultiplayer : public JocVideo {
private:
	float procentReducere;

public:
	JocMultiplayer() : JocVideo() {
		this->procentReducere = 0;
	}

	JocMultiplayer(int idJ, string denumireJ, float pretJ, float procentReducereJ)
		: JocVideo(idJ, denumireJ, pretJ) {
		this->procentReducere = procentReducereJ;
	}

	void afisare() {
		this->JocVideo::afisare();
		cout << endl << "Procent reducere: " << this->procentReducere;
	}

	float getProcentReducere() {
		return this->procentReducere;
	}
};

class Operatie {
public:
	virtual int adunare(int a, int b) = 0;
	virtual int scadere(int a, int b) = 0;
	virtual int inmultire(int a, int b) = 0;
};

class Calculator : public Operatie {
public:
	Calculator() {}

	int adunare(int a, int b) {
		return a + b;
	}

	int scadere(int a, int b) {
		return a - b;
	}

	int inmultire(int a, int b) {
		return a * b;
	}

};

void main() {
	JocVideo* vectorJocuri[3];
	vectorJocuri[0] = new JocMultiplayer(1, "EA FC27", 200, 15);
	vectorJocuri[1] = new JocMultiplayer(2, "Minecraft", 100, 10);
	vectorJocuri[2] = new JocMultiplayer(3, "Gta6", 400, 20);

	for (int i = 0; i < 3;i++) {
		vectorJocuri[i]->afisare();
		delete vectorJocuri[i];
	}

	JocVideo* pJoc = new JocMultiplayer();
	pJoc->afisare();
	delete pJoc;

	Operatie* calcul = new Calculator();
	cout << endl << "Adunare: " << calcul->adunare(7, 9);
	cout << endl << "Scadere: " << calcul->scadere(10, 2);
	cout << endl << "Inmultire: " << calcul->inmultire(3, 6);

	delete calcul;
}
