
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


/* This function get the arguments as provided by read_lastwallpaper, IE a
 * string, it converts this into an array and feed the output to execvp */
int
re_bsetroot_wallpaper(char *arguments)
{
	char **ap, *options[MAXARGS];

	/* execvp uses argv[0] as the command. But it has to be initialized, or
	 * else execvp runs into a null string. */
	options[0] = "blah";

	/* Now read the arguments into array. */
	for (ap = &options[1]; ap <= &options[MAXARGS] &&
		 (*ap = strsep(&arguments, " ")) != NULL;)
	{
		if (**ap != '\0')
			ap++;
	}
	*ap = NULL;

	/* bsetroot doesn't return errors so what the hell. */
	execvp("bsetroot", options);
	exit(0);
}
