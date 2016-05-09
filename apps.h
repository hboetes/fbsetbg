/*
 * Wallpapersetter wrapper for common purposes.
 *
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
 *
 */

#ifndef _apps_h
#define _apps_h

static char	standardok[] =
    "is a nice wallpapersetter. You won't have any problems.\n";

static char	standardrant[] =
    "sets the `wrong' wallpaper. Transparency for fluxbox\n"
    "and apps like aterm and xchat won't work right with it.\n"
    "Consider installing feh, wmsetbg (from windowmaker) or\n"
    "Esetroot (from Eterm) and I'll use them instead.\n";


/*
 * This struct contains all the settings for the wallpaper-setters.
 */
struct app
{
	char	       *name;
	char	       *full;
	char	       *aspect;
	char	       *tile;
	char	       *center;
	char	       *debug;
};


/*
 * Wallpapersetters here should be ordered in order of preference, the most
 * prefered on top. Terminate with { NULL }.
 */

static struct app apps[] =
{
	{
		/* name	  */ "Esetroot",
		/* full	  */ "-scale",
		/* tile	  */ "-fit",
		/* aspect */ "",
		/* center */ "-c",
		/* debug  */ standardok
	},
	{
		/* name	  */ "feh",
		/* full	  */ "--bg-scale",
		/* tile	  */ "--bg-tile",
		/* aspect */ "--bg-scale",
		/* center */ "--bg-center",
		/* debug  */ standardok
	},
	{
		/* name	  */ "xsri",
		/* full	  */ "--center-x --center-y --scale-width 100 --scale-height 100",
		/* tile	  */ "--tile",
		/* center */ "--center-x --center-y --color black",
		/* aspect */ "--center-x --center-y --scale-width 100 "
		"--scale-height 100 --keep-aspect --color black",
		/* debug  */ standardok
	},
	{
		/* name	  */ "wmsetbg",
		/* full	  */ "-s -S",
		/* tile	  */ "-t",
		/* center */ "-b black -e",
		/* aspect */ "-b black -a",
		/* debug  */ standardok
	},
	{
		/* name	  */ "chbg",
		/* full	  */ "-once -mode maximize",
		/* tile	  */ "-once -mode tile",
		/* center */ "-once -mode center",
		/* aspect */ "-once -mode smart -max_grow 100 -max_size 100",
		/* debug  */ "chbg supports all features but it doesn't report errors. "
		"I reported this bug to the chbg developers."
	},
	{
		/* name	  */ "display",
		/* full	  */ "`xwininfo -root 2> /dev/null|grep geom` -window root",
		/* tile	  */ "-window root",
		/* center */ "-backdrop -window root",
		/* aspect */ "`xwininfo -root 2> /dev/null|grep geom` -window root",
		/* debug  */ standardrant
	},
	{
		/* name	  */ "xsetbg",
		/* full	  */ "-fullscreen -border black",
		/* tile	  */ "-border black",
		/* center */ "-center -border black",
		/* aspect */ "-fullscreen -border black",
		/* debug  */ standardrant
	},
	{
		/* name	  */ "xli",
		/* full	  */ "-fullscreen -onroot -quiet -border black",
		/* tile	  */ "-onroot -quiet -border black",
		/* center */ "-center -onroot -quiet -border black",
		/* aspect */ "-fullscreen -onroot -quiet -border black",
		/* debug  */ standardrant
	},
	{
		/* name	  */ "qiv",
		/* full	  */ "--root_s",
		/* tile	  */ "--root_t",
		/* center */ "--root",
		/* aspect */ "-m --root",
		/* debug  */ standardrant
	},
	{
		/* name	  */ "xv",
		/* full	  */ "-max -smooth -root -quit",
		/* tile	  */ "-root -quit",
		/* center */ "-rmode 5 -root -quit",
		/* aspect */ "-maxpect -smooth -root -quit",
		/* debug  */ standardrant
	},
	/* Terminate. NULL's will do, we only have to test .name for
	 * NULLness. */
	{ NULL, NULL, NULL, NULL, NULL, NULL }
};

#endif /* _apps_h */
