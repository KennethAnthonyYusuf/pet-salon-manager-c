// This program was written by Kenneth Anthony Yusuf
// on 1/11/2024
//
// This program creates a pet salon manager for several salons where the
// salon has multiple rooms for different types of pets. The manager will
// track the details of the pets being cared for in each salon.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

////////////////////////////////////////////////////////////////////////////////
///////////////////////////      Constants       ///////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// provided constants
#define MAX_NAME_LEN 20
#define INVALID_PET_TYPE -1
#define CAPACITY 10
#define MAX_AMOUNT 10
#define TRUE 0
#define FALSE 1
#define ZERO 0
#define INFINITY 1000000000
#define RANDOM 234543
#define CAT_COST 11.5
#define DOG_COST 15.5
#define RABBIT_COST 5.5
#define PARROT_COST 7.6
#define MINIMUM_COST 0
#define MAXIMUM_COST 40
#define BASE_COST 10.2
#define FORWARD '>'
#define BACKWARD '<'
#define ONE 1
#define TWO 2

// all different types of pets that can be found in rooms
enum pet_type {
    CAT,
    DOG,
    RABBIT,
    PARROT,
};

////////////////////////////////////////////////////////////////////////////////
//////////////////////////  USER DEFINED TYPES  ////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// finance of the salon
struct financial_summary {
    int total_cared;
    double total_profit;
};

// salon overview
struct salon {
    char salon_name[MAX_NAME_LEN];
    struct financial_summary summary;
    double base_cost;
    struct pet_room *rooms;
    struct salon *next;
};
 
// room that can be found in salon
struct pet_room {
    char room_name[MAX_NAME_LEN];
    enum pet_type pet_type;
    int num_pets; 
    struct pet_room *next;
};


////////////////////////////////////////////////////////////////////////////////
////////////////////////// FUNCTION PROTOTYPES  ////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

struct salon *create_salon(char salon_name[MAX_NAME_LEN], double base_cost);
struct pet_room *create_room(char room_name[MAX_NAME_LEN], 
                                enum pet_type pet_type);
void print_one_room(int position, struct pet_room *room);
void print_pet_type(enum pet_type pet_type);
void print_salon_stats(struct salon *salon, int selected);
void print_total_stats(double profit, int pets);
void print_added_pets(int num_cats, int num_dogs, int num_rabbits, 
                        int num_parrots);
void scan_name(char string[MAX_NAME_LEN]);
enum pet_type scan_pet_type();
int scan_token(char *buffer, int buffer_size);
enum pet_type string_to_pet_type(char *pet_type);
struct pet_room *addroom(struct salon *head, char room_name[MAX_NAME_LEN], 
                            enum pet_type pet_type, char command);
void printallrooms(struct salon *head, struct salon *original);
int roomerror(struct salon *head, struct salon *original, char room_name[MAX_NAME_LEN]);
void outputroom(struct salon *head, struct salon *original, char command);
struct pet_room *adjecent(
    struct salon *head, 
    char room_name[MAX_NAME_LEN], 
    enum pet_type pet_type
);
struct pet_room *addamount(struct salon *head, enum pet_type pet_type, 
                            int amount);
int amountcheck(struct salon *head, enum pet_type pet_type);
void outputadd(struct salon *head, struct salon *original);
void countamount(struct salon *head, struct salon *original);
struct pet_room *addmaxamount(struct salon *head);
void splitroom(struct salon *head, struct salon *original);
struct pet_room *split(struct salon *head, struct pet_room *strroom,
                        char new_room_name[MAX_NAME_LEN]);
struct salon *addfinancial(struct salon *head, int amount, struct pet_room *room);
void financial(struct salon *head, struct salon *original);
int salonerror(struct salon *head, struct salon *original, char salon_name[MAX_NAME_LEN]);
int costerror(double base_cost);
struct salon *addsalon(struct salon *head, struct salon *original, 
                        char salon_name[MAX_NAME_LEN], double base_cost, 
                        char command);
int salonmsg(struct salon *head, struct salon *original, 
                char salon_name[MAX_NAME_LEN], double base_cost);
struct salon *forward(struct salon *head, struct salon *original,
                        struct salon *current);
void command(struct salon *head);
struct salon *backward(struct salon *head, struct salon *original,
                        struct salon *current);
void salondetails(struct salon *head, struct salon *original);
void errorfree(struct salon *head, struct salon *original);
struct pet_room *freeroom(struct salon *head, struct salon *original, char room_name[MAX_NAME_LEN]);
struct salon *freesalon(struct salon *head, struct salon *original, char command);
void memmoryfree(struct salon *original);
struct pet_room *orderroom(struct salon *head, struct salon *original);
int allocatecondition(struct salon *original, struct salon *head);
int mergeerror(char new_salon_name[MAX_NAME_LEN], 
                char old_salon_name1[MAX_NAME_LEN],
                char old_salon_name2[MAX_NAME_LEN],
                struct salon *oldsalon1,
                struct salon *oldsalon2, double base_cost, 
                struct salon *original, struct salon *head);
struct salon *merge(struct salon *original, struct salon *head, char command);

////////////////////////////////////////////////////////////////////////////////
////////////////////////////  MAIN FUNCTION  ///////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

int main(void) {
    printf("Welcome to 1091 CS Pet Salon manager! =^.^=\n");
    char salon_name[MAX_NAME_LEN] = "cs_salon";
    struct salon *head = create_salon(salon_name, BASE_COST);
    printf("Enter command: ");
    command(head);
    printf("\nAll pet salons closed! =^.^=\n");
    return ZERO;
}

////////////////////////////////////////////////////////////////////////////////
/////////////////////////////  FUNCTIONS  //////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// This function determine what function to call based on the user input
// 
// Parameters:
//      head    - linked list of salon 
// Returns:
//      None
void command(struct salon *head) {
    struct salon *original = head;
    struct salon *current = head;
    char salon_name[MAX_NAME_LEN];
    double base_cost = ZERO;
    int condition = TRUE;
    char command = ' ';
    while (scanf(" %c", &command) != EOF) {
        if (command == 'a') {
            outputroom(head, original, command);
        } else if (command == 'i') {
            outputroom(head, original, command);
        } else if (command == 'p') {
            printallrooms(head, original);
        } else if (command == 'm') {
            outputadd(head, original);
        } else if (command == 'h') {
            countamount(head, original);
        } else if (command == 's') {
            splitroom(head, original);
        } else if (command == 'f') {
            financial(head, original);
        } else if (command == 'c') {
            scan_name(salon_name);
            scanf("%lf", &base_cost);
            condition = salonmsg(head, original, salon_name, base_cost);
            if (condition == TRUE) {
                original = addsalon(head, original, salon_name, base_cost, 
                                    command);
            } 
        } else if (command == FORWARD) {
            current = forward(head, original, current);
            head = current;
        } else if (command == BACKWARD) {
            current = backward(head, original, current);
            head = current;
        } else if (command == 'd') {
            salondetails(head, original);
        } else if (command == 'r') {
            errorfree(head, original);
        } else if (command == 'q') {
            if (head == original) {
                condition = allocatecondition(original, head);
                head = freesalon(head, original, command);
                current = head;
                original = head;
            } else if (head != original) {
                head = freesalon(head, original, command);
                current = head;
                condition = FALSE;
            }
            if (condition == TRUE) {
                head = head->next;
            }
        } else if (command == 'o') {
            head->rooms = orderroom(head, original);
        } else if (command == 'x') {
            head = merge(original, head, command);
        }
        printf("Enter command: ");
    }
    memmoryfree(original);
}

// This function check for error input before merge a salon
// 
// Parameters:
//      original        - all the salon linked list from head until null
//      head            - currently selected salon
//      new_salon_name  - new salon name that the user want to create
//      old_salon_name1 - old salon name that the user want to merge
//      old_salon_name2 - old salon name that the user want to merge
//      oldsalon1       - address of the oldsalon
//      oldsalon2       - address of the oldsalon
//      base_cost       - average base_cost from both salon
// Returns:
//      variable name_condition true or false
int mergeerror(char new_salon_name[MAX_NAME_LEN], 
                char old_salon_name1[MAX_NAME_LEN],
                char old_salon_name2[MAX_NAME_LEN],
                struct salon *oldsalon1,
                struct salon *oldsalon2, double base_cost, 
                struct salon *original, struct salon *head) {
    struct salon *salon = original;
    int name_condition = TRUE;

    // This loop check if the new salon name already exist
    while (salon != NULL) {
        if (strcmp(salon->salon_name, new_salon_name) == ZERO && 
            strcmp(salon->salon_name, old_salon_name1) != ZERO &&
            strcmp(salon->salon_name, old_salon_name2) != ZERO) {
            name_condition = FALSE;
        }
        salon = salon->next;
    }

    // Condition to determine what error message to print
    if (name_condition == FALSE) {
        printf("Error: Salon name already exists!\n");
    } else if ((oldsalon1 == NULL) || (oldsalon2 == NULL)) {
        printf("Error: Salon name(s) do not exist to be merged!\n");
        name_condition = FALSE;
    } else if (strcmp(old_salon_name1, old_salon_name2) == ZERO) {
        printf("Error: Cannot merge a salon with itself!\n");
        name_condition = FALSE;
    }
    return name_condition;
}

// This function merge 2 salon into 1 salon 
// 
// Parameters:
//      original    - all the salon linked list from head until null
//      head        - currently selected salon
//      command     - char command from user to determine what function to call
// Returns:
//      newsalon new linkedlist with a merge salon inside
struct salon *merge(struct salon *original, struct salon *head, char command) {
    struct salon *salon = original;
    struct salon *oldsalon1 = NULL;
    struct salon *oldsalon2 = NULL;
    struct salon *newsalon = NULL;
    struct pet_room *room = NULL;
    char new_salon_name[MAX_NAME_LEN];
    char old_salon_name1[MAX_NAME_LEN];
    char old_salon_name2[MAX_NAME_LEN];
    scan_name(new_salon_name);
    scan_name(old_salon_name1);
    scan_name(old_salon_name2);
    double base_cost = ZERO;
    int condition = TRUE;
    while (salon != NULL) {
        if (strcmp(salon->salon_name, old_salon_name1) == ZERO) {
            oldsalon1 = salon;
        }
        salon = salon->next;
    }
    salon = original;
    while (salon != NULL) {
        if (strcmp(salon->salon_name, old_salon_name2) == ZERO) {
            oldsalon2 = salon;
        }
        salon = salon->next;
    }
    condition = mergeerror(new_salon_name, old_salon_name1, 
                old_salon_name2, oldsalon1, oldsalon2, base_cost,
                original, head);
    if (condition == FALSE) {
        return head;
    }
    base_cost = (oldsalon1->base_cost + oldsalon2->base_cost) / TWO;
    original = addsalon(head, original, new_salon_name, base_cost, command);
    salon = original;
    while (salon != NULL) {
        if (strcmp(salon->salon_name, new_salon_name) == ZERO) {
            newsalon = salon;
        }
        salon = salon->next;
    }
    if (oldsalon1->rooms != NULL) {
        newsalon->rooms = oldsalon1->rooms;
        if (oldsalon2->rooms != NULL) {
            room = newsalon->rooms;
            while (room->next != NULL) {
                room = room->next;    
            }
            room->next = oldsalon2->rooms;
        }
    } else if (oldsalon1->rooms == NULL && oldsalon2->rooms != NULL) {
        newsalon->rooms = oldsalon2->rooms;
    }
    head = freesalon(oldsalon1, original, command);
    head = freesalon(oldsalon2, original, command);
    newsalon->rooms = orderroom(newsalon, original);
    return newsalon;
}

// This function check the condition for selected salon
// 
// Parameters:
//      original    - all the salon linked list from head until null
//      head        - currently selected salon 
// Returns:
//     variable condition true or false
int allocatecondition(struct salon *original, struct salon *head) {
    int condition = TRUE;

    // This condition check where to put the selected salon
    if (head == original && head->next != NULL) {
        condition = TRUE;
    } else if (head == original && head->next == NULL) {
        condition = FALSE;
    } 
    return condition;
}

// This function order the rooms in alphabetical order
// 
// Parameters:
//      original    - all the salon linked list from head until null
//      head        - currently selected salon 
// Returns:
//      
struct pet_room *orderroom(struct salon *head, struct salon *original) {
    int len = ZERO;
    int count = ZERO;
    struct pet_room *loop = head->rooms;
    struct pet_room *current = head->rooms;
    struct pet_room *next = NULL;
    struct pet_room *before = NULL;
    struct pet_room *room = head->rooms;
    while (loop != NULL) {
        len++;
        loop = loop->next;
    }
    len = len - ONE;
    while (count < len) {
        int swap = ZERO;
        next = current->next;
        if (strcmp(next->room_name,current->room_name) < ZERO) {
            swap = ONE;
            if (current == head->rooms) {
                current->next = next->next;
                next->next = current;
                before = next;
                room = before;
            } else {
                current->next = next->next;
                next->next = current;
                before->next = next;
                before = next;
            }
        }
        before = current;
        current = current->next;
        count++;
        if (swap == ONE) {
            count = ZERO;
            current = room;
            before = NULL;
        }
    }
   
    return room;
}

// This function free all memmory 
// 
// Parameters:
//      original    - all the salon linked list from head until null
// Returns:
//      None
void memmoryfree(struct salon *original) {

    // the first salon in linked list
    struct salon *tmp = original;

    // the first room inside the first salon in linked list
    struct pet_room *str = original->rooms;
    struct pet_room *room = NULL;

    // Loop through the salons from head to NULL and freeing them 
    while (original != NULL) {
        tmp = original;
        room = original->rooms;

        // Loop through the rooms from head to NULL and freeing them 
        while (room != NULL) {
            str = room;
            room = room->next;
            free(str);
        }
        original = original->next;
        free(tmp);
    }
}

// This function will check for error and delete the currently selected salon
// 
// Parameters:
//      head        - currently selected salon 
//      original    - all the salon linked list from head until null
// Returns:
//      head which is the new linked list after freeing selected salon
struct salon *freesalon(struct salon *head, struct salon *original, 
                            char command) {

    // the first salon in the linked list
    struct salon *salon = original;
    struct salon *tmp = NULL;
    struct salon *before = NULL;
    struct salon *after = NULL;
    struct pet_room *room = NULL;
    struct pet_room *str = NULL;
    // condition to check if its possible to free the salon
    if (original->next == NULL) {
        printf("Error: Cannot remove when there is only one salon!\n");
    } else if (original->next != NULL) {

        // Loop to find the address before and after the selected salon
        while (salon != NULL) {
            if (strcmp(salon->salon_name, head->salon_name) == ZERO) {
                tmp = salon;
                salon = NULL;
            } else if (strcmp(salon->salon_name, head->salon_name) != ZERO) {
                before = salon;
                salon = salon->next;
            }
        }
        salon = original;

        // condition to rearrange the linked list order
        if (tmp->next != NULL) {
            after = tmp->next;
        }
        if (before == NULL) {
            head = salon->next;
        } else if (before != NULL) {
            before->next = after;
            head = before;
        }
        room = tmp->rooms;
        if (command != 'x') {
            // loop to free all the room 
            while (room != NULL) {
                str = room;
                room = room->next;
                free(str);
            }
        }
        free(tmp);
    }
    return head;
}

// This function check the error input from user for freeing the pet room
// 
// Parameters:
//      head        - currently selected salon 
//      original    - all the salon linked list from head until null
// Returns:
//      None
void errorfree(struct salon *head, struct salon *original) {

    // The first room in the selected salon
    struct pet_room *room = head->rooms;
    char room_name[MAX_NAME_LEN];
    scan_name(room_name);
    int condition = FALSE;

    // loop through the room from head to NULL
    while (room != NULL) {

        // checkin if the current room name are equal to the room name from user
        if (strcmp(room_name, room->room_name) == ZERO) {
            condition = TRUE;
        }
        room = room->next;
    }

    // Condition to determine what to print basead on the room condition
    if (condition == FALSE) {
        printf("Error: This room does not exist!\n");
    } else if (condition == TRUE) {
        head->rooms = freeroom(head, original, room_name);
        original->rooms = head->rooms;
        printf("Success! Room has been removed!\n");
    }
}

// This function free a selected room from user input
// 
// Parameters:
//      head        - currently selected salon 
//      original    - all the salon linked list from head until null
//      room_name   - the name of the room that the user input
// Returns:
//      room which is the new linked list of room in the selected salon
struct pet_room *freeroom(struct salon *head, struct salon *original, 
                            char room_name[MAX_NAME_LEN]) {

    // The first room of the selected salon
    struct pet_room *room = head->rooms;
    struct pet_room *tmp = NULL;
    struct pet_room *before = NULL;
    struct pet_room *after = NULL;

    // loop to find the address for the room before the selected room
    while (room != NULL) {

        // condition to find the address for selected room using room name
        if (strcmp(room_name, room->room_name) == ZERO) {
            tmp = room;
            room = NULL;
        } else if (strcmp(room_name, room->room_name) != ZERO) {
            before = room;
            room = room->next;
        }
    }

    // find the next address after the selected room 
    if (tmp->next != NULL) {
        after = tmp->next;
    }
    free(tmp);

    // condition to rearrange the linked list order
    if (before != NULL) {
        before->next = after;
        room = head->rooms;
    } else if (before == NULL) {
        room = after;
    }

    return room;
}

// This function will print out all the salons details
// 
// Parameters:
//      head        - currently selected salon 
//      original    - all the salon linked list from head until null
// Returns:
//      None
void salondetails(struct salon *head, struct salon *original) {

    // the selected salon
    struct salon *current = head;

    // the first salon in the linked list
    struct salon *salon = original;
    int selected = ZERO;
    double profit = ZERO;
    int pets = ZERO;

    // loop through all the salon in linked list and print the and count stats
    while (salon != NULL) {

        // condition to check if the current salon is the selected salon
        if (strcmp(salon->salon_name, current->salon_name) == ZERO) {
            selected = ONE;
        }
        print_salon_stats(salon, selected);
        selected = ZERO;
        profit = profit + salon->summary.total_profit;
        pets = pets + salon->summary.total_cared;
        salon = salon->next;
    }
    print_total_stats(profit, pets);
}

// This function move the salon backward 
// 
// Parameters:
//      head        - currently selected salon 
//      original    - all the salon linked list from head until null
//      current     - temporally variable to keep the current address
// Returns:
//      current which is the address of the new selected salon
struct salon *backward(struct salon *head, struct salon *original,
                        struct salon *current) {
    
    // first salon in the linked list
    struct salon *salon = original;

    // first salon in the linked list
    struct salon *loop = original;
    struct salon *tmp = NULL;

    // loop through all the salon in the linked list
    while (loop != NULL) {

        // condition to get the address of the salon near the selected salon
        if (strcmp(salon->salon_name, current->salon_name) == ZERO) {
            loop = NULL;
        } else if (strcmp(salon->salon_name, current->salon_name) != ZERO) {
            tmp = salon;
            loop = salon->next;
            salon = salon->next;
        }
    }

    // condition to assign the new selected salon
    if (tmp != NULL) {
        current = tmp;
    } else if (tmp == NULL) {
        
        // Loop to find the last salon in the linked list
        while (original->next != NULL) {
            original = original->next;
        }
        tmp = original;
        current = tmp;
    }
    printf("You have now selected salon: %s!\n", current->salon_name);
    return current;
}

// This function move the salon forward
// 
// Parameters:
//      head        - currently selected salon 
//      original    - all the salon linked list from head until null
//      current     - temporally variable to keep the current address
// Returns:
//      salon which is the address of the new selected salon
struct salon *forward(struct salon *head, struct salon *original,
                        struct salon *current) {
    
    // the selected salon inside current
    struct salon *salon = current;

    // condition to determine the selected salon
    if (salon->next == NULL) {
        salon = original;
    } else if (salon->next != NULL) {
        salon = salon->next;
    }
    printf("You have now selected salon: %s!\n", salon->salon_name);
    return salon;
}

// This function check the input for creating new room and error
// 
// Parameters:
//      head        - currently selected salon 
//      original    - all the salon linked list from head until null
//      salon_name  - the name of the salon that the user input
//      base_cost   - base cost that the user input
// Returns:
//      Variable condition true or false
int salonmsg(struct salon *head, struct salon *original, 
                char salon_name[MAX_NAME_LEN], double base_cost) {
    int name_condition = TRUE;
    int cost_condition = TRUE;
    int condition = FALSE;
    name_condition = salonerror(head, original, salon_name);
    cost_condition = costerror(base_cost);

    // Determing what to print basead on condition of salon name and cost
    if (name_condition == FALSE) {
        printf("Error: Salon name already exists!\n");
    } else if (cost_condition == FALSE) {
        printf("Error: Cost needs to within $0-$40!\n");
    }
    if (name_condition == TRUE && cost_condition == TRUE) {
        condition = TRUE;
    }
    return condition;
}

// This function add a new salon with name and base cost from user input
// 
// Parameters:
//      head        - currently selected salon 
//      original    - all the salon linked list from head until null
//      salon_name  - the name of the salon that the user input
//      base_cost   - base cost that the user input
// Returns:
//      Address of salon which is the new linked list with new salon inside
struct salon *addsalon(struct salon *head, struct salon *original, 
                        char salon_name[MAX_NAME_LEN],
                        double base_cost, char command) {
    
    // the first salon in the linked list
    struct salon *salon = original;
    struct salon *before = NULL;
    struct salon *storage1 = NULL;
    struct salon *storage2 = NULL;
    // The address of the new salon
    struct salon *newsalon = create_salon(salon_name, base_cost);

    // Loop to check the order of the salon name
    while (salon != NULL) {

        // Checking if salon name form user is bigger than the current salon
        if (strcmp(salon_name, salon->salon_name) > ZERO) {
            storage1 = salon;        
        } else if (strcmp(salon_name, salon->salon_name) < ZERO 
                    && (storage2 == NULL)) {
            storage2 = salon;    
        }
        salon = salon->next;
    }
    salon = original;

    // condition if the salon name from user smaller 
    if (storage2 != NULL) {

        // loop through all the salon in linked list
        while (salon != NULL) {

            // condition to find the salon address before the selected salon
            if (strcmp(salon_name, salon->salon_name) < ZERO) {
                salon = NULL;
            } else if (strcmp(salon_name, salon->salon_name) != ZERO) {
                before = salon;
                salon = salon->next;
            }
        }
    }

    // condition to allocate the new salon location in the linked list
    if (storage1 != NULL) {
        newsalon->next = storage1->next;
        storage1->next = newsalon;
        salon = original;
    } else if (storage2 != NULL && before != NULL) {
        before->next = newsalon;
        newsalon->next = storage2;
        salon = original;
    } else if (storage2 != NULL && before == NULL) {
        newsalon->next = storage2;
        salon = newsalon;
    }
    if (command == 'c') {
        printf("Success! The salon: %s has been created!\n", salon_name);
    }
    return salon;
}

// This function check the error input for base cost 
// 
// Parameters:
//      base_cost   - base cost that the user input
// Returns:
//      Variable condition true or false 
int costerror(double base_cost) {
    int condition = TRUE;

    // Determing whether the base cost from user input in the available range 
    if (base_cost < MINIMUM_COST || base_cost > MAXIMUM_COST) {
        condition = FALSE;
    }
    return condition;
}

// This function check the error input for salon name from user
// 
// Parameters:
//      head        - currently selected salon 
//      original    - all the salon linked list from head until null
//      salon_name  - the name of the salon that the user input
// Returns:
//      Variable condition true or false 
int salonerror(struct salon *head, struct salon *original, 
                char salon_name[MAX_NAME_LEN]) {

    // the first salon in the linked list
    struct salon *salon = original;
    int condition = TRUE;

    // Loop to check whether the salon name already exist or not
    while (salon != NULL) {

        // Checking if the salon name from user and the selected salon are equal
        if (strcmp(salon_name, salon->salon_name) == ZERO) {
            condition = FALSE;
            return condition;
        }
        salon = salon->next;
    }
    return condition;
}

// This function check the error input and update the salon financial value
// 
// Parameters:
//      head        - currently selected salon 
//      original    - all the salon linked list from head until null
// Returns:
//      None
void financial(struct salon *head, struct salon *original) {

    // The first room in the selected salon
    struct pet_room *find_room = head->rooms;
    struct pet_room *room = NULL;
    char room_name[MAX_NAME_LEN];
    scan_name(room_name);
    int amount = ZERO;
    scanf("%d", &amount);

    // Loop to find the salon that the user want to change
    while (find_room != NULL) {

        // Condition to find the address of the selected room using room name
        if (strcmp(room_name, find_room->room_name) == TRUE) {
            room = find_room;
        }
        find_room = find_room->next;
    }

    // Determine what to print according to the room condition and amount 
    if (room == NULL) {
        printf("Error: This room does not exist!\n");
    } else if (amount > room->num_pets || amount < ZERO) {
        printf("Error: Invalid amount!\n");
    } else {
        head = addfinancial(head, amount, room);
        printf("Success! %d pets have been cared for!\n", amount);
    }
}

// This function calculate the cost based on the pet that being cared for
// 
// Parameters:
//      head        - currently selected salon 
//      amount      - the number of pet the user input 
//      pet_room    - room that the user want change 
// Returns:
//      address of the selected salon 
struct salon *addfinancial(struct salon *head, int amount, 
                            struct pet_room *room) {
    double cost = ZERO;
    room->num_pets = room->num_pets - amount;

    // Condition to add the cost according to the selected room pet type
    if (room->pet_type == CAT) {
        cost = CAT_COST;
    } else if (room->pet_type == DOG) {
        cost = DOG_COST;
    } else if (room->pet_type == RABBIT) {
        cost = RABBIT_COST;
    } else if (room->pet_type == PARROT) {
        cost = PARROT_COST;
    }
    head->summary.total_cared = amount;
    head->summary.total_profit = amount * (head->base_cost + cost);
    return head;
}

// This function will take in input for spliting the room and check for error 
// 
// Parameters:
//      head        - currently selected salon 
//      original    - all the salon linked list from head until null
// Returns:
//      None
void splitroom(struct salon *head, struct salon *original) {

    // The first room in the selected salon
    struct pet_room *room = head->rooms;
    struct pet_room *strroom = NULL;
    char room_name[MAX_NAME_LEN];
    scan_name(room_name);
    char new_room_name[MAX_NAME_LEN];
    scan_name(new_room_name);

    // Loop through all the room in the selected salon form head until NULL
    while (room != NULL) {

        // Check if the room name from user are equal to the selected room
        if (strcmp(room_name, room->room_name) == ZERO) {
            strroom = room;
        }
        room = room->next;
    }
    int condition1 = roomerror(head, original, room_name);
    int condition2 = roomerror(head, original, new_room_name);

    // Condition to determine what to print according to the room condition
    if (condition1 == TRUE) {
        printf("Error: This room does not exist!\n");
    } else if (condition2 == FALSE) {
        printf(
        "Error: Cannot create room as room with given name already exists!\n"
        );
    } else if (strroom->num_pets <= ONE) {
        printf("Error: Not enough pets in room to split across two rooms!\n");
    } else {
        head->rooms = split(head, strroom, new_room_name);
        printf("Success! Pet amount has been split across two rooms!\n");
    }
}

// This function split one room into two rooms with the room name from user
// 
// Parameters:
//      head            - currently selected salon 
//      strroom         - the room that the user want to split
//      New_room_name   - name for the new room
// Returns:
//      The address of the room in the selected salon
struct pet_room *split(struct salon *head, struct pet_room *strroom,
                        char new_room_name[MAX_NAME_LEN]) {

    // The first room in the selected salon
    struct pet_room *room = head->rooms;     

    // The number of pet in the selected room
    int amount = strroom->num_pets;     
    int num1 = ZERO;
    int num2 = ZERO;            
    enum pet_type pet_type;

    // The type of pet in the selected room
    pet_type = strroom->pet_type;

    // The next address inside the selected room 
    struct pet_room *next = strroom->next;
    strroom->next = create_room(new_room_name, pet_type);
    room = strroom->next;
    room->next = next;

    // Condition to check whether the amount is odd or even
    if ((amount / TWO) != ZERO) {
        num1 = ((amount - ONE) / TWO) + ONE;
        num2 = amount - num1;
    } else if ((amount / TWO) == ZERO) {
        num1 = amount / TWO;
        num2 = amount - num1;
    }
    strroom->num_pets = num1;
    room->num_pets = num2;
    room = head->rooms;

    return room;
}

// This function will count how many num of pet thats been added
// 
// Parameters:
//      head        - currently selected salon 
//      original    - all the salon linked list from head until null
// Returns:
//      None
void countamount(struct salon *head, struct salon *original) {
    struct pet_room *room = head->rooms;
    enum pet_type pet_type;
    int cats = ZERO;
    int dogs = ZERO;
    int rabbits = ZERO;
    int parrots = ZERO;
    int used = ZERO;

    // Loop through current room and count all the room for each pet type
    while (room != NULL) {
        if (room->pet_type == CAT) {
            cats++;
        } else if (room->pet_type == DOG) {
            dogs++;
        } else if (room->pet_type == RABBIT) {
            rabbits++;
        } else if (room->pet_type == PARROT) {
            parrots++;
        }
        room = room->next;
    }
    room = head->rooms;      

    // Condition to count how many num has been added to each pet type 
    if (cats != ZERO) {
        pet_type = CAT;
        used = (cats * MAX_AMOUNT) - amountcheck(head, pet_type);
        cats = (cats * MAX_AMOUNT) - used;
    } 
    if (dogs != ZERO) {
        pet_type = DOG;
        used = (dogs * MAX_AMOUNT) - amountcheck(head, pet_type);
        dogs = (dogs * MAX_AMOUNT) - used;
    }
    if (rabbits != ZERO) {
        pet_type = RABBIT;
        used = (rabbits * MAX_AMOUNT) - amountcheck(head, pet_type);
        rabbits = (rabbits * MAX_AMOUNT) - used;
    }
    if (parrots != ZERO) {
        pet_type = PARROT;
        used = (parrots * MAX_AMOUNT) - amountcheck(head, pet_type);
        parrots = (parrots * MAX_AMOUNT) - used;
    }

    // Loop the room in the selected salon and add all pet num to max
    while (room != NULL) {
        room->num_pets = MAX_AMOUNT;
        room = room->next;
    }
    print_added_pets(cats, dogs, rabbits, parrots);
}

// This function add the max amount of pet num in each room for every pet type
// 
// Parameters:
//      head        - currently selected salon 
// Returns:
//       The address of the room in the selected salon
struct pet_room *addmaxamount(struct salon *head) {

    // The first room in the selected salon
    struct pet_room *room = head->rooms;

    // Loop the room in the selected salon and add all pet num to max
    while (room != NULL) {
        room->num_pets = MAX_AMOUNT;
        room = room->next;
    }
    room = head->rooms;
    return room;
}

// Tis function determine what to do base on the input, storage, and error check
// 
// Parameters:
//      head        - currently selected salon 
//      original    - all the salon linked list from head until null
// Returns:
//       None
void outputadd(struct salon *head, struct salon *original) {
    enum pet_type pet_type;
    pet_type = scan_pet_type();
    int amount = ZERO;
    scanf("%d", &amount);
    int total = amountcheck(head, pet_type);

    // determine what to print according to user input and available storrage
    if (pet_type == INVALID_PET_TYPE) {
        printf
        ("Error: Unfortunately, this salon does not cater for this pet type!\n"
        );
    } else if (total < amount) {
        printf("Error: There is not enough space to add that many pets!\n");
    } else if (amount < ZERO) {
        printf("Error: Amount of pets must be greater than zero!\n");
    } else if (total >= amount) {
        head->rooms = addamount(head, pet_type, amount);
        printf("Success! Pets have been added to room(s)!\n");
    }
}

// This function count how many storage is available 
// 
// Parameters:
//      head        - currently selected salon 
//      pet_type    - an enum of the pet_type that the user input 
// Returns:
//       Variable total of the available storage for the pet type
int amountcheck(struct salon *head, enum pet_type pet_type) {

    // The first room in the selected salon
    struct pet_room *room = head->rooms;
    int total = ZERO;

    // Loop the room in the selected salon from head until NULL
    while (room != NULL) {

        // check the current room pet type and pet type from user input 
        if (room->pet_type == pet_type) {

            // This condition count all the available storage for num pet
            if (room->num_pets == ZERO) {
                total = total + MAX_AMOUNT;
            } else if (room->num_pets > ZERO) {
                total = (MAX_AMOUNT - room->num_pets) + total;
            }
        }
        room = room->next;
    }
    return total;
}

// This function will add the amount of pet from the user input
// 
// Parameters:
//      head        - currently selected salon 
//      amount      - The number of pet the user input 
//      pet_type    - an enum of the pet_type that the user input 
// Returns:
//       The address of the room in the selected salon
struct pet_room *addamount(struct salon *head, enum pet_type pet_type, 
                            int amount) {

    // The first room in the selected salon
    struct pet_room *room = head->rooms;
    int leftover = ZERO;

    // Loop the room in the selected salon from head until NULL
    while (room != NULL) {

        // This condition count the leftover storage for selected pet type 
        if ((room->pet_type == pet_type) && (room->num_pets <= amount)) {
            room->num_pets = room->num_pets + amount;
            leftover = room->num_pets - MAX_AMOUNT;

            // Check whether the leftover num pet are bigger than zero
            if (leftover >= ZERO) {
                room->num_pets = MAX_AMOUNT;
            }
            amount = leftover;
        }
        room = room->next;
    }
    room = head->rooms;

    return room;
}

// This function determine what to do for adding room base on the error check
// 
// Parameters:
//      head        - currently selected salon 
//      original    - all the salon linked list from head until null
//      command     - character input from user to determine the output
// Returns:
//       None
void outputroom(struct salon *head, struct salon *original, char command) {
    char room_name[MAX_NAME_LEN];
    enum pet_type pet_type;
    int room_condition = TRUE;
    scan_name(room_name);
    pet_type = scan_pet_type();
    room_condition = roomerror(head, original, room_name);

    // determine what to do based on the room name and pet type condition
    if (room_condition == TRUE && pet_type != INVALID_PET_TYPE 
        && command == 'a') {
        head->rooms = addroom(head, room_name, pet_type, command);
    } else if (room_condition == TRUE && pet_type != INVALID_PET_TYPE 
    && command == 'i') {
        head->rooms = adjecent(head, room_name, pet_type);
    } else if (room_condition == FALSE) {
        printf("Error: This room name already exists!\n");

    } else if (pet_type == INVALID_PET_TYPE) {
        printf
        ("Error: Unfortunately, this salon does not cater for this pet type!\n"
        );

    }  
}

// This function allow user to add room to the salon
// 
// Parameters:
//      head        - currently selected salon 
//      room_name   - the name of the room that the user input
//      pet_type    - an enum of the pet_type that the user input 
//      command     - character input from user to determine the output
// Returns:
//       The address of the room in the selected salon
struct pet_room *addroom(struct salon *head, char room_name[MAX_NAME_LEN], 
                            enum pet_type pet_type, char command) {

    // The first room in the selected salon
    struct pet_room *room = head->rooms;
    struct pet_room *roomname = NULL;

    // Condition to check whether the selected salon have a room or not
    if (room == NULL) {
        room = create_room(room_name, pet_type);
        roomname = room;
    } else if (room != NULL) {

        // Loop until the last room to find the last room address
        while (room->next != NULL) {
            room = room->next;
        } 

        // assigning the new location for the new room into the linked list
        room->next = create_room(room_name, pet_type);
        room = room->next;
        roomname = room;
        room = head->rooms;
    }

    // Check if the input from user is correct then print the following 
    if (command == 'a') {
        printf("Room: '%s' added!\n", roomname->room_name);

    }
    return room;
}

// This function print a room and allocate them according to the room pet type
// 
// Parameters:
//      head        - currently selected salon 
//      room_name   - the name of the room that the user input
//      pet_type    - an enum of the pet_type that the user input 
// Returns:
//       The address of the room in the selected salon
struct pet_room *adjecent(struct salon *head, char room_name[MAX_NAME_LEN], 
                            enum pet_type pet_type) {

    // The first room in the selected salon
    struct pet_room *room = head->rooms;
    struct pet_room *roomstr = NULL;
    struct pet_room *roomname = NULL;

    // The first room in the selected salon
    struct pet_room *roomtest = head->rooms;
    int condition = FALSE;

    // Condition to check whether the selected salon have a room or not 
    if (roomtest != NULL) {

        // Loop the the room inside the selected salon from head until NULL
        while (roomtest != NULL) {

            // Check if the current room have the same pet type as the input
            if (roomtest->pet_type == pet_type) {
                condition = TRUE;
            }
            roomtest = roomtest->next;
        } 
    }

    // condition to create the new room and allocate them in the linked list
    if (room == NULL && condition == FALSE) {
        room = create_room(room_name, pet_type);
        roomname = room;
    } else if (room != NULL && condition == TRUE) {

        // Loop until the room pet type are equal the pet type from user
        while (room->pet_type != pet_type) {
            room = room->next;
        } 

        // assigning the new location for the new room into the linked list
        roomstr = room->next;
        room->next = create_room(room_name, pet_type);
        room = room->next;
        room->next = roomstr;
        roomname = room;
        room = head->rooms;
    } else if (room != NULL && condition == FALSE) {

        // Loop until the last room to find the last room address
        while (room->next != NULL) {
            room = room->next;
        } 

        // assigning the new location for the new room into the linked list
        room->next = create_room(room_name, pet_type);
        room = room->next;
        roomname = room;
        room = head->rooms;
    }
    printf("Room: '%s' inserted!\n", roomname->room_name);
    return room;
}

// This function check for the error input for room from user
// 
// Parameters:
//      head        - currently selected salon 
//      original    - all the salon linked list from head until null
//      room_name   - the name of the room that the user input
// Returns:
//       Variable condition true or false
int roomerror(struct salon *head, struct salon *original, 
                char room_name[MAX_NAME_LEN]) {
    int condition = TRUE;

    // First room inside the first salon in linked list
    struct pet_room *room = original->rooms;

    // Loop through all the salons in linked list from head until NULL
    while (original != NULL) {
        room = original->rooms;

        // Loop through all rooms in the selected salon from head until NULL
        while (room != NULL) {

            // Check equality for current room name and the room name from user
            if (strcmp(room_name, room->room_name) == ZERO) {
                return condition = FALSE;
            }
            room = room->next;
        }  
        original = original->next;
    }


    return condition;
}

// This function print all the rooms that the selected salon have
// 
// Parameters:
//      head        - currently selected salon 
//      original    - all the salon linked list from head until null
// Returns:
//       None
void printallrooms(struct salon *head, struct salon *original) {
    struct pet_room *room = head->rooms;
    int position = ONE;

    // Loop through all the rooms in the selected salon and print each of them 
    while (room != NULL) {
        print_one_room(position, room);
        room = room->next;
        position++;
    }

    // Condition to determine what to print 
    if (head->rooms == NULL) {
        printf("There are no pet rooms in this salon!\n");
    } else if (head->rooms != NULL) {
        printf("All the rooms listed above are in salon '%s'.\n", 
                head->salon_name);
    }
}

// Create a new salon with a given name from user
// 
// Parameters:
//      salon_name  - name for the new salon from user input
//      base_cost   - base cost for a new salon
// Returns:
//      the address of the new struct salon 
struct salon *create_salon(char salon_name[MAX_NAME_LEN], double base_cost) {
    struct salon *salon = malloc(sizeof (struct salon));
    strcpy(salon->salon_name, salon_name);
    salon->base_cost = base_cost;
    salon->summary.total_cared = ZERO;
    salon->summary.total_profit = ZERO;
    salon->next = NULL;
    salon->rooms = NULL;
    
    return salon;
}

// Create a new room inside the salon with a name and pet type given by user
//
// Paramters:
//      room_name   - the name of the room that the user input
//      pet_type    - an enum of the pet_type that the user input 
// Returns:
//      the new address of the new struct room
struct pet_room *create_room(char room_name[MAX_NAME_LEN], 
                                enum pet_type pet_type) {
    struct pet_room *room= malloc(sizeof (struct pet_room));
    strcpy(room->room_name, room_name);
    room->pet_type = pet_type;
    room->num_pets = ZERO;
    room->next = NULL;

    return room;
}

// Prints a single room, displaying name, position, pet_type, number of pets and
// cost of care for that room
//
// Parameters:
//      position    - the position of the room in the salon (the first 
//                        room will be room 1, second will be 2, etc)
//      room        - a pointer to the struct pet_room
//
// Returns:   
//      None
void print_one_room(int position, struct pet_room *room) {
    printf("/-------------------------------\\\n");
    printf("Room name: %s\n", room->room_name);
    printf("    Room position: %d\n", position);
    printf("    Pet type: ");
    print_pet_type(room->pet_type);
    printf("\n    Num of pets in room: %d/10\n", room->num_pets);
    printf("\\-------------- | --------------/\n");
    printf("                V\n");
}

// Print the statistics of one salon
// 
// Parameters:
//      salon    - a pointer to the struct salon
//      selected - an integer indicating if the salon is 'selected' or not
// Returns:
//      None
//
void print_salon_stats(struct salon *salon, int selected) {
    printf("/-------------------------------\\\n");
    printf("Stats from salon: %s", salon->salon_name);
    if (selected == 1) {
        printf(" (selected)");
    }
    printf("\n    Salon's base cost: %.2lf\n", salon->base_cost);
    printf("    Total pets cared for: %d\n", salon->summary.total_cared);
    printf("    Total profit from cared pets: %.2lf\n", 
            salon->summary.total_profit);
    printf("\\-------------- | --------------/\n");
    printf("                V\n");
}

// Print the statistics of all the salons combined
// 
// Parameters:
//      profit  - amount of money the salons has made
//      pets    - number of pets that have been cared for by the salons
// Returns:
//      None
//
void print_total_stats(double profit, int pets) {
    printf("/-------------------------------\\\n");
    printf("Combined stats from all salons!\n");
    printf("    Total pets cared for: %d\n", pets);
    printf("    Total profit from cared pets: %.2lf\n", profit);
    printf("\\-------------------------------/\n");
}

// Print type of pet as a string
// 
// Parameters:
//      pet_type    - the type of pet
// Returns:
//      None
//
void print_pet_type(enum pet_type pet_type) {
    if (pet_type == CAT) {
        printf("cat");
    } else if (pet_type == DOG) {
        printf("dog");
    } else if (pet_type == RABBIT) {
        printf("rabbit");
    } else if (pet_type == PARROT) {
        printf("parrot");
    }
}

// Print the amount of pets being added to the salon
// 
// Parameters:
//      num_cats    - number of additional cats added
//      num_dogs    - number of additional dogs added
//      num_rabbits - number of additional rabbits added
//      num_parrots - number of additional parrots added
// Returns:
//      None
//
void print_added_pets(int num_cats, int num_dogs, int num_rabbits, 
                        int num_parrots) {
    printf("/-------------------------------\\\n");
    printf("    Cats added: %d\n", num_cats);
    printf("    Dogs added: %d\n", num_dogs);
    printf("    Rabbits added: %d\n", num_rabbits);
    printf("    Parrots added: %d\n", num_parrots);
    printf("\\-------------------------------/\n");
}

// Scan for a name
// 
// Parameters:
//      string - the string to be scanned
// Returns:
//      None
//
void scan_name(char string[MAX_NAME_LEN]) {
    scan_token(string, MAX_NAME_LEN);
}

// Scan an enum pet_type
// 
// Parameters:
//      None
// Returns:
//      enum pet_type variable
//
enum pet_type scan_pet_type() {
    char pet_type[MAX_NAME_LEN];
    scan_token(pet_type, MAX_NAME_LEN);
    return string_to_pet_type(pet_type);
}

// Scan a token into the provided buffer of buffer_size
// 
// Parameters:
//      buffer      - the buffer being scanned into
//      buffer_size - the size of buffer
// Returns:
//      the number of chars scanned
//
int scan_token(char *buffer, int buffer_size) {
    if (buffer_size == ZERO) {
        return ZERO;
    }

    char c;
    int i = ZERO;
    int num_scanned = ZERO;

    // consume all leading whitespace
    scanf(" ");

    // scan in characters until whitespace
    while (i < buffer_size - ONE
        && (num_scanned = scanf("%c", &c)) == ONE
        && !isspace(c)) {

        buffer[i++] = c;
    }

    if (i > ZERO) {
        buffer[i] = '\0';
    }

    return num_scanned;
}

// Convert a string into an enum pet_type
// 
// Parameters:
//      pet_type    - a string version of the pet type
// Returns:
//      enum pet_type
//
enum pet_type string_to_pet_type(char *pet_type) {
    int len = strlen(pet_type);

    if (strncasecmp(pet_type, "cat", len) == ZERO) {
        return CAT;
    } 
    if (strncasecmp(pet_type, "dog", len) == ZERO) {
        return DOG;
    } 
    if (strncasecmp(pet_type, "rabbit", len) == ZERO) {
        return RABBIT;
    }
    if (strncasecmp(pet_type, "parrot", len) == ZERO) {
        return PARROT;
    } 

    return INVALID_PET_TYPE;
}