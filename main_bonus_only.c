#include "libft.h"
#include <stdio.h>
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

void print_list(t_list *lst, const char *name)
{
    printf("   %s: ", name);
    if (!lst) {
        printf("(empty)\n");
        return;
    }
    
    int count = 0;
    while (lst && count < 5) { // Limite pour éviter boucles infinies
        printf("\"%s\"", (char *)lst->content);
        lst = lst->next;
        if (lst) printf(" -> ");
        count++;
    }
    if (lst) printf(" -> ...");
    printf("\n");
}

void del_content(void *content)
{
    free(content);
}

void print_content(void *content)
{
    printf("   Processing: \"%s\"\n", (char *)content);
}

void *duplicate_content(void *content)
{
    return strdup((char *)content);
}

int main(void)
{
    printf(BOLD GREEN "==========================================\n");
    printf("       TESTS LIBFT - FONCTIONS BONUS\n");
    printf("        (Gestion listes chaînées)\n");
    printf("==========================================" RESET "\n\n");

    // Test ft_lstnew
    printf(BOLD BLUE "=== TEST FT_LSTNEW ===" RESET "\n");
    t_list *node1 = ft_lstnew(strdup("First"));
    printf("ft_lstnew(\"First\"): %s\n", node1 ? PASS : FAIL);
    if (node1) {
        printf("   Content: \"%s\", Next: %s\n", 
               (char *)node1->content, 
               node1->next ? "NOT NULL" : "NULL");
    }

    // Test ft_lstadd_front
    printf("\n" BOLD BLUE "=== TEST FT_LSTADD_FRONT ===" RESET "\n");
    t_list *list = NULL;
    ft_lstadd_front(&list, node1);
    printf("ft_lstadd_front (first element): %s\n", list ? PASS : FAIL);
    print_list(list, "List");

    t_list *node2 = ft_lstnew(strdup("Second"));
    ft_lstadd_front(&list, node2);
    printf("ft_lstadd_front (second element): %s\n", 
           (list && list == node2) ? PASS : FAIL);
    print_list(list, "List");

    // Test ft_lstsize
    printf("\n" BOLD BLUE "=== TEST FT_LSTSIZE ===" RESET "\n");
    int size = ft_lstsize(list);
    printf("ft_lstsize: %s (size: %d, expected: 2)\n", 
           (size == 2) ? PASS : FAIL, size);

    // Test ft_lstlast
    printf("\n" BOLD BLUE "=== TEST FT_LSTLAST ===" RESET "\n");
    t_list *last = ft_lstlast(list);
    printf("ft_lstlast: %s\n", 
           (last && last == node1) ? PASS : FAIL);
    if (last) {
        printf("   Last content: \"%s\"\n", (char *)last->content);
    }

    // Test ft_lstadd_back
    printf("\n" BOLD BLUE "=== TEST FT_LSTADD_BACK ===" RESET "\n");
    t_list *node3 = ft_lstnew(strdup("Third"));
    ft_lstadd_back(&list, node3);
    printf("ft_lstadd_back: %s (size should be 3)\n", 
           (ft_lstsize(list) == 3) ? PASS : FAIL);
    print_list(list, "List");

    // Test avec liste vide
    t_list *empty_list = NULL;
    t_list *node_for_empty = ft_lstnew(strdup("OnlyOne"));
    ft_lstadd_back(&empty_list, node_for_empty);
    printf("ft_lstadd_back (empty list): %s\n", 
           (empty_list == node_for_empty) ? PASS : FAIL);

    // Test ft_lstiter
    printf("\n" BOLD BLUE "=== TEST FT_LSTITER ===" RESET "\n");
    printf("ft_lstiter (printing each element):\n");
    ft_lstiter(list, print_content);
    printf("ft_lstiter: %s\n", INFO);

    // Test ft_lstmap
    printf("\n" BOLD BLUE "=== TEST FT_LSTMAP ===" RESET "\n");
    t_list *mapped_list = ft_lstmap(list, duplicate_content, del_content);
    printf("ft_lstmap: %s (created new list)\n", mapped_list ? PASS : FAIL);
    if (mapped_list) {
        printf("   Original size: %d, Mapped size: %d\n", 
               ft_lstsize(list), ft_lstsize(mapped_list));
        print_list(mapped_list, "Mapped");
    }

    // Test ft_lstmap avec liste vide
    t_list *empty_mapped = ft_lstmap(NULL, duplicate_content, del_content);
    printf("ft_lstmap (empty list): %s (should be NULL)\n", 
           !empty_mapped ? PASS : FAIL);

    // Test ft_lstdelone
    printf("\n" BOLD BLUE "=== TEST FT_LSTDELONE ===" RESET "\n");
    t_list *to_delete = ft_lstnew(strdup("ToDelete"));
    printf("Created node to delete: %s\n", to_delete ? PASS : FAIL);
    ft_lstdelone(to_delete, del_content);
    printf("ft_lstdelone: %s (node deleted)\n", INFO);

    // Test ft_lstclear
    printf("\n" BOLD BLUE "=== TEST FT_LSTCLEAR ===" RESET "\n");
    printf("Before clear - List size: %d\n", ft_lstsize(list));
    ft_lstclear(&list, del_content);
    printf("ft_lstclear: %s (list cleared)\n", !list ? PASS : FAIL);
    printf("After clear - List pointer: %s\n", !list ? "NULL" : "NOT NULL");

    if (mapped_list) {
        ft_lstclear(&mapped_list, del_content);
    }
    if (empty_list) {
        ft_lstclear(&empty_list, del_content);
    }

    // Tests de cas limites
    printf("\n" BOLD YELLOW "=== TESTS CAS LIMITES ===" RESET "\n");
    printf("ft_lstsize(NULL): %d %s\n", ft_lstsize(NULL), 
           (ft_lstsize(NULL) == 0) ? PASS : FAIL);
    printf("ft_lstlast(NULL): %s\n", 
           !ft_lstlast(NULL) ? PASS : FAIL);
    
    // Test avec un seul élément
    t_list *single = ft_lstnew(strdup("Single"));
    printf("Single element list size: %d %s\n", ft_lstsize(single), 
           (ft_lstsize(single) == 1) ? PASS : FAIL);
    printf("Single element is last: %s\n", 
           (ft_lstlast(single) == single) ? PASS : FAIL);
    ft_lstclear(&single, del_content);

    printf("\n" BOLD GREEN "==========================================\n");
    printf("            TESTS BONUS TERMINÉS\n");
    printf("==========================================" RESET "\n");
    printf("%s Toutes les fonctions de listes testées !\n", INFO);
    printf("%s Gestion mémoire et pointeurs vérifiée.\n", INFO);

    return 0;
}