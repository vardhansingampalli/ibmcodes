#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to hold account information
typedef struct {
    int accountNumber;
    int pin;
    char name[100];
    float balanceINR;
    float balanceUSD;
} Account;

int main() {
    // Initialize accounts
    Account accounts[4] = {
        {1, 1234, "ykb", 10000.0, 0.0},
        {2, 1234, "mukhesh", 20000.0, 0.0},
        {3, 1234, "charan", 30000.0, 0.0},
        {4, 1234, "girish", 40000.0, 0.0}
    };

    // Save accounts to file
    FILE *file = fopen("accounts.dat", "wb");
    if (file != NULL) {
        fwrite(accounts, sizeof(Account), 4, file);
        fclose(file);
    } else {
        printf("Error opening file.\n");
        return 1;
    }

    printf("Accounts saved to file.\n");
    return 0;
}
*/




#include <stdio.h>
#include <stdlib.h>

// Structure to hold account information
typedef struct {
    int accountNumber;
    int pin;
    char name[100];
    float balanceINR;
    float balanceUSD;
} Account;

// Function to display account details
void displayDetails(Account account) {
    printf("Account Number: %d\n", account.accountNumber);
    printf("Name: %s\n", account.name);
    printf("Balance: %.2f INR, %.2f USD\n", account.balanceINR, account.balanceUSD);
}

// Function to withdraw amount
void withdraw(Account *account, float amount, char currency) {
    if (currency == 'I') {
        if (account->balanceINR >= amount) {
            account->balanceINR -= amount;
            printf("Withdrawal successful. New balance: %.2f INR\n", account->balanceINR);
        } else {
            printf("Insufficient INR balance.\n");
        }
    } else if (currency == 'U') {
        if (account->balanceUSD >= amount) {
            account->balanceUSD -= amount;
            printf("Withdrawal successful. New balance: %.2f USD\n", account->balanceUSD);
        } else {
            printf("Insufficient USD balance.\n");
        }
    }
}

// Function to deposit amount
void deposit(Account *account, float amount, char currency) {
    if (currency == 'I') {
        account->balanceINR += amount;
        printf("Deposit successful. New balance: %.2f INR\n", account->balanceINR);
    } else if (currency == 'U') {
        account->balanceUSD += amount;
        printf("Deposit successful. New balance: %.2f USD\n", account->balanceUSD);
    }
}

// Function to transfer amount
void transfer(Account *fromAccount, Account *toAccount, float amount, char fromCurrency, char toCurrency) {
    if (fromCurrency == 'I' && toCurrency == 'I') {
        if (fromAccount->balanceINR >= amount) {
            fromAccount->balanceINR -= amount;
            toAccount->balanceINR += amount;
            printf("Transfer successful. New balance: %.2f INR\n", fromAccount->balanceINR);
        } else {
            printf("Insufficient INR balance in source account.\n");
        }
    } else if (fromCurrency == 'U' && toCurrency == 'U') {
        if (fromAccount->balanceUSD >= amount) {
            fromAccount->balanceUSD -= amount;
            toAccount->balanceUSD += amount;
            printf("Transfer successful. New balance: %.2f USD\n", fromAccount->balanceUSD);
        } else {
            printf("Insufficient USD balance in source account.\n");
        }
    }
}

// Function to convert currency
void convertCurrency(Account *account, float amount, char fromCurrency) {
    float rate = 83.0; // 1 USD = 83 INR
    if (fromCurrency == 'I') {
        if (account->balanceINR >= amount) {
            account->balanceINR -= amount;
            account->balanceUSD += amount / rate;
            printf("Currency conversion successful. New balance: %.2f INR, %.2f USD\n", account->balanceINR, account->balanceUSD);
        } else {
            printf("Insufficient INR balance.\n");
        }
    } else if (fromCurrency == 'U') {
        if (account->balanceUSD >= amount) {
            account->balanceUSD -= amount;
            account->balanceINR += amount * rate;
            printf("Currency conversion successful. New balance: %.2f INR, %.2f USD\n", account->balanceINR, account->balanceUSD);
        } else {
            printf("Insufficient USD balance.\n");
        }
    }
}

// Function to load accounts from file
void loadAccounts(Account *accounts, int numAccounts) {
    FILE *file = fopen("accounts.dat", "rb");
    if (file != NULL) {
        fread(accounts, sizeof(Account), numAccounts, file);
        fclose(file);
    }
}

// Function to save accounts to file
void saveAccounts(Account *accounts, int numAccounts) {
    FILE *file = fopen("accounts.dat", "wb");
    if (file != NULL) {
        fwrite(accounts, sizeof(Account), numAccounts, file);
        fclose(file);
    }
}

int main() {
    // Initialize accounts
    Account accounts[4];

    // Load accounts from file
    loadAccounts(accounts, 4);

    // Main program loop
    int accountNumber, pin, choice;
    float amount;
    char currency, fromCurrency, toCurrency;
    Account *account = NULL;

    while (1) {
        if (account == NULL) {
            printf("\n");
            printf("\n");
            printf("\t\t\tSMBG BANKING \t\t\t");
            printf("\n");
            printf("\t\t\t------------\t\t\t");
            printf("\n");
            printf("\n");
            printf("WELCOME TO BANKING SYSTEM ");
            printf("\n");
            printf("=========================================================");
            printf("\n");
            printf("\n");
           
            printf("Enter 1 to login or 2 to exit: ");
            scanf("%d", &choice);
            printf("\n");
            if (choice == 2) {
                printf("Thank you");
                printf("\n");
                printf("Exiting...\n");
                printf("=========================================================");

                return 0;
            } else if (choice == 1) {
                printf("Enter account number and pin: ");
                scanf("%d %d", &accountNumber, &pin);

                // Find the account
                for (int i = 0; i < 4; i++) {
                    if (accounts[i].accountNumber == accountNumber && accounts[i].pin == pin) {
                        account = &accounts[i];
                        break;
                    }
                }

                if (account == NULL) {
                    printf("Invalid account number or pin.\n");
                    continue;
                }
            } else {
                printf("Invalid choice.\n");
                continue;
            }
        }

        // Display account details
        displayDetails(*account);

        // Show options and perform actions
        printf("1. Withdraw\n2. Deposit\n3. Transfer\n4. Convert currency\n5. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter amount to withdraw and currency (I for INR, U for USD): ");
                scanf("%f %c", &amount, &currency);
                withdraw(account, amount, currency);
                break;
            case 2:
                printf("Enter amount to deposit and currency (I for INR, U for USD): ");
                scanf("%f %c", &amount, &currency);
                deposit(account, amount, currency);
                break;
            case 3:
                printf("Enter account number to transfer to, amount, from currency (I for INR, U for USD), and to currency (I for INR, U for USD): ");
                int toAccountNumber;
                scanf("%d %f %c %c", &toAccountNumber, &amount, &fromCurrency, &toCurrency);
                Account *toAccount = NULL;
                for (int i = 0; i < 4; i++) {
                    if (accounts[i].accountNumber == toAccountNumber) {
                        toAccount = &accounts[i];
                        break;
                    }
                }
                if (toAccount != NULL) {
                    transfer(account, toAccount, amount, fromCurrency, toCurrency);
                } else {
                    printf("Invalid account number.\n");
                }
                break;
            case 4:
                printf("Enter amount to convert and from currency (I for INR, U for USD): ");
                scanf("%f %c", &amount, &fromCurrency);
                convertCurrency(account, amount, fromCurrency);
                break;
            case 5:
                printf("Logging out...\n");
                account = NULL;
                break;
            default:
                printf("Invalid choice.\n");
        }

        // Save accounts to file
        saveAccounts(accounts, 4);
    }

    return 0;
}

