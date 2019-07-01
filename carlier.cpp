#include <iostream>
#include <fstream>
#include <queue>
#include <vector>

using namespace std;

struct Proces
{
    int ID;
    int R;
    int P;
    int Q;
    int tend;
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

void wczytaj(vector<Proces> &PI)
{
    string linia, data_nr = "data.001:";
    int l_procesow;
    ifstream plik;
    plik.open("carl.data.txt");

    while(linia!=data_nr) plik>>linia;
    plik>>l_procesow;

    for(int i=0;i<l_procesow;i++)
    {
        Proces zadanie;
        plik>>zadanie.R>>zadanie.P>>zadanie.Q, zadanie.ID=i;
        PI.push_back(zadanie);
    }

}

void przeglad(priority_queue< Proces,vector<Proces>, PorownajPoR> &Nieuszeregowane, priority_queue< Proces,vector<Proces>, PorownajPoQ> &Gotowe, int &t){
    while(!Nieuszeregowane.empty() && (Nieuszeregowane.top().R<=t))
        {
            Proces obecny;
            obecny=Nieuszeregowane.top();
            Nieuszeregowane.pop();
            Gotowe.push(obecny);
        }
        if(Gotowe.empty())
        {
            t=Nieuszeregowane.top().R;
            przeglad(Nieuszeregowane, Gotowe, t);
        }
}

int schrage(vector<Proces> &PI){
    priority_queue< Proces,vector<Proces>, PorownajPoR> Nieuszeregowane;
    priority_queue< Proces,vector<Proces>, PorownajPoQ> Gotowe;
    int t=0;
    int cmax=0;
    while(!PI.empty()){
        Proces P;
        P = PI.back();
        PI.pop_back();
        Nieuszeregowane.push(P);
    }
    while(!Gotowe.empty() || !Nieuszeregowane.empty())
    {
        Proces obecny;
       przeglad(Nieuszeregowane, Gotowe,t);
       obecny=Gotowe.top();
       Gotowe.pop();
       obecny.tend=t+obecny.P;
       PI.push_back(obecny);
       t+=obecny.P;
       cmax=max(cmax,t+obecny.Q);
    }
    return cmax;
}

void przeglad_prmt(priority_queue< Proces,vector<Proces>, PorownajPoR> &Nieuszeregowane, priority_queue< Proces,vector<Proces>, PorownajPoQ> &Gotowe, int &t, Proces &l){
    while(!Nieuszeregowane.empty() && (Nieuszeregowane.top().R<=t))
        {
            Proces e;
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
            przeglad_prmt(Nieuszeregowane,Gotowe,t,l);
        }
}

int schrage_prmt(vector<Proces> PI){
    priority_queue< Proces,vector<Proces>, PorownajPoR> Nieuszeregowane;
    priority_queue< Proces,vector<Proces>, PorownajPoQ> Gotowe;
    int t=0;
    int cmax=0;
    Proces l;
    l.Q=999999;
    while(!PI.empty()){
        Proces P;
        P = PI.back();
        PI.pop_back();
        Nieuszeregowane.push(P);
    }
    while(!Gotowe.empty() || !Nieuszeregowane.empty())
    {
       przeglad_prmt(Nieuszeregowane, Gotowe,t, l);
       Proces e;
       e=Gotowe.top();
       Gotowe.pop();
       l=e;
       t+=e.P;
       cmax=max(cmax,t+e.Q);
    }
    return cmax;
}

int carlier(vector<Proces> &OPT_PI,vector<Proces> PI, int UB)
{
    /// OBLICZAMY UB ALGORYTMEM SCHRAGE
    int U = schrage(PI);
    if(U<UB)
    {
        UB=U;
        OPT_PI=PI;
    }
    /// ZNAJDZ B
    int a,b,c=-1;
    for(int unsigned i=0;i<=PI.size();i++)
        if(U==PI[i].tend+PI[i].Q)
            b=i;
    /// ZNAJDZ A
    int suma;
    for(a=0;a<b-1;a++)
    {
            suma=0;
            for(int i=a;i<=b;i++)
                suma+=PI[i].P;
            if(U==(PI[a].R+suma+PI[b].Q))
                break;
    }


    /// ZNAJDZ C
    for(int i=b;i>=a;i--)
        if(PI[i].Q < PI[b].Q)
		{
			c=i;
			break;
		}
    if(c==-1){
        return U;
    }

    /// OBLICZAMY rK qK pK
    int rK=INT_MAX,qK=INT_MAX,pK=0,rKC=INT_MAX,qKC=INT_MAX,pKC=0,hK=0,hKC=0;
   for(int i=c+1;i<=b;i++)
   {
       rK=min(rK,PI[i].R);
       qK=min(qK,PI[i].Q);
       pK+=PI[i].P;
   }
   hK=(rK+qK+pK);
   /// SCHRAGE* Z PODSTAWIONYM NOWYM PI[c].R
   int oldR=PI[c].R;
   int oldID=PI[c].ID;
   PI[c].R=max(PI[c].R,rK+pK);
   int LB=schrage_prmt(PI);
   for(int i=c;i<=b;i++)
   {
       rKC=min(rKC,PI[i].R);
       qKC=min(qKC,PI[i].Q);
       pKC+=PI[i].P;
   }
   hKC=(rKC+qKC+pKC);
   LB=max(LB,max(hK,hKC));
   /// POTOMEK A
   if(LB<UB)
     UB= carlier(OPT_PI,PI,UB);
   /// ODTWARZAMY PI[c].R
   for(int unsigned i=0;i<PI.size();i++)
        if(oldID==PI[i].ID)
            PI[i].R=oldR;
   /// SCHRAGE* Z PODSTAWIONYM NOWYM PI[c].R
   int oldQ=PI[c].Q;
   oldID=PI[c].ID;
   PI[c].Q=max(PI[c].Q,qK+pK);
   LB=schrage_prmt(PI);
   rKC=INT_MAX,qKC=INT_MAX,pKC=0,hKC=0;
   for(int i=c;i<=b;i++)
   {
       rKC=min(rKC,PI[i].R);
       qKC=min(qKC,PI[i].Q);
       pKC+=PI[i].P;
   }
   hKC=(rKC+qKC+pKC);
   LB=max(LB,max(hK,hKC));
   /// POTOMEK B
   if(LB<UB)
       UB=carlier(OPT_PI,PI,UB);
   for(int unsigned i=0;i<PI.size();i++)
        if(oldID==PI[i].ID)
            PI[i].Q=oldQ;

   return UB;
}

int main()
{
    priority_queue< Proces,vector<Proces>, PorownajPoR> Nieuszeregowane;
    priority_queue< Proces,vector<Proces>, PorownajPoQ> Gotowe;
    vector<Proces> OPT_PI;
    vector<Proces> PI;
    int UB=99999999;
    wczytaj(PI);
    schrage(PI);
    carlier(OPT_PI,PI,UB);
    /////////////////////////////////////
    cout<<endl;
    for(int unsigned i=0;i<OPT_PI.size();i++)
        cout<<OPT_PI[i].ID<< " ";
    cout<<endl;

     int t=0,cmax=0;
        for(int unsigned i=0;i<OPT_PI.size();i++)
        {
            t=max(OPT_PI[i].R,t)+OPT_PI[i].P;
            cmax=max(cmax,t+OPT_PI[i].Q);
        }
    cout<<"cmax="<<cmax<<endl;
    ////////////////////////////////////
    return 0;
}
