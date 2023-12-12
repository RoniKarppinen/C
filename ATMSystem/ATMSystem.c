#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_PIN 5
#define MAX_ACC_NUMBER 6


void readTrash(void);
void readString(char * string, int size);
void quitScreen();
void startScreen(double balance);
void checkPincode(char correctCode[MAX_PIN]);
void handleUserAction(double *balance);
void checkBalance(double *balance);
void withdrawBalance(double *balance);
void withdrawNotes(double withdrawamount);
void readAccNumber(double *balance);


int main(void) {
    double balance = 0.0;

    readAccNumber(&balance);

    startScreen(balance);

    quitScreen();

    return 0;
}

/* readTrash - Reads the user input and
* If the user input is the newline character ('\n'),
* the loop stops and clears the buffer.
* If the user input isn't the newline character,
* the loop continues and buffers the new characters.
*
* Parameters:
* - (void): It doesn't take anything as a parameter.
*
* Return (void): Function doesn't return anything.
*/

void readTrash(void) {
    while (fgetc(stdin) != '\n');
}

/* readString - Asks for the string and
* the size of the string.
* After that function goes through the
* characters and if the character is
* newline character, it changes it to
* null character, so the string is
* handled properly.
* If the character isn't newline
* character, the function uses
* the readTrash function to clear
* the input buffer.
*
* Parameters:
* - string (char): Takes the given string as a parameter.
* - size (int): Asks for the size of the string.
*
* Return (void): Function doesn't return anything.
*/

void readString(char * string, int size) {
    fgets(string, size, stdin);
    if(string[strlen(string) - 1] == '\n') {
        string[strlen(string) - 1] = '\0';
    } else {
        readTrash();
    }
}

/* quitScreen - Function prints
* the two separate messages to two
* different lines and stops 
* the program.
*
* Parameters:
* None - Function has no parameters.
*
* Return (void): Function doesn't return anything.
*/

void quitScreen() {
    printf("\nKiitos kaynnista! \nTervetuloa uudestaan");
    exit(EXIT_SUCCESS);
}

/* startScreen - Function prints
* the options that the user has on
* different lines.
* With the first choice, user can
* check the account balance
* and this functionality utilizes
* checkBalance() -method.
* With second choice, user can
* withdraw money from the account
* utilizing withdrawBalance() 
* -method. Third choice terminates 
* the program and utilizes the
* quitScreen() - method.
*
* Parameters:
* - balance (double): The attribute that
* will be used for the calling function and 
* it contains the user's account balance.
*
* Return (void): Function doesn't return anything.
*/

void startScreen(double balance) {
    int action;
    do {
        printf("\nOlet paavalikossa, valitse toiminto: \n1. Saldo \n2. Otto \n3. Lopeta\nValitse toiminto >");
        scanf("%d", &action);
        switch (action){
            case 1:
                checkBalance(&balance);
                break;
            case 2:
                withdrawBalance(&balance);
                break;
            case 3:
                quitScreen();
                break;
            default:
                printf("Ole hyva ja valitse luku yhden ja kolmen valilta.\n");
                break;
        }
    } while(action != 3);
}

/* checkPincode - Function prints
* the welcome messages and asks for the
* pincode. If the pincode isn't correct,
* function prints the error message and it
* will ask for it three times.
* If the code isn't inputted correctly
* after three tries, the program will
* be terminated.
*
* Parameters:
* - correctCode (char): The attribute
* which the program compares the
* inputted values.
*
* Return (void): Function doesn't return anything.
*/

void checkPincode(char correctCode[MAX_PIN]) {
    int tries = 3;
    char pincode[MAX_PIN];
    printf("\nNappaile tunnusluku > ");
    readString(pincode, MAX_PIN);
    while(strcmp(pincode, correctCode) != 0 && tries > 0) {
        tries--;
        if(tries == 0) {
            printf("\nTunnusluku on vaarin, ohjelma suljetaan kolmen vaaran yrityksen jalkeen\nYrita myohemmin uudestaan!");
            exit(EXIT_FAILURE);
        }
        printf("\nTunnusluku on vaarin, syota nelinumeroinen luku.\nSinulla on %d yritysta.\nYrita uudestaan >", tries);
        readString(pincode, MAX_PIN);
    }
}

/* handleUserAction - Function
* handles the user choices after the 
* user has done the chosen action.
* Function prints the two options
* which are to go back to start screen
* or quit the program.
* Function utilizes the quitScreen() 
* and startScreen() - methods.
*
* Parameters:
* - balance (double): The attribute that
* will be used for the calling function and 
* it contains the user's account balance.
*
* Return (void): Function doesn't return anything.
*/

void handleUserAction(double* balance) {
    int action;
    printf("\n1. Palaa aloitusruutuun\n2. Lopeta\nValitse toiminto > ");
    scanf("%d", &action);
    
    switch (action) {
        case 1:
            startScreen(*balance);
            break;
        case 2:
            quitScreen();
            break;
        default:
            printf("\nValitse luku yhden ja kahden valilta");
            break;
    }
}


/* checkBalance - Function checks
* the balance and it will print the
* user balance.
* Function also utilizes the 
* handleUserAction() -method so
* the user will be able to continue or
* quit the program.
*
* Parameters:
* - balance (double): The attribute that
* will be used for the calling function and 
* it contains the user's account balance.
*
* Return (void): Function doesn't return anything.
*/

void checkBalance(double *balance) {
    int action;
    if(*balance >= 0.0) {
        printf("\nTilin saldo: +%.2lf", *balance);
    } else {
        printf("\nTilin saldo: -%.2lf", *balance);
    }
    handleUserAction(balance);
}


/* withdrawBalance - Function allows
* the user to withdraw money, either
* from preset choices or custom sum.
* After the withdraw has been done,
* withdraw sum will be deducted from
* the balance attribute. Function utilizes
* withdrawNotes() -method for withdrawing
* money from user's balance. Also handleUserAction()
* -method will be used for navigating purposes.
*
* Parameters:
* - balance (double): The attribute that
* will be used for the calling function and 
* it contains the user's account balance.
*
* Return (void): Function doesn't return anything.
*/

void withdrawBalance(double *balance) {
    double withdraw = 0;
    double minwithdraw = 20.00;
    double maxwithdraw = 1000.00;
    int action, action2;
    printf("\nValitse summa numeroilla:\n1. 20e\n2. 40e\n3. 60e\n4. 90e\n5. 120e\n6. 240e \n7. Valitse haluamasi summa\n");
    scanf("%d", &action);
    switch (action) {
        case 1:
            withdraw = 20;
            withdrawNotes(withdraw);
            break;
        case 2:
            withdraw = 40;
            withdrawNotes(withdraw);
            break;
        case 3:
            withdraw = 60;
            withdrawNotes(withdraw);
            break;
        case 4:
            withdraw = 90;
            withdrawNotes(withdraw);
            break;
        case 5:
            withdraw = 120;
            withdrawNotes(withdraw);
            break;
        case 6:
            withdraw = 240;
            withdrawNotes(withdraw);
            break;
        case 7:
            printf("\nSyota nostettava summa: ");
            scanf("%lf", &withdraw);
            if (withdraw < minwithdraw) {
                printf("\nPienin nostettava summa on 20 euroa.\nYrita uudelleen > ");
                scanf("%lf", &withdraw);
            } else if (withdraw > maxwithdraw) {
                printf("\nSuurin nostettava summa on 1000 euroa.\nYrita uudelleen > ");
                scanf("%lf", &withdraw);
            } else if (withdraw > *balance) {
                printf("\nVarasi eivat riittaneet nostoon\nYrita uudelleen > ");
                scanf("%lf", &withdraw);
            }
            withdrawNotes(withdraw);
            break;
        default:
            printf("\nValitse luku yhden ja seitseman valilta");
            break;
    }
    *balance -= withdraw;
    printf("\nUusi saldosi on %.2lf\nKiitos kaynnista!", *balance);
    handleUserAction(balance);
}

/* withdrawNotes - Function counts
* the most optimal way to give the
* withdraw sum for the user.
* It prints the amount of notes given
* and is specific which notes and how
* many of those notes.
*
* Parameters:
* - balance (double): The attribute that
* will be used for the calling function and 
* it contains the user's account balance.
*
* Return (void): Function doesn't return anything.
*/


void withdrawNotes(double withdrawamount) {
    int amount = (int)withdrawamount;
    int fifty_notes = 0;
    int twenty_notes = 0;
    if((amount % 50) == 0) {
        fifty_notes =  amount / 50;
    } else if((amount % 50) % 20 == 0) {
        fifty_notes = amount / 50;
        twenty_notes = (amount % 50) / 20;
    } else {
        fifty_notes = (amount / 50) - 1;
        twenty_notes = ((amount - fifty_notes * 50) / 20);
    }

    if(fifty_notes <= 0 && twenty_notes > 0) {
        printf("\nAutomaatti antoi sinulle %d 20 euron seteleita", twenty_notes);
    } else if(twenty_notes <= 0 && fifty_notes > 0) {
        printf("\nAutomaatti antoi sinulle %d 50 euron seteleita", fifty_notes);
    } else {
        printf("\nAutomaatti antoi sinulle %d kpl 50 euron seteleita ja %d kpl 20 euron seteleita", fifty_notes, twenty_notes);
    }
}

/* readAccnumber - Function asks for
* the account number and searches a
* filed named after the inputted number.
* If file isn't found, the user has three
* tries to get the account number right.
* Otherwise the program will be terminated.
* If the file is found, the program will
* read the pincode from first line and 
* balance from the second line. 
* Function asks for the pincode and if 
* the inputted pincode matches the correct
* pincode, the user will be navigated to
* the start screen. 
*
* Parameters:
* - balance (double): The attribute that
* will be used for the calling function and 
* it contains the user's account balance.
*
* Return (void): Function doesn't return anything.
*/

void readAccNumber(double *balance) {
    char accountNumber[MAX_ACC_NUMBER];
    char correctPinCode[MAX_PIN];
    int tries = 3;
    FILE *account;
    printf("\nTervetuloa!");
    printf("\nSyota tilin numero > ");
    readString(accountNumber, MAX_ACC_NUMBER);

    strcat(accountNumber, ".acc");
    account = fopen(accountNumber, "r");
    while (account == NULL && tries > 0) {
        tries--;
        if(tries == 0) {
            printf("\nTilia ei loytynyt, kokeile myohemmin uudestaan");
            exit(EXIT_FAILURE);
        }
        printf("\nKayttajaa ei loytynyt\nSinulla on viela %d yritysta jaljella\nOle hyva ja yrita uudestaan >", tries);
        readString(accountNumber, MAX_ACC_NUMBER);
    }
    fgets(correctPinCode, sizeof(correctPinCode), account);
    checkPincode(correctPinCode);

    fscanf(account, "%lf", balance);

    fclose(account);
}