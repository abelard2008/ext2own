/*
  File: linux/ext21_xattr.h

  On-disk format of extended attributes for the ext21 filesystem.

  (C) 2001 Andreas Gruenbacher, <a.gruenbacher@computer.org>
*/

#include <linux/init.h>
#include <linux/xattr.h>

/* Magic value in attribute blocks */
#define EXT21_XATTR_MAGIC		0xEA020000

/* Maximum number of references to one attribute block */
#define EXT21_XATTR_REFCOUNT_MAX		1024

/* Name indexes */
#define EXT21_XATTR_INDEX_USER			1
#define EXT21_XATTR_INDEX_POSIX_ACL_ACCESS	2
#define EXT21_XATTR_INDEX_POSIX_ACL_DEFAULT	3
#define EXT21_XATTR_INDEX_TRUSTED		4
#define	EXT21_XATTR_INDEX_LUSTRE			5
#define EXT21_XATTR_INDEX_SECURITY	        6

struct ext21_xattr_header {
	__le32	h_magic;	/* magic number for identification */
	__le32	h_refcount;	/* reference count */
	__le32	h_blocks;	/* number of disk blocks used */
	__le32	h_hash;		/* hash value of all attributes */
	__u32	h_reserved[4];	/* zero right now */
};

struct ext21_xattr_entry {
	__u8	e_name_len;	/* length of name */
	__u8	e_name_index;	/* attribute name index */
	__le16	e_value_offs;	/* offset in disk block of value */
	__le32	e_value_block;	/* disk block attribute is stored on (n/i) */
	__le32	e_value_size;	/* size of attribute value */
	__le32	e_hash;		/* hash value of name and value */
	char	e_name[0];	/* attribute name */
};

#define EXT21_XATTR_PAD_BITS		2
#define EXT21_XATTR_PAD		(1<<EXT21_XATTR_PAD_BITS)
#define EXT21_XATTR_ROUND		(EXT21_XATTR_PAD-1)
#define EXT21_XATTR_LEN(name_len) \
	(((name_len) + EXT21_XATTR_ROUND + \
	sizeof(struct ext21_xattr_entry)) & ~EXT21_XATTR_ROUND)
#define EXT21_XATTR_NEXT(entry) \
	( (struct ext21_xattr_entry *)( \
	  (char *)(entry) + EXT21_XATTR_LEN((entry)->e_name_len)) )
#define EXT21_XATTR_SIZE(size) \
	(((size) + EXT21_XATTR_ROUND) & ~EXT21_XATTR_ROUND)

# ifdef CONFIG_EXT21_FS_XATTR

extern const struct xattr_handler ext21_xattr_user_handler;
extern const struct xattr_handler ext21_xattr_trusted_handler;
extern const struct xattr_handler ext21_xattr_security_handler;

extern ssize_t ext21_listxattr(struct dentry *, char *, size_t);

extern int ext21_xattr_get(struct inode *, int, const char *, void *, size_t);
extern int ext21_xattr_set(struct inode *, int, const char *, const void *, size_t, int);

extern void ext21_xattr_delete_inode(struct inode *);
extern void ext21_xattr_put_super(struct super_block *);

extern int init_ext21_xattr(void);
extern void exit_ext21_xattr(void);

extern const struct xattr_handler *ext21_xattr_handlers[];

# else  /* CONFIG_EXT21_FS_XATTR */

static inline int
ext21_xattr_get(struct inode *inode, int name_index,
	       const char *name, void *buffer, size_t size)
{
	return -EOPNOTSUPP;
}

static inline int
ext21_xattr_set(struct inode *inode, int name_index, const char *name,
	       const void *value, size_t size, int flags)
{
	return -EOPNOTSUPP;
}

static inline void
ext21_xattr_delete_inode(struct inode *inode)
{
}

static inline void
ext21_xattr_put_super(struct super_block *sb)
{
}

static inline int
init_ext21_xattr(void)
{
	return 0;
}

static inline void
exit_ext21_xattr(void)
{
}

#define ext21_xattr_handlers NULL

# endif  /* CONFIG_EXT21_FS_XATTR */

#ifdef CONFIG_EXT21_FS_SECURITY
extern int ext21_init_security(struct inode *inode, struct inode *dir,
			      const struct qstr *qstr);
#else
static inline int ext21_init_security(struct inode *inode, struct inode *dir,
				     const struct qstr *qstr)
{
	return 0;
}
#endif
