/*
 *  linux/include/linux/ext21_fs.h
 *
 * Copyright (C) 1992, 1993, 1994, 1995
 * Remy Card (card@masi.ibp.fr)
 * Laboratoire MASI - Institut Blaise Pascal
 * Universite Pierre et Marie Curie (Paris VI)
 *
 *  from
 *
 *  linux/include/linux/minix_fs.h
 *
 *  Copyright (C) 1991, 1992  Linus Torvalds
 */

#ifndef _LINUX_EXT21_FS_H
#define _LINUX_EXT21_FS_H

#include <linux/types.h>
#include <linux/magic.h>

#define EXT21_NAME_LEN 255

/*
 * Maximal count of links to a file
 */
#define EXT21_LINK_MAX		32000
#define EXT21_SUPER_MAGIC       0xEF53
#define EXT21_SB_MAGIC_OFFSET	0x38
#define EXT21_SB_BLOCKS_OFFSET	0x04
#define EXT21_SB_BSIZE_OFFSET	0x18

static inline u64 ext21_image_size(void *ext21_sb)
{
	__u8 *p = ext21_sb;
	if (*(__le16 *)(p + EXT21_SB_MAGIC_OFFSET) != cpu_to_le16(EXT21_SUPER_MAGIC))
		return 0;
	return (u64)le32_to_cpup((__le32 *)(p + EXT21_SB_BLOCKS_OFFSET)) <<
		le32_to_cpup((__le32 *)(p + EXT21_SB_BSIZE_OFFSET));
}

#endif	/* _LINUX_EXT21_FS_H */
