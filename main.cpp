#include <random.hpp>
#include <iostream>
#include <string>
#include <array>
#include <cmath>
#include <utility>




class tabla{
private:
    std::array<int,100> t_p;

public:
    int getNr(int x){return t_p[x];}

    tabla()=default;

    explicit tabla(const std::array<int,100> t_p_) : t_p{t_p_}{}

    tabla(const tabla& other)= default;

    tabla& operator=(const tabla& other){
        t_p=other.t_p;
        return *this;
    }



    ~tabla()= default;

    std::array<int,100> getArray(){
        return t_p;
    }
    friend std::ostream& operator<<(std::ostream& os, const tabla& t){
        for(int i=0;i<100;i++){
            os<<t.t_p[i];
        }
        return os;
    }
};

class barca {
private:
    int poz_cap;
    int poz_coada;
    int hp;

public:

    barca(){
        poz_coada=0;
        poz_cap=0;
        hp=0;
    }

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
    bool tip_jucator{};
    tabla t{};
    std::vector<barca> boats;
    int hp = 2 * 3 + 3 * 3;
public:
    jucator() = default;

    jucator(const bool tip_jucator_, const tabla &t_, std::vector<barca> boats_, const int hp_) : tip_jucator{
            tip_jucator_}, t{t_}, boats{std::move(boats_)}, hp{hp_} {}

    jucator(const jucator &other) : tip_jucator(other.tip_jucator), t{other.t}, boats{other.boats}, hp{other.hp} {}

    ~jucator() {}

    jucator &operator=(const jucator &other) {
        tip_jucator = other.tip_jucator;
        t = other.t;
        boats = other.boats;
        hp = other.hp;
        return *this;
    }


    friend std::ostream &operator<<(std::ostream &os, const jucator &j) {
        os << "Jucator real=" << j.tip_jucator << "cu tabla reprezentate astfel: " << j.t << "si cu hp=" << j.hp
           << " cu barcile= ";
        for (auto i = 0ull; i < j.boats.size(); i++) {
            os << j.boats[i];
        }
        return os;
    }

    tabla getTabla() {
        return t;
    }

    int getHp() const {
        return hp;
    }


    bool getType() {
        return tip_jucator;
    }

    void change(int new_hp, const tabla &new_t){
        hp=new_hp;
        t=new_t;
    }


    void afis_player() {
        std::cout << " ";
        for (char x = 'A'; x <= 'J'; x++) {
            std::cout << " " << x;
        }
        std::cout << "\n";
        for (int i = 0; i < 10; i++) {
            std::cout << i;
            for (int j = 0; j < 10; j++) {
                int y = i * 10 + j;
                if (t.getNr(y) == 0)
                    std::cout << " ~";
                else if (t.getNr(y) == -1)
                    std::cout << " X";
                else if (t.getNr(y) == -2)
                    std::cout << " @";
                else if (t.getNr(y) < 5 && t.getNr(y) > 0) {
                    if (tip_jucator == true)
                        std::cout << " " << t.getNr(y);
                    else
                        std::cout << " " << "X";
                }
            }
            std::cout << "\n";
        }
    }
};


class game {
    jucator player1,player2;
public:
    game(){}
    game(const jucator &player1, const jucator &player2) : player1(player1), player2(player2) {}
    ~game(){};
    game(const game& other):player1(other.player1),player2(other.player2){}
    game& operator=(const game& other){
        player1=other.player1;
        player2=other.player2;
        return *this;
    }
    friend std::ostream& operator<<(std::ostream& os, const game& joc){
        os << "Jucatorul 1= "<<joc.player1<<"\nJucatorul 2= "<<joc.player2;
        return os;
    }

    static int citire(std::string x){
        int nr=10*(x[1]-'0')+(x[0]-'A');
        return nr;
    }
    static std::string conversie(int x){
        std::string a,b,c;
        a=('A'+x%10);
        b=('0'+x/10);
        c=a+b;
        return c;
    }

    void alegere_for(std::vector<int> &v,const std::array<int,100> x,int nr,std::string val,const std::string &lit,const std::string &cif){
        std::string r;
        std::string aux;
        for (int i = 0; i <= 1; i++) {
            if (lit==""){
                aux = val[0] + std::pow(-1, i) * (nr - 1);
                r=aux+cif;
            }
            else if(cif==""){
                aux = val[1] + std::pow(-1, i) * (nr - 1);
                r = lit + aux;
            }
            if (r[0] <= 'J' && r[0] >= 'A' && r[1] >= '0' && r[1] <= '9' ) {
                int output;
                output= citire(r);
                if (x[output]==0){
                    v.push_back(output);
                }
            }
        }
    }

    int alegere(int a,const std::array<int,100> x,int nr,bool test) {
        std::vector<int> v;
        std::string lit, cif, val;
        val = conversie(a);
        lit=val[0];
        cif=val[1];
        alegere_for(v,x,nr,val,lit,"");
        alegere_for(v,x,nr,val,"",cif);
        int i;
        if(test==true) {
            std::cout << "Alege unde va fi celalat cap al barcii:\n";
            for (unsigned c = 0; c < v.size(); c++) {
                std::cout << c + 1 << "." << conversie(v[c]) << "\n";
            }
            std::cin >> i;
            int size=v.size();
            while (0 >= i || i > size-1) {
                std::cout << "Introdu o varianta din cele afisate mai sus!\n";
                std::cin >> i;
            }
            i=i-1;
        }
        else{
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> random(0,v.size()-1);
            i=random(rd);
        }
        return v[i];
    }

    void alegere_barci_while(std::array<int,100> &x,int nr,bool player_type,std::vector<barca> &flota){
        int count=0;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> random(0,99);
        while(count!=3){
            std::string b;
            int a;
            if(player_type==true) {
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
            if (x[a]!=0 && player_type==true){
                std::cout<<"Deja ai aici o barca\n";
                continue;
            }
            else{
                x[a]=nr;
                int r=alegere(a,x,nr,player_type);
                x[r]=nr;
                if(nr==3){
                    x[a-((a-r)/2)]=nr;
                }
                count++;
                barca boat{a,r,nr};
                flota.push_back(boat);
            }
        }
    }


    tabla alegere_barci(bool test,std::vector<barca> &flota){
        std::array<int,100> x{0};
        alegere_barci_while(x,2,test,flota);
        alegere_barci_while(x,3,test,flota);
        tabla t{x};
        return t;
    }

    std::array<jucator,2> preparation(bool randomplay){
        std::cout<<"Bine ai venit la Batalia de pe Dunare\n";
        std::vector<barca> flota_player;
        std::vector<barca> flota_enemy;
        jucator player{true, alegere_barci(randomplay,flota_player),flota_player,2*3+3*3},enemy{false, alegere_barci(false,flota_enemy),flota_enemy,2*3+3*3};
        std::cout<<"Tabla ta:\n";
        player.afis_player();
        std::cout<<"\nTabla inamicului: \n";
        enemy.afis_player();
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

    void player_changes(jucator &player,bool tip) {
        int output;
        if (tip == true) {
            std::cout << "Alege unde ataci!\n";
        }
        output = attack(tip);
        tabla t_player = player.getTabla();
        std::array aux = t_player.getArray();
        int new_hp=player.getHp();
        while (t_player.getNr(output) < 0 && tip == true) {
            std::cout << "Ai mai lovit o data aici, alege alt loc!\n";
            output = attack(tip);
        }
        while (t_player.getNr(output) < 0 && tip == false) {
            output = attack(tip);
        }
        if (t_player.getNr(output) == 0) {
            aux[output] = -1;
        }
        else {
            aux[output] = -2;
            new_hp=player.getHp()-1;

        }
        std::cout<<"\n";
        tabla new_tabla{aux};
        player.change(new_hp,new_tabla);

    }

    void game_turn(jucator &player, jucator &enemy,bool randomplay){
        player_changes(player, randomplay);
        player_changes(enemy, false);
        std::cout << "Tabla ta:\n";
        player.afis_player();
        std::cout << "\nTabla inamicului: \n";
        enemy.afis_player();
    }



    void midgame(const std::array<jucator,2> endpreparation,bool randomplay){
        jucator player=endpreparation[0],enemy=endpreparation[1];
        while(player.getHp()!=0 && enemy.getHp()!=0){
            game_turn(player,enemy,randomplay);
        }
        if(player.getHp()==0){
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
        else if(answer=="Y" || answer=="y"){
            return true;
        }
        return false;

    }

    bool startgame(bool randomplay){
        midgame(preparation(randomplay),randomplay);
        bool replay=endgame();
        return replay;
    }
};

int main(){
    game joc;
    std::string answer;
    bool randomplay=false;
    bool play_again=true;
    std::cout<<"Vrei ca jocul sa fie generat random? Y/N \n";
    std::cin>>answer;
    if(answer=="N"||answer=="n"){
        randomplay=true;
    }
    else{
        randomplay=false;
    }
    while(play_again) {
        play_again=joc.startgame(randomplay);
    }
    return 0;
}

/*rlutil */
