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

#include <apr_signal.h>
#include <apr_thread_proc.h>
#include "chilli.h"
#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>

static bool daemon_running;

static void sigterm_handler(int signo)
{
	daemon_running = FALSE;
}

bool uni_daemon_run(bool detach)
{
	daemon_running = TRUE;

	if(detach == TRUE) {
		apr_proc_detach(APR_PROC_DETACH_DAEMONIZE);
	}

	apr_signal(SIGTERM, sigterm_handler);
	apr_signal(SIGINT, sigterm_handler);
#ifdef SIGTSTP
	apr_signal(SIGTSTP, sigterm_handler);
#endif
#ifdef SIGQUIT
	apr_signal(SIGQUIT, sigterm_handler);
#endif
#ifdef SIGTERM
	apr_signal(SIGTERM, sigterm_handler);
#endif

	/* start server */
	chilli::App::Start();
	while(daemon_running) apr_sleep(1000000);

	/* shutdown server */
	chilli::App::Stop();
	return TRUE;
}
