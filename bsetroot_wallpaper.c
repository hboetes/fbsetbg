
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

/* This module forwards arguments to bsetroot and remembers them on succesfull
 * execution. */
int
bsetroot_wallpaper(int argc, char *argv[], int remember)
{
	char *arguments[MAXARGS];
	int i, pid, ret;
	char *optstring, *tempstring = ""; /* stupid compiler :-) */

	optstring = malloc(MAXPATHLEN);
	if (optstring == NULL)
		err(1, "out of memory");

	/* The arguments have to be shifted */
	for(i = 1; i < argc && i < MAXARGS; i++)
		arguments[i - 1] = argv[i];

	/* The mantra for executing something in the background. */
	pid = fork();
	if (pid == -1)
		err(1, "couldn't fork");

	if (!pid)
	{
		ret = execvp("bsetroot", arguments);
		if (ret == -1)
		{
			ret = execvp("fbsetroot", arguments);
			if (ret == -1)
				/* Not that bsetroot can actually return errors,
				 * but suppose it doesn't exist. */
				err(1, "executing your bsetroot command failed");
		}
	}

	if (pid)
		waitpid(pid, NULL, 0);

	if (remember == REMEMBER)
	{
		/* Copy the arguments to a string. */
		for(i = 1; arguments[i] != 0; i++)
		{
			if ((tempstring = strdup(optstring)) == NULL)
				err(1, "out of memory");
			ret = snprintf(optstring, MAXPATHLEN,
			    "%s %s", tempstring, arguments[i]);
			if (ret < 0 || ret >= MAXPATHLEN)
				errx(1, "too many arguments to save");
			free(tempstring);
		}
		write_lastwallpaper("bsetroot", optstring);
	}
	free(optstring);
	return (TRUE);
}
