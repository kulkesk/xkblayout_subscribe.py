#include <stdio.h>
#include <X11/Xutil.h>
#include <X11/XKBlib.h>

/*
    based on original source: https://github.com/koonix/xkblayout-subscribe/blob/master/xkblayout-subscribe.c
    and reworked into module
*/

Display *xkbl_mod_display;
int xkbl_mod_prevlang;
int xkbl_mod_event_type;

int xkbl_mod_init(void);
int xkbl_mod_update(void);

int xkbl_mod_init(void){
    if (!(xkbl_mod_display = XOpenDisplay(NULL))){
        fprintf(stderr, "cannot open display\n");
        return 1;
    }

    XKeysymToKeycode(xkbl_mod_display,XK_F1);
    XkbQueryExtension(xkbl_mod_display, 0, &xkbl_mod_event_type, 0,0,0);
    XkbSelectEvents(xkbl_mod_display, XkbUseCoreKbd, XkbAllEventsMask, XkbAllEventsMask);
    XSync(xkbl_mod_display, False);
    return 0;
}


int xkbl_mod_update(void){
    XEvent e;
    #if defined XKBL_NO_RETURNS
    while(1){
        XNextEvent(xkbl_mod_display, &e);
        if (e.type != xkbl_mod_event_type) continue;
        XkbEvent* xkbEvent = (XkbEvent*) &e;
        if  (xkbEvent-> any.xkb_type != XkbStateNotify) continue;
        int lang = xkbEvent-> state.group;
        if (lang == xkbl_mod_prevlang) continue;
        xkbl_mod_prevlang = lang;
        return lang;
    }
    #else
        XNextEvent(xkbl_mod_display, &e);
        if (e.type != xkbl_mod_event_type) return -1;
        XkbEvent* xkbEvent = (XkbEvent*) &e;
        if  (xkbEvent-> any.xkb_type != XkbStateNotify) return -1;
        int lang = xkbEvent-> state.group;
        if (lang == xkbl_mod_prevlang) return -1;
        xkbl_mod_prevlang = lang;
        return lang;
    #endif
}



void xkbl_mod_deinit(void){
    if (xkbl_mod_display != NULL){
        XCloseDisplay(xkbl_mod_display);
        xkbl_mod_display = NULL;
    }
}

// int main(void){
//     init();
//     while(1){
//         int langlang = update();
//         if (langlang == -1) continue;
//         fprintf(stdout, "%u\n", langlang);
//         fflush(stdout);
//     }
// }

