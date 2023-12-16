#include <iostream>
#include <fstream>
#include <cstring>
#include <bitset>
using namespace std;
ifstream fin("in.txt");
ofstream fout("out.txt");
int nou[20][20],a[20][20],cheie[400], aux[400], cript[400], mesaj[400];
int main()
{
    //0x00
    int k,m,n,p;
    fin>>m>>n>>p;
    for(int i=0; i<=m+1; i++)
    {
        a[i][0]=0;
        a[i][m-1]=0;
    }
    for(int j=0; j<=n+1; j++)
    {
        a[0][j]=0;
        a[n-1][j]=0;
    }
    for(int x=1; x<=p; x++)
    {
        int i,j;
        fin>>i>>j;
        a[i+1][j+1]=1;
    }
    fin>>k;
    for(int x=1; x<=k; x++)
    {
        for(int i=1; i<=m; i++)
        {
            for(int j=1; j<=n; j++)
            {
                int v=0;
                if(a[i-1][j-1]==1)
                    v++;
                if(a[i-1][j]==1)
                    v++;
                if(a[i-1][j+1]==1)
                    v++;
                if(a[i][j-1]==1)
                    v++;
                if(a[i][j+1]==1)
                    v++;
                if(a[i+1][j-1]==1)
                    v++;
                if(a[i+1][j]==1)
                    v++;
                if(a[i+1][j+1]==1)
                    v++;
                if((a[i][j]==1)&&(v<2))
                    nou[i][j]=0;
                else if((a[i][j]==1)&&((v==2)||(v==3)))
                    nou[i][j]=1;
                else if((a[i][j]==1)&&(v>3))
                    nou[i][j]=0;
                else if((a[i][j]==0)&&(v==3))
                    nou[i][j]=1;
                else
                    nou[i][j]=0;
            }
        }
        for(int i=1; i<=m; i++)
            for(int j=1; j<=n; j++)
                a[i][j]=nou[i][j];
    }
    for(int i=1; i<=m; i++)
    {
        for(int j=1; j<=n; j++)
            fout<<nou[i][j]<<" ";
        fout<<endl;
    }
    //0x01
    int poz=0;
    for (int i = 0; i <= m + 1; i++)
    {
        for (int j = 0; j <= n + 1; j++)
        {
            cheie[poz] = a[i][j];
            poz++;
        }
    }
    long long key=0;
    for(int i=0; i<poz; i++)
        key=key*2+cheie[i]; //cheia e in baza 10
    bool c;
    fin>>c;
    char mes[100];
    fin>>mes;
    long long msj=0;
    for(int x=0; x<strlen(mes); x++)
    {
        int cod=mes[x]-0;
        msj=(msj<<8)+cod;
    }
    int nr=0;
    while(msj!=0 || nr%8!=0)
    {
        aux[nr]=msj%2;
        msj=msj/2;
        nr++;
    }
    for(int i=0; i<nr; i++)     //nr e maxim la mesaj
        mesaj[nr-i-1]=aux[i];
    for(int i=0; i<nr; i++)
        fout<<mesaj[i];
    fout<<endl;
    for(int i=0; i<poz; i++)    //poz e maxim la cheie
        fout<<cheie[i];
    fout<<endl;
    if(c==0) //criptare
    {
        int i=0;
        int cnr=nr;
        int cpoz=poz;
        while(poz<nr)
        {
            cheie[poz]=cheie[i];
            i++;
            poz++;
            if(i==cnr)
                i=0;
        }
        unsigned long long numcript=0;
        for(int i=0; i<poz; i++)
        {
            cript[i]=mesaj[i]^cheie[i];
            numcript=(numcript<<1)+cript[i];
        }
        fout<<numcript<<endl;
        char criptare[100];
        sprintf(criptare, "%X", numcript);
        fout<<criptare;
    }
    else //decriptare
    {

    }

    return 0;
}
