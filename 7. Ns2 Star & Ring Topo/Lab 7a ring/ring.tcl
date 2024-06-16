#Create a simulator object

set ns [new Simulator]

#Define different colors for data flows (for NAM)

$ns color 1 Blue

$ns color 2 Red

#Open the NAM file

set nf [open out.nam w]

$ns namtrace-all $nf

#Open the trace file

set tf [open out.tr w]

$ns trace-all $tf

#Define a 'finish' procedure

proc finish {} {

global ns nf tf

$ns flush-trace

#Close the NAM trace file

close $nf

close $tf

#Execute NAM on the trace file

exec nam out.nam &

exit 0

}

#Create six nodes

set n0 [$ns node]

set n1 [$ns node]

set n2 [$ns node]

set n3 [$ns node]

set n4 [$ns node]

set n5 [$ns node]

#Create duplex links between the nodes to form a Ring Topology

$ns duplex-link $n0 $n1 1Mb 10ms DropTail

$ns duplex-link $n1 $n2 1Mb 10ms DropTail

$ns duplex-link $n2 $n3 1Mb 10ms DropTail

$ns duplex-link $n3 $n4 1Mb 10ms DropTail

$ns duplex-link $n4 $n5 1Mb 10ms DropTail

$ns duplex-link $n5 $n0 1Mb 10ms DropTail

#Setup a TCP connection between node 1 and node 4

set tcp [new Agent/TCP]

$tcp set class_ 2

$ns attach-agent $n1 $tcp

set sink [new Agent/TCPSink]

$ns attach-agent $n4 $sink

$ns connect $tcp $sink

$tcp set fid_ 1

#Setup a CBR over TCP connection

set cbr [new Application/Traffic/CBR]

$cbr attach-agent $tcp

$cbr set type_ CBR

$cbr set packet_size_ 1000

$cbr set rate_ 1mb

$cbr set random_ false

#Schedule events for the CBR agent

$ns at 0.1 "$cbr start"

$ns at 4.5 "$cbr stop"

#Detach tcp and sink agents (not really necessary)

$ns at 4.5 "$ns detach-agent $n1 $tcp ; $ns detach-agent $n4 $sink"

#Call the finish procedure after 5 seconds of simulation time

$ns at 5.0 "finish"

#Print CBR packet size and interval

puts "CBR packet size = [$cbr set packet_size_]"

puts "CBR interval = [$cbr set interval_]"

#Run the simulation

$ns run

