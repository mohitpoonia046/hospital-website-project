#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_LENGTH 100


struct Property {
    char address[MAX_LENGTH];
    double price;
    int rooms;
    char type[MAX_LENGTH];
};


struct Client {
    char name[MAX_LENGTH];
    char email[MAX_LENGTH];
    char phone[MAX_LENGTH];
};


void registerProperty(struct Property *p) {
    printf("Enter property address: ");
    scanf("%s", p->address);
    printf("Enter property price: ");
    scanf("%lf", &p->price);
    printf("Enter number of rooms: ");
    scanf("%d", &p->rooms);
    printf("Enter property type: ");
    scanf("%s", p->type);
}


void displayProperty(struct Property *p) {
    printf("%s\t%.2f\t%d\t%s\n", p->address, p->price, p->rooms, p->type);
}


void registerClient(struct Client *c) {
    printf("Enter client name: ");
    scanf("%s", c->name);
    printf("Enter client email: ");
    scanf("%s", c->email);
    printf("Enter client phone: ");
    scanf("%s", c->phone);
}


void displayClient(struct Client *c) {
    printf("%s\t%s\t%s\n", c->name, c->email, c->phone);
}


void deleteProperty() {
    FILE *fp1, *fp2;
    char address[MAX_LENGTH];
    char line[MAX_LENGTH];


    printf("Enter address of property to delete: ");
    scanf("%s", address);

    
    fp1 = fopen("property_list.txt", "r");
    fp2 = fopen("temp.txt", "w");

    
    while (fgets(line, MAX_LENGTH, fp1)) {
        if (strstr(line, address) == NULL) {
            fputs(line, fp2);
        }
    }

    
    fclose(fp1);
    fclose(fp2);
    remove("property_list.txt");

    
    rename("temp.txt", "property_list.txt");

    printf("Property with address '%s' deleted.\n", address);
}


void contactOwner() {
    FILE *fp;
    char address[MAX_LENGTH];
    char line[MAX_LENGTH];

    
    printf("Enter address of property to contact owner: ");
    scanf("%s", address);

    
    fp = fopen("property_list.txt", "r");

    
    while (fgets(line, MAX_LENGTH, fp)) {
        if (strstr(line, address) != NULL) {
            printf("Property owner: %s", line);
        }
    }

    fclose(fp);
}


void addReview() {
    FILE *fp;
    char address[MAX_LENGTH];
    char line[MAX_LENGTH];
    char review[MAX_LENGTH];

    
    printf("Enter address of property to add review: ");
    scanf("%s", address);

    
    fp = fopen("property_list.txt", "r+");

    
    while (fgets(line, MAX_LENGTH, fp)) {
        if (strstr(line, address) != NULL) {
            printf("Enter review: ");
            scanf(" %[^\n]", review);
            fprintf(fp, "\nReview: %s\n", review);
        }
    }

    fclose(fp);
}


void displayAllProperties() {
    FILE *fp;
    struct Property p;

    
    fp = fopen("property_list.txt", "r");

    
    printf("Address\tPrice\tRooms\tType\n");
    while (fscanf(fp, "%s %lf %d %s", p.address, &p.price, &p.rooms, p.type) != EOF) {
        displayProperty(&p);
    }

    fclose(fp);
}


void displayAllClients() {
    FILE *fp;
    struct Client c;

   
    fp = fopen("client_list.txt", "r");

    
    printf("Name\tEmail\tPhone\n");
    while (fscanf(fp, "%s %s %s", c.name, c.email, c.phone) != EOF) {
        displayClient(&c);
    }

    fclose(fp);
}

int main() {
    int choice;
    struct Property p;
    struct Client c;

    
    while (1) {
        printf("\n");
        printf("1. Register property details\n");
        printf("2. Register client\n");
        printf("3. Delete property details\n");
        printf("4. Contact property owner\n");
        printf("5. Add client review\n");
        printf("6. Display all properties\n");
        printf("7. Display all clients\n");
        printf("8. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                registerProperty(&p);
                
                FILE *fp;
                fp = fopen("property_list.txt", "a");
                fprintf(fp, "%s %.2f %d %s\n", p.address, p.price, p.rooms, p.type);
                fclose(fp);
                printf("Property details registered.\n");
                break;

            case 2:
                registerClient(&c);
                
                fp = fopen("client_list.txt", "a");
                fprintf(fp, "%s %s %s\n", c.name, c.email, c.phone);
                fclose(fp);
                printf("Client registered.\n");
                break;

            case 3:
                deleteProperty();
                break;

            case 4:
                contactOwner();
                break;

            case 5:
                addReview();
                break;

            case 6:
                displayAllProperties();
                break;

            case 7:
                displayAllClients();
                break;

            case 8:
                return 0;

            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}
