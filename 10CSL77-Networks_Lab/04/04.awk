BEGIN {
	tcp_pkt_delvr = 0; udp_pkt_delvr = 0;
	throughput = 0; total_pkt_delvr = 0;
	#set this according to the values given in your program
	packetsize = 1000; simulation_time=18*1000000;
} {
	# $3 is source, $4 is destination; so they should be the nodes [4 & 5] connecting the two lans
	# 4 -> 5 : udp packets
	# 5 -> 4 : tcp packets
	if( $1 == "+" && $3 == "4" && $4 == "5" && $5 == "cbr")
		udp_pkt_delvr++;
	if( $1 == "+" && $3 == "5" && $4 == "4" && $5 == "tcp")
		tcp_pkt_delvr++;
} END {
	total_pkt_delvr = tcp_pkt_delvr + udp_pkt_delvr;
	printf("Total Packets Delivered: %d\n",total_pkt_delvr);

	# Throughput Formula = (total_packets_delvr * packetsize * 8[bits])/(simulation_time)
	throughput = ( total_pkt_delvr * packetsize * 8 ) / simulation_time;
	printf("Throughput: %f Mbps\n\n",throughput);
}