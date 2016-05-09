
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

/* The main function, it parses the arguments */
int
main(int argc, char *argv[])
{

	extern char    *optarg;
	extern int	optind;

	int		ret;
	int		ch;

	if (argc == 1)
	{
		display_usage();
		return (FALSE);
	}

	while ((ch = getopt(argc, argv, "F:f:C:c:T:t:A:a:BbR:r:o:lisph")) != -1)
	{
		/* Check for a sane length */
		if (optarg != NULL && (strlen(optarg) > MAXPATHLEN))
			err(1,"try less options");

		/* informational stuff, doesn't need lastwallpaper */
		switch (ch)
		{
		case 'i':
			find_setters(FIRST);
			break;
		case 's':
			find_setters(ALL);
			break;
		case 'p':
			display_tips();
			return (TRUE);
		case 'h':
			display_help();
			return (TRUE);
		}
		/* Only now initialize lastwallpaper. */
		lastwallpaper = malloc(MAXPATHLEN);

		/* define the lastwallpaperfile */
		ret = snprintf(lastwallpaper, MAXPATHLEN,
		    "%s/%s", getenv("HOME"), LASTWALLPAPERIN);
		if (ret < 0 || ret >= MAXPATHLEN)
			errx(1,"$HOME too big");

		switch (ch)
		{
			/* basic setter functions */
			/* set_wallpaper never returns; no need to break. */
		case 'F':
			ret = set_wallpaper(ch, optarg);
			break;
		case 'f':
			ret = set_wallpaper(ch, optarg);
			break;

		case 'C':
			ret = set_wallpaper(ch, optarg);
			break;
		case 'c':
			ret = set_wallpaper(ch, optarg);
			break;

		case 'T':
			ret = set_wallpaper(ch, optarg);
			break;
		case 't':
			ret = set_wallpaper(ch, optarg);
			break;

		case 'A':
			ret = set_wallpaper(ch, optarg);
			break;
		case 'a':
			ret = set_wallpaper(ch, optarg);
			break;
			/* specials build around the previous commandset */
		case 'B':
			ret = bsetroot_wallpaper(argc, argv, FORGET);
			break;
		case 'b':
			ret = bsetroot_wallpaper(argc, argv, REMEMBER);
			break;

		case 'R':
			ret = random_wallpaper(optarg, FORGET);
			break;
		case 'r':
			ret = random_wallpaper(optarg, REMEMBER);
			break;
		case 'o':
			ret = set_wallpaper(ch, optarg);
			break;

		case 'l':
			ret = last_wallpaper();
			break;
		default:
			display_usage();
			ret = FALSE;
			break;
		}
		free(lastwallpaper);
		return (ret);
	}
	argc -= optind;
	argv += optind;
	/* Getopt didn't find any options so lets assume the argument is a
	 * wallpaper and try to set this wallpaper with the default argument */
	ret = set_wallpaper(DEFAULTARG, argv[0]);
	exit (ret);
}
