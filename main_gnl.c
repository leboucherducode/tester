#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define GREEN "\033[32m"
#define RED "\033[31m"
#define BLUE "\033[34m"
#define YELLOW "\033[33m"
#define RESET "\033[0m"
#define BOLD "\033[1m"

#define PASS GREEN"✓ PASS"RESET
#define FAIL RED"✗ FAIL"RESET
#define INFO BLUE"ℹ INFO"RESET

void create_test_file(const char *filename, const char *content)
{
    int fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd >= 0) {
        write(fd, content, strlen(content));
        close(fd);
    }
}

int main(void)
{
    printf(BOLD GREEN "==========================================\n");
    printf("        TESTS GET_NEXT_LINE\n");
    printf("==========================================" RESET "\n\n");

    // Créer des fichiers de test
    create_test_file("test1.txt", "Line 1\nLine 2\nLine 3\n");
    create_test_file("test2.txt", "Single line without newline");
    create_test_file("test3.txt", "");
    create_test_file("test4.txt", "\n\n\n");
    create_test_file("test5.txt", "Very long line that should test buffer handling and memory allocation properly\nShort line\n");

    printf(BOLD BLUE "=== TEST 1: Fichier normal avec newlines ===" RESET "\n");
    int fd1 = open("test1.txt", O_RDONLY);
    if (fd1 >= 0) {
        char *line;
        int line_count = 0;
        while ((line = get_next_line(fd1)) != NULL) {
            line_count++;
            printf("Line %d: \"%s\" %s\n", line_count, line, 
                   (strlen(line) > 0) ? PASS : INFO);
            free(line);
        }
        printf("Total lines read: %d %s\n", line_count, 
               (line_count == 3) ? PASS : FAIL);
        close(fd1);
    } else {
        printf("Cannot open test1.txt: %s\n", FAIL);
    }

    printf("\n" BOLD BLUE "=== TEST 2: Ligne sans newline final ===" RESET "\n");
    int fd2 = open("test2.txt", O_RDONLY);
    if (fd2 >= 0) {
        char *line = get_next_line(fd2);
        printf("Line: \"%s\" %s\n", line ? line : "NULL", 
               (line && strcmp(line, "Single line without newline") == 0) ? PASS : FAIL);
        if (line) free(line);
        
        char *line2 = get_next_line(fd2);
        printf("Second call: %s %s\n", line2 ? line2 : "NULL", 
               !line2 ? PASS : FAIL);
        if (line2) free(line2);
        close(fd2);
    }

    printf("\n" BOLD BLUE "=== TEST 3: Fichier vide ===" RESET "\n");
    int fd3 = open("test3.txt", O_RDONLY);
    if (fd3 >= 0) {
        char *line = get_next_line(fd3);
        printf("Empty file result: %s %s\n", line ? line : "NULL", 
               !line ? PASS : FAIL);
        if (line) free(line);
        close(fd3);
    }

    printf("\n" BOLD BLUE "=== TEST 4: Fichier avec newlines seulement ===" RESET "\n");
    int fd4 = open("test4.txt", O_RDONLY);
    if (fd4 >= 0) {
        int empty_lines = 0;
        char *line;
        while ((line = get_next_line(fd4)) != NULL) {
            empty_lines++;
            printf("Empty line %d: \"%s\" %s\n", empty_lines, line,
                   (strlen(line) == 0) ? PASS : INFO);
            free(line);
        }
        close(fd4);
    }

    printf("\n" BOLD BLUE "=== TEST 5: Ligne très longue ===" RESET "\n");
    int fd5 = open("test5.txt", O_RDONLY);
    if (fd5 >= 0) {
        char *line1 = get_next_line(fd5);
        printf("Long line: %s (length: %zu)\n", 
               (line1 && strlen(line1) > 50) ? PASS : FAIL,
               line1 ? strlen(line1) : 0);
        if (line1) {
            printf("   Content: \"%.50s...\"\n", line1);
            free(line1);
        }
        
        char *line2 = get_next_line(fd5);
        printf("Short line: \"%s\" %s\n", line2 ? line2 : "NULL",
               (line2 && strcmp(line2, "Short line") == 0) ? PASS : FAIL);
        if (line2) free(line2);
        close(fd5);
    }

    printf("\n" BOLD BLUE "=== TEST 6: Descripteur invalide ===" RESET "\n");
    char *invalid_line = get_next_line(-1);
    printf("Invalid fd (-1): %s %s\n", invalid_line ? invalid_line : "NULL",
           !invalid_line ? PASS : FAIL);
    if (invalid_line) free(invalid_line);

    printf("\n" BOLD BLUE "=== TEST 7: Multiples fichiers simultanés ===" RESET "\n");
    int fdA = open("test1.txt", O_RDONLY);
    int fdB = open("test2.txt", O_RDONLY);
    
    if (fdA >= 0 && fdB >= 0) {
        char *lineA1 = get_next_line(fdA);
        char *lineB1 = get_next_line(fdB);
        char *lineA2 = get_next_line(fdA);
        
        printf("File A line 1: \"%s\" %s\n", lineA1 ? lineA1 : "NULL",
               (lineA1 && strstr(lineA1, "Line 1")) ? PASS : FAIL);
        printf("File B line 1: \"%s\" %s\n", lineB1 ? lineB1 : "NULL",
               (lineB1 && strstr(lineB1, "Single line")) ? PASS : FAIL);
        printf("File A line 2: \"%s\" %s\n", lineA2 ? lineA2 : "NULL",
               (lineA2 && strstr(lineA2, "Line 2")) ? PASS : FAIL);
        
        if (lineA1) free(lineA1);
        if (lineB1) free(lineB1);
        if (lineA2) free(lineA2);
        
        close(fdA);
        close(fdB);
    }

    printf("\n" BOLD BLUE "=== TEST 8: Lecture stdin (simulation) ===" RESET "\n");
    printf("%s Test stdin skippé (nécessite input utilisateur)\n", INFO);

    // Nettoyer les fichiers de test
    printf("\n" BOLD YELLOW "=== NETTOYAGE ===" RESET "\n");
    unlink("test1.txt");
    unlink("test2.txt");
    unlink("test3.txt");
    unlink("test4.txt");
    unlink("test5.txt");
    printf("%s Fichiers de test supprimés\n", INFO);

    printf("\n" BOLD GREEN "==========================================\n");
    printf("         TESTS GET_NEXT_LINE TERMINÉS\n");
    printf("==========================================" RESET "\n");
    printf("%s Vérifiez les résultats ci-dessus\n", INFO);
    printf("%s Testez aussi avec différentes valeurs de BUFFER_SIZE\n", INFO);

    return 0;
}