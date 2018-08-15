/*
 * Copyright 2008-2015 Arsen Chaloyan
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <apr.h>
#include <apr_poll.h>
#include <apr_strings.h>
#include "chilli.h"

static bool cmdline_process(char *cmdline)
{
	bool running = TRUE;
	char *name;
	char *last;
	name = apr_strtok(cmdline, " ", &last);


	if(strcasecmp(name,"exit") == 0 || strcmp(name,"quit") == 0) {
		running = FALSE;
	}

	else if(strcasecmp(name,"help") == 0) {
		printf("usage:\n");
		printf("- ... quit\n");
		printf("- quit, exit\n");
	}
	else {
		printf("unknown command: %s (input help for usage)\n",name);
	}
	return running;
}

bool uni_cmdline_run()
{
	bool running = TRUE;
	char cmdline[1024];
	apr_size_t i;

	/* start server */
	chilli::App::Start();

	do {
		printf(">");
		memset(&cmdline, 0, sizeof(cmdline));
		for(i = 0; i < sizeof(cmdline); i++) {
			cmdline[i] = (char) getchar();
			if(cmdline[i] == '\n') {
				cmdline[i] = '\0';
				break;
			}
		}
		if(*cmdline) {
			running = cmdline_process(cmdline);
		}
	}
	while(running != 0);

	/* shutdown server */
	chilli::App::Stop();
	return TRUE;
}
