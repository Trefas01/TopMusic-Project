 

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define PORT 2024
struct music{char nume[200];
  char nrvoturi[4];
  char  gen[20];
  char descriere[500];
  char link[200];};
struct user{char nume[20];
  char admin[3];
  char vot [8];};


extern int errno;

struct user lista[200];
struct music listam[200];
void puncomm(char num[],char comm[])
{
	FILE *fp,*temp;
	fp=fopen("comentarii.txt","r");
	temp=fopen("replace.txt","w");
	char buf[200];
	while(fgets(buf,200,fp)!=NULL)
	{
		buf[strlen(buf)-1]='\0';
		if(strcmp(num,buf)==0)
		{
			fputs(buf,temp);
			fputs("\n",temp);
			fputs(comm,temp);
			fputs("\n",temp);
		}
		else
		{
			
			fputs(buf,temp);
			fputs("\n",temp);
		}
		

	}
	fclose(fp);
	fclose(temp);
	remove("comentarii.txt");
	rename("replace.txt","comentarii.txt");

}



void stergpiesa(int i)
{
	FILE *fp,*temp;
	fp=fopen("music.txt","r");
	temp=fopen("replace.txt","w");
	char buf[200];int cnt=0;
	while(fgets(buf,200,fp)!=NULL)
	{
		cnt++;
		if(!(cnt>i*5&&cnt<=i*5+5))
		fputs(buf,temp);

	}
	fclose(fp);
	fclose(temp);
	remove("music.txt");
	rename("replace.txt","music.txt");

}
void anulez(int i)
{
	int line=i*3+3;
	FILE *fp,*temp;
	fp=fopen("inregistrari.txt","r");
	temp=fopen("replace.txt","w");
	int k=0;
	char buf[30];
	while(fgets(buf,30,fp)!=NULL)
	{
		k++;
		if(k==line)
		{
			fputs("nuvotez\n",temp);
		
		}
		else
		{
			fputs(buf,temp);
		}
		
	}
	fclose(fp);
	fclose(temp);
	remove("inregistrari.txt");
	rename("replace.txt","inregistrari.txt");

}
void adauguser(char nume[],int k)
{
	FILE *fp,*temp;
	fp=fopen("inregistrari.txt","r");
	temp=fopen("replace.txt","w");
	char buff[20];
	while(fgets(buff,30,fp)!=NULL)
	{
		fputs(buff,temp);
	}
	fputs("\n",temp);
	fputs(nume,temp);
	fputs("\nnu",temp);
	fputs("\nvotez",temp);
	fclose(fp);
	fclose(temp);
	remove("inregistrari.txt");
	rename("replace.txt","inregistrari.txt");


}
void votez(int client,char nume[],char nrvot[],int i)
{
  FILE *fp,*temp;
  fp=fopen("music.txt","r");
  temp=fopen("replace.txt","w");
  int k=0;
  char buff[100];
  int a=atoi(nrvot);
  a++;
  
  char newvot[4];
  sprintf(newvot,"%d",a);
  
  strcpy(listam[i].nrvoturi,newvot);
  while(fgets(buff,100,fp)!=NULL)
  {
	  buff[strlen(buff)-1]='\0';
    if(strcmp(nume,buff)==0)
    {fputs(buff,temp);
	fputs("\n",temp);
	fgets(buff,100,fp);

	fputs(newvot,temp);
	fputs("\n",temp);}
    else
    {
      fputs(buff,temp);
	  fputs("\n",temp);
    }
    
  }
fclose(fp);
fclose(temp);
remove("music.txt");

rename("replace.txt","music.txt");

}
int incarcmuzic()
{
	FILE *fp = fopen("music.txt", "r");
     if(fp == NULL) {
         perror("errr");
         exit(1);
     }

     char *line = NULL;
     size_t len = 0;
     char temp[13];
     int counter=0,n=0;
 
     while(getline(&line, &len, fp) != -1) {
         counter++;
         if(counter%5==1)
         {
             strcpy(listam[n].nume,line);
             listam[n].nume[strlen(line)-1]='\0';
             
         }
         if(counter%5==2)
         {
             strcpy(listam[n].nrvoturi,line);
             listam[n].nrvoturi[strlen(line)-1]='\0';
             
         }
         if(counter%5==3)
         {
             strcpy(listam[n].gen,line);
             listam[n].gen[strlen(line)-1]='\0';
             

         }
         if(counter%5==4)
         {
             strcpy(listam[n].descriere,line);
             listam[n].descriere[strlen(line)-1]='\0';
         }
         if(counter%5==0)
         {
             strcpy(listam[n].link,line);
             listam[n].link[strlen(line)-1]='\0';
         }
         if(counter==5)
         {
             counter=0;
             n++;
         }
     }
     
 
     fclose(fp);
	 return n;
        
};

int main ()
{
	int n;
	n=incarcmuzic();
	
	
	

	FILE *fp = fopen("inregistrari.txt", "r");
     if(fp == NULL) {
         perror("errr");
         exit(1);
     }

     char *line = NULL;
     size_t len = 0;
     char temp[13];
     int counter=0,k=0;
 
     while(getline(&line, &len, fp) != -1) {
         counter++;
         if(counter%3==1)
         {
             strcpy(lista[k].nume,line);
             lista[k].nume[strlen(line)-1]='\0';
             
         }
         if(counter%3==2)
         {
             strcpy(lista[k].admin,line);
             lista[k].admin[strlen(line)-1]='\0';
             
         }
         if(counter%3==0)
         {
             strcpy(lista[k].vot,line);
             lista[k].vot[strlen(line)-1]='\0';
             

         }
         if(counter==3)
         {
             counter=0;
             k++;
         }
     }
 
     fclose(fp);
     free(line);     
    struct sockaddr_in server;	
    struct sockaddr_in from;
    char msg[100];		
    char msgrasp[100]=" ";       
    int sd;			

   
    if ((sd = socket (AF_INET, SOCK_STREAM, 0)) == -1)
    {
    	perror ("[server]Eroare la socket().\n");
    	return errno;
    }

    
    bzero (&server, sizeof (server));
    bzero (&from, sizeof (from));

   
    server.sin_family = AF_INET;
    
    server.sin_addr.s_addr = htonl (INADDR_ANY);
    
    server.sin_port = htons (PORT);

   
    if (bind (sd, (struct sockaddr *) &server, sizeof (struct sockaddr)) == -1)
    {
    	perror ("[server]Eroare la bind().\n");
    	return errno;
    }

    
    if (listen (sd, 1) == -1)
    {
    	perror ("[server]Eroare la listen().\n");
    	return errno;
    }

    
    while (1)
    {
    	int client;
    	int length = sizeof (from);

    	printf (" %d...\n",PORT);
    	fflush (stdout);

    	
    	client = accept (sd, (struct sockaddr *) &from, &length);

    	
    	if (client < 0)
    	{
    		perror ("[server]Eroare la accept().\n");
    		continue;
    	}

    	int pid;
    	if ((pid = fork()) == -1) {
    		close(client);
    		continue;
    	} else if (pid > 0) {
    		close(client);
    		while(waitpid(-1,NULL,WNOHANG));
    		continue;
    	} else if (pid == 0) {

    		close(sd);

    		
    		bzero (msg, 100);
    		

    		    		if (read (client, msg, 100) <= 0)
    		{
    			perror ("[server]Eroare la read() de la client.\n");
    			close (client);	
    			continue;		   		}

    		
			int i,numaruser,ok=0;
			for( i=0;i<=k;i++)
			{
				if(strcmp(lista[i].nume,msg)==0)
				{
					numaruser=i;
					ok=1;
					break;
				}
			}
			int adm=0;
			if(ok==1)
			{ 
				if(strcmp(lista[i].admin,"da")==0)
				{strcpy(msgrasp,"admin accepted");
				adm=1;}

				else
				strcpy(msgrasp,"accepted");
				write (client, msgrasp, 100);
			}
			else
			{
				char inreg[20];
				strcpy(msgrasp,"denied");
				write (client, msgrasp, 100);
				read(client,inreg,20);
				
				if(strcmp(inreg,"inregistrare")==0)
				{
					char nume[100];
					read(client,nume,100);
					adauguser(nume,k);
					strcpy(lista[k].nume,nume);
					strcpy(lista[k].vot,"votez");
					strcpy(lista[k].admin,"nu");
					k++;
					
				}
			}
			
			char da[30];
			int dreptdevot=0;
    		
			if(strcmp(lista[numaruser].vot,"votez")==0)
			{
				dreptdevot=1;

			}
		
			while(1){	
			read(client,da,30);
			if(strcmp(da,"stergpiesa")==0&&adm==1)
		{
			char piesa[30];
			read(client,piesa,30);
			for(i=0;i<n;i++)
			if(strcmp(listam[i].nume,piesa)==0)
			{
				stergpiesa( i);
			}

			
			
		}
		




		
			if(strcmp(da,"vote")==0){
			if(dreptdevot==1){   char numepiesa[30];
				read(client,numepiesa,30);
				
				int lineno;
				for(i=0;i<n;i++)
				{
					
					
					if(strcmp(listam[i].nume,numepiesa)==0)
					{
					
						lineno=i*5+2;
						
						votez(client,numepiesa,listam[i].nrvoturi,i);
					}
				
				}
				
				
			}}
			
			
			else
			
			if(strcmp(da,"addnewsong")==0)
			{ char rasp[50];
			FILE *fp=fopen("music.txt","a"),*commen=fopen("comentarii.txt","a");

			
				
				
				read(client,rasp,50);
				fprintf(commen,"\n");
				fprintf(commen,"%s",rasp);
				strcpy(listam[n].nume,rasp);
				
				fprintf(fp,"%s",rasp);
				fprintf(fp,"\n");
				fprintf(fp,"0");
				read(client,rasp,50);
				strcpy(listam[n].gen,rasp);
				fprintf(fp,"\n");
				fprintf(fp,"%s",rasp);
				read(client,rasp,50);
				strcpy(listam[n].descriere,rasp);
				fprintf(fp,"\n");
				fprintf(fp,"%s",rasp);
				read(client,rasp,50);
				strcpy(listam[n].link,rasp);
				fprintf(fp,"\n");
				fprintf(fp,"%s",rasp);
				n++;
				fclose(fp);

			}
		else
		if(strcmp(da,"vezicomm")==0)
		{
			char num[30],buffer[100];
			int c=0,l;
		

			read(client,num,30);
			for(int j=0;j<n;j++)
			if(strcmp(listam[j].nume,num)==0)
			l=j;
			char a[100][100];
			FILE *f=fopen("comentarii.txt","r");
			while(fgets(buffer,100,f)!=NULL)
			{
				buffer[strlen(buffer)-1]='\0';
				if(strcmp(num,buffer)==0)
				{
					while(fgets(buffer,100,f)!=NULL)
					{
						buffer[strlen(buffer)-1]='\0';
						if(strcmp(listam[l+1].nume,buffer)!=0)
						strcpy(a[c++],buffer);
						else break;
					}
				}
			}
			char nr[4];
			sprintf(nr,"%d",c);
			write(client,nr,4);
			for(int j=0;j<c;j++)
			{write(client,a[j],100);
			printf("%s..",a[j]);
			fflush(stdout);
			}
		}
		if(strcmp(da,"adaugcomm")==0)
		{
			char nume[30],comm[200];
			read(client,nume,30);
			read(client,comm,200);
			puncomm(nume,comm);

		}
		if(strcmp(da,"anulezvotant")==0)
		{
			
			fflush(stdout);
			char name[20];
			read(client,name,20);
		
			fflush(stdout);
			for(i=0;i<k;i++)
			{
				if(strcmp(name,lista[i].nume)==0)
				{
					
					
					anulez(i);
				}
			}
		}
		if(strcmp(da,"showtopbygenre")==0)
		{ char ra[20];
		struct music aux[20],aux2;

		int co=0;
			read(client,ra,20);
			for(i=0;i<n;i++)
			{
				if(strcmp(listam[i].gen,ra)==0)
				{
					aux[co++]=listam[i];
				}
			}
			for(i=0;i<co-1;i++)
			for(int j=1;j<co;j++)
			{
				if(atoi(aux[i].nrvoturi)<atoi(aux[i].nrvoturi))
				{
					aux2=aux[i];
					aux[i]=aux[j];
					aux[j]=aux2;
				}

			}
			char nr[2];
			sprintf(nr,"%d",co);
			write(client,nr,2);
			for(i=0;i<co;i++)
			{
				write(client,aux[i].nume,20);
				write(client,aux[i].nrvoturi,20);
			}


		}
		
		
			if(strcmp(da,"showtop")==0)
			{
				
				struct music aux;
				n=incarcmuzic();
				for (i=0;i<n-1;i++)
				for(int j=1;j<n;j++)
				{
					if(atoi(listam[i].nrvoturi)<atoi(listam[j].nrvoturi))
					{
						aux =listam[i];
						listam[i]=listam[j];
						listam[j]=aux;

					}
				}
				
				char nr[3];
				sprintf(nr,"%d",n);
			
				write(client,nr,3);
				for(i=0;i<n;i++)
				{
					write(client,listam[i].nume,50);
					write(client,listam[i].nrvoturi,4);
				}
			}
			if(strcmp(da,"exit")==0)
			break;

			
			}


    		
			
    		
    		
    		close (client);
    		exit(0);
    	}

    }				
}				
