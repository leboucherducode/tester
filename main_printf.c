#include "ft_printf.h"
#include <stdio.h>
#include <string.h>
#include <limits.h>

#define GREEN "\033[32m"
#define RED "\033[31m"
#define BLUE "\033[34m"
#define YELLOW "\033[33m"
#define RESET "\033[0m"
#define BOLD "\033[1m"

#define PASS GREEN"✓ PASS"RESET
#define FAIL RED"✗ FAIL"RESET
#define INFO BLUE"ℹ INFO"RESET

int main(void)
{
    printf(BOLD GREEN "==========================================\n");
    printf("           TESTS FT_PRINTF\n");
    printf("==========================================" RESET "\n\n");

    int ft_ret, std_ret;

    printf(BOLD BLUE "=== TEST 1: Caractères simples %%c ===" RESET "\n");
    printf("Standard: ");
    std_ret = printf("Char: %c, %c, %c\n", 'A', '5', ' ');
    printf("ft_printf: ");
    ft_ret = ft_printf("Char: %c, %c, %c\n", 'A', '5', ' ');
    printf("Return values: std=%d, ft=%d %s\n\n", std_ret, ft_ret,
           (std_ret == ft_ret) ? PASS : FAIL);

    printf(BOLD BLUE "=== TEST 2: Chaînes %%s ===" RESET "\n");
    printf("Standard: ");
    std_ret = printf("String: '%s', '%s', '%s'\n", "Hello", "", "World");
    printf("ft_printf: ");
    ft_ret = ft_printf("String: '%s', '%s', '%s'\n", "Hello", "", "World");
    printf("Return values: std=%d, ft=%d %s\n\n", std_ret, ft_ret,
           (std_ret == ft_ret) ? PASS : FAIL);

    printf(BOLD BLUE "=== TEST 3: Pointeurs %%p ===" RESET "\n");
    char *ptr = "test";
    printf("Standard: ");
    std_ret = printf("Pointer: %p, NULL: %p\n", (void *)ptr, (void *)NULL);
    printf("ft_printf: ");
    ft_ret = ft_printf("Pointer: %p, NULL: %p\n", (void *)ptr, (void *)NULL);
    printf("Return values: std=%d, ft=%d %s\n\n", std_ret, ft_ret,
           (std_ret == ft_ret) ? PASS : FAIL);

    printf(BOLD BLUE "=== TEST 4: Entiers %%d et %%i ===" RESET "\n");
    printf("Standard: ");
    std_ret = printf("Integers: %d, %i, %d, %i\n", 42, -42, 0, INT_MAX);
    printf("ft_printf: ");
    ft_ret = ft_printf("Integers: %d, %i, %d, %i\n", 42, -42, 0, INT_MAX);
    printf("Return values: std=%d, ft=%d %s\n\n", std_ret, ft_ret,
           (std_ret == ft_ret) ? PASS : FAIL);

    printf(BOLD BLUE "=== TEST 5: Unsigned %%u ===" RESET "\n");
    printf("Standard: ");
    std_ret = printf("Unsigned: %u, %u, %u\n", 42u, 0u, UINT_MAX);
    printf("ft_printf: ");
    ft_ret = ft_printf("Unsigned: %u, %u, %u\n", 42u, 0u, UINT_MAX);
    printf("Return values: std=%d, ft=%d %s\n\n", std_ret, ft_ret,
           (std_ret == ft_ret) ? PASS : FAIL);

    printf(BOLD BLUE "=== TEST 6: Hexadécimal %%x et %%X ===" RESET "\n");
    printf("Standard: ");
    std_ret = printf("Hex: %x, %X, %x, %X\n", 42, 42, 255, 255);
    printf("ft_printf: ");
    ft_ret = ft_printf("Hex: %x, %X, %x, %X\n", 42, 42, 255, 255);
    printf("Return values: std=%d, ft=%d %s\n\n", std_ret, ft_ret,
           (std_ret == ft_ret) ? PASS : FAIL);

    printf(BOLD BLUE "=== TEST 7: Pourcentage %% ===" RESET "\n");
    printf("Standard: ");
    std_ret = printf("Percent: %%d gives %d%% success\n", 100);
    printf("ft_printf: ");
    ft_ret = ft_printf("Percent: %%d gives %d%% success\n", 100);
    printf("Return values: std=%d, ft=%d %s\n\n", std_ret, ft_ret,
           (std_ret == ft_ret) ? PASS : FAIL);

    printf(BOLD BLUE "=== TEST 8: Cas limites ===" RESET "\n");
    
    // Test avec INT_MIN
    printf("INT_MIN test:\n");
    printf("Standard: ");
    std_ret = printf("%d\n", INT_MIN);
    printf("ft_printf: ");
    ft_ret = ft_printf("%d\n", INT_MIN);
    printf("Return values: std=%d, ft=%d %s\n", std_ret, ft_ret,
           (std_ret == ft_ret) ? PASS : FAIL);

    // Test avec 0
    printf("Zero in hex:\n");
    printf("Standard: ");
    std_ret = printf("%x %X\n", 0, 0);
    printf("ft_printf: ");
    ft_ret = ft_printf("%x %X\n", 0, 0);
    printf("Return values: std=%d, ft=%d %s\n", std_ret, ft_ret,
           (std_ret == ft_ret) ? PASS : FAIL);

    printf("\n" BOLD BLUE "=== TEST 9: String NULL ===" RESET "\n");
    printf("Standard: ");
    printf("NULL string: '(null)'\n");
    std_ret = 19; // Longueur attendue
    printf("ft_printf: ");
    ft_ret = ft_printf("NULL string: '%s'\n", (char *)NULL);
    printf("Return values: std=%d, ft=%d %s\n\n", std_ret, ft_ret,
           (std_ret == ft_ret) ? PASS : FAIL);

    printf(BOLD BLUE "=== TEST 10: Format complexe ===" RESET "\n");
    printf("Standard: ");
    std_ret = printf("Complex: %c%s%p%d%i%u%x%X%%\n", 
                     'A', "test", (void*)0x42, -1, 2, 3u, 0xabc, 0Xdef);
    printf("ft_printf: ");
    ft_ret = ft_printf("Complex: %c%s%p%d%i%u%x%X%%\n", 
                       'A', "test", (void*)0x42, -1, 2, 3u, 0xabc, 0Xdef);
    printf("Return values: std=%d, ft=%d %s\n\n", std_ret, ft_ret,
           (std_ret == ft_ret) ? PASS : FAIL);

    printf(BOLD BLUE "=== TEST 11: Format sans arguments ===" RESET "\n");
    printf("Standard: ");
    std_ret = printf("No args: Hello World!\n");
    printf("ft_printf: ");
    ft_ret = ft_printf("No args: Hello World!\n");
    printf("Return values: std=%d, ft=%d %s\n\n", std_ret, ft_ret,
           (std_ret == ft_ret) ? PASS : FAIL);

    printf(BOLD YELLOW "=== PERFORMANCE TEST ===" RESET "\n");
    printf("%s Appel 1000 fois ft_printf...\n", INFO);
    int i;
    for (i = 0; i < 1000; i++) {
        ft_ret = ft_printf("");
        if (ft_ret != 0) break;
    }
    printf("Performance test: %s (completed %d/1000 calls)\n", 
           (i == 1000) ? PASS : FAIL, i);

    printf("\n" BOLD GREEN "==========================================\n");
    printf("           TESTS FT_PRINTF TERMINÉS\n");
    printf("==========================================" RESET "\n");
    printf("%s Comparez visuellement les sorties ci-dessus\n", INFO);
    printf("%s Vérifiez que les valeurs de retour correspondent\n", INFO);

    return 0;
}