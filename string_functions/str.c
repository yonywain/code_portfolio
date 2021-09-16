#include <stdio.h>
#include "str.h"
	
/*calculate the length of a string*/
size_t ystrlen(const char *str)
{
	char *runner = (char*) str;

	while(*runner != '\0')
	{
		++runner;
	}
	
	return (runner-str);
}
/*compare two strings*/
int ystrcmp(const char *s1, const char *s2)
{
	while((*s1 == *s2) && *s1)
	{
		++s1;
		++s2;
	}

	return (*s1 - *s2);
}
/*copy a string*/
char *ystrcpy(char *dest, const char *src)
{
	unsigned int i = 0;	

	while(*src!='\0')
	{
		*dest = *src;
		++dest;
		++src;
		++i;
	}
	*dest = '\0';

	return (dest - i);
}
/*copy a string - limited characters*/
char *ystrncpy(char *dest, const char *src, size_t len)
{
	while(len > 0)
	{
		if(*src != '\0')
		{
			*dest = *src;
			++src;
		}
		else
		{
			*dest = '\0';
		}
		++dest;
		--len;
	}
	*dest = '\0';

	return (dest - len);
}

/*compare two strings ignoring case*/
int ystrcasecmp(const char *s1, const char *s2)
{
	while((tolower(*s1) == tolower(*s2)) && *s1)
	{
		++s1;
		++s2;
	}

	return (*s1 - *s2);
}

/*locate character in string*/
char *ystrchr(const char *src, int val)
{
	while (*src)
	{
		if (*src == (char) val)
		{
			return (char*) src;
		}
		++src;
	}

	return NULL;
}

/*duplicate a string*/
char *ystrdup(const char *s1)
{
	char *new1 = (char*) malloc(ystrlen(s1)*sizeof(char)+1);
	if(0 == new1)
	{
		return NULL;
	}

	return ystrcpy(new1, s1);
}

/*concatenate two strings*/
char *ystrcat(char *s1, const char *s2)
{
	s1 = s1+ystrlen(s1);

	return (ystrcpy(s1,s2) - ystrlen(s1));
}

/*concatenate two strings - limited characters*/
char *ystrncat(char *dest, const char *src, size_t n)
{
	dest=dest+ystrlen(dest);
	return (ystrncpy(dest,src,n)-ystrlen(dest));
}

/*locate a substring*/
char *ystrstr(const char *haystack, const char *needle)
{
	char *marker = 0;
	int counter = 0;
	int needLen = ystrlen(needle);

	while (*haystack && *needle)
	{
		if (*haystack == *needle)
		{
			marker = (char*)haystack;
			++needle;
			++counter;
		}
		++haystack;
	}
	if(counter == needLen)
	{
		return marker - needLen+1;
	}
	
	return NULL;
}

/*search a string for a set of bytes */
size_t ystrspn(const char *s, const char *accept)
{
	char *runner = (char*) s;

	while(*runner == *accept)
	{
		++runner;
		++accept;
	}
	
	return (runner - s);
}

/*search location of specific char */
int ystrcspn(const char *s, const char *accept)
{
	char *runner;
	char c;
	char *p;
	for(runner = (char*)s, c = *runner; c != 0; runner++, c = *runner)
	{
		for(p = (char*)accept; *p != 0; p++)
		{
			if(c == *p)
			{
				return runner-s;
			}
		}
	}
	
	return runner-s;
	
}

/*extract tokens from strings*/
char *ystrtok(char *str, const char *delim)
{
	

	static char *lasts;
	int ch;

	if(str == 0)
	{
		str = lasts;
	}
	do
	{
		ch = *(str+1);
		if(ch == '\0')
		{
			return 0;
		}
		
	} while(ystrchr(delim, ch));
	
	lasts = str + ystrcspn(str, delim);
	if(*lasts != 0)
	{
		*lasts++ = 0;
	}

	return str;
}