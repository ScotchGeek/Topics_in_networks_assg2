#include<iostream>
#include <vector>
#include <limits.h>
#include<math.h>
using namespace std;

vector<vector<int>> cit(8);
vector<int> packetdelay(8);
int N=8,b=4;
double drop=0,tot=0,dt=0,dt1=0;
int portInUse[100],totalLinksUsed[100];
double packetgenprob=0.5,maxtimeslots=10000,time1=0,aver_delay=0;
vector<vector<int>> packet(8);
vector<vector<int>> oppacket(8);
double std_delay[100],sd=0,K=0.6*N;
int queue=1,t,g=2,k=0,j,i;

void calculate_average_delay()
{
    for(i=0;i<packetdelay.size();i++)
        aver_delay+=packetdelay[i];
    aver_delay=aver_delay/packetdelay.size();
    
    printf("%lf ",aver_delay);
}


void calculate_stddevation_delay()
{
    int n=packetdelay.size();
    for(i=0;i<n;i++)
        sd+=pow((packetdelay[i]-aver_delay),2);
    sd=sd/n;
    sd=sqrt(sd);
    printf("%lf ",sd);
}


void calculate_link_utilization()
{
    double link=0;
    for(i=0;i<oppacket.size();i++)
        link+=totalLinksUsed[i];
    link=link/(oppacket.size()*maxtimeslots);
    printf("%lf ",link);
}

void traffic_generation()
{
   
   
        for(j=0;j<N;j++){
            int port=(rand() % (N));
           if(((double) rand() / (RAND_MAX)) < packetgenprob)
           {
                tot++;
                   if((packet[port].size() == K))
                   {
                       drop++;
                    //   tot++;
                       continue;
                   }
                   else
                   {
                    //tot++;
                    packet[port].push_back(port);         //Stores the count of queue
                    cit[port].push_back((int)time1);          //Stores the arrival time
                    
                   }    
                   
            }
        }
        
    dt+=(drop/tot);
    dt1++;
}

void initialize_totalLinksUsed()
{
    for(i=0;i<N;i++)
        totalLinksUsed[i]=0;
}

void initialize_portInUse()
{
    for(i=0;i<N;i++)
        portInUse[i]=0;
}

void print_drop_frequency()
{
    printf("%f ",(dt/dt1));    
}

void two_schedule()
{
    initialize_portInUse();
    for(i=0;i<N;i++)
    {
        
        if(packet[i].size() != 0)
        {
            k=packet[i][0];
            if((portInUse[k]) == 0)   
            {    
                packetdelay.push_back(time1-cit[i][0]+1);
                portInUse[k]=1;
                totalLinksUsed[k]+=1;
                cit[i].erase(cit[i].begin());
                packet[i].erase(packet[i].begin());
            }
        }
        
    }
}

int main()
{
    printf("Enter number of ports:\n");
    scanf("%d",&N);
    printf("Enter number of buffers:\n");
    scanf("%d",&b);
    printf("Enter packet generation probability:\n");
    scanf("%lf",&packetgenprob);
    printf("Enter simulation time:\n");
    scanf("%lf",&maxtimeslots);
    printf("Type 1 for INQ,2 for KOUQ,3 for IsLIP:\n");
    scanf("%d",&queue);

    initialize_totalLinksUsed();
    packet.resize(N);
    oppacket.resize(N);
    cit.resize(N);
    
    i=1;
    K=0.6*N;
    packetdelay.resize(N);
 
    if(queue == 2)
    {
        while(time1 != maxtimeslots)
        {
        traffic_generation();
        two_schedule();
        time1++;
        }
        calculate_average_delay();
        calculate_stddevation_delay();
        calculate_link_utilization();
        print_drop_frequency();
    }
    
    
    return 0;
}
