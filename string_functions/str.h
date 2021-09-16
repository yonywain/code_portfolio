#include <string.h>
#include <ctype.h> /*for ystrcasecmp*/
#include <stdlib.h> /*for ystrdup*/

// function declarations
size_t ystrlen(const char *str);

int ystrcmp(const char *s1,const char *s2);

char *ystrcpy(char *dest, const char *src);

char *ystrncpy(char *, const char *, size_t);

int ystrcasecmp(const char *s1, const char *s2);

char *ystrchr(const char *src, int val);

char *ystrdup(const char *s1);

char *ystrcat(char *, const char *);

char *ystrncat(char *, const char *, size_t);

char *ystrstr(const char *, const char *);

size_t ystrspn(const char *__s, const char *__accept);

int ystrcspn(const char *__s, const char *__accept);

char *ystrtok(char *, const char *);


