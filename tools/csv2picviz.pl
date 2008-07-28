#!/usr/bin/perl
#
# CSV to Picviz
# (c) Sebastien Tricaud 2008
#

$nb_args = $#ARGV + 1;

if ($nb_args < 2) {
	print "Syntax: csv2picviz.pl filein.csv fileout.pcv\n";
	exit 1;
}

# Put the csv in an array
open(CSV, $ARGV[0]) || die("Could not open file!");
@raw_data=<CSV>;
close(CSV);

print "Is this line the graph header ?\n";
print $raw_data[0];
print "yes/no: ";
$graph_header = <STDIN>;
chomp($graph_header);
print "Please type the field separator: ";
$separator = <STDIN>;
chomp($separator);
print "Set your graph title: ";
$graph_title = <STDIN>;
chomp($graph_title);

open(PCV, ">$ARGV[1]") || die("Could not open file!");

print PCV "header {\n";
print PCV "    title = \"$graph_title\";\n";
print PCV "}\n";

$nbaxes = 1;
$nbaxes++ while $raw_data[0] =~ /$separator/g;

# Write the axis, their type and label
$col_pos = 0;
print PCV "axes {\n";
if ($graph_header =~ m/yes/) {
	@header = split(/$separator/, $raw_data[0]);
	while ($col_pos < $nbaxes) {
		$axis_label = $header[$col_pos];
		chomp($axis_label);
		print "Type the variable for $axis_label: ";
		$var = <STDIN>;
		chomp($var);
		print PCV "    $var axis$col_pos [label=\"$axis_label\"];\n";
		$col_pos++;
	}
	$col_pos = 0;
	splice(@raw_data, 0, 1);
} else {
	while ($col_pos < $nbaxes) {
		print PCV "    string axis$col_pos;\n";
		$col_pos++;
	}
}
print PCV "}\n";

# Write data
print PCV "data {\n";
foreach $line (@raw_data) {
	@items = split(/$separator/, $line);
	$col_pos = 0;
	while ($col_pos < $nbaxes) {
		$item = $items[$col_pos];
		chomp($item);
		$item =~ s/\"|&|<|>/\\"/g; # We escape our quotes
		if ( $col_pos != $nbaxes - 1) {
			print PCV " axis$col_pos=\"$item\", ";
		} else {
			print PCV " axis$col_pos=\"$item\";\n";
		}
		$col_pos++;
	}
}

print PCV "}\n";


close(PCV);

