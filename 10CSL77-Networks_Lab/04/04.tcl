# Set Up NS & files required
set ns [new Simulator]

set nf [open 04.nam w]
set tf [open 04.tr w]

$ns trace-all $tf
$ns namtrace-all $nf

# Set the number of nodes (n = 6 to 10 | according to the question) Let's use n=10
set numNodes 10

# Make 10 nodes - using a for loop to make an array of 10 nodes n(0) to n(9)
for {set i 0} {$i < $numNodes} {incr i} {
	set n($i) [$ns node]
}

# Build 2 ethernet lans of 5 nodes each
# make-lan function & parameters : make-lan {nodes bw delay lltype ifqtype mactype chantype}
# nodes : list of nodes in lan ; bandwidth, delay; lltype : Link Layer type (object for the link layer) ; 
# ifqtype : the interface queue type, here a normal DropTail; mactype : Mac layer object, here Ethernet 
# from IEEE Mac 802.3 Specification; chantype : physical layer channel object not used
$ns make-lan "$n(5) $n(6) $n(7) $n(8) $n(9)" 10Mb 20ms LL Queue/DropTail Mac/802_3
$ns make-lan "$n(0) $n(1) $n(2) $n(3) $n(4)" 10Mb 20ms LL Queue/DropTail Mac/802_3

# Data Rate for the LAN
Mac/802_3 set dataRate_ 10Mb

# Now connect the two lans via a duplex link between n(4) & n(5)
$ns duplex-link $n(4) $n(5) 2Mb 10ms DropTail

# Set the Error Model & error rate [vary this for graph]
set err [new ErrorModel]
$ns lossmodel $err $n(4) $n(5)
$err set rate_ 0.6

# Make agents & application
set tcp [new Agent/TCP]
set udp [new Agent/UDP]
set sink [new Agent/TCPSink]
set null [new Agent/Null]

set cbr [new Application/Traffic/CBR]
set ftp [new Application/FTP]

# Attach agents to different lans
$ns attach-agent $n(6) $tcp
$ns attach-agent $n(0) $udp
$ns attach-agent $n(3) $sink
$ns attach-agent $n(9) $null

# Attach the applications
$ftp attach-agent $tcp
$cbr attach-agent $udp

# Add labels for distinction
$n(6) label "TCP-FTP"
$n(0) label "UDP-CBR"
$n(3) label "Sink"
$n(9) label "Null"

# Additional parameters for connection
$cbr set interval_ 0.001
$cbr set packetSize_ 1000
$ftp set size_ 1000

# Connect the agents 
$ns connect $tcp $sink
$ns connect $udp $null

# Colors etc (optional)
$ns color 1 "Red"
$ns color 2 "Blue"
$tcp set class_ 1
$udp set class_ 2

# Procedure to run on simulation end
proc finish {} {
	global ns nf tr
	$ns flush-trace
	#exec nam 04.nam &
	exit 0
}

# Schedule
$ns at 0.0 "$cbr start"
$ns at 0.0 "$ftp start"
$ns at 18.0 "$cbr stop"
$ns at 18.0 "$ftp stop"
$ns at 20.0 "finish"

$ns run