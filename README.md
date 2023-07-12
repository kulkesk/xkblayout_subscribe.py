# xkblayout_subscribe.py
Python module made with [Cython][Cython] that recreates the functionality from [xkblayout-subscribe][xkblayout-subs] into a couple of functions for use in python code.

## Quick Start:
### Building:
1. make sure that your linux installation has X11 C library and that your installation includes necessary libraries for building python C extensions
2. [install Cython][Cython-install]
3. run [compile_inplace.sh](/compile_inplace.sh)
4. copy (or link) created file: xkblayout_subscribe.cpython-*.so into needed destination.

### Usage:
```python
# import .so file as a regular python module with:
import xkblayout_subscribe as xkbls

# initialize the library:
if not xkbls.init():
    print(f"ERROR: couldn't initialize the library")

layouts = {
    0: "english"
    1: "russian"
}

for _ in range(10):
    # wait for the layout to change
    # function is blocking in nature, 
    # but it can be thereaded with no problem
    changed_to_layout = xkbls.update()

    # do whatever you want with received information
    print(f"changed to {layouts[changed_to_layout]} layout")

# de-initialize the library when not needed
xkbls.deinit() 

```




[xkblayout-subs]: https://github.com/koonix/xkblayout-subscribe
[Cython]: https://cython.org/
[Cython-install]: https://cython.readthedocs.io/en/latest/src/quickstart/install.html
