#include <locale.h>
#include <string.h>
#include "categories.h"
#include "interaction.h"
#include "io.h"
#include "product.h"
#include "stack.h"
#include "tree.h"

int main(void)
{
    char products_filename[FILENAME_MAX];
    TreeNode* products = NULL, *current_product = NULL;

    State state = MENU;
    do
    {
        clear_screen();

        State prev_state = state;
        switch (state)
        {
        case MENU:
            printf("i - Import products\n");
            printf("c - Add category\n");
            if (get_categories_count() > 0)
                printf("a - Add product\n");
            if (products != NULL)
            {
                printf("l - Product catalog\n");
                printf("e - Export products\n");
            }
            printf("x - Exit\n");

            state = ask_action(get_categories_count() > 0 ? (products != NULL ? "icalxe" : "icax") : "icx");
            break;

        case IMPORT_PRODUCTS:
            printf("Enter filename to import products (Enter for %s): ", PRODUCTS_DEFAULT_FILENAME);
            read_string_or_default(products_filename, PRODUCTS_DEFAULT_FILENAME);

            int prev_products_count = tree_get_size(products, -1);
            import_products(&products, products_filename);
            int current_products_count = tree_get_size(products, -1);

            printf(current_products_count - prev_products_count > 0 ? SET_GREEN : SET_RED);
            printf("Imported %d products, total products %d\n" RESET, current_products_count - prev_products_count, current_products_count);
            break;

        case ADD_PRODUCT:
            Product product;
            do
            {
                print_available_categories();
                product = read_new_product(tree_get_size(products, -1));
                printf("\n");
                print_product_details(product);
                printf("All data correct? ");
            } while (ask_action("yn") == 'n');
            tree_add_element(&products, product);
            printf(SET_GREEN "Product added!\n" RESET);
            break;

        case ADD_CATEGORY:
            Category category;
            do {
                printf("\n");
                category = read_new_category();
                printf("All data correct? ");
            } while (ask_action("yn") == 'n');
            add_category(category);
            printf(SET_GREEN "Category successfully added!\n" RESET);
            break;

        case EXPORT_PRODUCTS:
            printf("Enter filename to export products (Enter for %s): ", PRODUCTS_DEFAULT_FILENAME);
            read_string_or_default(products_filename, PRODUCTS_DEFAULT_FILENAME);
            export_products(products, products_filename);
            printf(SET_GREEN "Products saved to file!\n" RESET);
            break;

        case LIST_PRODUCTS:
            printf("Sorting by rating\n");
            printf("a - Ascending\n");
            printf("d - Descending\n");
            bool ascending = (ask_action("ad") == 'a');

            printf("Filter by category? ");
            int filter = -1;
            if (ask_action("yn") == 'y')
            {
                print_available_categories();
                printf("Enter category ID: ");
                filter = read_int_range(0, get_categories_count() - 1);
            }

            print_products_header();
            tree_card_print(products, ascending, filter, 0);

            printf("Press Enter to view a product, Esc to return to menu\n");
            if (wait_special_symbol(true, true) == ENTER)
            {
                printf("Enter the product index to view.\n");
                current_product = tree_find(products, read_int_range(0, tree_get_size(products, filter) - 1), filter, ascending);
                state = VIEW_PRODUCT;
            }
            else
                state = MENU;

            break;

        case VIEW_PRODUCT:
            print_product_details(current_product->item);

            printf("\nPress Enter to rate the product, Esc for product list.\n");

            if (wait_special_symbol(true, true) == ENTER)
            {
                printf("Rate the product from 1 to %d: ", MAX_RATING);
                int new_rating = read_int_range(1, MAX_RATING);

                if (new_rating != current_product->item.rating)
                {
                    Product updated_product = current_product->item;
                    tree_remove_element(&products, updated_product);
                    updated_product.rating = new_rating;
                    tree_add_element(&products, updated_product);
                }
            }

            state = LIST_PRODUCTS;
            break;
        }

        if (prev_state != MENU && prev_state != LIST_PRODUCTS)
        {
            printf("\nPress Esc to return to menu.");
            wait_special_symbol(true, false);
            state = MENU;
        }
    } while (state != 'x');

    tree_clear(&products);

    return 0;
}
