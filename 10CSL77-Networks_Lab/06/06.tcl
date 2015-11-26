#check number of arguments
if {$argc!=1} {
	error "usage: ns 06.tcl <num_nodes>"
	exit 0
}

#set up the parameters for nodes etc
#To remember order: A L M I I A P PH T C | agent on, router on, mac off, move off
set val(rp) AODV
set val(ll) LL
set val(mac) Mac/802_11
set val(ifq) Queue/DropTail/PriQueue
set val(ifqlen) 50
set val(ant) Antenna/OmniAntenna
set val(prop) Propagation/TwoRayGround
set val(netif) Phy/WirelessPhy
# t is Topo instance - create later
set val(chan) Channel/WirelessChannel

# Other values
set val(nn) [lindex $argv 0]
set opt(x) 750
set opt(y) 750
set val(stop) 100

set ns [new Simulator]
set nf [open 06.nam w]
set tf [open 06.tr w]

$ns trace-all $tf
$ns namtrace-all-wireless $nf $opt(x) $opt(y)

# Create topo instance
set topo [new Topography]
$topo load_flatgrid $opt(x) $opt(y)

# Create god object
set god [create-god $val(nn)]

# Configure node objects
$ns node-config -adhocRouting $val(rp) \
-llType $val(ll) \
-macType $val(mac) \
-ifqType $val(ifq) \
-ifqLen $val(ifqlen) \
-antType $val(ant) \
-propType $val(prop) \
-phyType $val(netif) \
-topoInstance $topo \
-channelType $val(chan) \
-agentTrace ON \
-routerTrace ON \
-macTrace OFF \
-movementTrace OFF

# Create the nodes & set their initial features
for {set i 0} {$i < $val(nn)} {incr i} {
	set n($i) [$ns node]
	$n($i) random-motion 1

	# inital position
	set xx [expr rand()*$opt(x)]
	set yy [expr rand()*$opt(y)]
	$n($i) set X_ $xx
	$n($i) set Y_ $yy

	# initial size
	$ns initial_node_pos $n($i) 40
}

# Pick random src & dest nodes
set src [expr int(rand()*$val(nn))]
set des [expr int(rand()*$val(nn))]

puts "\n\nSource: $src\nDest: $des\n\n"

set tcp [new Agent/TCP]
set sink [new Agent/TCPSink]
set ftp [new Application/FTP]

$ns attach-agent $n($src) $tcp
$ns attach-agent $n($des) $sink
$ftp attach-agent $tcp

$ns connect $tcp $sink

proc finish {} {
	global ns tr nf 
	$ns flush-trace
	exec nam 06.nam &
	exit 0
}

proc nodeMovRandom {} {
	global ns val n opt
	set now [$ns now]
	set interval 5.0

	for {set i 0} {$i<$val(nn)} {incr i} {
		# generate random x, y
		set xx [expr rand()*$opt(x)]
		set yy [expr rand()*$opt(y)]

		$ns at [expr $now+$interval] "$n($i) setdest $xx $yy 20.0"
	}

	$ns at [expr $now+$interval] "nodeMovRandom"
}

$ns at 0.0 "nodeMovRandom"
$ns at 5.0 "$ftp start"
$ns at 90.0 "$ftp stop"

for {set i 0} {$i<$val(nn)} {incr i} {
	$ns at $val(stop) "$n($i) reset"
}

$ns at $val(stop) "finish"

$ns run
