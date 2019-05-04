#include <iostream>
#include <fstream>
#include <queue>
#include <vector>

using namespace std;

// INICJALIZACJA ZMIENNYCH
struct Proces
{
    int ID;
    int R;
    int P;
    int Q;
};
struct PorownajPoR
{
bool operator()(const Proces& a, const Proces& b)
{
    if( a.R > b.R ) return true;

    if( a.R < b.R) return false;

    if(a.ID > b.ID) return true;

    return false;
}
};
struct PorownajPoQ
{
bool operator()(const Proces& a, const Proces& b)
{
    if( a.Q < b.Q ) return true;

    if( a.Q > b.Q) return false;

    if(a.ID > b.ID) return true;

    return false;
}
};

vector <Proces> zadania;
priority_queue< Proces,vector<Proces>, PorownajPoR> Nieuszeregowane;
priority_queue< Proces,vector<Proces>, PorownajPoQ> Gotowe;
int l_procesow=0;
int t=0,k=0,cmax=0;
Proces obecny;
vector<int> permutacja;
// KONIEC INICJALIZACJI ZMIENNYCH

void wczytaj()
{
    string linia, data_nr = "data.008:";
    ifstream plik;
    plik.open("schr.data.txt");

    while(linia!=data_nr) plik>>linia;
    plik>>l_procesow;

    for(int i=0;i<l_procesow;i++)
    {
        Proces zadanie;
        plik>>zadanie.R>>zadanie.P>>zadanie.Q, zadanie.ID=i+1;
        Nieuszeregowane.push(zadanie);
    }
}

void przeglad(){
    while(!Nieuszeregowane.empty() && (Nieuszeregowane.top().R<=t))
        {
            obecny=Nieuszeregowane.top();
            Nieuszeregowane.pop();
            Gotowe.push(obecny);
        }
        if(Gotowe.empty())
        {
            t=Nieuszeregowane.top().R;
            przeglad();
        }
}

void schrage(){
    while(!Gotowe.empty() || !Nieuszeregowane.empty())
    {
       przeglad();
       obecny=Gotowe.top();
       Gotowe.pop();
      // k=k+1;
       permutacja.push_back(obecny.ID);
       t+=obecny.P;
       cmax=max(cmax,t+obecny.Q);
    }
}

int main()
{
    wczytaj();
    schrage();
    for(int unsigned i=0;i<permutacja.size();i++)
        cout<<permutacja[i]<< " ";
    cout<<endl;
    cout<<"cmax="<<cmax<<endl;
    return 0;

}
