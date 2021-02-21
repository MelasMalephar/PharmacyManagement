#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h>
#include<stdio.h>
#include<fstream.h>
#include<iomanip.h>
#include <time.h>

int n ,nmax=0,s=0,uniqueId=1;

time_t t = time(NULL);
tm* timePtr = localtime(&t);

class medicine_name
{
 private: unsigned int drugid ,mg;
	  char  drugname [30];
	  float drugprice;
 public : void insert();
    void update();
	  void display();
	  char* retname()
	  { return drugname; }
	  int retmed()
	  { return drugid ; }
	  float retamt()
	  { return drugprice ; }
};
void medicine_name::insert ()                //insert deatils of medicines
{
    cout<<"Enter the drug id:";
    cin>>drugid ;
    cout<<"Enter the mg:";
    cin>>mg ;
    cout<<"Enter the drug name:";
    gets(drugname) ;
    cout<<"Enter the drug price:";
    cin>>drugprice ;

}

void medicine_name::update ()                //update deatils of medicines
{
    cout<<"Drug id:"<<retmed()<<endl;
    cout<<"Enter the mg:";
    cin>>mg ;
    cout<<"Enter the drug name:";
    gets(drugname) ;
    cout<<"Enter the drug price:";
    cin>>drugprice ;

}
void medicine_name::display()
{ int k;
  k=(11-strlen(drugname));
  cout<<drugid<<"\t\t   "<<mg<<"\t\t\t   "<<drugname<<setw(13+k)<<drugprice<<" Rs"<<endl;
}

void medicineaddlist()          //Add new medicine in list
{
      char choice;
      medicine_name m;
      ofstream mfile("Medicine.dat",ios::binary||ios::nocreate||ios::app);
      do
    { mfile.seekp(0,ios::end);
      m.insert();
      mfile.write((char *) &m , sizeof (m)) ;
      cout<<"Want to continue Y/N";
      cin>>choice;
    }
      while(toupper(choice)=='Y');
      mfile.close();
}
void updatemedicinelist()          //function for updating order
{ int flag=0,tbno;
  medicine_name u;
  ifstream ufile("Medicine.dat",ios::binary);
  ofstream tsfile("temp.dat",ios::binary);
  cout<<"\t\t  Update Order \n";
  cout<<"\t\t----------------\n";
  cout<<"\nEnter the Drug-id to be updated : ";
  cin>>tbno;
  while(ufile.read((char*) &u , sizeof(u)))
  {   if(tbno==u.retmed())
	{ u.update();
	  flag=1;
	}
   tsfile.write((char*) &u,sizeof(u));
  }
  if(!flag)
  { textcolor(RED);
    cprintf("Invalid Recieptno");
    textcolor(WHITE);
  }
  getch();
 ufile.close();
 tsfile.close();
 remove("Medicine.dat");
 rename("temp.dat","Medicine.dat");
}
void medicinedisplaylist()     //display list of medicines
{
     medicine_name m;
     ifstream msfile("Medicine.dat",ios::binary);
     cout <<"**************************************************************************\n";
     cout<<"DRUGS ID"<<"\t    MG\t"<<"    \t\t  DRUGS NAME"<<"         DRUGS PRICE"<<endl;
     cout <<"**************************************************************************\n";
while(msfile.read((char*) &m,sizeof(m)))
 m.display();
 cout <<"**************************************************************************\n";
 msfile.close();
}

int  UniqueIDGenerator  ()
{
  return uniqueId++;
}

class maindata
 {
  private: unsigned int recieptno,id[8],quantity[8];
	   char customername[25];
	   float totalamt , amt[8];
  public:  void readmaindata();
	   void writemaindata();
	   int retrpt()
	   { return recieptno ;}
	   void updatedata();
	   void showupdatedata();
 };
void maindata::readmaindata()        //function for taking order
 {
  clrscr();
  cout<<"\t\t  Medicine order\n";
  cout<<"\t\t------------------\n";
  medicinedisplaylist();
  recieptno= UniqueIDGenerator();
  cout<<"\nReceipt number:"<<recieptno<<endl;
  cout<<"Enter the customer name:";
  gets(customername);
  cout<<"Enter the total number of medicines:";
  cin>>n;
  if (nmax==0)
     nmax=n;
  else
     if (n > nmax)
      nmax=n;
  for(int i=0;i<n;++i)
  {
   cout<<"Enter the drugID of medicine "<<i+1<<":";
   cin>>id[i];
     while(id[i]>7)
      {
  textcolor(RED);
  cprintf("Invalid drugID");
  textcolor(WHITE);
	cout<<"\nRenter the drugID of medicine "<<i+1<<":";
	cin>>id[i];
      }
   cout<<"Enter the desired quantity (<=10):";
   cin>>quantity[i];
     while(quantity[i]>10)
      {
   textcolor(RED);
   cprintf("quantity exceeded");
   textcolor(WHITE);
	 cout<<"\nRenter the desired quantity (<=10)";
	 cin>>quantity[i];
      }
  }
 }
void maindata::showupdatedata()        //function to show updated data
{
  cout<<"\nReceipt number:"<<recieptno<<endl;
  cout<<"Customer name:"<<customername;

}

void maindata::updatedata()       //function for updating data
 {
  medicinedisplaylist();
  showupdatedata();
  cout<<"\nEnter the total number of medicines:";
  cin>>n;
  if (nmax==0)
     nmax=n;
  else
     if (n > nmax)
      nmax=n;
  for(int i=0;i<n;++i)
  {
   cout<<"Enter the drugID of medicine "<<i+1<<":";
   cin>>id[i];
     while(id[i]>7)
      {
  textcolor(RED);
  cprintf("Invalid drugID");
  textcolor(WHITE);
	cout<<"\nRenter the drugID of medicine "<<i+1<<":";
	cin>>id[i];
      }
   cout<<"Enter the desired quantity (<=10):";
   cin>>quantity[i];
     while(quantity[i]>10)
      {
   textcolor(RED);
   cprintf("quantity exceeded");
   textcolor(WHITE);
	 cout<<"\nRenter the desired quantity (<=10)";
	 cin>>quantity[i];
      }
  }
 }

void maindata::writemaindata()        //function for displaying data
 {
  int j;
  float a;
  totalamt=0;
  cout<<"\nReceipt number: "
      <<recieptno<<endl;
  cout<<"Customer name: "
      <<customername;
  cout <<"\n**********************************************\n";
  cout<<"Medicines\t"<<"\tQuantities"<<"\tAmount" ;
  cout <<"\n**********************************************\n";
    for( j=0 ; j<nmax ; ++j)
     {    medicine_name  e ;
	 ifstream mj("Medicine.dat",ios::binary);
	while( mj.read((char *) &e,sizeof(e)))
	 {   if(e.retmed()==id[j])
	    {
	      cout<<e.retname();
	      cout<<setw(15)<<quantity[j];
	      amt[j]=e.retamt();
	      a=amt[j]*quantity[j];
	      cout<<setw(18)<<a<<endl;
	      totalamt+=a;

	    }
	 }
     }
     cout<<"\nTotal amount :" <<setw(30)<<totalamt;
     cout <<"\n**********************************************\n";
 }
void takeorder()              //function to take order
{
     char choice;
     maindata o;
     ofstream ofile("order.dat",ios::binary);
     do
     {
      o.readmaindata();
      ofile.write((char*) &o , sizeof(o));
      cout<<"\nWant to Enter more Order(y/n):";
      cin>>choice;
     }
     while(tolower(choice)=='y');
     ofile.close();
}

void addorder()              //function to add order
{
  char choice;
  maindata o;
  ofstream ofile("order.dat",ios::binary|ios::app);
  do
  {
   o.readmaindata();
   ofile.write((char*) &o , sizeof(o));
   cout<<"\nWant to Enter more Order(y/n)";
   cin>>choice;
  }
  while(tolower(choice)=='y');
  ofile.close();
}

void displayorder()         //function for displaying order
{
 maindata or;
 ifstream orfile("order.dat",ios::binary);
 orfile.seekg(0, ios::end);
 if (orfile.tellg() == 0)
  { textcolor(RED);
    cprintf("No data in file");
    cout << endl;
    textcolor(WHITE);
  }
 else
 {
   orfile.seekg(0, ios::beg);
   cout<<"\t\t  All Order list\n";
   cout<<"\t\t------------------\n";
   while(orfile.read((char*) &or,sizeof(or)))
   or.writemaindata();
   orfile.close();
 }
}

void deleteorder()        //function for deleting order
{
   maindata k;
   int delno,a;
   char confirm ='n',b,found='f';
   ifstream  kfile("order.dat",ios::binary);
   ofstream  lfile("temp.dat",ios::binary);
   cout<<"\t\t  Delete Order\n";
   cout<<"\t\t----------------\n";
   cout<<"\nEnter the Order no to be deleted :";
   cin>>delno;
   while(kfile.read((char*) &k ,sizeof(k)))
   if(k.retrpt() == delno)
     { cout<<"\nOrder being Deleted";
       found = 't';
       k.writemaindata();
       textcolor(RED);
       cprintf("Are you sure,You want to delete this record(y/n): ");
       cin>>confirm;
       textcolor(WHITE);
       b=toupper(confirm);
       if(b=='N')
	{ lfile.write((char*) &k,sizeof (k));
	  cout<<"\nOrder cancelled";
	}
      }
   else
      { lfile.write((char*) &k,sizeof (k));
	      found='t';
      }
   if( b!='N' && delno > (uniqueId-1) || found=='f')
      cout<<"\nItem to be deleted is not in the list";
   else if(found=='t' && b!='N')
      cout<<"\nOrder deleted ";
   getch();
   clrscr();
   cout<<"\nPrevious file data\n";
   displayorder();
   remove("order.dat");
   rename("temp.dat","order.dat");
   kfile.close();
   lfile.close();
   clrscr();
   ifstream  tfile("order.dat",ios::binary);
   tfile.seekg(0, ios::end);
   if (tfile.tellg() == 0)
    { textcolor(RED);
      cprintf("No data in file");
      cout << endl;
      textcolor(WHITE);
    }
   else
   {
     cout<<"New list\n";
     tfile.seekg(0, ios::beg);
     while(tfile.read((char*) &k,sizeof(k)))
     k.writemaindata();
     tfile.close();
   }
}

void updateorder()          //function for updating order
{ int flag=0,tbno;
  maindata u;
  ifstream ufile("order.dat",ios::binary);
  ofstream tsfile("tem.dat",ios::binary);
  cout<<"\t\t  Update Order \n";
  cout<<"\t\t----------------\n";
  cout<<"\nEnter the Recieptno to be updated : ";
  cin>>tbno;
  while(ufile.read((char*) &u , sizeof(u)))
  {   if(tbno==u.retrpt())
	{ u.updatedata();
	  flag=1;
	}
   tsfile.write((char*) &u,sizeof(u));
  }
  if(!flag)
  { textcolor(RED);
    cprintf("Invalid Recieptno");
    textcolor(WHITE);
  }
 ufile.close();
 tsfile.close();
 remove("order.dat");
 rename("tem.dat","order.dat");
}

void printorder()      //function for printing order
{  int flag=0,tbno;
  maindata u;
  ifstream ufile("order.dat",ios::binary);
  cout<<"\t\t  Print order\n";
  cout<<"\t\t----------------\n";
  cout<<"\nEnter the Recieptno to be shown: ";
  cin>>tbno;
  while(ufile.read((char*) &u , sizeof(u)))
   if(tbno==u.retrpt())
	{ clrscr();
	  cout<<"\t\t  Print order\n";
	  cout<<"\t\t----------------\n";
	  cout << "\nDate:" <<(timePtr->tm_mday)<<"/"<< (timePtr->tm_mon)+1 <<"/"<< (timePtr->tm_year)+1900<< endl;
	  cout << "Time:" << (timePtr->tm_hour)<<":"<< (timePtr->tm_min)<<":"<< (timePtr->tm_sec);
	  u.writemaindata();
	  flag=1;
	}
  if(!flag)
   {textcolor(RED);
    cprintf("Invalid Recieptno");
    textcolor(WHITE);}
}

void main()
{
  clrscr();

  int f=0,flag=0;
 do                        //admin password
 {
  clrscr();
  cout<<"Enter the password:";
  int i,x;
   char ch='/0',password[]="nmn",match[20];
   for(i=0;i>=0;)
    {
      ch=getch();

     if(ch!=8&&ch!=13)
      {
	cout<<"*";
	match[i]=ch;
	i++;
      }
     else if (ch==8)
      {
  cout<<"\b \b";
   i--;
      }
     else if(ch==13)
      {
       match[i]='\0';
       break;
      }
   else
       break;
 }
 if(strcmp(match,password)==0)
 {
  f=1;
  cout<<endl<<"password correct";
 }
 else if(!f)
 {
  textcolor(RED);
  cout<<endl;
  cprintf("incorrect password");
  textcolor(WHITE);

 }
getch();
}
while(!f);
  int men;
  char choice;
  do
  {
    clrscr();
    cout<<"\t\t\t    Pharmacy Management System \n";
    cout<<"\t\t==================================================\n\n";
    cout<<"\t\t--------------------------------------------------\n";
  if(s==0)
    cout<<"\t\t||\t1. Take new Medicine order \t\t ||\n";
  else
    cout<<"\t\t||\t1. Add Medicine order      \t\t ||\n";
    cout<<"\t\t||\t2. Delete latest Medicine order\t\t ||\n";
    cout<<"\t\t||\t3. Modify Order List \t\t\t ||\n";
    cout<<"\t\t||\t4. Print the Reciept \t\t\t ||\n";
    cout<<"\t\t||\t5. Daily Summary of total Sale \t\t ||\n";
    cout<<"\t\t||\t6. Exit\t\t\t\t\t ||\n";
    cout<<"\t\t--------------------------------------------------\n";
    cout<<"\nEnter choice: ";
    cin>>men;
    clrscr();
    switch (men)
     {
      case 1:if(s==0)
	     {  takeorder();
		s++ ; }
	     else
	       addorder();
      break;
      case 2: deleteorder();
      break;
      case 3: updateorder();
      break;
      case 4: printorder();
      break;
      case 5: displayorder();
      break;
      case 6:  cout<<"\nBye  \nProject by Namit and Ram";
	       getch();
	       exit(0);
      default: cout<<"\nInvalid input";
	       exit(0);
    }
 getch();
 clrscr();

 cout<<"Press 1 for Main menu"
     <<"\nPress any other  key to exit"<<endl;
     cin>>men;

 }

 while(men==1);
 cout<<"\nBye  \nProject by Namit and Ram";

 getch();
 /*updatemedicinelist();
 clrscr();
 medicinedisplaylist();
 getch();*/
 }
