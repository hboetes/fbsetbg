
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
#include "apps.h"


/*
 * This module sends the wallpaper-setting command to the system, if it involves
 * a wallpaper (jpg, png etc.)
 */
int
set_wallpaper(char option, char *filename)
{

	int		setter, ret = 0;
	char		*command;

	command = malloc(MAXPATHLEN);
	if (command == NULL)
		err(1, "out of memory");

	if (access(filename, R_OK) != 0)
		err(1, "%s", filename);

	setter = find_setters(QUIET);

	cleanpath(filename);

	switch (option)
	{
	case 'f':
		write_lastwallpaper("full", filename);
		/* fallthrough */
	case 'F':
		ret = snprintf(command, MAXPATHLEN, "%s %s \"%s\"",
		    apps[setter].name, apps[setter].full, filename);
		break;

	case 'c':
		write_lastwallpaper("center", filename);
		/* fallthrough */
	case 'C':
		ret = snprintf(command, MAXPATHLEN, "%s %s \"%s\"",
		    apps[setter].name, apps[setter].center, filename);
		break;

	case 'a':
		write_lastwallpaper("aspect", filename);
		/* fallthrough */
	case 'A':
		ret = snprintf(command, MAXPATHLEN, "%s %s \"%s\"",
		    apps[setter].name, apps[setter].aspect, filename);
		break;

	case 't':
		write_lastwallpaper("tile", filename);
		/* fallthrough */
	case 'T':
		ret = snprintf(command, MAXPATHLEN, "%s %s \"%s\"",
		    apps[setter].name, apps[setter].tile, filename);
		break;

	case 'o':
		write_lastwallpaper("rotate", filename);
		ret = snprintf(command, MAXPATHLEN, "%s %s \"%s\"",
		    apps[setter].name, apps[setter].full, filename);
		break;
	}

	if (ret < 0 || ret >= MAXPATHLEN)
		errx(1, "command to be executed too long");

	/* XXX system() ... Hard to avoid without dropping support for some
	 * older setters. */
	ret = system(command);
/* 	exit(ret); */
	free(command);
	return (ret);
}
