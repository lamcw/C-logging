#include <stdio.h>
#include <unistd.h>

#include "../src/log.h"

static void test_stderr(void)
{
	log_init(stderr, L_DEBUG);
	log_message(L_CRITICAL, "Hello\n");
	log_message(L_ERROR, "test var %d %s\n", 1234, "TEST");
	log_message(L_INFO, "info only\n");
	log_message(L_SILENT, "nothing is displayed\n");
	/* log_message(L_INFO, "type mismatch %d\n", "string"); */
}

static void test_fp(void)
{
	FILE *fp = fopen("log.txt", "w");
	log_init(fp, L_DEBUG);
	log_message(L_CRITICAL, "test output to plain txt file\n");
	fclose(fp);
	/* remove("log.txt"); */
}

int main(void)
{
	test_stderr();
	test_fp();

	return 0;
}
