#include "PJ_RPI.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

void finish_with_error(MYSQL *conn){
        fprintf(stderr, "%s\n",mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

int main(int args, char **argv)
{
	if(map_peripheral(&gpio) == -1) 
	{
       	 	printf("Failed to map the physical GPIO registers into the virtual memory space.\n");
        	return -1;
    	}
		MYSQL *conn = mysql_init(NULL);
	
	if(conn == NULL)
	{
		fprintf(stderr, "%s\n",mysql_error(conn));
        mysql_close(conn);
        exit(1);
	}

	if(mysql_real_connect(conn,"Localhost","pi","password","Embeded_GPIO",0,NULL,0) == NULL)
	{
		fprintf(stderr, "%s\n",mysql_error(conn));
        mysql_close(conn);
        exit(1);
	}
	char operation[50];
	int P26;
	int OS26 = 0;
	int NS26 = 0;
	int P17;
	int OS17 = 0;
	int NS17 = 0;
	INP_GPIO(26);
	INP_GPIO(17);
	while(1)
	{
		if(GPIO_READ(26))
		{
			NS26 = 1;
		}
		else
		{
			NS26 = 0;
		}
		if(OS26 != NS26)
		{
			if(GPIO_READ(26)){
			printf("de pin is hoog\n");
			P26 = 26;
			sprintf(operation,"INSERT INTO pinnen_log VALUES(NULL,'%d','%d',NULL)",P26, NS26); // versturen naar db
			if (mysql_query(conn,operation)) {
			finish_with_error(conn);
			}
			}
			else{
			printf("de pin is laag\n");
			P26 = 26;
			sprintf(operation,"INSERT INTO pinnen_log VALUES(NULL,'%d','%d',NULL)",P26, NS26); // versturen naar db
			if (mysql_query(conn,operation)) {
			finish_with_error(conn);
			}
			}
			OS26 = NS26;
		}

		if(GPIO_READ(17))
		{
			NS17 = 1;
		}
		else
		{
			NS17 = 0;
		}
		if(OS17 != NS17)
		{
			if(GPIO_READ(26)){
			printf("de pin is hoog\n");
			P17 = 26;
			sprintf(operation,"INSERT INTO pinnen_log VALUES(NULL,'%d','%d',NULL)",P17, NS17); // versturen naar db
			if (mysql_query(conn,operation)) {
			finish_with_error(conn);
			}
			}
			else{
			printf("de pin is laag\n");
			P17 = 26;
			sprintf(operation,"INSERT INTO pinnen_log VALUES(NULL,'%d','%d',NULL)",P17, NS17); // versturen naar db
			if (mysql_query(conn,operation)) {
			finish_with_error(conn);
			}
			}
			OS17 = NS17;
		}
	}

	return 0;	

}
