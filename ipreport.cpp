#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

#define IP_RANGE "10.2.7.128/25"
#define IP_KNOWN "known.conf"
#define IP_LIST "list.txt"
#define STR_SIZE 200
#define WT 60*15
struct node
{
   char ip[STR_SIZE];
   char name[STR_SIZE]; 
}known_list[1000],active_list[1000];

int known_cnt,active_cnt;

char * findNode(char * ip)
{
	int i;
	for(i=0;i<known_cnt;i++)
	{
	     if(0==strcmp(ip,known_list[i].ip))
	     {
	         return known_list[i].name;
	     }
	}
	return "unknow";
}

int main()
{
	while(1){
	FILE * fp = fopen(IP_KNOWN,"r");
	if(!fp)
	{
	    fprintf(stderr,"No IP_KNOWN file\n");	
	}
	else
	{
		known_cnt = 0;
	    while(EOF != fscanf(fp,"%s%s",known_list[known_cnt].ip,known_list[known_cnt].name))
	    {
	        known_cnt ++;
	    }
	    fclose(fp);
	}
	

	char cmd[STR_SIZE];
	sprintf(cmd,"nmap -sP %s > %s",IP_RANGE,IP_LIST);
	system(cmd);
	fp = fopen(IP_LIST,"r");
	active_cnt = 0;
	while(EOF != fscanf(fp,"%s",cmd))
	{
	     if(strncmp(cmd,IP_RANGE,7)==0)
	     {
	         strcpy(active_list[active_cnt].ip,cmd);
	         strcpy(active_list[active_cnt].name,findNode(active_list[active_cnt].ip));
		 active_cnt ++;
	     }
	}
	if(fp) fclose(fp);

	fp = fopen("index.html","w");
	int i;
	fprintf(fp,"<title>knocking on the heaven's door.</title>\n<br>Gait Active");
	for(i=0;i<active_cnt;i++)
	{
	     fprintf(fp,"\n<li>%s %s</li>",active_list[i].ip,active_list[i].name);
	}
	fclose(fp);
	system("git checkout -b gh-pages");
	system("git add .");
	system("git commit -m \"e..\"");
	system("git push -f origin gh-pages");
	fprintf(stderr,"wait..\n");
	sleep(WT);
	}
	return 0;
}
