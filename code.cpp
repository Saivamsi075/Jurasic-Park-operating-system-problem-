#include<iostream>
#include<vector>
#include<ctime>
#include<stdlib.h>

using namespace std;

class cars
{
    public:

    bool loaded;
    int startTime;
    int endTime;

    cars()
    {
        loaded=false;
        startTime=-1;
        endTime=-1;
    }
};

int Random()
{
    srand(time(0)*rand());
    return rand()%10 +1;
}

int main()
{
    int t;  //test cases
    int n;  //number of safari cars
    int m;  //number of passengers wandering in the museum
    int q;  //number of passengers in park gate
    int k;  //jurassic park remains open for

    int pc; //passengers who have completed park rid
    int cw; //cars waiting
    int cl; //cars loaded

    cin>>t;

    while(t--)
    {
        cin>>n>>m>>q>>k;

        vector<cars> car;
        car.resize(n);

        int ck=1;

        cw=n;
        cl=0;
        pc=0;

        //process cars while time remains
        while(ck<=k)
        {
                if(m>0 && ck%Random()==0)
                {
                    q++;
                    m--;
                }

            for(int ci=0;ci<n;ci++)
            {

               if(car[ci].loaded && car[ci].endTime==ck)
                {
                    car[ci]= cars();

                    pc++;
                    cw++;
                    cl--;
                }

                if(q>0 && !car[ci].loaded)
                {
                    car[ci].loaded=true;
                    car[ci].startTime=ck;
                    car[ci].endTime=ck+Random();

                    q--;
                    cl++;
                    cw--;
                }


            }

            ck++;
        }

        cout<<cw<<" "<<pc<<" "<<m<<" "<<q<<endl;
    }
}
