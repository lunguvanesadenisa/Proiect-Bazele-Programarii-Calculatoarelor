#include <stdio.h>
#include <time.h>
#include <stdlib.h>

struct DiceSide {
	char graphic[3][5];
};

struct Pair {
	int value1;
	int value2;
};

void InitializeDices(struct DiceSide diceSide[6]) {
	char diceOne[3][5] =
	{
		"|---|",
		"|-o-|",
		"|---|"
	};
	memcpy(diceSide[0].graphic, diceOne, sizeof(char) * 3 * 5);
	char diceTwo[3][5] =
	{
		"|-o-|",
		"|---|",
		"|-o-|"
	};
	memcpy(diceSide[1].graphic, diceTwo, sizeof(char) * 3 * 5);
	char diceThree[3][5] =
	{
		"|-o-|",
		"|-o-|",
		"|-o-|"
	};
	memcpy(diceSide[2].graphic, diceThree, sizeof(char) * 3 * 5);
	char diceFour[3][5] =
	{
		"|o-o|",
		"|---|",
		"|o-o|"
	};
	memcpy(diceSide[3].graphic, diceFour, sizeof(char) * 3 * 5);
	char diceFive[3][5] =
	{
		"|o-o|",
		"|-o-|",
		"|o-o|"
	};
	memcpy(diceSide[4].graphic, diceFive, sizeof(char) * 3 * 5);
	char diceSix[3][5] =
	{
		"|o-o|",
		"|o-o|",
		"|o-o|"
	};
	memcpy(diceSide[5].graphic, diceSix, sizeof(char) * 3 * 5);
}

void PrintDice(struct DiceSide diceSide[6], int roll) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 5; j++) {
			printf_s("%c", diceSide[roll - 1].graphic[i][j]);
		}
		printf_s("\n");
	}
}

void DisplayPlayersStatus(long* playerScores, int playerCount) {
	for (int i = 0; i < playerCount; i++) {
		printf("Player %d: %d      ", i + 1, playerScores[i]);
	}
	printf("\n");
}

void DisplayGameStatus(struct Pair dicePair, long* playerScores, int playerCount, struct DiceSide diceSide[6]) {
	PrintDice(diceSide, dicePair.value1);
	printf_s("\n");
	PrintDice(diceSide, dicePair.value2);
	printf_s("\n");
	DisplayPlayersStatus(playerScores, playerCount);
}

struct Pair RollDice() {
	struct Pair pair;
	pair.value1 = rand() % 6 + 1;
	pair.value2 = rand() % 6 + 1;
	return pair;
}

void ShowResult(int* playerScores, int playerCount) {
	int maxScorePlayer;
	int maxScore;
	maxScorePlayer = 0;
	maxScore = playerScores[0];
	for (int i = 0; i < playerCount; i++) {
		printf("Player %d rolled: %d\n", i + 1, playerScores[i]);
		if (maxScore < playerScores[i]) {
			maxScorePlayer = i;
			maxScore = playerScores[i];
		}
	}
	printf("Player %d won, score: %d\n", maxScorePlayer + 1, maxScore);
}

void RunGame(int playerCount, struct DiceSide diceSide[6]) {
	int gameFinished = 0, currentPlayer = 0, current=1;
	struct Pair dicePair;
	long* playerScores;
	playerScores = (long*)calloc(playerCount, sizeof(long));
	while (!gameFinished) {
		printf("Player %d: Press any key to roll the dice\n", current);
		current++;
		getch();
		dicePair = RollDice();
		playerScores[currentPlayer] = dicePair.value1 + dicePair.value2;
		DisplayGameStatus(dicePair, playerScores, playerCount, diceSide);
		currentPlayer++;
		if (currentPlayer > playerCount - 1) {
			ShowResult(playerScores, playerCount);
			gameFinished = 1;
		}
	}
}

void StartGame() {
	srand(time(NULL));
	struct DiceSide diceSide[6];
	InitializeDices(diceSide);
	int playerCount;
	scanf_s("%d", &playerCount);
	RunGame(playerCount, diceSide);
}

int main() {
	printf("Enter the number of players: ");
	StartGame();
}
