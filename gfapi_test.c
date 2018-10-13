#include <glusterfs/api/glfs.h>
#include <glusterfs/api/glfs-handles.h>
#include <stdio.h>
#include <string.h>

int
main()
{
	int ret_value;
	glfs_t *fs;
	glfs_fd_t *fd;
	char volname[] = "test";
	char log_file[] = "/tmp/test_gluster.log";
	char hostname[] = "localhost";
	char filename[] = "file1";
	char buf[] = "Hello World";

	fs = glfs_new(volname);
	if (!fs) {
		printf("\nglfs_new failed");
		return -1;
	}

	ret_value = glfs_set_volfile_server(fs, "tcp", hostname, 24007);
	if (ret_value < 0) {
		printf("\nglfs_set_volfile_server failed ret_value:%d", ret_value);
		return -1;
	}

	ret_value = glfs_set_logging(fs, log_file, 7);
	if (ret_value < 0) {
		printf("\nglfs_set_logging failed ret_value:%d", ret_value);
		return -1;
	}

	ret_value = glfs_init(fs);
	if (ret_value < 0) {
		printf("\nglfs_init failed ret_value:%d", ret_value);
		return -1;
	}

	fd = NULL;
	fd = glfs_creat (fs, filename, O_RDWR, 0644);
	if (fd == NULL) {
		printf("\nglfs_create failed ret_value:%d", ret_value);
		return -1;
	}

	ret_value = glfs_write (fd, buf, strlen(buf), 0);
	if (ret_value < 0) {
		printf("\nglfs_write failed ret_value:%d", ret_value);
		return -1;
	}

	ret_value = glfs_close (fd);
	if (ret_value < 0) {
		printf("\nglfs_close failed ret_value:%d", ret_value);
		return -1;
	}

	ret_value = glfs_fini(fs);
	if (ret_value < 0) {
		printf("glfs_fini failed with ret_value: %d", ret_value);
		return -1;
	}

	return 0;
}
