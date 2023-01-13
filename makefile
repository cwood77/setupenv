COMPILE_CMD = x86_64-w64-mingw32-g++
LINK_CMD = x86_64-w64-mingw32-g++
OBJ_DIR = bin/obj
OUT_DIR = bin/out
DEBUG_CC_FLAGS = -ggdb -c -Wall -D cdwDebugMode -D cdwTest
RELEASE_CC_FLAGS = -O3 -c -Wall -D cdwTest
DEBUG_LNK_FLAGS_POST = -ggdb -static-libgcc -static-libstdc++ -static
RELEASE_LNK_FLAGS_POST = -static-libgcc -static-libstdc++ -static

SCRIPTLIB = scriptlib/xcopy-deploy.bat

all: \
	$(OUT_DIR)/debug/setupenv.exe \
	$(OUT_DIR)/release/setupenv.exe \

clean:
	rm -rf bin

.PHONY: all clean

# ----------------------------------------------------------------------
# setupenv

SETUPENV_SRC = \
	src/accumulator.cpp \
	src/checker.cpp \
	src/finder.cpp \
	src/log.cpp \
	src/main.cpp \

SETUPENV_DEBUG_OBJ = $(subst src,$(OBJ_DIR)/debug,$(patsubst %.cpp,%.o,$(SETUPENV_SRC)))

$(OUT_DIR)/debug/setupenv.exe: $(SETUPENV_DEBUG_OBJ)
	$(info $< --> $@)
	@mkdir -p $(OUT_DIR)/debug
	@$(LINK_CMD) -o $@ $(SETUPENV_DEBUG_OBJ) $(DEBUG_LNK_FLAGS_POST) -Lbin/out/debug

$(SETUPENV_DEBUG_OBJ): $(OBJ_DIR)/debug/%.o: src/%.cpp
	$(info $< --> $@)
	@mkdir -p $(OBJ_DIR)/debug/setupenv
	@$(COMPILE_CMD) $(DEBUG_CC_FLAGS) $< -o $@

SETUPENV_RELEASE_OBJ = $(subst src,$(OBJ_DIR)/release,$(patsubst %.cpp,%.o,$(SETUPENV_SRC)))

$(OUT_DIR)/release/setupenv.exe: $(SETUPENV_RELEASE_OBJ)
	$(info $< --> $@)
	@mkdir -p $(OUT_DIR)/release
	@$(LINK_CMD) -o $@ $(SETUPENV_RELEASE_OBJ) $(RELEASE_LNK_FLAGS_POST) -Lbin/out/release

$(SETUPENV_RELEASE_OBJ): $(OBJ_DIR)/release/%.o: src/%.cpp
	$(info $< --> $@)
	@mkdir -p $(OBJ_DIR)/release/setupenv
	@$(COMPILE_CMD) $(RELEASE_CC_FLAGS) $< -o $@
