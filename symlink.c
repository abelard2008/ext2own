/*
 *  linux/fs/ext21/symlink.c
 *
 * Only fast symlinks left here - the rest is done by generic code. AV, 1999
 *
 * Copyright (C) 1992, 1993, 1994, 1995
 * Remy Card (card@masi.ibp.fr)
 * Laboratoire MASI - Institut Blaise Pascal
 * Universite Pierre et Marie Curie (Paris VI)
 *
 *  from
 *
 *  linux/fs/minix/symlink.c
 *
 *  Copyright (C) 1991, 1992  Linus Torvalds
 *
 *  ext21 symlink handling code
 */

#include "ext21.h"
#include "xattr.h"

const struct inode_operations ext21_symlink_inode_operations = {
	.readlink	= generic_readlink,
	.get_link	= page_get_link,
	.setattr	= ext21_setattr,
#ifdef CONFIG_EXT21_FS_XATTR
	.setxattr	= generic_setxattr,
	.getxattr	= generic_getxattr,
	.listxattr	= ext21_listxattr,
	.removexattr	= generic_removexattr,
#endif
};
 
const struct inode_operations ext21_fast_symlink_inode_operations = {
	.readlink	= generic_readlink,
	.get_link	= simple_get_link,
	.setattr	= ext21_setattr,
#ifdef CONFIG_EXT21_FS_XATTR
	.setxattr	= generic_setxattr,
	.getxattr	= generic_getxattr,
	.listxattr	= ext21_listxattr,
	.removexattr	= generic_removexattr,
#endif
};
