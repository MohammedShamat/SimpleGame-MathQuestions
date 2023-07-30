#include <iostream>
#include<string>
#include<cstdlib>

using namespace std;
enum enLevels {
	Easy = 1, Med = 2, Hard = 3, Mix = 4,
};
enum enOperationsType {
	Add = 1, Sub = 2, Mul = 3, Div = 4, MixOp = 5,
};
enum enFinalResults {
	Pass = 1, Fail = 2,
};
struct QuestionInfo {

	short numberOfQuestion = 1;
	float firstNumber = 0;
	float secondNumber = 0;
	float rightAnswer;
	short answerFromUser;
	enOperationsType operationType;




};
struct FinalResults {
	short rightAnswers;
	short worngAnswers;
	short numberOfQuestions;
	enOperationsType operationType;
	enLevels typeOfLevel;
	enFinalResults failOrPass;

};
float readAnswerFromUser() {
	float answer = 0;
	cout << endl;
	cin >> answer;
	while (cin.fail()) {
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "Invalid Number, Enter a valid one\n";
		cin >> answer;
	}
	return answer;
}
bool resultEachQuestion(short rightAnswer, short answerFromUser) {
	if (rightAnswer == answerFromUser) {
		return true;
	}
	else
		return false;
}
short ReadHowManyQuestions() {
	short questions = 1;
	cout << "How Many Questions do you want to answer ?  ";
	cin >> questions;
	while (cin.fail() || questions <= 0) {
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "Invalid Number, Enter a valid one\n";
		cin >> questions;
	}
	return questions;
}
float randomNumber(short from, short to) {
	return rand() % (to - from + 1) + from;;
}
enLevels ReadQuestionsLevel() {
	short level = 1;
	cout << "Enter Questions Level [1] Easy,[2] Med,[3] Hard,[4] Mix ?  ";
	cin >> level;
	while (cin.fail() || (level <= 0 || level > 4)) {
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "Invalid Number, Enter a valid one\n";
		cin >> level;
	}
	return (enLevels)level;
}
enOperationsType ReadOperationType() {
	short OperationType = 1;
	cout << "Enter Operation Type [1] Add,[2] Sub,[3] Mul,[4] Div,[5] Mix ?  ";
	cin >> OperationType;
	while (cin.fail() || (OperationType <= 0 || OperationType > 5)) {
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "Invalid Number, Enter a valid one\n";
		cin >> OperationType;
	}
	return (enOperationsType)OperationType;
}
short fillNumberByDifficultylevel(enLevels numberRange) {

	switch (numberRange)
	{
	case enLevels::Easy:
		return randomNumber(1, 20);

	case enLevels::Med:
		return randomNumber(10, 50);

	case enLevels::Hard:
		return randomNumber(50, 100);

	case enLevels::Mix:
		return randomNumber(1, 100);

	}
}
string mixOperationChar(short mixCase) {
	short randomOperation = mixCase;
	enOperationsType operationType;
	operationType = (enOperationsType)randomOperation;

	switch (operationType)
	{
	case enOperationsType::Add:
		return "+";
		break;
	case enOperationsType::Sub:
		return "-";
		break;
	case enOperationsType::Mul:
		return  "*";
		break;
	case enOperationsType::Div:
		return  "/";
		break;

	}
}
string operationType(enOperationsType operationType, short mixCase) {

	switch (operationType)
	{
	case enOperationsType::Add:
		return  "+";
		break;
	case enOperationsType::Sub:
		return  "-";
		break;
	case enOperationsType::Mul:
		return  "*";
		break;
	case enOperationsType::Div:
		return  "/";
		break;
	case enOperationsType::MixOp:
		return mixOperationChar(mixCase);
		break;
	}
}
float mixOperation(float firstNumber, float secondNumber, short mixCase) {
	short randomOperation = mixCase;
	enOperationsType operationType;
	operationType = (enOperationsType)randomOperation;
	switch (operationType)
	{
	case enOperationsType::Add:
		return firstNumber + secondNumber;
		break;
	case enOperationsType::Sub:
		return firstNumber - secondNumber;
		break;
	case enOperationsType::Mul:

		return firstNumber * secondNumber;
		break;
	case enOperationsType::Div:
		return  firstNumber / secondNumber;
		break;

	}
}
float rightAnswer(float firstNumber, float secondNumber, enOperationsType operationType, short mixCase) {

	switch (operationType)
	{
	case enOperationsType::Add:
		return firstNumber + secondNumber;
		break;
	case enOperationsType::Sub:
		return firstNumber - secondNumber;
		break;
	case enOperationsType::Mul:
		return firstNumber * secondNumber;
		break;
	case enOperationsType::Div:
		return  firstNumber / secondNumber;
		break;
	case enOperationsType::MixOp:

		return mixOperation(firstNumber, secondNumber, mixCase);
		break;

	}


}
void setScreenColor(bool byResult) {
	if (byResult) {
		system("color 2f");
	}
	else {
		cout << "\a";
		system("color 4F");
	}

}
string resutlEachRound(bool result, float rightAnswer) {
	if (result) {
		setScreenColor(result);
		return "Right Answer :-)\n";
	}
	else {
		setScreenColor(result);
		return "Worng Answer:-(\nThe right answer is :" + to_string(rightAnswer) + "\n";
	}
}
enFinalResults passOrFail(short rightAnswers, short worngAnswers) {
	if (rightAnswers > worngAnswers) {
		return	enFinalResults::Pass;
	}
	else {
		return enFinalResults::Fail;
	}
}
FinalResults playGame(short countOfQuestion, enLevels questionsLevels, enOperationsType opType) {
	FinalResults finalResult;
	QuestionInfo question;
	short rightAnswers = 0, wrongeAnswers = 0;


	bool resutl;
	for (short Ques = 1; Ques <= countOfQuestion; Ques++) {
		short randomOperation = randomNumber(1, 4);

		cout << "\nQuestions [" << Ques << "/" << countOfQuestion << "]\n";
		question.firstNumber = fillNumberByDifficultylevel(questionsLevels);
		question.secondNumber = fillNumberByDifficultylevel(questionsLevels);
		question.operationType = opType;
		cout << question.firstNumber << endl;
		cout << question.secondNumber << " " << operationType(opType, randomOperation) << "\n";
		cout << "_______________\n";
		question.answerFromUser = readAnswerFromUser();
		question.rightAnswer = rightAnswer(question.firstNumber, question.secondNumber, opType, randomOperation);
		resutl = resultEachQuestion(question.rightAnswer, question.answerFromUser);
		cout << resutlEachRound(resutl, question.rightAnswer);
		if (resutl) {
			rightAnswers++;
		}
		else {
			wrongeAnswers++;
		}

	}

	finalResult.rightAnswers = rightAnswers;
	finalResult.worngAnswers = wrongeAnswers;
	finalResult.numberOfQuestions = countOfQuestion;
	finalResult.typeOfLevel = questionsLevels;
	finalResult.operationType = opType;
	finalResult.failOrPass = passOrFail(finalResult.rightAnswers, finalResult.worngAnswers);
	return finalResult;
}
string printPassOrFail(enFinalResults passOrFail) {
	switch (passOrFail)
	{
	case enFinalResults::Pass:
		return "PASS  :-)";
		break;
	case enFinalResults::Fail:
		return "FAIL  :-(";
		break;

	}
}
string printQuestionslevel(enLevels questionslevel) {
	switch (questionslevel)
	{
	case enLevels::Easy:
		return "Easy";
		break;
	case enLevels::Med:
		return "Med";
		break;
	case enLevels::Hard:
		return "Hard";
		break;
	case enLevels::Mix:
		return "Mix";
		break;

	}
}
string printOpType(enOperationsType opType) {
	switch (opType)
	{
	case enOperationsType::Add:
		return "Add (+)";
		break;
	case enOperationsType::Sub:
		return "Sub (-)";
		break;
	case enOperationsType::Mul:
		return "Mul (*)";
		break;
	case enOperationsType::Div:
		return "Div (/)";
		break;
	case enOperationsType::MixOp:
		return "Mix (+,-,*,/)";
		break;

	}
}
void resetScreen() {
	system("color 0F");
	system("cls");

}
void printFinalResults(FinalResults finalResult) {
	cout << "\n_____________________________________\n\n";
	cout << "  Final Results is " << printPassOrFail(finalResult.failOrPass) << "\n";
	cout << "_____________________________________\n\n";
	cout << "Number Of Questions     :" << finalResult.numberOfQuestions << endl;
	cout << "Questions levels        :" << printQuestionslevel(finalResult.typeOfLevel) << endl;
	cout << "Operation Type          :" << printOpType(finalResult.operationType) << endl;
	cout << "Number of right answers :" << finalResult.rightAnswers << endl;
	cout << "Number of wrong answers :" << finalResult.worngAnswers << endl;
	cout << "\n_____________________________________\n\n";

}
void startGame() {
	char restart;
	do {
		resetScreen();
		short howManyQuestions = ReadHowManyQuestions();
		enLevels questionsLevels = ReadQuestionsLevel();
		enOperationsType opType = ReadOperationType();
		FinalResults finalResults = playGame(howManyQuestions, questionsLevels, opType);
		printFinalResults(finalResults);
		cout << endl << "Do you Want to play again ? Y/N ";
		cin >> restart;
	} while (restart == 'y' || restart == 'Y');
}
int main() {

	srand((unsigned)time(NULL));
	startGame();

	return 0;

}/*
How Many Questions do you want to answer ?  csd
Invalid Number, Enter a valid one
-99
Invalid Number, Enter a valid one
0
Invalid Number, Enter a valid one
3
Enter Questions Level [1] Easy,[2] Med,[3] Hard,[4] Mix ?  ddaa
Invalid Number, Enter a valid one
5
Invalid Number, Enter a valid one
0
Invalid Number, Enter a valid one
-99
Invalid Number, Enter a valid one
1
Enter Operation Type [1] Add,[2] Sub,[3] Mul,[4] Div,[5] Mix ?  6
Invalid Number, Enter a valid one
0
Invalid Number, Enter a valid one
-99
Invalid Number, Enter a valid one
aad
Invalid Number, Enter a valid one
1

Questions [1/3]
14
17 +
_______________

36
Worng Answer:-(
The right answer is :31.000000

Questions [2/3]
17
5 +
_______________

22
Right Answer :-)

Questions [3/3]
3
11 +
_______________

14
Right Answer :-)

_____________________________________

  Final Results is PASS  :-)
_____________________________________

Number Of Questions     :3
Questions levels        :Easy
Operation Type          :Add (+)
Number of right answers :2
Number of wrong answers :1

_____________________________________


Do you Want to play again ? Y/N

Or

How Many Questions do you want to answer ?  dd
Invalid Number, Enter a valid one
-99
Invalid Number, Enter a valid one
0
Invalid Number, Enter a valid one
5
Enter Questions Level [1] Easy,[2] Med,[3] Hard,[4] Mix ?  6
Invalid Number, Enter a valid one
0
Invalid Number, Enter a valid one
eee
Invalid Number, Enter a valid one
1
Enter Operation Type [1] Add,[2] Sub,[3] Mul,[4] Div,[5] Mix ?  6
Invalid Number, Enter a valid one
0
Invalid Number, Enter a valid one
eee
Invalid Number, Enter a valid one
5

Questions [1/5]
14
10 -
_______________

4
Right Answer :-)

Questions [2/5]
7
9 +
_______________

16
Right Answer :-)

Questions [3/5]
12
2 *
_______________

24
Right Answer :-)

Questions [4/5]
9
18 -
_______________

-9
Right Answer :-)

Questions [5/5]
5
15 +
_______________

20
Right Answer :-)

_____________________________________

  Final Results is PASS  :-)
_____________________________________

Number Of Questions     :5
Questions levels        :Easy
Operation Type          :Mix (+,-,*,/)
Number of right answers :5
Number of wrong answers :0

_____________________________________


Do you Want to play again ? Y/N
 */