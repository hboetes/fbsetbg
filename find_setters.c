
/*
 * Copyright (c) 2004 - 2016 Han Boetes <hboetes@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "fbsetbg.h"
#include "apps.h"

/*
 * Try to find usefull wallpapersetters. It has three options; show the first
 * one found, show all. Or just find it and return the answer.
 */
int
find_setters(char option)
{

	char	       *path, *path_element, *p;
	int		i, found_something = FALSE;
	struct stat	sbuf;

	char		*filename;

	filename = malloc(MAXPATHLEN);
	if (filename == NULL)
		err(1, "out of memory");

	if ((p = getenv("PATH")) == NULL)
		err(1, "can't get $PATH from environment");

	if ((path = strdup(p)) == NULL)
		errx(1, "can't allocate memory.");
	/* Now that we're done with p as a pointer to your PATH, use it to point
	 * to the start of path to free() the right memoryspace */
	p = path;
	while ((path_element = strsep(&path, ":")) != NULL)
	{
		for (i = 0; apps[i].name != NULL; i++)
		{
			(void) snprintf(filename, MAXPATHLEN, "%s/%s",
			    path_element, apps[i].name);

			if ((stat(filename, &sbuf) == 0) &&
			    S_ISREG(sbuf.st_mode) &&
			    access(filename, X_OK) == 0)
			{
				switch (option)
				{
				case FIRST:
					printf("I found %s:\n", apps[i].name);
					printf("%s %s\n",
					    apps[i].name, apps[i].debug);
					free(p);
					free(filename);
					exit(0);
				case ALL:
					printf("I found %s:\n", apps[i].name);
					printf("%s %s\n",
					    apps[i].name, apps[i].debug);
					found_something = TRUE;
					break;
				case QUIET:
					free(p);
					free(filename);
					return (i);
				}
			}
		}
	}
	free(p);
	free(filename);
	if (found_something == FALSE)
		errx(1, "I didn't find any wallpapersetters\n"
		    "Read all about choosing the right setter here:\n"
		    "  http://homepage.boetes.org/software/fbsetbg/fbsetbg.html");
	exit (0);
}
