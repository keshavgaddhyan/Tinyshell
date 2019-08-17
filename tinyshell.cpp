#include <iostream>    //Keshav Gaddhyan-3035437367
#include <stdlib.h>   
#include <algorithm>
#include <string.h>
#include <vector>
#include <map>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/wait.h>
#include <time.h>

using namespace std;


class details
{
    public:
    string com;
    float ti;
};

string delspaces(string  str)
{
str.erase(remove(str.begin(), str.end(), ' '), str.end());
return str;
}

bool operator <  (const details & a, const details & b)
{
    return a.ti<b.ti;
}
int main()
{
vector<details> histflag;
vector<details> hist;
int i;
float t=0;
pid_t pid; 
string command="";
cout<<"tinyshell>";
getline(cin,command);
string space="";
space=delspaces(command);
if(space=="history" || space=="history-sbu" || space=="exit")
command=space;
while ( command != "exit")
{
pid=fork();
if(pid<0)
{
cout<<"fork() error"<<endl;
exit(-1);
}
if(pid==0)
{
if(command == "history-sbu")
{
int count=0;
hist=histflag;
sort(hist.end()-5,hist.end());
for(int i=hist.size()-1;i>hist.size()-6;i--)
{
cout<<hist[i].com<<"  "<<hist[i].ti<<"s"<<endl;
}
}
else if(command == "history")
{
vector<details>::iterator itr;
for(itr=histflag.end()-1;itr>(histflag.end()-6) ;itr--)
{
cout<<(*itr).com<<"  "<<(*itr).ti<<"s"<<endl;
}
}
else
{
    
const char *execute = command.c_str();
system(execute);
}
exit(0);
}
if(pid>0)
{
clock_t tStart=clock();
wait(NULL);
t=(float)(clock()-tStart)/CLOCKS_PER_SEC;
cout<<"tinyshell>";

details r;
r.com=command;
r.ti=t;
histflag.push_back(r);
getline(cin,command);
string space="";
space=delspaces(command);
if(space=="history" || space=="history-sbu" || space=="exit")
{
command=space;
}

}
}
return 0;
}
