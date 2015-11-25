# Set Up NS & files required
set ns [new Simulator]

set nf [open 03.nam w]
set tf [open 03.tr w]

$ns trace-all $tf
$ns namtrace-all $nf

# Make 6 nodes
set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]
set n4 [$ns node]
set n5 [$ns node]

# Set up the duplex links
$ns duplex-link $n0 $n2 2Mbps 10ms DropTail
$ns duplex-link $n1 $n2 2Mbps 10ms DropTail
$ns duplex-link $n2 $n3 2Mbps 10ms DropTail
$ns duplex-link $n3 $n4 2Mbps 10ms DropTail
$ns duplex-link $n3 $n5 2Mbps 10ms DropTail

# Orient the links
$ns duplex-link-op $n0 $n2 orient right-down
$ns duplex-link-op $n1 $n2 orient right-up
$ns duplex-link-op $n2 $n3 orient right
$ns duplex-link-op $n3 $n4 orient right-up
$ns duplex-link-op $n3 $n5 orient right-down

# Queue limit (needed only for n2-n3)
$ns queue-limit $n2 $n3 10

# Set up agents
set ping0 [new Agent/Ping]
set ping1 [new Agent/Ping]
set ping4 [new Agent/Ping]
set ping5 [new Agent/Ping]

# Attach agents to nodes
$ns attach-agent $n0 $ping0
$ns attach-agent $n1 $ping1
$ns attach-agent $n4 $ping4
$ns attach-agent $n5 $ping5

# Connect Agents 1-4 and 0-5
$ns connect $ping0 $ping5
$ns connect $ping1 $ping4

# Assign colors & labels etc (optional)
$ns color 1 "Blue"
$ns color 2 "Green"
$ns color 3 "Red"
$ns color 4 "Purple"

$ping0 set class_ 1
$ping1 set class_ 2
$ping4 set class_ 3
$ping5 set class_ 4

# Procedure to run on simulation end
proc finish {} {
	global ns nf tr
	$ns flush-trace
	#exec nam 02.nam &
	exit 0
}

# Procedure for scheduling the sending of ping packets
# Vary intervaltime from 0.002 to 0.05 (in desired steps) and plot against number of packets dropped
set intervaltime 0.005
proc sendpingpacket {} {
	global ns ping0 ping1 ping4 ping5 intervaltime
	set now [$ns now]
	$ns at [expr $now+$intervaltime] "$ping0 send"
	$ns at [expr $now+$intervaltime] "$ping1 send"
	$ns at [expr $now+$intervaltime] "$ping4 send"
	$ns at [expr $now+$intervaltime] "$ping5 send"
	# recursively call this function again
	$ns at [expr $now+$intervaltime] "sendpingpacket"
}

# Define the object level 'recv' function for Agent/Ping
set seq 1
Agent/Ping instproc recv {from rtt} {
	global seq
	$self instvar node_
	#puts "64 Bytes from [$node_ id] icmp_seq=$seq ttl=64 time=$rtt ms"
	set seq [expr $seq + 1]
}

$ns at 1.0 "sendpingpacket"
$ns rtmodel-at 3.0 down $n2 $n3
$ns rtmodel-at 4.0 up $n2 $n3
$ns at 7.0 "finish"

$ns run


