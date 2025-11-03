#include "libft.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define GREEN "\033[32m"
#define RED "\033[31m"
#define RESET "\033[0m"

static int tests_passed = 0;
static int tests_failed = 0;

void print_result(const char *test_name, int passed)
{
	if (passed)
	{
		tests_passed++;
		printf("%s✓ PASS%s %s\n", GREEN, RESET, test_name);
	}
	else
	{
		tests_failed++;
		printf("%s✗ FAIL%s %s\n", RED, RESET, test_name);
	}
}

// Helper function for ft_strmapi
char to_upper_map(unsigned int i, char c)
{
	(void)i;
	if (c >= 'a' && c <= 'z')
		return c - 32;
	return c;
}

// Helper function for ft_striteri
void to_upper_iter(unsigned int i, char *c)
{
	(void)i;
	if (*c >= 'a' && *c <= 'z')
		*c = *c - 32;
}

void test_part1_ctype(void)
{
	printf("\n=== PART 1: Character Type Functions ===\n");
	
	print_result("ft_isalpha('a')", ft_isalpha('a') != 0);
	print_result("ft_isalpha('Z')", ft_isalpha('Z') != 0);
	print_result("ft_isalpha('5')", ft_isalpha('5') == 0);
	
	print_result("ft_isdigit('5')", ft_isdigit('5') != 0);
	print_result("ft_isdigit('a')", ft_isdigit('a') == 0);
	
	print_result("ft_isalnum('a')", ft_isalnum('a') != 0);
	print_result("ft_isalnum('5')", ft_isalnum('5') != 0);
	print_result("ft_isalnum('!')", ft_isalnum('!') == 0);
	
	print_result("ft_isascii(65)", ft_isascii(65) != 0);
	print_result("ft_isascii(128)", ft_isascii(128) == 0);
	
	print_result("ft_isprint('a')", ft_isprint('a') != 0);
	print_result("ft_isprint(31)", ft_isprint(31) == 0);
	
	print_result("ft_toupper('a')", ft_toupper('a') == 'A');
	print_result("ft_tolower('Z')", ft_tolower('Z') == 'z');
}

void test_part1_string(void)
{
	printf("\n=== PART 1: String Functions ===\n");
	
	print_result("ft_strlen(\"Hello\")", ft_strlen("Hello") == 5);
	print_result("ft_strlen(\"\")", ft_strlen("") == 0);
	
	print_result("ft_strchr(\"Hello\", 'e')", 
		ft_strchr("Hello", 'e') == strchr("Hello", 'e'));
	print_result("ft_strchr(\"Hello\", 'z')", 
		ft_strchr("Hello", 'z') == NULL);
	
	print_result("ft_strrchr(\"Hello\", 'l')", 
		ft_strrchr("Hello", 'l') == strrchr("Hello", 'l'));
	
	print_result("ft_strncmp(\"Hello\", \"Hello\", 5)", 
		ft_strncmp("Hello", "Hello", 5) == 0);
	print_result("ft_strncmp(\"Hello\", \"World\", 5)", 
		ft_strncmp("Hello", "World", 5) < 0);
	
	char *result = ft_strnstr("Hello World", "World", 11);
	print_result("ft_strnstr(\"Hello World\", \"World\", 11)", 
		result != NULL && strcmp(result, "World") == 0);
	
	char dst1[20] = "Hello";
	size_t r1 = ft_strlcpy(dst1, "World", 20);
	print_result("ft_strlcpy", r1 == 5 && strcmp(dst1, "World") == 0);
	
	char dst2[20] = "Hello ";
	size_t r2 = ft_strlcat(dst2, "World", 20);
	print_result("ft_strlcat", r2 == 11 && strcmp(dst2, "Hello World") == 0);
}

void test_part1_memory(void)
{
	printf("\n=== PART 1: Memory Functions ===\n");
	
	char buf1[10];
	char buf2[10];
	ft_memset(buf1, 'A', 5);
	memset(buf2, 'A', 5);
	print_result("ft_memset", memcmp(buf1, buf2, 5) == 0);
	
	char buf3[10] = "test";
	ft_bzero(buf3, 4);
	print_result("ft_bzero", buf3[0] == 0 && buf3[1] == 0);
	
	char src[] = "copy";
	char dest1[10];
	char dest2[10];
	ft_memcpy(dest1, src, 5);
	memcpy(dest2, src, 5);
	print_result("ft_memcpy", memcmp(dest1, dest2, 5) == 0);
	
	char overlap[20] = "123456789";
	ft_memmove(overlap + 2, overlap, 5);
	print_result("ft_memmove", overlap[2] == '1' && overlap[3] == '2');
	
	char *found = (char *)ft_memchr("Hello", 'l', 5);
	print_result("ft_memchr", found != NULL && *found == 'l');
	
	print_result("ft_memcmp(\"abc\", \"abc\", 3)", 
		ft_memcmp("abc", "abc", 3) == 0);
}

void test_part1_conversion(void)
{
	printf("\n=== PART 1: Conversion Functions ===\n");
	
	print_result("ft_atoi(\"42\")", ft_atoi("42") == 42);
	print_result("ft_atoi(\"-42\")", ft_atoi("-42") == -42);
	print_result("ft_atoi(\"   123\")", ft_atoi("   123") == 123);
}

void test_part1_alloc(void)
{
	printf("\n=== PART 1: Allocation Functions ===\n");
	
	int *arr = (int *)ft_calloc(5, sizeof(int));
	int ok = (arr != NULL && arr[0] == 0 && arr[4] == 0);
	print_result("ft_calloc", ok);
	free(arr);
	
	char *dup = ft_strdup("duplicate");
	ok = (dup != NULL && strcmp(dup, "duplicate") == 0);
	print_result("ft_strdup", ok);
	free(dup);
}

void test_part2_substr_join_trim(void)
{
	printf("\n=== PART 2: String Manipulation ===\n");
	
	char *sub = ft_substr("Hello World", 6, 5);
	int ok = (sub != NULL && strcmp(sub, "World") == 0);
	print_result("ft_substr", ok);
	free(sub);
	
	char *join = ft_strjoin("Hello ", "World");
	ok = (join != NULL && strcmp(join, "Hello World") == 0);
	print_result("ft_strjoin", ok);
	free(join);
	
	char *trim = ft_strtrim("  Hello  ", " ");
	ok = (trim != NULL && strcmp(trim, "Hello") == 0);
	print_result("ft_strtrim", ok);
	free(trim);
}

void test_part2_split(void)
{
	printf("\n=== PART 2: ft_split ===\n");
	
	char **split = ft_split("one,two,three", ',');
	int ok = (split != NULL && 
		strcmp(split[0], "one") == 0 &&
		strcmp(split[1], "two") == 0 &&
		strcmp(split[2], "three") == 0 &&
		split[3] == NULL);
	print_result("ft_split", ok);
	
	if (split)
	{
		for (int i = 0; split[i]; i++)
			free(split[i]);
		free(split);
	}
}

void test_part2_itoa(void)
{
	printf("\n=== PART 2: ft_itoa ===\n");
	
	char *s1 = ft_itoa(42);
	int ok1 = (s1 != NULL && strcmp(s1, "42") == 0);
	print_result("ft_itoa(42)", ok1);
	free(s1);
	
	char *s2 = ft_itoa(-42);
	int ok2 = (s2 != NULL && strcmp(s2, "-42") == 0);
	print_result("ft_itoa(-42)", ok2);
	free(s2);
	
	char *s3 = ft_itoa(0);
	int ok3 = (s3 != NULL && strcmp(s3, "0") == 0);
	print_result("ft_itoa(0)", ok3);
	free(s3);
}

void test_part2_map_iter(void)
{
	printf("\n=== PART 2: ft_strmapi & ft_striteri ===\n");
	
	char *mapped = ft_strmapi("hello", to_upper_map);
	int ok = (mapped != NULL && strcmp(mapped, "HELLO") == 0);
	print_result("ft_strmapi", ok);
	free(mapped);
	
	char str[] = "world";
	ft_striteri(str, to_upper_iter);
	print_result("ft_striteri", strcmp(str, "WORLD") == 0);
}

void test_part2_output(void)
{
	printf("\n=== PART 2: Output Functions ===\n");
	
	int fd = open("test_output.tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		print_result("open test file", 0);
		return;
	}
	
	ft_putchar_fd('A', fd);
	ft_putstr_fd("BC", fd);
	ft_putendl_fd("D", fd);
	ft_putnbr_fd(42, fd);
	close(fd);
	
	fd = open("test_output.tmp", O_RDONLY);
	char buffer[100];
	ssize_t bytes = read(fd, buffer, 99);
	buffer[bytes] = '\0';
	close(fd);
	unlink("test_output.tmp");
	
	int ok = (strstr(buffer, "ABCD") != NULL && strstr(buffer, "42") != NULL);
	print_result("ft_putchar_fd / ft_putstr_fd / ft_putendl_fd / ft_putnbr_fd", ok);
}

int main(void)
{
	printf("\n");
	printf("╔════════════════════════════════════════╗\n");
	printf("║     LIBFT COMPREHENSIVE TESTER        ║\n");
	printf("╚════════════════════════════════════════╝\n");
	
	test_part1_ctype();
	test_part1_string();
	test_part1_memory();
	test_part1_conversion();
	test_part1_alloc();
	test_part2_substr_join_trim();
	test_part2_split();
	test_part2_itoa();
	test_part2_map_iter();
	test_part2_output();
	
	printf("\n");
	printf("╔════════════════════════════════════════╗\n");
	printf("║            TEST SUMMARY                ║\n");
	printf("╠════════════════════════════════════════╣\n");
	printf("║  %sPassed: %2d%s                           ║\n", GREEN, tests_passed, RESET);
	printf("║  %sFailed: %2d%s                           ║\n", RED, tests_failed, RESET);
	printf("╚════════════════════════════════════════╝\n");
	printf("\n");
	
	return (tests_failed == 0) ? 0 : 1;
}
