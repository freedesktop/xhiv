/*
 * Copyright (c) 2013, Oracle and/or its affiliates. All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */
#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "xhiv.h"
#include <X11/Xlib.h>
#include <X11/Xproto.h>
#include <X11/Xatom.h>
#include <assert.h>
#include <stdio.h>
#include <limits.h>

static void
testOverflowFields(void)
{
    const xGetPropertyReply rep1 = {
        .type           = X_Reply,
        .length         = 32,
        .propertyType   = XA_ATOM,
        .nItems         = (UINT_MAX / 4) + 4,
        .format         = 32,
    };
    xhiv_response response1 = {
        .reqType = X_GetProperty,
        .reqMinor = XHIV_REQ_IGNORE,
        .sequence = 101,  /* Avoid answering the query during XOpenDisplay */
        .length = (sizeof(rep1) >> 2) + rep1.length,
        .response_data = &rep1,
        .response_datalen = sizeof(rep1)
    };
    Display *dpy = XhivOpenDisplay(&response1);
    int status;
    Atom type_return;
    int format_return;
    unsigned long num_items_return, bytes_after_return;
    unsigned char *data = NULL;

    /* set sequence to known value so that later calls match by sequence num */
    XhivSequenceSync(dpy, 100);

    printf("XGetWindowProperty: overflow number of items test: 0x%lx\n",
           (unsigned long) rep1.nItems);
    status = XGetWindowProperty(dpy, DefaultRootWindow(dpy),
                                /* property */ 0,
                                /* offset */ 0, /* length */ 0,
                                /* delete_property */ False,
                                /* type */ XA_ATOM,
                                &type_return, &format_return,
                                &num_items_return, &bytes_after_return,
                                &data);
    XFree(data);
    assert(status != Success);
    assert(data == NULL);
    assert(type_return == None);
    assert(format_return == 0);
    assert(num_items_return == 0);
    assert(bytes_after_return == 0);

    XhivCloseDisplay(dpy);
}

int
main(int argc, char **argv)
{
    testOverflowFields();
    printf("XGetWindowProperty: all tests passed\n");
    return 0;
}
