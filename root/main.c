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

    if(strcasecmp(str, "--str")){
        gets(str);
        printf("Invalid input.\n");
        return;
    }

    char* text = (char*)calloc(500, sizeof(char));
    free(str);

    while(1){
        scanf("%s", str);
        //printf("%s\n", str);
        if(!strcmp(str, "--pos"))
            break;
        strcat(text, str);
        strcat(text, " ");
        //str = (char*)calloc(150, sizeof(char));
    }

    //printf("Desired text: %s\n", text);

    int len = strlen(text), m = 0, n = 0;
    char* text_ = (char*)malloc(len);

    while(m<len){
        if( (text[m]=='\\') && (text[m+1]=='n') ){
            text_[n] = '\n';
            n++;
            m += 2;
            continue;
        }
        if( (text[m]=='\\') && (text[m+1]=='\\')){
            text_[n] = '\\';
            n++;
            m += 2;
            continue;
        }
        text_[n] = text[m];
        n++;
        m++;
    }

    strcpy(text, text_);
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
    //printf("buffer: %s\n", buffer);
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
        if(!strcmp(str, "--pos"))
            break;
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

//Finding the number of occurrence of a text inside a file
void find_count()
{
    char c;
    char *str, *s, *address;
    address = (char*)calloc(500, sizeof(char));
    str = (char*)calloc(150, sizeof(char));
    s = (char*)calloc(150, sizeof(char));

    scanf("%s", s);
    if(strcasecmp(s, "--file")){
        gets(s);
        printf("Invalid input.\n");
        return;
    }

    while(1){
        scanf("%s", str);
        //printf("%s\n", str);
        if(!strcmp(str, "--str"))
            break;
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
    if(strcasecmp(str, "--str")){
        gets(str);
        printf("Invalid input.\n");
        return;
    }
    scanf("%c", &c);
    char* text = (char*)calloc(500, sizeof(char));
    free(str);
    gets(text);
    long int len = strlen(text);
    char* buffer = (char*)malloc(len);
    fseek(fp, -len, SEEK_END);
    long int end = ftell(fp);
    int counter = 0;
    int leng = strlen(text), j = 0, i = 0;
    char* text_ = (char*)malloc(len);

    while(i<leng){
        if( (text[i]=='\\') && (text[i+1]=='n') ){
            text_[j] = '\n';
            j++;
            i += 2;
            continue;
        }
        if( (text[i]=='\\') && (text[i+1]=='\\')){
            text_[j] = '\\';
            j++;
            i += 2;
            continue;
        }
        if( (text[i]=='\\') && (text[i+1]=='*')){
            text_[j] = '*';
            j++;
            i += 2;
        }
        text_[j] = text[i];
        j++;
        i++;
    }
    text_[j] = '\0';
    strcpy(text, text_);
    printf("Text is: |%s|\nText_ is: %s\n", text, text_);
    for(long int i = 0; i < end; i++){
        int j = 0, id = 0;
        fseek(fp, i, SEEK_SET);
        for(j = 0; j < len; j++){
            c = fgetc(fp);
            if(c==EOF){
                id = 1;
                break;
            }
            buffer[j] = c;
        }
        buffer[j] = '\0';
        if(id==1)
            break;
        printf("|%s|\n", buffer);
        if(!strcmp(buffer, text))
            counter++;
    }
    printf("Total number of recurrence: %d\n", counter);
}

//Finding the nth recurrence
void find_at()
{
    char c;
    char *str, *s, *address;
    address = (char*)calloc(500, sizeof(char));
    str = (char*)calloc(150, sizeof(char));
    s = (char*)calloc(150, sizeof(char));
    int num = 0;
    scanf("%d", &num);
    scanf("%c", &c);
    scanf("%s", s);
    if(strcasecmp(s, "--file")){
        gets(s);
        printf("Invalid input.\n");
        return;
    }

    while(1){
        scanf("%s", str);
        //printf("%s\n", str);
        if(!strcmp(str, "--str"))
            break;
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
    if(strcasecmp(str, "--str")){
        gets(str);
        printf("Invalid input.\n");
        return;
    }
    scanf("%c", &c);
    char* text = (char*)calloc(500, sizeof(char));
    free(str);
    gets(text);
    long int len = strlen(text);
    char* buffer = (char*)malloc(len);
    fseek(fp, -len, SEEK_END);
    long int end = ftell(fp);
    int counter = 0;
    int leng = strlen(text), j = 0, i = 0;
    char* text_ = (char*)malloc(len);

    while(i<leng){
        if( (text[i]=='\\') && (text[i+1]=='n') ){
            text_[j] = '\n';
            j++;
            i += 2;
            continue;
        }
        if( (text[i]=='\\') && (text[i+1]=='\\')){
            text_[j] = '\\';
            j++;
            i += 2;
            continue;
        }
        if( (text[i]=='\\') && (text[i+1]=='*')){
            text_[j] = '*';
            j++;
            i += 2;
        }
        text_[j] = text[i];
        j++;
        i++;
    }
    text_[j] = '\0';
    strcpy(text, text_);
    //printf("Text is: |%s|\nText_ is: %s\n", text, text_);
    for(long int i = 0; i < end; i++){
        int j = 0, id = 0;
        fseek(fp, i, SEEK_SET);
        for(j = 0; j < len; j++){
            c = fgetc(fp);
            if(c==EOF){
                id = 1;
                break;
            }
            buffer[j] = c;
        }
        buffer[j] = '\0';
        if(id==1)
            break;
        //printf("|%s|\n", buffer);
        if(!strcmp(buffer, text))
            counter++;
        if(counter == num){
            printf("The %dth time of recurrence is at character: %ld\n", num, i+1);
            return;
        }
    }
    printf("The %dth time of recurrence is at character: -1 (There are not this many recurrences in this text.)\n", num);
}

//Finding recurrence by word
void find_byword()
{
    char c;
    char *str, *s, *address;
    address = (char*)calloc(500, sizeof(char));
    str = (char*)calloc(150, sizeof(char));
    s = (char*)calloc(150, sizeof(char));
    int word_counter = 0;
    scanf("%s", s);

    if(strcasecmp(s, "--file")){
        gets(s);
        printf("Invalid input.\n");
        return;
    }

    while(1){
        scanf("%s", str);
        //printf("%s\n", str);
        if(!strcmp(str, "--str"))
            break;
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

    if(strcasecmp(str, "--str")){
        gets(str);
        printf("Invalid input.\n");
        return;
    }

    scanf("%c", &c);
    char* text = (char*)calloc(500, sizeof(char));
    free(str);
    gets(text);
    long int len = strlen(text);
    char* buffer = (char*)malloc(len);
    fseek(fp, 0L, SEEK_END);
    long int end = ftell(fp);
    int id = 0;

    for(long int i = 0; i < end; i++){
        int j = 0;
        c = fgetc(fp);
        if(c==' ' || c=='\n')
            word_counter++;
        fseek(fp, i, SEEK_SET);
        for(j = 0; j < len; j++){
            c = fgetc(fp);
            if(c==EOF){
                id = 1;
                break;
            }
            buffer[j] = c;
        }
        buffer[j] = '\0';
        if(id==1)
            break;
        //printf("|%s|\n", buffer);
        if(!strcmp(buffer, text)){
            printf("Location by word: %d\n", word_counter+1);
            free(text);
            free(buffer);
            return;
        }
    }
    printf("Not found.\n");
}

//Returning all recurrences
void find_all()
{
    char c;
    char *str, *s, *address;
    address = (char*)calloc(500, sizeof(char));
    str = (char*)calloc(150, sizeof(char));
    s = (char*)calloc(150, sizeof(char));
    int word_counter = 0;
    scanf("%s", s);

    if(strcasecmp(s, "--file")){
        gets(s);
        printf("Invalid input.\n");
        return;
    }

    while(1){
        scanf("%s", str);
        //printf("%s\n", str);
        if(!strcmp(str, "--str"))
            break;
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

    if(strcasecmp(str, "--str")){
        gets(str);
        printf("Invalid input.\n");
        return;
    }
    int checker = 0;
    scanf("%c", &c);
    char* text = (char*)calloc(500, sizeof(char));
    free(str);
    gets(text);
    long int len = strlen(text);
    char* buffer = (char*)malloc(len);
    fseek(fp, 0L, SEEK_END);
    long int end = ftell(fp);
    int id = 0;

    for(long int i = 0; i < end; i++){
        int j = 0;
        c = fgetc(fp);
        if(c==' ' || c=='\n'){
            word_counter++;
            //printf("%ld\n", ftell(fp));
        }
        fseek(fp, i, SEEK_SET);
        for(j = 0; j < len; j++){
            c = fgetc(fp);
            if(c==EOF){
                id = 1;
                break;
            }
            buffer[j] = c;
        }
        buffer[j] = '\0';
        if(id==1)
            break;
        //printf("|%s|\n", buffer);
        if(!strcmp(buffer, text)){
            checker = 1;
            printf("%d ", word_counter+1);
        }
    }
    if(checker == 0)
        printf("Not found");
    printf("\n");
}

//Finding location of a certain text inside a file
void findstr()
{
    char c;
    char *str, *s, *address;
    address = (char*)calloc(500, sizeof(char));
    str = (char*)calloc(150, sizeof(char));
    s = (char*)calloc(150, sizeof(char));

    scanf("%s", s);
    if(!strcmp(s, "-count")){
        find_count();
        return;
    }
    if(!strcmp(s, "-at")){
        find_at();
        return;
    }
    if(!strcmp(s, "-byword")){
        find_byword();
        return;
    }
    if(!strcmp(s, "-all")){
        find_all();
        return;
    }

    if(strcasecmp(s, "--file")){
        gets(s);
        printf("Invalid input.\n");
        return;
    }

    while(1){
        scanf("%s", str);
        //printf("%s\n", str);
        if(!strcmp(str, "--str"))
            break;
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

    if(strcasecmp(str, "--str")){
        gets(str);
        printf("Invalid input.\n");
        return;
    }

    scanf("%c", &c);
    char* text = (char*)calloc(500, sizeof(char));
    free(str);
    gets(text);
    long int len = strlen(text);
    char* buffer = (char*)malloc(len);
    fseek(fp, 0L, SEEK_END);
    long int end = ftell(fp);
    int id = 0;

    for(long int i = 0; i < end; i++){
        int j = 0;
        fseek(fp, i, SEEK_SET);
        for(j = 0; j < len; j++){
            c = fgetc(fp);
            if(c==EOF){
                id = 1;
                break;
            }
            buffer[j] = c;
        }
        buffer[j] = '\0';
        if(id==1)
            break;
        if(!strcmp(buffer, text)){
            printf("Location: %ld\n", i+1);
            free(text);
            free(buffer);
            return;
        }
    }
    printf("Not found.\n");
}

//Replace at a particular recurrence
void replace_at()
{
    char c;
    char *str, *s, *address;
    address = (char*)calloc(500, sizeof(char));
    str = (char*)calloc(150, sizeof(char));
    s = (char*)calloc(150, sizeof(char));
    int num;
    scanf("%d", &num);
    scanf("%c", &c);
    scanf("%s", s);
    if(strcasecmp(s, "--file")){
        gets(s);
        printf("Invalid input.\n");
        return;
    }

     while(1){
        scanf("%s", str);
        //printf("%s\n", str);
        if(!strcmp(str, "--str1"))
            break;
        strcat(address, str);
        strcat(address, " ");
        str = (char*)calloc(150, sizeof(char));
    }
    FILE* fp = NULL;
    fp = fopen(address, "rb+");
    if(fp==NULL){
        gets(str);
        printf("The directory you entered does not exist.\nTry creating it using <createfile> command.\n\n");
    }

    if(strcasecmp(str, "--str1")){
        gets(str);
        printf("Invalid input.\n");
        return;
    }
    char* text1 = (char*)calloc(1000, sizeof(char));
    char* text2 = (char*)malloc(1000);
    char* text1tmp = (char*)malloc(100);

    scanf("%c", &c);

    while(1){
        scanf("%c", &c);
        if(c==' '){
            scanf("%s", text1tmp);
            printf("%s\n", text1tmp);
            if(!strcmp(text1tmp, "--str2"))
                break;
            else{
            strcat(text1, " ");
            strcat(text1, text1tmp);
            continue;
            }
        }
        strncat(text1, &c, 1);
        printf("Text: %s\n", text1);
    }

    if(strcasecmp(text1tmp, "--str2")){
        gets(str);
        printf("Invalid input.\n");
        return;
    }
    scanf("%c", &c);
    gets(text2);
    long int len = strlen(text1);
    char* buffer = (char*)malloc(len);
    fseek(fp, 0L, SEEK_END);
    long int end = ftell(fp);
    long int endtext = -1;
    int counter = 0;
    int id = 0;

    for(long int i = 0; i < end; i++){
        int k = 0;
        fseek(fp, i, SEEK_SET);
        for(k = 0; k < len; k++){
            c = fgetc(fp);
            if(c==EOF){
                id = 1;
                break;
            }
            buffer[k] = c;
        }
        buffer[k] = '\0';
        if(id==1)
            break;
        if(!strcmp(buffer, text1))
          counter++;
        if(counter == num){
            endtext = ftell(fp);
            break;
        }
    }
    printf("Text1 is: |%s|\n", text1);
    printf("Text2 is: |%s|\n", text2);
    printf("End of text: %ld \n", endtext);
    if(endtext== -1){
        printf("Not found.\n");
        return;
    }
    long int starttext = endtext - len;
    char buffer1[starttext], buffer2[5000];
    fseek(fp, 0L, SEEK_SET);
    long int i = 0;
    fread(buffer1, 1, starttext, fp);
    fseek(fp, endtext, SEEK_SET);
    for(i = 0; i < end; i++)
        buffer2[i] = fgetc(fp);
    buffer2[i] = '\0';
    fclose(fp);

    printf("starttext is: %ld\n", starttext);
    printf("First buffer: %s\nSecond buffer; %s\n", buffer1, buffer2);
    fp = fopen(address, "w+");
    fputs(buffer1, fp);
    fputs(text2, fp);
    fputs(buffer2, fp);
    fclose(fp);
}

//Replacing all recurrences
void replace_all()
{
    char c;
    char *str, *s, *address;
    address = (char*)calloc(500, sizeof(char));
    str = (char*)calloc(150, sizeof(char));
    s = (char*)calloc(150, sizeof(char));

     scanf("%c", &c);
    scanf("%s", s);
    if(strcasecmp(s, "--file")){
        gets(s);
        printf("Invalid input.\n");
        return;
    }

     while(1){
        scanf("%s", str);
        //printf("%s\n", str);
        if(!strcmp(str, "--str1"))
            break;
        strcat(address, str);
        strcat(address, " ");
        str = (char*)calloc(150, sizeof(char));
    }
    FILE* fp = NULL;
    fp = fopen(address, "rb+");
    if(fp==NULL){
        gets(str);
        printf("The directory you entered does not exist.\nTry creating it using <createfile> command.\n\n");
    }

    if(strcasecmp(str, "--str1")){
        gets(str);
        printf("Invalid input.\n");
        return;
    }
    char* text1 = (char*)calloc(1000, sizeof(char));
    char* text2 = (char*)malloc(1000);
    char* text1tmp = (char*)malloc(100);

    scanf("%c", &c);

    while(1){
        scanf("%c", &c);
        if(c==' '){
            scanf("%s", text1tmp);
            printf("%s\n", text1tmp);
            if(!strcmp(text1tmp, "--str2"))
                break;
            else{
            strcat(text1, " ");
            strcat(text1, text1tmp);
            continue;
            }
        }
        strncat(text1, &c, 1);
        //printf("Text: %s\n", text1);
    }

    if(strcasecmp(text1tmp, "--str2")){
        gets(str);
        printf("Invalid input.\n");
        return;
    }
    scanf("%c", &c);
    gets(text2);
    long int len = strlen(text1);
    char* buffer = (char*)malloc(len), *saver_ = (char*)calloc(10000, sizeof(char)), *save;
    fseek(fp, 0L, SEEK_END);
    long int end = ftell(fp);
    long int starttext = 0;
    int id = 0;

    for(long int i = 0; i < end; i++){
        int j = 0;
        fseek(fp, i, SEEK_SET);
        for(j = 0; j < len; j++){
            c = fgetc(fp);
            if(c == EOF){
                id = 1;
                break;
            }
            buffer[j] = c;
        }
        buffer[j] = '\0';
        if(id==1)
            break;
        if(!strcmp(buffer, text1)){
            long int length = i - starttext;
            fseek(fp, starttext, SEEK_SET);
            save = (char*)malloc(length);
            //fread(save, 1, length, fp);
            long int k;
            for(k = 0; k < length; k++)
                save[k] = fgetc(fp);
            save[k] = '\0';
            strcat(saver_, save);
            strcat(saver_, text2);
            //printf("\n\n\nSave: |%s|\n\n\n", save);
            starttext = i+j;
            free(save);
        }
    }
    long int length = end - starttext;
    save = (char*)malloc(length);
    fseek(fp, starttext, SEEK_SET);
    fread(save, 1, length, fp);
    strcat(saver_, save);
    fclose(fp);

    fp = fopen(address, "w+");
    fputs(saver_, fp);
    fclose(fp);
}

//Replacing a text inside a file
void replace()
{
    char c;
    char *str, *s, *address;
    address = (char*)calloc(500, sizeof(char));
    str = (char*)calloc(150, sizeof(char));
    s = (char*)calloc(150, sizeof(char));

    scanf("%s", s);
    if(!strcmp(s, "-all")){
        replace_all();
        return;
    }
    if(!strcmp(s, "-at")){
        replace_at();
        return;
    }
    if(strcasecmp(s, "--file")){
        gets(s);
        printf("Invalid input.\n");
        return;
    }

     while(1){
        scanf("%s", str);
        //printf("%s\n", str);
        if(!strcmp(str, "--str1"))
            break;
        strcat(address, str);
        strcat(address, " ");
        str = (char*)calloc(150, sizeof(char));
    }


    FILE* fp = NULL;
    fp = fopen(address, "rb+");
    if(fp==NULL){
        gets(str);
        printf("The directory you entered does not exist.\nTry creating it using <createfile> command.\n\n");
    }

    if(strcasecmp(str, "--str1")){
        gets(str);
        printf("Invalid input.\n");
        return;
    }
    char* text1 = (char*)calloc(1000, sizeof(char));
    char* text2 = (char*)malloc(1000);
    char* text1tmp = (char*)malloc(100);

    scanf("%c", &c);

    while(1){
        scanf("%c", &c);
        if(c==' '){
            scanf("%s", text1tmp);
            printf("%s\n", text1tmp);
            if(!strcmp(text1tmp, "--str2"))
                break;
            else{
            strcat(text1, " ");
            strcat(text1, text1tmp);
            continue;
            }
        }
        strncat(text1, &c, 1);
        printf("Text: %s\n", text1);
    }

    if(strcasecmp(text1tmp, "--str2")){
        gets(str);
        printf("Invalid input.\n");
        return;
    }
    scanf("%c", &c);
    gets(text2);
    long int len = strlen(text1);
    char* buffer = (char*)malloc(len);
    fseek(fp, 0L, SEEK_END);
    long int end = ftell(fp);
    long int endtext = -1;

    for(long int i = 0; i < end; i++){
        int j = 0;
        fseek(fp, i, SEEK_SET);
        for(j = 0; j < len; j++){
            c = fgetc(fp);
            buffer[j] = c;
        }
        buffer[j] = '\0';
        if(!strcmp(buffer, text1)){
          endtext = ftell(fp);
          break;
        }
    }
    //printf("Text1 is: |%s|\n", text1);
    //printf("Text2 is: |%s|\n", text2);
    //printf("End of text: %ld \n", endtext);
    if(endtext== -1){
        printf("Not found.\n");
        return;
    }
    long int starttext = endtext - len;
    char buffer1[starttext], buffer2[5000];
    fseek(fp, 0L, SEEK_SET);
    long int i = 0;
    fread(buffer1, 1, starttext, fp);
    fseek(fp, endtext, SEEK_SET);
    for(i = 0; i < end; i++)
        buffer2[i] = fgetc(fp);
    buffer2[i] = '\0';
    fclose(fp);

    printf("starttext is: %ld\n", starttext);
    printf("First buffer: %s\nSecond buffer; %s\n", buffer1, buffer2);
    fp = fopen(address, "w+");
    fputs(buffer1, fp);
    fputs(text2, fp);
    fputs(buffer2, fp);
    fclose(fp);
}

//Searching for a text inside multiple files
void grep()
{
    void grep_finder(char* location, char* rtext);
    int grep_finder_c(char* location, char* rtext);
    void grep_finder_l(char* location, char* rtext);
    char c;
    char *str, *s, *address;
    address = (char*)calloc(500, sizeof(char));
    str = (char*)calloc(150, sizeof(char));
    s = (char*)calloc(150, sizeof(char));
    int option = 0, count = 0;

    scanf("%s", s);
    if(!strcmp(s, "-c")){
        option = 1;
        scanf("%s", s);
        if(strcasecmp(s, "--file")){
            gets(s);
            printf("Invalid input.\n");
            return;
        }
    }
    else if(!strcmp(s, "-l")){
        option = 2;
        scanf("%c", &c);
        scanf("%s", s);
        if(strcasecmp(s, "--file")){
            gets(s);
            printf("Invalid input.\n");
            return;
        }
    }
    else if(strcasecmp(s, "--file")){
        gets(s);
        printf("Invalid input.\n");
        return;
    }

    scanf("%c", &c);
    while(1){
        scanf("%s", str);
        //printf("%s\n", str);
        if(!strcmp(str, "--str"))
            break;
        strcat(address, str);
        strcat(address, " ");
        str = (char*)calloc(150, sizeof(char));
    }

    scanf("%c", &c);
    if(strcasecmp(str, "--str")){
        gets(str);
        printf("Invalid input.\n");
        return;
    }
    char text[100];
    gets(text);

    int i = 0, j = 0;
    char* buffer = (char*)malloc(50);
    while(address[i] != '\0'){
        if(address[i] == ' '){
            buffer[j] = '\0';
            if(option == 0)
                grep_finder(buffer, text);
            else if(option == 1)
                count += grep_finder_c(buffer, text);
            else if(option == 2)
                grep_finder_l(buffer, text);
            free(buffer);
            buffer = (char*)malloc(50);
            i++;
            j = 0;
        }
        else{
            buffer[j] = address[i];
            j++;
            i++;
        }
    }
    if(option==1) printf("Number of lines: %d\n", count);
    if(option==2) printf("\n");
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
        else if(!strcmp(str, "find"))
            findstr();
        else if(!strcmp(str, "replace"))
            replace();
        else if(!strcmp(str, "grep"))
            grep();
        else if(!strcmp(str, "exit"))
            return 0;
        else{
            gets(str);
            printf("Invalid input\n");
        }
    }
}

/////////////////////////////////
//////    grep functions   //////
/////////////////////////////////

void grep_finder(char* location, char* rtext)
{
    char c;
    FILE *fp = NULL;
    fp = fopen(location, "rb+");
    if(fp == NULL)
        return;
    fseek(fp, 0L, SEEK_END);
    long int len = strlen(rtext);
    long int end = ftell(fp);
    char* buffer = (char*)malloc(len);
    fseek(fp, 0L, SEEK_SET);
    long int line_start = 0, line_end = 0;

    for(long int i = 0; i < end; i++){
        int j = 0;
        fseek(fp, i, SEEK_SET);
        if(fgetc(fp)=='\n')
            line_start = ftell(fp);
        fseek(fp, i, SEEK_SET);
        for(j = 0; j < len; j++){
            c = fgetc(fp);
            buffer[j] = c;
        }
        buffer[j] = '\0';
        if(!strcmp(buffer, rtext)){
          printf("%s: ", location);
          while(1){
            c = fgetc(fp);
            if( c == '\n' || c == EOF){
                line_end = ftell(fp);
                break;
            }
          }
          fseek(fp, line_start, SEEK_SET);
          while(ftell(fp) < line_end)
            printf("%c", fgetc(fp));
          i = line_end;
        }
    }
    printf("\n");
}

int grep_finder_c(char* location, char* rtext)
{
    char c;
    int line_counter = 0;
    FILE *fp = NULL;
    fp = fopen(location, "rb+");
    if(fp == NULL)
        return line_counter;
    fseek(fp, 0L, SEEK_END);
    long int len = strlen(rtext);
    long int end = ftell(fp);
    char* buffer = (char*)malloc(len);
    fseek(fp, 0L, SEEK_SET);
    long int line_end = 0;

    for(long int i = 0; i < end; i++){
        int j = 0;
        fseek(fp, i, SEEK_SET);
        for(j = 0; j < len; j++){
            c = fgetc(fp);
            buffer[j] = c;
        }
        buffer[j] = '\0';
        if(!strcmp(buffer, rtext)){
          while(1){
            c = fgetc(fp);
            if( c == '\n' || c == EOF){
                line_end = ftell(fp);
                break;
            }
          }
          line_counter++;
          i = line_end;
        }
    }
    fclose(fp);
    free(buffer);
    return line_counter;
}

void grep_finder_l(char* location, char* rtext)
{
    char c;
    FILE *fp = NULL;
    fp = fopen(location, "rb+");
    if(fp == NULL)
        return;
    fseek(fp, 0L, SEEK_END);
    long int len = strlen(rtext);
    long int end = ftell(fp);
    char* buffer = (char*)malloc(len);
    fseek(fp, 0L, SEEK_SET);

    for(long int i = 0; i < end; i++){
        int j = 0;
        fseek(fp, i, SEEK_SET);
        for(j = 0; j < len; j++){
            c = fgetc(fp);
            buffer[j] = c;
        }
        buffer[j] = '\0';
        if(!strcmp(buffer, rtext)){
          printf("%s ", location);
          fclose(fp);
          free(buffer);
          return;
        }
    }
}
