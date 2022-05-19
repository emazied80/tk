/*
 * tkUnixXId.c --
 *
 * Copyright © 1993 The Regents of the University of California.
 * Copyright © 1994-1997 Sun Microsystems, Inc.
 *
 * See the file "license.terms" for information on usage and redistribution of
 * this file, and for a DISCLAIMER OF ALL WARRANTIES.
 */

#include "tkUnixInt.h"


/*
 *----------------------------------------------------------------------
 *
 * Tk_GetPixmap --
 *
 *	Same as the XCreatePixmap function except that it manages resource
 *	identifiers better.
 *
 * Results:
 *	Returns a new pixmap.
 *
 * Side effects:
 *	None.
 *
 *----------------------------------------------------------------------
 */

Pixmap
Tk_GetPixmap(
    Display *display,		/* Display for new pixmap. */
    Drawable d,			/* Drawable where pixmap will be used. */
    int width, int height,	/* Dimensions of pixmap. */
    int depth)			/* Bits per pixel for pixmap. */
{
    return XCreatePixmap(display, d, (unsigned) width, (unsigned) height,
	    (unsigned) depth);
}

/*
 *----------------------------------------------------------------------
 *
 * Tk_FreePixmap --
 *
 *	Same as the XFreePixmap function except that it also marks the
 *	resource identifier as free.
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	The pixmap is freed in the X server and its resource identifier is
 *	saved for re-use.
 *
 *----------------------------------------------------------------------
 */

void
Tk_FreePixmap(
    Display *display,		/* Display for which pixmap was allocated. */
    Pixmap pixmap)		/* Identifier for pixmap. */
{
    XFreePixmap(display, pixmap);
}


/*
 *----------------------------------------------------------------------
 *
 * TkpScanWindowId --
 *
 *	Given a string, produce the corresponding Window Id.
 *
 * Results:
 *	The return value is normally TCL_OK; in this case *idPtr will be set
 *	to the Window value equivalent to string. If string is improperly
 *	formed then TCL_ERROR is returned and an error message will be left in
 *	the interp's result.
 *
 * Side effects:
 *	None.
 *
 *----------------------------------------------------------------------
 */

int
TkpScanWindowId(
    Tcl_Interp *interp,
    const char *string,
    Window *idPtr)
{
    int code;
    Tcl_Obj obj;

    obj.refCount = 1;
    obj.bytes = (char *) string;	/* DANGER?! */
    obj.length = strlen(string);
    obj.typePtr = NULL;

    code = Tcl_GetLongFromObj(interp, &obj, (long *)idPtr);

    if (obj.refCount > 1) {
	Tcl_Panic("invalid sharing of Tcl_Obj on C stack");
    }
    if (obj.typePtr && obj.typePtr->freeIntRepProc) {
	obj.typePtr->freeIntRepProc(&obj);
    }
    return code;
}

/*
 * Local Variables:
 * mode: c
 * c-basic-offset: 4
 * fill-column: 78
 * End:
 */
