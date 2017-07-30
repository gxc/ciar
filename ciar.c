/*
 * Copyright 2017 Guo, Xingchun <guoxingchun@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <arpa/inet.h>
#include <assert.h>

#define COUNTRY_CODE_LEN 2

static void save_rslt(FILE * fp, uint32_t start_ip, int32_t prefix);
static void cvt_ip_range(FILE * outfp, uint32_t start_ip, uint32_t end_ip);
static FILE *open_file(const char *path, const char *mode);

/* output an IP range like 1.0.8.0/21 */
static void save_rslt(FILE * fp, uint32_t start_ip, int32_t prefix)
{
	struct in_addr addr;

	assert(prefix > 0 && prefix <= 32);
	addr.s_addr = ntohl(start_ip);
	fprintf(fp, "%s/%d\n", inet_ntoa(addr), prefix);
}

/* convert an integer IP range to ASCII blocks */
static void cvt_ip_range(FILE * outfp, uint32_t ip_from, uint32_t ip_to)
{
	int32_t cnt;

	assert(ip_to >= ip_from);
	cnt = ip_to - ip_from + 1;
	for (int32_t i = 0; i < 32; ++i) {
		if (cnt & (0x01 << i)) {
			save_rslt(outfp, ip_from, 32 - i);
			ip_from += (0x01 << i);
		}
	}
}

static FILE *open_file(const char *path, const char *mode)
{
	FILE *stream;
	extern char *program_invocation_short_name;

	errno = 0;
	stream = fopen(path, mode);
	if (stream == NULL) {
		fprintf(stderr, "\
%s: Could not open file %s; %s\n",
program_invocation_short_name, path, strerror(errno));
		exit(EXIT_FAILURE);
	} else {
		return stream;
	}
}

int32_t main(int32_t argc, char *argv[])
{
	if (argc < 3 || argc > 4) {
		fprintf(stderr, "\
Usage:\n\
    %s csv_file country_code [output_file]\n\
", argv[0]);
		exit(EXIT_FAILURE);
	}

	FILE *src;
	FILE *dst;
	char reqcc[COUNTRY_CODE_LEN + 1];
	char cc[COUNTRY_CODE_LEN + 1];
	uint32_t ip_from;
	uint32_t ip_to;

	if (strlen(argv[2]) != COUNTRY_CODE_LEN) {
		puts("Country Code Error");
		exit(EXIT_FAILURE);
	}
	reqcc[0] = toupper(argv[2][0]);
	reqcc[1] = toupper(argv[2][1]);
	reqcc[2] = '\0';
	cc[2] = '\0';

	src = open_file(argv[1], "r");
	if (argc == 3)
		dst = stdout;
	else
		dst = open_file(argv[3], "w");

	while (fscanf(src, "\"%u\",\"%u\",\"%2s\"", &ip_from, &ip_to, cc) == 3) {
		if (strncmp(cc, reqcc, COUNTRY_CODE_LEN) == 0)
			cvt_ip_range(dst, ip_from, ip_to);
		while (fgetc(src) != '\n') ;
	}

	fclose(src);
	fclose(dst);
	return 0;
}
