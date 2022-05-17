//***************************************************************
// HEADER FILES
//****************************************************************

#include<conio.h>
#include<stdio.h>
#include<process.h>
#include<fstream.h>

//***************************************************************
// CLASS 
//****************************************************************

class product
{
int pno;
char name[50];
float price,qty,tax,dis;
public:
void create_product()
{
cout<<"\nPlease Enter The Product No. of The Product ";
cin>>pno;
cout<<"\n\nPlease Enter The Name of The Product ";
gets(name);
cout<<"\nPlease Enter The Price of The Product ";
cin>>price;
cout<<"\nPlease Enter The Discount (%) ";
cin>>dis;
}

void show_product()
{
cout<<"\nThe Product No. of The Product : "<<pno;
cout<<"\nThe Name of The Product : ";
puts(name);
cout<<"\nThe Price of The Product : "<<price;
cout<<"\nDiscount : "<<dis;
}

int retpno()
{return pno;}

float retprice()
{return price;}

char* retname()
{return name;}

int retdis()
{return dis;}

}; 






//***************************************************************
// global declaration for stream object, object
//****************************************************************

ifstream fin;
ofstream fout;
product pr;










//***************************************************************
// function to write in file
//****************************************************************
void write_product()
{
fout.open("Shop.dat",ios::out|ios::app);
pr.create_product();
fout.write((char*)&pr,sizeof(product));
fout.close();
cout<<"\n\nThe Product Has Been Created ";
getch();
}







//***************************************************************
// function to read all records from file
//****************************************************************
void display_all()
{
clrscr();
cout<<"\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
fin.open("Shop.dat",ios::in);
while(fin.read((char*)&pr,sizeof(product)))
{
pr.show_product();
cout<<"\n\n====================================\n";
getch();
}
fin.close();
getch();
}







//***************************************************************
// function to read specific record from file
//****************************************************************
void display_sp(int n)
{
int flag=0;
fin.open("Shop.dat",ios::in);
while(fin.read((char*)&pr,sizeof(product)))
{
if(pr.retpno()==n)
{
clrscr();
pr.show_product();
flag=1;
}
}
fin.close();
if(flag==0)
cout<<"\n\nrecord not present ";
getch();
}







//***************************************************************
// function to modify record of file
//****************************************************************
void modify_product()
{
int no,found=0;
clrscr();
cout<<"\n\n\tTo Modify ";
cout<<"\n\n\tPlease Enter The Product No. of The Product";
cin>>no;
fin.open("Shop.dat",ios::in|ios::out);
while(fin.read((char*)&pr,sizeof(product)) && found==0)
{
if(pr.retpno()==no)
{
pr.show_product();
cout<<"\nPlease Enter The New Details of Product"<<endl;
pr.create_product();
int pos=-1*sizeof(pr);
fout.seekp(pos,ios::cur);
fout.write((char*)&pr,sizeof(product));
cout<<"\n\n\t Record Updated";
found=1;
}
}
fout.close();
if(found==0)
cout<<"\n\n Record Not Found ";
getch();
}







//***************************************************************
// function to delete record of file
//****************************************************************
void delete_product()
{
int no;
clrscr();
cout<<"\n\n\n\tDelete Record";
cout<<"\n\nPlease Enter The product no. of The Product You Want To Delete";
cin>>no;
fin.open("Shop.dat",ios::in|ios::out);
ofstream fout;
fout.open("Temp.dat",ios::out);
fin.seekg(0,ios::beg);
while(fin.read((char*)&pr,sizeof(product)))
{
if(pr.retpno()!=no)
{
fout.write((char*)&pr,sizeof(product));
}
}
fout.close();
fin.close();
remove("Shop.dat");
rename("Temp.dat","Shop.dat");
cout<<"\n\n\tRecord Deleted ..";
getch();
}











//***************************************************************
// function to display all products price list
//****************************************************************

void menu()
{
clrscr();
fin.open("Shop.dat",ios::in);


cout<<"\n\n\t\tProduct MENU\n\n";
cout<<"====================================================\n";
cout<<"P.NO.\t\tNAME\t\tPRICE\n";
cout<<"====================================================\n";

while(fin.read((char*)&pr,sizeof(product)))
{
cout<<pr.retpno()<<"\t\t"<<pr.retname()<<"\t\t"<<pr.retprice()<<endl;
}
fin.close();
}













//***************************************************************
// function to place order and generating bill for Products
//****************************************************************

void place_order()
{
int order_arr[50],quan[50],c=0;
float amt,damt,total=0;
char ch='Y';
menu();
cout<<"\n============================";
cout<<"\n PLACE YOUR ORDER";
cout<<"\n============================\n";
do{
cout<<"\n\nEnter The Product No. Of The Product : ";
cin>>order_arr[c];
cout<<"\nQuantity in number : ";
cin>>quan[c];
c++;
cout<<"\nDo You Want To Order Another Product ? (y/n)";
cin>>ch;
}while(ch=='y' ||ch=='Y');
cout<<"\n\nThank You For Placing The Order";getch();clrscr();
cout<<"\n\n********************************INVOICE************************\n";
cout<<"\nPr No.\tPr Name\tQuantity \tPrice \tAmount \tAmount after discount\n";
for(int x=0;x<=c;x++)
{
fin.open("Shop.dat",ios::in);
fin.read((char*)&pr,sizeof(product));
while(!fin.eof())
{
if(pr.retpno()==order_arr[x])
{
amt=pr.retprice()*quan[x];
damt=amt-(amt*pr.retdis()/100);
cout<<"\n"<<order_arr[x]<<"\t"<<pr.retname()
<<"\t"<<quan[x]<<"\t\t"<<pr.retprice()<<"\t"<<amt<<"\t\t"<<damt;
total+=damt;
}
fin.read((char*)&pr,sizeof(product));
}

fin.close();
}
cout<<"\n\n\t\t\t\t\tTOTAL = "<<total;
getch();
}














//***************************************************************
// ADMINSTRATOR MENU FUNCTION
//****************************************************************
void admin_menu()
{
clrscr();
int opt2;
cout<<"\n\n\n\tADMINISTRATOR MENU";
cout<<"\n\n\t1.CREATE PRODUCT";
cout<<"\n\n\t2.DISPLAY ALL PRODUCTS";
cout<<"\n\n\t3.QUERY ";
cout<<"\n\n\t4.MODIFY PRODUCT";
cout<<"\n\n\t5.DELETE PRODUCT";
cout<<"\n\n\t6.VIEW PRODUCT MENU";
cout<<"\n\n\t7.BACK TO MAIN MENU";
cout<<"\n\n\tPlease Enter Your Choice (1-7) ";
cin>>opt2;

if(opt2==1)
{write_product();}
else if(opt2==2){display_all();}
else if (opt2==3)
{
int num;
clrscr();
cout<<"\n\n\tPlease Enter The Product No. ";
cin>>num;
display_sp(num);
}
else if(opt2==4){ modify_product();}
else if(opt2==5){ delete_product();}
else if(opt2==6){ menu();
getch(); }
else
{ admin_menu();}

}








//***************************************************************
// main
//****************************************************************
void main()
{
int opt1;

do
{
clrscr();
cout<<"\n\n\n\tMAIN MENU";
cout<<"\n\n\t01. CUSTOMER";
cout<<"\n\n\t02. ADMINISTRATOR";
cout<<"\n\n\t03. EXIT";
cout<<"\n\n\tPlease Select Your Option (1-3) ";
cin>>opt1;
if(opt1==1){ clrscr();
place_order();
getch();}
else if(opt1==2) {admin_menu();}
}
while(!opt1==3);
}














