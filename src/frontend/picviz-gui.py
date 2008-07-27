#!/usr/bin/env python
#
######################
# Frontend for Picviz
######################
# (C) 2008 Sebastien Tricaud
#

# Python libs
import os
import sys
import time

# QT
from PyQt4 import QtCore, QtGui

# Picviz
import picviz

# UI
from ui_picviz import Ui_MainWindow


axiswidth = 130

ui = Ui_MainWindow()
scene = QtGui.QGraphicsScene()


class PicvizApp(QtGui.QWidget):
    def __init__(self, parent=None):
        QtGui.QWidget.__init__(self, parent)
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)

#class LineItem(QtGui.QGraphicsItem):
#	pen = QtGui.QPen()
#
#	def __init__(self):
#		QtGui.QGraphicsItem.__init__(self)
#		self.setToolTip("Test")
#		self.pen.setColor(QtCore.Qt.black)
#
#	def setCoordinates(self, axis1, y1, axis2, y2):
#		self.addLine(axis1, y1, axis2, y2, self.pen)


def addLines(filename):
	pen = QtGui.QPen()
	pen.setColor(QtCore.Qt.black)

	image = picviz.ParseImage(filename)

	i = 0
	while i < image['axes_number']:
		scene.addLine(i * axiswidth, 0, i * axiswidth, image['height'], pen)
		i = i + 1

	for line in image['lines']:
		plotnb = 0
		for plot in line:
			if plotnb != image['axes_number'] - 1:
				ptr = scene.addLine(plotnb * axiswidth, image['height'] - line[plotnb]['y'], (plotnb + 1) * axiswidth, image['height'] - line[plotnb+1]['y'])
				ptr.setToolTip("%s -> %s" % (line[plotnb]['strval'], line[plotnb+1]['strval']))
				ptr.setCursor(QtCore.Qt.OpenHandCursor)
			plotnb = plotnb + 1

if __name__ == "__main__":

	if len(sys.argv) < 2:
		print "Syntax: %s file.pcv" % (sys.argv[0])
		sys.exit(1)
	else:
		pcvfile = sys.argv[1]

	app = QtGui.QApplication(sys.argv)
	window = QtGui.QMainWindow()

	ui.setupUi(window)
        window.setWindowTitle("Picviz %s Frontend [%s]" % (picviz.Version(), pcvfile))

	scene = QtGui.QGraphicsScene(ui.graphicsView)
	ui.graphicsView.setRenderHint(QtGui.QPainter.Antialiasing)
	ui.graphicsView.setScene(scene)
	#scene.setSceneRect(0, 0, 875, 500)

	window.show()

	addLines(pcvfile)

	sys.exit(app.exec_())

