//CRC-16-CCITT = x^{16} + x^{12} + x^5 + 1

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;

char poly[]="10001000000100001\0";
char enc[128], msg[128], remainder[128]="";

int poly_len, msg_len, enc_len, choice, flag;

void CRC();

int main(){	

	cout << "The generating polynomial for CRC-16-CCITT is:\n= ";
	poly_len = strlen(poly);
	for(int i=poly_len-1; i>=0; i--){
		if(poly[i]!='0')
			cout << "x^" << 16-i;
		if(i!=poly_len-1 && poly[i+1]!='0')
			cout << " + ";
	}
	cout << endl << endl << "Thus, divisor is: " << endl << poly << endl;
	cout << "\nEnter the message to be sent: ";
	cin >> msg;

	
	msg_len = strlen(msg);
	enc_len = msg_len + poly_len - 1;

	strcpy(enc,msg);
	//append 0's
	for(int i=msg_len; i<enc_len; i++){
		enc[i]='0';
	}
	cout << "\nMessage appended with 0's: " << endl << enc << endl;
	CRC();
	strncpy(remainder,enc+msg_len,poly_len-1);
	cout << "\nRemainder after division: \n" << remainder << " (16-bit CRC code)" << endl;
	for(int i=0; i<enc_len; i++){
		if(i<msg_len)
			enc[i]=msg[i];
	}
	cout << "\nMessage transmitted: " << endl << enc << endl;

	cout << "\nIntroduce an error? (1 = yes, 0 = no): ";
	cin >> choice;
	if(choice){
		int bit;
		cout << "Select a bit number (0 to " << enc_len-1 << "): ";
		cin >> bit;
		if(bit >= 0 && bit < enc_len ){
			cout << "\nBit #" << bit << " changed from " << enc[bit] << " to ";
			enc[bit] = enc[bit] == '0' ? '1' : '0';
			cout << enc[bit] << "." << endl << endl;
		}
		else{
			cout << "Invalid input.\n";
			return -1;
		}
	}

	cout << "Received message: " << endl << enc << endl;
	cout << "\nChecking for errors...\n\n";

	CRC();
	flag=0;
	for(int i=0; i<enc_len; i++)
		if(enc[i]=='1'){
			flag=1;
			break;
		}
	if(flag)
		cout << "An error was detected.\n";
	else
		cout << "No errors detected.\n";

	return 0;
}

void CRC(){
	for(int i=0; i<msg_len; i++){
		if(enc[i]=='0')
			continue;

		for(int j=i, k=0; k<poly_len; j++, k++){
			enc[j] = poly[k]==enc[j] ? '0' : '1';
		}
	}
}