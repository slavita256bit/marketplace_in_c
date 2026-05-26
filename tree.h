#pragma once
#include <malloc.h>
#include "product.h"
#include "image.h"

typedef struct TreeNode TreeNode;
struct TreeNode
{
	Product item;
	TreeNode *left, *right;
};

TreeNode* tree_create_node(Product x);                      // Создать узел

int childs_count(TreeNode* node);                           // Получение количества детей узла
int tree_get_depth(TreeNode* node);                         // Узнать глубину дерева

TreeNode** tree_get_next(TreeNode* node, Product x);        // Поск следущей вершины для поиска
TreeNode** tree_find_smallest(TreeNode** node);             // Найти наименьший узел в поддереве

void tree_add_element(TreeNode** current, Product x);       // Добавить элемент в дерево
bool tree_remove_element(TreeNode** current, Product x);    // Удалить элемент из дерева
void tree_clear(TreeNode** node);                           // Очистить дерево

TreeNode* tree_find(TreeNode* node, int index);

int tree_get_size(TreeNode* node);
void tree_save_direct(TreeNode* current, FILE* file);
void tree_card_print(TreeNode* node, Image* images, bool ascending);