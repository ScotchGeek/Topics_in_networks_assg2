#include<iostream>
#include <vector>
#include <limits.h>
#include<math.h>
using namespace std;

vector<vector<int>> cit(8);
vector<int> packetdelay(8);
int N=8,b=4;
int portInUse[100],totalLinksUsed[100];
long double drop=0,tot=0,dt=0,dt1=0,maxtimeslots=10000;
double packetgenprob=0.5,time1=0,aver_delay=0,K=0.6*N;
vector<vector<int>> packet(8);
double std_delay[100],sd=0,dropout_factor=0.6;
int queue=1,t,g=2,k=0,j,i;
int smallest_index,value_of_smallestl_index;
vector<vector<int>> oppacket(8);
vector<int> drops;


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

void traffic_generation_one()
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

void traffic_generation_two()
{
    drop=0;
    for(j=0;j<N;j++)
        drops[i]=-1;
    for(j=0;j<N;j++){
        int port=(rand() % (N));
       if(((double) rand() / (RAND_MAX)) < packetgenprob)
       {
            if((packet[port].size() == K))
            {
                drops[port]=0;
                drop++;
                continue;
            }
            else
            {
                drops[port]++;            
                packet[port].push_back(port);         //Stores the count of queue
                cit[port].push_back((int)time1);          //Stores the arrival time
            }    
                   
            }
        }
    
    for(j=0;j<N;j++)
        if(drops[i] == 0)
            drop++;
    tot=(long double)(drop/N);
    dt+=tot;
}


void traffic_generation_three()
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
            k=packet[i][0];
            if((portInUse[k]) == 0)   
            {    packetdelay.push_back(time1-cit[i][0]+1);
               
            portInUse[k]=1;
            totalLinksUsed[k]+=1;
            cit[i].erase(cit[i].begin());
            packet[i].erase(packet[i].begin());
            }
        }
        
    }
}


void print_drop_frequency()
{
    printf("%Lf ",(long double)(dt/(maxtimeslots)));    
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


void three_schedule()
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
    scanf("%Lf",&maxtimeslots);
    printf("Type 1 for INQ,2 for KOUQ,3 for IsLIP:\n");
    scanf("%d",&queue);
    if(queue == 2)
    {
        printf("Enter dropout factor:\n");
        scanf("%lf",&dropout_factor);
    }    
        

    initialize_totalLinksUsed();
    packet.resize(N);
    cit.resize(N);
    i=1;
    packetdelay.resize(N);
    drops.resize(N);
    oppacket.resize(N);
    
    if(queue == 1)
    {
        printf("%d %lf ",N,packetgenprob);
        printf("INQ ");
        while(time1 != maxtimeslots)
        {
        traffic_generation_one();
        one_schedule();
        time1++;
        }
        calculate_average_delay();
        calculate_stddevation_delay();
        calculate_link_utilization();
    }
    
    if(queue == 2)
    {
        printf("%d %lf ",N,packetgenprob);
        printf("KOUQ ");
        K=(double)(dropout_factor*N);
        while(time1 != maxtimeslots)
        {
        traffic_generation_two();
        two_schedule();
        time1++;
        }
        calculate_average_delay();
        calculate_stddevation_delay();
        calculate_link_utilization();
        print_drop_frequency();
    }
    
    if(queue == 3)
    {
        printf("%d %lf ",N,packetgenprob);
        printf("IsLIP ");
        while(time1 != maxtimeslots)
        {
        traffic_generation_three();
        three_schedule();
        time1++;
        }
        calculate_average_delay();
        calculate_stddevation_delay();
        calculate_link_utilization();
    }
    
    
    return 0;
}
