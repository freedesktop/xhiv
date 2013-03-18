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
#include "proto.h"
#include <X11/Xlibint.h>
#include <assert.h>
#include <sys/types.h>

static pid_t server_pid;

Display *
XhivOpenDisplay(xhiv_response *responses) {
    char *dpyname;
    Display *dpy;

    dpyname = XhivOpenServer(responses, &server_pid);
    assert(dpyname != NULL);

    dpy = XOpenDisplay(dpyname);
    assert(dpy != NULL);

    XhivSequenceSync(dpy, 0);

    return dpy;
}

void
XhivSequenceSync(Display *dpy, uint32_t sequence) {
    xResourceReq *xssreq;

    LockDisplay(dpy);
    GetResReq(XHIV_PROTO_REQTYPE, sequence, xssreq);
    ((xXhivSeqStartReq *)xssreq)->reqMinor = XhivSeqStart;
    UnlockDisplay(dpy);
    SyncHandle();
}

int
XhivCloseDisplay(Display *dpy) {
    int ret;
    pid_t waitfor;

    ret = XCloseDisplay(dpy);
    assert(ret == Success);

    waitfor = server_pid;
    server_pid = -1;
    return XhivWaitServer(waitfor);
}
