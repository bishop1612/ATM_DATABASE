#include<iostream.h>
#include<stdio.h>
#include<fstream.h>
#include<conio.h>
#include<time.h>
#include<stdlib.h>
class ATM
{
		long acno;
		int pin;
		char name[30];
		float bal;
	public:
		void balenq()
		{
			cout<<"\nName\t\t: "<<name;
			cout<<"\nAccount ID\t: "<<acno;
			cout<<"\nAccount Balance\t: "<<bal;
		}
		void cashdep();
		void cashwth();
		void pinch();
		long gacno()
		{
			return acno;
		}
		int gpin()
		{
			return pin;
		}
		void pacno(long a)
		{
			acno=a;
		}
		void ppin(int p)
		{
			pin=p;
		}
		void pname()
		{
			gets(name);
		}
		void pbal(float b)
		{
			bal=b;
		}

}n2;
void ATM::cashdep()
{
	float amt;
	cout<<"\nEnter amount to be deposited : Rs.";
	cin>>amt;
	if(amt>0)
	{
		bal+=amt;
	}
}
void ATM::cashwth()
{
	float amt;
	cout<<"\nEnter amount to be withdrawn : Rs.";
	cin>>amt;
	if((bal-amt)>40000)
	{
		bal-=amt;
	}
	else
	{
		cout<<"Balance insufficient for transaction!";
		getch();
	}
}
void ATM::pinch()
{
	int num;
	cout<<"\nEnter new 3-digit pin : ";
	cin>>num;
	if((num>=100)&&(num<=999))
	{
		pin=num;
		return;
	}
}
void modify(ATM);
void openac();
void closac(ATM);
int login();
void main()
{
	int c1=1,c2=1;
	while(c1)
	{
		clrscr();
		c1=0;
		cout<<"\n---CITIBANK SERVICES---";
		cout<<"\n\nPlease choose from below :";
		cout<<"\n1. Log in";
		cout<<"\n2. Create new account";
		cout<<"\nEnter choice (any other key to exit): ";
		cin>>c1;
		if(c1==1)
		{
			while(c2)
			{
				if(login()==0)
					break;
				c2=0;
				clrscr();
				cout<<"\nLogged in\n";
				n2.balenq();
				cout<<"\n\nPlease select from the following:";
				cout<<"\n1. Balance enquiry";
				cout<<"\n2. Cash deposit";
				cout<<"\n3. Cash Withdrawal";
				cout<<"\n4. Pin Change";
				cout<<"\n5. Delete account";
				cout<<"\nEnter choice (any other key to exit): ";
				cin>>c2;
				switch(c2)
				{
					case 1: n2.balenq();
					break;
					case 2: {
						n2.cashdep();
						modify(n2);
						n2.balenq();
						}
					break;
					case 3: {
						n2.cashwth();
						modify(n2);
						n2.balenq();
						}
					break;
					case 4: {
						n2.pinch();
						modify(n2);
						n2.balenq();
						}
					break;
					case 5: closac(n2);
					default:{
						cout<<"\nReturning to previous menu";
						c2=0;
						}
				}
			}
		}
		else if(c1==2)
		{
			clrscr();
			openac();
		}
	}
	cout<<"\nTHANK YOU FOR USING CITIBANK!!!";
	getch();
}
void modify(ATM n)
{
	fstream fio("List.txt", ios::in|ios::out);
	ATM n1;
	long pos;
	while(fio)
	{
		pos=fio.tellg();
		fio.read((char*)&n1, sizeof(n1));
		if(n1.gacno()==n.gacno())
		{
			fio.seekg(pos);
			fio.write((char*)&n, sizeof(n));
			break;
		}
	}
	fio.close();
}
void openac()
{
	ATM n;
	float amt;
	ofstream fout("List.txt", ios::app);
	cout<<"Enter name: ";
	n.pname();
	while(1)
	{
		cout<<"Enter amout to deposit (must be in excess of Rs.40000) : Rs.";
		cin>>amt;
		if(amt>=40000)
		{
			n.pbal(amt);
			break;
		}
		else
			cout<<"Wrong input! Please reenter amount!\n";
	}
	randomize();
	n.pacno(random(90000000)+10000000);
	n.ppin(random(900)+100);
	cout<<"\nYour new acount ID : "<<n.gacno();
	cout<<"\nYour new 3-digit PIN : "<<n.gpin();
	getch();
	fout.write((char*)&n,sizeof(n));
	fout.close();
	return;
}
void closac(ATM n)
{
	ifstream fin("List.txt",ios::in);
	ofstream fout("Temp.txt",ios::out);
	ATM n1;
	while(fin)
	{
		fin.read((char*)&n1, sizeof(n1));
		if(n1.gacno()==n.gacno())
		{
			cout<<"\nThe following account is being deleted :";
			n1.balenq();
			getch();
		}
		else
			fout.write((char*)&n1,sizeof(n1));
	}
	fin.close();
	fout.close();
	remove("List.txt");
	rename("Temp.txt","List.txt");
}
int login()
{
	long id;
	char flag='n';
	cout<<"\nEnter account ID : ";
	cin>>id;
	ifstream fin("List.txt", ios::in);
	fin.seekg(0);
	while(fin)
	{
		fin.read((char*)&n2, sizeof(n2));
		if(n2.gacno()==id)
		{
			flag='y';
			break;
		}
	}
	if(flag=='n')
	{
		cout<<"\nAccount ID not found!";
		getch();
		fin.close();
		return 0;
	}
	int pcode, tries=0;
	while(tries<3)
	{
		cout<<"\nEnter 3-digit pin : ";
		cin>>pcode;
		if(n2.gpin()==pcode)
			break;
		else
		{
			cout<<"\nWrong input! Please try again.";
			tries++;
		}
	}
	fin.close();
	if(tries==3)
	{
		cout<<"\nNo more retries! Quitting!!!";
		getch();
		return 0;
	}
	return 1;
}
