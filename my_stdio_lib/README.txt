	Structura:

typedef struct _so_file
{
    int _fd;                // file descriptor
    int _open_type;         // 1-r, 2-r+, 3-w, 4-w+, 5-a, 6-a+, 0-altceva
    int _error;             // 0-nu avem eroare, 1-avem eroare
    char _buffer[MAX_SIZE]; // buffering
    int _buffer_pos;        // pozitia in buffer
    int _file_pos;          // pozitia in fisier
    int _eof;               // 0-nu end of file, 1-end of file
    int _lastOperation;     // 0-read, 1-write, 2-altceva
    pid_t _child_pid;       // pid copil

} SO_FILE;

	Pentru fiecare functie in parte am intrat pe: https://www.tutorialspoint.com/c_standard_library/stdio_h.htm
si am citit documentatie (exemple de folosire, return values etc.)  pentru a mi da seama cum sa le implementez.
	
	SO_FOPEN: am alocat dinamic structura, am initializat fiecare camp al structurii pentru a nu aveam memcheck,
pentru fiecare mod de deschidere in parte am setat file descriptor (_fd) si tipul de fisier (_open_type).

	SO_FCLOSE: am  verificat  daca  ultima operatie facuta  (_lastOperation)  a  fost de  scriere  pentru a goli 
buffer ul (_buffer), am eliberat memoria.

	SO_FILENO: returneaza file descriptor.

	SO_FFLUSH: scrie  buffer  ul  in  file  descriptor  ul  precizat  si  seteaza  pozitia in buffer inapoi la 0.
(buffer ul este golit).

	SO_FSEEK: daca  ultima  operatie  a  fost de scriere se  da fflush, iar  apoi  se  muta  cursorul  fisierului
(_file_pos) folosind lseek.
	
	SO_FTELL: returneaza pozitia cursorului din fisier.
	
	SO_FREAD: daca fisierul se deschide cu a+ mutam pentru  citire cursorul la inceput (poate inainte s a facut o 
operatie de scriere). Folosind un buffer auxiliar citim caracter cu caracter apoi copiem cu memcpy continutul in *ptr.

	SO_FWRITE: daca fisierul se deschide cu a+ sau  a mutam pentru  scriere cursorul la final.  Citim cariacter cu 
caracter, iar daca numarul de caractere citite e 0 sau difera de nmemb returnam eroare.

	SO_FEOF: returneaza daca cursorul se afla la final de fisier sau nu.

	SO_FEOF: returneaza daca este eroare sau nu.

	SO_POPEN: am alocat dinamic  structura, am  initializat fiecare  camp al structurii pentru a nu aveam memcheck,
am verificat daca  sunt  erori  la  fork sau pipe,  pentru procesul  copil am verificat daca e  type r sau w, am inchis
capetele pipe ului neutilizate si am redirectionat input/output.
	https://www.man7.org/linux/man-pages/man3/popen.3.html

	SO_PCLOSE: am inchis file_descriptor si am verificat status ul procesului.


