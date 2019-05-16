/*
Tushar Tyagi, b17106
CS201P - Assignment 7.
A C++ CPU Simulator code
*/

#include <bits/stdc++.h>
using namespace std;

long hexToDec(string s);
int missNo(int n, bool rp, int cachesz, int bsize);

int main()
{

    /*
    Block Size          :   16 B
    Cache Size          :   1024,2048,4096,8192 B
    Mapping Function    :   Direct Mapped, 4-way set associative
    Replacement Policy  :   LRU(Least Recently Used) & FIFO(First in First Out)
    */

    ifstream address;
    string hex;
    int total=0;
    vector<int> miss;

    address.open("address.txt");
    if(!address)
    {
        cout<<"Unable to import addresses"<<endl;
        return 1;
    }

    while (getline(address, hex))
        total++;
    address.close();
    cout<<"TOTAL: "<<total<<endl;
    // Direct :
    cout<<"Direct Mapping: "<<endl<<endl;
    int bsm[2]={16,32};
    int csm[4]={1024,2048,4096,8192};
    for(int j=0;j<2;j++){ //Block size: 16,32

        if(j==0) cout<<"Block Size = 16 "<<endl;
        else cout<<"Block Size = 32 "<<endl;

        for(int i=0;i<4;i++){ //cache size: 1024,2048,4096,8192
            if(i==0) {
                cout<<"Cache Size = 1024, ";

            }
            else if(i==1) cout<<"Cache Size = 2048, ";
            else if(i==2) cout<<"Cache Size = 4096, ";
            else          cout<<"Cache Size = 8192, ";

            cout<<"Miss ratio= "<<missNo(1,0,csm[i],bsm[j])<<"/"<<total<<endl;
        }
        cout<<endl;
    }

    cout<<"4-Way set addressing: "<<endl<<endl;
    cout<<"Least Recently Used:"<<endl;
    for(int j=0;j<2;j++){ //Block size: 16,32

        if(j==0) cout<<"Block Size = 16 "<<endl;
        else cout<<"Block Size = 32 "<<endl;

        for(int i=0;i<4;i++){ //cache size: 1024,2048,4096,8192
            if(i==0) {
                cout<<"Cache Size = 1024, ";

            }
            else if(i==1) cout<<"Cache Size = 2048, ";
            else if(i==2) cout<<"Cache Size = 4096, ";
            else          cout<<"Cache Size = 8192, ";

            cout<<"Miss ratio= "<<missNo(4,0,csm[i],bsm[j])<<"/"<<total<<endl;
        }
        cout<<endl;
    }

    cout<<"First in First Out:"<<endl;

    return 0;

    }

int missNo(int n, bool rp, int cachesz, int bsize)
{
    long miss=0;
    long num;
    string hex;
    /* Returns number of misses in n-way set associative mapping.
        rp: 0 --> LRU, rp: 1 --> FIFO
        with cache size of "cachesz" bytes and
        block size of "bsize" bytes.
    */
    ifstream address;
    address.open("address.txt");
    if(!address)
    {
        cout<<"Unable to import addresses"<<endl;
        return 1;
    }

    if(rp==0)
    {
        long cache[cachesz/(n*bsize)][n];
        int table[cachesz/(n*bsize)][n+1]={0};

        for(int i=0;i<cachesz/(n*bsize);i++)
            for(int j=0;j<n;j++) cache[i][j]=9999999999;

            for(int i=0;i<cachesz/(n*bsize);i++)
                for(int j=0;j<n+1;j++) table[i][j]=0;


        while (getline(address, hex))
        { /////////////////////////////////////////////////num to byte ha, block dhumdna ha be.
            num=hexToDec(hex);
            long block=num/bsize;
            int set=block%(cachesz/(n*bsize));
            int flag=0;
            for(int i=0;i<n;i++){
                if(cache[set][i]==block){
                    //cout<<"hi<"<<endl;
                    flag=1;
                    table[set][i]=0;
                    for(int j=0;j<n;j++)
                    {
                        if(j!=i) table[set][j]++;
                    }
                    int temp=0;
                    for(int i=0;i<n;i++)
                    {
                        if(table[set][i]>temp) temp=i;
                    }
                    table[set][n]=temp;
                    break;
                }
            }

            if(flag==0)
            {
                miss++;
                int x=table[set][n];
                cache[set][x]=block;
                table[set][x]=0;
                for(int i=0;i<n;i++)
                {
                    if(i!=table[set][n]) table[set][i]++;
                }
                int temp=0;
                for(int i=0;i<n;i++)
                {
                    if(table[set][i]>temp) temp=i;
                }
                table[set][n]=temp;
            }

        }
        return miss;
    }
    else
    {

    }
}

long hexToDec(string num) //Function to convert given Hexadecimal number to decimal.
{
    int len;
    len = num.length();
    long r,hex2=0;
    for (int i = 0; num[i] != '\0'; i++)
    {
        len--;
        if(num[i] >= '0' && num[i] <= '9')
            r = num[i] - 48;
        else if(num[i] >= 'a' && num[i] <= 'f')
                r = num[i] - 87;
             else if(num[i] >= 'A' && num[i] <= 'F')
                    r = num[i] - 55;
        hex2 += r * pow(16,len);
    }
    return hex2;
}
