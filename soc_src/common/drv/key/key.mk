SOURCES	+= $(KEYDIR)/no_key.c
CFLAGS	+= -DKEYTYPE=$(KEYTYPE)
CFLAGS	+= -I$(KEYDIR)
VPATH   += $(KEYDIR)
