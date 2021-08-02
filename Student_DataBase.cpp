#include<iostream>
#include<string.h>
#include<fstream>
#include <unistd.h>
#define T "\t\t"
#define search Search_Record(S,str,i)
using namespace std;
class student
{
	char HTno[12];
	char name[25];
	char branch[5];
	char mail[30];
	char phone[10];
	public:
		void Remove_Record()
		{
			delete this;
			cout<<"Record deleted, redirecting to Home";
		}
		void Update_Record()
		{
			cout<<"Enter all the details(including updated)\n";
			cin>>this;
		}
		friend void Display_All(student **C,int x)
		{
			for(int j=0;j<x;j++)
				cout<<C[j];
		}
		friend int Search_Record(student **C,char srch[],int y);
		friend ostream &operator<<(ostream &out,const student *C);
		friend istream &operator>>(istream &in,student *C);
		void update(student *C)
		{
			strcpy(HTno,C->HTno);
			strcpy(name,C->name);
			strcpy(branch,C->branch);
			strcpy(mail,C->mail);
			strcpy(phone,C->phone);
		}
};
int Search_Record(student **Q,char srch[],int y)
{
	for(int j=0;j<y;j++)
	{
		if(strcmp(Q[j]->HTno,srch)==0 || strcmp(Q[j]->name,srch)==0)
			return j;
	}
	return -1;
}
ostream &operator<<(ostream &out,const student *C)
{
	out<<C->HTno<<"\t\t"<<C->name<<"\t"<<C->branch<<"\t\t"<<C->mail<<"\t"<<C->phone<<endl;
	return out;
}
istream &operator>>(istream &in,student *C)
{
	fflush(stdin);
	cout<<"Hall Ticket No. ";
	in>>C->HTno;
	cout<<"Name : ";
	in>>C->name;
	cout<<"E-mail : ";
	in>>C->mail;
	cout<<"Branch : ";
	in>>C->branch;
	cout<<"Contact : ";
	in>>C->phone;
	while(strlen(C->phone)!=10)
	{
		cout<<"Enter Contact again";
		in>>C->phone;
	}
	return in;
}
void display()
{
	cout<<T<<"STUDENT DATABASE\n\n  1.Add a Record\n  2.Remove a Record\n  3.Search a Record\n  4.Display all Records\n  5.Exit";
	cout<<endl<<"\n  Enter a number ";
}
int main()
{
	student **S,P;
	S=new student*;
	static int i;
	ofstream fout;
	char k,str[20];
	for(int z=1;z!=0;z++)
	{
		system("CLS");
		display();
		cin>>k;
		system("CLS");
		switch(k)
		{
			case '1':{
						cout<<"\tEnter the Details of New Record\n";
						S[i]=new student;
						cin>>S[i];
						i++;
						P.update(S[i]);
						fout.open("Student_Data.dat",ios::app|ios::binary);
						fout.write((char *)&P,sizeof(student));
						cout<<"Record added succesfully, Redirecting to Home\n";
						sleep(2);
						fout.close();
						break;				
					}
			case '2':{
						cout<<"\tEnter any detail related to the record to be deleted\n";
						cin>>str;
						if(search==-1)
						{
							cout<<" No such record exists. Redirecting to Home\n";
							sleep(2);
							break;
						}
						else
						{
							cout<<S[search];
							cout<<"Are you sure you want to delete this record!!!(Y/N)";
							cin>>k;
							if(k=='Y')
							{
								S[search]->Remove_Record();
								i--;
							}
							fout.open("Student_Data.dat",ios::trunc|ios::binary);
							for(int j=0;j<i;j++)
								fout.write((char *)S[j],sizeof(student));
							fout.close();
							sleep(1);
							break;
						}
					}
			case '3':{
						cout<<"\tEnter any detail related to the record\n";
						cin>>str;
						if(search==-1)
						{
							cout<<" No such record exists. Returning back to Home page\n";
							sleep(1);
							break;
						}
						else
						{
							cout<<S[search];
							cout<<" To Update Press U  ";
							cin>>k;
							if(k=='U' || k=='u')
								S[search]->Update_Record();
							fout.open("Student_Data.dat",ios::trunc|ios::binary);
							for(int j=0;j<i;j++)
								fout.write((char *)S[j],sizeof(student));
							fout.close();
							break;
						}
					}
			case '4':{
						if(i==0)
						{
							cout<<"No Records found, redirecting to Home";
							sleep(1);
						}
						else
						{
							cout<<"\tSTUDENT RECORDS\n";
							Display_All(S,i);
							sleep(5);
						}
					}
			default:
				cout<<"Thanks\n\t\tProgrammed By P.Sri Chakra Raj ©";
		}
		if(k=='5')
			break;
	}
}
