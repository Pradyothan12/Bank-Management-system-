#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct account {
    int acc_no;
    char name[50];
    float balance;
};

void createAccount();
void deposit();
void withdraw();
void display();

int main() {
    int choice;

    while(1) {
        printf("\n--- BANK MANAGEMENT SYSTEM ---\n");
        printf("1. Create Account\n");
        printf("2. Deposit Money\n");
        printf("3. Withdraw Money\n");
        printf("4. Display Account\n");
        printf("5. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: createAccount(); break;
            case 2: deposit(); break;
            case 3: withdraw(); break;
            case 4: display(); break;
            case 5: exit(0);
            default: printf("Invalid choice\n");
        }
    }
}

void createAccount() {
    FILE *fp;
    struct account acc;

    fp = fopen("bank.dat", "ab");

    printf("Enter Account Number: ");
    scanf("%d", &acc.acc_no);

    printf("Enter Name: ");
    scanf("%s", acc.name);

    printf("Enter Initial Balance: ");
    scanf("%f", &acc.balance);

    fwrite(&acc, sizeof(acc), 1, fp);
    fclose(fp);

    printf("Account Created Successfully!\n");
}

void deposit() {
    FILE *fp;
    struct account acc;
    int accno;
    float amount;

    fp = fopen("bank.dat", "rb+");

    printf("Enter Account Number: ");
    scanf("%d", &accno);

    while(fread(&acc, sizeof(acc), 1, fp)) {
        if(acc.acc_no == accno) {
            printf("Enter amount to deposit: ");
            scanf("%f", &amount);

            acc.balance += amount;

            fseek(fp, -sizeof(acc), SEEK_CUR);
            fwrite(&acc, sizeof(acc), 1, fp);

            printf("Money Deposited!\n");
            break;
        }
    }

    fclose(fp);
}

void withdraw() {
    FILE *fp;
    struct account acc;
    int accno;
    float amount;

    fp = fopen("bank.dat", "rb+");

    printf("Enter Account Number: ");
    scanf("%d", &accno);

    while(fread(&acc, sizeof(acc), 1, fp)) {
        if(acc.acc_no == accno) {
            printf("Enter amount to withdraw: ");
            scanf("%f", &amount);

            if(acc.balance >= amount) {
                acc.balance -= amount;

                fseek(fp, -sizeof(acc), SEEK_CUR);
                fwrite(&acc, sizeof(acc), 1, fp);

                printf("Withdrawal Successful!\n");
            } else {
                printf("Insufficient Balance!\n");
            }
            break;
        }
    }

    fclose(fp);
}

void display() {
    FILE *fp;
    struct account acc;
    int accno;

    fp = fopen("bank.dat", "rb");

    printf("Enter Account Number: ");
    scanf("%d", &accno);

    while(fread(&acc, sizeof(acc), 1, fp)) {
        if(acc.acc_no == accno) {
            printf("\nAccount Number: %d", acc.acc_no);
            printf("\nName: %s", acc.name);
            printf("\nBalance: %.2f\n", acc.balance);
            break;
        }
    }

    fclose(fp);
}