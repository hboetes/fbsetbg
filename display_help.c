
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


void
display_help(void)
{
	display_usage();
	printf(
		"Options:\n\n"

		    "	 -f  Set fullscreen wallpaper.\n"
		    "	 -c  Set centered wallpaper.\n"
		    "	 -t  Set tiled wallpaper.\n"
		    "	 -a  Set maximized wallpaper, preserving aspect.\n"
		    "	     (if your bgsetter doesn't support this option\n"
		    "	       fall back to fullscreen)\n"
		    /*
		     * TODO " -u Use specified wallpapersetter, use no argument
		     * to forget.\n");
		     */
		    "	 -b  Forward the options to bsetroot.\n"
		    "	 -r  Set random wallpaper from a directory.\n"
		    "	 -o  Set first wallpaper to be rotated. (Use -l to rotate)\n\n"

		    "	 -F,-C,-T,-A,-B,-R  Same as uncapsed but without remembering.\n\n");

	printf(
		"	 -h  Display this help.\n\n"

		    "	 -l  Repeat previous command.\n\n"

		    "	 -i  Information about selected wallpapersetter.\n"
		    "	 -s  Information about all wallpapersetters on this system.\n"
		    "	 -p  Tips.\n\n"

		    "Files:\n\n"

		    "	 ~/.lastwallpaper     In this file the wallpaper you set\n"
		    "			      will be stored,"
		    " for the -l option:\n\n");
	printf(
		"Environment variables:\n\n"
		    "	 DISPLAY     The display you want to set the"
		    " wallpaper on. For example:\n\n"

		    "		       DISPLAY=:0.0 fbsetbg -l\n\n");

	exit(0);
}
