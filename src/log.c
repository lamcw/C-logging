#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>

#include "log.h"

static const char *log_color[] = {
	[L_SILENT] = "",
	[L_DEBUG] = "",
	[L_INFO] = "\x1b[34m",
	[L_WARNING] = "\x1b[31m",
	[L_ERROR] = "\x1b[31m",
	[L_CRITICAL] = "\x1b[1;31m"
};
static const char *log_verbosity_name[] = {
	[L_SILENT] = "SILENT",
	[L_DEBUG] = "DEBUG",
	[L_INFO] = "INFO",
	[L_WARNING] = "WARNING",
	[L_ERROR] = "ERROR",
	[L_CRITICAL] = "CRITICAL"
};
static FILE *log_fp;
static verbosity_t log_level;

void __log_fclose(void)
{
	fclose(log_fp);
}

void log_init(FILE *fp, verbosity_t v)
{
	log_fp = fp;
	log_level = v;

	if (atexit(__log_fclose) != 0) {
		/* register fclose for log_fp */
		perror("Cannot set exit function\n");
		exit(EXIT_FAILURE);
	}
}

static inline char *get_curr_time_str(void)
{
	time_t nowtime;
	char *buf = malloc(26 * sizeof(char));
	if (buf == NULL) {
		/* out of memory */
		return NULL;
	}
	struct tm *tm_info;

	time(&nowtime);
	tm_info = localtime(&nowtime);
	strftime(buf, 26, "%Y-%m-%d %H:%M:%S", tm_info);
	return buf;
}

static inline char *get_level_str(const verbosity_t level)
{
	const char *ansi_reset = "\x1b[0m";
	const size_t buf_len = strlen(log_color[level])
				+ strlen(log_verbosity_name[level])
				+ strlen(ansi_reset) + 1;
	char *buf = malloc(buf_len * sizeof(char));
	if (buf == NULL) {
		return NULL;
	}
	snprintf(buf, buf_len, "%s%s%s", log_color[level],
		 log_verbosity_name[level], ansi_reset);
	return buf;
}

void __log_message(const verbosity_t level, const char *file, 
		   const int line, const char *fmt, ...)
{
	/* check log level */
	if (level < log_level) {
		return;
	}
	va_list args;
	va_start(args, fmt);
	char *time_buffer = get_curr_time_str();
	char *color_buffer = get_level_str(level);

	/* print system info first, then the log message */
	fprintf(log_fp, "%s %s:%s:%d:", color_buffer, time_buffer, file, line);
	free(time_buffer);
	free(color_buffer);
	vfprintf(log_fp, fmt, args);

	va_end(args);
}
