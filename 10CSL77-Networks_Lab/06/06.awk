BEGIN {
	totalPkts = 0;
	throughput = 0;
} 
{
	if( ($1 == "r") && ($3 == "_4_") && ($4 == "AGT") && ($7=="tcp") && ($8>=1000) )
		totalPkts++;
}
END {
	throughput = (totalPkts * 1000 * 8) / (85 * 1000000);
	printf("Total delivered: %ld\n",totalPkts);
	printf("throughput: %f Mbps\n\n",throughput);
}