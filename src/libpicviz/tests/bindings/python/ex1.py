#!/usr/bin/env python

import picviz

filename = "test1.pcv"
lnb = 0
dnb = 0

print "Picviz Python API version: %s" % picviz.Version()
print "Loading file '%s'" % filename
data = picviz.ParseLines(filename)
for i in data:
	lnb = lnb + 1
	for j in i:
		dnb = dnb + 1
	print "Data for line %d: %s" % (lnb, str(i))

print "There are %d lines." % lnb

