/*	$Id: last_wallpaper.c,v 1.9 2006/03/30 21:51:22 han Exp $	*/

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


/* This function knows what to do with the contents of the lastwallpaper file */
int
last_wallpaper(void)
{

	char	       *option, *options;
	int             ret;

	option =  malloc(MAXPATHLEN);
	if (option == NULL)
		err(1, "out of memory");
	options = malloc(MAXPATHLEN);
	if (options == NULL)
		err(1, "out of memory");

	read_lastwallpaper(option, options);

	if (strcmp(option, "full") == 0)
		ret = set_wallpaper('F', options);
	else if (strcmp(option, "aspect") == 0)
		ret = set_wallpaper('A', options);
	else if (strcmp(option, "tile") == 0)
		ret = set_wallpaper('T', options);
	else if (strcmp(option, "center") == 0)
		ret = set_wallpaper('C', options);
	else if (strcmp(option, "bsetroot") == 0)
		ret = re_bsetroot_wallpaper(options);
	else if (strcmp(option, "random") == 0)
		ret = random_wallpaper(options, FALSE);
	else if (strcmp(option, "rotate") == 0)
		ret = re_rotate_wallpaper(options);
	else
		/* We should only get here if someone has messed
		 * with the lastwallpaper file. */
		errx(1,
		    "something went wrong while reading %s. Try removing it",
		    lastwallpaper);

	free(option);
	free(options);

	return (ret);
}
