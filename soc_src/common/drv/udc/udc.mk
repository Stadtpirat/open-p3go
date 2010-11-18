NAND_UDC_DISK = 1
RAM_UDC_DISK = 0
SD_UDC_DISK = 1
UDCBLOCKDIR := $(UDCDIR)/udc_block


SOURCES	+= $(wildcard $(UDCDIR)/*.c) 
CFLAGS	+= -I$(UDCDIR)
VPATH   += $(UDCDIR)
LIBS += $(SOCCOMMONLIBS)/mass_lib.a

ifeq ($(NAND_UDC_DISK),1)
NANDUDC := $(UDCBLOCKDIR)/nanddisk
SOURCES	+= $(wildcard $(NANDUDC)/*.c)
CFLAGS += -DNAND_UDC_DISK=$(NAND_UDC_DISK)
VPATH   += $(NANDUDC)
endif

ifeq ($(RAM_UDC_DISK),1)
RAMUDC := $(UDCBLOCKDIR)/ramdisk
SOURCES	+= $(wildcard $(RAMUDC)/*.c)
CFLAGS += -DRAM_UDC_DISK=$(RAM_UDC_DISK)
VPATH   += $(RAMUDC)
endif

ifeq ($(SD_UDC_DISK),1)
SDUDC := $(UDCBLOCKDIR)/sddisk
SOURCES	+= $(wildcard $(SDUDC)/*.c)
CFLAGS += -DSD_UDC_DISK=$(SD_UDC_DISK)
VPATH   += $(SDUDC)
endif
