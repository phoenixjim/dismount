#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>
#include <stdbool.h>

int checkDir(char* directory)
{
    DIR* dir = opendir(directory);
    if (directory) {
        /* Directory exists. */
        closedir(dir);
        return 1;
    } else if (ENOENT == errno) {
        /* Directory does not exist. */
        return 0;
    } else {
        /* opendir() failed for some other reason. */
        return 0;
    }
}
void usage()
{
    printf("Dismount [m,d] [mount point in fstab]\n\tm = mount, d = umount\n\n");
}

int main( int argc, char *argv[] )
{
    char mcommand[300] = "sudo mount ";
	char dcommand[300] = "sudo umount ";
	
    if ( argc != 3 || !checkDir( argv[2]) ) {
		usage();
		return 1;
    }

    setuid(0);
    if ( !strcmp( argv[1],"m" ) ) {
    	strcat( mcommand,argv[2] );
    	system ( mcommand );
    }
    else if ( !strcmp( argv[1],"d" ) ) {
    	strcat( dcommand ,argv[2] );
	    system(dcommand);
    }
    else {
        usage();
        return 1;
    }
    return 0;
}

