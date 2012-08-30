#########################################################
# Location of the CUDB source root and the project root #
#########################################################

# Please do not edit this section unless you know what you are doing!

get_dir = $(if $(findstring $(1),$(2)),$(word 1,$(subst $(1), ,$(2)))$(1),$(error $(3)))
ifeq ($(strip $(SOURCES_DIR)),)
get_src_errmsg := Could not determine the CUDB sources directory
get_src_pattern := /
export SOURCES_DIR := $(call get_dir,$(get_src_pattern),$(CURDIR)/,$(get_src_errmsg))
endif

get_prj_errmsg := Could not determine the project root directory
get_prj_pattern := /WordCloud/
export PROJECT_ROOT := $(call get_dir,$(get_prj_pattern),$(CURDIR)/,$(get_prj_errmsg))

#########################################
# Include project-wide default settings #
#########################################

# Please do not edit this section unless you know what you are doing!

include $(PROJECT_ROOT)/project_defaults.mk

###########################
# Settings for this level #
###########################

# You can change this section.

# Settings for recursion down from this level.
#
DEFAULT_GOAL := all
SUBDIRS := 
COMMON_GOALS := all clean real-clean depend nodep

# Settings for the source code on this level.
#
SRCS := $(wildcard *.cpp)
HEADERS := $(wildcard *.hpp)
OBJS := $(SRCS:%.cpp=%.o)
LIBS :=
BINS := wordCloud
TARGET := dependency $(LIBS) $(BINS)
DEPFILE := .depend
INCL_DIRS := $(INCL_DIRS) -I $(PROJECT_ROOT)/src 

########################
# Default common rules #
########################

# Please do not edit this section unless you know what you are doing!

include $(PROJECT_ROOT)/project_rules.mk

#######################
# Default local rules #
#######################

# You can change this section.

.PHONY: all
all: $(TARGET)

.PHONY: local-clean
local-clean: clean

.PHONY: local-real-clean
local-real-clean: real-clean

######################
# Custom local rules #
######################

# You can change this section. Your local rules go here (e.g. rules for
# libraries, executables).

.PHONY: $(BINS)
dependency:
	$(MAKE) -C $(PROJECT_ROOT)/lib $(MAKECMDGOALS)

BOOST_LIBS = $(boost_lib_dir)/libboost_thread.a \
	$(boost_lib_dir)/libboost_system.a \
	$(boost_lib_dir)/libboost_filesystem.a \
	$(boost_lib_dir)/libboost_regex.a
#	$(gcc_lib_dir)/libstdc++.a
#	$(boost_lib_dir)/libboost_program_options.a \
#	$(boost_lib_dir)/libboost_serialization.a \

wordCloud: $(OBJS) 
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(LDFLAGS) \
	-o $@ $^ \
	$(PROJECT_ROOT)/lib/libWordCloud.a \
	$(BOOST_LIBS) \
	-lpthread
	
