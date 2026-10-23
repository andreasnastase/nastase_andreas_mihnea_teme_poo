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
    
    int getNr_tipuri_abonamente()
    {
        return this->nr_tipuri_abonamente;
    }
    
    void setNr_tipuri_abonamnete(int nr_abonamente_nou)
    {
        if(nr_abonamente_nou >= 0)
        {
            this->nr_tipuri_abonamente = nr_abonamente_nou;
        }
        else
        { 
            throw exception();
        }
    }
    
    float* getVector_preturi_abonamente()
    {
        float* vector_preturi_nou = new float[this->nr_tipuri_abonamente];
        for(int i=0; i < this->nr_tipuri_abonamente; i++)
        {
            vector_preturi_nou[i] = this->vector_preturi_abonamente[i];   
        }
        return vector_preturi_nou;
    }
    
    void setVector_preturi_abonamente(float* vector, int nrTA)
    {
        setNr_tipuri_abonamnete(nrTA);
        if (this->vector_preturi_abonamente != nullptr)
        {
            delete[] this->vector_preturi_abonamente;
        }
        this->vector_preturi_abonamente = new float[this->nr_tipuri_abonamente];
        for(int i=0; i < this->nr_tipuri_abonamente ; i++)
        {
            this->vector_preturi_abonamente[i] = vector[i];
        }
        delete[] vector;
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
    try
    {
        salaDefault.setNr_tipuri_abonamnete(2);
    }
    catch(...)
    {
        cout << endl << "Numarul de abonamente este negativ!";
    }
    
    cout << endl << "Noul numar de abonamente este: " << salaDefault.getNr_tipuri_abonamente() << endl;

    salaDefault.setVector_preturi_abonamente(new float[3] {129.99, 169.99, 199.99}, 3);
    float* vector = salaDefault.getVector_preturi_abonamente();
    
    cout << endl << "Noile preturi sunt: ";
    for(int i = 0; i < 3; i++)
    {
        if (i!=2)
        {
            cout << vector[i] << " lei,";
        }
        else cout << vector[i] << " lei." << endl;
    }
    salaDefault.afisare_sala();
    delete[] vector;


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
