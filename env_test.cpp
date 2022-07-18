#include <iostream>
#include <string.h>

extern "C" char ** environ;
int main(int argc, char *argv[]) {

    int i = 0;
    for (i = 0; environ[i] != nullptr; i++) {
        std::cout << environ[i] << std::endl;
    }

    char ** environ2 = (char **) malloc(sizeof(char * ) * i);

    for (i = 0; environ[i] != nullptr; i++) {
        environ2[i] = strdup(environ[i]);
    }


    environ = environ2;
    for (i = 0; environ[i] != nullptr; i++) {
        std::cout << environ[i] << std::endl;
    }

    return 0;

}