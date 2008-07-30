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
from PicvizGui import selection


axiswidth = 130

ui = Ui_MainWindow()
app = QtGui.QApplication(sys.argv)
window = QtGui.QMainWindow()
scene = QtGui.QGraphicsScene()
comboboxes = {}
image = 0


#class Timeout:
#	def __init__(self, last):
#		self.last_timeout = last
#
#	def canActivate(self, time):
#		if int(time) - self.last_timeout > 1:
#			print "update: %d-%d" % (int(time),self.last_timeout)
#		self.last_timeout = int(time)
#
#	def getTimeout(self):
#		return self.last_timeout
#
#	def updateTimeout(self):
#		self.last_timeout = int(time.time())

class PicvizApp(QtGui.QWidget):
    def __init__(self, parent=None):
        QtGui.QWidget.__init__(self, parent)
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)

def ComboIndexChange(widget):
	print "foo"

class AxisName(QtGui.QWidget):
	def __init__(self, parent = None):
		QtGui.QWidget.__init__(self, parent)
		self.combo = QtGui.QComboBox()
		ui.horizontalLayout.addWidget(self.combo)
		self.connect(self.combo, QtCore.SIGNAL('currentIndexChanged(int)'),
				self.indexChanged)

	def setItemName(self, label, id):
		if label:
			self.combo.addItem(label)
		else:
			self.combo.addItem("axis%d" % id)

	def indexChanged(self, id):
		pass
		#print "Change axis id: %d" % id

	def setCurrentIndex(self, i):
		self.combo.setCurrentIndex(i)

def addAxes():
	pen = QtGui.QPen()
	pen.setColor(QtCore.Qt.black)

	item = selection.SelectionItem()
	item.setPos(0,0)
        scene.addItem(item)

	i = 0
	while i < image['axes_number']:
		scene.addLine(i * axiswidth, 0, i * axiswidth, image['height'], pen)
		i = i + 1

def QTColorGet(color):
	if (color == "#000000"):
		return QtCore.Qt.black
	if (color == "#FF0000"):
		return QtCore.Qt.red
	if (color == "#0000FF"):
		return QtCore.Qt.blue
	if (color == "#FF9900"):
		return QtCore.Qt.yellow

	return QtCore.Qt.black

def addLines(show_max):
	pen = QtGui.QPen()

	linecounter = 0
	for line in image['lines']:
		if linecounter == show_max:
			return
		linecounter = linecounter + 1

		plotnb = 0
		for plot in line:
			if plotnb != image['axes_number'] - 1:
				qtcolor = QTColorGet(line[plotnb]['color'])
				pen.setColor(qtcolor)
				ptr = scene.addLine(plotnb * axiswidth, image['height'] - line[plotnb]['y'], (plotnb + 1) * axiswidth, image['height'] - line[plotnb+1]['y'], pen)
				ptr.setToolTip("%s -> %s" % (line[plotnb]['strval'], line[plotnb+1]['strval']))
				ptr.setCursor(QtCore.Qt.OpenHandCursor)
			plotnb = plotnb + 1

def showLines(show_max):
	itemnb = 0
	counter = 0
	for item in scene.items():
		if ((itemnb - 1)/image['axes_number']  == show_max):
			return
		itemnb = itemnb + 1
		item.show()

def update_lines_view(value):
	for item in scene.items():
		item.hide()

	showLines(value)

if __name__ == "__main__":

	if len(sys.argv) < 2:
		print "Syntax: %s file.pcv" % (sys.argv[0])
		sys.exit(1)
	else:
		pcvfile = sys.argv[1]


	image = picviz.ParseImage(pcvfile)

	ui.setupUi(window)
        window.setWindowTitle("Picviz %s Frontend [%s]" % (picviz.Version(), pcvfile))
	window.show()

	scene = QtGui.QGraphicsScene(ui.graphicsView)
	#ui.graphicsView.setRenderHint(QtGui.QPainter.Antialiasing)
	ui.graphicsView.setScene(scene)
	#scene.setSceneRect(0, 0, 875, 500)

	i = 0
	while i < image['axes_number']:
		combo = AxisName(window)
		combo.show()
		for axis in image['axes']:
			combo.setItemName(axis['label'],axis['id'])
		combo.setCurrentIndex(i)

		i = i + 1

	ui.horizontalSlider.setPageStep(1)
	ui.horizontalSlider.setMinimum(0)
	linenb = 0
	for line in image['lines']:
		linenb = linenb + 1
	ui.horizontalSlider.setMaximum(linenb)
	ui.horizontalSlider.setValue(linenb)
	addAxes()
	addLines(linenb)

	window.connect(ui.horizontalSlider, QtCore.SIGNAL('valueChanged(int)'),
			update_lines_view)

	#addLines(window, image)

	sys.exit(app.exec_())

