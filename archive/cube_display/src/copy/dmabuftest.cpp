/*
 * Copyright (C) 2011 Texas Instruments
 * Author: Rob Clark <rob.clark@linaro.org>
 * Adopted for testing VIP capture by: Nikhil Devshatwar <nikhil.nd@ti.com>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published by
 * the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#include <pthread.h>
#include "util.h"

//#include "cv_link.h"

#define NBUF 6
#define CNT  500000
#define MAX_CAP 6

struct thr_data {
	struct display *disp;
	struct v4l2 *v4l2;
	uint32_t fourcc, width, height;
};

static void
usage(char *name)
{
	MSG("Usage: %s [OPTION]...", name);
	MSG("Test of buffer passing between v4l2 camera and display.");
	MSG("");
	MSG("viddec3test options:");
	MSG("\t-h, --help: Print this help and exit.");
	MSG("\t--multi <num>: Capture from <num> different devices.");
	MSG("\t\t\tEach device name and format would be parsed in the cmdline");
	MSG("");
	disp_usage();
	v4l2_usage();
}

void *
capture_loop(void *arg)
{
	struct thr_data *data = (struct thr_data *)arg;
	struct display *disp = data->disp;
	struct v4l2 *v4l2 = data->v4l2;
	uint32_t fourcc = data->fourcc;
	uint32_t width = data->width, height = data->height;

	struct buffer **buffers, *capt, *alg, **alg_bufs;
	int ret, i;
	int *src, *dst;
	int w, h;

	buffers = disp_get_vid_buffers(disp, NBUF, fourcc, width, height);
	if (!buffers) {
		return NULL;
	}

	alg_bufs = disp_get_vid_buffers(disp, 1, fourcc, width, height);
	alg = alg_bufs[0];

	ret = v4l2_reqbufs(v4l2, buffers, NBUF);
	if (ret) {
		return NULL;
	}

	for (i = 0; i < NBUF; i++) {
		v4l2_qbuf(v4l2, buffers[i]);
	}

	ret = v4l2_streamon(v4l2);
	if (ret) {
		return NULL;
	}

	for (i = 1; i < CNT; i++) {

		capt = v4l2_dqbuf(v4l2);

src = omap_bo_map(capt->bo[0]);
dst = omap_bo_map(alg->bo[0]);

//printf("debug: %p %p\n", src, dst);
omap_bo_cpu_prep(capt->bo[0], OMAP_GEM_READ);
omap_bo_cpu_prep(alg->bo[0], OMAP_GEM_WRITE);
//printf("bufers prepared\n");

/*
for (h=0; h<720; h++)
	for(w=0;w<1280 / 2;w++)
		dst[h * 1280 / 2 + w] = src[h * 1280 / 2 + 1280 / 2 - w];


*/

printf("Calling get Image");
//getImage(dst);




//printf("Mirrrored\n");
omap_bo_cpu_fini(capt->bo[0], OMAP_GEM_READ);
omap_bo_cpu_fini(alg->bo[0], OMAP_GEM_WRITE);

ret = disp_post_vid_buffer(disp, alg,
		0, 0, width, height);

//printf("Alg buffer posted\n");
		ret = disp_post_vid_buffer(disp, capt,
			0, 0, width, height);
		if (ret) {
			ERROR("Post buffer failed");
			return NULL;
		}
		v4l2_qbuf(v4l2, capt);
	}
	v4l2_streamoff(v4l2);

	MSG("Ok!");
	return disp;
}

int
main(int argc, char **argv)
{
	struct display *disp;
	struct v4l2 *v4l2;
	pthread_t threads[MAX_CAP];
	struct thr_data tdata[MAX_CAP];
	void *result = NULL;
	int ret = 0, i, multi = 1, idx = 0;
	char c;

	MSG("Opening Display..");
	disp = disp_open(argc, argv);
	if (!disp) {
		usage(argv[0]);
		return 1;
	}

	for (i = 1; i < argc; i++) {
		if (!argv[i])
			continue;

		if (!strcmp("--multi", argv[i])) {
			argv[i++] = NULL;
			sscanf(argv[i], "%d", &multi);
			argv[i] = NULL;
			if(multi < 1 || multi > MAX_CAP) {
				usage(argv[i]);
				return 1;
			}
		}
	}

	for (i = 0; i < multi; i++) {
		MSG("Opening V4L2..");
		v4l2 = v4l2_open(argc, argv, &tdata[i].fourcc,
			&tdata[i].width, &tdata[i].height);
		if (!v4l2) {
			usage(argv[0]);
			return 1;
		}
		tdata[i].disp = disp;
		tdata[i].v4l2 = v4l2;
	}

	if (check_args(argc, argv)) {
		/* remaining args.. print usage msg */
		usage(argv[0]);
		return 0;
	}

	for (i = 0; i < multi; i++) {
		ret = pthread_create(&threads[i], NULL, capture_loop, &tdata[i]);
		if(ret) {
			MSG("Failed creating thread");
		}
	}

	for (i = 0; i < multi; i++) {
		pthread_join(threads[i], &result);
	}

	disp_close(disp);

	return ret;
}
