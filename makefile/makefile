#--------------------------------------------------
# about =,:=,?=,+=
ifdef DEF_HELLO
	VER = "Hello World!"
else
$(warning you can define DEF_HELLO, warning)
#$(error We need DEF_HELLO)
endif

ifeq ($(OPT),define)
	VER ?="Hello World! ?= EXIST ? First Def Here : USE EXIST"
else ifeq ($(OPT),append)
	VER += " += is APPEND"
else ifeq ($(OPT),recover)
	VER :="Hello World! := is RECOVER"
else
$(warning can not parse OPT: $(OPT))
endif

x=foo
y=$(x) bar
x=abc
# $(y) is aabbcc bar
x:=foo
y:=$(x) bar
x:=aabbcc
# $(y) is foo bar

all:
	@echo $(VER)
	@echo y is $(y)


debug:
	@echo make debug version $(GDB)

release:
	@echo make release version $(GDB)
# make DEF_HELLO=true OPT=define ; Hello World!
# make DEF_HELLO=true OPT=append ; Hello World! += is APPEND
# make DEF_HELLO=true OPT=recover ; Hello World! := is RECOVER
# make OPT=define  ; Hello World! ?= EXIST ? First Def Here : USE EXIST
# make OPT=append  ;  += is APPEND
# make OPT=recover ; Hello World! := is RECOVER"