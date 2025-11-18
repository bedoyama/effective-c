#include <stdio.h>
#include <stdlib.h>

typedef enum
{
    Savings,
    Checking,
    MoneyMarket,
    CD
} AccountType;

void assignInterestRate(AccountType account)
{
    double interest_rate;
    switch (account)
    {
    case Savings:
        interest_rate = 3.0;
        break;
    case Checking:
        interest_rate = 1.0;
        break;
    case MoneyMarket:
        interest_rate = 4.5;
        break;
    case CD:
        interest_rate = 7.5;
        break;
    default:
        abort();
    }
    printf("Interest rate = %g.\n", interest_rate);
    return;
}

// Helper function to get account type name
const char *getAccountTypeName(AccountType account)
{
    switch (account)
    {
    case Savings:
        return "Savings";
    case Checking:
        return "Checking";
    case MoneyMarket:
        return "Money Market";
    case CD:
        return "Certificate of Deposit";
    default:
        return "Unknown";
    }
}

// Calculate interest for given principal
void calculateInterest(AccountType account, double principal)
{
    printf("\n=== Calculating Interest ===\n");
    printf("Account type: %s\n", getAccountTypeName(account));
    printf("Principal: $%.2f\n", principal);

    double interest_rate;
    switch (account)
    {
    case Savings:
        interest_rate = 3.0;
        break;
    case Checking:
        interest_rate = 1.0;
        break;
    case MoneyMarket:
        interest_rate = 4.5;
        break;
    case CD:
        interest_rate = 7.5;
        break;
    default:
        printf("Invalid account type!\n");
        return;
    }

    double interest = principal * (interest_rate / 100.0);
    printf("Interest rate: %.1f%%\n", interest_rate);
    printf("Interest earned: $%.2f\n", interest);
    printf("Total: $%.2f\n", principal + interest);
}

int main()
{
    printf("=== Bank Account Interest Rates ===\n\n");

    // Test each account type
    printf("Test 1: All account types\n");
    printf("Savings account: ");
    assignInterestRate(Savings);

    printf("Checking account: ");
    assignInterestRate(Checking);

    printf("Money Market account: ");
    assignInterestRate(MoneyMarket);

    printf("CD account: ");
    assignInterestRate(CD);

    printf("\n");

    // Using enum values directly
    printf("Test 2: Using enum values\n");
    AccountType myAccount = MoneyMarket;
    printf("My account type: %s\n", getAccountTypeName(myAccount));
    assignInterestRate(myAccount);
    printf("\n");

    // Array of account types
    printf("Test 3: Processing multiple accounts\n");
    AccountType accounts[] = {Savings, Checking, MoneyMarket, CD, Savings};
    int num_accounts = sizeof(accounts) / sizeof(accounts[0]);

    for (int i = 0; i < num_accounts; i++)
    {
        printf("Account %d (%s): ", i + 1, getAccountTypeName(accounts[i]));
        assignInterestRate(accounts[i]);
    }
    printf("\n");

    // Calculate actual interest
    printf("Test 4: Interest calculations\n");
    calculateInterest(Savings, 10000.0);
    calculateInterest(Checking, 5000.0);
    calculateInterest(MoneyMarket, 25000.0);
    calculateInterest(CD, 50000.0);

    // Comparison table
    printf("\n=== Interest Rate Comparison ===\n");
    printf("%-20s | %-15s | %-20s\n", "Account Type", "Interest Rate", "$10,000 Annual");
    printf("---------------------|-----------------|---------------------\n");

    AccountType types[] = {Savings, Checking, MoneyMarket, CD};
    double rates[] = {3.0, 1.0, 4.5, 7.5};
    const char *names[] = {"Savings", "Checking", "Money Market", "CD"};

    for (int i = 0; i < 4; i++)
    {
        double interest = 10000.0 * (rates[i] / 100.0);
        printf("%-20s | %13.1f%% | $%17.2f\n", names[i], rates[i], interest);
    }

    // Note about invalid account type
    printf("\n=== Note on Invalid Account Types ===\n");
    printf("The default case calls abort() for invalid account types.\n");
    printf("This ensures all enum values are handled explicitly.\n");
    printf("Uncommenting the line below would trigger abort():\n");
    printf("// assignInterestRate((AccountType)999);\n");

    return EXIT_SUCCESS;
}
