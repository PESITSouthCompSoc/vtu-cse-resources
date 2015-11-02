#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>

using namespace std;

int isPrime(int x);
int gcd(int a, int b);
long long int encrypt(long long int m,long long int x,long long int n);
long long int decrypt(long long int c,long long int y,long long int n);

int main(){

	cout << "\t\tRSA Algorithm Implementation\n\n";
	int a, b;
	long long int x, y, z, n, len;
	long long int m, c;
	long long int cipher[20];
	char message[20];

	//Generate two random prime numbers
	do{
 		a = rand()%30; 
	}while( !isPrime(a) );

	do{
		b = rand()%30; 
	}while( !isPrime(b) || a==b );

	cout << "Generated two prime numbers " << a << "(a) " << b << "(b).\n";
	n = a * b;
	z = (a-1)*(b-1);
	cout << "n = (a*b) = " << n << endl;
	cout << "z = (a-1)*(b-1) = " << z << endl << endl;

	//x coprime to z
	do{
		x = ( rand()%z ) + 1;
	}while(gcd(x,z)!=1 || x==1);

	//find y such that  xy mod z = 1;
	y=1;
	while( ((x*y)%z) !=1 || x==y)
		y++;

	// now {x, n} is the public key & {y, n} is the private key
	cout << "Public Key: {" << x << "," << n << "}\n";
	cout << "Private Key: {" << y << "," << n << "}\n\n";

	cout << "Enter message (no spaces): ";
	cin >> message;
	len = strlen(message);

	cout << "Cipher Text: ";
	for(int i=0; i<len; i++){
		cipher[i] = encrypt(message[i],x,n);
		cout << cipher[i];
	}
	cout << "\nDecrypted text: ";
	for(int i=0; i<len; i++){
		message[i] = decrypt(cipher[i],y,n);
		cout << message[i];
	}
	cout << endl << endl;
	// c = encrypt(m,x,n);
	// cout << "Cipher: " << c << endl;

	// m = decrypt(c,y,n);
	// cout << "Message: " << m << endl << endl;
}

int isPrime(int x){
	int n = sqrt(x);
	for(int i=2; i<=n; i++){
		if( x%i == 0 )
			return 0;
	}
	return 1;
}

int gcd(int a, int b){
	int temp;
	while(b){
		temp = b;
		b = a%b;
		a = temp;
	}
	return a;
}

long long int encrypt(long long int m,long long int x,long long int n){
	long long int temp=1;
	for(long long int i=0; i<x; i++){
		temp *= m;
		temp %= n;
	}
	return temp;
}

long long int decrypt(long long int c,long long int y,long long int n){
	long long int temp=1;
	for(long long int i=0; i<y; i++){
		temp *= c;
		temp %= n;
	}
	return temp;
}