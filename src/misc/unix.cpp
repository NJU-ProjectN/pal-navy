/* -*- mode: c; tab-width: 4; c-basic-offset: 4; c-file-style: "linux" -*- */
//
// Copyright (c) 2009-2011, Wei Mingzhi <whistler_wmz@users.sf.net>.
// Copyright (c) 2011-2020, SDLPAL development team.
// All rights reserved.
//
// This file is part of SDLPAL.
//
// SDLPAL is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
// unix/unix.cpp: GUI for Unix-like & Linux systems.
//       @Author: Lou Yihua <louyihua@21cn.com>.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "global.h"
#include "util.h"
#include "palcfg.h"

#include <syslog.h>


BOOL
UTIL_GetScreenSize(
   DWORD *pdwScreenWidth,
   DWORD *pdwScreenHeight
)
{
   return pdwScreenWidth && pdwScreenHeight && *pdwScreenWidth && *pdwScreenHeight;
}

BOOL
UTIL_IsAbsolutePath(
   LPCSTR lpszFileName
)
{
   return lpszFileName && *lpszFileName == '/';
}

INT
UTIL_Platform_Init(
   int argc,
   char* argv[]
)
{
	openlog("sdlpal", LOG_PERROR | LOG_PID, LOG_USER);
	UTIL_LogAddOutputCallback([](LOGLEVEL level, const char* str, const char*)->void {
		const static int priorities[] = {
			LOG_DEBUG,
			LOG_DEBUG,
			LOG_INFO,
			LOG_WARNING,
			LOG_ERR,
			LOG_EMERG
		};
		syslog(priorities[level], "%s", str);
	}, PAL_DEFAULT_LOGLEVEL);

   gConfig.fLaunchSetting = FALSE;
   return 0;
}

VOID
UTIL_Platform_Quit(
   VOID
)
{
	closelog();
}