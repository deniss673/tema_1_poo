#include <random.hpp>
#include <iostream>
#include <string>
#include <array>
#include <cmath>


class tabla{
private:
    std::array<int,100> t_p;

public:
    int getNr(int x){return t_p[x];}

    tabla(){}

    tabla(const std::array<int,100> t_p_) : t_p{t_p_}{}

    tabla(const tabla& other): t_p{other.t_p}{}

    tabla& operator=(const tabla& other){
        t_p=other.t_p;
        return *this;
    }

    ~tabla(){}

    std::array<int,100> getArray(){
        return t_p;
    }

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
    const int getHp(){return hp;}

    std::array<int,2> getPoz(){
        std::array<int,2> pozitie{poz_cap,poz_coada};
        return pozitie;
    }


    barca(){}

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


class jucator {
    bool tip_jucator;
    tabla t;
    std::vector <barca> boats;
public:
    jucator() {}

    jucator(const bool tip_jucator_,const tabla t_, std::vector <barca> boats_) : tip_jucator{tip_jucator_}, t{t_},boats{boats_} {}

    jucator(const jucator &other) : tip_jucator(other.tip_jucator), t{other.t}, boats{other.boats} {}

    ~jucator() {}

    jucator &operator=(const jucator &other) {
        tip_jucator = other.tip_jucator;
        t = other.t;
        boats = other.boats;
        return *this;
    }


    /*friend std::ostream& operator<<(std::ostream& os, const jucator& j){
        os << "Jucator real="<<j.tip_jucator<<"cu tabla reprezentate astfel: "<<j.t<<"pl"<<j.nr_barci;
        return os;
    }*/

    tabla getTabla(){
        return t;
    }

    bool getType(){
        return tip_jucator;
    }


    int getNrBarci(){
        return boats.size();
    }

    std::vector<barca> getBarci(){
        return boats;
    }

    void afis_player() {
        std::cout<<" ";
        for (char x='A';x<='J';x++){
            std::cout<<" "<<x;
        }
        std::cout<<"\n";
        for(int i=0; i<10;i++){
            std::cout<<i;
            for(int j=0;j<10;j++){
                int y=i*10+j;
                if (t.getNr(y)==0)
                    std::cout<<" ~";
                else if (t.getNr(y)==-1)
                    std::cout<<" X";
                else if (t.getNr(y)==-2)
                    std::cout<<" @";
                else if (t.getNr(y)<5 && t.getNr(y)>0)
                    std::cout<<" "<<t.getNr(y);
            }
            std::cout<<"\n";
        }
    }
    void afis_enemy(){
        {
            std::cout<<" ";
            for (char x='A';x<='J';x++){
                std::cout<<" "<<x;
            }
            std::cout<<"\n";
            for(int i=0; i<10;i++){
                std::cout<<i;
                for(int j=0;j<10;j++){
                    int y=i*10+j;
                    if (t.getNr(y)>=0)
                        std::cout<<" ~";
                    else if (t.getNr(y)==-2)
                        std::cout<<" @";
                    else if (t.getNr(y)==-1){
                        std::cout<<" X";
                    }

                }
                std::cout<<"\n";
            }

        }
    }

};

class game {
    jucator player,enemy;
public:
    game(){}
    game(const jucator &player, const jucator &enemy) : player(player), enemy(enemy) {}
    ~game(){};
    game(const game& other):player(other.player),enemy(other.enemy){}
    game& operator=(const game& other){
        player=other.player;
        enemy=other.enemy;
        return *this;
    }
    int citire(std::string x){
        int nr=10*(x[1]-'0')+(x[0]-'A');
        return nr;
    }
    std::string conversie(int x){
        std::string a,b,c;
        a=('A'+x%10);
        b=('0'+x/10);
        c=a+b;
        return c;
    }


    int alegere(int a,std::array<int,100> x,int nr,bool test) {
        std::vector<int> v;
        std::string lit, cif, val, r;
        val = conversie(a);
        cif = val[1];
        lit = val[0];
        for (int i = 0; i <= 1; i++) {
            lit = val[0] + std::pow(-1, i) * (nr - 1);
            r = lit + cif;
            if (r[0] <= 'J' && r[0] >= 'A' && r[1] >= '0' && r[1] <= '9' ) {
                int nr = citire(r);
                if (x[nr]==0)
                    v.push_back(nr);
            }
        }
        lit = val[0];

        for (int i = 0; i <= 1; i++) {
            cif = val[1] + std::pow(-1, i) * (nr - 1);
            r = lit + cif;
            if (r[0] <= 'J' && r[0] >= 'A' && r[1] >= '0' && r[1] <= '9') {
                int nr = citire(r);
                if (x[nr]==0)
                    v.push_back(nr);
            }
        }
        int i;
        if(test==true) {
            std::cout << "Alege unde va fi celalat cap al barcii:\n";
            for (unsigned c = 0; c < v.size(); c++) {
                std::cout << c + 1 << "." << conversie(v[c]) << "\n";
            }
        }
        if(test==true) {
            std::cin >> i;
            while (0 > i || i > v.size()) {
                std::cout << "Introdu o varianta din cele afisate mai sus!\n";
                std::cin >> i;
            }
        }
        else{
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> random(1,v.size());
            i=random(rd);
        }
        return v[i-1];
    }

    tabla alegere_barci(bool test,std::vector<barca> &flota){
        int b2=0,b3=0;
        std::array<int,100> x{0};
        std::vector<barca> boats;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> random(0,99);
        while(b2!=3){
            std::string b;
            int a;
            if(test==true) {
                std::cout << "Alege unde va fi varful\n";
                std::cin >> b;
                a=citire(b);
                while(a<0 || a>99){
                    std::cout<<"Alege un input format din o litera de la A la J si o cifra de la 0 la 9!\n";
                    std::cin>>b;
                    a=citire(b);
                    std::cout<<b<<"\n";
                }
            }
            else{
                a=random(rd);
                while (x[a]!=0){
                    a=random(rd);
                }
            }
            if (x[a]!=0 && test==true){
                std::cout<<"Deja ai aici o barca\n";
                continue;
            }
            else{
                x[a]=2;
                int r=alegere(a,x,2,test);
                x[r]=2;
                b2++;
                barca boat{a,r,2};
                flota.push_back(boat);
            }
        }
        while(b3!=3){
            int a;
            std::string b;
            if(test==true) {
                std::cout << "Alege unde va fi varful\n";
                std::cin >> b;
                a = citire(b);
                while (a < 0 || a > 99) {
                    std::cout << "Alege un input format din o litera de la A la J si o cifra de la 0 la 9!\n";
                    std::cin >> b;
                    a = citire(b);
                }
            }
            else{
                a=random(rd);
                while (x[a]!=0){
                    a=random(rd);
                }
            }

            if (x[a]!=0 && test==true){
                std::cout<<"Deja ai aici o barca\n";
                continue;
            }
            else{
                x[a]=3;
                int r=alegere(a,x,3,test);
                x[r]=3;
                x[a-((a-r)/2)]=3;
                b3++;
                barca boat{a,r,3};
                flota.push_back(boat);
            }
        }
        tabla t{x};

        return t;
    }

    std::array<jucator,2> preparation(){
        std::cout<<"Bine ai venit la Batalia de pe Dunare\n";
        std::vector<barca> flota_player;
        std::vector<barca> flota_enemy;
        jucator player{true, alegere_barci(true,flota_player),flota_player},enemy{false, alegere_barci(false,flota_enemy),flota_enemy};
        std::cout<<"Tabla ta:\n";
        player.afis_player();
        std::cout<<"\nTabla inamicului: \n";
        enemy.afis_enemy();
        std::array<jucator,2> endpreparation{player,enemy};
        return endpreparation;
    }


    int attack(bool tip){
        int output;
        if (tip == true) {
            std::string input;
            std::cin >> input;
            output = citire(input);
            while (output < 0 || output > 99) {
                std::cout << "Alege un input format din o litera de la A la J si o cifra de la 0 la 9!\n";
                std::cin >> input;
                output = citire(input);
            }

        }
        else {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> random(0, 99);
            output = random(rd);
        }
        return output;
    }

    jucator player_changes(jucator player,bool tip){
        int output;
        if (tip==true) {
            std::cout << "Alege unde ataci!\n";
        }
        output=attack(tip);
        std::vector<barca> aux_v = player.getBarci();
        tabla t_player = player.getTabla();
        std::array aux = t_player.getArray();
        std::vector<barca> new_v;
        std::array<int, 2> poz{0};
        bool test=true;
        while (t_player.getNr(output) < 0 && tip==true) {
            std::cout << "Ai mai lovit o data aici, alege alt loc!\n";
            output=attack(tip);
        }
        while (t_player.getNr(output) < 0 && tip==false) {
            output=attack(tip);
        }
        if (t_player.getNr(output) == 0) {
            aux[output] = -1;
            test=false;
        }
        else {

            aux[output] = -2;
            int i;
            for (i = 0; i < player.getNrBarci(); i++) {
                poz = aux_v[i].getPoz();
                if (poz[0] == output || poz[1] == output || poz[0] + 10 == output || poz[0] - 10 == output ||
                poz[0] - 1 == output || poz[0] + 1 == output) {
                    if (aux_v[i].getHp() == 1) {
                        if(tip==true){
                            std::cout<<"Ai distrus o barca a inamicului!\n";
                        }
                        else{
                            std::cout<<"Ti-a fost distrusa o barca!\n";
                        }
                    }
                    else {
                        barca aux_barca{poz[0], poz[1], aux_v[i].getHp() - 1};
                        new_v.push_back(aux_barca);
                    }
                    }
                new_v.push_back(aux_v[i]);
            }

            /*std::cout<<"**********************\n";
            new_player.afis_player();
            std::cout<<"**********************\n";
            */
        }
        tabla new_tabla{aux};
        if(test==false)
            new_v=aux_v;
        jucator new_player{tip,new_tabla,new_v};

        return new_player;

    }

    void game_turn(jucator &player, jucator &enemy){
        jucator new_player = player_changes(player, false);
        jucator new_enemy = player_changes(enemy, true);
        std::array<jucator, 2> answer{new_player, new_enemy};
        std::cout << "Tabla ta:\n";
        new_player.afis_player();
        std::cout << "\nTabla inamicului: \n";
        new_enemy.afis_enemy();
        player=new_player;
        enemy=new_enemy;
    }



    void midgame(std::array<jucator,2> endpreparation){
        jucator player=endpreparation[0],enemy=endpreparation[1];
        int player_boats=player.getNrBarci(),enemy_boats=enemy.getNrBarci();
        while(player_boats!=0 && enemy_boats!=0){
            game_turn(player,enemy);
            player_boats=player.getNrBarci();
            enemy_boats=enemy.getNrBarci();
        }
        if(player_boats==0){
            std::cout<<"Imi pare rau ai pierdut!\n";
        }
        else{
            std::cout<<"Felicitari ai castigat!\n";
        }

    }
    bool endgame(){
        std::string answer;
        std::cout<<"Vrei sa mai joci? Y/N\n";
        std::cin>>answer;
        if (answer=="N" || answer=="n"){
            return false;
        }
        else if(answer=="Y" || answer=="N"){
            return true;
        }
    }

    void startgame(){
        midgame(preparation());
        if(endgame())
            startgame();
    }
};

int main(){
    game joc;
    joc.startgame();
    return 0;
}

/*rlutil */
