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
int t=0,cmax=0;
Proces e,l;
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
            e=Nieuszeregowane.top();
            Nieuszeregowane.pop();
            Gotowe.push(e);
            if(e.Q>l.Q)
            {
                l.P=t-e.R;
                t=e.R;
                if(l.P>0)
                Gotowe.push(l);
            }
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
       e=Gotowe.top();
       Gotowe.pop();
       l=e;
       t+=e.P;
       cmax=max(cmax,t+e.Q);
    }
}

int main()
{

    wczytaj();
    l.Q=9999999;
    schrage();
    cout<<endl;
    cout<<"cmax="<<cmax<<endl;
    return 0;

}
