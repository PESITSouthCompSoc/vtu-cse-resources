BEGIN {
	tcpcnt = 0;
	cbrcnt = 0;
}
{
	if($1 == "d")
	{
		if($5 == "tcp")
			tcpcnt++;
		else
			cbrcnt++;
	}
}
END {
	print("TCP packets dropped = "tcpcnt);
	print("CBR packets dropped = "cbrcnt);
}