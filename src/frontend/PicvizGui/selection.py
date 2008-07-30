from PyQt4 import QtCore, QtGui

class SelectionItem(QtGui.QGraphicsItem):
	def __init__(self):
		QtGui.QGraphicsItem.__init__(self)
		self.color = QtGui.QColor(QtCore.qrand() % 256, QtCore.qrand() % 256,
				QtCore.qrand() % 256)
		self.setToolTip("Drag this item over the axis to remove lines")
		self.setCursor(QtCore.Qt.OpenHandCursor)

	def boundingRect(self):
        	return QtCore.QRectF(-20, 2, 20, -2)

	def paint(self, painter, option, widget):
		painter.setPen(QtGui.QPen(QtCore.Qt.black, 1))
		painter.setBrush(QtGui.QBrush(self.color))
		painter.drawLine(-20, 0, 20, 0)

