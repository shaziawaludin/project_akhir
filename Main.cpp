#include <iostream>
#include <iomanip>
#include <windows.h>
#include <fstream>
#include <string.h>
#include <conio.h>
using namespace std;

void gotoxy ( short x, short y )
{
  COORD coord = {x, y};
  SetConsoleCursorPosition ( GetStdHandle ( STD_OUTPUT_HANDLE ), coord );
}

void delete_line(const char *file_name, int n) 
{ 
    ifstream is(file_name); //membuka file dalam read only mode;
    ofstream ofs; //membuka file dalam bentuk output mode
    ofs.open("temp.txt", ofstream::out); 
  
    // looping untuk membaca setiap char dalam file
    char c; 
    int line_no = 0; 
    while (is.get(c)) 
    {
        if (c == '\n') // kalau nemu karakter newline. 
        line_no++; 
  
        if (line_no != n)  // isi file yang ga dihapus 
            ofs << c; 
    } 
  
    ofs.close(); // closing output file 
    is.close();  // closing input file 
    remove(file_name);  // remove the original file 
    rename("temp.txt", file_name);  // rename the file 
} 
  
void input_line(const char *file_name,string inputdata){
	
	fstream ofs;
	ofs.open(file_name,ios::app);
	
	if(!ofs)
		cout << "File file tidak dapat dibuka";
	else{
		ofs << "\n" << inputdata;
	}
	
	ofs.close();
}
  
void accvalidation(const char *FILENAME, bool *found, int *line, string VALIDATION){
	ifstream USERACC(FILENAME);
	string acc;
	int loc = 21;
	do{
		USERACC.seekg(loc,ios::beg);
		getline(USERACC,acc);
		if(VALIDATION == acc)
		{
			(*found) = true;
		}
		loc += acc.length()+2;
		(*line)++;
	}while((*line) < 90 && !(*found));
}
  
bool search_acc(const char *FILENAME,string VALIDATION){
	string valtemp = VALIDATION;
	bool found = false;
	int line = 1;
	accvalidation(FILENAME,&found,&line,valtemp);
	return( found );
}  

int search_line(const char *FILENAME,string VALIDATION){
	string valtemp = VALIDATION;
	bool found = false;
	int line = 1;
	accvalidation(FILENAME,&found,&line,valtemp);
	return(line-1);
}  


void modify(){
	string userinput;
	string validation;
	
	cout << "data yang ingin diubah >>";
	cout << "\nUsername : ";
	getline(cin,userinput);
	validation += userinput + '#';
	cout << "\nPassword : ";
	getline(cin,userinput);
	validation += userinput;
			
	int found = search_acc("pass.txt",validation);
	int line = search_line("pass.txt",validation);
	string databaru;
	
	
	if(found && line >=1)
		{
			cout << "Username : ";
			getline(cin,userinput);
			databaru += userinput + '#';
			cout << "\nPassword : ";
			getline(cin,userinput);
			databaru += userinput;
		}
	
	delete_line("pass.txt",line);
	input_line("pass.txt",databaru);
}

void login(int *LOGIN_ACCESS){
	string userinput;
	string validation;
	
	bool found = false;
	int line = 0;
	do{
		validation.clear();
	system("color F0");
	cout << "\n\t\t\t\t" << "|____/|==>> LOGIN <<==|\\____|";
	cout << "\n\t\t\t\t" << "|                           |";
	cout << "\n\t\t\t\t" << "| Username :                |";
	cout << "\n\t\t\t\t" << "| Password :                |";
	cout << "\n\t\t\t\t" << "|___________________________|";
	cout << "\n\t\t\t\t" << "|    \\_________________/    |";

	cout << endl;
	getline(cin,userinput);
	validation += userinput + '#';
	getline(cin,userinput);
	validation += userinput;
	cout << validation;
	
	found = search_acc("pass.txt",validation);
	line = search_line("pass.txt",validation);
	if(!found){
		cout <<"\nUsername atau password tidak ditemukan";
		cout << endl;
		system("pause");
		system("cls");
	}
	}while(!found);
	
	if(found && line == 1)
	*LOGIN_ACCESS = 0;
	else if(found && line >1)
	*LOGIN_ACCESS = 1;
	
	system("cls");
}


void logo(){
	int matrix[33][32]={
		{48},{48},{48},{17,26,5},{17,26,5},{13,4,7,19,5},
		{9,6,2,4,7,15,5},{6,5,6,8,5,13,5},{4,4,5,4,6,4,5,11,5},
		{2,4,4,4,3,3,5,4,4,10,5},{2,4,3,4,4,4,3,4,4,11,5},
		{3,4,3,4,3,9,4,5,2,6,5},{4,5,3,3,2,7,4,5,6,4,5},
		{6,4,3,4,9,5,8,4,5},{7,5,9,7,8,7,5},{10,6,1,6,9,11,5},
		{13,4,10,16,5},{17,26,5},{17,26,5},{48},{48},{48},{48},
		{1,7,2,2,4,2,1,2,2,6,3,2,4,4,6},
		{1,8,1,3,2,3,1,2,2,2,3,2,2,2,3,2,2,2,5},
		{1,3,3,2,2,2,2,2,2,2,2,2,4,2,1,2,2,2,4,2,4},
		{1,3,3,3,2,4,3,2,2,2,4,2,1,2,2,2,4,2,4},
		{1,3,3,3,2,4,3,2,2,2,3,2,2,2,2,8,4},
		{1,3,3,3,3,2,4,2,2,6,3,2,2,2,4,2,4},{48},{48},{48}
	};
	
	int baris;
	int kolom;
	int ispace;
	int isi = 0;
	for(baris = 0; baris < 32; baris++){
		cout << "\t\t\t\t";
		for(ispace = 0 ; ispace < 30; ispace++)
		{
			for(kolom = 0; kolom < matrix[baris][ispace]; kolom++)
			{	
				if(ispace %2 == 0){
					cout << '8';
				}
				else 
					cout << '_';
				Sleep(5);
			}
			
			isi += matrix[baris][ispace];
			if(isi == 48)
			ispace = 31;
		}
		cout << endl;
	}
	
	Sleep(5);
	system("color 0b");
	Sleep(500);
	system("color 0a");
	Sleep(20);
	system("cls");
}

void exit(){
	char Excheck;
	do{
	system("cls");
	cout << "\nyakin ingin keluar? (y/n) : ";
	cin >> Excheck;
	}while(Excheck != 'n' && Excheck != 'n' &&
	Excheck != 'y' && Excheck != 'Y');
	if(Excheck == 'y' || Excheck == 'Y')
		exit(1);
	
	system("cls");
}


main(){
	int LOGIN_ACCESS = 0; //0 = admin, 1 = cashier
	
	//login(&LOGIN_ACCESS);
	system("color 0a");
	//logo();

	char MENU = 0;
	///main menu//
	if(LOGIN_ACCESS == 0){
		do{
			system("cls");
			cout << "\t\t\t\\\t\t  Home  \t\t/\n";
			cout << "\t\t\t \\" << setfill('-') << setw(38) << "-/";
			cout << setfill(' ');
			cout << "\n\t\t\t |\t" << setw(31) << left << "1. Penjualan" << '|';
			cout << "\n\t\t\t |\t" << setw(31) << "2. Transaksi" << '|';
			cout << "\n\t\t\t |\t" << setw(31) << "3. Data Barang" << '|';
			cout << "\n\t\t\t |\t" << setw(31) << "4. User management" << '|';
			cout << "\n\t\t\t |" << setw(38) << right<< '|';
			cout << "\n\t\t\t | " << setw(36) << left << "0. Exit" << '|';
			cout << "\n\t\t\t |" << setw(38) << right<< '|';;
			cout << "\n\t\t\t | " << setw(36) << left << "PILIH :> " << '|';
			cout << "\n\t\t\t/\\" << setfill('-') << setw(38) << right << "-/\\";
			gotoxy(36,9);
			cin >> MENU;
			
			switch(MENU){
				case('1'):{
					
				break;
				}
				case('2'):{
					
				break;
				}
				case('3'):{
					
				break;
				}
				case('4'):{
					
					char menu2;
					system("cls");
					cout << "USER MANAJEMENT";
					cout << "\n1. Input data baru";
					cout << "\n2. Edit data";
					cout << "\n3. Hapus data";
					cout << "\n4. Perlihatkan semua data";
					cout << "\n\nPilih > ";
					cin >> menu2;
					switch(menu2){
						case '1':{
							string userinput;
							string inputdata;
							cin.ignore();
							cout << "\nUsername : ";
							getline(cin,userinput);
							inputdata += userinput + '#';
							cout << "Password : ";
							getline(cin,userinput);
							inputdata += userinput;
							input_line("pass.txt",inputdata);
						break;
						}
							
						case '2':{
							cin.ignore();
							modify();
						break;
						}
						case '3':{
							string username,password;
							string inputdata;
							bool found;
							char agreement;
							int line;
							do{
								cin.ignore();
								inputdata.clear();
								cout << "\nUsername : ";
								getline(cin,username);
								inputdata += username + '#';
								cout << "Password : ";
								getline(cin,password);
								inputdata += password;
								cout << "apa kamu yakin menghapus :"
									 << username
									 << '?'
									 << "\n(y/n) :";
								cin >> agreement;
								if(agreement == 'y' || agreement == 'Y'){
									found = search_acc("pass.txt",inputdata);
									line = search_line("pass.txt",inputdata);
									if(found && line != 1){
										delete_line("pass.txt", line);
										cout << "\nSuccess!";
									}
									else if(found && line == 1)
										cout << "\nKamu tidak bisa menghapus admin";
										else
											cout << "\nAkun tidak ditemukan";
								}
							}while(!found);
						break;
						}
						case '4':{
						break;
						}
					}
				break;
				}
				case('0'):{
					exit();
				break;
				}
				
			}
			cout << endl;
			system("pause");
		}while(5);
	}
	else if(LOGIN_ACCESS == 1){
		do{
			cout << "\t\t\t\\\t\t  Home  \t\t/\n";
			cout << "\t\t\t \\" << setfill('-') << setw(38) << "-/";
			setfill(' ');
			cout << "\n\t\t\t\t1. Cashier";
			cout << "\n\t\t\t\t2. Detail Transaksi";
			cout << "\n\n\t\t\t0. Exit\n";
			cout << "\n\t\t\tPILIH :> ";
			cin >> MENU;
			
			switch(MENU){
				case('1'):{
					
				break;
				}
				case('2'):{
					
				break;
				}
				case('0'):{
					exit();
				break;
				}
			}
		}while(5);
	}
}
