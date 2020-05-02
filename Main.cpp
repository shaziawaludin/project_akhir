#include <iostream>
#include <iomanip>
#include <windows.h>
#include <fstream>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include <sstream>
using namespace std;

struct barang{
	string nama;
	long int hargabeli, hargajual, discount;
	int stok;
	string barcode;
	int qty;
};

struct transaksi{
	string c_invoice;
	barang dibeli[300];
	
};
barang detailbarang[2];
barang BarangSorted[1000];
string sortingtemp[1000];
transaksi detailt[2];
transaksi transaksitemp[10000];

void gotoxy ( short x, short y )
{
  COORD coord = {x, y};
  SetConsoleCursorPosition ( GetStdHandle ( STD_OUTPUT_HANDLE ), coord );
}

void delete_line(const char *FILE_NAME, int n) 
{ 
    ifstream is(FILE_NAME); //membuka file dalam read only mode;
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
    remove(FILE_NAME);  // remove the original file 
    rename("temp.txt", FILE_NAME);  // rename the file 
} 
  
void input_line(const char *file_name,string inputdata){
	
	fstream ofs;
	ofs.open(file_name,ios::app);
	
	if(!ofs)
		cout << "File tidak dapat dibuka";
	else{
		ofs << "\n" << inputdata;
	}
	cout << "\n\nSUCCESS!\nData Berhasil Diubah";
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

int carilineinvoice(){
	char c;
	int akhir=0;
	ifstream ifs;
	ifs.open("datatransaksi.txt");
	while(ifs.get(c)){
		if(c == '*')
			akhir++;
	}
	ifs.close();
	return(akhir);
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
	cout << endl;
	int akhir;
	akhir = carilineinvoice();
	ifstream fs;
	fs.open("datatransaksi.txt",ios::in);
	if(fs){
		int totalbayar=0;
		int i=0;
		int j=0;
		char c;
		fs.seekg(0,ios::beg);
		while(!fs.eof() && i < akhir){
			int indeks = i;
			if(indeks == i){
				fs >> transaksitemp[1].c_invoice;
				indeks++;
				cout << "No Invoice : "<< transaksitemp[1].c_invoice << endl;
			totalbayar = 0;
			cout << "  Kode barang" << setw(5) << ' ' 
			 << "Nama Barang" <<  setw(10) << ' ' 
			 << "Harga Satuan" << setw(10) << ' ' 
			 << "Qty" << setw(5) << ' ' 
			 << "%Disc" << setw(10) << ' '
			 << "Rp. Disc" << setw(10) << ' ' 
			 << "Total"
			 << endl;
			 
			do{
			fs >> transaksitemp[1].dibeli[j].barcode 
			>> transaksitemp[1].dibeli[j].nama  
			>> transaksitemp[1].dibeli[j].hargabeli
			>> transaksitemp[1].dibeli[j].hargajual 
			>> transaksitemp[1].dibeli[j].qty 
			>> c;
			j++;
			totalbayar += transaksitemp[1].dibeli[j-1].qty * 
				  transaksitemp[1].dibeli[j-1].hargajual;
				  
			 cout << "  " << transaksitemp[1].dibeli[j-1].barcode << setw(7) << ' '
				  << setw(20) << left << transaksitemp[1].dibeli[j-1].nama 
				  << setw(13) << right << transaksitemp[1].dibeli[j-1].hargajual
				  << setw(13) << transaksitemp[1].dibeli[j-1].qty
				  << setw(10) << 0
				  << setw(18) << 0
				  << setw(15) << transaksitemp[1].dibeli[j-1].qty * 
				  transaksitemp[1].dibeli[j-1].hargajual;
			
			
			cout << endl;
			}while(c == '#');
		}
		cout << "\n\nTotal bayar \t: " 
				 << totalbayar << endl; 		
			cout << setfill('=') 
				 << setw(30) << ' ';
			cout << setfill(' ');
		cout << "\n\n";;
			i++; 
		}
		i = 10, j=10;
			
		fs.close();
	
	}
	else
		cout << "\nData belum ada!";
		
	cout << endl;
	system("pause");
	
}

void selection(int arr[], int banyak){
	int selected;
	for(int i=0; i < banyak-1; i++){
		selected = i;
		for(int j = i+1; j < banyak; j++)
			if(arr[selected] > arr[j])
				selected = j;
		
		int urut = arr[selected]; 
		
		while( selected > i)
		{
			arr[selected] = arr[selected-1];
			selected--;
		}
		
		arr[i] = urut; 
	}
	
}


void sortbarcode(){
	ifstream ifs;
	ifs.open("databarang.txt");
	int i=0;
	int selected=0;
	int temp1, temp2;
	string barcode1,barcode2;
	if(ifs){
		while(ifs.peek() != EOF){
				ifs >> BarangSorted[i].barcode >>
				BarangSorted[i].nama>>
				BarangSorted[i].hargabeli>>
				BarangSorted[i].hargajual>>
				BarangSorted[i].stok;
			barcode1 = BarangSorted[i].barcode;
			barcode1 = barcode1.substr(2,7);
			sortingtemp[i] = barcode1;
			i++;
		}
		
		for(int index1 = 0; index1 < i-1; index1++){
			selected = index1;
			for(int index2 = index1 + 1; index2 < i ; index2++){
				barcode1 = BarangSorted[selected].barcode;
				barcode1 = barcode1.substr(2,7);
				stringstream toint1(barcode1);
				toint1 >> temp1;
				barcode2 = BarangSorted[index2].barcode;
				barcode2 = barcode2.substr(2,7);
				stringstream toint2(barcode2);
				toint2 >> temp2;
				if(temp1 > temp2)
					selected = index2;
				detailbarang[1].barcode = BarangSorted[selected].barcode;
				detailbarang[1].nama = BarangSorted[selected].nama;
				detailbarang[1].hargabeli = BarangSorted[selected].hargabeli;
				detailbarang[1].hargajual = BarangSorted[selected].hargajual;
				detailbarang[1].stok = BarangSorted[selected].stok;
				
				while(selected > index1){
					BarangSorted[selected].barcode = BarangSorted[selected-1].barcode;
					BarangSorted[selected].nama = BarangSorted[selected-1].nama;
					BarangSorted[selected].hargabeli = BarangSorted[selected-1].hargabeli;
					BarangSorted[selected].hargajual = BarangSorted[selected-1].hargajual;
					BarangSorted[selected].stok = BarangSorted[selected-1].stok;
					selected--;
				}
				BarangSorted[index1].barcode = detailbarang[1].barcode;
				BarangSorted[index1].nama = detailbarang[1].nama;
				BarangSorted[index1].hargabeli= detailbarang[1].hargabeli;
				BarangSorted[index1].hargajual = detailbarang[1].hargajual;
				BarangSorted[index1].stok = detailbarang[1].stok;
			}
		}
		ofstream ofs;
		ofs.open("temp.txt",ios::out);
			if(ofs){
				int z = 0;
				i--;
				while(i >=0 ){
					ofs << endl
					<< BarangSorted[z].barcode << ' '
					<< left << setw(25) << BarangSorted[z].nama
					<< right << setw(15) << BarangSorted[z].hargabeli
					<< setw(15) << BarangSorted[z].hargajual
					<< setw(10) << BarangSorted[z].stok;
					i--;
					z++;
				}
				
			}
		ofs.close();
	
	ifs.close();
	remove("databarang.txt");  // remove the original file 
    rename("temp.txt", "databarang.txt");  // rename the file 
    }
	
}


void showdatabarang(){
	cout << detailbarang[1].barcode << ' '
	 << left << setw(25) << detailbarang[1].nama
	 << right << setw(15) << detailbarang[1].hargabeli
	 << setw(15) << detailbarang[1].hargajual
	 << setw(10) << detailbarang[1].stok;
	}

bool checkspasi(){
	int spasi=1;
	for(int i=0; detailbarang[0].nama[i]; i++)
	{
		if(isspace(detailbarang[0].nama[i]))
		{
			spasi++;
		}   
    }
    if(spasi == 1 && detailbarang[0].nama.length() < 25)
		return(true);
	else 
		return(false);
}

void caribarang_barcode(int *LINE,bool *FOUND){ 
	ifstream ifs;
	bool cari=false;
	ifs.open("databarang.txt");
	if(!ifs)
		cout << "\nFile gagal dibuka";
	else {
		while(!ifs.eof() && !(cari)){
				ifs >> detailbarang[1].barcode >> 
				detailbarang[1].nama >> 
				detailbarang[1].hargabeli >> 
				detailbarang[1].hargajual >>
				detailbarang[1].stok;
				
			if(detailbarang[0].barcode == detailbarang[1].barcode){
				*FOUND = true;
				cari = true;
			}
			else{
				*FOUND = false;
				cari = false;
			}
			*LINE +=1;
		}
	}
}

void caribarang_nama(int *LINE,bool *FOUND){ 
	ifstream ifs;
	bool cari=false;
	ifs.open("databarang.txt");
	if(!ifs)
		cout << "\nFile gagal dibuka";
	else {
		while(!ifs.eof() && !(cari)){
				ifs >> detailbarang[1].barcode >> 
				detailbarang[1].nama >> 
				detailbarang[1].hargabeli >> 
				detailbarang[1].hargajual >>
				detailbarang[1].stok;
				
			if(detailbarang[0].nama == detailbarang[1].nama){
				*FOUND = true;
				cari = true;
			}
			else{
				
				*FOUND = false;
				cari = false;
			}
			(*LINE)++;
		}
	}
}

void inputbarang(bool *ULANG, int *y,bool BARU){
	bool found = *ULANG;
	int line = 0;
	//buat barcode
	string BarcodeTerakhir;
	int BarcodeInt;
	
		//cari barcode terakhir
		ofstream ofs;
		ofs.open("databarang.txt",ios::app);
		ofs.close();
		
		ifstream ifs;
		ifs.open("databarang.txt");
		if(BARU){
			//untuk buat barcode
			while(!ifs.eof()){
				ifs >> detailbarang[1].barcode >> 
				detailbarang[1].nama >> 
				detailbarang[1].hargabeli >> 
				detailbarang[1].hargajual >>
				detailbarang[1].stok;
				
			}
			if(detailbarang[1].barcode.size() == 0)
				{ 
					BarcodeTerakhir = "SA1000000";
				}
			else
				BarcodeTerakhir = detailbarang[1].barcode;
				cout << "\nBarcode Terakhir : \n";
				cout << BarcodeTerakhir;
			BarcodeTerakhir = BarcodeTerakhir.substr(2,7);
			stringstream toint(BarcodeTerakhir);
			toint >> BarcodeInt;
			BarcodeInt = BarcodeInt + 1;
			stringstream tostring;
			tostring << BarcodeInt;
			detailbarang[0].barcode = "SA" + tostring.str();
		}
				ifs.close();
	
	//mencari data yang sama
	caribarang_nama(&line, &found);
	//mencari data yang sama
	if(!found)
	{
		ofstream ofs;
		ofs.open("databarang.txt",ios::app);
		ofs	<< endl
			<< detailbarang[0].barcode << ' '
			<< left << setw(25) << detailbarang[0].nama
			<< right << setw(15) << detailbarang[0].hargabeli
			<< setw(15) << detailbarang[0].hargajual
			<< setw(10) << detailbarang[0].stok;
			
		cout << "\nData Berhasil diinput\n";
		*ULANG = false;
		cout << endl;
		ofs.close();
	}
	else{
		cout << "\nGAGAL DIINPUT, ADA DATA SAMA\n";
		*ULANG = found;
		(*y) +=2;
	}
}
	

void inputbarangmenu(){
cout << setfill(' ');
int y = 10;
bool ULANG = false;
do{ 
	
	do{
		
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

		gotoxy(18,y);
		cin.ignore();
		getline(cin, detailbarang[0].nama);
		gotoxy(18,y+1);
		cin >> detailbarang[0].hargabeli;
		gotoxy(18,y+2);
		cin >> detailbarang[0].hargajual;
		gotoxy(18,y+3);
		cin >> detailbarang[0].stok;
		system("cls");
		if(!checkspasi()){
			cout << "Nama barang tidak boleh memiliki spasi\n";
			y++;
		}
	}while(!checkspasi());
		y = 10;
		inputbarang(&ULANG, &y,true);
}while(ULANG);
	
}

void editbarang(){
	
	cout << setfill(' ');
	int line = 0;
	int y = 0;
	bool found = false , delvar = true;
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
	cout << endl << endl;
	cout << setw(6) << ' ' << "Barcode : ";
	cin >> detailbarang[0].barcode;
	caribarang_barcode(&line,&found);
	if(found){
		cout << setw(4) << ' ' << "Nama barang : "; 
		cin.ignore();
		getline(cin, detailbarang[0].nama);
		cout << endl << setw(4) << ' ' << "Harga Beli \t: ";
		cin >> detailbarang[0].hargabeli;
		cout << endl << setw(4) << ' ' << "Harga Jual \t: ";
		cin >> detailbarang[0].hargajual;
		cout << endl << setw(4) << ' ' << "Stok \t: ";
		cin >> detailbarang[0].stok;
		cout << endl;
		
		inputbarang(&delvar,&y, false);
		if(!delvar){
			delete_line("databarang.txt",line);
			cout << "\nData Sebelumnya berhasil diubah";
		}
	}
	sortbarcode();
	cout << endl;
	system("pause");
}

void deletebarang(){
	cout << setfill(' ');
	//bool ulang = true;
	int line = 0;
	bool found = false;
	char agreement;
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
		cout << endl << endl;
		cout << setw(6) << ' ' << "Barcode : ";
		cin >> detailbarang[0].barcode;
		caribarang_barcode(&line,&found);
		if(found){
		cout << "\nHapus Barang : \n";
		cout << "Barcode" << setw(3) << ' ' 
			 << "Nama Barang" << setw(19) <<' ' 
			 << "Harga Beli" << setw(5) << ' ' 
			 << "Harga Jual" << setw(4) << ' ' 
			 << "Jumlah" << endl;
		showdatabarang();
		cout << endl;
		do{
			cout << " ? (y/n) : ";
			cin >> agreement;
			if(agreement == 'y' || agreement == 'Y'){
				delete_line("databarang.txt",line);
				sortbarcode();
				cout << "\nDATA BERHASIL DIHAPUS\n";
			}
		}while(agreement != 'n' && agreement != 'N' && agreement != 'y' && agreement != 'Y');
		do{
			cout << "\nUlang ? (y/n) : ";
			cin >> agreement;
		}while(agreement != 'n' && agreement != 'N' && agreement != 'y' && agreement != 'Y');
		}
		else 
			cout << "Barang tidak ada";
			cout << endl;
			system("pause");
	}while(agreement == 'y' ||agreement == 'Y');
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



void buatcinvoice(){
	int akhir, invoiceInt;
	akhir = carilineinvoice();
	string invoiceterakhir;
	//untuk membuat file pertama kali
	ofstream ofs;
	ofs.open("datatransaksi.txt",ios::app);
	ofs.close();
	//untuk membuat file pertama kali
	
	ifstream fs;
	fs.open("datatransaksi.txt",ios::in);
	int i=0;
	int j=0;
	char c;
	fs.seekg(0,ios::beg);
	while(!fs.eof() && i < akhir){
		int indeks = i;
		if(indeks == i){
			fs >> transaksitemp[indeks].c_invoice;
			indeks++;
		do{
		fs >> transaksitemp[i].dibeli[j].barcode 
		>> transaksitemp[i].dibeli[j].nama  
		>> transaksitemp[i].dibeli[j].hargabeli
		>> transaksitemp[i].dibeli[j].hargajual 
		>> transaksitemp[i].dibeli[j].qty 
		>> c;
		j++;
		}while(c == '#');
	}
		i++; 
	}
	if(i == 0)
		invoiceterakhir = "HA1000000";
	else
		invoiceterakhir = transaksitemp[i-1].c_invoice;
		
		invoiceterakhir = invoiceterakhir.substr(2,7);
		stringstream toint(invoiceterakhir);
		toint >> invoiceInt;
		invoiceInt = invoiceInt + 1;
		stringstream tostring;
		tostring << invoiceInt;
		detailt[0].c_invoice = "HA" + tostring.str();
	fs.close();
}

void kasir(){
int line = 0,qty = 0, discount =0;
bool found = false , update = false;

string tambah;
char lanjut;
int banyakbarang = 0,updateint = 0;
long int bayar,kembali,totalbayar=0;
buatcinvoice();
do{
	do{
		do{
			if(update)
				updateint = 1;
			if(updateint == 1)
				update = false;
			system("cls");
			cout << "\t __  __     ______     ______     __     ______    \n";
			cout << "\t/\\ \\/ /    /\\  __ \\   /\\  ___\\   /\\ \\   /\\  == \\\n";   
			cout << "\t\\ \\  _\"-.  \\ \\  __ \\  \\ \\___  \\  \\ \\ \\  \\ \\  __< \n";  
			cout << "\t \\ \\_\\ \\_\\  \\ \\_\\ \\_\\  \\/\\_____\\  \\ \\_\\  \\ \\_\\ \\_\\ \n";
			cout << "\t  \\/_/\\/_/   \\/_/\\/_/   \\/_____/   \\/_/   \\/_/ /_/\n";
			cout << "\n\n";
			cout << "  No.Invoice : " << detailt[0].c_invoice<< endl;
			cout << "  Total Harus Bayar : Rp. " << totalbayar << endl;
			cout << setfill('=') << setw(120) << ' ' << endl;
			cout << setfill(' ');
			cout << endl;


			cout << " Barang Dibeli : " << endl;
			cout << "  Kode barang" << setw(5) << ' ' 
				 << "Nama Barang" <<  setw(11) << ' ' 
				 << "Harga Satuan" << setw(10) << ' ' 
				 << "Qty" << setw(5) << ' ' 
				 << "%Disc" << setw(11) << ' '
				 << "Rp. Disc" << setw(10) << ' ' 
				 << "Total"
				 << endl;
			for(int j =0; j <= banyakbarang-1; j++){
				cout << "  "
					<< detailt[0].dibeli[j].barcode << setw(7) << ' '
					<< setw(19) << left << detailt[0].dibeli[j].nama
					<< setw(15) << right << detailt[0].dibeli[j].hargajual
					<< setw(12) << detailt[0].dibeli[j].qty
					<< setw(10) << 0
					<< setw(20) << 0
					<< setw(15) << (detailt[0].dibeli[j].hargajual * detailt[0].dibeli[j].qty)
					<< endl;
			}
			cout << endl;
			cout << setfill('=') << setw(120) << ' ' << endl;
			cout << setfill(' ');
			if(updateint != 1){
				cout << "\n\tBarcode\t\t: ";
				cin >> detailbarang[0].barcode;
				caribarang_barcode(&line, &found);
				cout << "\n\tBarcode" << setw(3) << ' ' 
					 << "Nama Barang" << setw(19) <<' ' 
					 << "Harga Beli" << setw(5) << ' ' 
					 << "Harga Jual" << setw(4) << ' ' 
					 << "Jumlah";
				cout << "\n\t";
				cout << setfill('-') << setw(81) << ' ';
				cout << setfill(' ');
				cout << "\n\t";
				if(found){
					showdatabarang();
					cout << "\n\n\tQty \t\t: ";
					cin >> qty;
				}
				else
					cout << "Barang Tidak ada";

			cout << "\n\n";
			//cout << "\n\tDiscount\t: ";
				if(found){
					do{
						cout << "\tTambah >    Hapus <    Selesai >>\n";
						cout << "\t";
						cin >> tambah;
					}while(tambah != ">" && tambah != "<" && tambah != ">>");
							detailt[0].dibeli[banyakbarang].barcode = detailbarang[1].barcode;
							detailt[0].dibeli[banyakbarang].nama = detailbarang[1].nama;
							detailt[0].dibeli[banyakbarang].hargabeli = detailbarang[1].hargabeli;
							detailt[0].dibeli[banyakbarang].hargajual = detailbarang[1].hargajual;
							detailt[0].dibeli[banyakbarang].stok = detailbarang[1].stok;
							detailt[0].dibeli[banyakbarang].qty = qty;
							totalbayar += (detailt[0].dibeli[banyakbarang].hargajual*qty);
							banyakbarang++;
							
						if(tambah == "<"){
							banyakbarang--;
							totalbayar -= (detailt[0].dibeli[banyakbarang].hargajual*qty);
							
						}
					}
				else{
					do{
					cout << "\tUlang <    Selesai >>\n";
						cout << "\t";
						cin >> tambah;
					}while(tambah != "<" && tambah != ">>");
					
				}
				
				if(tambah == ">>") 
					update = true;
					else update = false;
			}
		}while(updateint == 0);
		updateint = 0;
	}while(tambah == ">" || tambah == "<");
do{
	cout << "\n\t< Batal     > Lanjut bayar";
	cout << "\n\t";
	cin >> lanjut;
}while(lanjut != '<' && lanjut != '>');
	
	if(lanjut =='<'){
		banyakbarang = 0;
		totalbayar = 0;
	}

}while(lanjut == '<');
	
	if(lanjut == '>' && (found || banyakbarang > 0)){
		cout << "\n\tBAYAR \t: Rp. ";
		cin >> bayar;
		kembali = bayar - totalbayar;
		if(kembali >=0){
			cout << "\n\tKEMBALI\t: Rp. " << kembali;
			
			ofstream ofs;
			ofs.open("datatransaksi.txt",ios::app);
				ofs << endl 
					<< detailt[0].c_invoice << ' ';
				
				for(int j = 0; j < banyakbarang; j++){
				ofs << detailt[0].dibeli[j].barcode << ' '
					<< detailt[0].dibeli[j].nama << ' '
					<< detailt[0].dibeli[j].hargabeli << ' '
					<< detailt[0].dibeli[j].hargajual << ' '
					<< detailt[0].dibeli[j].qty << ' ';
					if(j == banyakbarang-1)
						ofs << '*';
					else 
						ofs << '#'<< ' ';
				}
			ofs.close();
			
			
			cout << "\n\nTERIMAKASIH! TRANSAKSI SUKSES";
		}
		else{
			cout << "\nTRANSAKSI GAGAL! UANG TIDAK MENCUKUPI";
		}
	}
		
}

int penjualan(){
	int akhir;
	int untung;
	akhir = carilineinvoice();
	ifstream fs;
	fs.open("datatransaksi.txt",ios::in);
	if(fs){
		int i=0;
		int j=0;
		char c;
		fs.seekg(0,ios::beg);
		while(!fs.eof() && i < akhir){
			int indeks = i;
			if(indeks == i){
				fs >> transaksitemp[1].c_invoice;
			do{
			fs >> transaksitemp[1].dibeli[j].barcode 
			>> transaksitemp[1].dibeli[j].nama  
			>> transaksitemp[1].dibeli[j].hargabeli
			>> transaksitemp[1].dibeli[j].hargajual 
			>> transaksitemp[1].dibeli[j].qty 
			>> c;
			j++;
			}while(c == '#');
			untung += (transaksitemp[1].dibeli[j].hargajual - 
						 transaksitemp[1].dibeli[j].hargabeli) *
						 transaksitemp[1].dibeli[j].qty ;
		}
			i++; 
			
		}
		fs.close();
		return(untung);
	}
	else 
		return(-1);
	
	
}

main(){
	int LOGIN_ACCESS = 1; //0 = admin, 1 = cashier 
	int LAYERMENU = 1; //semakin tinggi angkanya, semakin dalam lapisannya.
	bool BACKVALIDATION = true;
do{
	system("cls");

	login(&LOGIN_ACCESS);
	system("color 0a");
	//logo();

	char MENU = 0;
	///main menu//

	if(LOGIN_ACCESS == 0){
		do{
			BACKVALIDATION = false;
			LAYERMENU = 2;
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
					if(penjualan() != -1){
					cout << setw(4) << ' ' << "\nTOTAL KEUNTUNGAN : Rp." << penjualan();
					}
					else 
						cout << "Data belum ada!";
					cout << "\n\n";
					cout << setfill('=') << setw(120) << ' ' << endl;
					cout << setfill(' ');
					cout << endl;
					system("pause");
				break;
				}
				case('2'):{
					system("cls");
					detailtransaksi();
				break;
				}
				case('3'):{
					BACKVALIDATION = false;
					LAYERMENU = 3;
					cout << setfill(' ');
					char MENUbarang;
					do{
					system("cls");
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
							inputbarangmenu();
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
							cout << "\n\nData Barang : \n";
							
							ifstream ifs;
							ifs.open("databarang.txt");
							if(ifs){
								cout << setfill('=') << setw(90) << " \n";
								cout << setfill(' ');
								cout << "Barcode" << setw(3) << ' ' 
									 << "Nama Barang" << setw(19) <<' ' 
									 << "Harga Beli" << setw(5) << ' ' 
									 << "Harga Jual" << setw(4) << ' ' 
									 << "Jumlah" << endl;
								cout << setfill('=') << setw(90) << " \n";
								cout << setfill(' ');
								while(!ifs.eof()){
									ifs >> detailbarang[1].barcode >> 
									detailbarang[1].nama >> 
									detailbarang[1].hargabeli >> 
									detailbarang[1].hargajual >>
									detailbarang[1].stok;
									showdatabarang();
									cout << endl;
								}
								cout << setfill('=') << setw(90) << " \n";
								cout << setfill(' ');
							}
							else{
							 cout << "\nFile Tidak Dapa Dibuka"
								  << "\nAtau FIle Tidak Ada";
							  }
							ifs.close();
							
							cout << endl;
							system("pause");
							break;
						}
						
						case'9':{
							BACKVALIDATION = true;
							LAYERMENU = 2;
						break;
						}
						
						case'0':{
							exit();
						break;
						}
					}
					}while(!BACKVALIDATION || LAYERMENU == 3);	 
				break;
				}
				case('4'):{
					BACKVALIDATION = false;
					LAYERMENU = 3;
					do{
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
						
						case '9':{
							BACKVALIDATION = true;
							LAYERMENU = 2;
						break;
						}
						case '0':{
							exit();
						break;
						}
					}
					}while(!BACKVALIDATION || LAYERMENU == 3);
				break;
				}
				case '9':{
					BACKVALIDATION = true;
					LAYERMENU = 1;
				break;
				}
				case '0':{
					exit();
				break;
				}
				
			}
		}while(!BACKVALIDATION || LAYERMENU == 2);
	}
	else if(LOGIN_ACCESS == 1){
		do{
			BACKVALIDATION = false;
			LAYERMENU = 2;
			system("cls");
			cout << "\t\t\t\\\t\t  Home  \t\t/\n";
			cout << "\t\t\t \\" << setfill('-') << setw(38) << "-/";
			setfill(' ');
			cout << "\n\t\t\t\t1. Cashier";
			cout << "\n\t\t\t\t2. Detail Transaksi";
			cout << "\n\n\t\t\t\t9. Back";
			cout << "\n\t\t\t0. Exit\n";
			cout << "\n\t\t\tPILIH :> ";
			cin >> MENU;
			
			switch(MENU){
				case('1'):{
					system("cls");
					kasir();
					
					cout << endl;
					system("pause");
				break;
				}
				case('2'):{
					system("cls");
					detailtransaksi();
				break;
				}
				case('9'):{
					BACKVALIDATION = true;
					LAYERMENU = 1;
				break;	
				}
				case('0'):{
					exit();
				break;
				}
			}
		}while(!BACKVALIDATION || LAYERMENU == 2);
	}
cin.ignore();

}while(BACKVALIDATION == true);
}
