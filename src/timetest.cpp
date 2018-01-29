#include <time.h> 
#include <stdlib.h>
#include <stdio.h> 
#include <string.h>
int main( void ) 
{ 
    char test[100];
    scanf("%[^\n]",&test);
    getchar();
    printf("%s\n", test);
    bool tttt = strcmp(test,"ccc ccc");
    printf("%d\n", tttt);
    sprintf(test,"test for sprintf");
    printf("%s\n", test);
    time_t t = time(0); 
    char tmp[64]; 
    strftime( tmp, sizeof(tmp), "%Y_%m_%d_%H-%M-%S",localtime(&t) ); 
    puts( tmp ); 
    char f_name[64];
    strcpy(f_name, "../logs/");
    strcat(f_name, tmp);
    strcat(f_name, ".log");
    puts(f_name);
    FILE *log;
    log = fopen(f_name, "w");
    system("PAUSE");    return 0; 
}