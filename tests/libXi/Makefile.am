#
# Copyright (c) 2013, Oracle and/or its affiliates. All rights reserved.
#
# Permission is hereby granted, free of charge, to any person obtaining a
# copy of this software and associated documentation files (the "Software"),
# to deal in the Software without restriction, including without limitation
# the rights to use, copy, modify, merge, publish, distribute, sublicense,
# and/or sell copies of the Software, and to permit persons to whom the
# Software is furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice (including the next
# paragraph) shall be included in all copies or substantial portions of the
# Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
# THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
# DEALINGS IN THE SOFTWARE.
#

noinst_PROGRAMS  = XGetDeviceButtonMapping
noinst_PROGRAMS += XGetDeviceControl
noinst_PROGRAMS += XGetDeviceDontPropagateList
noinst_PROGRAMS += XGetDeviceMotionEvents
noinst_PROGRAMS += XGetDeviceProperty
noinst_PROGRAMS += XGetFeedbackControl
noinst_PROGRAMS += XListInputDevices
noinst_PROGRAMS += XQueryDeviceState
noinst_PROGRAMS += XIGetProperty
noinst_PROGRAMS += XIGetSelectedEvents
noinst_PROGRAMS += XIPassiveGrabDevice

noinst_HEADERS = xhiv-Xi.h

AM_CPPFLAGS = -I$(top_builddir) -I$(top_srcdir)/include
AM_CFLAGS = $(CWARNFLAGS) $(LIBXI_CFLAGS)
LDADD = -L$(top_builddir)/src -lXhiv $(LIBXI_LIBS)
# ../../src/xstrans.o ../../src/server.o ../../src/xlib_client.o

TESTS = $(noinst_PROGRAMS)

