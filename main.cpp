#include <rlutil.h>
#include <digestpp.hpp>
#include <random.hpp>
#include <csv.hpp>
#include <date.h>
#include <iostream>
#include <cctype>
#include <chrono>
#include <thread>
#include <string>
#include <utility>
#include <array>



class tabla{
private:
    std::array<int,100> t_p;

public:
    int const getNr(int x){return t_p[x];}

    tabla(const std::array<int,100> t_p_) : t_p{t_p_}{}

    tabla(const tabla& other): t_p{other.t_p}{}

    tabla& operator=(const tabla& other){
        t_p=other.t_p;
        return *this;
    }

    ~tabla(){}

    /*friend std::ostream& operator<<(std::ostream& os, const tabla& t){
        os << "Tabla este reprezentata de "<<t.t_p;
        return os;
    }*/



};

class barca {
private:
    int hp;
    int poz_cap;
    int poz_coada;

public:
    int const getHp(int x){return hp;}

    barca(const int poz_cap_,int poz_coada_, int hp_) : poz_cap{poz_cap_},poz_coada{poz_coada_},hp{hp_}{};

    barca(const barca& other): poz_cap{other.poz_cap},poz_coada{other.poz_coada},hp{other.hp}{};

    barca& operator=(const barca& other){
        poz_cap=other.poz_cap;
        poz_coada=other.poz_coada;
        hp=other.hp;
        return *this;
    }
    ~barca(){}

    friend std::ostream& operator<<(std::ostream& os, const barca& b){
        os << "Barca care pleaca din" << b.poz_cap << "pana in" <<b.poz_coada << "are "<< b.hp<< "puncte de viata";
        return os;

    }

};

void afisare_tabla_p(tabla a){
    std::cout<<" ";
    for (char x='A';x<='J';x++){
        std::cout<<" "<<x;
    }
    std::cout<<"\n";
    for(int i=0; i<10;i++){
        std::cout<<i;
        for(int j=0;j<10;j++){
            int y=i*10+j;
            if (a.getNr(y)==0)
                std::cout<<" ~";
            else if (a.getNr(y)==-1)
                std::cout<<" X";
            else if (a.getNr(y)<5 && a.getNr(y)>0)
                std::cout<<" "<<a.getNr(y);
        }
        std::cout<<"\n";
    }
}

void afisare_tabpla_i(tabla a){
    std::cout<<" ";
    for (char x='A';x<='J';x++){
        std::cout<<" "<<x;
    }
    std::cout<<"\n";
    for(int i=0; i<10;i++){
        std::cout<<i;
        for(int j=0;j<10;j++){
            int y=i*10+j;
            if (a.getNr(y)==0)
                std::cout<<" ~";
            else if (a.getNr(y)==-1)
                std::cout<<" @";
            else if (a.getNr(y)==1){
                std::cout<<" X";
            }

        }
        std::cout<<"\n";
    }

}

int citire(std::string x){
    int nr=10*(x[1]-'0')+(x[0]-'A');
    return nr;
}

class jucator{
    bool tip_jucator;
    tabla t;
public:
    jucator(const bool tip_jucator_, tabla t_) : tip_jucator{tip_jucator_},t{t_}{};
    jucator(const jucator& other):tip_jucator(other.tip_jucator),t{other.t}{};
    ~jucator(){}
    jucator& operator=(const jucator& other){
        tip_jucator=other.tip_jucator;
        t=other.t;
        return *this;
    }
    /*friend std::ostream& operator<<(std::ostream& os, const jucator& j){
        os << "Jucator real="<<j.tip_jucator<<"cu tabla reprezentate astfel: "<<j.t.t_p;
        return os;
    }*/
    void afis() {
        if (tip_jucator == true) {
            afisare_tabla_p(t);
        }
        else {
            afisare_tabpla_i(t);
        }
    }
};

std::string conversie(int x){
    std::string a,b,c;
    a=('A'+x%10);
    b=('0'+x/10);
    c=a+b;
    return c;
}



int alegere(int a,std::array<int,100> x,int nr){
    std::vector<int> v;
    int val;
    if(x[a-nr+1]==0){
        val=a-nr+1;
        v.push_back(val);
    }
    if(x[a+nr-1]==0){
        val=a+nr-1;
        v.push_back(val);
    }
    if(x[a-10*(nr-1)]==0){
        val=a-10*(nr-1);
        v.push_back(val);
    }
    if(x[a+10*(nr-1)]==0){
        val=a+10*(nr-1);
        v.push_back(val);
    }
    int i;
    std::cout<<"Alege unde va fi celalat cap al barcii:\n";
    for(unsigned c=0;c<v.size();c++){
        std::cout<<c+1<<"."<<conversie(v[c])<<"\n";
    }
    std::cin>>i;
    while(0>i || i>=v.size()){
        std::cout<<"Introdu o varianta din cele afisate mai sus!\n";
        std::cin>>i;
    }
    return v[i];
}

void alegere_barci(std::array<int,100> &x){
    int b2=0,b3=0;
    while(b2!=3){
        std::string b;
        std::cout<<"Alege unde va fi catarmul\n";
        std::cin>>b;
        int a=citire(b);
        while(a<0 || a>99){
            std::cout<<"Alege un input format din o litera de la A la J si o cifra de la 0 la 9!\n";
            std::cin>>b;
            a=citire(b);
        }

        if (x[a]!=0){
            std::cout<<"Deja ai aici o barca\n";
            continue;
        }
        else{
            x[a]=2;
            int r=alegere(a,x,2);
            x[r]=2;
            b2++;
        }
    }
    while(b3!=3){
        std::string b;
        std::cout<<"Alege unde va fi catarmul\n";
        std::cin>>b;
        int a=citire(b);
        while(a<0 || a>99){
            std::cout<<"Alege un input format din o litera de la A la J si o cifra de la 0 la 9!\n";
            std::cin>>b;
            a=citire(b);
        }
        if (x[a]!=0){
            std::cout<<"Deja ai aici o barca\n";
            continue;
        }
        else{
            x[a]=3;
            int r=alegere(a,x,3);
            x[r]=3;
            x[a+(a-r)/2]=3;
            b3++;
        }
    }
}

int main(){
    bool game=true;
    while(game){
        std::array<int,100> x{0};
        alegere_barci(x);
        tabla t{x};
        jucator eu{true,t};
        eu.afis();
        game=false;
    }


    return 0;
}

/*rlutil */
