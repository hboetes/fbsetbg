/*	$Id: read_lastwallpaper.c,v 1.14 2006/03/30 21:51:22 han Exp $	*/

/*
 * Copyright (c) 2004 - 2005 Han Boetes <han@mijncomputer.nl>
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


/*
 * This function reads arguments of the last remembered session for reuse for
 * fbsetbg -l
 */
int
read_lastwallpaper(char *option, char *wallpaper)
{

	char		*lstwllpprarray;
	char		*tempstring;
	char	        *display, *t1, *t2;
	FILE	        *fp;
	uint		 i;
	int              found = FALSE, ret;

	tempstring     = malloc(MAXPATHLEN);
	if (tempstring == NULL)
		err(1, "out of memory");

	lstwllpprarray = malloc(MAXPATHLEN);
	if (lstwllpprarray == NULL)
		err(1, "out of memory");

	/* Copy the pointers for freeing (because of strsep */
	t1             = tempstring;
	t2             = lstwllpprarray;

	if ((display = getenv("DISPLAY")) == NULL)
		errx(1, "the DISPLAY environment variable isn't set");

	if ((fp = fopen(lastwallpaper, "r")) == NULL)
		/* Most likely ~/.lastwallpaper doesn't exist */
		err(1, "%s", lastwallpaper);

	for (i = 0; i < MAXLLW; i++)
	{
		if (fgets(lstwllpprarray, MAXPATHLEN, fp) == NULL)
				break;

		ret = snprintf(tempstring, MAXPATHLEN, "|%s\n", display);
		if (ret < 0 || ret >= MAXPATHLEN)
		{
			if (fclose(fp) != 0)
				err(1, "%s", lastwallpaper);
			errx(1, "error while trying to read %s", lastwallpaper);
		}

		if (strstr(lstwllpprarray, tempstring))
		{
			(void)strncpy(option, strsep(&lstwllpprarray, "|"), MAXPATHLEN - 1);
			option[MAXPATHLEN - 1] = '\0';

			(void)strncpy(wallpaper, strsep(&lstwllpprarray, "|"), MAXPATHLEN - 1);
			wallpaper[MAXPATHLEN - 1] = '\0';

			found = TRUE;
			break;
		}
	}

	if (fclose(fp) != 0)
		err(1, "%s", lastwallpaper);

	free(t1);
	free(t2);

	if (found == TRUE)
		return(TRUE);
	else
		errx(1, "no wallpaper recorded for display %s", display);
}
