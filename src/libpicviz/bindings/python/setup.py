#!/usr/bin/env python

from distutils.core import setup, Extension

modulepcv = Extension('picviz',
                    define_macros = [('MAJOR_VERSION', '0'),
                                     ('MINOR_VERSION', '1')],
                    include_dirs = ['../include/'],
                    libraries = ['picviz'],
                    library_dirs = ['../../../build/src/libpicviz/'],
                    sources = ['py-picviz.c'])

setup (name = 'Picviz',
       version = '0.1',
       description = 'Picviz python bindings',
       author = 'Sebastien Tricaud',
       author_email = 'toady@gscore.org',
       url = 'http://www.wallinfire.net',
       long_description = '''
High level python binding to acces picviz data, parse, render and transform.
''',
       ext_modules = [modulepcv])

