from PyQt4 import QtCore, QtGui

import selection, defaults

class AxisName(QtGui.QWidget):
	def __init__(self, ui, parent = None):
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


def addAxes(image, scene):
	pen = QtGui.QPen()
	pen.setColor(QtCore.Qt.black)

	item = selection.SelectionItem()
	item.setPos(0,0)
        scene.addItem(item)

	i = 0
	while i < image['axes_number']:
		scene.addLine(i * defaults.axiswidth, 0, i * defaults.axiswidth, image['height'], pen)
		i = i + 1

