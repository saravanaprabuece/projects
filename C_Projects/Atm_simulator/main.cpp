#include <stdio.h>

int main() {
    float balance = 1000.00;  // Initial balance
    int choice;
    float amount;

    while (1) {
        // Display ATM Menu
        printf("\n--- Banking ATM Simulator ---\n");
        printf("1. Check Balance\n");
        printf("2. Deposit Money\n");
        printf("3. Withdraw Money\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // Check Balance
                printf("\nYour current balance is: $%.2f\n", balance);
                break;

            case 2:
                // Deposit Money
                printf("\nEnter the amount to deposit: $");
                scanf("%f", &amount);
                if (amount > 0) {
                    balance += amount;
                    printf("Deposit successful! New balance: $%.2f\n", balance);
                } else {
                    printf("Invalid amount. Please enter a positive value.\n");
                }
                break;

            case 3:
                // Withdraw Money
                printf("\nEnter the amount to withdraw: $");
                scanf("%f", &amount);
                if (amount > 0 && amount <= balance) {
                    balance -= amount;
                    printf("Withdrawal successful! New balance: $%.2f\n", balance);
                } else if (amount > balance) {
                    printf("Insufficient balance! Your balance is: $%.2f\n", balance);
                } else {
                    printf("Invalid amount. Please enter a positive value.\n");
                }
                break;

            case 4:
                // Exit
                printf("\nThank you for using the ATM. Goodbye!\n");
                return 0;

            default:
                printf("\nInvalid choice! Please select a valid option.\n");
        }
    }
}
