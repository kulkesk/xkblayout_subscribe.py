from setuptools import Extension, setup
from Cython.Build import cythonize

setup(
    name="xkblayout module",
    ext_modules=cythonize("cy_src/xkblayout_subscribe.pyx"),
    zip_safe=True,
)
