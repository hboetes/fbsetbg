
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
 * This function has a wallpaper as an argument. It sets the _next_ wallpaper in
 * the same directory and saves the name of it.
 */

int
re_rotate_wallpaper(char *wallpaper)
{
        char           *path2wallpaper, *wall_base, *wall_path;
        DIR            *dirp;
        struct dirent  *dp;
        int             ret;
        int             found = FALSE;

        /* Suppose someone is doing something nasty with `lastwallpaper' */
        cleanpath(wallpaper);

        path2wallpaper = malloc(MAXPATHLEN);
        if (path2wallpaper == NULL)
                err(1, "out of memory");

        wall_path = malloc(MAXPATHLEN);
        if (wall_path == NULL)
                err(1, "out of memory");

        wall_base = malloc(MAXPATHLEN);
        if (wall_base == NULL)
                err(1, "out of memory");


        /* dirname ruins wallpaper, so run basename first. */
        ret = snprintf(wall_base, MAXPATHLEN, "%s", basename(wallpaper));
        if (ret < 0 || ret >= MAXPATHLEN)
                errx(1, "arguments out of bounds for wallpaperpath");

        ret = snprintf(wall_path, MAXPATHLEN, "%s",  dirname(wallpaper));
        if (ret < 0 || ret >= MAXPATHLEN)
                errx(1, "arguments out of bounds for wallpaperpath");


#ifdef DEBUG
        printf("path: %s ;name: %s\n", wall_path, wall_base);
#endif

        /* Open the directory */
        if ((dirp = opendir(wall_path)) == NULL)
                err(1, "%s: ", wall_path);

        /* First lets find the current wallpaper in this dir. */
        while ((dp = readdir(dirp)) != NULL)
        {
                /* step over . and .. */
                if (dp->d_name[0] == '.')
                {
                        if (dp->d_name[1] == '\0' ||
                            (dp->d_name[1] == '.' && dp->d_name[2] == '\0'))
                                continue;
                }
                if (strcmp (wall_base, dp->d_name) == 0)
                {
                        /* We found our wallpaper, lets step to the next one.
                         * If it happened to be the last member of list, cycle
                         * and read the first entry. */
                        found = TRUE;
                        if ((dp = readdir(dirp)) == NULL)
                        {
                                rewinddir(dirp);
                                dp = readdir(dirp);
                        }
                }
                /* Now that we found our wallpaper the _next_ one with a valid
                 * extension will be set. */
                if (found == TRUE && checkextension(dp->d_name) == 0)
                {
                        ret = snprintf(path2wallpaper, MAXPATHLEN, "%s/%s",
                                       wall_path, dp->d_name);
                        if (ret < 0 || ret >= MAXPATHLEN)
                                errx(1, "arguments out of bounds"
                                     " for wallpaperpath");
                        set_wallpaper('o', path2wallpaper);
                        break;
                }

#ifdef DEBUG
                printf("looking for:%s ;current: %s\n", wall_base, dp->d_name);
#endif

        }
        closedir(dirp);

        free(path2wallpaper);
        free(wall_path);
        free(wall_base);

        if (found == TRUE)
                return(TRUE);
        else
                errx(1, "no wallpaper was found");
}
