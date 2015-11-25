BEGIN {
	dropped=0;
} {
	if($1 == "d")
		dropped++;
} END {
	printf("Packets dropped: %d\n\n",dropped);
}