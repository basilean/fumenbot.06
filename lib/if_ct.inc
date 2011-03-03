sub crontab {
	my ($item, @data) = @_;
	use Config::Crontab;
	my $ct = new Config::Crontab;
	$ct->read;

	sub list {
		my ($ct) = @_;
		my $out;
		for my $line ($ct->select) {
			if ( $line->active ) {
				$out .= "<div class=\"event\">";
				$out .= "<div class=\"hour\">".$line->hour."h</div>";
				$out .= "<div class=\"min\">".$line->minute."m</div>";
				my ($command, $bit, $what) = split (' ', $line->command);
				my $turn;
				if ( $what ==  0 ) { $turn = "off" }
				elsif ( $what ==  1 ) { $turn = "on" }
				else { $turn = "delay" }
				my ($type, $num) = split('_', $pin[$bit]);
				$out .= "<div class=\"item_".$turn."\">".$type." ".$num;
				if ( $turn eq "delay" ) { $out .= "<div>".$what."</div>"; }
				$out .= "</div>";
				$out .= "<div class=\"del\" onclick=\"handler( [\'args__ct\', \'args__del\', \'args__".$line->data."\'], ['crontab', 'debug'] )\;\"></div>";
			}
			else {
				$out .= "<div class=\"com\">";
				$out .= "<div>".$line->dump."</div>";
			}
			$out .= "</div>";
		}

		$out .= "<div class=\"event\"><div class=\"hour\"><select id=\"hour\"><option value=\"*\">*</option>";
		for my $hour ( 0 .. 23 ) {
			$out .= "<option value=\"".$hour."\">".$hour."</option>";
		}
		$out .= "</select></div><div class=\"min\"><select id=\"min\">";
		for my $min ( 0 .. 59 ) {
			$out .= "<option value=\"".$min."\">".$min."</option>";
		}
		$out .= "</select></div><div class=\"item_new\"><select id=\"item\">";
		for my $bit ( 0 .. (scalar(@pin) - 1) ) {
			my ($type, $num) = split('_', $pin[$bit]);
			$out .= "<option value=\"".$bit."\">".$type." ".$num."</option>";
		}
		$out .= "</select><select id=\"data\"><option value=\"0\">off</option><option value=\"1\">on</option>";
		for my $what ( 2 .. 9 ) {
			$out .= "<option value=\"".$what."\">".$what."s</option>";
		}
		$out .= "</select></div><div class=\"add\" onclick=\"handler( [\'args__ct\', \'args__add\', \'min\', \'hour\', \'item\', \'data\'], ['crontab', 'debug'] )\;\"></div></div>";
		return($out);
	}

	if ( $item eq "list" ) {
		return(&list($ct));
	}
	elsif ( $item eq "add" ) {
		my ($min, $hour, $bit, $what) = @data;
		my $temp = "$min $hour * * * /var/www/lib/cronport.pl $bit $what";
		$ct->last(new Config::Crontab::Block(-data => $temp));
		return($ct->write);
	}
	elsif ( $item eq "del" ) {
		my ($line) = @data;
		my ($match) = $ct->select(-data => $line);
		$ct->remove($match);
		return($ct->write);
	}
	else {
		return("NOTHING");
	}
}
1;

