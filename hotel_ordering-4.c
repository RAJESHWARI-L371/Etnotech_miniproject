#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Menu
{
    int id;
    char name[50];
    float price;
    char cuisine[30];
    int prepTime;
};

struct Order
{
    int orderID;
    int roomNo;
    int itemID;
    char itemName[50];
    int quantity;
    float totalPrice;
    char status[20];
};

struct Menu menu[10] = {
    {1, "Pizza",   250, "Italian",  20},
    {2, "Burger",  120, "FastFood", 10},
    {3, "Biryani", 180, "Indian",   25},
    {4, "Pasta",   200, "Italian",  15},
    {5, "Noodles", 150, "Chinese",  12}
};

int menuSize = 5;
int orderCounter = 1001;

struct Order orders[100];
int orderCount = 0;

void displayMenu()
{
    int i;
    printf("\n========= HOTEL MENU =========\n");
    printf("ID\tName\t\tPrice\tCuisine\t\tPrepTime\n");
    for (i = 0; i < menuSize; i++)
    {
        printf("%d\t%-12s\t%.2f\t%-10s\t%d mins\n",
               menu[i].id,
               menu[i].name,
               menu[i].price,
               menu[i].cuisine,
               menu[i].prepTime);
    }
}

void placeOrder()
{
    struct Order o;
    int itemID, qty, i, found = 0;
    int roomNo;
    char more;

    printf("\nEnter Room Number (1-100): ");
    scanf("%d", &roomNo);

    if (roomNo < 1 || roomNo > 100)
    {
        printf("Invalid Room Number!\n");
        return;
    }

    do
    {
        displayMenu();

        printf("\nEnter Item ID: ");
        scanf("%d", &itemID);
        printf("Enter Quantity: ");
        scanf("%d", &qty);

        found = 0;
        for (i = 0; i < menuSize; i++)
        {
            if (menu[i].id == itemID)
            {
                found = 1;
                o.orderID = orderCounter;
                o.roomNo = roomNo;
                o.itemID = itemID;
                strcpy(o.itemName, menu[i].name);
                o.quantity = qty;
                o.totalPrice = menu[i].price * qty;
                strcpy(o.status, "Received");

                orders[orderCount++] = o;

                printf("\nItem '%s' added to order!\n", menu[i].name);
                break;
            }
        }

        if (found == 0)
        {
            printf("Invalid Item ID!\n");
        }

        printf("\nAdd another item to this order? (y/n): ");
        scanf(" %c", &more);

    } while (more == 'y' || more == 'Y');

    orderCounter++;
    printf("\nOrder Placed Successfully! Order ID: %d\n", orderCounter - 1);
}

void displayOrders()
{
    int i;
    if (orderCount == 0)
    {
        printf("\nNo Orders Found!\n");
        return;
    }

    printf("\n========= ORDER DETAILS =========\n");
    for (i = 0; i < orderCount; i++)
    {
        printf("\nOrder ID : %d", orders[i].orderID);
        printf("\nRoom No  : %d", orders[i].roomNo);
        printf("\nItem     : %s", orders[i].itemName);
        printf("\nQuantity : %d", orders[i].quantity);
        printf("\nBill     : %.2f", orders[i].totalPrice);
        printf("\nStatus   : %s\n", orders[i].status);
    }
}

void addItems()
{
    struct Order o;
    int orderID, qty, itemID, i, found = 0, orderFound = 0;
    int roomNo = 0;

    printf("\nEnter Existing Order ID: ");
    scanf("%d", &orderID);

    for (i = 0; i < orderCount; i++)
    {
        if (orders[i].orderID == orderID)
        {
            orderFound = 1;
            roomNo = orders[i].roomNo;
            break;
        }
    }

    if (orderFound == 0)
    {
        printf("Order ID Not Found!\n");
        return;
    }

    displayMenu();

    printf("\nEnter New Item ID: ");
    scanf("%d", &itemID);
    printf("Enter Quantity: ");
    scanf("%d", &qty);

    for (i = 0; i < menuSize; i++)
    {
        if (menu[i].id == itemID)
        {
            found = 1;
            o.orderID = orderID;
            o.roomNo = roomNo;
            o.itemID = itemID;
            strcpy(o.itemName, menu[i].name);
            o.quantity = qty;
            o.totalPrice = menu[i].price * qty;
            strcpy(o.status, "Received");

            orders[orderCount++] = o;
            printf("\nItem Added Successfully!\n");
            break;
        }
    }

    if (found == 0)
    {
        printf("Invalid Item ID!\n");
    }
}

void cancelItem()
{
    int orderID, itemID, found = 0, i;

    printf("\nEnter Order ID: ");
    scanf("%d", &orderID);
    printf("Enter Item ID to Cancel: ");
    scanf("%d", &itemID);

    for (i = 0; i < orderCount; i++)
    {
        if (orders[i].orderID == orderID && orders[i].itemID == itemID)
        {
            found = 1;
            int j;
            for (j = i; j < orderCount - 1; j++)
            {
                orders[j] = orders[j + 1];
            }
            orderCount--;
            printf("\nItem Cancelled Successfully!\n");
            return;
        }
    }

    if (found == 0)
    {
        printf("\nOrder or Item Not Found!\n");
    }
}

void generateBill()
{
    int roomNo, i;
    float grandTotal = 0;

    printf("\nEnter Room Number: ");
    scanf("%d", &roomNo);

    printf("\n========= ROOM BILL =========\n");
    for (i = 0; i < orderCount; i++)
    {
        if (orders[i].roomNo == roomNo)
        {
            printf("%s x%d = %.2f\n",
                   orders[i].itemName,
                   orders[i].quantity,
                   orders[i].totalPrice);
            grandTotal += orders[i].totalPrice;
        }
    }

    if (grandTotal == 0)
        printf("No orders found for this room.\n");
    else
        printf("\nTotal Bill = %.2f\n", grandTotal);
}

void kitchenSummary()
{
    int i, j;

    if (orderCount == 0)
    {
        printf("\nNo Orders Found!\n");
        return;
    }

    printf("\n========= KITCHEN SUMMARY =========\n");
    for (i = 0; i < orderCount; i++)
    {
        if (strcmp(orders[i].status, "Served") != 0)
        {
            printf("\nOrder ID : %d", orders[i].orderID);
            printf("\nItem     : %s", orders[i].itemName);
            printf("\nQuantity : %d", orders[i].quantity);

            for (j = 0; j < menuSize; j++)
            {
                if (menu[j].id == orders[i].itemID)
                {
                    printf("\nPrep Time: %d mins\n", menu[j].prepTime);
                }
            }
        }
    }
}

void updateStatus()
{
    int orderID, found = 0, choice, i;

    printf("\nEnter Order ID: ");
    scanf("%d", &orderID);

    for (i = 0; i < orderCount; i++)
    {
        if (orders[i].orderID == orderID)
        {
            found = 1;
            printf("\n1. Preparing");
            printf("\n2. Served");
            printf("\nEnter Status Choice: ");
            scanf("%d", &choice);

            if (choice == 1)
                strcpy(orders[i].status, "Preparing");
            else if (choice == 2)
                strcpy(orders[i].status, "Served");
            else
                printf("Invalid Choice!\n");

            printf("\nStatus Updated Successfully!\n");
            break;
        }
    }

    if (found == 0)
    {
        printf("\nOrder ID Not Found!\n");
    }
}

int main()
{
    int choice;

    while (1)
    {
        printf("\n\n===== HOTEL FOOD ORDERING SYSTEM =====\n");
        printf("1. Display Menu\n");
        printf("2. Place Order\n");
        printf("3. Add Items to Existing Order\n");
        printf("4. Cancel Item from Order\n");
        printf("5. Generate Room Bill\n");
        printf("6. Display Kitchen Summary\n");
        printf("7. Update Order Status\n");
        printf("8. Display All Orders\n");
        printf("9. Exit\n");
        printf("\nEnter Your Choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1: displayMenu();    break;
            case 2: placeOrder();     break;
            case 3: addItems();       break;
            case 4: cancelItem();     break;
            case 5: generateBill();   break;
            case 6: kitchenSummary(); break;
            case 7: updateStatus();   break;
            case 8: displayOrders();  break;
            case 9:
                printf("\nThank You!\n");
                exit(0);
            default:
                printf("\nInvalid Choice!\n");
        }
    }

    return 0;
}
