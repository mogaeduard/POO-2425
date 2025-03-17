#include <iostream>
#include <vector>

using namespace std;

// CLASA MOTOR
class Motor
{
private:
    string tipCombustibil;
    double consum;
public:
    Motor(string tipCombustibil = "Necunoscut", double consum = 0.0); // constructor

    void setConsum(double consum); // seteaza consumul
    double getConsum() const; // returneaza consumul
    double calculeazaConsum(double distanta) const; // calculeaza consumul pentru o distanta
    void afisare() const; // cam self explanatory
};

Motor::Motor(string tipCombustibil, double consum)
{
    this->tipCombustibil = tipCombustibil;
    this->consum = consum;
}

void Motor::setConsum(double consum)
{
    this->consum = consum;
}

double Motor::getConsum() const
{
    return this->consum;
}

double Motor::calculeazaConsum(double distanta) const
{
    return (consum * distanta) / 100.0;
}


void Motor::afisare() const
{
    cout << "Tip combustibil: " << tipCombustibil << "\n";
    cout << "Consum: " << consum << " litri/100 km\n";
}


//  CLASA AUTOVEHICUL
class Autovehicul
{
private:
    string marca;
    string model;
    int an_fabricatie;
    int pret;
    Motor motor; // motorul masinii (relatie de compunere)
public:
    Autovehicul(string marca = "Necunoscut", string model = "Necunoscut", int an_fabricatie = 0, int pret = 0, string tipCombustibil = "Necunoscut", double consum = 0.0);

    void display() const; // afiseaza detaliile masinii

    Autovehicul(const Autovehicul& other); // constructor de copiere

    Autovehicul& operator=(const Autovehicul& other); // operator de atribuire

    ~Autovehicul(); // destructor

    void citire(istream& in); // citeste detaliile masinii

    void afisare(ostream& out) const; // afiseaza detaliile masinii intr-un stream

    friend istream& operator>>(istream& in, Autovehicul& a); // supraincarcare pentru citire

    friend ostream& operator<<(ostream& out, const Autovehicul& a); // supraincarcare pentru afisare

    Autovehicul& operator+=(int euro); // adauga o suma la pret

    friend Autovehicul operator+(const Autovehicul& a1, const Autovehicul& a2); // combina doua masini
};

Autovehicul::Autovehicul(string marca, string model, int an_fabricatie, int pret,
                         string tipCombustibil, double consum)
    : marca(marca), model(model), an_fabricatie(an_fabricatie), pret(pret),
      motor(tipCombustibil, consum) {}

void Autovehicul::display() const
{
    cout << "Marca: " << marca << "\n";
    cout << "Model: " << model << "\n";
    cout << "An fabricatie: " << an_fabricatie << "\n";
    cout << "Pret: " << pret << " EUR\n";
    cout << "Detalii motor:\n";
    motor.afisare();
    cout << '\n';
}

Autovehicul::Autovehicul(const Autovehicul& other)
{
    this->marca = other.marca;
    this->model = other.model;
    this->an_fabricatie = other.an_fabricatie;
    this->pret = other.pret;
    this->motor = other.motor;
}

Autovehicul& Autovehicul::operator=(const Autovehicul& other)
{
    if (this != &other) // verificam auto-atribuirea
    {
        this->marca = other.marca;
        this->model = other.model;
        this->an_fabricatie = other.an_fabricatie;
        this->pret = other.pret;
        this->motor = other.motor;
    }
    return *this;
}

Autovehicul::~Autovehicul()
{
    cout << "Destructor apelat pentru " << marca << " " << model << '\n' << '\n';
}

void Autovehicul::citire(istream& in)
{
    cout << "Introdu marca masinii: ";
    in >> this->marca;
    cout << "Introdu modelul masinii: ";
    in >> this->model;
    cout << "Introdu anul fabricatiei: ";
    in >> an_fabricatie;
    cout << "Introdu pretul masini: ";
    in >> pret;

    string tipCombustibil;
    double consum;
    cout << "Introdu tipul de combustibil al motorului: ";
    in >> tipCombustibil;
    cout << "Introdu consumul motorului (litri/100 km): ";
    in >> consum;

    this->motor = Motor(tipCombustibil, consum);
}

void Autovehicul::afisare(ostream& out) const
{
    out << "Marca: " << marca << "\nModel: " << model << "\nAn Fabricatie: " << an_fabricatie << "\nPret: " << pret;
}

istream& operator>>(istream& in, Autovehicul& a)
{
    a.citire(in);
    return in;
}

ostream& operator<<(ostream& out, const Autovehicul& a)
{
    a.afisare(out);
    return out;
}

Autovehicul& Autovehicul::operator+=(int euro)
{
    this->pret += euro;
    return *this;
}

Autovehicul operator+(const Autovehicul& a1, const Autovehicul& a2)
{
    string marcaNoua = a1.marca + "-" + a2.marca; // combina marciile
    string modelNou = a1.model + "-" + a2.model; // combina modelele
    return Autovehicul(marcaNoua, modelNou, a1.an_fabricatie - a2.an_fabricatie, a1.pret + a2.pret);
}

// CLASA PROPRIETAR
class Proprietar
{
private:
    string nume;
    Autovehicul* autovehicul; // pointer catre masina detinuta (relatia de agregare)
public:
    Proprietar(string nume = "Necunoscut", Autovehicul* autovehicul = nullptr);  // constructor

    void setAutovehicul(Autovehicul* autovehicul); // seteaza masina proprietarului


    void afiseazaDetalii() const; // afiseaza detaliile proprietarului si ale masinii

};


Proprietar::Proprietar(string nume, Autovehicul* autovehicul)
{
    this->nume = nume;
    this->autovehicul = autovehicul;
}

void Proprietar::setAutovehicul(Autovehicul* autovehicul)
{
    this->autovehicul = autovehicul;
}

void Proprietar::afiseazaDetalii() const
{
    cout << "Nume proprietar: " << nume << "\n";
    if (autovehicul)
    {
        cout << "Detalii autovehicul:\n";
        autovehicul->display();
    }
    else
    {
        cout << "Proprietarul nu are autovehicul.\n";
    }
}



// MENIU INTERACTIV
void uiMeniu()
{
    cout<<"+++++++++++++++++++++++++++++++"<<endl;
    cout<<" Introdu 1 pentru a citi n autovehicule."<<endl;
    cout<<" Introdu 2 pentru a afisa autovehiculele. "<<endl;
    cout<<" Introdu 3 pentru a adauga un pret unei masini existente."<<endl;
    cout<<" Pentru a iesi din program apasa 0"<<endl;
    cout<<"-----------------------------\n"<<endl;
}

// gestioneaza meniul interactiv
void meniu(vector <Autovehicul>& autovehicule)
{
    bool stop = false;
    int opt;
    while(stop == false)
    {
        uiMeniu();
        cout<<"Introdu optiunea: ";
        cin>>opt;

        switch (opt)
        {
        case 1: // citeste n autovehicule
            int n;
            cout << "Introdu numarul de autovehicule: ";
            cin >> n;

            for (int i = 0; i <n; i++)
            {
                Autovehicul a;
                cout << "\nIntrodu datele pentru autovehiculul " << i +10
                 << ":\n";
                cin >> a;
                autovehicule.push_back(a); // adauga autovehiculul in vector
            }
            break;

        case 2: // afiseaza toate autovehiculele
            cout << "\nDetaliile autovehiculelor introduse:\n";
            for (int i = 0; i <= autovehicule.size(); i++)
            {
                cout << "Autovehicul " << i +1<< ":\n";
                autovehicule[i].display();
            }
            break;

        case 3: // adauga un pret unei masini existente
            if (autovehicule.empty())
            {
                cout << "Nu exista autovehicule in lista.\n";
                break;
            }

            int index, euro;
            cout << "Introdu indexul autovehiculului (1-" << autovehicule.size() << "): ";
            cin >> index;

            if (index < 1 || index > autovehicule.size())
            {
                cout << "Index invalid!\n";
                break;
            }

            cout << "Introdu suma de adaugat la pret (EUR): ";
            cin >> euro;

            autovehicule[index-1] += euro; // folosim operatorul +=
            cout << "Pretul a fost actualizat.\n";
            break;
        case 0: // iesire din program
            stop = true;
            break;
        default:
            cout << "Optiune nevalida! Incearca din nou.\n";
        }

        system("pause");
        system("cls");
    }
}

int main()
{
    vector<Autovehicul> autovehicule;
    meniu(autovehicule); // ruleaza meniul interactiv

    return 0;
}
