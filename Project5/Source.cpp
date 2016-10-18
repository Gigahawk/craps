#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define MIN_BET 5

//prototypes
int getWallet(void);
int makeBet(int wallet);
bool playRound(void);
bool doAgain(void);
void goodbye(int wallet);
bool rollForPoint(int point);
int rollDice(void);
int rollDie(void);
void printResult(bool won);

int main(void){
	srand(time(NULL));
	int money, bet;
	bool won;

	money = getWallet();

	do{
		printf("You have $%d in your wallet.\n", money);
		bet = makeBet(money);
		won = playRound();
		if (won){
			money += bet;
		}
		else{
			money -= bet;
		}

		printResult(won);

	} while (doAgain() && money >= MIN_BET);

	goodbye(money);

	system("PAUSE");

	return 0;
}

/* Function: getWallet
* Prompts the user for the amount of money they have to play with – assumed to be
* measured in whole dollars. Rejects values that are not at least MIN_BET in size and
* prompts for another value until a value of size MIN_BET or greater is entered.
* Returns: amount of money entered by user (a positive, integer dollar value)
*/
int getWallet(void){
	int money;
	printf("How much money do you have to play with?\n");
	scanf("%d", &money);
	while (money < MIN_BET){
		printf("get ya broke ass outta hea. Now...\n");
		printf("How much money do you have to play with?\n");
		scanf("%d", &money);
	} 

	return money;
}

/* Function: makeBet
* Prompts user to make a bet (minimum value: MIN_BET; maximum value: amount in wallet).
* Keeps prompting user until a value of at least MIN_BET but no more than amount
* in wallet is entered.
* Parameter: wallet - the amount in the user's wallet
* Returns: user's bet (minimum MIN_BET)
*/
int makeBet(int wallet){
	int bet;
	printf("Place your bet (minimum $5): ");
	scanf("%d", &bet);
	while (bet<MIN_BET || bet > wallet){
		printf("get ya broke ass outta hea. Now...\n");
		printf("Place your bet (minimum $5): ");
		scanf("%d", &bet);
	} 
	return bet;
}

/* Function: playRound
* Plays a single round of craps with the user.
* Returns: true if user won round, false otherwise.
*/
bool playRound(void){
	int point;
	bool won;

	point = rollDice();

	if (point == 2 || point == 3 || point == 12){
		won = false;
		return won;
	}
	else if (point == 7 || point == 11){
		won = true;
		return won;
	}

	printf("\nRolling for point: %d...\n", point);
	won = rollForPoint(point);

	return won;
}

/* Function: printResult
* Prints whether player won or lost
*/
void printResult(bool won){
	if (won){
		printf("\nYou Won :-)\n");
	}
	else{
		printf("\nYou lose :-(\n");
	}
	return;
}

/* Function: rollForPoint
* Repeatedly rolls dice until either the point value or the value 7 is rolled.
* Parameter: point - the current point value
* Returns: true if user rolled point value before rolling a 7 (user won round),
* false otherwise (user lost round)
*/
bool rollForPoint(int point){
	int roll = -1;
	while (!(roll == 7 || roll == point)){
		roll = rollDice();
	}
	if (roll == 7){
		return false;
	}
	else{
		return true;
	}
}


/* Function: rollDice
* Rolls a pair of dice.
* Returns: sum of face values rolled
*/
int rollDice(void){
	int dice = 0;
	dice += rollDie();
	dice += rollDie();
	printf("You rolled a %d.\n", dice);
	return dice;
}

/* Function: rollDie
* Rolls a single die.
* Returns: face value rolled
*/
int rollDie(void){
	int die;
	die = 1 + rand() % 6;
	return die;
}

/* Function: doAgain
* Ask user if they want to play again.
* Returns: true if user wants to play again, false otherwise.
*/
bool doAgain(void){
	int playagain;
	do{
		printf("Enter 1 to play again, 0 to quit:\n");
		scanf("%d", &playagain);
	} while (!(playagain == 0 || playagain == 1));

	return playagain;
}

/* Function: goodbye
* Prints goodbye message to user based on whether or not they
* went broke while playing the game. Tells the user they're broke
* if they have less than MIN_BET in their wallet, otherwise tells
* them how much they have in their wallet.
* Parameter: wallet - amount of money in wallet
*/

void goodbye(int wallet){
	if (wallet>MIN_BET){
		printf("You have $%d left in your wallet. Goodbye!\n",wallet);
	}
	else {
		printf("YA BROKE\n");
	}
	return;
}