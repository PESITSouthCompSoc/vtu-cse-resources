set ns [new Simulator]

set tf [open 02.tr w]
set nf [open 02.nam w]

$ns trace-all $tf
$ns namtrace-all $nf

#nodes
set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]

#topologies
$ns duplex-link $n0 $n2 2Mb 10ms DropTail
$ns duplex-link $n1 $n2 2Mb 10ms DropTail
$ns duplex-link $n2 $n3 2Mb 15ms DropTail

#orientation
$ns duplex-link-op $n0 $n2 orient right-down
$ns duplex-link-op $n1 $n2 orient right-up
$ns duplex-link-op $n2 $n3 orient right

#queue limit
$ns queue-limit $n0 $n2 10
$ns queue-limit $n1 $n2 10
$ns queue-limit $n2 $n3 15

#agents & applications
set tcp0 [new Agent/TCP]
set udp0 [new Agent/UDP]
set sink0 [new Agent/TCPSink]
set null0 [new Agent/Null]

set ftp0 [new Application/FTP]
set cbr0 [new Application/Traffic/CBR]

#attaching
$ns attach-agent $n0 $tcp0
$ns attach-agent $n1 $udp0
$ns attach-agent $n3 $sink0
$ns attach-agent $n3 $null0

$ftp0 attach-agent $tcp0
$cbr0 attach-agent $udp0

#properties
$ftp0 set pktSize_ 100
$cbr0 set packetSize_ 100
$cbr0 set interval_ 0.001

$ns connect $tcp0 $sink0
$ns connect $udp0 $null0

proc finish {} {
	global ns tf nf
	$ns flush-trace
	exec nam 02.nam &
	exit 0
}

$ns color 1 "Blue"
$ns color 2 "Green"

$tcp0 set class_ 1
$udp0 set class_ 2

$ns at 1.0 "$cbr0 start"
$ns at 2.0 "$ftp0 start"
$ns at 3.0 "$ftp0 stop"
$ns at 4.0 "$cbr0 stop"
$ns at 5.0 "finish"

$ns run

