
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>


extern int errno;

int port;


int main (int argc, char *argv[])
{
  int sd;			
  struct sockaddr_in server;	 
  char msg[100];		

  
  if (argc != 3)
    {
      return -1;
    }

  
  port = atoi (argv[2]);

    if ((sd = socket (AF_INET, SOCK_STREAM, 0)) == -1)
    {
      perror ("Eroare la socket().\n");
      return errno;
    }

  
  
  server.sin_family = AF_INET;
  
  server.sin_addr.s_addr = inet_addr(argv[1]);
  
  server.sin_port = htons (port);
  
  
  if (connect (sd, (struct sockaddr *) &server,sizeof (struct sockaddr)) == -1)
    {
      perror ("[client]Eroare la connect().\n");
      return errno;
    }

  
  bzero (msg, 100);
  printf ("Introduceti un nume: ");
  fflush (stdout);
  read (0, msg, 100);
  msg[strlen(msg)-1]='\0';
  char msg1[200];
  strcpy(msg1,msg);
  
  
  if (write (sd, msg, 100) <= 0)
    {
      perror ("[client]Eroare la write() spre server.\n");
      return errno;
    }

  
  if (read (sd, msg, 100) < 0)
    {
      perror ("[client]Eroare la read() de la server.\n");
      return errno;
    }
  int adm=0;
  printf ("Login: %s\n", msg);
  if(strcmp(msg,"admin accepted")==0)
  {adm=1;
    printf("aveti urm actiuni:\nadd new song\nshow top\nvote\nshow top by genre\nanulez votant\nsterg piesa\nadauga comm\n vezi comm\n");
  }
  else
  if(strcmp(msg,"accepted")==0)
  {
    printf("aveti urmatoarele actiuni:\nadd new song\nvote\nshow top\nshow top by genre\nvezi comentarii\nadauga comentariu\n");
  }
  else
  {
    char raspuns[5];
    printf("doriti sa va inregistrati cu numele deja introdus?da/nu\n");
    fgets(raspuns,5,stdin);
    raspuns[strlen(raspuns)-1]='\0';
    if(strcmp(raspuns,"nu")==0)
    {close(sd);exit(1);}
    else
    {
      write(sd,"inregistrare",20);
      write(sd,msg1,100);
      printf("esti inregistrat\nacum poti folosi functiile\n");

      
        
      
    }
    
    
  }
  while(1)
  {
    char comanda[50];
    fgets(comanda,50,stdin);
    comanda[strlen(comanda)-1]='\0';
   
    if(adm=1&&strcmp(comanda,"anulez votant")==0)
    {
      write(sd,"anulezvotant",20);
      char num[20];
      printf("introduceti numele userului\n");
      fgets(num,20,stdin);
      num[strlen(num)-1]='\0';
      printf("%s...",num);
      write(sd,num,20);

    }
    else
    if(strcmp(comanda,"vezi comentarii")==0)
    {
      char com[100];
      write(sd,"vezicomm",20);
      char ce[30];
      printf("\nla ce piesa\n");
      fgets(ce,30,stdin);
      ce[strlen(ce)-1]='\0';
      write(sd,ce,30);
      read(sd,ce,30);
      int cnt=atoi(ce);
      printf("%d",cnt);
      for(int i=0;i<cnt;i++)
      {
        read(sd,com,100);
        printf("\n%s\n",com);
      }
      
    }
    if(strcmp(comanda,"adauga comentariu")==0)
    {
      write(sd,"adaugcomm",20);
      char ps[30],comm[200];
      printf("la ce piesa\n");
      fgets(ps,30,stdin);
      ps[strlen(ps)-1]='\0';
      write(sd,ps,30);
      printf("\nce comentariu\n");
      fgets(comm,200,stdin);
      comm[strlen(comm)-1]='\0';
      strcat(msg1,":");
      strcat(msg1,comm);
      write(sd,msg1,200);

    }
    if(strcmp(comanda,"show top by genre")==0)
    {char numr[2];
      char ge[20];
      write(sd,"showtopbygenre",20);
      printf("introduceti genul\n");
      fgets(ge,20,stdin);
      ge[strlen(ge)-1]='\0';
      write(sd,ge,10);
      read(sd,numr,2);
      int count=atoi(numr);
      int i;
      for(i=0;i<count;i++)
      {
        read(sd,ge,20);
        printf("\n%s",ge);
        read(sd,ge,20);
        printf("   %s",ge);
      }

    }
    if(strcmp(comanda,"sterg piesa")==0)
    {
      char num3[30];
      write(sd,"stergpiesa",20);
      printf("introduceti numele piesei\n");
      fgets(num3,30,stdin);
      num3[strlen(num3)-1]='\0';
      write(sd,num3,30);
      printf("piesa stearsa\n");

    }
    if(strcmp(comanda,"exit")==0)
    {
      write(sd,"exit",10);
      break;}
    if(strcmp(comanda,"show top")==0)
   {char cv[3];
     write(sd,"showtop",10);
     read(sd,cv,3);
     printf("%s",cv);
     int nr=atoi(cv);
     char num[50],vo[4];
     for(int i=0;i<nr;i++)
     {
       read(sd,num,50);
       printf("%s  ",num);
       read(sd,vo,4);
       printf("%s\n",vo);
     }
     
   }
   if(strcmp(comanda,"add new song")==0)
   { char num[50];
     write(sd,"addnewsong",30);
     printf("\nintroduceti numele piesei:\n");
     fgets(num,50,stdin);
     num[strlen(num)-1]='\0';
     write(sd,num,50);
     printf("\nintroduceti genul muzical\n");
     fgets(num,50,stdin);
     num[strlen(num)-1]='\0';
     write(sd,num,50);
     printf("\nintroduceti o descriere \n");
     fgets(num,50,stdin);
     num[strlen(num)-1]='\0';
     write (sd,num,50);
     printf("\nintroduceti link ul piesei\n");
     fgets(num,50,stdin);
     num[strlen(num)-1]=0;
     write(sd,num,50);
   }
   if(strcmp(comanda,"vote")==0)
   { char piesa[30];
   write(sd,"vote",30);
     printf("ce piesa doriti sa votati?\n");
     fgets(piesa,30,stdin);
     piesa[strlen(piesa)-1]='\0';
     write(sd,piesa,30);
   }
       
  }
  
  
  

  
  

  
  close (sd);
}
