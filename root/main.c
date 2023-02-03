#include <conio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <windows.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

char* saver, *bush;
char* text_generator(char* atext);
void previous_saver(char* location, char* rtext);

//Creating a File
//createfile --file
void create()
{
    char c;
    char *s = (char*)malloc(200), *str = (char*)calloc(1000, sizeof(char)), *address = (char*)calloc(1000, sizeof(char));

    scanf("%s", s);

    if(strcmp(s, "--file")){
        gets(s);
        printf("Invalid Input\n");
        return;
    }
    free(s);
    long int i = 0;
    scanf("%c", &c);
    scanf("%c", &c);
    if(c != '"'){
        int f = 1;
        str[0] = c;
        scanf("%c", &c);
        while( (c != '\n') && (c != ' ') ){
            str[f] = c;
            f++;
            scanf("%c", &c);
        }
        str[f] = '\0';
    }
    else{
        while(1){
            scanf("%c", &str[i]);
            if((str[i] == '"') && (str[i-1] != '\\'))
                break;
            i++;
        }
        str[i] = '\0';
    }
    strcpy(address, str);

    //printf("\nYour chosen path: %s\n\n", str);

    char* str_ = (char*)calloc(200, sizeof(char));

    i = 0;

    while(1){
        if(address[i]=='\\'){
            mkdir(str_);
        }
        str_[i] = address[i];
        i++;
        if(address[i]=='\0'){
            str_[i] = '\0';
            break;
        }
    }

    FILE* fp = NULL;
    fp = fopen(address, "r");
    if(fp != NULL){
        printf("File already exist.\n");
        free(str); free(address); free(str_);
        return;
    }

    fp = fopen(address, "w+");
    if(fp==NULL){
        printf("Unable to create file.\n");
        free(str); free(address); free(str_);
        return;
    }

    fclose(fp);
    free(str); free(address); free(str_);
}

//Inserting a String
//insertstr --file --str --pos d:d
void insertstr()
{
    void previous_saver(char* location, char* rtext);
    char c;
    char *str, *s, *address;
    address = (char*)calloc(500, sizeof(char));
    str = (char*)calloc(500, sizeof(char));
    s = (char*)calloc(150, sizeof(char));
    char* text = (char*)calloc(500, sizeof(char));
    long int i = 0;
    scanf("%s", s);
    if(strcasecmp(s, "--file")){
        gets(s);
        printf("Invalid input.\n");
        return;
    }
    scanf("%c", &c);
    scanf("%c", &c);
    if(c != '"'){
        int f = 1;
        str[0] = c;
        scanf("%c", &c);
        while( (c != '\n') && (c != ' ') ){
            str[f] = c;
            f++;
            scanf("%c", &c);
        }
        str[f] = '\0';
    }
    else{
        while(1){
            scanf("%c", &str[i]);
            if((str[i] == '"') && (str[i-1] != '\\'))
                break;
            i++;
        }
        str[i] = '\0';
    }
    strcpy(address, str);
    i = 0;
    FILE* fp = NULL;
    fp = fopen(address, "rb+");
    if(fp==NULL){
        gets(str);
        printf("The directory you entered does not exist.\nTry creating it using <createfile> command.\n\n");
    }

    scanf("%s", str);
    if(strcasecmp(str, "--str")){
        gets(str);
        fclose(fp); free(text);
        printf("Invalid input.\n");
        return;
    }
    scanf("%c", &c);
    scanf("%c", &c);
    if(c != '"'){
        int f = 1;
        str[0] = c;
        scanf("%c", &c);
        while( (c != '\n') && (c != ' ') ){
            str[f] = c;
            f++;
            scanf("%c", &c);
        }
        str[f] = '\0';
    }
    else{
        while(1){
            scanf("%c", &str[i]);
            if((str[i] == '"') && (str[i-1] != '\\'))
                break;
            i++;
        }
        str[i] = '\0';
    }
    text = text_generator(str);
    fseek(fp, 0L, SEEK_END);
    long int end = ftell(fp), ct = 0;
    char* current = (char*)calloc(end, sizeof(char));
    fseek(fp, 0L, SEEK_SET);
    while(c != EOF){
        c = fgetc(fp);
        current[ct] = c;
        ct++;
    }
    current[ct-1] = '\0';
    previous_saver(address, current);
    fseek(fp, 0L, SEEK_SET);

    scanf("%s", str);
    if(strcasecmp(str, "--pos")){
        gets(str);
        printf("Invalid input.\n");
        fclose(fp); free(text); free(current);
        return;
    }
    //printf("Desired text: %s\n", text);

    char get;
    int line, ch, j = 0;
    i = 1;
    scanf(" %d:%d", &line, &ch);

    //printf("Line: %d | Character: %d\n", line, ch);

    while(i < line){
        //printf("Line: %d | Character: %d\n", line, ch);
        get = fgetc(fp);
        if(get==EOF){
            printf("Invalid position.\n");
            fclose(fp); free(text); free(current);
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
            fclose(fp); free(text); free(current);
            return;
        }
        //printf("%c | ", get);
        j++;
    }


    long int here = ftell(fp);
    long int buf_size = end - here;
    fseek(fp, here, SEEK_SET);
    char* buffer = (char*)calloc(buf_size, sizeof(char));
    fread(buffer, 1, buf_size, fp);
    //printf("buffer: %s\n", buffer);
    fseek(fp, here, SEEK_SET);
    i = 0;
    while(text[i] != '\0'){
        fputc(text[i], fp);
        i++;
    }
    i = 0;
    while(buffer[i] != '\0'){
        fputc(buffer[i], fp);
        i++;
    }
    //fputs(text, fp);
    //fputs(buffer, fp);

    fclose(fp); free(buffer); free(text); free(current);
}

//Showing a file
//cat --file
void cat()
{
    char* s = (char*)malloc(200), *str = (char*)calloc(1000, sizeof(char)), *address = (char*)calloc(1000, sizeof(char));
    char c;
    scanf("%s", s);
    if(strcasecmp(s, "--file")){
        gets(s);
        printf("Invalid input.\n");
        return;
    }
    //free(s);
    long int i = 0;
    scanf("%c", &c);
    scanf("%c", &c);
    if(c != '"'){
        int f = 1;
        str[0] = c;
        scanf("%c", &c);
        while( (c != '\n') && (c != ' ') ){
            str[f] = c;
            f++;
            scanf("%c", &c);
        }
        str[f] = '\0';
    }
    else{
        while(1){
            scanf("%c", &str[i]);
            if((str[i] == '"') && (str[i-1] != '\\'))
                break;
            i++;
        }
        str[i] = '\0';
    }
    strcpy(address, str);
    //printf("%s", s);

    FILE* fp = NULL;
    fp = fopen(address, "r");
    if(fp==NULL){
        printf("The directory you entered does not exist.\nTry creating it using <createfile> command.\n");
        free(s); free(address); free(str);
        return;
    }

    while(c != EOF){
        c = fgetc(fp);
        printf("%c", c);
    }
    printf("\n");
    free(s); free(address); free(str);
    fclose(fp);
}

//Removing a string
//remove --file --pos d:d -size d -b/f
void removestr()
{
    void previous_saver(char* location, char* rtext);
    char* buffer = (char*)malloc(4000), *str = (char*)malloc(500), *address= (char*)malloc(500);
    char s[300];
    char c;
    scanf("%s", s);
    if(strcmp(s, "--file")){
        gets(s);
        printf("Invalid input.\n");
        return;
    }
    long int i = 0;
    scanf("%c", &c);
    scanf("%c", &c);
    if(c != '"'){
        int f = 1;
        str[0] = c;
        scanf("%c", &c);
        while( (c != '\n') && (c != ' ') ){
            str[f] = c;
            f++;
            scanf("%c", &c);
        }
        str[f] = '\0';
    }
    else{
        while(1){
            scanf("%c", &str[i]);
            if((str[i] == '"') && (str[i-1] != '\\'))
                break;
            i++;
        }
        str[i] = '\0';
    }
    strcpy(address, str);
    i = 0;

    //printf("Address is: %s\n", address);
    FILE* fp = NULL;
    fp = fopen(address, "r");
    if(fp==NULL){
        printf("The directory you entered does not exist.\nTry creating it using <createfile> command.\n\n");
        return;
    }

    fseek(fp, 0L, SEEK_END);
    long int end_file = ftell(fp), ct = 0;
    char* current = (char*)calloc(end_file, sizeof(char));
    fseek(fp, 0L, SEEK_SET);
    while(c != EOF){
        c = fgetc(fp);
        current[ct] = c;
        ct++;
    }
    current[ct-1] = '\0';
    previous_saver(address, current);
    fseek(fp, 0L, SEEK_SET);

    scanf("%s", s);
    if(strcmp(s, "--pos")){
        gets(s);
        printf("Invalid input.\n");
        return;
    }
    int line, ch;
    long int len;
    scanf(" %d:%d ", &line, &ch);
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
    int j = 0;
    i = 1;
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
//copystr --file --pos d:d -size d -b/f
void copystr()
{
    free(saver);
    saver = (char*)malloc(15000);
    char s[300];
    char c;
    char *address = (char*)malloc(500);
    char *str= (char*)malloc(300);
    scanf("%c", &c);
    scanf("%s", s);
    if(strcmp(s, "--file")){
        gets(s);
        printf("Invalid input.\n");
        return;
    }
    long int i = 0;
    scanf("%c", &c);
    scanf("%c", &c);
    if(c != '"'){
        int f = 1;
        str[0] = c;
        scanf("%c", &c);
        while( (c != '\n') && (c != ' ') ){
            str[f] = c;
            f++;
            scanf("%c", &c);
        }
        str[f] = '\0';
    }
    else{
        while(1){
            scanf("%c", &str[i]);
            if((str[i] == '"') && (str[i-1] != '\\'))
                break;
            i++;
        }
        str[i] = '\0';
    }
    strcpy(address, str);
    i = 0;

    //printf("Address is: %s\n", address);
    FILE* fp = NULL;
    fp = fopen(address, "r");
    if(fp==NULL){
        printf("The directory you entered does not exist.\nTry creating it using <createfile> command.\n\n");
        return;
    }

    scanf("%s", s);
    if(strcmp(s, "--pos")){
        gets(s);
        printf("Invalid input.\n");
        return;
    }
    int line, ch;
    long int len;
    scanf(" %d:%d ", &line, &ch);
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
    i = 1;
    int j = 0;
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
//cutstr --file --pos d:d -size d -b/f
void cutstr()
{
    void previous_saver(char* location, char* rtext);
    free(saver);
    saver = (char*)malloc(15000);
    char* buffer = (char*)malloc(4000);
    char* address = (char*)malloc(500);
    char *str= (char*)malloc(300);
    char s[300];
    char c;
    scanf("%s", s);
    if(strcmp(s, "--file")){
        gets(s);
        printf("Invalid input.\n");
        return;
    }
    long int i = 0;
    scanf("%c", &c);
    scanf("%c", &c);
    if(c != '"'){
        int f = 1;
        str[0] = c;
        scanf("%c", &c);
        while( (c != '\n') && (c != ' ') ){
            str[f] = c;
            f++;
            scanf("%c", &c);
        }
        str[f] = '\0';
    }
    else{
        while(1){
            scanf("%c", &str[i]);
            if((str[i] == '"') && (str[i-1] != '\\'))
                break;
            i++;
        }
        str[i] = '\0';
    }
    strcpy(address, str);
    i = 0;
    //printf("Address is: %s\n", address);
    FILE* fp = NULL;
    fp = fopen(address, "r");
    if(fp==NULL){
        printf("The directory you entered does not exist.\nTry creating it using <createfile> command.\n\n");
        return;
    }

    fseek(fp, 0L, SEEK_END);
    long int end_file = ftell(fp), ct = 0;
    char* current = (char*)calloc(end_file, sizeof(char));
    fseek(fp, 0L, SEEK_SET);
    while(c != EOF){
        c = fgetc(fp);
        current[ct] = c;
        ct++;
    }
    current[ct-1] = '\0';
    previous_saver(address, current);
    fseek(fp, 0L, SEEK_SET);

    strcpy(s, str);
    scanf("%s", s);
    if(strcmp(s, "--pos")){
        gets(s);
        printf("Invalid input.\n");
        return;
    }
    int line, ch;
    long int len;
    scanf(" %d:%d ", &line, &ch);
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
    int j = 0;
    i = 1;
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
//pastestr --file --pos d:d -size d -b/f
void pastestr()
{
    void previous_saver(char* location, char* rtext);
    char *str, *s, *address, c;
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
    long int i = 0;
    scanf("%c", &c);
    scanf("%c", &c);
    if(c != '"'){
        int f = 1;
        str[0] = c;
        scanf("%c", &c);
        while( (c != '\n') && (c != ' ') ){
            str[f] = c;
            f++;
            scanf("%c", &c);
        }
        str[f] = '\0';
    }
    else{
        while(1){
            scanf("%c", &str[i]);
            if((str[i] == '"') && (str[i-1] != '\\'))
                break;
            i++;
        }
        str[i] = '\0';
    }
    strcpy(address, str);
    i = 0;

    FILE* fp = NULL;
    fp = fopen(address, "r+");
    if(fp==NULL){
        gets(str);
        printf("The directory you entered does not exist.\nTry creating it using <createfile> command.\n\n");
    }

    fseek(fp, 0L, SEEK_END);
    long int end_file = ftell(fp), ct = 0;
    char* current = (char*)calloc(end_file, sizeof(char));
    fseek(fp, 0L, SEEK_SET);
    while(c != EOF){
        c = fgetc(fp);
        current[ct] = c;
        ct++;
    }
    current[ct-1] = '\0';
    previous_saver(address, current);
    fseek(fp, 0L, SEEK_SET);

    scanf("%s", str);
    if(strcasecmp(str, "--pos")){
        printf("%s\n", str);
        gets(str);
        printf("Invalid input.\n");
        return;
    }

    char get;
    int line, ch,j = 0;
    i = 1;
    scanf(" %d:%d", &line, &ch);

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

int star = -1;
void find()
{
    star = -1;
    long int* find_all(FILE *fp, char* text, int starpos, int word);
    long int find_at(FILE *fp, char* dtext, int place, int starpos, int word);
    int find_count(FILE *fp, char* dtext, int starpos);
    char c;
    char *str, *s, *address, *text = (char*)calloc(200, sizeof(char));
    address = (char*)calloc(500, sizeof(char));
    str = (char*)calloc(150, sizeof(char));
    s = (char*)calloc(150, sizeof(char));
    int all = 0, at = 0, byword = 0, count = 0, at_num = 0, counter = 0;
    long int *results = (long int*)calloc(500, sizeof(long int)), places = -1;

    while(counter <= 2){
        scanf("%c", &c);
        scanf("%s", s);
        if(!strcmp(s, "-count"))
            count = 1;
        else if(!strcmp(s, "-at")){
            scanf("%d", &at_num);
            at = 1;}
        else if(!strcmp(s, "-byword"))
            byword = 1;
        else if(!strcmp(s, "-all"))
            all = 1;
        else if(!strcmp(s, "--file")){
            counter = 4;
            break;
        }
        else{
            printf("Invalid input.\n");
            gets(str);
            return;
        }
        counter++;
    }

    if(counter <= 3){
        scanf("%c", &c);
        scanf("%s", s);
        if(strcasecmp(s, "--file")){
            gets(s);
            printf("Invalid input.\n");
            return;
        }
    }
    counter = 0;
    long int i = 0;
    scanf("%c", &c);
    scanf("%c", &c);
    if(c != '"'){
        int f = 1;
        str[0] = c;
        scanf("%c", &c);
        while( (c != '\n') && (c != ' ') ){
            str[f] = c;
            f++;
            scanf("%c", &c);
        }
        str[f] = '\0';
    }
    else{
        while(1){
            scanf("%c", &str[i]);
            if((str[i] == '"') && (str[i-1] != '\\'))
                break;
            i++;
        }
        str[i] = '\0';
    }
    strcpy(address, str);
    i = 0;

    scanf("%s", s);
    if(strcasecmp(s, "--str")){
        gets(s);
        printf("Invalid input.\n");
        return;
    }
    scanf("%c", &c);
    scanf("%c", &c);
    if(c != '"'){
        int f = 1;
        str[0] = c;
        scanf("%c", &c);
        while(c != '\n'){
            str[f] = c;
            f++;
            scanf("%c", &c);
        }
        str[f] = '\0';
    }
    else{
        while(1){
            scanf("%c", &str[i]);
            if((str[i] == '"') && (str[i-1] != '\\'))
                break;
            i++;
        }
        str[i] = '\0';
    }
    text = text_generator(str);
    //printf("%s\n", text);
    //printf("STAR: %d\n", star);
    i = 0;

    FILE* fp = NULL;
    fp = fopen(address, "r");
    if(fp==NULL){
        gets(str);
        printf("The directory you entered does not exist.\nTry creating it using <createfile> command.\n\n");
    }

    if( (count == 1) && (at==0) && (byword==0) && (all==0)){
        counter = find_count(fp, text, star);
        printf("Number of occurrence: %d\n", counter);
        star = -1;
        return;
    }
    else if( (count == 0) && (at==0) && (all==1)){
        results = find_all(fp, text, star, byword);
        int cunt = 0;
        while(*(results+cunt) != -1){
            printf(" %ld", *(results+cunt));
            cunt++;
        }
        printf("\n");
    }
    else if( (count == 0) && (at==1) && (all==0)){
        places = find_at(fp, text, at_num, star, byword);
        printf("%ld\n", places);
    }
    else if( (count == 0) && (at==0) && (all==0)){
        places = find_at(fp, text, 1, star, byword);
        printf("%ld\n", places);
    }
    else{
        printf("Invalid combination of attributes.\n");
    }
    star = -1;
}

void replace()
{
    star = -1;
    void replace_all(char* address, char* text, long int* starts, long int* ends);
    long int* find_all2(FILE *fp, char* dtext, int starpos, int word);
    long int find_at2(FILE *fp, char* dtext, int place, int starpos, int word);
    void replace_at(char* file_address, char* changetext, long int location1, long int location2);
    long int* find_all(FILE *fp, char* text, int starpos, int word);
    long int find_at(FILE *fp, char* dtext, int place, int starpos, int word);
    void previous_saver(char* location, char* rtext);
    char c;
    char *str, *s, *address;
    address = (char*)calloc(500, sizeof(char));
    str = (char*)calloc(150, sizeof(char));
    s = (char*)calloc(150, sizeof(char));
    char* text1 = (char*)calloc(1000, sizeof(char));
    char* text2 = (char*)malloc(1000);
    int all = 0, at = 0, at_num = -1;
    long int at_start = -1, at_end = -1, *results_end = (long int*)calloc(500, sizeof(long int));
    long int *results_start = (long int*)calloc(500, sizeof(long int));
    scanf("%s", s);
    if(!strcmp(s, "-all")){
        all = 1;
        scanf("%c", &c);
        scanf("%s", s);
        if(strcasecmp(s, "--file")){
            printf("FILE\n");
            gets(s);
            printf("Invalid input.\n");
            return;
        }
    }
    else if(!strcmp(s, "-at")){
        at = 1;
        scanf("%d", &at_num);
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

    long int i = 0;
    scanf("%c", &c);
    scanf("%c", &c);
    if(c != '"'){
        int f = 1;
        str[0] = c;
        scanf("%c", &c);
        while( (c != '\n') && (c != ' ') ){
            str[f] = c;
            f++;
            scanf("%c", &c);
        }
        str[f] = '\0';
    }
    else{
        while(1){
            scanf("%c", &str[i]);
            if((str[i] == '"') && (str[i-1] != '\\'))
                break;
            i++;
        }
        str[i] = '\0';
        scanf("%c", &c);
    }
    strcpy(address, str);
    i = 0;

    scanf("%s", s);
    if(strcasecmp(s, "--str1")){
        gets(s);
        printf("Invalid input.\n");
        return;
    }
    scanf("%c", &c);
    scanf("%c", &c);
    if(c != '"'){
        int f = 1;
        str[0] = c;
        scanf("%c", &c);
        while( (c != '\n') && (c != ' ') ){
            str[f] = c;
            f++;
            scanf("%c", &c);
        }
        str[f] = '\0';
    }
    else{
        while(1){
            scanf("%c", &str[i]);
            if((str[i] == '"') && (str[i-1] != '\\'))
                break;
            i++;
        }
        str[i] = '\0';
        scanf("%c", &c);
    }
    text1 = text_generator(str);
    //printf("%s\n", text);
    //printf("STAR: %d\n", star);
    i = 0;

    scanf("%s", s);
    if(strcasecmp(s, "--str2")){
        gets(s);
        printf("Invalid input.\n");
        return;
    }
    scanf("%c", &c);
    scanf("%c", &c);
    if(c != '"'){
        int f = 1;
        str[0] = c;
        scanf("%c", &c);
        while( (c != '\n') && (c != ' ') ){
            str[f] = c;
            f++;
            scanf("%c", &c);
        }
        str[f] = '\0';
    }
    else{
        while(1){
            scanf("%c", &str[i]);
            if((str[i] == '"') && (str[i-1] != '\\'))
                break;
            i++;
        }
        str[i] = '\0';
        scanf("%c", &c);
    }
    text2 = text_generator(str);

    FILE* fp = NULL;
    fp = fopen(address, "rb");
    if(fp==NULL){
        gets(str);
        printf("The directory you entered does not exist.\nTry creating it using <createfile> command.\n\n");
    }

    fseek(fp, 0L, SEEK_END);
    long int end = ftell(fp), ct = 0;
    char* current = (char*)calloc(end, sizeof(char));
    fseek(fp, 0L, SEEK_SET);
    while(c != EOF){
        c = fgetc(fp);
        current[ct] = c;
        ct++;
    }
    current[ct-1] = '\0';
    previous_saver(address, current);
    fseek(fp, 0L, SEEK_SET);
    //printf("G\n");

    if(at==1){
        at_start = find_at(fp, text1, at_num, star, 0);
        at_end = find_at2(fp, text1, at_num, star, 0);
        //printf("ATPLACE: %ld | ATEND: %ld\n\n\n", at_start, at_end);
        fclose(fp);
        replace_at(address, text2, at_start, at_end);
    }
    else if(all==1){
        results_start = find_all(fp, text1, star, 0);
        results_end = find_all2(fp, text1, star, 0);
        fclose(fp);
        replace_all(address, text2, results_start, results_end);
    }
    else if(all==0 && at==0){
        at_start = find_at(fp, text1, 1, star, 0);
        at_end = find_at2(fp, text1, 1, star, 0);
        //fclose(fp);
        replace_at(address, text2, at_start, at_end);
    }
    free(text1);
    free(text2);
    free(address);
    star = -1;
}

//Searching for a text inside multiple files
//grep --str --file
void grep()
{
    void line_reader(char* address, long int location);
    long int* grep_finder(char* location, char* rtext);
    int grep_finder_c(char* location, char* rtext);
    int grep_finder_l(char* location, char* rtext);
    char c;
    char *str, *s, *address, *text;
    address = (char*)calloc(500, sizeof(char));
    str = (char*)calloc(150, sizeof(char));
    s = (char*)calloc(150, sizeof(char));
    text = (char*)calloc(200, sizeof(char));
    char** list = (char**)calloc(100, sizeof(char*));
    long int* line_starts = (long int*)calloc(100, sizeof(int)),*lines = (long int*)calloc(100, sizeof(int)) ;
    for(int i = 0; i < 100; i++) *(list+i) = (char*)calloc(100, sizeof(char));

    int option = 0, count = 0, listct = 0;
    long int i = 0;
    scanf("%s", s);
    if(!strcmp(s, "-c")){
        option = 1;
        scanf("%s", s);
        if(strcasecmp(s, "--str")){
            gets(s);
            printf("Invalid input.\n");
            return;
        }
    }
    else if(!strcmp(s, "-l")){
        option = 2;
        scanf("%c", &c);
        scanf("%s", s);
        if(strcasecmp(s, "--str")){
            gets(s);
            printf("Invalid input.\n");
            return;
        }
    }
    else if(strcasecmp(s, "--str")){
        gets(s);
        printf("Invalid input.\n");
        return;
    }
    scanf("%c", &c);
    scanf("%c", &c);
    if(c != '"'){
        int f = 1;
        str[0] = c;
        scanf("%c", &c);
        while( (c != '\n') && (c != ' ') ){
            str[f] = c;
            f++;
            scanf("%c", &c);
        }
        str[f] = '\0';
    }
    else{
        while(1){
            scanf("%c", &str[i]);
            if((str[i] == '"') && (str[i-1] != '\\'))
                break;
            i++;
        }
        str[i] = '\0';
    }
    text = text_generator(str);
    i = 0;
    scanf("%s", s);
    if(strcasecmp(s, "--file")){
        gets(s);
        printf("Invalid input.\n");
        return;
    }
    scanf("%c", &c);
    while(c != '\n'){
        //scanf("%c", &c);
        //if(c=='\n')
            //break;
        scanf("%c", &c);
        if(c=='\n')
            break;
        if(c != '"'){
            int f = 1;
            str[0] = c;
            scanf("%c", &c);
            while( (c != '\n') && (c != ' ') ){
                str[f] = c;
                f++;
                scanf("%c", &c);
            }
            str[f] = '\0';
        }
        else{
            while(1){
                scanf("%c", &str[i]);
                if((str[i] == '"') && (str[i-1] != '\\'))
                    break;
                i++;
            }
            str[i] = '\0';
            scanf("%c", &c);
        }
        strcpy(address, str);
        //printf("%s\n", address);
        i = 0;
        if(option == 0){
            lines = grep_finder(address, text);
            if(lines==NULL){
                free(str);
                str = (char*)calloc(200, sizeof(char));
                continue;
            }
            int j = 0;
            while(*(lines+j)!=-1){
                strcpy(*(list+listct), address);
                *(line_starts+listct) = *(lines+j);
                listct++;
                j++;
            }
        }
        else if(option == 1)
            count += grep_finder_c(address, text);
        else if(option == 2){
            if(grep_finder_l(address, text)){
                strcpy(*(list+listct), address);
                listct++;
            }
        }
        free(str);
        str = (char*)calloc(200, sizeof(char));
    }
    //printf("%s | %s | %s\n", *(list), *(list+1), *(list+2));
    //printf("%ld | %ld | %ld\n", *(line_starts), *(line_starts+1), *(line_starts+2));
    if(option==0){
        for(int i = 0; i < listct; i++){
            printf("%s: ", *(list+i));
            line_reader(*(list+i), *(line_starts+i));
            printf("\n");
        }
    }
    else if(option==1){
        printf("%d\n", count);
    }
    else if(option==2){
        for(int i = 0; i < listct; i++)printf(" %s ", *(list+i));
        printf("\n");
    }
}

//Undoing changes
void undo()
{
    void previous_saver(char* location, char* rtext);
    char* address = (char*)malloc(200);
    char c;
    scanf("%s", address);
    if(strcasecmp(address, "--file")){
        gets(address);
        printf("Invalid input.\n");
        return;
    }
    scanf("%c", &c);
    free(address);
    address = (char*)malloc(200);
    gets(address);
    char def[700] = "C:\\Users\\shayan\\Documents\\GitHub\\project-shayandesu\\Copy\\";
    strcat(def, address);
    FILE *fp = fopen(def, "r");
    fseek(fp, 0L, SEEK_END);
    long int end = ftell(fp), i = 0, ct = 0;
    char* pre = (char*)malloc(end);
    fseek(fp, 0L, SEEK_SET);
    c = fgetc(fp);
    while(c != EOF){
        pre[i] = c;
        i++;
        c = fgetc(fp);
    }
    pre[i] = '\0';
    //fread(pre, 1, end, fp);
    //printf("%s\n", pre);
    fclose(fp);
    fp = fopen(address, "rb+");
    fseek(fp, 0L, SEEK_END);
    end = ftell(fp);
    char* current = (char*)calloc(end, sizeof(char));
    fseek(fp, 0L, SEEK_SET);
    c = fgetc(fp);
    while(c != EOF){
        current[ct] = c;
        //printf("|%c|", c);
        c = fgetc(fp);
        ct++;
    }
    current[ct-1] = '\0';
    ct = 0;
    //printf("Current:\n%s\n\n", current);
    //previous_saver(address, current);
    fclose(fp);
    fp = fopen(def, "w+");
    while(current[ct] != '\0'){
        fputc(current[ct], fp);
        ct++;
    }
    ct = 0;
    fclose(fp);
    fp = fopen(address, "w+");
    //printf("Pre:\n%s\n\n", pre);
    long int newest = 0;
    while(pre[newest] != '\0'){
        fputc(pre[newest], fp);
        newest++;
    }
    fclose(fp);
    //free(pre);
    //free(current);
}

void indent()
{
    char* space(char* text, long int location);
    char* nospace(char* text, long int location);
    char* newline1(char* text, long int location);
    char* emptybrace(char* text, long int left, long int right);
    char* indentation(char*text, long int location, int indent);
    char c, *address = (char*)calloc(300, sizeof(char));
    scanf("%c", &c);
    gets(address);
    FILE *fp = fopen(address, "r+");
    fseek(fp, 0L, SEEK_END);
    long int end = ftell(fp), ct = 0, i = 0;
    char* buffer = (char*)calloc(end, sizeof(char));

    /*fseek(fp, 0L, SEEK_END);
    long int end_ = ftell(fp), ct_ = 0;
    char* current = (char*)calloc(end_, sizeof(char));
    fseek(fp, 0L, SEEK_SET);
    while(c != EOF){
        c = fgetc(fp);
        current[ct_] = c;
        ct_++;
    }
    current[ct_-1] = '\0';
    previous_saver(address, current);
    fseek(fp, 0L, SEEK_SET);*/


    fseek(fp, 0L, SEEK_SET);
    while(c != EOF){
        c = fgetc(fp);
        buffer[ct] = c;
        ct++;
    }
    buffer[ct-1] = '\0';
    previous_saver(address, buffer);
    //printf("%s\n\n", buffer);
    int rbracect = 0, rbracedone = 0;
    while(1){
        //printf("%ld - %c\n", i, buffer[i]);
        if(buffer[i] == '{'){
            rbracect++;
            if(rbracect > rbracedone){
                buffer = space(buffer, i);
                i = 0;
                rbracect = 0;
                rbracedone++;
                continue;
            }
        }
        if(buffer[i] == '\0')
            break;
        i++;
    }
    i = 0;
    rbracect = 0, rbracedone = 0;

    int lbracect = 0, lbracedone = 0;
    while(1){
        //printf("%ld - %c\n", i, buffer[i]);
        if(buffer[i] == '}'){
            lbracect++;
            if(lbracect > lbracedone){
                buffer = nospace(buffer, i);
                i = 0;
                lbracect = 0;
                lbracedone++;
                continue;
            }
        }
        if(buffer[i] == '\0')
            break;
        i++;
    }
    i = 0;

    while(1){
        //printf("%ld - %c\n", i, buffer[i]);
        if( (buffer[i] == '{') || (buffer[i] == '}'))
            buffer = newline1(buffer, i+1);
        if(buffer[i] == '\0')
            break;
        i++;
    }
    i = 0;

    while(1){
        if(buffer[i]=='{'){
            if((buffer[i+2]=='}'))
                buffer = emptybrace(buffer, i, i+2);
        }
        if(buffer[i]=='\0')
            break;
        i++;
    }
    int indent = 0;
    i = 0;
    while(1){
        if(buffer[i]=='{')
            indent += 4;
        if(buffer[i]=='}')
            indent -= 4;
        if(buffer[i]=='\n'){
            if(buffer[i+1]=='}'){
                buffer = indentation(buffer, i , indent-4);
                i++;
                continue;
            }
            buffer = indentation(buffer, i, indent);
        }
        if(buffer[i]=='\0')
            break;
        i++;
    }
    i = 0;

    fclose(fp);
    fopen(address, "w+");
    //printf("gee\n");
    while(buffer[i] != '\0'){
        fputc(buffer[i], fp);
        i++;
    }
    fclose(fp);
}

void compare()
{
    long int* comparing(char* address1, char* address2);
    long int* results = (long int*)calloc(200, sizeof(long int));
    char *str = (char*)calloc(150, sizeof(char)), c;
    char *address1 = (char*)calloc(150, sizeof(char)), *address2 = (char*)calloc(150, sizeof(char));
    long int i = 0;
    scanf("%c", &c);
    scanf("%c", &c);
    if(c != '"'){
        int f = 1;
        str[0] = c;
        scanf("%c", &c);
        while( (c != '\n') && (c != ' ') ){
            str[f] = c;
            f++;
            scanf("%c", &c);
        }
        str[f] = '\0';
    }
    else{
        while(1){
            scanf("%c", &str[i]);
            if((str[i] == '"') && (str[i-1] != '\\'))
                break;
            i++;
        }
        str[i] = '\0';
        scanf("%c", &c);
    }
    strcpy(address1, str);
    //printf("ADDRESS1: |%s|\n", address1);
    i = 0;
    scanf("%c", &c);
    if(c != '"'){
        int f = 1;
        str[0] = c;
        scanf("%c", &c);
        while( (c != '\n') && (c != ' ') ){
            str[f] = c;
            f++;
            scanf("%c", &c);
        }
        str[f] = '\0';
    }
    else{
        while(1){
            scanf("%c", &str[i]);
            if((str[i] == '"') && (str[i-1] != '\\'))
                break;
            i++;
        }
        str[i] = '\0';
        scanf("%c", &c);
    }
    address2 = text_generator(str);
    //printf("ADDRESS2: |%s|\n", address2);
    i = 0;
    results = comparing(address1, address2);
    FILE *fp1 = fopen(address1, "r");
    FILE *fp2 = fopen(address2, "r");
    while(*(results+i) != -1){
        fseek(fp1, 0, SEEK_SET);
        fseek(fp2, 0, SEEK_SET);
        int linect = 1, id = 0;
        char* line1 = (char*)calloc(400, sizeof(char)), *line2 = (char*)calloc(400, sizeof(char));
        while(1){
            c= fgetc(fp1);
            if(c=='\n')
                linect++;
            if(linect==*(results+i)){
                long int j = 0;
                while(1){
                    c = fgetc(fp1);
                    if(c=='\n' || c==EOF){
                        id = 1;
                        break;
                    }
                    line1[j] = c;
                    j++;
                }
                line1[j] = '\0';
                break;
            }
            if(id==1)
                break;
        }
        linect = 1;
        while(1){
            c= fgetc(fp2);
            if(c=='\n')
                linect++;
            if(linect==*(results+i)){
                long int j = 0;
                while(1){
                    c = fgetc(fp2);
                    if(c=='\n' || c==EOF)
                        break;
                    line2[j] = c;
                    j++;
                }
                line2[j] = '\0';
                break;
            }
        }

        printf("========== Line: %ld ==========\n", *(results+i));
        printf("File 1: %s\n", line1);
        printf("File 2: %s\n", line2);
        free(line1);
        free(line2);
        i++;
    }
    i++;
    FILE *fp = NULL;
    if(*(results+i)==1)
        fp = fopen(address1, "r");
    else if(*(results+i)==2)
        fp = fopen(address2, "r");
    else
        return;
    int line_end = 1;
    while(1){
        c = fgetc(fp);
        if(c=='\n')
            line_end++;
        if(c==EOF)
            break;
    }
    fseek(fp, 0, SEEK_SET);
    char* buffer = (char*)calloc(300, sizeof(char));
    int linect = 1;
    while(1){
        c = fgetc(fp);
        if(c=='\n')
            linect++;
        if(linect==*(results+i+1)){
            long int j = 0;
            while(1){
                c = fgetc(fp);
                if(c==EOF)
                    break;
                buffer[j] = c;
                j++;
            }
            buffer[j] = '\0';
            break;
        }
        if(c==EOF)
            return;
    }
    printf(">>>>>>>>>> File: %ld | Start: %ld | End: %d >>>>>>>>>>\n", *(results+i), *(results+i+1), line_end);
    printf("File %ld: %s\n", *(results+i), buffer);
}

int reccur = 0;
void tree()
{
    scanf("%d", &reccur);
    void filelist(char* directory, int indentnum, int counter);
    filelist(".", 4, 1);
    reccur = 0;
}

int main()
{
    char* str = (char*)calloc(150, sizeof(char));
    void arman();
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
            find();
        else if(!strcmp(str, "replace"))
            replace();
        else if(!strcmp(str, "grep"))
            grep();
        else if(!strcmp(str, "undo"))
            undo();
        else if(!strcmp(str, "auto-indent"))
            indent();
        else if(!strcmp(str, "compare"))
            compare();
        else if(!strcmp(str, "tree"))
            tree();
        else if(!strcmp(str,"=D"))
            arman();
        else if(!strcmp(str, "clear"))
            system("cls");
        else if(!strcmp(str, "exit"))
            return 0;
        else{
            gets(str);
            printf("Invalid input\n");
        }
    }
}

void arman_insert(char* text)
{
    char *str = (char*)calloc(1000, sizeof(char)), c;
    char *address = (char*)calloc(1000, sizeof(char));
    scanf("%c", &c);
    scanf("%s", str);
    if(strcmp(str, "--file")){
        gets(str);
        printf("Invalid input");
    }
    long int i = 0;
    scanf("%c", &c);
    scanf("%c", &c);
    if(c != '"'){
        int f = 1;
        str[0] = c;
        scanf("%c", &c);
        while( (c != '\n') && (c != ' ') ){
            str[f] = c;
            f++;
            scanf("%c", &c);
        }
        str[f] = '\0';
    }
    else{
        while(1){
            scanf("%c", &str[i]);
            if((str[i] == '"') && (str[i-1] != '\\'))
                break;
            i++;
        }
        str[i] = '\0';
        scanf("%c", &c);
    }
    strcpy(address, str);
    i = 0;
    FILE* fp = NULL;
    fp = fopen(address, "rb+");
    if(fp==NULL){
        gets(str);
        printf("The directory you entered does not exist.\nTry creating it using <createfile> command.\n\n");
        return;
    }
    fseek(fp, 0L, SEEK_END);
    long int end = ftell(fp), ct = 0;
    char* current = (char*)calloc(end, sizeof(char));
    fseek(fp, 0L, SEEK_SET);
    while(c != EOF){
        c = fgetc(fp);
        current[ct] = c;
        ct++;
    }
    current[ct-1] = '\0';
    previous_saver(address, current);
    fseek(fp, 0L, SEEK_SET);

    scanf("%s", str);
    if(strcasecmp(str, "--pos")){
        gets(str);
        printf("Invalid input.\n");
        return;
    }
    //printf("Desired text: %s\n", text);

    char get;
    int line, ch, j = 1;
    i = 1;
    scanf(" %d:%d", &line, &ch);

    //printf("Line: %d | Character: %d\n", line, ch);

    while(i < line){
        //printf("Line: %d | Character: %d\n", line, ch);
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

void arman_replace(char* sub)
{
    star = -1;
    void replace_all(char* address, char* text, long int* starts, long int* ends);
    long int* find_all2(FILE *fp, char* dtext, int starpos, int word);
    long int find_at2(FILE *fp, char* dtext, int place, int starpos, int word);
    void replace_at(char* file_address, char* changetext, long int location1, long int location2);
    long int* find_all(FILE *fp, char* text, int starpos, int word);
    long int find_at(FILE *fp, char* dtext, int place, int starpos, int word);
    void previous_saver(char* location, char* rtext);
    char c;
    char *str, *s, *address;
    address = (char*)calloc(500, sizeof(char));
    str = (char*)calloc(150, sizeof(char));
    s = (char*)calloc(150, sizeof(char));
    char* text1 = (char*)calloc(1000, sizeof(char));
    char* text2 = (char*)malloc(1000);
    int all = 0, at = 0, at_num = -1;
    long int at_start = -1, at_end = -1, *results_end = (long int*)calloc(500, sizeof(long int));
    long int *results_start = (long int*)calloc(500, sizeof(long int));
    scanf("%s", s);
    if(!strcmp(s, "-all")){
        all = 1;
        scanf("%c", &c);
        scanf("%s", s);
        if(strcasecmp(s, "--file")){
            printf("FILE\n");
            gets(s);
            printf("Invalid input.\n");
            return;
        }
    }
    else if(!strcmp(s, "-at")){
        at = 1;
        scanf("%d", &at_num);
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

    long int i = 0;
    scanf("%c", &c);
    scanf("%c", &c);
    if(c != '"'){
        int f = 1;
        str[0] = c;
        scanf("%c", &c);
        while( (c != '\n') && (c != ' ') ){
            str[f] = c;
            f++;
            scanf("%c", &c);
        }
        str[f] = '\0';
    }
    else{
        while(1){
            scanf("%c", &str[i]);
            if((str[i] == '"') && (str[i-1] != '\\'))
                break;
            i++;
        }
        str[i] = '\0';
        scanf("%c", &c);
    }
    strcpy(address, str);
    i = 0;

    scanf("%s", s);
    int which = 0;
    if(!strcasecmp(s, "--str1"))
        which = 1;
    else if(!strcasecmp(s, "--str2"))
        which = 2;
    else{
        gets(s);
        printf("Invalid input.\n");
        return;
    }
    scanf("%c", &c);
    scanf("%c", &c);
    if(c != '"'){
        int f = 1;
        str[0] = c;
        scanf("%c", &c);
        while( (c != '\n') && (c != ' ') ){
            str[f] = c;
            f++;
            scanf("%c", &c);
        }
        str[f] = '\0';
    }
    else{
        while(1){
            scanf("%c", &str[i]);
            if((str[i] == '"') && (str[i-1] != '\\'))
                break;
            i++;
        }
        str[i] = '\0';
        scanf("%c", &c);
    }
    if(which==1){
        text1 = text_generator(str);
        strcpy(text2, sub);
    }
    else if(which==2){
        text2 = text_generator(str);
        strcpy(text1, sub);
    }
    //printf("text1: %s\ntext2: %s", text1, text2);
    //printf("STAR: %d\n", star);
    i = 0;

    FILE* fp = NULL;
    fp = fopen(address, "rb");
    if(fp==NULL){
        gets(str);
        printf("The directory you entered does not exist.\nTry creating it using <createfile> command.\n\n");
        return;
    }

    fseek(fp, 0L, SEEK_END);
    long int end = ftell(fp), ct = 0;
    char* current = (char*)calloc(end, sizeof(char));
    fseek(fp, 0L, SEEK_SET);
    while(c != EOF){
        c = fgetc(fp);
        current[ct] = c;
        ct++;
    }
    current[ct-1] = '\0';
    previous_saver(address, current);
    fseek(fp, 0L, SEEK_SET);

    if(at==1){
        at_start = find_at(fp, text1, at_num, star, 0);
        at_end = find_at2(fp, text1, at_num, star, 0);
        //printf("ATPLACE: %ld | ATEND: %ld\n\n\n", at_start, at_end);
        fclose(fp);
        replace_at(address, text2, at_start, at_end);
    }
    else if(all==1){
        results_start = find_all(fp, text1, star, 0);
        results_end = find_all2(fp, text1, star, 0);
        fclose(fp);
        replace_all(address, text2, results_start, results_end);
    }
    else if(all==0 && at==0){
        at_start = find_at(fp, text1, 1, star, 0);
        at_end = find_at2(fp, text1, 1, star, 0);
        //fclose(fp);
        replace_at(address, text2, at_start, at_end);
    }
    free(text1);
    free(text2);
    free(address);
    star = -1;
}

void arman_find_input(char* sub)
{
    star = -1;
    long int* find_all(FILE *fp, char* text, int starpos, int word);
    long int find_at(FILE *fp, char* dtext, int place, int starpos, int word);
    int find_count(FILE *fp, char* dtext, int starpos);
    char c;
    char *str, *s, *address, *text = (char*)calloc(200, sizeof(char));
    address = (char*)calloc(500, sizeof(char));
    str = (char*)calloc(150, sizeof(char));
    s = (char*)calloc(150, sizeof(char));
    int all = 0, at = 0, byword = 0, count = 0, at_num = 0, counter = 0;
    long int *results = (long int*)calloc(500, sizeof(long int)), places = -1;

    while(counter <= 2){
        scanf("%c", &c);
        scanf("%s", s);
        if(!strcmp(s, "-count"))
            count = 1;
        else if(!strcmp(s, "-at")){
            scanf("%d", &at_num);
            at = 1;}
        else if(!strcmp(s, "-byword"))
            byword = 1;
        else if(!strcmp(s, "-all"))
            all = 1;
        else if(!strcmp(s, "--file")){
            counter = 4;
            break;
        }
        else{
            printf("Invalid input.\n");
            gets(str);
            return;
        }
        counter++;
    }

    if(counter <= 3){
        scanf("%c", &c);
        scanf("%s", s);
        if(strcasecmp(s, "--file")){
            gets(s);
            printf("Invalid input.\n");
            return;
        }
    }
    counter = 0;
    long int i = 0;
    scanf("%c", &c);
    scanf("%c", &c);
    if(c != '"'){
        int f = 1;
        str[0] = c;
        scanf("%c", &c);
        while( (c != '\n') && (c != ' ') ){
            str[f] = c;
            f++;
            scanf("%c", &c);
        }
        str[f] = '\0';
    }
    else{
        while(1){
            scanf("%c", &str[i]);
            if((str[i] == '"') && (str[i-1] != '\\'))
                break;
            i++;
        }
        str[i] = '\0';
    }
    strcpy(address, str);
    i = 0;

    strcpy(text, sub);

    FILE* fp = NULL;
    fp = fopen(address, "r");
    if(fp==NULL){
        gets(str);
        printf("The directory you entered does not exist.\nTry creating it using <createfile> command.\n\n");
        return;
    }

    if( (count == 1) && (at==0) && (byword==0) && (all==0)){
        counter = find_count(fp, text, star);
        printf("Number of occurrence: %d\n", counter);
        star = -1;
        return;
    }
    else if( (count == 0) && (at==0) && (all==1)){
        results = find_all(fp, text, star, byword);
        int cunt = 0;
        while(*(results+cunt) != -1){
            printf(" %ld", *(results+cunt));
            cunt++;
        }
        printf("\n");
    }
    else if( (count == 0) && (at==1) && (all==0)){
        places = find_at(fp, text, at_num, star, byword);
        printf("%ld\n", places);
    }
    else if( (count == 0) && (at==0) && (all==0)){
        places = find_at(fp, text, 1, star, byword);
        printf("%ld\n", places);
    }
    else{
        printf("Invalid combination of attributes.\n");
    }
    star = -1;
}

void arman_grep_input(char* sub)
{
    void line_reader(char* address, long int location);
    long int* grep_finder(char* location, char* rtext);
    int grep_finder_c(char* location, char* rtext);
    int grep_finder_l(char* location, char* rtext);
    char c;
    char *str, *s, *address, *text;
    address = (char*)calloc(500, sizeof(char));
    str = (char*)calloc(150, sizeof(char));
    s = (char*)calloc(150, sizeof(char));
    text = (char*)calloc(200, sizeof(char));
    char** list = (char**)calloc(100, sizeof(char*));
    long int* line_starts = (long int*)calloc(100, sizeof(int)),*lines = (long int*)calloc(100, sizeof(int)) ;
    for(int i = 0; i < 100; i++) *(list+i) = (char*)calloc(100, sizeof(char));
    strcpy(text, sub);
    int option = 0, count = 0, listct = 0;
    long int i = 0;
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
    while(c != '\n'){
        //scanf("%c", &c);
        //if(c=='\n')
            //break;
        scanf("%c", &c);
        if(c=='\n')
            break;
        if(c != '"'){
            int f = 1;
            str[0] = c;
            scanf("%c", &c);
            while( (c != '\n') && (c != ' ') ){
                str[f] = c;
                f++;
                scanf("%c", &c);
            }
            str[f] = '\0';
        }
        else{
            while(1){
                scanf("%c", &str[i]);
                if((str[i] == '"') && (str[i-1] != '\\'))
                    break;
                i++;
            }
            str[i] = '\0';
            scanf("%c", &c);
        }
        strcpy(address, str);
        //printf("%s\n", address);
        i = 0;
        if(option == 0){
            lines = grep_finder(address, text);
            int j = 0;
            while(*(lines+j)!=-1){
                strcpy(*(list+listct), address);
                *(line_starts+listct) = *(lines+j);
                listct++;
                j++;
            }
        }
        else if(option == 1)
            count += grep_finder_c(address, text);
        else if(option == 2){
            if(grep_finder_l(address, text)){
                strcpy(*(list+listct), address);
                listct++;
            }
        }
        free(str);
        str = (char*)calloc(200, sizeof(char));
    }
    //printf("%s | %s | %s\n", *(list), *(list+1), *(list+2));
    //printf("%ld | %ld | %ld\n", *(line_starts), *(line_starts+1), *(line_starts+2));
    if(option==0){
        for(int i = 0; i < listct; i++){
            printf("%s: ", *(list+i));
            line_reader(*(list+i), *(line_starts+i));
            printf("\n");
        }
    }
    else if(option==1){
        printf("%d\n", count);
    }
    else if(option==2){
        for(int i = 0; i < listct; i++)printf(" %s ", *(list+i));
        printf("\n");
    }
}

void arman_cat()
{
    char *str = (char*)calloc(1000, sizeof(char)), c;
    char *address = (char*)calloc(1000, sizeof(char)), *buffer = (char*)calloc(5000, sizeof(char));
    scanf("%c", &c);
    scanf("%s", str);
    if(strcmp(str, "--file")){
        gets(str);
        printf("Invalid input");
    }
    long int i = 0;
    scanf("%c", &c);
    scanf("%c", &c);
    if(c != '"'){
        int f = 1;
        str[0] = c;
        scanf("%c", &c);
        while( (c != '\n') && (c != ' ') ){
            str[f] = c;
            f++;
            scanf("%c", &c);
        }
        str[f] = '\0';
    }
    else{
        while(1){
            scanf("%c", &str[i]);
            if((str[i] == '"') && (str[i-1] != '\\'))
                break;
            i++;
        }
        str[i] = '\0';
        scanf("%c", &c);
    }
    address = text_generator(str);
    i = 0;
    FILE* fp = NULL;
    fp = fopen(address, "rb+");
    if(fp==NULL){
        gets(str);
        printf("The directory you entered does not exist.\nTry creating it using <createfile> command.\n\n");
        return;
    }
    c = fgetc(fp);
    while(c != EOF){
        buffer[i] = c;
        c = fgetc(fp);
        i++;
    }
    buffer[i] = '\0';
    scanf("%s", str);
    if(!strcmp(str, "insertstr"))
        arman_insert(buffer);
    else if(!strcmp(str, "replace"))
        arman_replace(buffer);
    else if(!strcmp(str, "find"))
        arman_find_input(buffer);
    else if(!strcmp(str, "grep"))
        arman_grep_input(buffer);
}

void arman_find_output()
{
    star = -1;
    long int* find_all(FILE *fp, char* text, int starpos, int word);
    long int find_at(FILE *fp, char* dtext, int place, int starpos, int word);
    int find_count(FILE *fp, char* dtext, int starpos);
    char c;
    char *str, *s, *address, *text = (char*)calloc(200, sizeof(char));
    address = (char*)calloc(500, sizeof(char));
    str = (char*)calloc(150, sizeof(char));
    s = (char*)calloc(150, sizeof(char));
    int all = 0, at = 0, byword = 0, count = 0, at_num = 0, counter = 0;
    long int *results = (long int*)calloc(500, sizeof(long int)), places = -1;

    while(counter <= 2){
        scanf("%c", &c);
        scanf("%s", s);
        if(!strcmp(s, "-count"))
            count = 1;
        else if(!strcmp(s, "-at")){
            scanf("%d", &at_num);
            at = 1;}
        else if(!strcmp(s, "-byword"))
            byword = 1;
        else if(!strcmp(s, "-all"))
            all = 1;
        else if(!strcmp(s, "--file")){
            counter = 4;
            break;
        }
        else{
            printf("Invalid input.\n");
            gets(str);
            return;
        }
        counter++;
    }

    if(counter <= 3){
        scanf("%c", &c);
        scanf("%s", s);
        if(strcasecmp(s, "--file")){
            gets(s);
            printf("Invalid input.\n");
            return;
        }
    }
    counter = 0;
    long int i = 0;
    scanf("%c", &c);
    scanf("%c", &c);
    if(c != '"'){
        int f = 1;
        str[0] = c;
        scanf("%c", &c);
        while( (c != '\n') && (c != ' ') ){
            str[f] = c;
            f++;
            scanf("%c", &c);
        }
        str[f] = '\0';
    }
    else{
        while(1){
            scanf("%c", &str[i]);
            if((str[i] == '"') && (str[i-1] != '\\'))
                break;
            i++;
        }
        str[i] = '\0';
    }
    strcpy(address, str);
    i = 0;

    scanf("%s", s);
    if(strcasecmp(s, "--str")){
        gets(s);
        printf("Invalid input.\n");
        return;
    }
    scanf("%c", &c);
    scanf("%c", &c);
    if(c != '"'){
        int f = 1;
        str[0] = c;
        scanf("%c", &c);
        while(c != '\n' && c!=' '){
            str[f] = c;
            f++;
            scanf("%c", &c);
        }
        str[f] = '\0';
    }
    else{
        while(1){
            scanf("%c", &str[i]);
            if((str[i] == '"') && (str[i-1] != '\\'))
                break;
            i++;
        }
        str[i] = '\0';
    }
    text = text_generator(str);
    //printf("%s\n", text);
    //printf("STAR: %d\n", star);
    i = 0;

    FILE* fp = NULL;
    fp = fopen(address, "r");
    if(fp==NULL){
        gets(str);
        printf("The directory you entered does not exist.\nTry creating it using <createfile> command.\n\n");
        return;
    }
    char *next = (char*)calloc(200, sizeof(char));
    char *strized = (char*)calloc(300, sizeof(char));
    if( (count == 1) && (at==0) && (byword==0) && (all==0)){
        counter = find_count(fp, text, star);
        sprintf(strized, "%d", counter);
        //printf("Number of occurrence: %d\n str: %s\n", counter, strized);
        star = -1;
    }
    else if( (count == 0) && (at==0) && (all==1)){
        results = find_all(fp, text, star, byword);
        int cunt = 0;
        while(*(results+cunt) != -1){
            char *tmp = (char*)calloc(200, sizeof(char));
            //printf(" %ld", *(results+cunt));
            //printf("%ld\n", *(results+cunt));
            sprintf(tmp, "%ld", *(results+cunt));
            //printf("=%s\n", tmp);
            strcat(strized, tmp);
            strcat(strized, " ");
            cunt++;
            free(tmp);
        }
        printf("\n");
    }
    else if( (count == 0) && (at==1) && (all==0)){
        places = find_at(fp, text, at_num, star, byword);
        //printf("%ld\n", places);
        sprintf(strized, "%ld", places);
    }
    else if( (count == 0) && (at==0) && (all==0)){
        places = find_at(fp, text, 1, star, byword);
        sprintf(strized, "%ld", places);
    }
    star = -1;
    scanf("%s", next);
    if(!strcmp(next, "insertstr"))
        arman_insert(strized);
    else if(!strcmp(next, "replace"))
        arman_replace(strized);
    else if(!strcmp(next, "find"))
        arman_find_input(strized);
    else if(!strcmp(next, "grep"))
        arman_grep_input(strized);
}

void arman_grep_output()
{
    char* arman_line_reader(char* address, long int location);
    void line_reader(char* address, long int location);
    long int* grep_finder(char* location, char* rtext);
    int grep_finder_c(char* location, char* rtext);
    int grep_finder_l(char* location, char* rtext);
    char c;
    char *str, *s, *address, *text;
    address = (char*)calloc(500, sizeof(char));
    str = (char*)calloc(150, sizeof(char));
    s = (char*)calloc(150, sizeof(char));
    text = (char*)calloc(200, sizeof(char));
    char** list = (char**)calloc(100, sizeof(char*));
    long int* line_starts = (long int*)calloc(100, sizeof(int)),*lines = (long int*)calloc(100, sizeof(int)) ;
    for(int i = 0; i < 100; i++) *(list+i) = (char*)calloc(100, sizeof(char));

    int option = 0, count = 0, listct = 0;
    long int i = 0;
    scanf("%s", s);
    if(!strcmp(s, "-c")){
        option = 1;
        scanf("%s", s);
        if(strcasecmp(s, "--str")){
            gets(s);
            printf("Invalid input.\n");
            return;
        }
    }
    else if(!strcmp(s, "-l")){
        option = 2;
        scanf("%c", &c);
        scanf("%s", s);
        if(strcasecmp(s, "--str")){
            gets(s);
            printf("Invalid input.\n");
            return;
        }
    }
    else if(strcasecmp(s, "--str")){
        gets(s);
        printf("Invalid input.\n");
        return;
    }
    scanf("%c", &c);
    scanf("%c", &c);
    if(c != '"'){
        int f = 1;
        str[0] = c;
        scanf("%c", &c);
        while( (c != '\n') && (c != ' ') ){
            str[f] = c;
            f++;
            scanf("%c", &c);
        }
        str[f] = '\0';
    }
    else{
        while(1){
            scanf("%c", &str[i]);
            if((str[i] == '"') && (str[i-1] != '\\'))
                break;
            i++;
        }
        str[i] = '\0';
    }
    text = text_generator(str);
    i = 0;
    scanf("%c", &c);
    scanf("%s", s);
    if(strcasecmp(s, "--file")){
        gets(s);
        printf("Invalid input.\n");
        return;
    }
    scanf("%c", &c);
    while(c != '>'){
        //scanf("%c", &c);
        //if(c=='\n')
            //break;
        scanf("%c", &c);
        if(c=='>')
            break;
        if(c != '"'){
            int f = 1;
            str[0] = c;
            scanf("%c", &c);
            while( (c != '\n') && (c != ' ') ){
                str[f] = c;
                f++;
                scanf("%c", &c);
            }
            str[f] = '\0';
        }
        else{
            while(1){
                scanf("%c", &str[i]);
                if((str[i] == '"') && (str[i-1] != '\\'))
                    break;
                i++;
            }
            str[i] = '\0';
            scanf("%c", &c);
        }
        strcpy(address, str);
        //printf("%s\n", address);
        i = 0;
        if(option == 0){
            lines = grep_finder(address, text);
            int j = 0;
            while(*(lines+j)!=-1){
                strcpy(*(list+listct), address);
                *(line_starts+listct) = *(lines+j);
                listct++;
                j++;
            }
        }
        else if(option == 1)
            count += grep_finder_c(address, text);
        else if(option == 2){
            if(grep_finder_l(address, text)){
                strcpy(*(list+listct), address);
                listct++;
            }
        }
        free(str);
        str = (char*)calloc(200, sizeof(char));
    }
    //printf("%s | %s | %s\n", *(list), *(list+1), *(list+2));
    //printf("%ld | %ld | %ld\n", *(line_starts), *(line_starts+1), *(line_starts+2));
    char *finale = (char*)calloc(3000, sizeof(char));
    if(option==0){
        for(int i = 0; i < listct; i++){
            //printf("%s: ", *(list+i));
            //line_reader(*(list+i), *(line_starts+i));
            //printf("\n");
            strcat(finale, *(list+i));
            strcat(finale, ": ");
            strcat(finale, arman_line_reader(*(list+i), *(line_starts+i)) );
            strcat(finale, "\n");
        }
    }
    else if(option==1){
        sprintf(finale, "%d", count);
    }
    else if(option==2){
        for(int i = 0; i < listct; i++)strcat(finale, *(list+i));
    }
    //printf("%s\n", finale);
    scanf("%c", &c);
    scanf("%s", str);
    if(!strcmp(str, "insertstr"))
        arman_insert(finale);
    else if(!strcmp(str, "replace"))
        arman_replace(finale);
    else if(!strcmp(str, "find"))
        arman_find_input(finale);
    else if(!strcmp(str, "grep"))
        arman_grep_input(finale);
}

void arman_compare()
{
    char *finale = (char*)calloc(5000, sizeof(char)), *strized = (char*)calloc(500, sizeof(char));
    long int* comparing(char* address1, char* address2);
    long int* results = (long int*)calloc(200, sizeof(long int));
    char *str = (char*)calloc(150, sizeof(char)), c;
    char *address1 = (char*)calloc(150, sizeof(char)), *address2 = (char*)calloc(150, sizeof(char));
    long int i = 0;
    scanf("%c", &c);
    scanf("%c", &c);
    if(c != '"'){
        int f = 1;
        str[0] = c;
        scanf("%c", &c);
        while( (c != '\n') && (c != ' ') ){
            str[f] = c;
            f++;
            scanf("%c", &c);
        }
        str[f] = '\0';
    }
    else{
        while(1){
            scanf("%c", &str[i]);
            if((str[i] == '"') && (str[i-1] != '\\'))
                break;
            i++;
        }
        str[i] = '\0';
        scanf("%c", &c);
    }
    strcpy(address1, str);
    //printf("ADDRESS1: |%s|\n", address1);
    i = 0;
    scanf("%c", &c);
    if(c != '"'){
        int f = 1;
        str[0] = c;
        scanf("%c", &c);
        while( (c != '\n') && (c != ' ') ){
            str[f] = c;
            f++;
            scanf("%c", &c);
        }
        str[f] = '\0';
    }
    else{
        while(1){
            scanf("%c", &str[i]);
            if((str[i] == '"') && (str[i-1] != '\\'))
                break;
            i++;
        }
        str[i] = '\0';
        scanf("%c", &c);
    }
    strcpy(address2,str);
    //printf("ADDRESS2: |%s|\n", address2);
    i = 0;
    results = comparing(address1, address2);
    FILE *fp1 = fopen(address1, "r");
    FILE *fp2 = fopen(address2, "r");
    while(*(results+i) != -1){
        fseek(fp1, 0, SEEK_SET);
        fseek(fp2, 0, SEEK_SET);
        int linect = 1, id = 0;
        char* line1 = (char*)calloc(400, sizeof(char)), *line2 = (char*)calloc(400, sizeof(char));
        while(1){
            c= fgetc(fp1);
            if(c=='\n')
                linect++;
            if(linect==*(results+i)){
                long int j = 0;
                while(1){
                    c = fgetc(fp1);
                    if(c=='\n' || c==EOF){
                        id = 1;
                        break;
                    }
                    line1[j] = c;
                    j++;
                }
                line1[j] = '\0';
                break;
            }
            if(id==1)
                break;
        }
        linect = 1;
        while(1){
            c= fgetc(fp2);
            if(c=='\n')
                linect++;
            if(linect==*(results+i)){
                long int j = 0;
                while(1){
                    c = fgetc(fp2);
                    if(c=='\n' || c==EOF)
                        break;
                    line2[j] = c;
                    j++;
                }
                line2[j] = '\0';
                break;
            }
        }
        //printf("========== Line: %ld ==========\n", *(results+i));
        //printf("File 1: %s\n", line1);
        //printf("File 2: %s\n", line2);
        sprintf(strized, "%ld", *(results+i));
        strcat(finale, "========== Line:");
        strcat(finale, strized);
        strcat(finale, "==========\nFile 1: ");
        strcat(finale, line1);
        strcat(finale, "\nFile 2: ");
        strcat(finale, line2);
        strcat(finale, "\n");
        free(line1);
        free(line2);
        i++;
    }
    i++;
    FILE *fp = NULL;
    if(*(results+i)==1)
        fp = fopen(address1, "r");
    else if(*(results+i)==2)
        fp = fopen(address2, "r");
    else
        return;
    int line_end = 1;
    while(1){
        c = fgetc(fp);
        if(c=='\n')
            line_end++;
        if(c==EOF)
            break;
    }
    fseek(fp, 0, SEEK_SET);
    char* buffer = (char*)calloc(300, sizeof(char));
    int linect = 1;
    while(1){
        c = fgetc(fp);
        if(c=='\n')
            linect++;
        if(linect==*(results+i+1)){
            long int j = 0;
            while(1){
                c = fgetc(fp);
                if(c==EOF)
                    break;
                buffer[j] = c;
                j++;
            }
            buffer[j] = '\0';
            break;
        }
        if(c==EOF)
            return;
    }
    //printf(">>>>>>>>>> File: %ld | Start: %ld | End: %d >>>>>>>>>>\n", *(results+i), *(results+i+1), line_end);
    //printf("File %ld: %s\n", *(results+i), buffer);
    strcat(finale, ">>>>>>>>>> File: ");
    if(*(results+i)==1)
        strcat(finale, "1 | Start: ");
    else
        strcat(finale, "2 | Start: ");
    char *end = (char*)calloc(200, sizeof(char)), *start = (char*)calloc(200, sizeof(char));
    sprintf(start, "%ld", *(results+i+1));
    sprintf(end, "%d", line_end);
    strcat(finale, start);
    strcat(finale, " | End: ");
    strcat(finale, end);
    strcat(finale, " >>>>>>>>>>\nFile ");
    if(*(results+i)==1)
        strcat(finale, "1: ");
    else
        strcat(finale, "2: ");
    strcat(finale, buffer);
    scanf("%s", str);
    if(!strcmp(str, "insertstr"))
        arman_insert(finale);
    else if(!strcmp(str, "replace"))
        arman_replace(finale);
    else if(!strcmp(str, "find"))
        arman_find_input(finale);
    else if(!strcmp(str, "grep"))
        arman_grep_input(finale);
}

void arman_tree()
{
    char *str = (char*)calloc(200, sizeof(char)),*svr = (char*)calloc(2000, sizeof(char)), c;
    scanf("%d", &reccur);
    char* arman_filelist(char* directory, int indentnum, int counter, char *sv);
    svr = arman_filelist(".", 4, 1, svr);
    //printf("%s\n", svr);
    scanf("%c", &c);
    scanf("%s", str);
    if(!strcmp(str, "insertstr"))
        arman_insert(svr);
    else if(!strcmp(str, "replace"))
        arman_replace(svr);
    else if(!strcmp(str, "find"))
        arman_find_input(svr);
    else if(!strcmp(str, "grep"))
        arman_grep_input(svr);
    //free(bush);
    reccur = 0;
}

void arman()
{
    char *str = (char*)calloc(100, sizeof(char));
    scanf("%s", str);
    if(!strcmp(str, "cat"))
        arman_cat();
    else if(!strcmp(str, "find"))
        arman_find_output();
    else if(!strcmp(str, "grep"))
        arman_grep_output();
    else if(!strcmp(str, "compare"))
        arman_compare();
    else if(!strcmp(str, "tree"))
        arman_tree();
    else{
        gets(str);
        printf("Invalid input");
    }
}

char* text_generator(char* atext)
{
    char* buffer = (char*)malloc(3000);
    long int i = 0, j = 0;
    while(atext[i]  != '\0'){
        if(atext[i] == '\\'){
            if(atext[i+1] == 'n'){
                buffer[j] = '\n';
                j++;
                i+=2;
            }
            else if(atext[i+1] == '\\'){
                buffer[j] = '\\';
                j++;
                i+=2;
            }
            else if(atext[i+1] == '"'){
                buffer[j] = '"';
                j++;
                i+=2;
            }
            else if(atext[i+1] == '*'){
                //printf("i: %d", i);
                buffer[j] = '*';
                j++;
                i+=2;
                //printf("new i: %d", i);
            }
            else{
                buffer[j] = atext[i];
                i++;
                j++;
            }
            continue;
        }
        if(atext[i]=='*'){
            star = i;
            //printf("FUCCK\n", i);
        }
        buffer[j] = atext[i];
        i++;
        j++;
    }
    buffer[j] = '\0';
    return buffer;
}

/////////////////////////////////
//////    grep functions   //////
/////////////////////////////////

long int* grep_finder(char* location, char* rtext)
{
    char c;
    long int *lines = (long int*)calloc(100, sizeof(long int));
    int ct = 0;
    FILE *fp = NULL;
    fp = fopen(location, "rb+");
    if(fp == NULL){
        return NULL;
    }
    fseek(fp, 0L, SEEK_END);
    long int len = strlen(rtext);
    long int end = ftell(fp);
    char* buffer = (char*)malloc(len);
    fseek(fp, 0L, SEEK_SET);
    long int line_start = 0;

    for(long int i = 0; i < end; i++){
        int j = 0;
        fseek(fp, i, SEEK_SET);
        if(fgetc(fp)=='\n'){
            line_start = ftell(fp);
            //printf("new: %ld\n", line_start);
        }
        fseek(fp, i, SEEK_SET);
        for(j = 0; j < len; j++){
            c = fgetc(fp);
            buffer[j] = c;
        }
        buffer[j] = '\0';
        if(!strcmp(buffer, rtext)){
          *(lines+ct) = line_start;
          ct++;
          c = fgetc(fp);
          while(c != '\n' && c != EOF)
              c = fgetc(fp);
          if(c==EOF)
            break;
          i = ftell(fp)-2;
        }
    }
    *(lines+ct) = -1;
    return lines;
}

int grep_finder_c(char* location, char* rtext)
{
    char c;
    int line_counter = 0;
    FILE *fp = NULL;
    fp = fopen(location, "rb+");
    if(fp == NULL){
        //printf("HHH\n");
        return line_counter;
    }
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

int grep_finder_l(char* location, char* rtext)
{
    char c;
    FILE *fp = NULL;
    fp = fopen(location, "rb+");
    if(fp == NULL){
        return 0;
    }
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
          return 1;
          fclose(fp);
          free(buffer);
        }
    }
    return 0;
}

void line_reader(char* address, long int location)
{
    FILE *fp = fopen(address, "rb");
    fseek(fp, location, SEEK_SET);
    char c = fgetc(fp);
    while(c!='\n' && c!=EOF){
        printf("%c", c);
        c = fgetc(fp);
    }
    fclose(fp);
}

char* arman_line_reader(char* address, long int location)
{
    FILE *fp = fopen(address, "rb");
    char* buffer = (char*)calloc(3000, sizeof(char));
    int i = 0;
    fseek(fp, location, SEEK_SET);
    char c = fgetc(fp);
    while(c!='\n' && c!=EOF){
        buffer[i] = c;
        c = fgetc(fp);
        i++;
    }
    buffer[i] ='\0';
    fclose(fp);
    return buffer;
}

void previous_saver(char* location, char* rtext)
{
    char def[700] = "C:\\Users\\shayan\\Documents\\GitHub\\project-shayandesu\\Copy\\";
    strcat(def, location);
    char* str_ = (char*)calloc(200, sizeof(char));

    int i = 0;
    long int j= 0;

    while(1){
        if(def[i]=='\\'){
            mkdir(str_);
        }
        str_[i] = def[i];
        i++;
        if(def[i]=='\0'){
            str_[i] = '\0';
            break;
        }
    }

    FILE *fp = fopen(def, "wb+");
    if(fp==NULL){
        printf("Crashed\n");
        return;
    }
    while(rtext[j] != '\0'){
        fputc(rtext[j], fp);
        j++;
    }
    fclose(fp);
}

//////////////////////////////////////////////////
//INDENT

char* space(char* text, long int location)
{
    char* buff = (char*)calloc(5000, sizeof(char));
    long int i = location-1, j = 0, k = -1;
    while(i >= 0){
        if(text[i] == ' ')
            i--;
        else{
            k = i;
            break;
        }
    }
    //printf("\n\n\nFirst non-whitespace character: %ld, %c\n\n\n", k, text[k]);
    for(j = 0; j <= k; j++) buff[j] = text[j];
    if(text[k]=='\n'){
        buff[k+1] = '{';
        j = k+2;
    }
    else if(k==-1){
        buff[0] = '{';
        j = 1;
    }
    else{
        buff[k+1] = ' ';
        buff[k+2] = '{';
        j = k+3;
    }
    i = location+1;
    while(1){
        buff[j] = text[i];
        if(text[i] == '\0')
            break;
        i++;
        j++;
    }

    //printf("\n\n\n\n\n============\n\n%s\n\n============\n\n\n\n\n", buff);
    return buff;
}

char* nospace(char* text, long int location)
{
    char* buff = (char*)calloc(5000, sizeof(char));
    long int i = location-1, j = 0, k = -1;
    while(i >= 0){
        if(text[i] == ' ')
            i--;
        else{
            k = i;
            break;
        }
    }
    for(j = 0; j <= k; j++) buff[j] = text[j];
    if(text[k] == '\n'){
        buff[k+1] = '}';
        j = k+2;
    }
    else{
        buff[k+1] = '\n';
        buff[k+2] = '}';
        j = k+3;
    }
    i = location+1;
    while(1){
        buff[j] = text[i];
        if(text[i] == '\0')
            break;
        i++;
        j++;
    }
    return buff;
}

char* newline1(char* text, long int location)
{
    char* buff = (char*)calloc(1000, sizeof(char));
    long int i = location, k = -1;
    while(text[i] != '\n'){
        if(text[i] == ' '){
            i++;
            continue;
        }
        else{
            k = i;
            break;
        }
    }
    if(k == -1)
        return text;
    long int j = 0;
    for(j = 0; j < location; j++) buff[j] = text[j];
    buff[location] = '\n';
    j = location+1;
    while(text[k] != '\0'){
        buff[j] = text[k];
        j++;
        k++;
    }
    return buff;
}


char* emptybrace(char* text, long int left, long int right)
{
    char* buff = (char*)calloc(5000, sizeof(char));
    for(long int i = 0; i <= left; i++) buff[i] = text[i];
    buff[left+1] = '\n';
    buff[left+2] = '\n';
    long int i = left+3, j = right;
    while(1){
        buff[i] = text[j];
        if(text[j] == '\0')
            break;
        i++;
        j++;
    }
    return buff;
}

char* indentation(char*text, long int location, int indent)
{
    char* buff = (char*)calloc(5000, sizeof(char));
    for(long int i = 0; i <= location; i++) buff[i] = text[i];
    long int i = 1, j = location+1;
    for(; i <= indent;i++) buff[location+i] = ' ';
    i = location+indent+1;
    while(1){
        buff[i] = text[j];
        if(text[j] == '\0')
            break;
        i++;
        j++;
    }
    return buff;
}

//////////////////////////////////////////////////


//////////////////////////////////////////////////
//FIND

int find_count(FILE *fp, char* dtext, int starpos)
{
    char c;
    int counter = 0;
    long int len = strlen(dtext);
    char* buffer = (char*)malloc(len);
    char* noast = (char*)calloc(200, sizeof(char));
    fseek(fp, -len, SEEK_END);
    long int end = ftell(fp);
    if(0==starpos){
        long int ct = 0;
        while(1){
            noast[ct] = dtext[ct+1];
            if(dtext[ct+1]=='\0')
                break;
            ct++;
        }
        for(long int i = 0; i < end; i++){
            int j = 0, id = 0;
            fseek(fp, i-1, SEEK_SET);
            char before = fgetc(fp);
            fseek(fp, i, SEEK_SET);
            for(j = 0; j < len-1; j++){
                c = fgetc(fp);
                if(c==EOF){
                    id = 1;
                    break;
                }
                buffer[j] = c;
            }
            buffer[j] = '\0';
            //printf("buffer:|%s|\n", buffer);
            if(id==1)
                break;
            if(!strcmp(buffer, noast)){
                if( (before!= ' ') && (before!= '\n') ){
                    counter++;
                    while(1){
                        c = fgetc(fp);
                        if(c==' '){
                            i = ftell(fp);
                            break;
                        }
                        if(c==EOF){
                            id = 1;
                            break;
                        }
                    }
                    if(id==1)
                        break;
                }
            }
        }
        free(buffer);
        free(noast);
        return counter;
    }
    else if(len-1==starpos){
        //printf("HERE\n");
        //printf("%ld\n", len);
        int i = 0;
        for(; i < len-1; i++) noast[i] = dtext[i];
        noast[i] = '\0';
        //printf("%s\n", noast);
        for(long int i = 0; i < end; i++){
            int j = 0, id = 0;
            fseek(fp, i, SEEK_SET);
            for(j = 0; j < len-1; j++){
                c = fgetc(fp);
                if(c==EOF){
                    id = 1;
                    break;
                }
                buffer[j] = c;
            }
            if(id==1)
                break;
            buffer[j] = '\0';
            char after = fgetc(fp);
            //printf("buffer:|%s|\n", buffer);
            if(!strcmp(buffer, noast)){
                //printf("H\n");
                if( (after!= ' ') && (after!= '\n') ){
                    counter++;
                    while(1){
                        c = fgetc(fp);
                        if(c==' '){
                            i = ftell(fp);
                            break;
                        }
                        if(c==EOF){
                            id = 1;
                            break;
                        }
                    }
                    if(id==1)
                        break;
                }
            }
        }
        free(buffer);
        free(noast);
        return counter;
    }
    else if(starpos != -1){
        char* noast1 = (char*)calloc(200, sizeof(char)), *noast2 = (char*)calloc(200, sizeof(char));
        int i = 0;
        for(i = 0; i < starpos; i++){
            noast1[i] = dtext[i];
        }
        noast1[starpos] = '\0';
        int k = starpos+1;
        i = 0;

        while(1){
            noast2[i] = dtext[k];
            if(dtext[i]=='\0')
                break;
            k++;
            i++;
        }
        //printf("Noast1: %s\n\nNoast2: %s\n\n", noast1, noast2);
        int len1 = strlen(noast1), len2 = strlen(noast2);
        char* buffer1 = (char*)calloc(len1, sizeof(char)), *buffer2 = (char*)calloc(len2, sizeof(char));
        for(long int i = 0; i < end; i++){
            int j = 0, id = 0;
            fseek(fp, i, SEEK_SET);
            for(j = 0; j < len1; j++){
                c = fgetc(fp);
                if(c==EOF){
                    id = 1;
                    break;
                }
                buffer1[j] = c;
            }
            buffer1[j] = '\0';
            //printf("buffer1:|%s|\n", buffer1);
            if(id==1)
                break;
            if(!strcmp(buffer1, noast1)){
                long int m = ftell(fp)+1L;
                long int start = m;
                for(; m < end; m++){
                    int n = 0;
                    fseek(fp, m, SEEK_SET);
                    for(n = 0; n < len2; n++){
                        c = fgetc(fp);
                        if(c==EOF){
                            id = 1;
                            break;
                        }
                        buffer2[n] = c;
                    }
                buffer2[n] = '\0';
                //printf("    buffer2:|%s|\n", buffer2);
                if(id==1)
                    break;
                if(!strcmp(buffer2, noast2)){
                        fseek(fp, start, SEEK_SET);
                        int nos = 0;
                        for(long int h = start; h < m; h++){
                            c = fgetc(fp);
                            if((c==' ')||(c=='\n')){
                                nos = 1;
                                break;
                            }
                        }
                        if(nos==0)
                            counter++;
                    }
                }
            if(id==1)
                break;
            }
        }
    free(noast1);
    free(noast2);
    free(buffer1);
    free(buffer2);
    return counter;
    }
    else{
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
        if(!strcmp(buffer, dtext))
            counter++;
        }
        free(buffer);
        return counter;
    }
}

long int* find_all(FILE *fp, char* dtext, int starpos, int word)
{
    char c , c_ = '\0';
    long int *answers = (long int*)calloc(500, sizeof(long int));
    int answersct = 0;
    long int len = strlen(dtext);
    char* buffer = (char*)malloc(len);
    char* noast = (char*)calloc(200, sizeof(char));
    fseek(fp, 0L, SEEK_END);
    long int end = ftell(fp);
    if(0==starpos){
        long int ct = 0;
        while(1){
            noast[ct] = dtext[ct+1];
            if(dtext[ct+1]=='\0')
                break;
            ct++;
        }
        for(long int i = 0; i < end; i++){
            int j = 0, id = 0;
            fseek(fp, i-1, SEEK_SET);
            char before = fgetc(fp);
            fseek(fp, i, SEEK_SET);
            for(j = 0; j < len-1; j++){
                c = fgetc(fp);
                if(c==EOF){
                    id = 1;
                    break;
                }
                buffer[j] = c;
            }
            buffer[j] = '\0';
            //printf("buffer:|%s|\n", buffer);
            if(id==1)
                break;
            if(!strcmp(buffer, noast)){
                if( (before!= ' ') && (before!= '\n') ){
                    long int space = 0, wordct = 1;
                    long int h = 0;
                    while(h <= i){
                        fseek(fp, h, SEEK_SET);
                        c = fgetc(fp);
                        if( (c== ' ') || (c=='\n'))
                            space = h;
                        if( (c != ' ') && (c != '\n')){
                            if( (c_==' ') || (c_=='\n') )
                               wordct++;
                        }
                        c_ = c;
                        h++;
                    }
                    if(word==1)
                        *(answers+answersct) = wordct;
                    else
                        *(answers+answersct) = space;
                    answersct++;
                    fseek(fp, i, SEEK_SET);
                    while(1){
                        c = fgetc(fp);
                        if(c==' '){
                            i = ftell(fp);
                            break;
                        }
                        if(c==EOF){
                            id = 1;
                            break;
                        }
                    }
                    if(id==1)
                        break;
                }
            }
        }
        free(buffer);
        free(noast);
    }
    else if(len-1==starpos){
        int i = 0, wordct = 1;
        char c_ = '\0';
        for(; i < len-1; i++) noast[i] = dtext[i];
        noast[i] = '\0';
        for(long int i = 0; i < end; i++){
            int j = 0, id = 0;
            fseek(fp, i, SEEK_SET);
            for(j = 0; j < len-1; j++){
                c = fgetc(fp);
                if(c==EOF){
                    id = 1;
                    break;
                }
                buffer[j] = c;
            }
            buffer[j] = '\0';
            char after = fgetc(fp);
            //printf("buffer:|%s|\n", buffer);
            if(id==1)
                break;
            if(!strcmp(buffer, noast)){
                if( (after!= ' ') && (after!= '\n') ){
                    long int h = 0;
                    while(h <= i){
                        fseek(fp, h, SEEK_SET);
                        c = fgetc(fp);
                        if( (c != ' ') && (c != '\n')){
                            if( (c_==' ') || (c_=='\n') )
                               wordct++;
                        }
                        c_ = c;
                        h++;
                    }
                    //printf("I: %ld | H: %ld\n", i, h);
                    if(word==1)
                        *(answers+answersct) = wordct;
                    else
                        *(answers+answersct) = i;
                    wordct = 1;
                    answersct++;
                    fseek(fp, i, SEEK_SET);
                    while(1){
                        c = fgetc(fp);
                        if(c==' '){
                            i = ftell(fp);
                            break;
                        }
                        if(c==EOF){
                            id = 1;
                            break;
                        }
                    }
                    if(id==1)
                        break;
                }
            }
        }
        free(buffer);
        free(noast);
    }
    else if(starpos != -1){
        char* noast1 = (char*)calloc(200, sizeof(char)), *noast2 = (char*)calloc(200, sizeof(char));
        int i = 0;
        for(i = 0; i < starpos; i++){
            noast1[i] = dtext[i];
        }
        noast1[starpos] = '\0';
        int k = starpos+1;
        i = 0;

        while(1){
            noast2[i] = dtext[k];
            if(dtext[i]=='\0')
                break;
            k++;
            i++;
        }
        //printf("Noast1: %s\n\nNoast2: %s\n\n", noast1, noast2);
        int len1 = strlen(noast1), len2 = strlen(noast2);
        char* buffer1 = (char*)calloc(len1, sizeof(char)), *buffer2 = (char*)calloc(len2, sizeof(char));
        for(long int i = 0; i < end; i++){
            int j = 0, id = 0;
            fseek(fp, i, SEEK_SET);
            for(j = 0; j < len1; j++){
                c = fgetc(fp);
                if(c==EOF){
                    id = 1;
                    break;
                }
                buffer1[j] = c;
            }
            buffer1[j] = '\0';
            //printf("buffer1:|%s|\n", buffer1);
            if(id==1)
                break;
            if(!strcmp(buffer1, noast1)){
                long int m = ftell(fp)+1L;
                long int start = m;
                for(; m < end; m++){
                    int n = 0;
                    fseek(fp, m, SEEK_SET);
                    for(n = 0; n < len2; n++){
                        c = fgetc(fp);
                        if(c==EOF){
                            id = 1;
                            break;
                        }
                        buffer2[n] = c;
                    }
                buffer2[n] = '\0';
                //printf("    buffer2:|%s|\n", buffer2);
                if(id==1)
                    break;
                if(!strcmp(buffer2, noast2)){
                        fseek(fp, start, SEEK_SET);
                        int nos = 0;
                        for(long int h = start; h < m; h++){
                            c = fgetc(fp);
                            if((c==' ')||(c=='\n')){
                                nos = 1;
                                break;
                            }
                        }
                        if(nos==0){
                            int wordct = 1;
                            long int h = 0;
                            while(h <= i){
                                fseek(fp, h, SEEK_SET);
                                c = fgetc(fp);
                                if( (c != ' ') && (c != '\n')){
                                    if( (c_==' ') || (c_=='\n') )
                                    wordct++;
                                }
                                c_ = c;
                                h++;
                            }
                            //printf("I: %ld | H: %ld\n", i, h);
                            if(word==1)
                                *(answers+answersct) = wordct;
                            else
                                *(answers+answersct) = i;
                            wordct = 1;
                            answersct++;
                        }
                    }
                }
            if(id==1)
                break;
            }
        }
    free(noast1);
    free(noast2);
    free(buffer1);
    free(buffer2);
    }
    else{
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
        if(!strcmp(buffer, dtext)){
            int wordct = 1;
            long int h = 0;
            while(h <= i){
                fseek(fp, h, SEEK_SET);
                c = fgetc(fp);
                if( (c != ' ') && (c != '\n')){
                    if( (c_==' ') || (c_=='\n') )
                    wordct++;
                }
                c_ = c;
                h++;
            }
            //printf("I: %ld | H: %ld\n", i, h);
            if(word==1)
                *(answers+answersct) = wordct;
            else
                *(answers+answersct) = i;
            wordct = 1;
            answersct++;
            if(word==1){
                while(1){
                    c = fgetc(fp);
                    if(c==' '){
                        i = ftell(fp);
                        break;
                    }
                    if(c==EOF){
                        id = 1;
                        break;
                    }
                }
                if(id==1)
                    break;
            }
        }
        }
        free(buffer);
    }
    answers[answersct] = -1;
    return answers;
}

long int find_at(FILE *fp, char* dtext, int place, int starpos, int word)
{
    //printf("Star: %d\n", starpos);
    char c , c_ = '\0';
    int counter = 0;
    long int len = strlen(dtext);
    char* buffer = (char*)malloc(len);
    char* noast = (char*)calloc(200, sizeof(char));
    fseek(fp, 0L, SEEK_END);
    long int end = ftell(fp);
    if(0==starpos){
        long int ct = 0;
        while(1){
            noast[ct] = dtext[ct+1];
            if(dtext[ct+1]=='\0')
                break;
            ct++;
        }
        for(long int i = 0; i < end; i++){
            int j = 0, id = 0;
            fseek(fp, i-1, SEEK_SET);
            char before = fgetc(fp);
            fseek(fp, i, SEEK_SET);
            for(j = 0; j < len-1; j++){
                c = fgetc(fp);
                if(c==EOF){
                    id = 1;
                    break;
                }
                buffer[j] = c;
            }
            buffer[j] = '\0';
            //printf("buffer:|%s|\n", buffer);
            if(id==1)
                break;
            if(!strcmp(buffer, noast)){
                if( (before!= ' ') && (before!= '\n') ){
                    counter++;
                    long int space = 0, wordct = 1;
                    long int h = 0;
                    while(h <= i){
                        fseek(fp, h, SEEK_SET);
                        c = fgetc(fp);
                        if( (c== ' ') || (c=='\n'))
                            space = h;
                        if( (c != ' ') && (c != '\n')){
                            if( (c_==' ') || (c_=='\n') )
                               wordct++;
                        }
                        c_ = c;
                        h++;
                    }
                    if(counter==place){
                        if(word==1)
                            return wordct;
                        else
                            return space;
                    }
                    fseek(fp, i, SEEK_SET);
                    while(1){
                        c = fgetc(fp);
                        if(c==' '){
                            i = ftell(fp);
                            break;
                        }
                        if(c==EOF){
                            id = 1;
                            break;
                        }
                    }
                    if(id==1)
                        break;
                }
            }
        }
        free(buffer);
        free(noast);
    }
    else if(len-1==starpos){
        int i = 0, wordct = 1;
        char c_ = '\0';
        for(; i < len-1; i++) noast[i] = dtext[i];
        noast[i] = '\0';
        for(long int i = 0; i < end; i++){
            int j = 0, id = 0;
            fseek(fp, i, SEEK_SET);
            for(j = 0; j < len-1; j++){
                c = fgetc(fp);
                if(c==EOF){
                    id = 1;
                    break;
                }
                buffer[j] = c;
            }
            buffer[j] = '\0';
            char after = fgetc(fp);
            //printf("buffer:|%s|\n", buffer);
            if(id==1)
                break;
            if(!strcmp(buffer, noast)){
                if( (after!= ' ') && (after!= '\n') ){
                    counter++;
                    long int h = 0;
                    while(h <= i){
                        fseek(fp, h, SEEK_SET);
                        c = fgetc(fp);
                        if( (c != ' ') && (c != '\n')){
                            if( (c_==' ') || (c_=='\n') )
                               wordct++;
                        }
                        c_ = c;
                        h++;
                    }
                    //printf("I: %ld | H: %ld\n", i, h);
                    if(counter==place){
                        if(word==1)
                            return wordct;
                        else
                            return i;
                    }
                    wordct = 1;
                    fseek(fp, i, SEEK_SET);
                    while(1){
                        c = fgetc(fp);
                        if(c==' '){
                            i = ftell(fp);
                            break;
                        }
                        if(c==EOF){
                            id = 1;
                            break;
                        }
                    }
                    if(id==1)
                        break;
                }
            }
        }
        free(buffer);
        free(noast);
    }
    else if(starpos != -1){
        char* noast1 = (char*)calloc(200, sizeof(char)), *noast2 = (char*)calloc(200, sizeof(char));
        int i = 0;
        for(i = 0; i < starpos; i++){
            noast1[i] = dtext[i];
        }
        noast1[starpos] = '\0';
        int k = starpos+1;
        i = 0;

        while(1){
            noast2[i] = dtext[k];
            if(dtext[i]=='\0')
                break;
            k++;
            i++;
        }
        noast2[i] = '\0';
        //printf("Noast1: %s\n\nNoast2: %s\n\n", noast1, noast2);
        int len1 = strlen(noast1), len2 = strlen(noast2);
        char* buffer1 = (char*)calloc(len1, sizeof(char)), *buffer2 = (char*)calloc(len2, sizeof(char));
        for(long int i = 0; i < end; i++){
            int j = 0, id = 0;
            fseek(fp, i, SEEK_SET);
            for(j = 0; j < len1; j++){
                c = fgetc(fp);
                if(c==EOF){
                    id = 1;
                    break;
                }
                buffer1[j] = c;
            }
            buffer1[j] = '\0';
            //printf("buffer1:|%s|\n", buffer1);
            if(id==1)
                break;
            if(!strcmp(buffer1, noast1)){
                //printf("buf1 found: %ld\n", i);
                long int m = ftell(fp)+1L;
                long int start = m;
                for(; m < end; m++){
                    int n = 0;
                    fseek(fp, m, SEEK_SET);
                    for(n = 0; n < len2; n++){
                        c = fgetc(fp);
                        if(c==EOF){
                            break;
                        }
                        buffer2[n] = c;
                    }
                buffer2[n] = '\0';
                //printf("    buffer2:|%s|\n", buffer2);
                if(id==1)
                    break;
                if(!strcmp(buffer2, noast2)){
                        //printf("buf1 found: %ld\n", m);
                        fseek(fp, start, SEEK_SET);
                        int nos = 0;
                        for(long int h = start; h < m; h++){
                            fseek(fp, h, SEEK_SET);
                            c = fgetc(fp);
                            if((c==' ')||(c=='\n')){
                                //printf("No\n");
                                nos = 1;
                                break;
                            }
                        }
                        if(nos==0){
                            counter++;
                            int wordct = 1;
                            long int h = 0;
                            while(h <= i){
                                fseek(fp, h, SEEK_SET);
                                c = fgetc(fp);
                                if( (c != ' ') && (c != '\n')){
                                    if( (c_==' ') || (c_=='\n') )
                                    wordct++;
                                }
                                c_ = c;
                                h++;
                            }
                            //printf("I: %ld | H: %ld\n", i, h);
                            if(counter==place){
                                if(word==1)
                                    return wordct;
                                else
                                    return i;
                            }
                            wordct = 1;
                        }
                    }
                }
            }
        }
    free(noast1);
    free(noast2);
    free(buffer1);
    free(buffer2);
    }
    else{
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
        if(!strcmp(buffer, dtext)){
            counter++;
            int wordct = 1;
            long int h = 0;
            while(h <= i){
                fseek(fp, h, SEEK_SET);
                c = fgetc(fp);
                if( (c != ' ') && (c != '\n')){
                    if( (c_==' ') || (c_=='\n') )
                    wordct++;
                }
                c_ = c;
                h++;
            }
            //printf("I: %ld | H: %ld\n", i, h);
            if(counter==place){
                if(word==1)
                    return wordct;
                else
                    return i;
            }
            wordct = 1;
        }
        }
        free(buffer);
    }
    return -1;
}

////////////////////////////////////////////////////////
//REPLACE
void replace_at(char* file_address, char* changetext, long int location1, long int location2)
{
    if(location1==-1)
        return;
    FILE *fp = fopen(file_address, "rb");
    fseek(fp, 0L, SEEK_END);
    long int end = ftell(fp), i = 0, j = 0;
    long int buf2size = end - location2 + 1;
    char *buffer1 = (char*)calloc(location1, sizeof(char));
    char *buffer2 = (char*)calloc(buf2size, sizeof(char));
    fseek(fp, 0L, SEEK_SET);
    while(i < location1){
        buffer1[i] = fgetc(fp);
        i++;
    }
    buffer1[i] = '\0';
    fseek(fp, location2, SEEK_SET);
    i = location2;
    while(i < end){
        buffer2[j] = fgetc(fp);
        j++;
        i++;
    }
    buffer2[j] = '\0';
    fclose(fp);
    fp = fopen(file_address, "w+");
    long int h = 0;
    while(1){
        if((buffer1[h]=='\0')){
            break;
        }
        fputc(buffer1[h], fp);
        h++;
    }
    h = 0;
    while(1){
        if((changetext[h]=='\0')){
            break;
        }
        fputc(changetext[h], fp);
        h++;
    }
    h = 0;
    while(1){
        if((buffer2[h]=='\0')){
            fputc(EOF, fp);
            break;
        }
        fputc(buffer2[h], fp);
        h++;
    }
    fclose(fp);
}

void replace_all(char* address, char* text, long int* starts, long int* ends)
{
    char* allbuffer = (char*)calloc(5000, sizeof(char)), *buffer = (char*)calloc(5000, sizeof(char)), c;
    FILE *fp = fopen(address, "rb");
    fseek(fp, 0L, SEEK_END);
    long int end = ftell(fp);
    fseek(fp, 0L, SEEK_SET);
    long int i = 0, j = 0, k = 0;
    while(i < *starts){
        fseek(fp, i, SEEK_SET);
        c = fgetc(fp);
        allbuffer[i] = c;
        i++;
    }
    allbuffer[*starts] = '\0';
    strcat(allbuffer, text);
    while(1){
        k = 0;
        i = *(ends+j);
        fseek(fp, i, SEEK_SET);
        if(*(starts+j+1)==-1){
            while( i <= end){
                fseek(fp, i, SEEK_SET);
                c = fgetc(fp);
                buffer[k] = c;
                k++;
                i++;
            }
            buffer[k] = '\0';
            strcat(allbuffer, buffer);
            break;
        }
        while( i < *(starts+j+1)){
            fseek(fp, i, SEEK_SET);
            c = fgetc(fp);
            buffer[k] = c;
            k++;
            i++;
        }
        buffer[k] = '\0';
        //printf("\n==============\n%s\n============\n", buffer);
        strcat(allbuffer, buffer);
        strcat(allbuffer, text);
        j++;
    }
    fclose(fp);
    fp = fopen(address, "w+");
    long int h = 0;
    while(1){
        if((allbuffer[h]=='\0')){
            fputc(EOF, fp);
            break;
        }
        fputc(allbuffer[h], fp);
        h++;
    }
    fclose(fp);
    free(buffer);
    free(allbuffer);
}

long int find_at2(FILE *fp, char* dtext, int place, int starpos, int word)
{
    char c , c_ = '\0';
    int counter = 0;
    long int len = strlen(dtext);
    char* buffer = (char*)malloc(len);
    char* noast = (char*)calloc(200, sizeof(char));
    fseek(fp, 0L, SEEK_END);
    long int end = ftell(fp);
    if(0==starpos){
        long int ct = 0;
        while(1){
            noast[ct] = dtext[ct+1];
            if(dtext[ct+1]=='\0')
                break;
            ct++;
        }
        for(long int i = 0; i < end; i++){
            int j = 0, id = 0;
            fseek(fp, i-1, SEEK_SET);
            char before = fgetc(fp);
            fseek(fp, i, SEEK_SET);
            for(j = 0; j < len-1; j++){
                c = fgetc(fp);
                if(c==EOF){
                    id = 1;
                    break;
                }
                buffer[j] = c;
            }
            buffer[j] = '\0';
            //printf("buffer:|%s|\n", buffer);
            if(id==1)
                break;
            if(!strcmp(buffer, noast)){
                if( (before!= ' ') && (before!= '\n') ){
                    long int ending = i + len -1;
                    counter++;
                    /*long int space = 0, wordct = 1;
                    long int h = 0;
                    while(h <= i){
                        fseek(fp, h, SEEK_SET);
                        c = fgetc(fp);
                        if( (c== ' ') || (c=='\n'))
                            space = h;
                        if( (c != ' ') && (c != '\n')){
                            if( (c_==' ') || (c_=='\n') )
                               wordct++;
                        }
                        c_ = c;
                        h++;
                    }*/
                    if(counter==place){
                        return ending;
                    }
                    fseek(fp, i, SEEK_SET);
                    while(1){
                        c = fgetc(fp);
                        if(c==' '){
                            i = ftell(fp);
                            break;
                        }
                        if(c==EOF){
                            id = 1;
                            break;
                        }
                    }
                    if(id==1)
                        break;
                }
            }
        }
        free(buffer);
        free(noast);
    }
    else if(len-1==starpos){
        int i = 0, wordct = 1;
        char c_ = '\0';
        for(; i < len-1; i++) noast[i] = dtext[i];
        noast[i] = '\0';
        for(long int i = 0; i < end; i++){
            int j = 0, id = 0;
            fseek(fp, i, SEEK_SET);
            for(j = 0; j < len-1; j++){
                c = fgetc(fp);
                if(c==EOF){
                    id = 1;
                    break;
                }
                buffer[j] = c;
            }
            buffer[j] = '\0';
            char after = fgetc(fp);
            //printf("buffer:|%s|\n", buffer);
            if(id==1)
                break;
            if(!strcmp(buffer, noast)){
                if( (after!= ' ') && (after!= '\n') ){
                    long int text_ending = i + len, ending = 0;
                    fseek(fp, text_ending, SEEK_SET);
                    while(1){
                        c = fgetc(fp);
                        if( (c==' ') || (c=='\n')){
                            ending = ftell(fp)-1;
                            break;
                        }
                        else if(c==EOF){
                            ending = ftell(fp);
                            break;
                        }
                    }
                    counter++;
                    long int h = 0;
                    while(h <= i){
                        fseek(fp, h, SEEK_SET);
                        c = fgetc(fp);
                        if( (c != ' ') && (c != '\n')){
                            if( (c_==' ') || (c_=='\n') )
                               wordct++;
                        }
                        c_ = c;
                        h++;
                    }
                    //printf("I: %ld | H: %ld\n", i, h);
                    if(counter==place){
                        if(word==1)
                            return wordct;
                        else
                            return ending;
                    }
                    wordct = 1;
                    fseek(fp, i, SEEK_SET);
                    while(1){
                        c = fgetc(fp);
                        if(c==' '){
                            i = ftell(fp);
                            break;
                        }
                        if(c==EOF){
                            id = 1;
                            break;
                        }
                    }
                    if(id==1)
                        break;
                }
            }
        }
        free(buffer);
        free(noast);
    }
    else if(starpos != -1){
        char* noast1 = (char*)calloc(200, sizeof(char)), *noast2 = (char*)calloc(200, sizeof(char));
        int i = 0;
        for(i = 0; i < starpos; i++){
            noast1[i] = dtext[i];
        }
        noast1[starpos] = '\0';
        int k = starpos+1;
        i = 0;

        while(1){
            noast2[i] = dtext[k];
            if(dtext[i]=='\0')
                break;
            k++;
            i++;
        }
        //printf("Noast1: %s\n\nNoast2: %s\n\n", noast1, noast2);
        int len1 = strlen(noast1), len2 = strlen(noast2);
        char* buffer1 = (char*)calloc(len1, sizeof(char)), *buffer2 = (char*)calloc(len2, sizeof(char));
        for(long int i = 0; i < end; i++){
            int j = 0, id = 0;
            fseek(fp, i, SEEK_SET);
            for(j = 0; j < len1; j++){
                c = fgetc(fp);
                if(c==EOF){
                    id = 1;
                    break;
                }
                buffer1[j] = c;
            }
            buffer1[j] = '\0';
            //printf("buffer1:|%s|\n", buffer1);
            if(id==1)
                break;
            if(!strcmp(buffer1, noast1)){
                long int m = ftell(fp)+1L;
                long int start = m;
                for(; m < end; m++){
                    int n = 0;
                    fseek(fp, m, SEEK_SET);
                    for(n = 0; n < len2; n++){
                        c = fgetc(fp);
                        if(c==EOF){

                            break;
                        }
                        buffer2[n] = c;
                    }
                buffer2[n] = '\0';
                //printf("    buffer2:|%s|\n", buffer2);
                if(id==1)
                    break;
                if(!strcmp(buffer2, noast2)){
                        fseek(fp, start, SEEK_SET);
                        int nos = 0;
                        for(long int h = start; h < m; h++){
                            c = fgetc(fp);
                            if((c==' ')||(c=='\n')){
                                nos = 1;
                                break;
                            }
                        }
                        if(nos==0){
                            counter++;
                            int wordct = 1;
                            long int h = 0;
                            while(h <= i){
                                fseek(fp, h, SEEK_SET);
                                c = fgetc(fp);
                                if( (c != ' ') && (c != '\n')){
                                    if( (c_==' ') || (c_=='\n') )
                                    wordct++;
                                }
                                c_ = c;
                                h++;
                            }
                            //printf("I: %ld | H: %ld\n", i, h);
                            if(counter==place){
                                if(word==1)
                                    return wordct;
                                else
                                    return m+len2;
                            }
                            wordct = 1;
                        }
                    }
                }
            if(id==1)
                break;
            }
        }
    free(noast1);
    free(noast2);
    free(buffer1);
    free(buffer2);
    }
    else{
        for(long int i = 0; i < end; i++){
        int j = 0, id = 0;
        fseek(fp, i, SEEK_SET);
        for(j = 0; j < len; j++){
            c = fgetc(fp);
            if(c==EOF){
                i++;
                id = 1;
                break;
            }
            buffer[j] = c;
        }
        buffer[j] = '\0';
        if(id==1)
            break;
        //printf("|%s|\n", buffer);
        if(!strcmp(buffer, dtext)){
            counter++;
            int wordct = 1;
            long int h = 0;
            while(h <= i){
                fseek(fp, h, SEEK_SET);
                c = fgetc(fp);
                if( (c != ' ') && (c != '\n')){
                    if( (c_==' ') || (c_=='\n') )
                    wordct++;
                }
                c_ = c;
                h++;
            }
            //printf("I: %ld | H: %ld\n", i, h);
            if(counter==place){
                if(word==1)
                    return wordct;
                else
                    return i+len;
            }
            wordct = 1;
        }
        }
        free(buffer);
    }
    return -1;
}

long int* find_all2(FILE *fp, char* dtext, int starpos, int word)
{
    char c , c_ = '\0';
    long int *answers = (long int*)calloc(500, sizeof(long int));
    int answersct = 0;
    long int len = strlen(dtext);
    char* buffer = (char*)malloc(len);
    char* noast = (char*)calloc(200, sizeof(char));
    fseek(fp, 0L, SEEK_END);
    long int end = ftell(fp);
    if(0==starpos){
        long int ct = 0;
        while(1){
            noast[ct] = dtext[ct+1];
            if(dtext[ct+1]=='\0')
                break;
            ct++;
        }
        for(long int i = 0; i < end; i++){
            int j = 0, id = 0;
            fseek(fp, i-1, SEEK_SET);
            char before = fgetc(fp);
            fseek(fp, i, SEEK_SET);
            for(j = 0; j < len-1; j++){
                c = fgetc(fp);
                if(c==EOF){
                    i++;
                    id = 1;
                    break;
                }
                buffer[j] = c;
            }
            buffer[j] = '\0';
            //printf("buffer:|%s|\n", buffer);
            if(id==1)
                break;
            if(!strcmp(buffer, noast)){
                if( (before!= ' ') && (before!= '\n') ){
                    /*long int h = 0;
                    while(h <= i){
                        fseek(fp, h, SEEK_SET);
                        c = fgetc(fp);
                        if( (c== ' ') || (c=='\n'))
                            space = h;
                        if( (c != ' ') && (c != '\n')){
                            if( (c_==' ') || (c_=='\n') )
                               wordct++;
                        }
                        c_ = c;
                        h++;
                    }*/
                    *(answers+answersct) = i+len-1;
                    answersct++;
                    fseek(fp, i, SEEK_SET);
                    while(1){
                        c = fgetc(fp);
                        if(c==' '){
                            i = ftell(fp);
                            break;
                        }
                        if(c==EOF){
                            i++;
                            id = 1;
                            break;
                        }
                    }
                    if(id==1)
                        break;
                }
            }
        }
        free(buffer);
        free(noast);
    }
    else if(len-1==starpos){
        int i = 0, wordct = 1;
        char c_ = '\0';
        for(; i < len-1; i++) noast[i] = dtext[i];
        noast[i] = '\0';
        for(long int i = 0; i < end; i++){
            int j = 0, id = 0;
            fseek(fp, i, SEEK_SET);
            for(j = 0; j < len-1; j++){
                c = fgetc(fp);
                if(c==EOF){
                    i++;
                    id = 1;
                    break;
                }
                buffer[j] = c;
            }
            buffer[j] = '\0';
            char after = fgetc(fp);
            //printf("buffer:|%s|\n", buffer);
            if(id==1)
                break;
            if(!strcmp(buffer, noast)){
                if( (after!= ' ') && (after!= '\n') ){
                    long int text_ending = i + len, ending = 0;
                    fseek(fp, text_ending, SEEK_SET);
                    while(1){
                        c = fgetc(fp);
                        if( (c==' ') || (c=='\n')){
                            ending = ftell(fp)-1;
                            break;
                        }
                        else if(c==EOF){
                            ending = ftell(fp);
                            break;
                        }
                    }
                    long int h = 0;
                    while(h <= i){
                        fseek(fp, h, SEEK_SET);
                        c = fgetc(fp);
                        if( (c != ' ') && (c != '\n')){
                            if( (c_==' ') || (c_=='\n') )
                               wordct++;
                        }
                        c_ = c;
                        h++;
                    }
                    //printf("I: %ld | H: %ld\n", i, h);
                    if(word==1)
                        *(answers+answersct) = wordct;
                    else
                        *(answers+answersct) = ending;
                    wordct = 1;
                    answersct++;
                    fseek(fp, i, SEEK_SET);
                    while(1){
                        c = fgetc(fp);
                        if(c==' '){
                            i = ftell(fp);
                            break;
                        }
                        if(c==EOF){
                            i++;
                            id = 1;
                            break;
                        }
                    }
                    if(id==1)
                        break;
                }
            }
        }
        free(buffer);
        free(noast);
    }
    else if(starpos != -1){
        char* noast1 = (char*)calloc(200, sizeof(char)), *noast2 = (char*)calloc(200, sizeof(char));
        int i = 0;
        for(i = 0; i < starpos; i++){
            noast1[i] = dtext[i];
        }
        noast1[starpos] = '\0';
        int k = starpos+1;
        i = 0;

        while(1){
            noast2[i] = dtext[k];
            if(dtext[i]=='\0')
                break;
            k++;
            i++;
        }
        //printf("Noast1: %s\n\nNoast2: %s\n\n", noast1, noast2);
        int len1 = strlen(noast1), len2 = strlen(noast2);
        char* buffer1 = (char*)calloc(len1, sizeof(char)), *buffer2 = (char*)calloc(len2, sizeof(char));
        for(long int i = 0; i < end; i++){
            int j = 0, id = 0;
            fseek(fp, i, SEEK_SET);
            for(j = 0; j < len1; j++){
                c = fgetc(fp);
                if(c==EOF){
                    id = 1;
                    break;
                }
                buffer1[j] = c;
            }
            buffer1[j] = '\0';
            //printf("buffer1:|%s|\n", buffer1);
            if(id==1)
                break;
            if(!strcmp(buffer1, noast1)){
                long int m = ftell(fp)+1L;
                long int start = m;
                for(; m < end; m++){
                    int n = 0;
                    fseek(fp, m, SEEK_SET);
                    for(n = 0; n < len2; n++){
                        c = fgetc(fp);
                        if(c==EOF){
                            m++;
                            break;
                        }
                        buffer2[n] = c;
                    }
                buffer2[n] = '\0';
                //printf("    buffer2:|%s|\n", buffer2);
                if(id==1)
                    break;
                if(!strcmp(buffer2, noast2)){
                        fseek(fp, start, SEEK_SET);
                        int nos = 0;
                        for(long int h = start; h < m; h++){
                            c = fgetc(fp);
                            if((c==' ')||(c=='\n')){
                                nos = 1;
                                break;
                            }
                        }
                        if(nos==0){
                            int wordct = 1;
                            long int h = 0;
                            while(h <= i){
                                fseek(fp, h, SEEK_SET);
                                c = fgetc(fp);
                                if( (c != ' ') && (c != '\n')){
                                    if( (c_==' ') || (c_=='\n') )
                                    wordct++;
                                }
                                c_ = c;
                                h++;
                            }
                            //printf("I: %ld | H: %ld\n", i, h);
                            if(word==1)
                                *(answers+answersct) = wordct;
                            else
                                *(answers+answersct) = m+len2;
                            wordct = 1;
                            answersct++;
                        }
                    }
                }
            if(id==1)
                break;
            }
        }
    free(noast1);
    free(noast2);
    free(buffer1);
    free(buffer2);
    }
    else{
        for(long int i = 0; i < end; i++){
        int j = 0, id = 0;
        fseek(fp, i, SEEK_SET);
        for(j = 0; j < len; j++){
            c = fgetc(fp);
            if(c==EOF){
                i++;
                id = 1;
                break;
            }
            buffer[j] = c;
        }
        buffer[j] = '\0';
        if(id==1)
            break;
        //printf("|%s|\n", buffer);
        if(!strcmp(buffer, dtext)){
            int wordct = 1;
            long int h = 0;
            while(h <= i){
                fseek(fp, h, SEEK_SET);
                c = fgetc(fp);
                if( (c != ' ') && (c != '\n')){
                    if( (c_==' ') || (c_=='\n') )
                    wordct++;
                }
                c_ = c;
                h++;
            }
            //printf("I: %ld | H: %ld\n", i, h);
            if(word==1)
                *(answers+answersct) = wordct;
            else
                *(answers+answersct) = i+len;
            wordct = 1;
            answersct++;
        }
        }
        free(buffer);
    }
    answers[answersct] = -1;
    return answers;
}

/////////////////////////////////////////////////
// COMPARE

long int* comparing(char* address1, char* address2)
{
    long int *check = (long int*)calloc(30, sizeof(long int));
    int linect = 1, ct = 0;
    char c1, c2;
    FILE *fp1 = NULL, *fp2 = NULL;
    fp1 = fopen(address1, "r");
    fp2 = fopen(address2, "r");
    while(1){
        c1 = fgetc(fp1);
        c2 = fgetc(fp2);
        if(c2 != c1){
            //printf("%ld : %c | %ld : %c\n", ftell(fp1), c1, ftell(fp2), c2);
            *(check+ct) = linect;
            ct++;
            int id = 0;
            while(1){
                if(c2=='\n'){
                    while(1){
                        if(c1=='\n'){
                            linect++;
                            id = 1;
                            break;
                        }
                        if(c1==EOF){
                            *(check+ct) = -1;
                            *(check+ct+1) = 2;
                            *(check+ct+2) = linect;
                            return check;
                        }
                        c1 = fgetc(fp1);
                    }
                    //printf("A: %d\n", linect);
                    if(id==1) break;
                }
                else if(c1=='\n'){
                    while(1){
                        if(c2=='\n'){
                            linect++;
                            id = 1;
                            break;
                        }
                        if(c2==EOF){
                            *(check+ct) = -1;
                            *(check+ct+1) = 1;
                            *(check+ct+2) = linect;
                            return check;
                        }
                        c2 = fgetc(fp2);
                    }
                    //printf("B: %d\n", linect);
                    if(id==1) break;
                }
                else if(c1==EOF){
                    if(c2!=EOF){
                        *(check+ct) = -1;
                        *(check+ct+1) = 2;
                        *(check+ct+2) = linect+1;
                        //printf("C: %d\n", linect+1);
                        return check;
                    }
                    if(c2==EOF){
                        *(check+ct) = -1;
                        *(check+ct+1) = 0;
                        return check;
                    }
                }
                else if(c2==EOF){
                    if(c1!=EOF){
                        *(check+ct) = -1;
                        *(check+ct+1) = 1;
                        *(check+ct+2) = linect+1;
                        //printf("D: %d\n", linect+1);
                        return check;
                    }
                    if(c1==EOF){
                        *(check+ct) = -1;
                        *(check+ct+1) = 0;
                        return check;
                    }
                }
                c2 = fgetc(fp2);
                c1 = fgetc(fp1);
            }

        }
        else if(c1==EOF){
            //printf("DONE");
            *(check+ct) = -1;
            *(check+ct+1) = 0;
            return check;
        }
        else if(c1=='\n')
            linect++;
    }
}

void filelist(char* directory, int indentnum, int counter)
{
    //printf("+++++COUNTER: %d+++++\n", counter);
    if(counter>reccur){
        //printf("Not This One\n");
        return;
    }
    DIR *d;
    struct dirent *dir;
    struct stat *statbuf;
    statbuf = (struct stat*)malloc(sizeof(struct stat));
    chdir(directory);
    d = opendir(".");
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            stat(dir->d_name, statbuf);
            int type = statbuf->st_mode;
            if( (strcmp(dir->d_name, ".")) && (strcmp(dir->d_name, ".."))){
            for(int i = 0; i < indentnum; i++) printf(" ");
            printf("%s\n", dir->d_name);
                if(type==16895 || type==0){
                    //printf("New folder: %s\n", dir->d_name);
                    filelist(dir->d_name, indentnum+4, counter+1);
                }
            }
        }
        if(counter >= 2)
            chdir("..");
        closedir(d);
    }
}

char* arman_filelist(char* directory, int indentnum, int counter, char* sv)
{
    if(counter>reccur)
        return sv;
    DIR *d;
    struct dirent *dir;
    struct stat *statbuf;
    statbuf = (struct stat*)malloc(sizeof(struct stat));
    chdir(directory);
    d = opendir(".");
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            stat(dir->d_name, statbuf);
            int type = statbuf->st_mode;
            if( (strcmp(dir->d_name, ".")) && (strcmp(dir->d_name, ".."))){
            for(int i = 0; i < indentnum; i++) strcat(sv, " ");
            //printf("%s\n", dir->d_name);
            strcat(sv, dir->d_name);
            strcat(sv, "\n");
                if(type==16895)
                    arman_filelist(dir->d_name, indentnum+4, counter+1, sv);
            }
        }
        if(counter >= 2)
            chdir("..");
        closedir(d);
    }
    return sv;
}
