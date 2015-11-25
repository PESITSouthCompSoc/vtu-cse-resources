# Set Up NS & files required
set ns [new Simulator]

set nf [open 05.nam w]
set tf [open 05.tr w]

$ns trace-all $tf
$ns namtrace-all $nf

# Open the xgraph files for writing
set oFile1 [open congestion1.xg w]
set oFile2 [open congestion2.xg w]

# 10 nodes
set numNodes 10
for {set i 0} {$i < $numNodes} {incr i} {
	set n($i) [$ns node]
}

# Build 2 ethernet lans of 5 nodes each
# make-lan function & parameters : make-lan {nodes bw delay lltype ifqtype mactype chantype}
# nodes : list of nodes in lan ; bandwidth, delay; lltype : Link Layer type (object for the link layer) ; 
# ifqtype : the interface queue type, here a normal DropTail; mactype : Mac layer object, here Ethernet 
# from IEEE Mac 802.3 Specification; chantype : physical layer channel object not used
$ns make-lan "$n(0) $n(1) $n(2) $n(3) $n(4)" 10Mb 20ms LL Queue/DropTail Mac/802_3
$ns make-lan "$n(5) $n(6) $n(7) $n(8) $n(9)" 10Mb 20ms LL Queue/DropTail Mac/802_3

# Set datarate for lan
Mac/802_3 set dataRate_ 10

# Connect the LANs via 4 & 5
$ns duplex-link $n(4) $n(5) 2Mb 10ms DropTail
# Set the queue limit
$ns queue-limit $n(4) $n(5) 10
# And error model & rate
set err [new ErrorModel]
$ns lossmodel $err $n(4) $n(5)
$err set rate_ 0.1

# Set up agents & applications
set tcp0 [new Agent/TCP]
set tcp1 [new Agent/TCP]
set sink0 [new Agent/TCPSink]
set sink1 [new Agent/TCPSink]
set telnet [new Application/Telnet]
set ftp [new Application/FTP]

# Attach agents & application
$ns attach-agent $n(0) $tcp0
$ns attach-agent $n(3) $sink1
$ns attach-agent $n(6) $tcp1
$ns attach-agent $n(9) $sink0

$ftp attach-agent $tcp0
$telnet attach-agent $tcp1

# Additional paramenters for connection
$ftp set packetSize_ 100
$telnet set packetSize_ 100

# Colors & labels
$n(0) label "FTP-TCP"
$n(6) label "Telnet-TCP"
$n(3) label "Sink1-FTP"
$n(9) label "Sink2-Telnet"
$ns color 1 "Blue"
$ns color 2 "Green"

$tcp0 set class_ 1
$tcp1 set class_ 2

# Connect the agents
$ns connect $tcp0 $sink0
$ns connect $tcp1 $sink1

# Procedure for calculating the congestion window
proc calcCongestion {tcpSource outFile} {
	global ns
	set now [$ns now]
	set interval 0.1
	set cwindow [$tcpSource set cwnd_]
	puts $outFile "$now $cwindow"
	# Recursively call the function again
	$ns at [expr $now + $interval] "calcCongestion $tcpSource $outFile"
}

proc finish {} {
	global ns nf tf
	$ns flush-trace
	close $tf
	close $nf
	# graph execution: line width 3, bg white, geometry 600x600
	exec xgraph -lw 3 -bg white -geometry 600*600 congestion1.xg &
	exec xgraph -lw 3 -bg white -geometry 600*600 congestion2.xg &
	exit 0
}

# Schedule
$ns at 0.0 "calcCongestion $tcp0 $oFile1"
$ns at 0.0 "calcCongestion $tcp1 $oFile2"
$ns at 5.0 "$ftp start"
$ns at 5.0 "$telnet start"
$ns at 40.0 "$telnet stop"
$ns at 40.0 "$ftp stop"
$ns at 50.0 "finish"

$ns run