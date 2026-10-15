#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>

using namespace std;

class SalaFitness
{
private:
    const int id;
    string denumire;
    int nr_tipuri_abonamente;
    float* vector_preturi_abonamente;

public:
    static int nr_sali;

    SalaFitness() : id(nr_sali++)
    {
        this->denumire = "Default";
        this->nr_tipuri_abonamente = 0;
        this->vector_preturi_abonamente = nullptr;
    }

    SalaFitness(int id, string denumire, int nr_tipuri_abonamente,
        float* vector_preturi_abonamente) : id(nr_sali++)
    {
        this->denumire = denumire;
        this->nr_tipuri_abonamente = nr_tipuri_abonamente;

        if (nr_tipuri_abonamente > 0 &&
            vector_preturi_abonamente != nullptr)
        {
            this->vector_preturi_abonamente =
                new float[nr_tipuri_abonamente];

            for (int i = 0; i < this->nr_tipuri_abonamente; i++)
            {
                this->vector_preturi_abonamente[i] =
                    vector_preturi_abonamente[i];
            }
        }
        else
        {
            this->vector_preturi_abonamente = nullptr;
        }
    }

    void afisare_sala()
    {
        cout << endl << "Id: " << this->id;
        cout << endl << "Denumire: " << this->denumire;
        cout << endl << "Numar tipuri de abonamente: "
             << this->nr_tipuri_abonamente;

        if (this->nr_tipuri_abonamente > 0 &&
            this->vector_preturi_abonamente != nullptr)
        {
            cout << endl << "Preturi abonamente: ";

            for (int i = 0; i < this->nr_tipuri_abonamente - 1; i++)
            {
                cout << this->vector_preturi_abonamente[i]
                     << " lei, ";
            }

            cout << this->vector_preturi_abonamente[
                this->nr_tipuri_abonamente - 1] << " lei.";
        }

        cout << endl;
    }

    ~SalaFitness()
    {
        if (this->vector_preturi_abonamente != nullptr)
        {
            delete[] this->vector_preturi_abonamente;
        }
    }
};

int SalaFitness::nr_sali = 0;

int main()
{
    SalaFitness salaDefault;
    salaDefault.afisare_sala();

    float* vector_preturi = new float[3] {159.99, 259.99, 300.99};

    SalaFitness* pPowerGym = new SalaFitness(
        1, "Andreas Gym", 3, vector_preturi
    );

    pPowerGym->afisare_sala();

    delete pPowerGym;
    delete[] vector_preturi;

    if (SalaFitness::nr_sali == 1)
    {
        cout << endl << "Am construit o sala de fitness!"
             << endl;
    }
    else
    {
        cout << endl << "Am construit "
             << SalaFitness::nr_sali
             << " sali de fitness!" << endl;
    }

    return 0;
}
