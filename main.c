#include <stdio.h>
#include <stdlib.h> 
#include <string.h>



char* StrHandler(char *ini, int* maxlen, char end)
{
	int real_len = 0;
	int DEBUG = 0;	

	if(!ini ||!maxlen) return NULL;
	if(*maxlen < 1) return NULL;
	
	real_len = *maxlen;
	if(DEBUG) printf("maxlen:|%d| \n", real_len);

	while(real_len > -1 && ini[real_len] != end) real_len--;
	if(DEBUG) printf("Debug:|%c|", ini[real_len+1]);
	while(real_len > -1 && ini[real_len] == end) real_len--;

	real_len++;
	
	if(DEBUG) printf("real len:|%d| \n", real_len);	
	
	char *str;
	str = (char *)calloc (real_len + 1, sizeof(char));

	if(!str) return NULL;
	strncpy(str, ini, real_len);
	
	*maxlen = real_len;

	return str;
}


char* getIP()
{
	int DEBUG = 0;
	int IPv4len = 15;

	FILE *fp;
  	char line[130]="";


	fp = popen("ifconfig", "r");	

  	for(int i = 0; i < 2; i++) fgets( line, sizeof line, fp);

	
	if (DEBUG) printf("line: %s", line);
	
	int inetStart = 13;

	char *inet = StrHandler(line + inetStart, &IPv4len, ' ');
	printf("\nYour IP address:|%s| \n\n", inet); //0x48B3D3

	char *aux = StrHandler(inet, &IPv4len, '.');
	if (DEBUG) printf("aux: %s \n", aux);

	char ports[] = ".0/24";

	char* range = (char *)calloc(IPv4len + strlen(ports) + 1, sizeof(char) );

	sprintf(range, "%s%s", aux, ports);
	if (DEBUG) printf("Range: %s \n",range);
	

	free(inet);
	free(aux);
	
	pclose(fp);

	return range;
}


int main()
{
	int DEBUG = 0;
	

	char option;


	do
	{
		printf("Nmap requeired! Do you want to install it or upgrade it? \n");
		printf("Type 'i' to istall or upgrade it \n");
		printf("Type 'c' to continue \n");
		printf("Type 't' to leave \n\n");	
		
		if(DEBUG == 1) option = 'c';
		else scanf("%c", &option);

		switch(option)
		{
			case 'i':
				system("sudo apt install nmap");
				option = 'c';
				break;
			case 'l': return 0;
		}	
		
	} while(option != 'c');

	char *range = getIP();


	printf("Range: %s \n", range);

	char* cmd = (char *)calloc(strlen("sudo nmap -sn") + 1 + strlen(range) + 1, sizeof(char) );
	sprintf(cmd, "%s %s", "sudo nmap -sn", range);

	free(range);

	if(DEBUG == 1) puts(cmd);

	system(cmd);


	return 0;
}
