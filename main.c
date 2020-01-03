#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int drink_amount = 0;
int drinks_made = 0;
void *drinks = NULL;
struct cookie *cookie_head = NULL;
int receipts[] = {
        50,
        30,
        20
};

struct drink {
    int price;
    char *name;
    long int id;
    long int votes;
};

struct cookie {
    struct cookie *fd;
    long int id;
};

void print_menu() {
    puts("1. make a drink");
    puts("2. list cookies");
    puts("3. make a cookie");
    puts("4. get the flag and win");
    puts("5. print receipts for the day");
    puts("6. exit the shop");
}

void make_cookie() {
    int stuffing;
    puts("how many bytes would you like to stuff your cookies?");
    scanf("%d%*c", &stuffing);
    puts("put cookie id:");
    if (cookie_head == NULL) {
        cookie_head = malloc(sizeof(struct cookie) + stuffing);
        scanf("%ld%*c", &cookie_head->id);
        cookie_head->fd = NULL;

    } else {
        struct cookie *save = cookie_head->fd;
        cookie_head->fd = malloc(sizeof(struct cookie));
        cookie_head->fd->fd = save;
        scanf("%ld%*c", &cookie_head->fd->id);
    }
}

void print_cookies() {
    struct cookie *ptr = cookie_head;
    while (ptr != NULL) {
        printf("cookie id: %ld\n", ptr->id);
        ptr = ptr->fd;
    }
}

void make_drink() {
    if (drink_amount <= drinks_made) {
        if (drinks_made == 0 && drink_amount == 0) {
            puts("so first you say you're not gonna make drinks then you do??? okay???");
        } else {
            puts("you've made too many drinks sir");
            exit(1);
        }

    }
    long int price;
    int id;
    long int votes;
    char name_buffer[32];
    puts("input drink price");
    scanf("%ld%*c", &price);
    puts("input drink id");
    scanf("%d%*c", &id);
    puts("input the rating you give this drink");
    scanf("%ld%*c", &votes);
    puts("input drink name");
    fgets(name_buffer, sizeof name_buffer, stdin);
    name_buffer[32] = '\0';
    struct drink *selected_drink = &drinks[drinks_made * sizeof(struct drink)];
    selected_drink->price = price;
    if (name_buffer[1] != '\0') {
        selected_drink->name = malloc(strlen(name_buffer));
        strcpy(selected_drink->name, name_buffer);
    } else {
        selected_drink->name = NULL;
    }
    selected_drink->id = id;
    selected_drink->votes = votes;
    drinks_made++;
}

void print_flag() {
    FILE *flag = fopen("./flag.txt","r");
    if (flag == NULL)
    {
        printf("Cannot open file \n");
        exit(0);
    }
    char c;
    c = fgetc(flag);
    while (c != EOF)
    {
        printf ("%c", c);
        c = fgetc(flag);
    }
    printf("\n");
}

void print_receipt() {
    int index;
    puts("what receipt would you like to see?");
    scanf("%d%*c", &index);
    printf("%d$ was made from this purchase", receipts[index]);
}

int main(int argc, char *argv[]) {
    int choice;
    puts("welcome to the pepsi cafe, where we say fuck you to top chunks");
    puts("how many drinks would you like to make?");
    scanf("%d", &drink_amount);
    if (drink_amount < 0 || drink_amount > 3) {
        puts("invalid amount");
        exit(1);
    }
    drinks = malloc(drink_amount * sizeof(struct drink));
    while (1) {
        print_menu();
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                make_drink();
                break;
            case 2:
                print_cookies();
                break;
            case 3:
                make_cookie();
                break;
            case 4:
                print_flag();
                break;
            case 5:
                print_receipt();
                break;
            case 6:
                exit(1);
            default:
                break;
        }
    }
}


