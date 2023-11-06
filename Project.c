#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<windows.h>
#include<string.h>

void gotop(int,int);      /*function to display output at x,y position */
void menu();              
void add();              /*Add Student Information*/
void search();           /*Search Particular student */
void modify();           /*Can modify detail of any individual student*/
void deleterec();        /*Can delete the record the any student */
void display();         /*Display the data of all students */
struct student{

    char name[20];
    char mobile[10];     /*Mobile number of student */
    int roll;           /*Roll number of student */
    char course[30];
    char branch[20];
};
int main(){

gotop(17,10);
printf("***STUDENT RECORD MANAGEMENT SYSTEM***");
gotop(21,15);
printf("Press any key to continue");
getch();                               /*It will pause the execution of program until the user enters a character*/
menu();
   
return 0;
}
void gotop(int x,int y){

    COORD c;
    c.X=x;
    c.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);

}
void menu(){

    int choice;
    system("cls");
    gotop(12,3);
    printf("<<==:MENU:==>>");
    gotop(12,5);
    printf("Enter appropriate number to perform follow:");
    gotop(12,7);
    printf("1 : Add Record");
    gotop(12,8);
    printf("2 : Display Record");
    gotop(12,9);
    printf("3 : Search Record");
    gotop(12,10);
    printf("4 : Modify Record");
    gotop(12,11);
    printf("5 : Delete.");
    gotop(12,12);
    printf("6 : Exit.");
    gotop(12,15);
    printf("Enter your choice.");
    scanf("%d",&choice);  

    switch(choice){

        case 1:
        add();
        break;
 
        case 2:
        display();
        break;
        
        case 3:
        search();
        break;

        case 4:
        modify();
        break;

        case 5:
        deleterec();
        break;
        
        case 6:
        exit(1);
        break;
        
        default:
        gotop(12,17);
        printf("Invalid Choice.");
        }

}
void add(){

    FILE *f;               
    struct student std;
    char another ='y';
    system("cls");         /*To clear screen*/

    f = fopen("record.txt","ab+");

 if(f==NULL){
   gotop(12,5);
   printf("Error opening file");
   exit(1);
}
   fflush(stdin);
   while(another=='y'){
      
       gotop(12,3);
       printf("<<==ADD RECORD==>>");
       gotop(12,5);
       printf("Enter details of student.");
       gotop(12,7);
       printf("Enter Name :");
       gets(std.name);
       gotop(12,9);
       printf("Enter Mobile Number.");
       gets(std.mobile);
       gotop(12,11);
       printf("Enter Roll NO.");
       scanf("%d",&std.roll);
       fflush(stdin);
       gotop(12,13);
       printf("Enter Course .");
       gets(std.course);
       gotop(12,15);
       printf("Enter Branch.");
       gets(std.branch);

       fwrite(&std,sizeof(std),1,f);
       gotop(12,17);
       printf("To add another record click y.");
       fflush(stdin);
       another=getch();
       system("cls");
       fflush(stdin);

   }
   fclose(f);
   gotop(12,19);
   printf("press any key to continue.");
   getch();
   menu();
}
void search(){

FILE *f;
struct student std;
char sname[20];
system("cls");
gotop(12,3);
printf("<<===SEARCH RECORD===>>");
gotop(12,5);
printf("Enter Student's name:");
fflush(stdin);
gets(sname);

f=fopen("record.txt","rb+");
if(f==NULL){
    gotop(12,6);
    printf("Error Opening file");
    exit(1);
}
    while(fread(&std,sizeof(std),1,f)==1){

        if(strcmp(sname,std.name)==0){
            gotop(12,8);
            printf("Name : %s",std.name);
            gotop(12,9);
            printf("Mobile no. :%s",std.mobile);
            gotop(12,10);
            printf("Roll no. :%d",std.roll);
            gotop(12,11);
            printf("Course :%s",std.course);
            gotop(12,12);
            printf("Branch :%s",std.branch);
           
        }
    }
    fclose(f);
    gotop(12,16);
    printf("Press any key to continue.");
    getch();
    menu();
}
void modify(){

 char sname[20];
 FILE *f;
 struct student std;
 system("cls");
 gotop(12,3);
 printf("<<===MODIFY RECORD===>>");
 gotop(12,5);
 printf("Enter Student's name to modify :");
 fflush(stdin);
 gets(sname);
 f = fopen("record.txt","rb+");
 if(f==NULL){
    gotop(12,6);
    printf("Error Opening File");
    exit(1);
 }
rewind(f);
fflush(stdin);
while(fread(&std,sizeof(std),1,f)==1){

    if(strcmp(sname,std.name)==0){
 
        gotop(12,7);
        printf("Enter Name :");
        gets(std.name);
        gotop(12,9);
        printf("Enter Mobile Number.");
        gets(std.mobile);
        gotop(12,11);
        printf("Enter Roll NO.");
        scanf("%d",&std.roll);
        fflush(stdin);
        gotop(12,13);
        printf("Enter Course .");
        gets(std.course);
        gotop(12,15);
        printf("Enter Branch.");
        gets(std.branch);
        fseek(f,-sizeof(std),SEEK_CUR);
        fwrite(&std,sizeof(std),1,f);
        break;
       }
}
    fclose(f);
    gotop(12,16);
    printf("Press any key to continue.");
    getch();
    menu();


}
void deleterec(){

     char sname[20];
 FILE *f,*fn;
 struct student std;
 system("cls");
 gotop(12,3);
 printf("<<===DELETE RECORD===>>");
 gotop(12,5);
 printf("Enter Student's name to delete it from record :");
 fflush(stdin);
 gets(sname);
 f = fopen("record.txt","rb+");
 if(f==NULL){
    gotop(12,6);
    printf("Error Opening File");
    exit(1);
 }
 fn = fopen("new.txt","wb");
 if(fn==NULL){
    gotop(12,6);
    printf("Error Opening File");
    exit(1);
    }
    while(fread(&std,sizeof(std),1,f)==1){
      if(strcmp(sname,std.name)!=0){
        fwrite(&std,sizeof(std),1,fn);
      }
    }
    fclose(f);
    fclose(fn);
    remove("record.txt");
    rename("new.txt","record.txt");
    gotop(12,10);
    printf("Press any key to continue.");
    getch();
    menu();
}
void display(){
    FILE *f;
    int i=1,j;
    struct student std;
    system("cls");
    gotop(12,5);
    printf("<<====STUDENT RECORD====>>");
    gotop(12,8);
   
    printf("S.No   |Name of Student       |Mobile No.  |Roll No. |Course      |Branch      ");
    gotop(12,9);
    printf("=====================================================================================");
    f = fopen("record.txt","rb+");
if(f==NULL){
gotop(12,11);
printf("Error opening file");
exit(1);
}
j=12;
while(fread(&std,sizeof(std),1,f)==1){
    gotop(12,j);
    printf("%-7d%-22s%-12s%-9d%-12s%-12s",i,std.name,std.mobile,std.roll,std.course,std.branch);
    i++;
    j++;
}
fclose(f);
gotop(12,j+3);
printf("Press any key to continue.");
getch();
menu();
}