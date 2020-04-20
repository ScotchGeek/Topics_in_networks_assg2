#include<iostream>
#include <vector>
#include <limits.h>
#include<math.h>
using namespace std;

vector<vector<int>> cit(8);
vector<int> packetdelay(8);
int N=8,b=4;
//int maxtimeslots=10000;
int portInUse[100],totalLinksUsed[100];
double packetgenprob=0.5,maxtimeslots=10000,time1=0,aver_delay=0;
    vector<vector<int>> packet(8);
double std_delay[100],sd=0;
int queue=1,t,g=2,k=0,j,i;
int smallest_index,value_of_smallestl_index;

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
    sd=sqrt(aver_delay);
    printf("%lf ",sd);
}


void calculate_link_utilization()
{
    double link=0;
    for(i=0;i<packet.size();i++)
            link+=totalLinksUsed[i];
    link=link/(packet.size()*maxtimeslots);
    printf("%lf ",link);
}

void traffic_generation()
{
   
        for(j=0;j<N;j++){
           if(((double) rand() / (RAND_MAX)) < packetgenprob)
           {
               if((packet[j].size() == b))
                continue;
                else
               {
                    //packet[j].push_back(j);         //Stores the count of queue
                    cit[j].push_back((int)time1);          //Stores the arrival time
                    packet[j].push_back((rand() % (N)));          //Stores the destination port
                    
               }
            }
        }
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

void one_schedule()
{
    initialize_portInUse();
    for(i=0;i<N;i++)
    {
        
        if(packet[i].size() != 0)
        {
            smallest_index=-1,value_of_smallestl_index=INT_MAX;
            k=packet[i][0];
            for(j=0;j<packet[i].size();j++)
            {
            if((portInUse[k]) == 0)   
                {    
                    smallest_index=j;
                    value_of_smallestl_index=packet[i][j];
                }
            }
            if(smallest_index == -1)
                continue;
            packetdelay.push_back(time1-cit[i][smallest_index]+1);
            portInUse[value_of_smallestl_index]=1;
            totalLinksUsed[value_of_smallestl_index]+=1;
            cit[i].erase(cit[i].begin()+smallest_index);
            packet[i].erase(packet[i].begin()+smallest_index);
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
    cit.resize(N);
    
    i=1;
    
    packetdelay.resize(N);
    if(queue == 1)
    {
        while(time1 != maxtimeslots)
        {
        traffic_generation();
        one_schedule();
        
        //transmission();
        time1++;
        }
    }
    calculate_average_delay();
    calculate_stddevation_delay();
    calculate_link_utilization();
    
    return 0;
}
