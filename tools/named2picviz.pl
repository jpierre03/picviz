#!/usr/bin/perl
#
# For python folks: show me the equivalent code for this
#

print "header {\n";
print "    title = \"Syslog picviz analysis\";\n";
print "}\n";

print "axes {\n";
print "    timeline t [label=\"Timeline\"];\n";
print "    string   cat [label=\"Category\"];\n";
print "    ipv4     source [label=\"Source\"];\n";
print "    string   log [label=\"Log\"];\n";
print "}\n";

print "data {\n";

while ($line = <>) {

	$typed = 0;

        $line =~ s/\"/\\"/g; # We escape our quotes
        $line =~ s/&//g; # We escape our quotes
        $line =~ s/<//g; # We escape our quotes
        $line =~ s/>//g; # We escape our quotes
	$line =~ m/.* (\d+:\d+:\d+).\d+ (\S+): (\S+): \S+ (\d+.\d+.\d+.\d+)#\d+: (.*)/;

        $t=$1;
        $cat=$2;
	$msgtype=$3; # info, warning, error
        $source=$4;
        $log=$5;

	# 29-Jul-2008 09:14:09.692 update-security: error: client 84.91.74.38#32773: update 'mylinux.net/IN' denied
        if ($msgtype =~ m/error/) {
		print "t=\"$t\", cat=\"$cat\", source=\"$source\", log=\"$log\" [color=\"red\"];\n";
		$typed = 1;
        }
	if ($msgtype =~ m/warning/) {
		print "t=\"$t\", cat=\"$cat\", source=\"$source\", log=\"$log\" [color=\"orange\"];\n";
		$typed = 1;
        }
	if ($msgtype =~ m/info/) {
		print "t=\"$t\", cat=\"$cat\", source=\"$source\", log=\"$log\" [color=\"blue\"];\n";
		$typed = 1;
        }

	if ($typed == 0) {
		print "t=\"$t\", cat=\"$cat\", source=\"$source\", log=\"$log\";\n";
	}
}

print "}\n";

