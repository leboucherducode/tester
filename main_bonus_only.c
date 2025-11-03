#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

// Helper function to free content
void del_content(void *content)
{
	free(content);
}

// Helper function for ft_lstmap
void *duplicate_content(void *content)
{
	char *str = (char *)content;
	return strdup(str);
}

// Helper function for ft_lstiter
void print_content(void *content)
{
	// Just to test iteration, we don't actually print in tests
	(void)content;
}

void test_lstnew(void)
{
	printf("\n=== ft_lstnew ===\n");
	
	char *content = strdup("Hello");
	t_list *node = ft_lstnew(content);
	
	int ok = (node != NULL && node->content == content && node->next == NULL);
	print_result("ft_lstnew creates node with correct content and NULL next", ok);
	
	free(content);
	free(node);
	
	t_list *node_null = ft_lstnew(NULL);
	ok = (node_null != NULL && node_null->content == NULL && node_null->next == NULL);
	print_result("ft_lstnew with NULL content", ok);
	free(node_null);
}

void test_lstadd_front(void)
{
	printf("\n=== ft_lstadd_front ===\n");
	
	t_list *lst = NULL;
	t_list *node1 = ft_lstnew(strdup("First"));
	t_list *node2 = ft_lstnew(strdup("Second"));
	
	ft_lstadd_front(&lst, node1);
	int ok = (lst == node1);
	print_result("ft_lstadd_front to empty list", ok);
	
	ft_lstadd_front(&lst, node2);
	ok = (lst == node2 && lst->next == node1);
	print_result("ft_lstadd_front to existing list", ok);
	
	free((char *)node1->content);
	free((char *)node2->content);
	free(node1);
	free(node2);
}

void test_lstsize(void)
{
	printf("\n=== ft_lstsize ===\n");
	
	t_list *lst = NULL;
	print_result("ft_lstsize of NULL list is 0", ft_lstsize(lst) == 0);
	
	t_list *node1 = ft_lstnew(strdup("1"));
	t_list *node2 = ft_lstnew(strdup("2"));
	t_list *node3 = ft_lstnew(strdup("3"));
	
	lst = node1;
	node1->next = node2;
	node2->next = node3;
	
	print_result("ft_lstsize of 3-element list is 3", ft_lstsize(lst) == 3);
	
	free((char *)node1->content);
	free((char *)node2->content);
	free((char *)node3->content);
	free(node1);
	free(node2);
	free(node3);
}

void test_lstlast(void)
{
	printf("\n=== ft_lstlast ===\n");
	
	t_list *lst = NULL;
	print_result("ft_lstlast of NULL list is NULL", ft_lstlast(lst) == NULL);
	
	t_list *node1 = ft_lstnew(strdup("1"));
	t_list *node2 = ft_lstnew(strdup("2"));
	t_list *node3 = ft_lstnew(strdup("3"));
	
	lst = node1;
	print_result("ft_lstlast of single element", ft_lstlast(lst) == node1);
	
	node1->next = node2;
	node2->next = node3;
	
	print_result("ft_lstlast returns last element", ft_lstlast(lst) == node3);
	
	free((char *)node1->content);
	free((char *)node2->content);
	free((char *)node3->content);
	free(node1);
	free(node2);
	free(node3);
}

void test_lstadd_back(void)
{
	printf("\n=== ft_lstadd_back ===\n");
	
	t_list *lst = NULL;
	t_list *node1 = ft_lstnew(strdup("First"));
	
	ft_lstadd_back(&lst, node1);
	int ok = (lst == node1);
	print_result("ft_lstadd_back to empty list", ok);
	
	t_list *node2 = ft_lstnew(strdup("Second"));
	ft_lstadd_back(&lst, node2);
	ok = (lst == node1 && node1->next == node2 && node2->next == NULL);
	print_result("ft_lstadd_back to existing list", ok);
	
	t_list *node3 = ft_lstnew(strdup("Third"));
	ft_lstadd_back(&lst, node3);
	ok = (node2->next == node3 && node3->next == NULL);
	print_result("ft_lstadd_back adds to end", ok);
	
	free((char *)node1->content);
	free((char *)node2->content);
	free((char *)node3->content);
	free(node1);
	free(node2);
	free(node3);
}

void test_lstdelone(void)
{
	printf("\n=== ft_lstdelone ===\n");
	
	char *content = strdup("Delete me");
	t_list *node = ft_lstnew(content);
	
	ft_lstdelone(node, del_content);
	print_result("ft_lstdelone deletes node (no crash)", 1);
}

void test_lstclear(void)
{
	printf("\n=== ft_lstclear ===\n");
	
	t_list *node1 = ft_lstnew(strdup("1"));
	t_list *node2 = ft_lstnew(strdup("2"));
	t_list *node3 = ft_lstnew(strdup("3"));
	
	node1->next = node2;
	node2->next = node3;
	
	t_list *lst = node1;
	ft_lstclear(&lst, del_content);
	
	print_result("ft_lstclear clears list and sets to NULL", lst == NULL);
	
	// Test with NULL list
	t_list *null_lst = NULL;
	ft_lstclear(&null_lst, del_content);
	print_result("ft_lstclear with NULL list (no crash)", 1);
}

void test_lstiter(void)
{
	printf("\n=== ft_lstiter ===\n");
	
	t_list *node1 = ft_lstnew(strdup("1"));
	t_list *node2 = ft_lstnew(strdup("2"));
	t_list *node3 = ft_lstnew(strdup("3"));
	
	node1->next = node2;
	node2->next = node3;
	
	ft_lstiter(node1, print_content);
	print_result("ft_lstiter iterates without crash", 1);
	
	ft_lstclear(&node1, del_content);
}

void test_lstmap(void)
{
	printf("\n=== ft_lstmap ===\n");
	
	t_list *node1 = ft_lstnew(strdup("one"));
	t_list *node2 = ft_lstnew(strdup("two"));
	t_list *node3 = ft_lstnew(strdup("three"));
	
	node1->next = node2;
	node2->next = node3;
	
	t_list *new_list = ft_lstmap(node1, duplicate_content, del_content);
	
	int ok = (new_list != NULL && 
		new_list != node1 &&
		new_list->content != node1->content &&
		strcmp((char *)new_list->content, "one") == 0);
	print_result("ft_lstmap creates new list with mapped content", ok);
	
	if (new_list)
	{
		ok = (new_list->next != NULL &&
			strcmp((char *)new_list->next->content, "two") == 0 &&
			new_list->next->next != NULL &&
			strcmp((char *)new_list->next->next->content, "three") == 0);
		print_result("ft_lstmap preserves list structure", ok);
		
		ft_lstclear(&new_list, del_content);
	}
	
	ft_lstclear(&node1, del_content);
	
	// Test with NULL list
	t_list *null_result = ft_lstmap(NULL, duplicate_content, del_content);
	print_result("ft_lstmap with NULL list returns NULL", null_result == NULL);
}

int main(void)
{
	printf("\n");
	printf("╔════════════════════════════════════════╗\n");
	printf("║     LIBFT BONUS TESTER (Lists)        ║\n");
	printf("╚════════════════════════════════════════╝\n");
	
	test_lstnew();
	test_lstadd_front();
	test_lstsize();
	test_lstlast();
	test_lstadd_back();
	test_lstdelone();
	test_lstclear();
	test_lstiter();
	test_lstmap();
	
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
