#include "tree.h"
#include "utils.h"
#include <assert.h>

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

// Поск следущей вершины для поиска
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
		current = tree_get_next(*current, x);

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

 tree_find(TreeNode* node)
{
	//todo
}

int tree_get_size(TreeNode* node)
{
	if (node == NULL)
		return 0;
	return tree_get_size(node->left) + tree_get_size(node->right) + 1;
}

// Сохранение в файл в порядке прямого обхода
void tree_save_direct(TreeNode* current, FILE* file)
{
	if (current == NULL) return;
	fwrite(&current->item, sizeof(Product), 1, file);
	tree_save_direct(current->left, file);
	tree_save_direct(current->right, file);
}