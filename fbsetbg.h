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

#ifndef _fbsetbg_h
#define _fbsetbg_h

/* To get alloca for Linux */
#ifdef __GNUC__
#  define _GNU_SOURCE
#endif

#include <sys/param.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

#include <ctype.h>
#include <dirent.h>
#include <err.h>
#include <errno.h>
#include <fcntl.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>



#ifdef HAVE_ARC4RANDOM_EXT
#  include <bsd/stdlib.h>
#  define HAVE_ARC4RANDOM
#endif

#ifndef HAVE_ARC4RANDOM
#  include <sys/time.h>
#endif


#define	 FIRST	   'f'
#define	 ALL	   'a'
#define	 QUIET	   'q'

#define	 TRUE	    0
#define	 FALSE	    1

#define  FORGET     1
#define  REMEMBER   0

#define	 MAXARGS  128		/* maximum args for bsetroot */
#define  MAXLLW	   20		/* maximum lines in ~/.lastwallpaper */

#define DEFAULTARG 'F'          /* Default argument if no option is given. Also
				 * used for random- and rotate-mode */


#define	 LASTWALLPAPERIN ".lastwallpaper"

char     *lastwallpaper;	/* later on defined to $HOME/.lastwallpaper */

extern void display_usage(void);

extern void display_tips(void);

extern void display_help(void);

extern int cleanpath(char *filename);

extern char * strtolower(char *input);

extern int checkextension(char *filename);

extern int read_lastwallpaper(char *option, char *wallpaper);

extern int write_lastwallpaper(char *option, char *wallpaper);

extern int find_setters(char option);

extern int set_wallpaper(char option, char *filename);

extern int bsetroot_wallpaper(int argc, char *argv[], int remember);

extern int re_bsetroot_wallpaper(char *arguments);

extern int random_wallpaper(char *wall_path, int remember);

extern int re_rotate_wallpaper(char *wallpaper);

extern int last_wallpaper(void);

#endif /* _fbsetbg_h */
