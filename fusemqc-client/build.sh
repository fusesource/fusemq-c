#!/bin/bash -e
# ------------------------------------------------------------------------
# Licensed to the Apache Software Foundation (ASF) under one or more
# contributor license agreements.  See the NOTICE file distributed with
# this work for additional information regarding copyright ownership.
# The ASF licenses this file to You under the Apache License, Version 2.0
# (the "License"); you may not use this file except in compliance with
# the License.  You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
# ------------------------------------------------------------------------

# load the user supplied build configuration file if present.
if [ -f "./build.conf" ] ; then
  . ./build.conf
fi

# load user activemq-c build configuration
if [ -f "$HOME/.activemqcrc" ] ; then
  . "$HOME/.activemqcrc"
fi

# This is where we run all the build steps, configure, make, etc.
if [ -z "$AMQC_BUILD_DIR" ] ; then
   AMQC_BUILD_DIR="$PWD/build"
fi

check_Configure() {

    # No Configure script means we have to run autogen, which in turn means
    # we need to run a new Configure on the project.
    if [ -x "./configure" ] ; then

        # even if we have a configure script, if the template has been updated we should
        # run it again to account for the changes, which also means we need to run a autogen
        # to create the actual script and associated autoconf artifacts.
        if [ "./configure.ac" -ot "./configure" ] && [ -d $AMQC_BUILD_DIR ] ; then
            runconfigure=false
        else
            runconfigure=true
        fi

    fi

    if [ "x$runconfigure" -ne x ] ; then
        run_Configure
    fi

}

run_Configure() {

    if [ -z "$AMQC_DISABLE_SHARED" ] ; then
        AMQC_DISABLE_SHARED=false;
    fi
    if [ -z "$AMQC_DISABLE_STATIC" ] ; then
        AMQC_DISABLE_STATIC=false;
    fi

    ./autogen.sh

    local args

    if ! [ -d "$AMQC_BUILD_DIR" ] ; then
        mkdir -p $AMQC_BUILD_DIR
    fi

    if [ -n "$AMQC_INSTALL_PREFIX" ] ; then
        args="$args --prefix=$AMQC_INSTALL_PREFIX"
    fi

    if [ -n "$AMQC_LIBDIR" ] ; then
        args="$args --libdir=$AMQC_LIBDIR"
    fi

    if [ -n "$AMQC_APR_DIST" ] ; then
        args="$args --with-apr=$AMQC_APR_DIST"
    fi

    if [ -n "$AMQC_APU_DIST" ] ; then
        args="$args --with-aprutil=$AMQC_APU_DIST"
    fi

    if [ -n "$AMQC_ACTIVEMQCPP_DIST" ] ; then
        args="$args --with-activemqcpp=$AMQC_ACTIVEMQCPP_DIST"
    fi

    if [ -n "$AMQC_CPPUNIT_DIST" ] ; then
        args="$args --with-cppunit=$AMQC_CPPUNIT_DIST"
    fi

    if [ -n "$AMQC_CPPUNIT_EXECDIR" ] ; then
        args="$args --with-cppunit-exec=$AMQC_CPPUNIT_EXECDIR"
    fi

    if $AMQC_DISABLE_SHARED && $AMQC_DISABLE_STATIC ; then
        echo "ERROR: AMQC_DISABLE_SHARED and AMQC_DISABLE_STATIC can't both be set to true."
        exit 1
    fi

    if $AMQC_DISABLE_SHARED ; then
        args="$args --enable-shared=no"
    fi

    if $AMQC_DISABLE_STATIC ; then
        args="$args --enable-static=no"
    fi

    pushd $AMQC_BUILD_DIR
    ../configure $args
    popd
    exit
}

run_Clean() {
    rm -rf $AMQC_BUILD_DIR
    exit
}

run_Make() {
    check_Configure
    pushd $AMQC_BUILD_DIR
    make
    popd
    exit
}

run_Check() {
    check_Configure
    pushd $AMQC_BUILD_DIR
    make check
    popd
    exit
}

run_Doxygen() {
    check_Configure
    pushd $AMQC_BUILD_DIR
    make doxygen-run
    popd
    exit
}

case "$1" in
configure)
    run_Configure
    ;;
compile)
    run_Make
    ;;
test)
    run_Check
    ;;
clean)
    run_Clean
    ;;
doxygen)
    run_Doxygen
    ;;
*)
    echo "Usage: $0 {configure,compile,clean,test,doxygen}"
    exit 1
esac

exit 0

