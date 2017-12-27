#ifndef _LOG_H
#define _LOG_H

#include <stdio.h>

typedef enum verbosity {
	L_SILENT,
	L_DEBUG,
	L_INFO,
	L_WARNING,
	L_ERROR,
	L_CRITICAL
} verbosity_t;

void log_init(FILE *fp, verbosity_t v);
void __log_message(const verbosity_t level, const char *file, 
		   const int line, const char *fmt, ...)
	__attribute__((format(printf, 4, 5)));
#define log_message(verbosity, ...)	\
	__log_message(verbosity, __FILE__, __LINE__, __VA_ARGS__)
#endif
