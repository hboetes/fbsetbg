
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
 * Check the filename for the evil chars ` and $ and find the absolute path to
 * the file.
 */
int
cleanpath(char *filename)
{
	char		*temppath;

 	if ((temppath = strdup(filename)) == NULL)
		errx(1, "can't allocate memory.");

	if (strlen(temppath) > MAXPATHLEN)
		errx(1, "try something shorter");

	if ((strchr(temppath, '`')) != NULL || (strchr(temppath, '$')) != NULL)
		errx(1, "Evil chars detected in %s", temppath);

	if (realpath(temppath, filename) == NULL)
		errx(1, "can't find the realpath of %s", filename);

	free(temppath);
	return (TRUE);
}
