#include "myscp.h"

int main(int argc, char** argv) {
    // check arguments 
    if (argc != 4){
        fprintf(stderr, "Incorrect number of arguments. Provide <flag>, <source_file> and <remote_server>\n");
        exit(EXIT_FAILURE);
    }
    //flag (either "-s" or "-c") indicates WHO WE ARE
    char *flag = argv[1]; 
    char *dest, *file;

    // determine which remote to open
    if (strcmp(flag, "-s") == 0) {
        file = argv[2];
        dest = argv[3];
        // open DEST as client and Local as server

    } else {
        file = argv[3];
        dest = argv[2];
        // open DEST as server and Local as client

    }


    return EXIT_SUCCESS;
}