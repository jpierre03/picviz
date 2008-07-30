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

	def mousePressEvent(self, event):
        	if event.button() != QtCore.Qt.LeftButton:
            		event.ignore()
            		return

		print "Mouse pressed"

        	drag = QtGui.QDrag(event.widget())
        	mime = QtCore.QMimeData()
        	drag.setMimeData(mime)

		drag.start()

	def dragEnterEvent(self, event):
		print "Enter event"

	def dragLeaveEvent(self, event):
		print "Leave event"

	def dropEvent(self, event):
		print "Drop event"
