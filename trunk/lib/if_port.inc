sub if_port {
	my ($item, @data) = @_;
	use Device::ParallelPort;
	my $port = Device::ParallelPort->new('auto:0');

	sub status {
		my ($port) = @_;
		my $out = "<div class=\"sta_info\">".ord($port->get_byte(0))."</div>";
		my $bit;
		for $bit ( 0 .. (scalar(@pin) - 1) ) {
			my ($type, $num) = split('_', $pin[$bit]);
			if ( $port->get_bit($bit) ) {
				$out .= "<div class=\"".$type."_on\" onclick=\"handler( [\'args__port\', \'args__switch\', \'args__".$bit."\', \'args__0\'], ['status', 'debug' ] )\;\">".$type." ".$num."</div>";
			}
			else {
				$out .= "<div class=\"".$type."_off\" onclick=\"handler( [\'args__port\',\'args__switch\', \'args__".$bit."\', \'args__1\'], ['status', 'debug' ] )\;\">".$type." ".$num."</div>";
			}
		}
		$out .= "<div class=\"sta_ref\" onclick=\"handler( [ \'args__port\', \'args__status\' ], ['status', 'debug'] )\;\"></div>";
		return($out);
	}

	sub switch {
	        my ($port,  $item, $turn ) = @_;
		return($port->set_bit($item, $turn));
	}

	if ( $item eq "status" ) {
		return(&status($port));
	}

	if ( $item eq "switch" ) {
		return(&switch($port, @data));
	}

	else {
		return("NOTHING");
	}
}



sub irrigate {
        my ($port,  $item, $delay ) = @_;
        $port->set_bit($item, 1);
        sleep $delay;
        $port->set_bit($item, 0);
}

1;
