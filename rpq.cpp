#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

void sorting(int tabr[],int tabp[],int tabq[],int tabid[], int left, int right, int dir)
{
    int v=tabr[(left+right)/2];
    int i,j,x;
    i=left;
    j=right;
    do
    {
        if(dir==0)
        {
            while (tabr[i]<v) i++;
            while (tabr[j]>v) j--;
        }
        else
        {
            while (tabr[i]>v) i++;
            while (tabr[j]<v) j--;
        }
        if (i<=j)
        {
            x=tabr[i];
            tabr[i]=tabr[j];
            tabr[j]=x;

             x=tabp[i];
            tabp[i]=tabp[j];
            tabp[j]=x;

             x=tabq[i];
            tabq[i]=tabq[j];
            tabq[j]=x;

             x=tabid[i];
            tabid[i]=tabid[j];
            tabid[j]=x;

            i++; j--;
        }
    }
    while (i<=j);
    if (j>left) sorting(tabr,tabp,tabq,tabid,left, j,dir);
    if (i<right) sorting(tabr,tabp,tabq,tabid, i, right,dir);
}


int main()
{
    int n, longestr=0, rpq=0, id=0, sum=0;
    int R[100],P[100],Q[100],ID[100];
    string s,dataid[4]={"data.1","data.2","data.3","data.4"};

    ifstream plik;
    plik.open("rpq.data.txt");

    for(int j=0;j<4;j++)
    {
        while(s!=dataid[j]) plik>>s;
        plik>>n;

        for(int i=0;i<n;i++) plik>>R[i]>>P[i]>>Q[i], ID[i]=i+1;

        for(int i=0;i<n;i++)
            if (R[i]+P[i]+Q[i]>rpq)
            {
                rpq=R[i]+P[i]+Q[i];
                longestr=R[i];
            }

        sorting(R,P,Q,ID, 0,n-1,0);

        int elapsed = R[0]+ P[0];
        for(int i=1;elapsed<longestr;i++)
        {
            id=i;
            if(elapsed>=R[i])
                elapsed+=P[i];
            else
                elapsed+=(R[i]-elapsed+P[i]);
        }

        sorting(Q,R,P,ID,id,n-1,1);

        cout<<"Kolejnosc: ";
        for(int i=0;i<n;i++) cout<<ID[i]<<" ";

        int t=0,cmax=0;
        for(int i=0;i<n;i++)
        {
            t=max(R[i],t)+P[i];
            cmax=max(cmax,t+Q[i]);
        }
        cout<<endl;
        cout<<"Suma dla "<<dataid[j]<<": "<<cmax<<endl;
        sum+=cmax;
        cout<<endl;
    }

    cout<<"Suma wszystkich: "<<sum<<endl;

    system("pause");
    return 0;
}



