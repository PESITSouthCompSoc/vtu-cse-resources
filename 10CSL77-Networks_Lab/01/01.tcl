set ns [new Simulator]

set tf [open 01.tr w]
set nf [open 01.nam w]

$ns trace-all $tf
$ns namtrace-all $nf

set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]

$ns duplex-link $n0 $n2 1.5Mb 10ms DropTail
$ns duplex-link $n1 $n2 1.5Mb 10ms DropTail

$ns duplex-link-op $n0 $n2 orient right-up
$ns duplex-link-op $n1 $n2 orient right-down

$ns queue-limit $n0 $n2 10
$ns queue-limit $n1 $n2 10

set tcp0 [new Agent/TCP]
$ns attach-agent $n0 $tcp0

set ftp0 [new Application/FTP]
$ftp0 attach-agent $tcp0

set udp0 [new Agent/UDP]
$ns attach-agent $n1 $udp0

set cbr0 [new Application/Traffic/CBR]
$cbr0 attach-agent $udp0

set sink0 [new Agent/TCPSink]
$ns attach-agent $n2 $sink0

set null0 [new Agent/Null]
$ns attach-agent $n2 $null0

#set additional parameters for connection
$cbr0 set interval_ 0.001
$cbr0 set packetSize_ 1000

$ftp0 set size_ 1000

#make the connections
$ns connect $tcp0 $sink0
$ns connect $udp0 $null0

proc finish {} {
	global ns tf nf
	$ns flush-trace
#	exec nam 01.nam &
	exit 0
}

#colors etc
$ns color 1 "Red"
$ns color 2 "Blue"
$ns color 3 "Green"
$ns color 4 "Black"

$udp0 set class_ 1
$tcp0 set class_ 2

$n0 shape hexagon
$n0 label "FTP"
$n1 label "CBR"
$n2 label "SINK/NULL"


#schedule
$ns at 0.5 "$cbr0 start"
$ns at 1.0 "$ftp0 start"
$ns at 4.0 "$ftp0 stop"
$ns at 4.5 "$cbr0 stop"
$ns at 5.0 "finish"

$ns run
