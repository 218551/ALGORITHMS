#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>

using namespace std;


int main()
{
    int n;
    int P[100],W[100],T[100],ID[100];
    string s;

    ifstream plik;
    plik.open("witi.data.txt");

    fstream plik1;
    plik1.open("Wyniki.txt",std::ios::in | std::ios::out);


    string data_nr[11]={"data.10:","data.11:","data.12:","data.13:","data.14:","data.15:","data.16:","data.17:","data.18:","data.19:","data.20:"};
    string data;
    for(int i=0;i<11;i++){

    while(s!=data_nr[i]) plik>>s;
    plik>>n;
    plik1<< n<<endl;
    for(int i=0;i<n;i++) plik>>P[i]>>W[i]>>T[i], ID[i]=i+1;
    for(int i=0;i<n;i++) plik1<<ID[i]<<". "<<P[i]<<" "<<W[i]<<" "<<T[i]<<" "<<endl;

    int C,N=1<<n, *F=new int[N]; F[0]=0;
    for(int set=1;set<N;set++)
    {
        C=0;
        for(int i=0,b=1;i<n;i++,b*=2)
        {
            if(b&set)
            {
                C=C+P[i];
                F[set]=999999999;
                for(int i=0,b=1;i<n;i++,b=b*2)
                {
                    if(b&set)
                    {
                        F[set]=min(F[set],F[set-b]+W[i]*max(0,C-T[i]));
                    }

                }
            }
        }

    }
plik1<<F[N-1]<<endl;
delete[]F;
plik1<<endl;
}

    return 0;
}
