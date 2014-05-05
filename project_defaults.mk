#################################
# Project-wide default settings #
#################################

# You can change these settings. Note that anything you write before the
# include line below may be overridden in the cudb.makefile file.

# Elements of the compiler toolchain.
#
clang_dir := /proj/cudbdm/tools/external/clang-3.4/SLED11/bin/
CC := $(clang_dir)/clang
CPP := $(clang_dir)/clang -E
CXX := $(clang_dir)/clang++

#gcc_dir := /home/egbomrt/gcc/4.7.1/bin
#CC := $(gcc_dir)/gcc
#CPP := $(gcc_dir)/gcc -E
#CXX := $(gcc_dir)/g++
#LD = $(CXX)
AR := ar

# Overrides from CUDB.
#
save_sources_dir := $(SOURCES_DIR)
save_project_root:= $(PROJECT_ROOT)
#include $(SOURCES_DIR)/build/cudb.makefile
SOURCES_DIR := $(strip $(save_sources_dir))
PROJECT_ROOT := $(strip $(save_project_root))

# Automatic dependency generation. Set to TRUE if you want .depend files to
# be updated automatically, or FALSE to disable this feature. This is a
# project-wide default, but individual developers can override it by exporting
# a shell environment variable with the same name.
# If you set this to TRUE, you have to set SRCS and HEADERS properly in each
# Makefile of the project (there's a sane default for them in the template).
# In this case you can occasionally make the default target without dependency
# regeneration with 'make nodep'.
#
ifeq ($(strip $(PROJECT_AUTODEP)),)
PROJECT_AUTODEP = TRUE
endif

oventoboost_dir := /home/egbomrt/BOOST/OvenToBoost
oventoboost_incl_dir := $(oventoboost_dir)/
oventoboost_incl_statement := -isystem $(oventoboost_incl_dir)

boost_dir := /home/egbomrt/BOOST/inst_1_51_0
boost_incl_dir := $(boost_dir)/include
boost_incl_statement := -isystem $(boost_incl_dir)
boost_lib_dir := $(boost_dir)/lib
boost_lib_statement := -L $(boost_lib_dir)

gcc_dir := /home/egbomrt/gcc/4.7.1
gcc_lib_dir := $(gcc_dir)/lib64
gcc_lib_statement := -L $(gcc_lib_dir)

project_incl_dir := $(PROJECT_ROOT)/include
project_incl_statement := -I $(project_incl_dir) 
project_lib_dir := $(PROJECT_ROOT)/lib
project_lib_statement := -L $(project_lib_dir) 

more_dir := /home/egbomrt/workspaces/cpp11/More.Range.Adaptors
more_incl_dir := $(more_dir)/include
more_incl_statement := -I $(more_incl_dir)

DEFS =
INCL_DIRS = $(project_incl_statement) $(boost_incl_statement) #$(more_incl_statement) $(oventoboost_incl_statement) 
LIB_DIRS = $(project_lib_statement) $(boost_lib_statement) $(gcc_lib_statement)

CPPFLAGS = -std=c++11 -Wall -Wextra -O0 -g $(DEFS) $(INCL_DIRS)
CXXFLAGS = -fmessage-length=0
LD = $(CXX)
LDFLAGS = $(LIB_DIRS)


