
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


/*
 * Store arguments of the last remembered session for reuse for fbsetbg -l
 */
int
write_lastwallpaper(char *option, char *wallpaper)
{

	char	       *lstwllpprarray[MAXLLW];
	FILE	       *fp;
	char	       *display, *tempstring;
	int		i = 0, j, ret, found = FALSE;

	if ((display = getenv("DISPLAY")) == NULL)
		errx (1, "the DISPLAY environment variable isn't set");

	tempstring = malloc(MAXPATHLEN);
	if (tempstring == NULL)
		err(1, "out of memory");

	/* First read ~/.lastwallpaper into an array */
	if ((fp = fopen(lastwallpaper, "r")) != NULL)
	{
		for (i = 0; i < MAXLLW; i++)
		{
			lstwllpprarray[i] = malloc(MAXPATHLEN);
			if (lstwllpprarray[i] == NULL)
				err(1, "out of memory");


			if (fgets(lstwllpprarray[i], MAXPATHLEN, fp) == NULL)
				break;
		}

		/* Add sanity */
		if (fclose(fp) != 0)
			err(1, "error");
	} else {
		/* Initiate  variable */
		lstwllpprarray[0] = malloc(MAXPATHLEN);
		if (lstwllpprarray[0] == NULL)
			err(1, "out of memory");

		lstwllpprarray[0][0] = '\0';
	}

	/* And then  write all lines back again. */
	if ((fp = fopen(lastwallpaper, "w")) == NULL)
		err(1, "%s", lastwallpaper);

	for (j = 0; j <= i; j++)
	{
		if (lstwllpprarray[j][0] != '\0' && lstwllpprarray[j][0] != '\n')
		{
			ret = snprintf(tempstring,
			    MAXPATHLEN, "|%s\n", display);
			if (ret < 0 || ret >= MAXPATHLEN)
			{
				fclose(fp);
				errx(1, "error while trying to backup %s",
				    lastwallpaper);
			}
			/* If a line matching the current DISPLAY is
			 * found overwrite it. */
			if (strstr(lstwllpprarray[j], tempstring))
			{
				fprintf(fp, "%s|%s|%s\n",
				    option, wallpaper, display);
				found = TRUE;
			}
			/* or else keep it. */
			else
				fprintf(fp, "%s", lstwllpprarray[j]);

		}
		free(lstwllpprarray[j]);
	}
	if (found == FALSE)
		fprintf(fp, "%s|%s|%s\n", option, wallpaper, display);

	if (fclose(fp) != 0)
		err(1, "error");

	free(tempstring);
	return (TRUE);
}
