
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


void
display_tips(void)
{
	extern char *__progname;
	printf(

		"Common tips to use with %s:\n\n"

		    " 1) To replace all occurrences of bsetbg with %s in a file\n"
		    "	 use this command:\n\n"

		    "	   perl -pi -e 's,([^f]|^)bsetbg,%s,' filename\n\n"

		    " 2) If you want the style to set the wallpaper and you want %s to\n"
		    "	 remember the previous wallpaper put this in your ~/.fluxbox/init\n\n"

		    "	   session.screen0.rootCommand:	   %s -l\n\n"

		    " 3) Use %s -i to find out what wallpapersetter will be\n"
		    "	 used and what %s thinks about it.\n\n"

		    ,__progname, __progname, __progname, __progname
		    ,__progname, __progname, __progname);

	return;
}
