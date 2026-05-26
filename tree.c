#include "tree.h"
#include "utils.h"
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>

// Создать узел
TreeNode* tree_create_node(Product x)
{
	TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
	node->item = x;
	node->left = NULL;
	node->right = NULL;
	return node;
}

// Получение количества детей узла
int childs_count(TreeNode* node)
{
	if (node == NULL)
		return 0;

	return (int)(node->left != NULL) + (int)(node->right != NULL);
}

// Узнать глубину дерева
int tree_get_depth(TreeNode* node)
{
	if (node == NULL)
		return 0;

	return max(tree_get_depth(node->left), tree_get_depth(node->right)) + 1;
}

// Поиск следующей вершины для поиска
TreeNode** tree_get_next(TreeNode* node, Product x)
{
	return (x.rating <= node->item.rating) ? (&node->left) : (&node->right);
}

// Найти наименьший узел в поддереве
TreeNode** tree_find_smallest(TreeNode** node)
{
	assert((*node) != NULL);

	while ((*node)->left != NULL)
		node = &(*node)->left;

	return node;
}

// Добавить элемент в дерево
void tree_add_element(TreeNode** current, Product x)
{
	while ((*current) != NULL)
	{
		if (x.id == (*current)->item.id)
			return;
		current = tree_get_next(*current, x);
	}

	(*current) = tree_create_node(x);
}

// Удалить элемент из дерева
bool tree_remove_element(TreeNode** current, Product x)
{
	while ((*current) != NULL && (*current)->item.id != x.id) // Поиск элемента равного x
		current = tree_get_next(*current, x);

	if ((*current) == NULL)
		return false;

	TreeNode* to_remove = (*current);

	if (childs_count(to_remove) == 2) // Если у вершины 2 детей
	{
		// Поиск наименьшего элемента в правом поддереве (первый больший)
		TreeNode** smallest_right = tree_find_smallest(&to_remove->right);
		TreeNode* instead_of_removed = *smallest_right;

		// Вставляем первый больший вместо удалённого
		(*smallest_right) = instead_of_removed->right;

		instead_of_removed->left = to_remove->left;
		instead_of_removed->right = to_remove->right;

		(*current) = instead_of_removed;
	}
	else // Если у вершины 0 и 1 ребёнок
		(*current) = (to_remove->left != NULL ? to_remove->left : to_remove->right);

	free(to_remove);

	return true;
}

// Очистить дерево
void tree_clear(TreeNode** node)
{
	if ((*node) == NULL)
		return;

	tree_clear(&((*node)->left));
	tree_clear(&((*node)->right));

	free(*node);
	(*node) = NULL;
}

// Поиск товара в дереве по индексу
TreeNode* tree_find(TreeNode* node, int index, int category_filter, bool ascending)
{
	if (node == NULL)
		return NULL;

	TreeNode* first = (ascending ? node->right : node->left);
	TreeNode* second = (ascending ? node->left : node->right);

	int first_size = tree_get_size(first, category_filter);
	bool this_node_correct = (category_filter == -1 || node->item.cs.category_id == category_filter);

	if (this_node_correct && index == first_size)
		return node;

	if (index < first_size)
		return tree_find(first, index, category_filter, ascending);

	return tree_find(second, index - first_size - this_node_correct, category_filter, ascending);
}

// Получение количества элементов в дереве (с учетом фильтра)
int tree_get_size(TreeNode* node, int category_filter)
{
	if (node == NULL)
		return 0;

	bool this_node_correct = (category_filter == -1 || node->item.cs.category_id == category_filter);
	return tree_get_size(node->left, category_filter) + tree_get_size(node->right, category_filter) + this_node_correct;
}

// Сохранение дерева в файл (прямой обход)
void tree_save_direct(TreeNode* current, FILE* file)
{
	if (current == NULL) return;
	fwrite(&current->item, sizeof(Product), 1, file);
	tree_save_direct(current->left, file);
	tree_save_direct(current->right, file);
}

// Вывод товаров (симметричный обход)
void tree_card_print(TreeNode* node, bool ascending, int category_filter, int index_offset)
{
	if (node == NULL)
		return;

	TreeNode* first = (ascending ? node->right : node->left);
	TreeNode* second = (ascending ? node->left : node->right);

	int current_index = index_offset + tree_get_size(first, category_filter);

	tree_card_print(first, ascending, category_filter, index_offset);
	if (category_filter == -1 || node->item.cs.category_id == category_filter)
		print_product_row(node->item, current_index);
	tree_card_print(second, ascending, category_filter, current_index + 1);
}
