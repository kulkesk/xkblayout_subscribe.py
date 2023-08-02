# distutils: libraries = X11


cdef extern from "../c_src/xkblayout_module.c":
    """
    /* #define XKBL_NO_RETURNS */
    """
    int xkbl_mod_init()
    int xkbl_mod_update() nogil
    void xkbl_mod_deinit()

__is_init: bool = False

def init() -> int:
    """
    Initializes the module, it has to be ran before using any other functions!
    """
    global __is_init
    if __is_init:
        raise RuntimeError("`init()` was ran before")

    success = xkbl_mod_init()
    __is_init = not bool(success)
    return success


def update() -> int:
    """
        Returns the id of the switched keyboard layout
    """
    global __is_init
    if not __is_init:
        raise RuntimeError("`init()` wasn't ran before using this function")

    cdef int lang
    with nogil:
        while True:
            lang = xkbl_mod_update()
            if lang == -1:
                continue
            break
    return lang


def deinit():
    """
        De-initionalizes the library,
    """
    global __is_init
    if not __is_init:
        raise RuntimeError("`init()` wasn't ran before using this function")

    __is_init = False
    xkbl_mod_deinit()

