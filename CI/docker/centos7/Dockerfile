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

# All of the build tools want to use Ninja as the cmake generator, but ninja doesn't work in this older
# environment. Rather than specifying a generator, use whichever happens to be the default on the machine.
ENV DEVELOPMENT_ENVIRONMENT_CPP_USE_DEFAULT_CMAKE_GENERATOR=1 \
    CXX=gcc \
    CC=gcc
