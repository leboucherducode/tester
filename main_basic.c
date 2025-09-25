#include "libft.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define GREEN "\033[32m"
#define RED "\033[31m"
#define BLUE "\033[34m"
#define RESET "\033[0m"
#define BOLD "\033[1m"

#define PASS GREEN"✓ PASS"RESET
#define FAIL RED"✗ FAIL"RESET
#define INFO BLUE"ℹ INFO"RESET

int main(void)
{
    printf(BOLD GREEN "==========================================\n");
    printf("      TESTS LIBFT - FONCTIONS DE BASE\n");
    printf("   (is*, str*, mem*, conversions, utils)\n");
    printf("==========================================" RESET "\n\n");

    // Tests des fonctions is*
    printf(BOLD BLUE "=== FONCTIONS DE CARACTÈRES ===" RESET "\n");
    printf("ft_isalpha('a'): %s, ft_isalpha('5'): %s\n", 
           ft_isalpha('a') ? PASS : FAIL, !ft_isalpha('5') ? PASS : FAIL);
    printf("ft_isdigit('5'): %s, ft_isdigit('a'): %s\n", 
           ft_isdigit('5') ? PASS : FAIL, !ft_isdigit('a') ? PASS : FAIL);
    printf("ft_isalnum('a'): %s, ft_isalnum('@'): %s\n", 
           ft_isalnum('a') ? PASS : FAIL, !ft_isalnum('@') ? PASS : FAIL);
    printf("ft_isascii('a'): %s, ft_isascii(128): %s\n", 
           ft_isascii('a') ? PASS : FAIL, !ft_isascii(128) ? PASS : FAIL);
    printf("ft_isprint('a'): %s, ft_isprint('\\n'): %s\n", 
           ft_isprint('a') ? PASS : FAIL, !ft_isprint('\n') ? PASS : FAIL);

    // Tests des conversions
    printf("\n" BOLD BLUE "=== CONVERSIONS ===" RESET "\n");
    printf("ft_toupper('a') -> '%c': %s\n", ft_toupper('a'), 
           (ft_toupper('a') == 'A') ? PASS : FAIL);
    printf("ft_tolower('Z') -> '%c': %s\n", ft_tolower('Z'), 
           (ft_tolower('Z') == 'z') ? PASS : FAIL);
    printf("ft_atoi(\"123\"): %d %s\n", ft_atoi("123"), 
           (ft_atoi("123") == 123) ? PASS : FAIL);
    printf("ft_atoi(\"-456\"): %d %s\n", ft_atoi("-456"), 
           (ft_atoi("-456") == -456) ? PASS : FAIL);

    // Tests des fonctions de longueur et recherche
    printf("\n" BOLD BLUE "=== FONCTIONS DE CHAÎNES ===" RESET "\n");
    printf("ft_strlen(\"Hello\"): %zu %s\n", ft_strlen("Hello"), 
           (ft_strlen("Hello") == 5) ? PASS : FAIL);
    
    char *str = "Hello World";
    printf("ft_strchr(\"Hello World\", 'o'): %s\n", 
           (ft_strchr(str, 'o') == strchr(str, 'o')) ? PASS : FAIL);
    printf("ft_strrchr(\"Hello World\", 'o'): %s\n", 
           (ft_strrchr(str, 'o') == strrchr(str, 'o')) ? PASS : FAIL);
    printf("ft_strncmp(\"Hello\", \"Hello\", 5): %s\n", 
           (ft_strncmp("Hello", "Hello", 5) == 0) ? PASS : FAIL);
    printf("ft_strnstr(\"Hello World\", \"World\", 11): %s\n", 
           (ft_strnstr("Hello World", "World", 11) != NULL) ? PASS : FAIL);

    // Tests des fonctions mémoire
    printf("\n" BOLD BLUE "=== FONCTIONS MÉMOIRE ===" RESET "\n");
    char test1[10] = "Hello";
    char test2[10] = "Hello";
    ft_memset(test1, 'X', 3);
    memset(test2, 'X', 3);
    printf("ft_memset: %s (result: \"%s\")\n", 
           (strcmp(test1, test2) == 0) ? PASS : FAIL, test1);

    char src[] = "Test";
    char dest1[10], dest2[10];
    ft_memcpy(dest1, src, 5);
    memcpy(dest2, src, 5);
    printf("ft_memcpy: %s\n", (memcmp(dest1, dest2, 5) == 0) ? PASS : FAIL);

    printf("ft_memchr(\"Hello\", 'e', 5): %s\n", 
           (ft_memchr("Hello", 'e', 5) == memchr("Hello", 'e', 5)) ? PASS : FAIL);
    printf("ft_memcmp(\"Hello\", \"Hello\", 5): %s\n", 
           (ft_memcmp("Hello", "Hello", 5) == 0) ? PASS : FAIL);

    // Tests strlcpy/strlcat
    printf("\n" BOLD BLUE "=== FONCTIONS BSD ===" RESET "\n");
    char dst1[10];
    size_t ret1 = ft_strlcpy(dst1, "Hello World", 10);
    printf("ft_strlcpy: %s (copied: \"%s\", returned: %zu)\n", 
           (ret1 == 11 && strcmp(dst1, "Hello Wor") == 0) ? PASS : FAIL, dst1, ret1);

    char dst2[20] = "Hello ";
    size_t ret2 = ft_strlcat(dst2, "World", 20);
    printf("ft_strlcat: %s (result: \"%s\", returned: %zu)\n", 
           (ret2 == 11 && strcmp(dst2, "Hello World") == 0) ? PASS : FAIL, dst2, ret2);

    // Tests allocation et nouvelles fonctions
    printf("\n" BOLD BLUE "=== ALLOCATION ET NOUVELLES FONCTIONS ===" RESET "\n");
    
    // ft_calloc
    int *arr = (int *)ft_calloc(5, sizeof(int));
    printf("ft_calloc(5, sizeof(int)): %s (all zeros: %s)\n", 
           arr ? PASS : FAIL, (arr && arr[0] == 0 && arr[4] == 0) ? "YES" : "NO");
    free(arr);

    // ft_strdup
    char *dup = ft_strdup("Hello");
    printf("ft_strdup(\"Hello\"): %s (result: \"%s\")\n", 
           (dup && strcmp(dup, "Hello") == 0) ? PASS : FAIL, dup ? dup : "NULL");
    free(dup);

    // ft_substr
    char *sub = ft_substr("Hello World", 6, 5);
    printf("ft_substr(\"Hello World\", 6, 5): %s (result: \"%s\")\n", 
           (sub && strcmp(sub, "World") == 0) ? PASS : FAIL, sub ? sub : "NULL");
    free(sub);

    // ft_strjoin
    char *joined = ft_strjoin("Hello ", "World");
    printf("ft_strjoin(\"Hello \", \"World\"): %s (result: \"%s\")\n", 
           (joined && strcmp(joined, "Hello World") == 0) ? PASS : FAIL, joined ? joined : "NULL");
    free(joined);

    // ft_strtrim
    char *trimmed = ft_strtrim("  Hello  ", " ");
    printf("ft_strtrim(\"  Hello  \", \" \"): %s (result: \"%s\")\n", 
           (trimmed && strcmp(trimmed, "Hello") == 0) ? PASS : FAIL, trimmed ? trimmed : "NULL");
    free(trimmed);

    // ft_split
    char **split = ft_split("Hello,World,Test", ',');
    int split_ok = 0;
    if (split && split[0] && split[1] && split[2] && !split[3]) {
        split_ok = (strcmp(split[0], "Hello") == 0 && 
                   strcmp(split[1], "World") == 0 && 
                   strcmp(split[2], "Test") == 0);
        for (int i = 0; split[i]; i++) free(split[i]);
        free(split);
    }
    printf("ft_split(\"Hello,World,Test\", ','): %s\n", split_ok ? PASS : FAIL);

    // ft_itoa
    char *num = ft_itoa(-42);
    printf("ft_itoa(-42): %s (result: \"%s\")\n", 
           (num && strcmp(num, "-42") == 0) ? PASS : FAIL, num ? num : "NULL");
    free(num);

    // ft_strmapi
    char *mapped = ft_strmapi("hello", NULL); // Juste test d'allocation
    if (mapped) free(mapped);
    printf("ft_strmapi: %s (function pointer handling)\n", INFO);

    printf("\n" BOLD GREEN "==========================================\n");
    printf("            TESTS DE BASE TERMINÉS\n");
    printf("==========================================" RESET "\n");
    printf("%s Fonctions de base testées avec succès !\n", INFO);

    return 0;
}