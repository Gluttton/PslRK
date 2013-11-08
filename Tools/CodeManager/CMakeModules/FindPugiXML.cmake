# Find the pugixml XML parsing library.
#
# Sets the usual variables expected for find_package scripts:
#
# PUGIXML_INCLUDE_DIR - header location
# PUGIXML_LIBRARIES - library to link against
# PUGIXML_FOUND - true if pugixml was found.
#
# This module is part of OpenImageIO project
#(https://github.com/OpenImageIO).
#
# OpenImageIO and all code, documentation, and other materials contained
# therein are:
#
# Copyright 2008 Larry Gritz and the other authors and contributors.
# All Rights Reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are
# met:
# * Redistributions of source code must retain the above copyright
#   notice, this list of conditions and the following disclaimer.
# * Redistributions in binary form must reproduce the above copyright
#   notice, this list of conditions and the following disclaimer in the
#   documentation and/or other materials provided with the distribution.
# * Neither the name of the software's owners nor the names of its
#   contributors may be used to endorse or promote products derived from
#   this software without specific prior written permission.
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
# A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
# OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
# SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
# LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
# THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
# (This is the Modified BSD License)

find_path (PUGIXML_INCLUDE_DIR
           NAMES pugixml.hpp
           PATHS ${PUGIXML_HOME}/include)
find_library (PUGIXML_LIBRARY
              NAMES pugixml
              PATHS ${PUGIXML_HOME}/lib)

# Support the REQUIRED and QUIET arguments, and set PUGIXML_FOUND if found.
include (FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS (PugiXML DEFAULT_MSG PUGIXML_LIBRARY
                                   PUGIXML_INCLUDE_DIR)

if (PUGIXML_FOUND)
    set (PUGIXML_LIBRARIES ${PUGIXML_LIBRARY})
    message (STATUS "PugiXML include = ${PUGIXML_INCLUDE_DIR}")
    message (STATUS "PugiXML library = ${PUGIXML_LIBRARY}")
else ()
    message (STATUS "No PugiXML found")
endif()

mark_as_advanced (PUGIXML_LIBRARY PUGIXML_INCLUDE_DIR)
