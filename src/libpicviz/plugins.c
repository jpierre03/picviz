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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dlfcn.h>

#include <math.h>

#include <debug.h>
#include <linuxlist.h>
#include <plugins.h>


void picviz_plugin_load(char *plugin_name, pcimage_t *image)
{
	char *plugin_path;
	char plugin_full[1024];
	void *dlh;
	void (*func)(pcimage_t *);

#if 0
	plugin_path = getenv("PICVIZ_PLUGINS_PATH");
	if (!plugin_path) // no env variable, we let ld do its job
		plugin_full = (char *)plugin_name;
	else
		sprintf(plugin_full, "%s/%s", plugin_path, plugin_name);
#endif

	dlh = dlopen(plugin_name, RTLD_LAZY);
	if ( ! dlh ) {
		fprintf(stderr, "Cannot open plugin: %s\n", dlerror());
		exit(EXIT_FAILURE);
	}

	*(void **)(&func) = dlsym(dlh, "output");
	if ( ! func ) {
		fprintf(stderr, "Symbol output not found in '%s'\n", plugin_full);
		exit(EXIT_FAILURE);
	}

	(*func)(image);

	dlerror();    /* Clear any existing error */

	dlclose(dlh);

}

#if 0
/* Every plugin call this function to register themselves */
void picviz_plugin_register(struct picviz_plugin_t *pp)
{

        if (strcmp(pp->api_version, PICVIZ_OUTPUT_API_VERSION)) {
                picviz_debug(PICVIZ_DEBUG_CRITICAL, PICVIZ_AREA_PLUGIN,
                             "Incompatible version '%s' for plugin. Needed '%s'",
                             pp->api_version, PICVIZ_OUTPUT_API_VERSION);
        }
        if (picviz_plugin_find(pp->name)) {
                picviz_debug(PICVIZ_DEBUG_WARNING, PICVIZ_AREA_PLUGIN,
                             "Plugin '%s' already registered", pp->name);
        } else {
                picviz_debug(PICVIZ_DEBUG_NOTICE, PICVIZ_AREA_PLUGIN,
                             "Registering plugin '%s'", pp->name);
                //llist_add(&pp->list, &picviz_plugins);
        }

}
#endif
