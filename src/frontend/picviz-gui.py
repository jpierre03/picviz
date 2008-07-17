#!/usr/bin/env python
#
######################
# Frontend for Picviz
######################
# (C) 2008 Sebastien Tricaud
#

import os
import sys
import time

from PyQt4 import QtCore, QtGui

from ui_picviz import Ui_MainWindow

ui = Ui_MainWindow()
scene = QtGui.QGraphicsScene()

line1_text = "timeline"
line1_x = 80
line2_text = "alert.source(0).node.address(0).address"
line2_x = 260
line3_text = "alert.target(0).node.address(0).address"
line3_x = 440
line4_text = "alert.classification.text"
line4_x = 620
line5_text = "alert.assessment.impact.description"
line5_x = 780

def draw_default_layout(scene):
	for item in scene.items():
		scene.removeItem(item)

	scene.addLine(line1_x,0,line1_x,500)
	scene.addLine(line2_x,0,line2_x,500)
	scene.addLine(line3_x,0,line3_x,500)
	scene.addLine(line4_x,0,line4_x,500)
	scene.addLine(line5_x,0,line5_x,500)


def colorize_impact_severity(idmef):

	severity = idmef.Get("alert.assessment.impact.severity")

	if severity == "high":
		return QtCore.Qt.red
	if severity == "medium":
		return QtCore.Qt.yellow
	if severity == "low":
		return QtCore.Qt.green
	if severity == "info":
		return QtCore.Qt.blue

def idmef_message_plot(idmef, path):

	if path == "timeline":
		return plot_timeline()
	message = idmef.Get(path)

	if sre.match(".*.address", path):
		return plot_ip_addr(message)

	if sre.match(".*.impact.severity", path):
		return plot_impact_severity(message)

	return text_pos(message)


def handle_alert(idmef):

# Draw the line with severity color
	pen = QtGui.QPen()
	pen.setColor(colorize_impact_severity(idmef))

	scene.addLine(line1_x, idmef_message_plot(idmef, str(ui.lineEdit1.text())),
			line2_x, idmef_message_plot(idmef, str(ui.lineEdit2.text())),
			pen)
	scene.addLine(line2_x, idmef_message_plot(idmef, str(ui.lineEdit2.text())),
			line3_x, idmef_message_plot(idmef, str(ui.lineEdit3.text())),
			pen)
	scene.addLine(line3_x, idmef_message_plot(idmef, str(ui.lineEdit3.text())),
			line4_x, idmef_message_plot(idmef, str(ui.lineEdit4.text())),
			pen)
	scene.addLine(line4_x, idmef_message_plot(idmef, str(ui.lineEdit4.text())),
			line5_x, idmef_message_plot(idmef, str(ui.lineEdit5.text())),
			pen)

def run_files_load():
    src_dir = sys.argv[1]
    for root, dirs, files in os.walk(src_dir):
        for name in files:
            if name.endswith(".idmef"):
                idmef = PreludeEasy.IDMEF()
                idmef.ReadFromFile(src_dir + name)
                handle_alert(idmef)

class PigApp(QtGui.QWidget):
    def __init__(self, parent=None):
        QtGui.QWidget.__init__(self, parent)
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)

def entry1Clicked():
	line1_text = ui.lineEdit1.text()
	if mode == "files":
		draw_default_layout(scene)
		run_files_load()
	else:
		draw_default_layout(scene)
def entry2Clicked():
	line2_text = ui.lineEdit2.text()
	if mode == "files":
		draw_default_layout(scene)
		run_files_load()
	else:
		draw_default_layout(scene)
def entry3Clicked():
	line3_text = ui.lineEdit3.text()
	if mode == "files":
		draw_default_layout(scene)
		run_files_load()
	else:
		draw_default_layout(scene)
def entry4Clicked():
	line4_text = ui.lineEdit4.text()
	if mode == "files":
		draw_default_layout(scene)
		run_files_load()
	else:
		draw_default_layout(scene)
def entry5Clicked():
	line5_text = ui.lineEdit5.text()
	if mode == "files":
		draw_default_layout(scene)
		run_files_load()
	else:
		draw_default_layout(scene)



if __name__ == "__main__":
    app = QtGui.QApplication(sys.argv)
    window = QtGui.QMainWindow()

    ui.setupUi(window)
    ui.lineEdit1.setText(line1_text)
    ui.lineEdit2.setText(line2_text)
    ui.lineEdit3.setText(line3_text)
    ui.lineEdit4.setText(line4_text)
    ui.lineEdit5.setText(line5_text)

    scene = QtGui.QGraphicsScene(ui.graphicsView)
    ui.graphicsView.setScene(scene)
    scene.setSceneRect(0, 0, 875, 500)

    draw_default_layout(scene)

    window.show()
    window.connect(ui.lineEdit1, QtCore.SIGNAL("returnPressed()"),
                        entry1Clicked)
    window.connect(ui.lineEdit2, QtCore.SIGNAL("returnPressed()"),
                        entry2Clicked)
    window.connect(ui.lineEdit3, QtCore.SIGNAL("returnPressed()"),
                        entry3Clicked)
    window.connect(ui.lineEdit4, QtCore.SIGNAL("returnPressed()"),
                        entry4Clicked)
    window.connect(ui.lineEdit5, QtCore.SIGNAL("returnPressed()"),
                        entry5Clicked)


    if len(sys.argv) > 1:
        mode = "files"
        run_files_load()
#    else:
#        pigTimer = QtCore.QTimer();
#        window.connect(pigTimer, QtCore.SIGNAL("timeout()"), PreludeTimer);
#        pigTimer.start(0);
#

    sys.exit(app.exec_())

