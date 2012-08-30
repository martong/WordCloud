########################
# Default common rules #
########################

# Please do not edit this section unless you know what you are doing!

.PHONY: default
default: $(DEFAULT_GOAL)

.PHONY: nodep
nodep: $(DEFAULT_GOAL)

goal := $(if $(strip $(MAKECMDGOALS)),$(MAKECMDGOALS),$(DEFAULT_GOAL))

ifneq ($(strip $(SUBDIRS)),)

.PHONY: $(SUBDIRS)
$(SUBDIRS):
	$(MAKE) -C $@

ifneq ($(strip $(COMMON_GOALS)),)

recursive_goals := $(patsubst %,recursive-%,$(COMMON_GOALS))
prereq := $(if $(findstring ' $(goal) ',$(patsubst %,' % ',$(COMMON_GOALS))),recursive-$(goal),)

ifneq ($(strip $(prereq)),)
.PHONY: $(goal)
$(goal): $(prereq)
endif

.PHONY: $(recursive_goals)
$(recursive_goals):
	@for dir in $(SUBDIRS); do $(MAKE) -C $$dir $(goal) || exit 1; done

endif

endif

no_dep_include := depend clean real-clean local-clean local-real-clean
.PHONY: depend
ifeq ($(strip $(DEPFILE)),)
depend: ;
else
depend: $(SRCS) $(HEADERS)
	@echo  --1 updating dependency file: $(DEPFILE)
	$(CPP) $(CPPFLAGS) -MM $(SRCS) >$(DEPFILE)
ifeq ($(strip $(PROJECT_AUTODEP)),TRUE)
ifneq ($(strip $(filter-out $(no_dep_include),$(goal))),)
.DELETE_ON_ERROR: $(DEPFILE)
ifneq ($(strip $(goal)),nodep)
$(DEPFILE): $(SRCS) $(HEADERS)
	@echo  --2 updating dependency file: $(DEPFILE)
	$(CPP) $(CPPFLAGS) -MM $(SRCS) >$(DEPFILE)
endif
else
$(DEPFILE): ;
endif
endif
ifneq ($(strip $(filter-out $(no_dep_include),$(goal))),)
-include $(DEPFILE)
endif
endif

%.po: %.cpp
	 $(CXX) $(CXXFLAGS) $(CPPFLAGS) -fPIC -c -o $@ $^

.PHONY: clean
clean:
	rm -f $(BINS)
	rm -f $(LIBS)
	rm -f $(OBJS)
	rm -f $(PIC_OBJS)

.PHONY: real-clean
real-clean:
	find . -maxdepth 1 -type f \(  -name '*.o' -o -name '*.po' -o -name '*.so' -o -name '*.a' -o -name '*.pa' \) 2>/dev/null | xargs rm -f
	rm -f $(DEPFILE)


full_build:
	$(MAKE) -C $(PROJECT_ROOT) real-clean
	$(MAKE) -C $(PROJECT_ROOT) all


