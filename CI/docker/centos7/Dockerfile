FROM centos:7

# Install packages on the image:
#
#   - git:                                  required during bootstrapping
#   - sudo:                                 required by Azure DevOps
#   - various development tools:            required by everything
#
RUN yum install -y \
    git \
    sudo \
    gcc-4.8.5 \
    gcc-c++-4.8.5 \
    kernel-devel-3.10.0 \
    make-3.82

# DEVELOPMENT_ENVIRONMENT_CPP_USE_DEFAULT_CMAKE_GENERATOR
# All of the build tools want to use Ninja as the cmake generator, but ninja doesn't work in this older
# environment. Rather than specifying a generator, use whichever happens to be the default on the machine.
#
# DEVELOPMENT_ENVIRONMENT_CPP_NO_STATIC_CRT
# This build environment has problems when attempting to link with the static c runtime.
# Disable that functionality for now.
ENV DEVELOPMENT_ENVIRONMENT_CPP_USE_DEFAULT_CMAKE_GENERATOR=1 \
    DEVELOPMENT_ENVIRONMENT_CPP_NO_STATIC_CRT=1 \
    CXX=g++ \
    CC=gcc
