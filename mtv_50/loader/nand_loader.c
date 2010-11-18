/*
 *  XBurst  mobile_tv  Project  V1.0.0
 *  Copyright (C) 2006 - 2007 Ingenic Semiconductor Inc.
 *  Author: <xliu@ingenic.cn>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License version 2 as
 *  published by the Free Software Foundation.
 *
 *  2007-12-27, xliu
 *  Created.
 */

#include <bsp.h>
#include <os_api.h>
#include "nand_api.h"
#include "function.h"

#define BLOCK_MAX					(1024 * 1)
#define	IMG_AND_DEF_BIN_PAGE_SIZE	(2048)

unsigned int	g_page_size = IMG_AND_DEF_BIN_PAGE_SIZE;
unsigned int	g_page_per_block = 128;

// Ӧ�ó�����ں���
static void (*minios_entry)();

unsigned int load_data(	unsigned int	page_addr,
						unsigned int	page_count,
						unsigned char	*buffer)
{
	unsigned int dev_id = 0, ret, i;
	unsigned int cur_page, cur_block, first_page, last_page;
	unsigned int read_page_count = 0;
	nand_page_info_t	info, info2;

	cur_page = page_addr;
	cur_block = cur_page / g_page_per_block;
	for (i = 0; i < BLOCK_MAX; i++) {
		first_page = cur_block * g_page_per_block;
		last_page = first_page + g_page_per_block - 1;

		jz_nand_read_page_info(&dev_id, first_page, &info);
		jz_nand_read_page_info(&dev_id, last_page, &info2);
		if ((0xFFFFFFFF != info.block_status) || (0xFFFFFFFF != info2.block_status)) {
			cur_block++;
			printf("bad block.");
			continue;
		}

		cur_page = first_page;
		while (cur_page <= last_page) {
			ret = jz_nand_read_page(&dev_id, cur_page, buffer, &info);
			
			if (0 != ret) {
				printf("Read nand data error!\n");
				return (0);
			}
			buffer += g_page_size;
			read_page_count ++;
			cur_page++;
			if (read_page_count >= page_count) {
				printf("OK, read in %d pages.\n", read_page_count);
				return (1);
			}
		}
		cur_block++;
	}

	printf("Too many bad blocks!\n");
	return (0);
}

void LoaderInit(void)
{
	flash_info_t flashinfo;

	jz_nand_init();
	jz_nand_get_info(&flashinfo);
	__dcache_writeback_all();
	g_page_size = flashinfo.pnandinfo->dwPageSize;
	if (g_page_size == 0) {
		printf("jz_nand_get_info!\n");
		while (1);
	}

	g_page_per_block = flashinfo.pnandinfo->dwBlockSize / g_page_size;
}

void LoaderTask(void)
{
	unsigned int c;

	//ж��USB
	disable_device(1);
	mdelay(100);

    // ��ʼ��OS���
    JZ_StartTicker(OS_TICKS_PER_SEC);

	// Loader Nand Init
    LoaderInit();
    if(0 == load_data(2176, 510, (unsigned char*)0x80001000 ))
	{
        printf("Read application module failure!\n");
        while(1);
    }

    minios_entry = (void *)0x80002000;
    // ��ת��Ӧ�ó������
    printf("go go go! goto 0x%08X\n", minios_entry);

    cli();
	__dcache_writeback_all();
	__icache_invalidate_all();
    minios_entry();
}

