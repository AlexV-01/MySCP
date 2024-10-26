#include "client.c"
#include "server.c"

/* Determine if WE are the server*/
int isServer(char* flag){
    return flag=="-s"; 
}

int main(int argc, char** argv) {
    // check arguments 
    if (argc != 4){
        fprintf(stderr,"Not correct number of arguments. Provide flag, source_file and remote server");
    }
    //flag (either "-s" or "-c") indicates WHO WE ARE
    char *flag = argv[1]; 
    char *dest, *file;

    if (isServer(flag)) { // we are the server; I want to send FILE to DEST
        file = argv[2];
        dest = argv[3];
    } else { // we are the client; I want DEST to send me FILE
        file = argv[3];
        dest = argv[2];
    }

    // determine which remote to open
    if (isServer(flag)) {
        // open DEST as client and Local as server

    } else {
        // open DEST as server and Local as client

    }


    return EXIT_SUCCESS;
}