#  
#  Copyright (C) 2011 Texas Instruments
#  Author: Rob Clark <rob.clark@linaro.org>
#  
#  This program is free software; you can redistribute it and/or modify it
#  under the terms of the GNU General Public License version 2 as published by
#  the Free Software Foundation.
#  
#  This program is distributed in the hope that it will be useful, but WITHOUT
#  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
#  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
#  more details.
#  
#  You should have received a copy of the GNU General Public License along with
#  this program.  If not, see <http://www.gnu.org/licenses/>.
#  

noinst_LTLIBRARIES = libutil.la

libutil_la_SOURCES = \
	display-kms.c \
	util.c \
	vpe-common.c

if ENABLE_V4L2_DMABUF
libutil_la_SOURCES += v4l2.c
endif

if ENABLE_DCE
libutil_la_SOURCES += demux.c
endif

if ENABLE_KMSCUBE
libutil_la_SOURCES += display-kmscube.c esTransform.c
endif

libutil_la_LIBADD = @DRM_LIBS@ @DCE_LIBS@ @GBM_LIBS@ @EGL_LIBS@ @GLES2_LIBS@
libutil_la_CFLAGS = @DRM_CFLAGS@ @DCE_CFLAGS@ @WARN_CFLAGS@ @GBM_CFLAGS@ @EGL_CFLAGS@ @GLES2_CFLAGS@
