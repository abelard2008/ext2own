/*
  File: fs/ext21/acl.h

  (C) 2001 Andreas Gruenbacher, <a.gruenbacher@computer.org>
*/

#include <linux/posix_acl_xattr.h>

#define EXT21_ACL_VERSION	0x0001

typedef struct {
	__le16		e_tag;
	__le16		e_perm;
	__le32		e_id;
} ext21_acl_entry;

typedef struct {
	__le16		e_tag;
	__le16		e_perm;
} ext21_acl_entry_short;

typedef struct {
	__le32		a_version;
} ext21_acl_header;

static inline size_t ext21_acl_size(int count)
{
	if (count <= 4) {
		return sizeof(ext21_acl_header) +
		       count * sizeof(ext21_acl_entry_short);
	} else {
		return sizeof(ext21_acl_header) +
		       4 * sizeof(ext21_acl_entry_short) +
		       (count - 4) * sizeof(ext21_acl_entry);
	}
}

static inline int ext21_acl_count(size_t size)
{
	ssize_t s;
	size -= sizeof(ext21_acl_header);
	s = size - 4 * sizeof(ext21_acl_entry_short);
	if (s < 0) {
		if (size % sizeof(ext21_acl_entry_short))
			return -1;
		return size / sizeof(ext21_acl_entry_short);
	} else {
		if (s % sizeof(ext21_acl_entry))
			return -1;
		return s / sizeof(ext21_acl_entry) + 4;
	}
}

#ifdef CONFIG_EXT21_FS_POSIX_ACL

/* acl.c */
extern struct posix_acl *ext21_get_acl(struct inode *inode, int type);
extern int ext21_set_acl(struct inode *inode, struct posix_acl *acl, int type);
extern int ext21_init_acl (struct inode *, struct inode *);

#else
#include <linux/sched.h>
#define ext21_get_acl	NULL
#define ext21_set_acl	NULL

static inline int ext21_init_acl (struct inode *inode, struct inode *dir)
{
	return 0;
}
#endif

