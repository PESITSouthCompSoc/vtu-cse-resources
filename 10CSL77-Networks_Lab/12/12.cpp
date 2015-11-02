#include <iostream>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>

#define NUM_PKTS 10

using namespace std;

int myrandom(int a);

int main(){

	int pkt_size[NUM_PKTS], clk, bkt_size;
	int output_rate, pkt_size_rem=0;
	int pk_size, pk_time, output;

	//randomize packet sizes
	for(int i=0; i<NUM_PKTS; i++){
		pkt_size[i]=myrandom(6)*10;
		cout << "packet #" << i << "  = " << pkt_size[i] <<" bytes\n";
	}

	cout << "Enter the following:-\n\nOutput Rate: ";
	cin >> output_rate;
	cout << "Bucket Size: ";
	cin >> bkt_size;
	cout << "\n\n";
	//run algorithm for Leaky Bucket
	for(int i=0; i<NUM_PKTS; i++){
		//if current packet size + rem size is greater than bucket size
		if( (pkt_size[i] + pkt_size_rem) > bkt_size ){
			if( pkt_size[i] > bkt_size ){
				cout << "Packet #" << i << " of size " << pkt_size[i] << " exceeds the size of the bucket (" << bkt_size <<"). DROPPED.\n";
			}
			else{
				cout << "Bucket capacity exceeded! Packet #" << i << " DROPPED.\n";
			}
		}//else if can be accommodated
		else{
			pkt_size_rem += pkt_size[i];
			cout << "Incoming packet size: " << pkt_size[i] << endl;
			cout << "Bytes remaining to transmit: " << pkt_size[i] << endl;
			pk_time = myrandom(4)*10;
			cout << "Time left for transmission: " << pk_time << " units.\n";

			for(clk=10; clk<=pk_time; clk+=10){
				sleep(1);
				if(pkt_size_rem){
					//completely transmissible in this cycle
					if(pkt_size_rem <= output_rate){
						output = pkt_size_rem;
						pkt_size_rem = 0;
					}
					//partially transmissible in this cycle
					else{
						output = output_rate;
						pkt_size_rem -+ output_rate;
					}
					cout << "Packet of size " << output << " transmitted.\n";
					cout << pkt_size_rem << " bytes left to transmit.\n";
				}
				//if nothing left to transmit
				else{
					cout << "Time left for transmission: " << pk_time << " units.\n";
					cout << "No packets left to transmit!\n";
					break;
				}
			}
		}
		cout << "\n\n";
	}
	return 0;
}

int myrandom(int a){
//	srand(time(NULL));
	int r = (rand()%a);
	return  (r == 0) ? 1 : r ;
}