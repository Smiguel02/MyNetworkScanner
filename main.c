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
	
	if(DEBUG) printf("Ini: |%c| \n", ini[0]);
	if(DEBUG) printf("maxlen:|%d| \n", real_len);

	while(real_len > -1 && ini[real_len] != end) real_len--;
	if(DEBUG) printf("Debug - Last char:|%c|\n", ini[real_len+1]);
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

char* getPackageManager()
{
	int DEBUG = 0;
	FILE *fp;
  	char line[130]="";
	
	fp = fopen("/etc/os-release", "r");

	for(int i = 0; i < 7; i++) fgets( line, sizeof line, fp);

	fclose(fp);

	if (DEBUG) printf("line: %s", line);
	
	int ID_LIKE_Start = 8;
	char* ID_LIKE = (char *)calloc (10 + 1, sizeof(char));
	
	int i = 0;
	
	while( line[ID_LIKE_Start + i] != '\0')
	{
		ID_LIKE[i] = line[ID_LIKE_Start + i];
		i++;
	}
	
	ID_LIKE[--i] = '\0';	
	
	printf("\nID_LIKE:|%s| \n\n", ID_LIKE);
	
	if (strcmp("debian\0", ID_LIKE) == 0 ) if(DEBUG == 1) printf("apt \n");
	else if (strcmp("arch\0", ID_LIKE) == 0 ) if(DEBUG == 1) printf("pacman -S");



	return NULL;
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
	printf("\nYour IP address:|%s| \n\n", inet);

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
	int DEBUG = 1;

	getPackageManager();
	

	char option;


	do
	{
		printf("Nmap requeired! Do you want to install it or upgrade it? \n\n");
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

	char cmd[] = "sudo nmap -sn";

	char* Finalcmd = (char *)calloc(strlen(cmd) + 1 + strlen(range) + 1, sizeof(char) );

	sprintf(Finalcmd, "%s %s", cmd, range);
	//-sT: scan TCP
	//-sn: ping scan - nao funciona localmente
	//-O: Enable OS detection;  You need to use a scan type along with it, such as -sS, -sT, -sF, etc instead of -sn

	free(range);

	if(DEBUG == 1) puts(cmd);

	system(Finalcmd);


	return 0;
}
