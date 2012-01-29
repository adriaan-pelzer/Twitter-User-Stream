#ifndef _INCLUDES_H_
#define _INCLUDES_H_

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>
#include <signal.h>
#include <curl/curl.h>
#include <json/json.h>
#include <oauth.h>

#include "curl.h"
#include "json.h"

#define P_EMG LOG_DAEMON|LOG_EMERG
#define P_ALT LOG_DAEMON|LOG_ALERT
#define P_CRT LOG_DAEMON|LOG_CRIT
#define P_ERR LOG_DAEMON|LOG_ERR
#define P_WRN LOG_DAEMON|LOG_WARNING
#define P_NTC LOG_DAEMON|LOG_NOTICE
#define P_INF LOG_DAEMON|LOG_INFO
#define P_DBG LOG_DAEMON|LOG_DEBUG

#endif
