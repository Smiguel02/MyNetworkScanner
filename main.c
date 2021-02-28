#include"info.h"

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
