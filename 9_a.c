#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    int fd1, fd2;
    char buffer[100];
    int n;

    fd1 = open("source.txt", O_RDONLY);

    if (fd1 < 0)
    {
        printf("Source file not found\n");
        exit(1);
    }

    fd2 = open("dest.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);

    printf("Reading from source file...\n");

    n = read(fd1, buffer, sizeof(buffer));

    printf("Writing into destination file...\n");

    write(fd2, buffer, n);

    printf("File copied successfully\n");

    close(fd1);
    close(fd2);

    return 0;
}