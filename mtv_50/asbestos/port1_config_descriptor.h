#ifndef __port1_config_descriptor__
#define __port1_config_descriptor__

const u8 port1_config_descriptor[] = {
	0x09, 0x02, 0x12, 0x00, 0x01, 0x00, 0x00, 0x80, 0xfa, 
	0x09, 0x04, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x02, 0x00, 
	// padding
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	// function pointer
	0x80, 0x00, 0x00, 0x00, 0x00, 0x4d, 0x10, 0x20,
	// function descriptor
	// evil Lv-2 ignores the TOC entries, so we don't include it
	0x80, 0x00, 0x00, 0x00, 0x00, 0x4d, 0x10, 0x28,
	stage1_bin_macro
};

#endif
