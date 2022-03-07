#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>

class Numar_Complex {
private:
    double real, imag;
public:

    //constructorii get si set
    double getreal() const {
        return real;
    }

    double getimag() const {
        return imag;
    }

    void setreal(const double a) {
        this->real = a;
    };

    void setimag(const double b) {
        this->imag = b;
    };

    //constructori de initializare si copiere
    Numar_Complex(){
        real = 0;
        imag = 0;
    }
    Numar_Complex(const double real_, double imag_) {
        real = real_;
        imag = imag_;
    }

    Numar_Complex(const Numar_Complex &b) {
        real = b.getreal();
        imag = b.getimag();
    }

    double modul() const {
        return sqrt((real * real) + (imag * imag));
    };

    //rescrierea operatorilor
    Numar_Complex operator+(const Numar_Complex &rhs) const {
        //std::cout << "Adunare" << std::endl;
        return Numar_Complex(real + rhs.real, imag + rhs.imag);
    }

    Numar_Complex operator*(const Numar_Complex &rhs) const {
        //std::cout << "Inmultire" << std::endl;
        return Numar_Complex((real * rhs.real) - (imag * rhs.imag), (real * rhs.imag) + (imag * rhs.real));
    }

    Numar_Complex operator/(const Numar_Complex &rhs) const {
        // std::cout << "Impartire" << std::endl;
        if(rhs.real != 0 && rhs.imag != 0)
        {
            return Numar_Complex(((real * rhs.real) + (imag * rhs.imag)) / ((rhs.real * rhs.real) + (rhs.imag * rhs.imag)),
                                 ((rhs.real * imag) - (real * rhs.imag)) / ((rhs.real * rhs.real) + (rhs.imag * rhs.imag)));
        }
        //std::cout<<"Nu se poate!\n";
    }

    friend std::istream &operator>>(std::istream &is, Numar_Complex &x) {
        std::cout<<"parte reala=";
        is >> x.real;
        std::cout<<"parte imaginara=";
        is >> x.imag;
        return is;
    };

    friend std::ostream &operator<<(std::ostream &os, Numar_Complex &x) {
        os << x.real << "+i*" << x.imag;
        return os;
    };

    void afisare() const {
        std::cout << real;
        if (imag != 0) std::cout << "+i*" << imag;
    }

    //declararea clasei friend
    friend class Matrice_Complexa;
};

class Matrice_Complexa{
private:
    int n,m;
    Numar_Complex *matrice;

public:
    //constructorii get si set
    int getn(){
        return n;
    }
    int getm(){
        return m;
    }
    Numar_Complex getelem(){
        return matrice[0];
    }
    void setn(int a){
        this->n = a;
    }
    void setm(int a){
        this->m = a;
    }
    void getelem(Numar_Complex a){
        this->matrice[0] = a;
    }

    //constructorii de initializare si copiere
    Matrice_Complexa(Numar_Complex elem,int n_, int m_){
        matrice = new Numar_Complex[1000];
        n = n_;
        m = m_;
        for(int i=0;i<n;i++)
            for(int j=0;j<m;j++)
                matrice[i*n+j] = elem;
    };

    Matrice_Complexa(const Matrice_Complexa &mat){
        matrice = new Numar_Complex[1000];
        n = mat.n;
        m = mat.m;
        for(int i=0;i<n;i++)
            for(int j=0;j<m;j++)
                matrice[i*n+j] = mat.matrice[i*n+j];

    };

    Matrice_Complexa(){
        matrice = new Numar_Complex[1000];
        n = 0;
        m = 0;
    };

    // rescrierea operatorilor
    Matrice_Complexa operator+(const Matrice_Complexa &rhs) const {
        return Matrice_Complexa(rhs.matrice[0] + matrice[0], n, m);
    };

    Matrice_Complexa operator*(const Matrice_Complexa &rhs) const {
        Numar_Complex aux(n,0);
        return Matrice_Complexa((rhs.matrice[0]*matrice[0])*aux, n, rhs.m);
    };

    friend std::istream &operator>>(std::istream &is, Matrice_Complexa &x) {
        Numar_Complex aux(0,0);
        is >> aux;
        is >> x.n;
        is >> x.m;
        for(int i=0;i<x.n;i++)
            for(int j=0;j<x.m;j++)
                x.matrice[i*x.n+j] = aux;
        return is;
    };

    friend std::ostream &operator<<(std::ostream &os, Matrice_Complexa &x) {
        os <<x.n<<" "<<x.m<<std::endl;
        for(int i=0;i<x.n;i++)
        {
            for(int j=0;j<x.m;j++) {
                os << std::setw(8);
                os << x.matrice[i*x.n+j];
            }
            os << std::endl;
        }
        return os;
    };

    void afisare(){
        std::cout<<"( "<<matrice[0]<<", "<<n<<", "<<m<<");\n";
    }
    //destructor matrice
    ~Matrice_Complexa(){
        delete[] matrice;
    }
};

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// !!                                                           !!
// !!     De aici in jos este codul pentru meniul din consola.  !!
// !!                                                           !!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

std::vector<Matrice_Complexa> v;
int meniu();
int inserare(){
    int n,m;
    Numar_Complex aux;
    std::cout<<"Numar linii=";std::cin>>n;
    std::cout<<"Numar coloane=";std::cin>>m;
    std::cout<<"Element:\n";std::cin>>aux;
    Matrice_Complexa y(aux,n,m);
    v.push_back(y);
    return meniu();
}

int adunare(){
    int a,b;
    std::cout<<"Nr. matrice a:"; std::cin>>a;
    std::cout<<"\nNr. matrice b:"; std::cin>>b;
    if(v[a].getn() != v[b].getn() || v[a].getm() != v[b].getm() || b >= v.size() || a >= v.size())
    {
        std::cout<<"Nu se poate realiza adunarea!\n";
        system("PAUSE");
        return meniu();
    }
    Matrice_Complexa aux(v[a]+v[b]);
    std::cout<<"\n"<<aux<<"Doriti sa inserati matricea creata in lista?(1/0)\n";
    std::cin>>a;
    if(a == 1) v.push_back(aux);
    return meniu();
}

int inmultire(){
    int a,b;
    std::cout<<"Nr. matrice a:"; std::cin>>a;
    std::cout<<"\nNr. matrice b:"; std::cin>>b;
    if(b >= v.size() || a >= v.size())
    {
        std::cout<<"Nu se poate realiza inmultirea!\n";
        system("PAUSE");
        return meniu();
    }
    Matrice_Complexa aux(v[a]*v[b]);
    std::cout<<aux;
    std::cout<<"Doriti sa inserati matricea creata in lista?(1/0)";
    std::cin>>a;
    std::cout<<a;
    system("PAUSE");
    Matrice_Complexa y(aux.getelem(),aux.getn(),aux.getm());
    v.push_back(y);
    return meniu();
}
int afisare(){
    int x;
    std::cout<<"Matricea dorita a se afisa:";
    std::cin>>x;
    std::cout<<v[x];
    system("PAUSE");
    return meniu();
}
int listare(){
    for(int i=0;i<v.size();i++)
    {
        std::cout<<i<<":";
        v[i].afisare();
    }
    system("PAUSE");
    return meniu();
}
int meniu(){
    int x;
    std::cout<<"\nOptiunea se alege inserand nr. optiunei respective!Matricele sunt numerotate de la 0 in lista lor!\nAlegeti optiunea:\n0.Inchidere meniu!\n1.Inserare matrice noua.\n2.Adunare matrice a cu matrice b.(daca este posibil)\n3.Inmultire matrice a cu matrice b.\n4.Afisare matrice a.\n5.Listare matrice\n";
    std::cin>>x;

    if(x == 0) return 0;
    if(x == 1) inserare();
    if(x == 2) adunare();
    if(x == 3) inmultire();
    if(x == 4) afisare();
    if(x == 5) listare();
    else{
        std::cout<<"Numarul ales nu face parte din optiuni\n";
        return meniu();
    }
}
int main() {
    meniu();
    return 0;
}