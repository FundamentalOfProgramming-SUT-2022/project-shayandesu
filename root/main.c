#include <conio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* saver;

//Creating a File
void create()
{
    char c, str[200];
    char *s = (char*)malloc(200);

    scanf("%s", s);

    if(strcmp(s, "--file")){
        gets(s);
        printf("Invalid Input\n");
        return;
    }

    free(s);

    scanf("%c", &c);

    gets(str);

    printf("\nYour chosen path: %s\n\n", str);

    char* str_ = (char*)calloc(200, sizeof(char));

    int i = 0;

    while(1){
        if(str[i]=='\\'){
            int check = mkdir(str_);
            if(check)
                printf("\nUnable to create folder or the path already exists.\n");
        }
        str_[i] = str[i];
        i++;
        if(str[i]=='\0'){
            str_[i] = '\0';
            break;
        }
    }

    FILE* fp;

    fp = fopen(str, "w+");

    fclose(fp);
}

//Inserting a String
void insertstr()
{
    char *str, *s, *address;
    address = (char*)calloc(500, sizeof(char));
    str = (char*)calloc(150, sizeof(char));
    s = (char*)calloc(150, sizeof(char));

    scanf("%s", s);
    //printf("%s\n", s);
    if(strcasecmp(s, "--file")){
        gets(s);
        printf("Invalid input.\n");
        return;
    }

    while(1){
        scanf("%s", str);
        //printf("%s\n", str);
        if(!strcmp(str, "--str")){
            //printf("SHIT\n");
            break;}
        strcat(address, str);
        strcat(address, " ");
        str = (char*)calloc(150, sizeof(char));
    }


    FILE* fp = NULL;
    fp = fopen(address, "r+");
    if(fp==NULL){
        gets(str);
        printf("The directory you entered does not exist.\nTry creating it using <createfile> command.\n\n");
    }

    //printf("\n\n==== 3 =====\n\n");

    if(strcasecmp(str, "--str")){
        gets(str);
        printf("Invalid input.\n");
        return;
    }

    char* text = (char*)calloc(500, sizeof(char));
    free(str);

    //printf("\n\n==== 4 =====\n\n");

    while(1){
        scanf("%s", str);
        //printf("%s\n", str);
        if(!strcmp(str, "--pos")){
            //printf("SHIT\n");
            break;
        }
        strcat(text, str);
        strcat(text, " ");
        //printf("SHIIIIIT\n");
        //str = (char*)calloc(150, sizeof(char));
    }

    //printf("Desired text: %s\n", text);

    int len = strlen(text);

    for(int i = 0; i < len-1; i++){
        if( (text[i]=='\\') && (text[i+1]=='n') ){
            text[i] = ' ';
            text[i+1] = '\n';
        }
    }

    char get;
    int line, ch, i = 1,j = 1;
    scanf(" <%d:%d>", &line, &ch);

    //printf("Line: %d | Character: %d\n", line, ch);

    while(i < line){
        printf("Line: %d | Character: %d\n", line, ch);
        get = fgetc(fp);
        if(get==EOF){
            printf("Invalid position.\n");
            return;
        }
        printf("| %c", get);
        if(get=='\n')
            i++;
        //int a = ftell(fp);
        //printf(" %d |\n", a);
    }

    while(j < ch){
        get = fgetc(fp);
        if(get=='\n'){
            printf("Invalid position.\n");
            return;
        }
        //printf("%c | ", get);
        j++;
    }


    long int here = ftell(fp);
    fseek(fp, 0L, SEEK_END);
    long int end = ftell(fp);

    long int buf_size = end - here;
    fseek(fp, here, SEEK_SET);
    char* buffer = (char*)calloc(buf_size, sizeof(char));
    fread(buffer, 1, buf_size, fp);
    printf("buffer: %s\n", buffer);
    fseek(fp, here, SEEK_SET);

    fputs(text, fp);
    fputs(buffer, fp);

    fclose(fp);
}


//Showing a file
void cat()
{
    char* s = (char*)malloc(200);
    char c;
    scanf("%s", s);
    if(strcasecmp(s, "--file")){
        gets(s);
        printf("Invalid input.\n");
        return;
    }
    scanf("%c", &c);
    free(s);
    s = (char*)malloc(200);
    gets(s);
    //printf("%s", s);

    FILE* fp = NULL;
    fp = fopen(s, "r");
    if(fp==NULL){
        printf("The directory you entered does not exist.\nTry creating it using <createfile> command.\n\n");
        return;
    }

    while(c != EOF){
        c = fgetc(fp);
        printf("%c", c);
    }
    printf("\n");
    free(s);
    fclose(fp);
}

//Removing a string
void removestr()
{
    char* buffer = (char*)malloc(4000);
    char s[300];
    char c;
    scanf("%s", s);
    if(strcmp(s, "--file")){
        gets(s);
        printf("Invalid input.\n");
        return;
    }
    scanf("%c", &c);
    char address[300] = "";
    char *str= (char*)malloc(300);

    while(1){
        scanf("%s", str);
        //printf("%s\n", str);
        if(!strcmp(str, "--pos")){
            //printf("SHIT\n");
            break;}
        strcat(address, str);
        strcat(address, " ");
        str = (char*)calloc(150, sizeof(char));
    }

    //printf("Address is: %s\n", address);
    FILE* fp = NULL;
    fp = fopen(address, "r");
    if(fp==NULL){
        printf("The directory you entered does not exist.\nTry creating it using <createfile> command.\n\n");
        return;
    }

    strcpy(s, str);
    if(strcmp(s, "--pos")){
        gets(s);
        printf("Invalid input.\n");
        return;
    }
    int line, ch;
    long int len;
    scanf(" <%d:%d> ", &line, &ch);
    //printf("Line %d | Char %d\n", line, ch);

    scanf("%s", s);
    if(strcmp(s, "-size")){
        gets(s);
        printf("Invalid input.\n");
        return;
    }
    scanf(" %ld ", &len);
    //printf("Size: %ld\n", len);

    scanf("%s", s);
    int i = 1, j = 1;
    char get;

    while(i < line){
        get = fgetc(fp);
        if(get==EOF){
            printf("Invalid position.\n");
            return;
        }
        //printf("| %c", get);
        if(get=='\n'){
            //printf("Incremented\n");
            i++;
        }
        //int a = ftell(fp);
        //printf(" %d |\n", a);
    }

    while(j < ch){
        get = fgetc(fp);
        if(get=='\n'){
            printf("Invalid position.\n");
            return;
        }
        //printf("%d %c | ", j, get);
        j++;
    }

    long int here = ftell(fp);

    if(!strcmp(s, "-f")){

        long int start = here + 1L;
        fseek(fp, len, SEEK_CUR);
        long int end = ftell(fp);
        fseek(fp, 0L, SEEK_SET);
        char ch;
        i = 0;

        while(ch != EOF){
            ch = fgetc(fp);
            if( (ftell(fp) >= start) && (ftell(fp) <= end) )
                continue;
            buffer[i] = ch;
            i++;
        }

        fclose(fp);
        fp = fopen(address, "w+");
        fputs(buffer, fp);
        fclose(fp);
        free(buffer);
    }
    else if(!strcmp(s, "-b")){
        long int end = here + 1;
        fseek(fp, -len + 2, SEEK_CUR);
        long int start = ftell(fp);
        fseek(fp, 0L, SEEK_SET);
        char ch;
        i = 0;

        while(ch != EOF){
            ch = fgetc(fp);
            if( (ftell(fp) >= start) && (ftell(fp) <= end) )
                continue;
            buffer[i] = ch;
            i++;
        }

        fclose(fp);
        fp = fopen(address, "w+");
        fputs(buffer, fp);
        fclose(fp);
        free(buffer);
    }
    else{
        printf("Invalid input.\n");
        return;
    }
}

//Copying text from a string
void copystr()
{
    free(saver);
    saver = (char*)malloc(1000);
    char s[300];
    char c;
    scanf("%s", s);
    if(strcmp(s, "--file")){
        gets(s);
        printf("Invalid input.\n");
        return;
    }
    scanf("%c", &c);
    char address[300] = "";
    char *str= (char*)malloc(300);

    while(1){
        scanf("%s", str);
        //printf("%s\n", str);
        if(!strcmp(str, "--pos")){
            //printf("SHIT\n");
            break;}
        strcat(address, str);
        strcat(address, " ");
        str = (char*)calloc(150, sizeof(char));
    }

    //printf("Address is: %s\n", address);
    FILE* fp = NULL;
    fp = fopen(address, "r");
    if(fp==NULL){
        printf("The directory you entered does not exist.\nTry creating it using <createfile> command.\n\n");
        return;
    }

    strcpy(s, str);
    if(strcmp(s, "--pos")){
        gets(s);
        printf("Invalid input.\n");
        return;
    }
    int line, ch;
    long int len;
    scanf(" <%d:%d> ", &line, &ch);
    //printf("Line %d | Char %d\n", line, ch);

    scanf("%s", s);
    if(strcmp(s, "-size")){
        gets(s);
        printf("Invalid input.\n");
        return;
    }
    scanf(" %ld ", &len);
    //printf("Size: %ld\n", len);

    scanf("%s", s);
    int i = 1, j = 1;
    char get;

    while(i < line){
        get = fgetc(fp);
        if(get==EOF){
            printf("Invalid position.\n");
            return;
        }
        //printf("| %c", get);
        if(get=='\n'){
            //printf("Incremented\n");
            i++;
        }
        //int a = ftell(fp);
        //printf(" %d |\n", a);
    }

    while(j < ch){
        get = fgetc(fp);
        if(get=='\n'){
            printf("Invalid position.\n");
            return;
        }
        //printf("%d %c | ", j, get);
        j++;
    }

    //long int here = ftell(fp);

    if(!strcmp(s, "-f")){
        i = 0;

        while(i < len){
            c = fgetc(fp);
            saver[i] = c;
            i++;
        }
        saver[i] = '\0';
    }
    else if(!strcmp(s, "-b")){
        fseek(fp, -len+1L, SEEK_CUR);
        i = 0;

        while(i <= len){
            c = fgetc(fp);
            saver[i] = c;
            i++;
        }
        saver[i] = '\0';
    }
    else{
        printf("Invalid input.\n");
        return;
    }
}

//Cutting a text inside a file
void cutstr()
{
    free(saver);
    saver = (char*)malloc(1000);
    char* buffer = (char*)malloc(4000);
    char s[300];
    char c;
    scanf("%s", s);
    if(strcmp(s, "--file")){
        gets(s);
        printf("Invalid input.\n");
        return;
    }
    scanf("%c", &c);
    char address[300] = "";
    char *str= (char*)malloc(300);

    while(1){
        scanf("%s", str);
        //printf("%s\n", str);
        if(!strcmp(str, "--pos")){
            //printf("SHIT\n");
            break;}
        strcat(address, str);
        strcat(address, " ");
        str = (char*)calloc(150, sizeof(char));
    }

    //printf("Address is: %s\n", address);
    FILE* fp = NULL;
    fp = fopen(address, "r");
    if(fp==NULL){
        printf("The directory you entered does not exist.\nTry creating it using <createfile> command.\n\n");
        return;
    }

    strcpy(s, str);
    if(strcmp(s, "--pos")){
        gets(s);
        printf("Invalid input.\n");
        return;
    }
    int line, ch;
    long int len;
    scanf(" <%d:%d> ", &line, &ch);
    //printf("Line %d | Char %d\n", line, ch);

    scanf("%s", s);
    if(strcmp(s, "-size")){
        gets(s);
        printf("Invalid input.\n");
        return;
    }
    scanf(" %ld ", &len);
    //printf("Size: %ld\n", len);

    scanf("%s", s);
    int i = 1, j = 1;
    char get;

    while(i < line){
        get = fgetc(fp);
        if(get==EOF){
            printf("Invalid position.\n");
            return;
        }
        //printf("| %c", get);
        if(get=='\n'){
            //printf("Incremented\n");
            i++;
        }
        //int a = ftell(fp);
        //printf(" %d |\n", a);
    }

    while(j < ch){
        get = fgetc(fp);
        if(get=='\n'){
            printf("Invalid position.\n");
            return;
        }
        //printf("%d %c | ", j, get);
        j++;
    }

    long int here = ftell(fp);

    if(!strcmp(s, "-f")){
        long int start = here + 1L;
        fseek(fp, len, SEEK_CUR);
        long int end = ftell(fp);
        fseek(fp, 0L, SEEK_SET);
        char ch;
        i = 0;
        j = 0;

        while(ch != EOF){
            ch = fgetc(fp);
            if( (ftell(fp) >= start) && (ftell(fp) <= end) ){
                saver[j] = ch;
                j++;
                continue;
                }
            buffer[i] = ch;
            i++;
        }

        saver[j] = '\0';
        fclose(fp);
        fp = fopen(address, "w+");
        fputs(buffer, fp);
        fclose(fp);
        free(buffer);
    }
    else if(!strcmp(s, "-b")){
        long int end = here + 1;
        fseek(fp, -len + 2, SEEK_CUR);
        long int start = ftell(fp);
        fseek(fp, 0L, SEEK_SET);
        char ch;
        i = 0;
        j = 0;

        while(ch != EOF){
            ch = fgetc(fp);
            if( (ftell(fp) >= start) && (ftell(fp) <= end) ){
                saver[j] = ch;
                j++;
                continue;
                }
            buffer[i] = ch;
            i++;
        }

        saver[j] = '\0';
        fclose(fp);
        fp = fopen(address, "w+");
        fputs(buffer, fp);
        fclose(fp);
        free(buffer);
    }
    else{
        printf("Invalid input.\n");
        return;
    }
}

//Pasting text
void pastestr()
{
    char *str, *s, *address;
    address = (char*)calloc(500, sizeof(char));
    str = (char*)calloc(150, sizeof(char));
    s = (char*)calloc(150, sizeof(char));

    scanf("%s", s);
    //printf("%s\n", s);
    if(strcasecmp(s, "--file")){
        gets(s);
        printf("Invalid input.\n");
        return;
    }

    while(1){
        scanf("%s", str);
        //printf("%s\n", str);
        if(!strcmp(str, "--pos")){
            //printf("SHIT\n");
            break;}
        strcat(address, str);
        strcat(address, " ");
        str = (char*)calloc(150, sizeof(char));
    }


    FILE* fp = NULL;
    fp = fopen(address, "r+");
    if(fp==NULL){
        gets(str);
        printf("The directory you entered does not exist.\nTry creating it using <createfile> command.\n\n");
    }

    //printf("\n\n==== 3 =====\n\n");

    if(strcasecmp(str, "--pos")){
        gets(str);
        printf("Invalid input.\n");
        return;
    }

    char get;
    int line, ch, i = 1,j = 1;
    scanf(" <%d:%d>", &line, &ch);

    //printf("Line: %d | Character: %d\n", line, ch);

    while(i < line){
        get = fgetc(fp);
        if(get==EOF){
            printf("Invalid position.\n");
            return;
        }
        //printf("| %c", get);
        if(get=='\n')
            i++;
        //int a = ftell(fp);
        //printf(" %d |\n", a);
    }

    while(j < ch){
        get = fgetc(fp);
        if(get=='\n'){
            printf("Invalid position.\n");
            return;
        }
        //printf("%c | ", get);
        j++;
    }


    long int here = ftell(fp);
    fseek(fp, 0L, SEEK_END);
    long int end = ftell(fp);

    long int buf_size = end - here;
    fseek(fp, here, SEEK_SET);
    char* buffer = (char*)calloc(buf_size, sizeof(char));
    fread(buffer, 1, buf_size, fp);
    fseek(fp, here, SEEK_SET);

    fputs(saver, fp);
    fputs(buffer, fp);

    fclose(fp);
}

int main()
{
    char* str = (char*)calloc(150, sizeof(char));

    while(1){
        printf("root >>> ");
        scanf("%s", str);

        if(!strcmp(str, "createfile"))
            create();
        else if(!strcmp(str,"insertstr"))
            insertstr();
        else if(!strcmp(str, "cat"))
            cat();
        else if(!strcmp(str, "remove"))
            removestr();
        else if(!strcmp(str, "copystr"))
            copystr();
        else if(!strcmp(str, "cutstr"))
            cutstr();
        else if(!strcmp(str, "pastestr"))
            pastestr();
        else if(!strcmp(str, "exit"))
            return 0;
        else{
            gets(str);
            printf("Invalid input\n");
        }
    }
}

