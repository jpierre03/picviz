#!/usr/bin/perl
#
# For python folks: show me the equivalent code for this
#

print "header {\n";
print "    title = \"Syslog picviz analysis\";\n";
print "}\n";

print "axes {\n";
print "    timeline t;\n"; # Time
print "    string   m;\n"; # Machine
print "    string   a;\n"; # Application
print "    string   l;\n"; # Log
print "}\n";

print "data {\n";

while ($line = <>) {

        $line =~ s/\"/\\"/g; # We escape our quotes
        $line =~ s/&//g; # We escape our quotes
        $line =~ s/<//g; # We escape our quotes
        $line =~ s/>//g; # We escape our quotes
        $line =~ m/\w+ \d+ (\d+:\d+):\d+ (\w+) (\S+) (.*)/;

        $t=$1;
        $m=$2;
        $a=$3;
        $l=$4;

        if ($a =~ m/.*kernel.*/) {
                print "    t=\"$t\",m=\"$m\",a=\"$a\",l=\"$l\" [color=\"red\"];\n";
        } else {
                        print "    t=\"$t\",m=\"$m\",a=\"$a\",l=\"$l\";\n";
        }
}

print "}\n";

