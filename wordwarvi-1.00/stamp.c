#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	struct timeval tv;
	int uid;

	gettimeofday(&tv, NULL);
	uid = getuid();

	printf("static int builder = %d;\n", uid);
	printf("static uint64_t builtat = %d;\n", tv.tv_sec);

	exit(0);	
}
