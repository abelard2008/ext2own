This ext2own is from [linux kernel 4.5](https://kojipkgs.fedoraproject.org/packages/kernel/4.5.5/300.fc24/src/kernel-4.5.5-300.fc24.src.rpm)'s ext2(fs/ext2), and compile and test under Fedora 24(4.5.5-300.fc24.x86_64).

For compiling and testing it individually, I modified the Makefile. For distinguishing from ext2, I changed all ext2/EXT2 into ext21/EXT21 in \\*.c|h, espically, 

	static struct file_system_type ext21_fs_type = {
		.owner		= THIS_MODULE,
		.name		= "ext21",
		.mount		= ext21_mount,
		.kill_sb	= kill_block_super,
		.fs_flags	= FS_REQUIRES_DEV,
	};
	MODULE_ALIAS_FS("ext21");

so, I can mount a filesystem called ext21:



