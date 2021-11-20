// (c) RomeuHub.cat 2003-2021

#include <iostream>
#include <iomanip>
#include <sstream>
#include <bitset>
#include <string>
using namespace std;

int bitExtracted(int number, int k, int p)
{
    return (((1 << k) - 1) & (number >> (p - 1)));
}

string mnemonic(int op, int f) {
	string mnemo = "none";
	if (op <= 10) switch (op) {
		case 0:
		{
			switch (f) {
				case 0: mnemo = "AND"; break;
				case 1: mnemo = "OR";  break;
				case 2: mnemo = "XOR"; break;
				case 3: mnemo = "NOT"; break;
				case 4: mnemo = "ADD"; break;
				case 5: mnemo = "SUB"; break;
				case 6: mnemo = "SHA"; break;
				case 7: mnemo = "SHL"; break;
			}
		}
		break;

		case 1:
		{
			switch (f) {
                                case 0: mnemo = "CMPLT";  break;
                                case 1: mnemo = "CMPLE";  break;
                                case 2: mnemo = "-";      break;
                                case 3: mnemo = "CMPEQ";  break;
                                case 4: mnemo = "CMPLTU"; break;
                                case 5: mnemo = "CMPLEU"; break;
                                case 6: mnemo = "-";      break;
                                case 7: mnemo = "-";      break;

			}
		}
		break;

		case 2: mnemo = "ADDI"; break;
		case 3: mnemo = "LD";   break;
		case 4: mnemo = "ST";   break;
		case 5: mnemo = "LDB";  break;
		case 6: mnemo = "STB";  break;
		case 7: mnemo = "Branch future extension"; break;
		case 8:
		{
			switch (f) {
				case 0: mnemo = "BZ";  break;
				case 1: mnemo = "BNZ"; break;
			}
		}
		break;

		case 9:
		{
			switch (f) {
				case 0: mnemo = "MOVI";  break;
				case 1: mnemo = "MOVHI"; break;
			}
		}
		break;

		case 10:
		{
			switch (f) {
				case 0: mnemo = "IN";  break;
				case 1: mnemo = "OUT"; break;
			}
		}
		break;
		
	}

	return mnemo;
}

void entries(int op, int instruction){
	int  i = instruction;
	char r = 'R';
	char c = ',';
	
	switch(op) {
		case 0:
		case 1:
			cout << r << bitExtracted(i, 3, 4) << c << r << bitExtracted(i, 3, 10) << c << r << bitExtracted(i, 3, 7) << endl;
		       	break;
		case 2:
		case 3:
		case 5:
			cout << r << bitExtracted(i, 3, 7) << c << r << bitExtracted(i, 3, 10) << c << "0x" << hex << uppercase << bitExtracted(i, 6, 1) << endl;
			break;
		case 4:
		case 6:
			cout << r << bitExtracted(i, 3, 10) << c << r << bitExtracted(i, 3, 7) << c << "0x" << hex << uppercase << bitExtracted(i, 6, 1) << endl;
			break;
		case 8:
		case 9:
		case 10:
			cout << r << bitExtracted(i, 3, 10) << c << "0x" << hex << uppercase << bitExtracted(i, 6, 1) << endl;
			break;


	}
}


int main()
{
    int instruction, op, f, a, b, d;
    cout << "Escriu un numero hexadecimal per convertir-lo en una instrucció d'ensemblador" << endl;
    cin >> hex >> instruction;

    op = bitExtracted(instruction, 5, 13);
    if (op <= 1) f  = bitExtracted(instruction, 3, 1);
    else f = bitExtracted(instruction, 1, 9);

    cout << mnemonic(op, f) << ' ';
    entries(op, instruction);
    cout << endl;  
}
