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
SUBDIRS := simple
COMMON_GOALS := all clean real-clean depend nodep

# Settings for the source code on this level.
#
SRCS := $(wildcard *.cpp)
HEADERS := $(wildcard *.hpp)
OBJS := $(SRCS:%.cpp=%.o)
LIBS :=
BINS :=
TARGET := $(OBJS)
DEPFILE := .depend

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

.PHONY: dependencies
dependencies:
	$(MAKE) -C $(LOGGER_DIR)
	$(MAKE) -C $(IMMCC_DIR)

.PHONY: local-clean
local-clean: clean

.PHONY: local-real-clean
local-real-clean: real-clean

######################
# Custom local rules #
######################

# You can change this section. Your local rules go here (e.g. rules for
# libraries, executables).

#.PHONY: install-client
#install-client:
#	$(MAKE) -C src pus_client
#	cp $(PROJECT_ROOT)/src/pus_client $(DESTDIR)/$(PREFIX)/bin/

