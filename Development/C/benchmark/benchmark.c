/*
	Simple File System Benchmark
	Copyright (C) 2018 Prof. Ki-Woong Park., Sejong Univ. <woongbak@sejong.ac.kr>

*/

#define _GNU_SOURCE

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <malloc.h>

const int NUMFILES = 1;
const int FILESIZE = 1 * 1024 *1024;

char *dirname;
int req_size;
ssize_t act_size;


void usage(char *prog)
{
	fprintf(stderr, "Usage: %s <working directory> <request size>\n", prog);
	exit(1);
}


long gettimeusec(){
	struct timeval time;
	long usec; 

	gettimeofday(&time, NULL);

	usec = (time.tv_sec * 1000000 + time.tv_usec);
	return usec;
}



void file_create(){
	int i, fd = 0;
	char filename[128];


	/* Create phase */
	for (i = 0; i < NUMFILES; i++) {
		snprintf(filename, 128, "%s/file-%d", dirname,  i);
		fd = open(filename, O_WRONLY | O_CREAT | O_EXCL , S_IWUSR | S_IRUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
		if (fd == -1) {
			perror("open");
			exit(1);
		}
		close(fd);
	}
	printf ("File Created .. \n");
	return;
}


void file_delete(){
	int i, ret;

	char filename[128];

	/* Unlink phase */
	for (i = 0; i < NUMFILES; i++) {
		snprintf(filename, 128, "%s/file-%d", dirname, i);
		ret = unlink(filename);
		if (ret == -1) {
			perror("unlink");
			exit(1);
		}
	}
	return;
}


void file_write_sequential(){
	int i, j, fd, ret;
	char filename[128];
	ssize_t act_size;
	

	char *buf  = (char *) (memalign((size_t)req_size,(size_t) req_size));

	//buf = (char *)malloc(req_size);
	if (!buf) {
		fprintf(stderr, "ERROR: Failed to allocate buffer");
		exit(1);
	}

	
	for (i = 0; i < NUMFILES; i++) {
		snprintf(filename, 128, "%s/file-%d", dirname, i);
		fd = open(filename, O_DIRECT | O_WRONLY |  O_EXCL, S_IWUSR | S_IRUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
		//fd = open(filename,  O_WRONLY |  O_EXCL, S_IWUSR | S_IRUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);

		if (fd == -1) {
			perror("open");
			exit(1);
		}
		printf ("File Opened Sequential Write .. \n");

		for( j = 0; j < FILESIZE; j += req_size){
			act_size = write(fd, buf, req_size);
			if (act_size == -1) {
				perror("write");
				exit(1);
			}
		}

		close(fd);
	}
	return;
}



void file_read_sequential(){
	int i, j, fd;
	char filename[128];

	char *buf = (char *) malloc(req_size);

	for (i = 0; i < NUMFILES; i++) {
		snprintf(filename, 128, "%s/file-%d", dirname, i);
		fd = open(filename,  O_RDONLY |  O_EXCL, S_IWUSR | S_IRUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);

		if (fd == -1) {
			perror("open");
			exit(1);
		}
		printf ("File Opened Sequential Read .. \n");

		for( j = 0; j < FILESIZE; j += req_size){
			act_size = read(fd, buf, req_size);
			if (act_size == -1) {
				perror("read");
				exit(1);
			}
		}

		close(fd);
	}


	return;
}


void file_write_random(){
	int i, j, fd, ret, num;
	char filename[128];
	ssize_t act_size;
	

	char *buf  = (char *) (memalign((size_t)req_size,(size_t) req_size));

	//buf = (char *)malloc(req_size);
	if (!buf) {
		fprintf(stderr, "ERROR: Failed to allocate buffer");
		exit(1);
	}

	
	for (i = 0; i < NUMFILES; i++) {
		snprintf(filename, 128, "%s/file-%d", dirname, i);
		fd = open(filename, O_DIRECT | O_WRONLY |  O_EXCL, S_IWUSR | S_IRUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
		//fd = open(filename,  O_WRONLY |  O_EXCL, S_IWUSR | S_IRUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);

		if (fd == -1) {
			perror("open");
			exit(1);
		}
		printf ("File Opened Random Write .. \n");

		for( j = 0; j < FILESIZE; j += req_size){
			num = rand()%(FILESIZE/req_size);
			lseek(fd, num * req_size, SEEK_SET);
			act_size = write(fd, buf, req_size);
			if (act_size == -1) {
				perror("write");
				exit(1);
			}
		}

		close(fd);
	}
	return;
}


void file_read_random(){
	int i, j, fd, num;
	char filename[128];

	char *buf = (char *) malloc(req_size);

	for (i = 0; i < NUMFILES; i++) {
		snprintf(filename, 128, "%s/file-%d", dirname, i);
		fd = open(filename,  O_RDONLY |  O_EXCL, S_IWUSR | S_IRUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);

		if (fd == -1) {
			perror("open");
			exit(1);
		}
		printf ("File Opened Random Read .. \n");

		for( j = 0; j < FILESIZE; j += req_size){
			num = rand()%(FILESIZE/req_size);
			lseek(fd, num * req_size, SEEK_SET);
			act_size = read(fd, buf, req_size);
			if (act_size == -1) {
				perror("read");
				exit(1);
			}
		}

		close(fd);
	}

	return;
}



int main(int argc, char **argv)
{
	long creat_time_sequential, write_time_sequential, read_time_sequential, delete_time_sequential, end_time_sequential;
	long creat_time_random, write_time_random, read_time_random, delete_time_random, end_time_random;

	if (argc != 3) {
		usage(argv[0]);
	}
	dirname = argv[1];
	req_size = atoi( argv[2] );

	// Sequential Access Test
	creat_time_sequential = gettimeusec();
	file_create();


	write_time_sequential = gettimeusec();	
	file_write_sequential();


	read_time_sequential = gettimeusec();
	file_read_sequential();

	

	// Random Access Test

	srand(30);	

	write_time_random = gettimeusec();
	file_write_random();


	read_time_random = gettimeusec();
	file_read_random();

	
	delete_time_random = gettimeusec();
	file_delete();

	end_time_random=gettimeusec();




	printf("==============  File System Benchmark Execution Result (Time usec)  ==============\n");
	printf("File Create\t : \t%10ld\n",write_time_sequential-creat_time_sequential);
	printf("Sequential Write : \t%10ld\n",read_time_sequential-write_time_sequential);
	printf("Sequential Read\t : \t%10ld\n",write_time_random-read_time_sequential);
	printf("Random Write\t : \t%10ld\n",read_time_random - write_time_random);
	printf("Random Read\t : \t%10ld\n",delete_time_random-read_time_random);
	printf("File Delete\t : \t%10ld\n",end_time_random-delete_time_random);
	printf("Total\t\t : \t%10ld\n",end_time_random - creat_time_sequential);

	printf("==================================================================================\n");


}
