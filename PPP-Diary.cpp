/*
 *  Created on: 13-Oct-2017
 *      Author: amogh
 */
#include<iostream>
#include<fstream>
#include<string>
#include<unistd.h>
using namespace std;

class person
{
	string username, password, data;
public:
	string filename;
	void getdata()
	{
		cout<<"\nEnter Username: ";
		getline(cin,this->username);
		cout<<"Enter new Password: ";
		getline(cin,this->password);
		cout<<"Enter data (Insert @ in the end):\n";
		getline(cin,data,'@');
		this->filename=this->username+".dat";
	}
	void adddata(string data)
	{
		this->data=this->data+"\n"+data;
	}
	void show()
	{
		cout<<"\n ~~~~~ "<<username<<" ~~~~~~\n";
		cout<<this->data;
		cout<<"\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
		cout<<endl;
	}
	friend bool checkpass(person);
};

bool checkpass(person p)
{
	string pass;
	for(int i=1;i<=3;i++)
	{
		cout<<" ~ Attempt "<<i<<" ~";
		cout<<"\nEnter Password: ";
		getline(cin,pass);
		if(p.password==pass)
		{
			return 1;
		}
	}
	cout<<"\n 3 Failed attempts, Please try again later.";
	return 0;
}

int menu()             // Displays Menu and returns choice
{
	int ch;
	cout<<"\n        --- What would you like to do? ---";
	cout<<"\n\t1. Add New Person.";
	cout<<"\n\t2. Erase your data.";
	cout<<"\n\t3. Add your data.";
	cout<<"\n\t4. Show your data.";
	cout<<"\n\t5. Exit the Program.";
	cout<<"\n\tYour Choice: ";
	cin>>ch;
	return ch;
}


int main()
{
	int ch;
	string username,newdata,usernm;
	person P;
	fstream file,file2;
	cout<<"=============================================================\n";
	cout<<"            PASSWORD PROTECTED PERSONAL DIARY\n";
	cout<<"=============================================================\n\n";
	do
	{
		string usernme;
		ch=menu();
		switch (ch)
		{
		case 1:
			cout<<endl;
			cin.ignore();
			P.getdata();
			file.open(P.filename.c_str(), ios::binary |ios::out);
			file.write(reinterpret_cast<char*>(&P),sizeof(P));
			file.close();
			break;

		case 2:
			cout<<"\nEnter username: ";
			cin.ignore();
			getline(cin,username);
			username=username+".dat";
			file.open(username.c_str(), ios::binary | ios::in);
			if(file.fail())
			{
				cout<<"\n Error, No Username.\n";
				break;
			}
			file.read(reinterpret_cast <char*> (&P) ,sizeof(P));
			if(checkpass(P)==1)
			{
				file.close();
				remove(username.c_str());
				break;
			}
			file.close();
			cout<<"\nFILE DELETED!\n";
			break;

		case 3:
			cout<<"\nEnter Username: ";
			cin.ignore();
			getline(cin,username);
			username=username+".dat";
			file.open(username.c_str(), ios::binary |ios::out);
			if(file.fail())
			{
				cout<<"\n Error, No Username.\n";
				break;
			}
			file.read(reinterpret_cast <char*> (&P), sizeof(P));
			if(checkpass(P)==1)
			{
				file.close();
				cout<<"\nEnter new Data (Insert @ at the end):\n";
				getline(cin,newdata,'@');
				P.adddata(newdata);
				file.open(username.c_str(), ios::binary | ios::trunc | ios::out);
				file.write(reinterpret_cast <char*> (&P), sizeof(P));
				file.close();
				break;
			}
			file.close();
			break;

		case 4:
			cout<<"\nEnter Username: ";
			cout<<"HELLO";

			cin.ignore();
			getline(cin,usernme);

			cout<<"TEST";
			usernme=usernme+".dat";

			file.open(usernme.c_str(), ios::binary | ios::in);
			if(file.fail())
			{
				cout<<"\n Error, No username.\n";
				file.close();
				break;
			}
			file.read(reinterpret_cast <char*> (&P), sizeof(P));
			if(checkpass(P)==1)
			{
				P.show();
				file.close();
				break;
			}
			file.close();
			break;

		case 5:
			break;
		}
	} while(ch!=5);
	cout<<"\n\n======================== THANK YOU ==============================";
	return 0;
}




