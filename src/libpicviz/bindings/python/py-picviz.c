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

#include <stdio.h>

#include <picviz.h>
#include <linuxlist.h>

#include "py-picviz.h"

PyObject *pypicviz_version_get(PyObject *self, PyObject *args)
{
	PyObject *py_result = Py_BuildValue("s", PICVIZ_PYTHON_VERSION);
	return py_result;
}

int pypicviz_dict_keyval_append_str(PyObject *dict, char *key, char *val)
{
        PyObject *value;
        int ret;

        value = PyString_FromString(val);

        ret = PyDict_SetItemString(dict, key, value);
        if (ret < 0) {
                fprintf(stderr, "[PYTHON_BINDINGS]: Can not append value '%s' to '%s'", val, key);
        }

        return ret;
}

int pypicviz_dict_keyval_append_long(PyObject *dict, char *key, long val)
{
        PyObject *value;
        int ret;

        value = PyInt_FromLong(val);

        ret = PyDict_SetItemString(dict, key, value);
        if (ret < 0) {
                fprintf(stderr, "[PYTHON_BINDINGS]: Can not append value '%li' to '%s'", val, key);
        }

        return ret;
}

PyObject *pypicviz_lines_list_build_from_file(PyObject *self, PyObject *args)
{
        int ret;
	char *filename;
	struct pcimage_t *image;
	struct axis_t *axis;
        struct line_t *line;
        struct axisplot_t *axisplot;
        unsigned int ui = 0;

        PyObject *main_dict = PyDict_New();
        PyObject *axeslist = PyList_New(0);
        PyObject *lineslist = PyList_New(0);
        //PyObject *linedata = PyDict_New();
        //PyObject *lineprops = PyDict_New();

	picviz_init();
	PyArg_ParseTuple(args, "s", &filename);

	image = (struct pcimage_t *)pcv_parse(filename);
	if ( ! image ) {
		fprintf(stderr, "Cannot create image");
		Py_RETURN_NONE;
	}

        /* Set Image properties */
        ret = pypicviz_dict_keyval_append_long(main_dict, "height", image->height);
        if (ret < 0)
                Py_RETURN_NONE;

        /* Set axes */
	llist_for_each_entry(axis, &image->axes->list, list) {
		PyObject *axisdata = PyDict_New();
		ret = pypicviz_dict_keyval_append_long(axisdata, "id", axis->id);
                if (ret < 0) {
                        Py_RETURN_NONE;
                }
		ret = pypicviz_dict_keyval_append_str(axisdata, "label", axis->props->label);
                if (ret < 0) {
                        Py_RETURN_NONE;
                }
                ui++;
		PyList_Append(axeslist, axisdata);
        }
        ret = pypicviz_dict_keyval_append_long(main_dict, "axes_number", ui);
        if (ret < 0)
                Py_RETURN_NONE;

        ret = PyDict_SetItemString(main_dict, "axes", axeslist);

        /* Set Lines plots and properties */
	llist_for_each_entry(line, &image->lines->list, list) {
                PyObject *axisplotlist = PyList_New(0);
                //ret = pypicviz_dict_keyval_append_long(linedata, "id", line->id);
                //if (ret < 0) {
                //        Py_RETURN_NONE;
                //}
                //ret = pypicviz_dict_keyval_append_str(linedata, "color", line->props->color);
                //if (ret < 0) {
                //        Py_RETURN_NONE;
                //}
                /* Set Line plots */
		llist_for_each_entry(axisplot, &line->axisplot->list, list) {
                        PyObject *plotsdata = PyDict_New();
			/* We add the color information along with plots, to ease the line creation with QT */
			ret = pypicviz_dict_keyval_append_str(plotsdata, "color", line->props->color);
			if (ret < 0) {
				Py_RETURN_NONE;
			}
                        ret = pypicviz_dict_keyval_append_str(plotsdata, "strval", axisplot->strval);
                        if (ret < 0) {
                                Py_RETURN_NONE;
                        }
                        ret = pypicviz_dict_keyval_append_long(plotsdata, "y", axisplot->y);
                        if (ret < 0) {
                                Py_RETURN_NONE;
                        }
                        ret = pypicviz_dict_keyval_append_long(plotsdata, "axis_id", axisplot->axis_id);
                        if (ret < 0) {
                                Py_RETURN_NONE;
                        }
			PyList_Append(axisplotlist, plotsdata);

		}
		PyList_Append(linedata, axisplotlist);
	}
        PyList_Append(lineslist, linedata);
        ret = PyDict_SetItemString(main_dict, "lines", lineslist);

	picviz_image_destroy(image);

	return main_dict;
}


/****************
 * Method table *
 ****************/
static PyMethodDef picvizMethods[] =
{
    { "Version", pypicviz_version_get, METH_VARARGS,
      "Returns the Picviz version"},
    { "ParseImage", pypicviz_lines_list_build_from_file, METH_VARARGS,
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

