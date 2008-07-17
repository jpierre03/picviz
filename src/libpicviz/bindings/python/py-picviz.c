/*
 * Picviz - Parallel coordinates ploter
 * Copyright (C) 2008 Sebastien Tricaud <toady@gscore.org>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <Python.h>

#include <picviz.h>
#include <linuxlist.h>

#include "py-picviz.h"

PyObject *pypicviz_version_get(PyObject *self, PyObject *args)
{
	PyObject *py_result = Py_BuildValue("s", PICVIZ_PYTHON_VERSION);
	return py_result;
}

PyObject *pypicviz_lines_list_build_from_file(PyObject *self, PyObject *args)
{
	char *filename;
	struct pcimage_t *image;
        struct line_t *line;
        struct axisplot_t *axisplot;


	PyObject *main_list = PyList_New(0);

	picviz_init();
	PyArg_ParseTuple(args, "s", &filename);

	image = (struct pcimage_t *)pcv_parse(filename);

	llist_for_each_entry(line, &image->lines->list, list) {
		PyObject *axisplot_list = PyList_New(0);
		llist_for_each_entry(axisplot, &line->axisplot->list, list) {
			PyList_Append(axisplot_list, PyInt_FromLong(axisplot->y));
		}
		PyList_Append(main_list, axisplot_list);
	}

	picviz_image_destroy(image);

	return main_list;
}


/****************
 * Method table *
 ****************/
static PyMethodDef picvizMethods[] =
{
    { "Version", pypicviz_version_get, METH_VARARGS,
      "Returns the Picviz version"},
    { "ParseLines", pypicviz_lines_list_build_from_file, METH_VARARGS,
      "Parse lines from the file"},

    {NULL,NULL}
};


#ifdef WIN32
__declspec(dllexport)
#endif
void initpicviz(void)
{
 	PyObject *m, *d;


	m = Py_InitModule4("picviz",
			picvizMethods,
			"Parse, Render and Manipulate data from Picviz",
			0,
			PYTHON_API_VERSION);

	d = PyModule_GetDict(m);

}

