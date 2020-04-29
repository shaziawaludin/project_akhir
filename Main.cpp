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
	
	cout << setw(4) << ' ' <<  "data yang Akan diubah >> \n";
	cout << setw(8) << ' ' << "Username : ";
	getline(cin,userinput);
	validation += userinput + '#';
	cout << endl;
	cout << setw(8) << ' ' << "Password : ";
	getline(cin,userinput);
	validation += userinput;
	cout << endl;
			
	int found = search_acc("pass.txt",validation);
	int line = search_line("pass.txt",validation);
	string databaru;
	
	
	if(found && line >1)
		{	cout << setfill('<') << setw(120)<<' ';
			cout << setfill(' ');
			cout << setw(4) << ' ' <<  "[DATA BARU] >> \n";
			cout << setw(8) << ' ' << "Username : ";
			getline(cin,userinput);
			databaru += userinput + '#';
			cout << setw(8) << ' ' << "Password : ";
			getline(cin,userinput);
			databaru += userinput;
			cout << "\n\nSUCCESS!\nData Berhasil Diubah";
		}
	else if(!found)
	{
		cout << setfill('>') << setw(120)<<' ';
		cout << setfill(' ');
		cout << "\nDATA TIDAK DITEMUKAN\n";
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
	gotoxy(44,3);
	getline(cin,userinput);
	validation += userinput + '#';
	gotoxy(44,4);
	getline(cin,userinput);
	validation += userinput;
	
	
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


void detailtransaksi(){
	cout << setfill(' ');
	cout << setw(4) << ' ' << "________          __         .__.__    ___________                                    __           .__ \n";
	cout << setw(4) << ' ' << "\\______ \\   _____/  |______  |__|  |   \\__    ___/___________    ____   ___________  |  | __  _____|__|\n";
	cout << setw(4) << ' ' << " |    |  \\_/ __ \\   __\\__  \\ |  |  |     |    |  \\_  __ \\__  \\  /    \\ /  ___/\\__  \\ |  |/ / /  ___/  |\n";
	cout << setw(4) << ' ' << " |    `   \\  ___/|  |  / __ \\|  |  |__   |    |   |  | \\// __ \\|   |  \\\\___ \\  / __ \\|    <  \\___ \\|  |\n";
	cout << setw(4) << ' ' << "/_______  /\\___  >__| (____  /__|____/   |____|   |__|  (____  /___|  /____  >(____  /__|_ \\/____  >__|\n";
	cout << setw(4) << ' ' << "        \\/     \\/          \\/                                \\/     \\/     \\/      \\/     \\/     \\/    \n";
	
	cout << setfill('=') << setw(120) << ' ' << endl;
	cout << setfill(' ');
	cout << "No Invoice : "<< endl;
	cout << "  Kode barang" << setw(5) << ' ' 
		 << "Nama Barang" <<  setw(10) << ' ' 
		 << "Harga Satuan" << setw(10) << ' ' 
		 << "Qty" << setw(5) << ' ' 
		 << "%Disc" << setw(10) << ' '
		 << "Rp. Disc" << setw(10) << ' ' 
		 << "Total"
		 << endl;
	cout << "\nTotal belanja : Rp. " << endl;
	/*cout << "  Kode barang" << setw(5) << ' ' 
		 << "Nama Barang" <<  setw(10) << ' ' 
		 << "Harga Satuan" << setw(10) << ' ' 
		 << "Qty" << setw(5) << ' ' 
		 << "%Disc" << setw(10) << ' '
		 << "Rp. Disc" << setw(10) << ' ' 
		 << "Total"
		 << endl;
	* */ // isi dengan data dari dalam file.
}

void inputbarang(){
cout << setfill(' ');
cout << setw(4) << ' ' << " _____                  _    ______                             \n";
cout << setw(4) << ' ' << "|_   _|                | |   | ___ \\                            \n";
cout << setw(4) << ' ' << "  | | _ __  _ __  _   _| |_  | |_/ / __ _ _ __ __ _ _ __   __ _ \n";
cout << setw(4) << ' ' << "  | || '_ \\| '_ \\| | | | __| | ___ \\/ _` | '__/ _` | '_ \\ / _` |\n";
cout << setw(4) << ' ' << " _| || | | | |_) | |_| | |_  | |_/ / (_| | | | (_| | | | | (_| |\n";
cout << setw(4) << ' ' << " \\___/_| |_| .__/ \\__,_|\\__| \\____/ \\__,_|_|  \\__,_|_| |_|\\__, |\n";
cout << setw(4) << ' ' << "           | |                                             __/ |\n";
cout << setw(4) << ' ' << "           |_|                                            |___/ 	\n";
cout << setfill('=') << setw(120) << ' ' << endl;
cout << setfill(' ');
cout << endl;
cout << setw(4) << ' ' << "Nama barang : \n"
	 << setw(4) << ' ' << "Harga Beli \t: \n"
	 << setw(4) << ' ' << "Harga Jual \t: \n"
	 << setw(4) << ' ' << "Stok \t: \n";
cout << endl;
cout << setfill('=') << setw(120) << ' ' << endl;
cout << setfill(' ');
}

void pilihcaribarang(bool *ulang){
	char pilihcari;
	cout << setw(4) << ' ' << "Cari barang" << endl
		 << setw(6) << ' ' << "1) Barcode\n"
		 << setw(6) << ' ' << "2) Nama\n";
	cout << setw(4) << ' ' << "Select your option : ";
	cin >> pilihcari;
	if(pilihcari == '1'){
		cout << setw(6) << ' ' << "Barcode : \n";
		*ulang = false;
	}
	else if(pilihcari == '2'){
		cout << setw(6) << ' ' << "Nama Barang : \n";
		*ulang = false;
	}
}
void editbarang(){
	
	cout << setfill(' ');
	bool ulang = true;
	do{
		system("cls");
	cout << setw(4) << ' ' << " _____    _ _ _    ______                             \n";
	cout << setw(4) << ' ' << "|  ___|  | (_) |   | ___ \\                            \n";
	cout << setw(4) << ' ' << "| |__  __| |_| |_  | |_/ / __ _ _ __ __ _ _ __   __ _ \n";
	cout << setw(4) << ' ' << "|  __|/ _` | | __| | ___ \\/ _` | '__/ _` | '_ \\ / _` |\n";
	cout << setw(4) << ' ' << "| |__| (_| | | |_  | |_/ / (_| | | | (_| | | | | (_| |\n";
	cout << setw(4) << ' ' << "\\____/\\__,_|_|\\__| \\____/ \\__,_|_|  \\__,_|_| |_|\\__, |\n";
	cout << setw(4) << ' ' << "                                                 __/ |\n";
	cout << setw(4) << ' ' << "                                                |___/ \n";
	cout << setfill('=') << setw(120) << ' ' << endl;
	cout << setfill(' ');
	cout << endl;
	pilihcaribarang(&ulang);
	}while(ulang);
	/*
	cout << "Input data baru : \n";
	cout << setw(4) << ' ' << "Nama barang : \n"
		 << setw(4) << ' ' << "Harga Beli \t: \n"
		 << setw(4) << ' ' << "Harga Jual \t: \n"
		 << setw(4) << ' ' << "Stok \t: \n";
		 * */ // taruh di bagian input data barang sesuai pilihan cari
}

void deletebarang(){
	
	cout << setfill(' ');
	bool ulang = true;
	do{
		system("cls");
	cout << setw(4) << ' ' << "______     _      _        ______                             \n";
	cout << setw(4) << ' ' << "|  _  \\   | |    | |       | ___ \\                            \n";
	cout << setw(4) << ' ' << "| | | |___| | ___| |_ ___  | |_/ / __ _ _ __ __ _ _ __   __ _ \n";
	cout << setw(4) << ' ' << "| | | / _ \\ |/ _ \\ __/ _ \\ | ___ \\/ _` | '__/ _` | '_ \\ / _` |\n";
	cout << setw(4) << ' ' << "| |/ /  __/ |  __/ ||  __/ | |_/ / (_| | | | (_| | | | | (_| |\n";
	cout << setw(4) << ' ' << "|___/ \\___|_|\\___|\\__\\___| \\____/ \\__,_|_|  \\__,_|_| |_|\\__, |\n";
	cout << setw(4) << ' ' << "                                                         __/ |\n";
	cout << setw(4) << ' ' << "                                                        |___/ \n";
	cout << setfill('=') << setw(120) << ' ' << endl;
	cout << setfill(' ');
	cout << endl;
	pilihcaribarang(&ulang);
	}while(ulang);
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
	
	login(&LOGIN_ACCESS);
	system("color 0a");
	logo();

	char MENU = 0;
	///main menu//
	if(LOGIN_ACCESS == 0){
		do{
			system("cls");
			cout << setfill(' ');
			cout << setw(10) << ' '<< " __  __   ___            .--.   _..._    " << endl;
			cout << setw(10) << ' '<< "|  |/  `.'   `.          |__| .'     '.      *           )"<< endl;
			cout << setw(10) << ' '<< "|   .-.  .-.   '         .--..   .-.   .   (  `       ( /("<< endl;
			cout << setw(10) << ' '<< "|  |  |  |  |  |    __   |  ||  '   '  |   )\\))(  (   )\\())   ("<< endl;
			cout << setw(10) << ' '<< "|  |  |  |  |  | .:--.'. |  ||  |   |  |  ((_)()\\ )\\ ((_)\\    )\\ "<< endl; 
			cout << setw(10) << ' '<< "|  |  |  |  |  |/ |   \\ ||  ||  |   |  |  (_()((_|(_) _((_)_ ((_) "<< endl;
			cout << setw(10) << ' '<< "|  |  |  |  |  |`' __ | ||  ||  |   |  |  |  \\/  | __| \\| | | | | "<< endl;
			cout << setw(10) << ' '<< "|__|  |__|  |__| .'.''| ||__||  |   |  |  | |\\/| | _|| .` | |_| | "<< endl;
			cout << setw(10) << ' '<< "                / /   | |_   |  |   |  |  |_|  |_|___|_|\\_|\\___/  "<< endl;
			cout << setw(10) << ' '<< "                \\ \\._,\\ '/   |  |   |  |  -----------------------"<< endl;
			cout << setw(10) << ' '<< "                 `--'  `'    \'--\'   \'--\' " << endl;

			cout << setfill('=') << setw(120) << ' ' << endl;
			cout << setfill(' ') << setw(60) 
				 << "Menu" << endl;
			cout << setfill('=') << setw(120) << ' ' << endl;

			cout << endl << setfill(' ');

			cout << setw(4) << ' ' << "Available Option : \n";
			cout << setw(8) << ' ' << "1) Penjualan \n";
			cout << setw(8) << ' ' << "2) Transaksi \n";
			cout << setw(8) << ' ' << "3) Data Barang \n";
			cout << setw(8) << ' ' << "4) User Management \n";
			cout << endl;
			cout << setw(8) << ' ' << "9) Back \n";
			cout << setw(8) << ' ' << "0) Exit \n";
			cout << "\n\nSelect Your option : ";

			cin >> MENU;
			
			switch(MENU){
				case('1'):{
					system("cls");
					cout << setfill(' ');
					
cout << setw(4) << ' ' << "__________                   __             .__                 \n"; 
cout << setw(4) << ' ' << "\\______   \\ ____   ____     |__|__ _______  |  | _____    ____  \n"; 
cout << setw(4) << ' ' << " |     ___// __ \\ /    \\    |  |  |  \\__  \\ |  | \\__  \\  /    \\ \n"; 
cout << setw(4) << ' ' << " |    |   \\  ___/|   |  \\   |  |  |  // __ \\|  |__/ __ \\|   |  \\ \n"; 
cout << setw(4) << ' ' << " |____|    \\___  >___|  /\\__|  |____/(____  /____(____  /___|  /	\n"; 
cout << setw(4) << ' ' << "               \\/     \\/\\______|          \\/          \\/     \\/ \n"; 
					
					cout << setfill('=') << setw(120) << ' ' << endl;
					cout << setfill(' ');
					cout << setw(4) << ' ' << "\nTOTAL KEUNTUNGAN : ";
					cout << "\n\n";
					cout << setfill('=') << setw(120) << ' ' << endl;
					cout << setfill(' ');
				break;
				}
				case('2'):{
					system("cls");
					detailtransaksi();
				break;
				}
				case('3'):{
					system("cls");
					cout << setfill(' ');
					char MENUbarang;
					cout << setw(4) << ' ' << "______      _         ______   \n";                          
					cout << setw(4) << ' ' << "|  _  \\    | |        | ___ \\ \n";                           
					cout << setw(4) << ' ' << "| | | |__ _| |_ __ _  | |_/ / __ _ _ __ __ _ _ __   __ _ \n";
					cout << setw(4) << ' ' << "| | | / _` | __/ _` | | ___ \\/ _` | '__/ _` | '_ \\ / _` | \n";
					cout << setw(4) << ' ' << "| |/ / (_| | || (_| | | |_/ / (_| | | | (_| | | | | (_| |\n";
					cout << setw(4) << ' ' << "|___/ \\__,_|\\__\\__,_| \\____/ \\__,_|_|  \\__,_|_| |_|\\__, |\n";
					cout << setw(4) << ' ' << "                                                    __/ |\n";
					cout << setw(4) << ' ' << "                                                   |___/ \n";
					cout << setfill('=') << setw(120) << ' ' << endl;
					cout << setfill(' ');
					cout << setw(4) << ' ' << "Available Option : \n";
					cout << setw(8) << ' ' << "1) Input Data Barang \n";
					cout << setw(8) << ' ' << "2) Edit Data Barang \n";
					cout << setw(8) << ' ' << "3) Hapus Data Barang\n";
					cout << setw(8) << ' ' << "4) Tampilkan Semua \n";
					cout << endl;
					cout << setw(8) << ' ' << "9) Back \n";
					cout << setw(8) << ' ' << "0) Exit \n";
					cout << "\n\nSelect Your option : ";
					cin >> MENUbarang;
					
					switch(MENUbarang){
						case'1':{
							system("cls");
							inputbarang();
						break;
						}
						
						case'2':{
							system("cls");
							editbarang();
						break;
						}
						
						case'3':{
							system("cls");
							deletebarang();
						break;
						}
						
						case'4':{
							cout << endl;
							cout << setfill('=') << setw(120) << ' ' << endl;
							cout << setfill(' ');
							cout << endl;
							cout << setw(8) << ' ' 
								 << "Barcode" << setw(3) << ' ' 
								 << "Nama Barang" << setw(10) << ' '
								 << "Harga Beli" << setw(7) << ' '
								 << "Harga Jual" << setw(7) << ' '
								 << "Stok" << setw(4) << ' '
								 << "Discount" << endl;
						break;
						}
						
						case'9':{
						break;
						}
						
						case'0':{
							exit(1);
						break;
						}
					}		 
				break;
				}
				case('4'):{
					
					char menu2;
					system("cls");
					cout << setfill(' ');
					cout << setw(4) << ' ' << " _   _                ___  ___                                                  _   \n"; 
					cout << setw(4) << ' ' << "| | | |               |  \\/  |                                                 | |  \n"; 
					cout << setw(4) << ' ' << "| | | |___  ___ _ __  | .  . | __ _ _ __   __ _  __ _  ___ _ __ ___   ___ _ __ | |_ \n"; 
					cout << setw(4) << ' ' << "| | | / __|/ _ \\ '__| | |\\/| |/ _` | '_ \\ / _` |/ _` |/ _ \\ '_ ` _ \\ / _ \\ '_ \\| __|\n"; 
					cout << setw(4) << ' ' << "| |_| \\__ \\  __/ |    | |  | | (_| | | | | (_| | (_| |  __/ | | | | |  __/ | | | |_ \n"; 
					cout << setw(4) << ' ' << " \\___/|___/\\___|_|    \\_|  |_/\\__,_|_| |_|\\__,_|\\__, |\\___|_| |_| |_|\\___|_| |_|\\__|\n"; 
					cout << setw(4) << ' ' << "                                                 __/ |                              \n"; 
					cout << setw(4) << ' ' << "                                                |___/                               \n"; 
					cout << setfill('=') << setw(120) << '=' << endl;
					cout << setfill(' ');					
					cout << endl;
					cout << setw(4) << ' ' << "Available Option : \n";
					cout << setw(8) << ' ' << "1) Input data baru\n";
					cout << setw(8) << ' ' << "2) Edit data\n";
					cout << setw(8) << ' ' << "3) Hapus data\n";
					cout << setw(8) << ' ' << "4) Perlihatkan semua data\n";
					cout << endl;
					cout << setw(8) << ' ' << "9) Back \n";
					cout << setw(8) << ' ' << "0) Exit \n\n";
					cout << setfill('=') << setw(120) << '=' << endl;
					cout << "\nSelect Your option : ";
					
					cin >> menu2;
					switch(menu2){
						case '1':{
							system("cls");
							cout << setfill(' ');	
							cout << setw(4) << ' ' << ".___                      __    ________          __          \n"; 
							cout << setw(4) << ' ' << "|   | ____ ______  __ ___/  |_  \\______ \\ _____ _/  |______   \n"; 
							cout << setw(4) << ' ' << "|   |/    \\\\____ \\|  |  \\   __\\  |    |  \\\\__  \\\\   __\\__  \\  \n"; 
							cout << setw(4) << ' ' << "|   |   |  \\  |_> >  |  /|  |    |    `   \\/ __ \\|  |  / __ \\_\n"; 
							cout << setw(4) << ' ' << "|___|___|  /   __/|____/ |__|   /_______  (____  /__| (____  /\n"; 
							cout << setw(4) << ' ' << "         \\/|__|                         \\/     \\/          \\/ \n"; 
														
							cout << setfill('=') << setw(120) << '=' << endl;
							cout << setfill(' ');	
							
							string userinput;
							string inputdata;
							cout << setw(4) << ' ' << "Data Baru >> \n";
							cout << setw(8) << ' ' << "Username : \n";
							cout << setw(8) << ' ' << "Password : \n";
							cout << endl;
							
							cout << setfill('=') << setw(120) << '=' << endl;
							cout << setfill(' ');	
							
							
							gotoxy(20,8);
							cin.ignore();
							getline(cin,userinput);
							inputdata += userinput + '#';
							gotoxy(20,9);
							
							getline(cin,userinput);
							inputdata += userinput;
							input_line("pass.txt",inputdata);
						break;
						}
							
						case '2':{
							cin.ignore();
							system("cls");
							cout << setfill(' ');
cout << setw(4) << ' ' << "___________    .___.__  __    ________          __          \n"; 
cout << setw(4) << ' ' << "\\_   _____/  __| _/|__|/  |_  \\______ \\ _____ _/  |______   \n"; 
cout << setw(4) << ' ' << " |    __)_  / __ | |  \\   __\\  |    |  \\\\__  \\\\   __\\__  \\  \n"; 
cout << setw(4) << ' ' << " |        \\/ /_/ | |  ||  |    |    `   \\/ __ \\|  |  / __ \\_\n"; 
cout << setw(4) << ' ' << "/_______  /\\____ | |__||__|   /_______  (____  /__| (____  /\n"; 
cout << setw(4) << ' ' << "        \\/      \\/                    \\/     \\/          \\/ \n"; 
							cout << setfill('=') << setw(120) << '=' << endl;
							cout << setfill(' ');	
							modify();
						break;
						}
						case '3':{
							string username,password;
							string inputdata;
							system("cls");
							cout << setfill(' ');
							
cout << setw(4) << ' ' << "________         .__          __           ________          __          \n"; 
cout << setw(4) << ' ' << "\\______ \\   ____ |  |   _____/  |_  ____   \\______ \\ _____ _/  |______   \n"; 
cout << setw(4) << ' ' << " |    |  \\_/ __ \\|  | _/ __ \\   __\\/ __ \\   |    |  \\\\__  \\\\   __\\__  \\  \n"; 
cout << setw(4) << ' ' << " |    `   \\  ___/|  |_\\  ___/|  | \\  ___/   |    `   \\/ __ \\|  |  / __ \\_\n"; 
cout << setw(4) << ' ' << "/_______  /\\___  >____/\\___  >__|  \\___  > /_______  (____  /__| (____  /\n"; 
cout << setw(4) << ' ' << "        \\/     \\/          \\/          \\/          \\/     \\/          \\/ \n"; 
        
							cout << setfill('=') << setw(120) << '=' << endl;
							cout << setfill(' ');	
							bool found;
							char agreement;
							int line;
								cin.ignore();
								inputdata.clear();
								cout << setw(4) << ' ' <<  "Data Yang Akan Dihapus >> \n";
								cout << setw(8) << ' ' << "Username : ";
								getline(cin,username);
								inputdata += username + '#';
								cout << setw(8) << ' ' << "Password : ";
								getline(cin,password);
								inputdata += password;
								cout << setw(4) << ' ' << "Apa Kamu Yakin Akan Menghapus Data  "
									 << username
									 << '?'
									 << setw(4) << ' ' 
									 << "\n(y/n) :";
								cin >> agreement;
								if(agreement == 'y' || agreement == 'Y'){
									found = search_acc("pass.txt",inputdata);
									line = search_line("pass.txt",inputdata);
								}
								if(found && line != 1){
										delete_line("pass.txt", line);
										cout << "\nSuccess!";
								}
								else if(found && line == 1){
										cout << "\nKamu tidak bisa menghapus admin";
										}
										else{
											cout << "\nAkun tidak ditemukan";
											cout << "\nAtau Password salah";
										}
								
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
			system("cls");
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
					system("cls");
					
					cout << "\t __  __     ______     ______     __     ______    \n";
					cout << "\t/\\ \\/ /    /\\  __ \\   /\\  ___\\   /\\ \\   /\\  == \\\n";   
					cout << "\t\\ \\  _\"-.  \\ \\  __ \\  \\ \\___  \\  \\ \\ \\  \\ \\  __< \n";  
					cout << "\t \\ \\_\\ \\_\\  \\ \\_\\ \\_\\  \\/\\_____\\  \\ \\_\\  \\ \\_\\ \\_\\ \n";
					cout << "\t  \\/_/\\/_/   \\/_/\\/_/   \\/_____/   \\/_/   \\/_/ /_/\n";
					cout << "\n\n";
					cout << "  No.Invoice : " << endl;
					cout << "  Total Harus Bayar : " << endl;
					cout << setfill('=') << setw(120) << ' ' << endl;
					cout << setfill(' ');
					cout << "\n\tBarcode\t\t: ";
					
					cout << "\n\tNama Produk\t: ";
					cout << "\n\tHarga satuan\t: ";
					cout << "\n\tStok\t\t: ";
					
					cout << "\n\tQty \t\t: ";
					cout << "\n\tDiscount\t: ";
					cout << "\n\n\t\tTambah >    Hapus <    Selesai >>";
					
					cout << "\n\t\tBarcode : ";
					
					
					
					cout << endl;
					cout << setfill('=') << setw(120) << ' ' << endl;
					cout << setfill(' ');
					
					cout << " Barang Dibeli : " << endl;
					cout << "  Kode barang" << setw(5) << ' ' 
						 << "Nama Barang" <<  setw(10) << ' ' 
						 << "Harga Satuan" << setw(10) << ' ' 
						 << "Qty" << setw(5) << ' ' 
						 << "%Disc" << setw(10) << ' '
						 << "Rp. Disc" << setw(10) << ' ' 
						 << "Total"
						 << endl;
					
					cout << "\n\tBayar \t: Rp. ";
					cout << "\n\tKembali\t: Rp. ";
					cout << "\n\tX Batal     > Lanjut";
					cout << endl;
					system("pause");
				break;
				}
				case('2'):{
					system("cls");
					detailtransaksi();
					cout << endl;	
					system("pause");
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
