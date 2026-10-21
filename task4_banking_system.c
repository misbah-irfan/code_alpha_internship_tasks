#include <stdio.h>
#include <string.h>

#define FILE_NAME "accounts.dat"

typedef struct {
    int accNo;
    char name[50];
    int pin;
    double balance;
} Account;

void clearInput(void) {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {}
}

/* Returns record index of account, or -1 if not found. Fills *acc. */
int findAccount(int accNo, Account *acc) {
    FILE *fp = fopen(FILE_NAME, "rb");
    Account a;
    int idx = 0;
    if (!fp) return -1;
    while (fread(&a, sizeof(Account), 1, fp) == 1) {
        if (a.accNo == accNo) { *acc = a; fclose(fp); return idx; }
        idx++;
    }
    fclose(fp);
    return -1;
}

void saveAccount(int idx, const Account *acc) {
    FILE *fp = fopen(FILE_NAME, "rb+");
    if (!fp) return;
    fseek(fp, (long)idx * sizeof(Account), SEEK_SET);
    fwrite(acc, sizeof(Account), 1, fp);
    fclose(fp);
}

void createAccount(void) {
    Account a, tmp;
    printf("Enter new account number: ");
    if (scanf("%d", &a.accNo) != 1) { clearInput(); printf("Invalid input.\n"); return; }
    clearInput();
    if (findAccount(a.accNo, &tmp) != -1) { printf("Account already exists.\n"); return; }
    printf("Account holder name: ");
    fgets(a.name, sizeof a.name, stdin);
    a.name[strcspn(a.name, "\n")] = '\0';
    printf("Set 4-digit PIN: ");
    if (scanf("%d", &a.pin) != 1) { clearInput(); printf("Invalid input.\n"); return; }
    clearInput();
    a.balance = 0.0;
    FILE *fp = fopen(FILE_NAME, "ab");
    if (!fp) { printf("Cannot open file.\n"); return; }
    fwrite(&a, sizeof(Account), 1, fp);
    fclose(fp);
    printf("Account created successfully.\n");
}

/* Asks for account number + PIN; returns index or -1 */
int login(Account *acc) {
    int accNo, pin;
    printf("Account number: ");
    if (scanf("%d", &accNo) != 1) { clearInput(); return -1; }
    printf("PIN: ");
    if (scanf("%d", &pin) != 1) { clearInput(); return -1; }
    clearInput();
    int idx = findAccount(accNo, acc);
    if (idx == -1 || acc->pin != pin) {
        printf("Invalid account number or PIN.\n");
        return -1;
    }
    return idx;
}

void deposit(void) {
    Account a;
    int idx = login(&a);
    if (idx == -1) return;
    double amt;
    printf("Amount to deposit: ");
    if (scanf("%lf", &amt) != 1 || amt <= 0) { clearInput(); printf("Invalid amount.\n"); return; }
    clearInput();
    a.balance += amt;
    saveAccount(idx, &a);
    printf("Deposited %.2f. New balance: %.2f\n", amt, a.balance);
}

void withdraw(void) {
    Account a;
    int idx = login(&a);
    if (idx == -1) return;
    double amt;
    printf("Amount to withdraw: ");
    if (scanf("%lf", &amt) != 1 || amt <= 0) { clearInput(); printf("Invalid amount.\n"); return; }
    clearInput();
    if (amt > a.balance) { printf("Insufficient balance.\n"); return; }
    a.balance -= amt;
    saveAccount(idx, &a);
    printf("Withdrawn %.2f. New balance: %.2f\n", amt, a.balance);
}

void balanceEnquiry(void) {
    Account a;
    if (login(&a) == -1) return;
    printf("Account Holder: %s\nBalance: %.2f\n", a.name, a.balance);
}

int main(void) {
    int choice;
    do {
        printf("\n===== Bank Account Management =====\n");
        printf("1. Create Account\n2. Deposit\n3. Withdraw\n4. Balance Enquiry\n5. Exit\n");
        printf("Enter choice: ");
        if (scanf("%d", &choice) != 1) { clearInput(); choice = 0; }
        else clearInput();
        switch (choice) {
            case 1: createAccount();  break;
            case 2: deposit();        break;
            case 3: withdraw();       break;
            case 4: balanceEnquiry(); break;
            case 5: printf("Thank you for banking with us!\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 5);
    return 0;
}
