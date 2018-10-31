#include "../watcher/watcher.h"
#include <unistd.h>
#include <locale.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
	int h = 512, w = 512;

	watcher_open(h,w);

	for(int r = 0; r <  h; r++)
	{
		for(int c = 0; c < w; c++)
		{
			watcher_set_color((double)r/(double)h, (double)c/(double)w, (double)r/(double)h);
			watcher_paint_pixel(r, c);
		}
	}

	sleep(5);

	watcher_close();

	return 0;
}
