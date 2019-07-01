#include <iostream>
#include <vector>
#include <fstream>
#include <numeric>
#include <algorithm>

using namespace std;

ofstream output;

bool compare(const vector<int>& a, const vector<int>& b)
{
    if(accumulate(a.begin(), a.end()-1, 0) > accumulate(b.begin(), b.end()-1, 0))
        return true;
    if(accumulate(a.begin(), a.end()-1, 0) < accumulate(b.begin(), b.end()-1, 0))
        return false;
    if(a.back()<b.back())
        return true;
    return false;
}

int findCMax(vector< vector < int > > Perm)
{
    vector<int> Mach(Perm[0].size()-1, 0);

    for(unsigned int i=0;i<Perm.size();i++)
    {
       vector<int> Ctmp=Perm[i];
        for(unsigned int j=0; j<Ctmp.size(); j++)
        {
            if(j!=0)
                Mach[j] = max(Mach[j], Mach[j-1]) + Ctmp[j];
            else
                Mach[j] = Mach[j] + Ctmp[j];
        }
    }
    return Mach.back();


}

int main()
{
    output.open("output.txt", std::ofstream::out | std::ofstream::trunc);
    char bufer[15];
    for(int data=0;data<=120;data++)
    {
        if(data<10)
            sprintf(bufer,"data.00%d:", data);
        if(data>=10 && data<100)
            sprintf(bufer,"data.0%d:", data);
        if(data>=100)
            sprintf(bufer,"data.%d:", data);

    int L,M;
    int tmp;
    vector< vector<int> > Data;
    vector< vector<int> > OptPerm;
    string linia;
    ifstream plik;
    plik.open("neh.data.txt");

    output<<bufer<<endl;
    cout<<bufer<<endl;
    while(linia!=bufer) plik>>linia;
    plik>>L;
    plik>>M;

      for(int i=0;i<L;i++)
    {
        Data.push_back(vector<int>());
        for(int j=0;j<M;j++)
        {
            plik>>tmp;
            Data[i].push_back(tmp);
        }
        Data[i].push_back(i+1);
    }

    sort(Data.begin(), Data.end(), compare);
    int CurrMax=999999;
    vector< vector<int> > CurrPerm;
    vector<int> CurrTmp;
    for(int i=0;i<L;i++)
    {
        CurrMax=999999;
        CurrTmp=Data[i];
        CurrPerm=OptPerm;
        for(int j=0;j<=i;j++)
        {

            CurrPerm.insert(CurrPerm.begin()+j, CurrTmp);

            int Maximum=findCMax(CurrPerm);
            if(Maximum<CurrMax)
            {
              OptPerm=CurrPerm;
              CurrMax=Maximum;
            }
            CurrPerm.erase(CurrPerm.begin()+j);
        }

    }
    output<<"Perm:"<<endl;
      for(unsigned int i=0;i<OptPerm.size();i++)
    {
            output<<OptPerm[i][OptPerm[i].size()-1]<<" ";
    }

    output<<endl;
    int cmax=findCMax(OptPerm);
    output<<"Dlugosc: "<<cmax<<endl;
    output<<endl;
    }
    return 0;
}
