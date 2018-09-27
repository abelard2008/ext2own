/*
 * linux/fs/ext21/xattr_trusted.c
 * Handler for trusted extended attributes.
 *
 * Copyright (C) 2003 by Andreas Gruenbacher, <a.gruenbacher@computer.org>
 */

#include "ext21.h"
#include "xattr.h"

static bool
ext21_xattr_trusted_list(struct dentry *dentry)
{
	return capable(CAP_SYS_ADMIN);
}

static int
ext21_xattr_trusted_get(const struct xattr_handler *handler,
		       struct dentry *dentry, const char *name,
		       void *buffer, size_t size)
{
	return ext21_xattr_get(d_inode(dentry), EXT21_XATTR_INDEX_TRUSTED, name,
			      buffer, size);
}

static int
ext21_xattr_trusted_set(const struct xattr_handler *handler,
		       struct dentry *dentry, const char *name,
		       const void *value, size_t size, int flags)
{
	return ext21_xattr_set(d_inode(dentry), EXT21_XATTR_INDEX_TRUSTED, name,
			      value, size, flags);
}

const struct xattr_handler ext21_xattr_trusted_handler = {
	.prefix	= XATTR_TRUSTED_PREFIX,
	.list	= ext21_xattr_trusted_list,
	.get	= ext21_xattr_trusted_get,
	.set	= ext21_xattr_trusted_set,
};
