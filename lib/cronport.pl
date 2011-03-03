#!/usr/bin/perl -w
my ($item, $what) = @ARGV;
use Device::ParallelPort;
my $port = Device::ParallelPort->new('auto:0');

if ( $what < 2 ) {
        $port->set_bit($item, $what);
}

else {
        $port->set_bit($item, 1);
        sleep $what;
        $port->set_bit($item, 0);
}

