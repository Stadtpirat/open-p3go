SOURCES	+= $(wildcard $(LCDDIR)/*.c)
CFLAGS	+= -DLCDTYPE=$(LCDTYPE)
CFLAGS	+= -I$(LCDDIR)
VPATH   += $(LCDDIR)

