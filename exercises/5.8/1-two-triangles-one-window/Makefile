##
# Makefile shim for building Meson projects.
#

# Enables verbosity for this Makefile.
#
# Set this to 1 to see all commands and output.
#
VERBOSE ?= 0

ifeq ($(VERBOSE),1)
export Q :=
export VERBOSE := 1
else
export Q := @
export VERBOSE := 0
endif

# The meson command to use.
#
# This can be changed to try out pre-releases or other versions of Meson.
#
MESON ?= meson

# Build directory.
#
# The directory with which to set the Meson build directory.
#
BUILD_DIR ?= build

# Tests build directory.
#
# The directory with which to set the Meson build directory for the tests build.
#
TESTS_BUILD_DIR ?= testsbuild

# Default location of the ninja build file.
#
# This is used in a rule below for running meson if the file needs to be created.
#
CONFIGURED_BUILD_DEP = $(BUILD_DIR)/build.ninja

# Location of the test coverage ninja build file.
# 
# This is used in a rule below for running meson if the file needs to be created.
#  
CONFIGURED_TESTS_BUILD_DEP = $(BUILD_DIR)/$(TESTS_BUILD_DIR)/build.ninja

# Provide additional Meson command options.
# 
# See the Meson commands reference for the command being run:
# https://mesonbuild.com/Commands.html
#
# Example:
# 
# 	> make OPTIONS="-Denable-pedantic=true"
# 
OPTIONS ?=

# Enables link-time optimization.
#
LTO ?= 0

# Enables debug build. 
#
# When set to 1, the buildtype is set to debug, debug = true, optimization = g,
# and the appropriate macros are defined.
#
DEBUG ?= 0

# Set to use a santizer.
#
# Options: 	none (default)
# 			address
# 			thread
# 			undefined
# 			memory
#			address,undefined as a combined option
# 
# NOTE: Sanitizers are not supported by arm-none-eabi-gcc.
# 
SANITIZER ?= none

# Options internal to Meson.
#
# This is used to collect the internal options to be passed to Meson.
#
INTERNAL_OPTIONS =

ifeq ($(LTO),1)
	INTERNAL_OPTIONS += -Db_lto=true -Ddisable-builtins=true
endif

ifeq ($(DEBUG),1)
	INTERNAL_OPTIONS += -Ddebug=true -Doptimization=g
endif

ifeq ($(SYSTEMVIEW),1)
	INTERNAL_OPTIONS += -Denable-segger-systemview=true
endif

ifneq ($(SANITIZER),none)
	INTERNAL_OPTIONS += -Db_sanitize=$(SANITIZER) -Db_lundef=false
endif

all: default

.PHONY: default
default: | $(CONFIGURED_BUILD_DEP)
	$(Q)ninja -C $(BUILD_DIR)

.PHONY: test
test: | $(CONFIGURED_TESTS_BUILD_DEP)
	$(Q)ninja -C $(BUILD_DIR)/$(TESTS_BUILD_DIR) tests

.PHONY: test-coverage
test-coverage: | $(CONFIGURED_TESTS_BUILD_DEP)
	$(Q)ninja -C $(BUILD_DIR)/$(TESTS_BUILD_DIR) tests
	$(Q) ninja -C $(BUILD_DIR)/$(TESTS_BUILD_DIR) coverage

.PHONY: docs
docs: | $(CONFIGURED_BUILD_DEP)
	$(Q)ninja -C $(BUILD_DIR) docs

.PHONY: docs-ci
docs-ci: | $(CONFIGURED_BUILD_DEP)
	$(Q)ninja -C $(BUILD_DIR) docs-ci

.PHONY: docs-coverage
docs-coverage: | $(CONFIGURED_BUILD_DEP)
	$(Q)ninja -C $(BUILD_DIR) docs-coverage

.PHONY: docs-coverage-browsable
docs-coverage-browsable: | $(CONFIGURED_BUILD_DEP)
	$(Q)ninja -C $(BUILD_DIR) docs-coverage-lcov
	$(Q)ninja -C $(BUILD_DIR) docs-coverage-browsable

.PHONY: package
package: default docs
	$(Q)ninja -C $(BUILD_DIR) package
	$(Q)ninja -C $(BUILD_DIR) package-native

# Manually Reconfigure a target, esp. with new options.
# 
.PHONY: reconfig
reconfig:
	$(Q) $(MESON) setup $(BUILD_DIR) --reconfigure $(INTERNAL_OPTIONS) $(OPTIONS)

# Runs whenever the build has not been configured successfully.
# 
$(CONFIGURED_BUILD_DEP):
	$(Q) $(MESON) setup $(BUILD_DIR) $(INTERNAL_OPTIONS) $(OPTIONS)

# Runs whenever the test build has not been configured successfully.
#
# A second test-specific build nested in the regular build. This allows
# test-specific flags and build settings to be enforced without configuring or
# rebuilding the regular build.
#
$(CONFIGURED_TESTS_BUILD_DEP): | $(CONFIGURED_BUILD_DEP)
	$(eval INTERNAL_OPTIONS += -Ddebug=true -Doptimization=0 -Db_coverage=true)
	$(Q) $(MESON) setup $(BUILD_DIR)/$(TESTS_BUILD_DIR) $(INTERNAL_OPTIONS) $(OPTIONS)

.PHONY: clean
clean:
	$(Q) if [ -d "$(BUILD_DIR)" ]; then ninja -C build clean; fi

.PHONY: distclean
distclean:
	$(Q) rm -rf $(BUILD_DIR)

.PHONY : help
help :
	@echo "usage: make [OPTIONS] <target>"
	@echo "  Options:"
	@echo "    > MESON Override meson tool - useful for testing meson prereleases and forks."
	@echo "    > VERBOSE Show verbose output for Make rules. Default: 0. Enable with 1."
	@echo "    > BUILD_DIR Directory for build results. Default: build."
	@echo "    > OPTIONS Configuration options to pass to a build. Default: empty."
	@echo "    > LTO Enable LTO builds. Default: 0. Enable with 1."
	@echo "    > DEBUG Enable a debug build. Default: 0 (release). Enable with 1."
	@echo "    > SANITIZER Compile with support for a Clang/GCC Sanitizer."
	@echo "         Options are: none (default), address, thread, undefined, memory,"
	@echo "         and address,undefined' as a combined option"
	@echo "Build Targets"
	@echo "  default: build all default targets ninja knows about"
	@echo "  test: build and run unit test programs"
	@echo "  test-coverage: build and run unit test programs with coverage reporting"
	@echo "  package: build the project, generate docs, and create a release package"
	@echo "  clean: clean build artifacts, keeping build files in place"
	@echo "  distclean: remove the configured build output directory"
	@echo "  reconfig: reconfigure an existing build output folder with new settings"
	@echo "Documentation Targets"
	@echo "  docs: generate documentation"
	@echo "  docs-ci: generate documentation for use in CI process for coverage reporting"
	@echo "  docs-coverage: run documentation comment coverage and generate a report"
	@echo "  docs-coverage-browsable: run documentation comment coverage and generate a browsable report"
