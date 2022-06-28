# graph

Делаю по статье с [Хабра](https://habr.com/ru/post/596925/)
void encript() {
    char path[300];
    if (scanf("%s", path) != 1) {
        printf("n/iugiughouh");
        return;
    }
    DIR *dir;
    struct dirent *ent;
    dir = opendir(path);
    if (!dir)
        puts("lidhenwn");
    while ((ent=readdir(dir))) {
//        printf("%s\n", ent->d_name);
//        printf("%c    %c\n", ent->d_name[strlen(ent->d_name) - 1], ent->d_name[strlen(ent->d_name) - 2]);
        if (ent->d_name[strlen(ent->d_name) - 1] == 'c' && ent->d_name[strlen(ent->d_name) - 2] == '.') {
            char str[300];
            strcpy(str, path);
            strcat(str, ent->d_name);
            puts(str);
            FILE* f = fopen(str, "r+");
            shift(f, -10);
            fclose(f);
            
        }
    }
    closedir(dir);
}
void shift(FILE* f, int n) {
    fseeko(f, 0, SEEK_SET);
    int chr;
    while ((chr = getc(f)) != EOF) {
        fseeko(f, -1, SEEK_CUR);
        putc(chr + n, f);
    }
}
