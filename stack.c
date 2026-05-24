// #include "stack.h"
// #include "product.h"
// #include <malloc.h>
//
// void stack_push(ProductStack** head, Product item)
// {
// 	ProductStack* new_element = (ProductStack*)malloc(sizeof(ProductStack));
// 	new_element->item = item;
// 	new_element->next = *head;
// 	*head = new_element;
// }
//
// ProductStack* stack_get(ProductStack* head, int index)
// {
// 	while (index--)
// 		head = head->next;
// 	return head;
// }
//
// void stack_pop(ProductStack** head)
// {
// 	ProductStack* prev_head = *head;
// 	*head = prev_head->next;
// 	free(prev_head);
// }
//
//
// void stack_print(ProductStack* head, Image* images)
// {
// 	while (head != NULL)
// 	{
// 		// printf("%s %d %s %d", head->item.name, head->item.cost, head->item.description, head->item.rating);
// 		print_card_short(head->item);
// 		head = head->next;
// 	}
// 	printf("\n");
// }
//
// void stack_clear(ProductStack** head)
// {
// 	while (*head != NULL)
// 		stack_pop(head);
// }