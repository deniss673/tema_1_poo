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



};

class barca_2 {
private:
    int hp=2;
    int poz_cap;
    int poz_coada;

public:
    int const getHp(int x){return hp;}

    barca_2(const int poz_cap_,int poz_coada_, int hp_) : poz_cap{poz_cap_},poz_coada{poz_coada_},hp{hp_}{};

    barca_2(const barca_2& other): poz_cap{other.poz_cap},poz_coada{other.poz_coada},hp{other.hp}{};

    barca_2& operator=(const barca_2& other){
        poz_cap=other.poz_cap;
        poz_coada=other.poz_coada;
        hp=other.hp;
        return *this;
    }
    ~barca_2(){}

    friend std::ostream& operator<<(std::ostream& os, const barca_2& b2){
        os << "Barca care pleaca din" << b2.poz_cap << "pana in" <<b2.poz_coada << "are "<< b2.hp<< "puncte de viata";
        return os;

    }

};

class barca_3 {
private:
    int hp=3;
    int poz_cap;
    int poz_coada;
public:
    int const getHp(){return hp;}

    barca_3(const int poz_cap_,int poz_coada_, int hp_) : poz_cap{poz_cap_},poz_coada{poz_coada_},hp{hp_}{};

    barca_3(const barca_3& other): poz_cap{other.poz_cap},poz_coada{other.poz_coada},hp{other.hp}{};

    barca_3& operator=(const barca_3& other){
        poz_cap=other.poz_cap;
        poz_coada=other.poz_coada;
        hp=other.hp;
        return *this;
    }

    ~barca_3(){}

    friend std::ostream& operator<<(std::ostream& os, const barca_3& b3){
        os << "Barca care pleaca din" << b3.poz_cap << "pana in" <<b3.poz_coada << "are "<< b3.hp<< "puncte de viata";
        return os;

    }

    void incaMerge(){
        if (getHp()==0){
            std::cout<<"Ai pierdut o barca! :(";
        }
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

int main(){
    std::array<int,100> x;
    for(int i=0;i<100;i++){
        if (i==30){
            x[i]=-1;
        }
        else if (i==31){
            x[i]=2;
        }
        else if (i==32){
            x[i]=3;
        }
        else
            x[i]=0;
    }
    tabla player{x};

    afisare_tabla_p(player);


    afisare_tabla_p(player);


    std::cout<<"GATA JOACA";

    return 0;
}

/*rlutil */
