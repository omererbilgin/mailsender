#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

//
void outro(int, char*);
char *readFile(char*);
int getmailnum(char*);
char *setvmail(char*, int);
char *mailpath();
void setopts(char*, int);
int getprocnum(char*);
bool cred();
void changeproc(int, char*);
//


int main(){ 

system("clear");

char *path = malloc(10000);
path = mailpath();
system("clear");

int mailnum = getmailnum(path);

setopts(path, mailnum);

getchar();

int i = getprocnum(path);

system("clear");

while(i < mailnum){


char *vmail = malloc(300);
vmail = setvmail(path, i);

char *runcmd = malloc(100);
snprintf(runcmd, 100, "python3 connectsmtp.py %s",vmail);
system(runcmd);
free(runcmd);

// gonna set threads compatible with memory 
// do not forget to set i++ on each thread
i++;

changeproc(i,path);

}
system("clear");
outro(i + 1,path);
return 0;
}

char *readFile(char cmd[200]) { 

char cmd1[99999] = {0};
system("touch cmd");  
snprintf(cmd1, 99999, "%s >> cmd", cmd);
system(cmd1); 
    
FILE *f = fopen("cmd", "rt");
assert(f);
fseek(f, 0, SEEK_END);
long length = ftell(f);
fseek(f, 0, SEEK_SET);
char *buffer = (char *) malloc(length + 1);
buffer[length] = '\0';
fread(buffer, 1, length, f);
fclose(f);
system("rm cmd");

return buffer;
}

char *setvmail(char *path, int proc){ 


char *vmail = malloc(60);
char *vmailcmd = malloc(100);
snprintf(vmailcmd, 100, "sed -n %dp %s",proc + 3,path);
vmail = readFile(vmailcmd);
int length = strlen(vmail);
vmail[length - 1] = '\0';
free(vmailcmd);

return vmail;

}

int getmailnum(char *path){ 

char *getnumcmd = malloc(100);
snprintf(getnumcmd, 100, "wc -l templist.txt | cut -f 1 -d ' '");
char *num = readFile(getnumcmd);
int length = strlen(num);
num[length - 1] = '\0';
int numm = atoi(num);

return numm + 1;

}

char *mailpath(){ 

char *path = malloc(900);
system("clear");
printf("List path: ");
fgets(path, 900, stdin);

int length1 = strlen(path);
path[length1 - 1] = '\0';

char *pwd = malloc(2000);
pwd = readFile("pwd");
int length = strlen(pwd);
pwd[length - 1] = '\0';
char *cpcmd = malloc(2000);
snprintf(cpcmd, 2000, "cp %s templist.txt", path);
system(cpcmd);
char *curpath = malloc(5000);
snprintf(curpath, 5000, "%s/templist.txt",pwd);

return curpath;
}

void setopts(char *path, int x){ 

char *setproc = malloc(100);
snprintf(setproc, 100, "sed -i '1i proc=0' %s",path);
system(setproc);
free(setproc);

char *setnum = malloc(100);
snprintf(setnum, 100, "sed -i '1i num=%d' %s",x,path);
system(setnum);
free(setnum);

}

int getprocnum(char *path){ 

char *numcmd = malloc(100);
snprintf(numcmd, 100, "sed -n 2p %s | cut -f 2 -d '='",path);
char *num = readFile(numcmd);
int length = strlen(num);
num[length - 1] = '\0';
int i = atoi(num);

return i;

}


void changeproc(int i, char *path){

char *del = malloc(20000);
snprintf(del, 20000, "sed -i '2d' %s",path);
system(del);

char *write = malloc(20000);
snprintf(write, 20000, "sed -i '2i proc=%d' %s",i,path);
system(write);

}

void outro(int x, char *path){

char *del = malloc(100);
snprintf(del, 100, "rm %s",path);
system(del);

char *zenity = malloc(100);
snprintf(zenity, 100, "zenity --info --text='%d mails has been sent'",x - 1);
system(zenity);
system("clear");
exit(0);

}
