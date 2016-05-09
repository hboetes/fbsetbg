
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


/* This module finds the number of images in a directory and then picks a random
 * one. It saves the name of the directory if remember is set. */
int
random_wallpaper(char *wall_path, int remember)
{

#ifndef HAVE_ARC4RANDOM
	struct timeval	tv[2];
#endif
	uint		random;
	char	       *path2wallpaper;
	uint		i = 0;
	int             ret;
	int		found = FALSE;

	DIR	       *dirp;
	struct dirent  *dp;

	path2wallpaper = malloc(MAXPATHLEN);
	if (path2wallpaper == NULL)
		err(1, "out of memory");

	cleanpath(wall_path);

	/* Open the directory */
	if ((dirp = opendir(wall_path)) == NULL)
		err(1, "%s", wall_path);

	/* Count the number of image-files */
	while ((dp = readdir(dirp)) != NULL)
	{
		/* step over . and .. */
		if (dp->d_name[0] == '.')
		{
			if (dp->d_name[1] == '\0' ||
			    (dp->d_name[1] == '.' && dp->d_name[2] == '\0'))
				continue;
		}
		/* check the extension of the file */
		if (checkextension(dp->d_name) == 0)
			i++;
	}

	/* Verify at least one file has been found. */
	if (i < 1)
		errx(1, "directory %s does not contain any wallpapers",
		    wall_path);

	/* Use gettimeofday to get a quick and dirty random number. It's not
	 * very random so try to get your hands on arc4random */
#ifdef HAVE_ARC4RANDOM
	random = (uint)arc4random();
#else
	gettimeofday(&tv[0], NULL);
	random = (uint)tv[0].tv_usec;
#endif
	random %= i;
	i = 0;

	/* Reset to first file in directory structure */
	rewinddir(dirp);
	while ((dp = readdir(dirp)) != NULL)
	{
		/* step over . and .. */
		if (dp->d_name[0] == '.')
		{
			if (dp->d_name[1] == '\0' ||
			    (dp->d_name[1] == '.' && dp->d_name[2] == '\0'))
				continue;
		}

		/* if it's a picture and i equals the generated random number */
		if (checkextension(dp->d_name) == 0 && i++ == random)
		{
			ret = snprintf(path2wallpaper, MAXPATHLEN,
			    "%s/%s", wall_path, dp->d_name);
			if (ret < 0 || ret >= MAXPATHLEN)
				errx(1, "arguments out of bounds for pathname");
			if (remember == REMEMBER)
				write_lastwallpaper("random", wall_path);
			/* TODO support other options? */
			found = TRUE;
			set_wallpaper(DEFAULTARG, path2wallpaper);
			break;
		}
	}
	/* No wallpaper was found. */
	free(path2wallpaper);
	closedir(dirp);
	if (found == TRUE)
		return(TRUE);
	else
		errx(1, "no wallpaper was found in %s", wall_path);
}
