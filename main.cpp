#include <iostream>
#include <string.h>

class obiect{
public:
    int x,y,h;
    char forma[20];
};
int main() {
    obiect ob1;
    std::cout<<"Forma este: "; std::cin>>ob1.forma;
    if(!strcmp(ob1.forma,"dreptunghi")) {
        std::cout << "Latura mica: ";
        std::cin >> ob1.x;
        std::cout << "Latura mare: ";
        std::cin >> ob1.y;
        std::cout<<"Inaltime: "; std::cin>>ob1.h;
        std::cout<<"Unt folosit: "<<2*(ob1.x*ob1.y+ob1.x*ob1.h+ob1.y*ob1.h)<<"grame\n";
        std::cout<<"Gem folosit: "<<float(ob1.x*ob1.y*ob1.h/2.0)<<"grame\n";
    }
    if(!strcmp(ob1.forma,"patrat")) {
        std::cout << "Latura: ";
        std::cin >> ob1.x;
        std::cout<<"Inaltime: "; std::cin>>ob1.h;
        std::cout<<"Unt folosit: "<<2*(ob1.x*ob1.x+2*ob1.x*ob1.h)<<"grame\n";
        std::cout<<"Gem folosit: "<<float(ob1.x*ob1.x*ob1.h/2.0)<<"grame\n";
    }
    if(!strcmp(ob1.forma,"cerc")) {
        std::cout << "Raza: ";
        std::cin >> ob1.x;
        std::cout<<"Inaltime: "; std::cin>>ob1.h;
        std::cout<<"Unt folosit: "<<float(2*ob1.x*ob1.x*3.14+2*3.14*ob1.h)<<"grame\n";
        std::cout<<"Gem folosit: "<<float(2*ob1.x*ob1.x*3.14*ob1.h/2)<<"grame\n";
    }


    return 0;
}
