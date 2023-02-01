#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

bool checkFile( string& name ) {
    fstream file{ name };
    return file.good();
}

void readFile( string fileName ) {
    string line;
    ifstream myfile( fileName ); // otwarcie pliku wejsciowego
    if(!checkFile( fileName )) {   return;    }
    ofstream outputFile( "ready"+fileName+".csv"); // utworzenie pliku wyjsciowego
    string date, firstValue, secondValue, thirdValue, fourthValue, fifthValue, sixthValue;
    int g = 0;
    while(getline( myfile, line )) { // dopoki nie przeczyta calego pliku myfile
        stringstream ss( line ); // zamiana wczytanej linii na strumien danych
        getline( ss, date, '\t' ); // odczytuje strumien danych do znaku tabulacji i zapisuje go do zmiennej date
        size_t commaPos = date.find( ',' ); // zapisanie do zmiennej commaPos pozycji przecinka
        if(commaPos != string::npos) { // sprawdzenie czy find nie zwrocil npos
            date.erase( commaPos, 1 ); // usuniecie przecinka
        }
        getline( ss, firstValue, '\t' ); 
        size_t commaPos2 = firstValue.find( ',' );
        if(commaPos2 != string::npos) {
            firstValue.erase( commaPos2, 1 );
        }
        double convertedValue1 = strtod( firstValue.c_str(), nullptr ); // strtod konwertuje ciag znakow na typ double, c_str() zwraca wskaznik na zmienna, 
        // drugim argumentem jest wskaznikiem na zmienna do ktorej ciag zostanie zapisany, lecz ja przypisuje ja bezposrednio do convertedValue1,
        // dlatego uzywam nullptr co oznacza ze ta informacja jest niepotrzebna i nie bedzie wykorzystywana
        getline( ss, secondValue, '\t' );
        getline( ss, thirdValue, '\t' );
        getline( ss, fourthValue, '\t' );
        size_t commaPos3 = fourthValue.find( ',' );
        if(commaPos3 != string::npos) {
            fourthValue.erase( commaPos3, 1 );
        }
        double convertedValue2 = strtod( fourthValue.c_str(), nullptr );
        getline( ss, fifthValue, '\t' );
        getline( ss, sixthValue, '\t' );
        g++;
        outputFile << g << "\t" << date << "\t" << firstValue << "\t" << fourthValue << "\t" << convertedValue1 - convertedValue2 << endl; // zapisanie potrzebnych danych do pliku wyjsciowego
    }
    myfile.close(); // zamkniecie plikow
    outputFile.close();
}



void removeEmptyLines( string& fileName1 ) {
    ifstream inputFile{ fileName1 };
    checkFile( fileName1 );
    ofstream tempFile;
    tempFile.open( "temp"+fileName1 );
    string line;

    while(getline( inputFile, line )) {
        if(line.find( "-" ) != string::npos) { // wyszukiwanie - ktore w plikach oznaczaja brak wartosci
            int count = 0;
            for(int i = 0; i < line.size(); i++) { // dopoki i jest mniejsze niz dlugosc linii
                if(line[ i ] == '-') { 
                    count++;
                }
            }
            if(count > 1) { // jedna - nie oznacza ze wiersz jest bledny, dopiero 2 lub wiecej
                continue;
            }
            else
            {
                tempFile << line << endl; // zapisanie poprawnej linii
            }
        }
        else
        {
            tempFile << line << endl;
        }
    }
    inputFile.close(); // zamkniecie plikow
    tempFile.close();
}

void countLines( string& name, string& name2, string& name3) {
    ifstream file{ "temp" + name };
    ifstream file2{ "temp" + name2 };
    ifstream file3{ "temp" + name3 };
    ofstream dates;
    dates.open( "dates.txt" );
    if(!dates) {
        cerr << "Nie mozna otworzyc pliku do zapisu." << endl;
        return;
    }
    
    string line, line2, line3;
    while(getline( file, line )) {
        string date = line.substr( 0, 12 ); // zapisanie do zmiennej date date z pliku, ktora znajduje sie na poczatku wiersza i zajmuje 12 znakow
        dates << date << endl; // zapisanie do pliku dates dat ze wszystkich plikow wejsciowych
    }
    while(getline( file2, line2 )) {
        string date = line2.substr( 0, 12 );
        dates << date << endl;
    }
    while(getline( file3, line3 )) {
        string date = line3.substr( 0, 12 );
        dates << date << endl;
    }
    dates.close();
    return;
}

void repetedLines( string& fileName ) {
    fstream date{ fileName };
    if(!checkFile( fileName )) {
        return;
    }
    ofstream dates2;
    dates2.open( "dates2.txt" );
    if(!dates2) {
        cerr << "Nie mozna otworzyc pliku do zapisu." << endl;
        return;
    }
    static string lines[ 15000 ]; // pliki wejsciowy maja niecale 5000 linii, dlatego wartosc 15000, powinno to byc zrobione dynamicznie ???????
    // static, gdyz tablica jest duza i nie ma wtedy warninga od kompilatora
    int lineCount = 0;


    while(getline( date, lines[ lineCount ] )) { //przepisanie linii z pliku do tablicy oraz policzenie elementow tablicy
        lineCount++;
    }


    for(int i = 0; i < lineCount; i++) { // dopoki i mniejsze od rozmiaru tablicy, w sumie moglem uzyc chyba size_of zamiast liczyc to
        int count = 0;
        for(int j = 0; j < lineCount; j++) {
            if(lines[ i ] == lines[ j ]) {
                count++;
            }
        }
        if(count == 3) { // gdy data powtarza sie 3 razy oznacza, ze znajduje sie w kazdym pliku i te wiersze zapisuje do nowego pliku

            dates2 << lines[ i ] << endl;
        }
    }
    date.close();
    dates2.close();
}

void newFile( string fileName, string fileName2, string fileName3, string data ) {
    fstream oldFile{ fileName };
    fstream oldFile2{ fileName2 };
    fstream oldFile3{ fileName3 };
    fstream dat{ data };

    ofstream newFile1;
    newFile1.open( "new"+fileName );
    if(!newFile1) {
        cerr << "Nie mozna otworzyc pliku do zapisu." << endl;
        return;
    }
    ofstream newFile2;
    newFile2.open( "new"+fileName2 );
    if(!newFile2) {
        cerr << "Nie mozna otworzyc pliku do zapisu." << endl;
        return;
    }
    ofstream newFile3;
    newFile3.open( "new"+fileName3 );
    if(!newFile3) {
        cerr << "Nie mozna otworzyc pliku do zapisu." << endl;
        return;
    }

    string line, line1, line2, line3;

    while(getline( dat, line )) { // ogolnie: porownywanie dat z pliku do ktorego zapisalem powtarzajace sie daty 3 razy z biezacymi plikami i wypisanie z nich dobrych linii do nowych plikow

        while(getline( oldFile, line1 )) {
            string date = line1.substr( 0, 12 );

            if(line.find( date ) != string::npos) {
                newFile1 << line1 << endl;
                break;
            }
        }
        while(getline( oldFile2, line2 )) {
            string date = line2.substr( 0, 12 );

            if(line.find( date ) != string::npos) {
                newFile2 << line2 << endl;
                break;
            }
        }
        while(getline( oldFile3, line3 )) {
            string date = line3.substr( 0, 12 );

            if(line.find( date ) != string::npos) {
                newFile3 << line3 << endl;
                break;
            }
        }
    }
    oldFile.close();
    oldFile2.close();
    oldFile3.close();
    dat.close();
    newFile1.close();
    newFile2.close();
    newFile3.close();
}
int lines( string& fileName ) { // funkcja zwracajaca ilosc linii w pliku, napisana tylko dla sprawdzenia
    if(!checkFile( fileName )) { return 0; }
    fstream file{ fileName };
    int n = 0;
    string line;
    while(getline( file, line )) {
        n++;
    }
    return n;
}

class file {    
    public:
        string fileName;
        
        void alert() {
            cout << "Prepering file: " << fileName << endl;
            removeEmptyLines( fileName );
            cout << "File preperation completed successfully and empty lines removed\n" << endl;
        }
        file( string &x ) {
            fileName = x;
            
        }
    private:
        bool checkFile( string& name ) {
            fstream file{ name };
            return file.good();
        }
};

class cLines {
public:
    string name1;
    string name2;
    string name3;
    void alert() {
        cout << "starting counting lines...\n" << endl;
        countLines( name1, name2, name3 );
        cout << "lines counted and saved to dates.txt file\n " << endl;
    }
    cLines( string& x, string& y, string& z ):name1( x ), name2( y ), name3( z ) {};
};

class dates {
    public:
        string name;

        void alert() {
            cout << "saving to dates2.txt common dates\n" << endl;
            repetedLines( name );
            cout << "repeted lines just saved\n" << endl;
        }
        dates( string& x ) {
            name = x;
        }
    private:
        bool checkFile( string& name ) {
            fstream file{ name };
            return file.good();
        }
};

class readyFiles {

    public:
        string name;
        void alert() {
            cout << "Analyzing file: " << name << endl;
            readFile( name );
            cout << "File analyzed\n" << endl;
        }
        readyFiles( string& x ) {
            name = x;
        }    

    private:
        bool checkFile( string& name ) {
            fstream file{ name };
            return file.good();
        }
};

int main()
{
    string eur_usd = "EUR_USD.txt";
    string gold = "gold.txt";
    string sip500 = "us500.txt";
    file plik1( eur_usd );
    plik1.alert();
    file plik2( gold );
    plik2.alert();
    file plik3( sip500 );
    plik3.alert();
    cLines files( eur_usd, gold, sip500);
    files.alert();
    string dat = "dates.txt";
    dates daty( dat );
    daty.alert();
    cout << "Starting creating files ready to analyze...\n " << endl;
    newFile( "tempEUR_USD.txt", "tempgold.txt", "tempus500.txt", "dates2.txt" );
    cout << "Files newtempEUR_USD.txt newtempgold.txt and newtempus500.txt ready to analyze\n" << endl;
    string eurusd = "newtempEUR_USD.txt", goldd = "newtempgold.txt", sip_500 = "newtempus500.txt";
    readyFiles eur(eurusd);
    eur.alert();
    readyFiles gol( goldd );
    gol.alert();
    readyFiles sip( sip_500 );
    sip.alert();
    string a = "readynewtempEUR_USD.txt.csv";
    string b = "readynewtempgold.txt.csv";
    string c = "readynewtempus500.txt.csv";
    int n = lines( a );
    int m = lines( b );
    int l = lines( c );
    cout << "Liczba linii: " << a << " wynosi: " << n << endl;
    cout << "Liczba linii: " << b << " wynosi: " << m << endl;
    cout << "Liczba linii: " << c << " wynosi: " << l << endl;
}
