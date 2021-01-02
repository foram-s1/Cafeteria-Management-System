#include<string.h>//header file - defines one variable type , manipulates array of characters -stri(ignore case)
#include<conio.h>//header - console input output - clrscr() , getch() = (it holds the screen until and input from keyboard is received)
#include<stdio.h>//header - standard input output - printf(), scanf()
#include<stdlib.h>//header - standard library - memory allocating , decision making , looping  - if..else, do..while
#include<windows.h>//header - to access Windows API -  sleep, cls


struct Restuarant{//structure - group different datatyes into single data type
    char dish[50];
    int key;
    float price;
}r;

void DrawLine();// method declaration
void add();
void delet();
void modify();
void display(int a);
void search();
void adminPin();
void admin();
void bill();
void showbill();
void box();

float total=0;

void DrawLine(int n){ //ascii value of drawline function
 for(int i=0; i<n; i++)
  {
      printf("%c",254);
  }
}
int main()
{
    system("color E5");
    int a;
    system("cls");
    do
    {
        DrawLine(30);
        printf("   Welcome to the Canteen Management System!!!  ");
        DrawLine(40);
        printf("\n\n\t\t\t\t\t\t||||||||||||||||||||\n");
        printf("\t\t\t\t\t\t|                  |\n");
        printf("\t\t\t\t\t\t|    1)Admin       |\n");
        printf("\t\t\t\t\t\t|    2)Customer    |\n");
        printf("\t\t\t\t\t\t|    0)Exit        |\n");
        printf("\t\t\t\t\t\t|                  |\n");
        printf("\t\t\t\t\t\t||||||||||||||||||||\n\n");
        printf("\t\t\t\t\t\t Select the Menu:- ");
        scanf("%d",&a);
        switch(a)
        {
        case 0:
            exit(1);
            break;
        case 1:
             system("cls");
            adminPin();
            break;
        case 2:
             system("cls");
            bill();
            break;
        }
    }
    while(a!=0);
}

void adminPin()
{
    system("cls");
    char pin[4]="";
    printf("||||||||||||\t Enter the Pin :- ");
    system("color F5");
    int p=0;
    do{
        pin[p]=_getch();
        if(pin[p]!='\r'){ //return carriage
            printf("*");
        }
        p++;
    }while(pin[p-1]!='\r');
    pin[p-1]='\0'; // null terminator
    int y=atoi(pin); // alpha to int = type casting
    if(y==1234){
        printf("\n  **Verified**");
        admin();
    }
    else{
        printf("\n  Incorrect Pin. Returning to Main Menu.....");
        Sleep(2000); // millisecond
        main();
    }
}

void add()
{
    char a;
    int k;
    FILE *obj; // file pointer
    top:
        obj=fopen("menu.txt", "r+"); //read and write mode
        printf("  Enter the dish key:");
        scanf("%d",&k);
        fflush(stdin); // to flush out garbage value
        while(fread(&r,sizeof(struct Restuarant),1,obj))
        {
            if(r.key==k)
            {
                printf("  Key already exist.\n");
                fclose(obj);
                goto top; // goes to top
            }

        }
        fclose(obj);
        obj=fopen("menu.txt","a"); //append mode
        r.key=k;
        printf("  Enter the Dish Name :");
        scanf("%[^\n]s",r.dish); //delimeter
        printf("  Enter the Dish Price :");
        scanf("%f",&r.price);
        fflush(stdin);
        fwrite(&r,sizeof(struct Restuarant ),1,obj); //  adress, size , byte, pointer file
        fclose(obj);
        printf("  Would you like to add another item  [y/n]:");
        scanf("%c",&a);
        if(a=='y'){ goto top;}
        else
        {
            system("cls");
            admin();
        }
}

COORD coord = { 0, 0 }; // function to set coordinates
void gotoxy(int x, int y)
{
    coord.X = x; coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void display(int a)
{
      int c=0;
     FILE *obj;
     obj=fopen("menu.txt","r");
     gotoxy(1,1);
     int i=1,j=2;
    printf("\tKey\t\tDish Name\t\tPrice\n");

    while(fread(&r,sizeof(r),1,obj))
    {
        gotoxy(i,j);
        printf("\t%d",r.key);
        gotoxy(i+=23,j); // to create spacing in x direction
         printf(" %s",r.dish);
        gotoxy(i+=23,j);
        printf("%0.2f\n",r.price);
        i=1; c++; j++;
    }
    if(c==0)
    {
        printf("\n  List is Empty.\n");
    }
    printf("\n\n\n\n");
    fclose(obj);
    fflush(stdin);
    if(a==1){
        admin();
    }
}

void search()
{
     int c=0;
     char a[25];
     FILE *obj;
     obj=fopen("menu.txt","r");
    printf("  Enter the Dish Name:");
    fflush(stdin);
    scanf("%[^\n]s",a);
    while(fread(&r,sizeof(r),1,obj))
    {
           if(stricmp(r.dish,a)==0)  //compare two strings ignoring their case
           {
               printf("  Destination Record:\n");
                printf("\t %d\t\t %s\t\t\t %0.2f\n",r.key,r.dish,r.price);
                c++;
                break;
           }

    }
    if(c==0)
    {
        printf("Dish Not found\n");
    }
    fclose(obj);
    admin();
}

void modify()
{
     int a,c=0;
     FILE *obj;
     obj=fopen("menu.txt","r+");
    printf("  Enter the dish key:");
    scanf("%d",&a);
    fflush(stdin);
    rewind(obj);  //rewinding the file*
    while(fread(&r,sizeof(r),1,obj))
    {
        if(r.key==a)
        {
            printf("  Destination record:");
            printf("\t %d\t\t %s\t\t\t %0.2f\n",r.key,r.dish,r.price);
            //Can't change the dish key
            printf("  Enter the Dish Name at Dish Key %d:", r.key);
            scanf("%[^\n]s",r.dish);
            printf("  Enter the Dish Price:");
            scanf("%f",&r.price);
            fflush(stdin);
            fseek(obj,-sizeof(r),SEEK_CUR);  //seeking the cursor position by decreasing the size of one struct
            fwrite(&r,sizeof(r),1,obj); // And rewriting the entry
            c++;
            printf("  Record is Modified.");
            break;
        }
    }
    if(c==0)
    {
        printf("  Not found");
    }
    fclose(obj);
    admin();
}

void delet()
{
     int a,c=0;
     FILE *obj,*obj1;
     obj=fopen("menu.txt","r");
     obj1=fopen("temp.txt","w");
    printf("  Enter the dish key:");
    scanf("%d",&a);
    fflush(stdin);
    rewind(obj);
    while(fread(&r,sizeof(r),1,obj))
    {
        if(r.key==a)
        {
            printf("\t %d\t\t %s\t\t\t %0.2f\n",r.key,r.dish,r.price);
            printf("  Destination record is deleted");
            c++;
        }
        if(r.key!=a)
        {
            fwrite(&r,sizeof(r),1,obj1);
        }
    }
    if(c==0)
    {
        printf("  Not found\n\n\n");
    }
    fclose(obj);
    fclose(obj1);
    remove("menu.txt");
    rename("temp.txt","menu.txt");
    admin();
}

void admin()
{
    int a;
            printf("\n\t\t\t\t\t\t|||||||||||||||||||||||||\n");
            printf("\t\t\t\t\t\t|                       |\n");
            printf("\t\t\t\t\t\t|  1) Add Dish          |\n");
            printf("\t\t\t\t\t\t|  2) Display           |\n");
            printf("\t\t\t\t\t\t|  3) Search            |\n");
            printf("\t\t\t\t\t\t|  4) Modify            |\n");
            printf("\t\t\t\t\t\t|  5) Delete            |\n");
            printf("\t\t\t\t\t\t|  0) Exit to Main Menu |\n");
            printf("\t\t\t\t\t\t|                       |\n");
            printf("\t\t\t\t\t\t|||||||||||||||||||||||||\n");
            printf("\t\t\t\t\t\tSelect the Key:- ");
            scanf("%d",&a);
            switch(a)
            {
            case 0:
                system("cls");
                main();
                break;
            case 1:
                system("CLS");
               add();
                break;
            case 2:
                system("CLS");
               display(1);
                break;
            case 3:
                system("CLS");
               search();
                break;
            case 4:
                system("CLS");
               modify();
                break;
            case 5:
                system("CLS");
                delet();
                break;
            }
}

struct {
char d[50];
float p,amount;
int qty;
}rd;

void bill()
{
     int a,c=0;
     char ch;
    system("Color B0");
    FILE *obj,*obj1;
    display(0);
    obj1=fopen("bill.txt","w");
    do{
        obj=fopen("menu.txt","r");
        printf("  Enter the Dish Key:");
        scanf("%d",&a);
        while(fread(&r,sizeof(r),1,obj))
        {
            if(r.key==a)
            {
                c++;
                printf("  Enter the quantity:");
                scanf("%d",&rd.qty);
                rd.amount=rd.qty*r.price;
                printf("\t\t    %s\t%0.2f * %d = %0.2f\n",r.dish,r.price,rd.qty,rd.amount);
                strcpy(rd.d,r.dish);
                rd.p=r.price;
                fwrite(&rd,sizeof(rd),1,obj1);
                total=total+rd.amount;
            }
        }
        if(c==0)
        {
            printf(" Key Not found\n");
        }
        fclose(obj);
        printf("  Would you like to add another item [y/n]: ");
        fflush(stdin);
        scanf("%c",&ch);
    }while(ch!='n');
        fclose(obj1);
        showbill();
}

void showbill(){
    system("cls");
    system("Color F0");
    FILE *obj;
    obj=fopen("bill.txt","r");
    gotoxy(1,1);
    printf("|||||||||||||||||||||||||||||||||||||||||||||||| BILL  |||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    gotoxy(1,2);
    printf("\tDish Name\t\tPrice\t\t\tQty\t\tAmount\n");
    int i=2,j=3;
    while(fread(&rd,sizeof(rd),1,obj))
    {
        gotoxy(i,j);
        printf("\t%s",rd.d);
        gotoxy(i+=30,j);
        printf("%0.2f",rd.p);
        gotoxy(i+=25,j);
        printf("%d",rd.qty);
        gotoxy(i+=15,j);
        printf("%0.2f",rd.amount);
        i=2; j++;
    }
    printf("\n\t\t\t\t\t\t\t\tTOTAL = %0.2f\t\t\t\t\t\n",total);
    printf("\n\t\t\t\t\tThank You for Ordering!!!\n\n");
    fclose(obj);
}

