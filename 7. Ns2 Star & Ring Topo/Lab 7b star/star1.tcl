# Create a simulator object
set ns [new Simulator]

# Define different colors for data flows (for NAM)
$ns color 1 Blue
$ns color 2 Red
# Open the NAM file
set nf [open out.nam w]
$ns namtrace-all $nf

# Open the trace file
set tf [open out.tr w]
$ns trace-all $tf

# Define a 'finish' procedure
proc finish {} {
    global ns nf tf
    $ns flush-trace
    # Close the NAM trace file
    close $nf
    close $tf
    # Execute NAM on the trace file
    exec nam out.nam &
    exit 0
}

# Create six nodes
set n(0) [$ns node]  
set n(1) [$ns node]
set n(2) [$ns node]
set n(3) [$ns node]
set n(4) [$ns node]
set n(5) [$ns node]

# Create duplex links to form a Star Topology 
$ns duplex-link $n(0) $n(1) 1Mb 10ms DropTail
$ns duplex-link $n(0) $n(2) 1Mb 10ms DropTail
$ns duplex-link $n(0) $n(3) 1Mb 10ms DropTail
$ns duplex-link $n(0) $n(4) 1Mb 10ms DropTail
$ns duplex-link $n(0) $n(5) 1Mb 10ms DropTail

#Set Queue Size of link (n0-n1) to 10
$ns queue-limit $n(0) $n(1) 2

#Monitor the queue for link (n0-n1). (for NAM)
$ns duplex-link-op $n(0) $n(1) queuePos 0.5

# Setup a TCP connection between node 1 and node 5
set tcp [new Agent/TCP]
$tcp set class_ 3  
$ns attach-agent $n(1) $tcp
set sink [new Agent/TCPSink]
$ns attach-agent $n(5) $sink  
$ns connect $tcp $sink
$tcp set fid_ 1

# Setup a CBR over TCP connection
set cbr [new Application/Traffic/CBR]
$cbr attach-agent $tcp
$cbr set type_ CBR
$cbr set packet_size_ 1000
$cbr set rate_ 1mb
$cbr set random_ false

# Schedule events for the CBR agent
$ns at 0.5 "$cbr start"
$ns at 4.5 "$cbr stop"

# Call the finish procedure after 5 seconds of simulation time
$ns at 5.0 "finish"

# Print CBR packet size and interval
puts "CBR packet size = [$cbr set packet_size_]"
puts "CBR interval = [$cbr set interval_]"

# Run the simulation
$ns run
