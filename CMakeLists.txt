# Copyright (c) 2011-2018 LG Electronics, Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
# SPDX-License-Identifier: Apache-2.0

#
# PmKLogDaemon/CMakeLists.txt
#

cmake_minimum_required(VERSION 2.8.7)

project(PmKLogDaemon C)

include(webOS/webOS)
webos_modules_init(1 0 0 QUALIFIER RC2)
webos_component(2 0 0)

include(FindPkgConfig)

pkg_check_modules(GLIB2 REQUIRED glib-2.0)
include_directories(${GLIB2_INCLUDE_DIRS})
webos_add_compiler_flags(ALL ${GLIB2_CFLAGS_OTHER})

include_directories(src)
webos_add_compiler_flags(ALL -Wall -Wconversion)

webos_configure_source_files(SOURCE_FILES src/PmKLogDaemon.c src/PmKLogDaemonUtil.c)
add_executable(PmKLogDaemon ${SOURCE_FILES})

target_link_libraries(PmKLogDaemon ${GLIB2_LDFLAGS})

webos_build_daemon()
