#!/usr/bin/perl
  
use strict;
use CGI;      # or any other CGI:: form handler/decoder
use CGI::Ajax;

my $cgi = new CGI;
my $pjx = new CGI::Ajax( 'handler' => \&handler );
# $pjx->DEBUG(1);
print $pjx->build_html( $cgi, \&Show_HTML);

sub handler {
	my ($action, $item, @data) = @_;

	our @pin = (
		'light_0',
		'light_1',
		'cooler_0',
		'light_2',
		'valve_1',
		'valve_2',
		'valve_3',
		'valve_4',
	);

	if ( $action eq "port" ) {
		require('lib/if_port.inc');
		my $debug = &if_port($item, @data);
		my $status = &if_port('status');
		return($status, $debug);
	}
	elsif ( $action eq "ct" ) {
		require('lib/if_ct.inc');
		my $debug = &crontab($item, @data);
		my $list = &crontab('list');
		return($list, $debug)
	}
	else {
		return("Nothing to say!");
	}
}

sub Show_HTML {
	my $html = <<EOHTML;
<HTML>
<HEAD>
<LINK href="skin/default/style.css" rel="stylesheet" type="text/css">
</HEAD>
<BODY>
<div id="status"></div>
<div id="video"><img src="http://192.168.7.10:8081"></div>
<div id="crontab"></div>
<div id="debug"></div>
</BODY>
<SCRIPT LANGUAGE="JavaScript" TYPE="TEXT/JAVASCRIPT">
<!--

handler( ['args__port', 'args__status'], ['status', 'debug'] );
handler( ['args__ct', 'args__list'], ['crontab', 'debug'] );

//-->
</SCRIPT>
</HTML>
EOHTML
	return $html;
}

