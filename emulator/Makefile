PRODUCT := casioemu
SRCDIR := src
DEPDIR := dep
BINDIR := bin
OBJDIR := obj

INCLUDEDIRS :=

CXX ?= g++
CCEXT ?= cpp
CCFLAGS ?= -O2 -fdiagnostics-color=always -g -std=c++11 -Wall -Wextra -Werror -pedantic \
	   -I"D:\Setup\SDL2-devel-2.0.12-mingw\SDL2-2.0.12\x86_64-w64-mingw32\include\SDL2" \
	   -I"D:\Setup\SDL2_image-2.0.5\x86_64-w64-mingw32\include\SDL2" \
	   -I"D:\Setup\lua-5.3.4_Win64_dllw6_lib\include" \
	   #-I"D:\Setup\readline-5.0-1-lib\include" \

CCLINK ?= -lpthread \
	   -L"D:\Setup\SDL2-devel-2.0.12-mingw\SDL2-2.0.12\x86_64-w64-mingw32\lib" \
	   -L"D:\Setup\SDL2_image-2.0.5\x86_64-w64-mingw32\lib" \
	   -L"D:\Setup\lua-5.3.4_Win32_mingw6_lib" \
	   -L"D:\Setup\lua-5.3.4_Win64_dllw6_lib" \
	   -llua53 -lSDL2_image -lSDL2

	   # -L"D:\Setup\readline-5.0-1-lib\lib"


FILES := $(shell find $(SRCDIR) -name *.$(CCEXT))
FILES := $(subst \,/,$(FILES))

# RELATIVEPATH only affects GCC output

$(BINDIR)/$(PRODUCT): $(patsubst %,$(OBJDIR)/%.o,$(subst /,__,$(patsubst $(SRCDIR)/%,%,$(FILES)))) $(LIBSTOLINK) Makefile
	@$(CXX) -o $(BINDIR)/$(PRODUCT) $(patsubst %,$(OBJDIR)/%.o,$(subst /,__,$(patsubst $(SRCDIR)/%,%,$(FILES)))) $(CCLINK)

# -include $(patsubst %,$(DEPDIR)/%.dep,$(subst /,__,$(patsubst $(SRCDIR)/%,%,$(FILES))))

$(OBJDIR)/%.$(CCEXT).o: 
	@$(eval CPATH := $(patsubst %,$(SRCDIR)/%,$(subst __,/,$*.$(CCEXT))))
	@$(eval DPATH := $(patsubst %,$(DEPDIR)/%,$*.$(CCEXT)).dep)
	@$(eval RELBACK := )
	cd $(RELATIVEPATH). && $(CXX) $(CCFLAGS) $(subst -I,-I$(RELBACK),$(INCLUDEDIRS)) -c ./$(RELBACK)$(CPATH) -o ./$(RELBACK)$(OBJDIR)/$*.$(CCEXT).o
	cd $(RELATIVEPATH). && $(CXX) $(CCFLAGS) $(subst -I,-I$(RELBACK),$(INCLUDEDIRS)) -MM ./$(RELBACK)$(CPATH) > ./$(RELBACK)$(DPATH)
	@mv -f $(DPATH) $(DPATH).tmp
	@sed -e 's|.*:|$(OBJDIR)/$*.$(CCEXT).o:|' < $(DPATH).tmp > $(DPATH)
	@sed -e 's/.*://' -e 's/ .$$//' -e 's/^ *//' -e 's/ *$$//' -e 's/$$/:/' < $(DPATH).tmp >> $(DPATH)
	@rm -f $(DPATH).tmp

clean:
	@rm -f $(BINDIR)/$(PRODUCT) $(OBJDIR)/*.o $(DEPDIR)/*.dep
