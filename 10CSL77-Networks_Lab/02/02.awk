BEGIN {
	tcp_sent = 0; tcp_drop = 0;
	udp_sent = 0; udp_drop = 0;
	tcp_delR = 0; tcp_drpR = 0;
	udp_delR = 0; udp_drpR = 0;
} {
	
	if( $1 == "d" ){
		if($5 == "tcp")
			tcp_drop++;
		else
			udp_drop++;
	}
	if( $1 == "+" ){
		if($5 == "tcp")
			tcp_sent++;
		else
			udp_sent++;
	}

} END {
	
	tcp_delR = (tcp_sent - tcp_drop) / tcp_sent;
	udp_delR = (udp_sent - udp_drop) / udp_sent;
	tcp_drpR = tcp_drop / tcp_sent;
	udp_drpR = udp_drop / udp_sent;
	
	print("TCP\n");
	print("Delivery Ratio: "tcp_delR);
	print("Drop Ratio: "tcp_drpR);

	print("\n\nUDP\n");
	print("Delivery Ratio: "udp_delR);
	print("Drop Ratio: "udp_drpR);
}