#include<iostream>

using  namespace std;
enum enQuestionsLevel {
	EasyLevel = 1,
	MedLevel = 2,
	HardLevel = 3,
	MixLevel = 4,
};
enum enOperationType {
	Add = 1,
	Sub = 2,
	Mult = 3,
	Div = 4,
	Mix = 5,
};
string GetOpTypeSymbol(enOperationType opType) {
	switch (opType)
	{
	case Add:
		return "+";
	case Sub:
		return "-";
	case Mult:
		return "*";
	case Div:
		return "/";
	case Mix:
		return " Mix (+ / * -)";
	}
}
string GetQuestionLevelText(enQuestionsLevel qyestionLevel) {
	string ArrQuesLevel[4] = { "Easy Level","Med Level","Hard Level","Mix Level" };
	return ArrQuesLevel[qyestionLevel - 1];
}
short RandomNumber(short from, short to) {
	return rand() % (to - from + 1) + from;
}
void SetScreenColor(bool right) {
	if (right) {
		system("color 2f");
	}
	else {
		cout << "\a";
		system("color 4F");
	}
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
	return  questions;
}

enQuestionsLevel ReadQuestionsLevel() {
	short level = 1;
	cout << "Enter Questions Level [1] Easy,[2] Med,[3] Hard,[4] Mix ?  ";
	cin >> level;
	while (cin.fail() || (level <= 0 || level > 4)) {
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "Invalid Number, Enter a valid one\n";
		cin >> level;
	}
	return (enQuestionsLevel)level;
}
enOperationType ReadOpType() {
	short OperationType = 1;
	cout << "Enter Operation Type [1] Add,[2] Sub,[3] Mul,[4] Div,[5] Mix ?  ";
	cin >> OperationType;
	while (cin.fail() || (OperationType <= 0 || OperationType > 5)) {
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "Invalid Number, Enter a valid one\n";
		cin >> OperationType;
	}
	return (enOperationType)OperationType;
}
struct stQuestion {
	short number1 = 0;
	short number2 = 0;
	enOperationType operationType;
	enQuestionsLevel questionLevel;
	short correctAnswer = 0;
	short playAnswer = 0;
	bool answerResult = false;
};
struct stQuizz {
	stQuestion questionsList[100];
	short numberOfQuestions;
	enQuestionsLevel questionsLevel;
	enOperationType opType;
	short numberOfWrongAnswers = 0;
	short numberOfRightAnswers = 0;
	bool isPass = false;
};
int SimpleCalculator(int number1, int number2, enOperationType opType) {
	switch (opType)
	{
	case Add:
		return number1 + number2;
	case Sub:
		return number1 - number2;
	case Mult:
		return number1 * number2;
	case Div:
		return number1 / number2;
	}
}
enOperationType GetRandomOperationType() {
	short op = RandomNumber(1, 4);
	return (enOperationType)op;
}
stQuestion GenerateQuestion(enQuestionsLevel quetionLevel, enOperationType opType) {
	stQuestion question;
	if (quetionLevel == enQuestionsLevel::MixLevel) {
		quetionLevel = (enQuestionsLevel)RandomNumber(1, 3);
	}
	if (opType == enOperationType::Mix) {
		opType = GetRandomOperationType();
	}
	question.operationType = opType;

	switch ((quetionLevel))
	{
	case enQuestionsLevel::EasyLevel:

		question.number1 = RandomNumber(1, 10);
		question.number2 = RandomNumber(1, 10);
		question.correctAnswer = SimpleCalculator(question.number1, question.number2, question.operationType);
		question.questionLevel = quetionLevel;
		return question;
	case enQuestionsLevel::MedLevel:
		question.number1 = RandomNumber(10, 50);
		question.number2 = RandomNumber(10, 50);
		question.correctAnswer = SimpleCalculator(question.number1, question.number2, question.operationType);
		question.questionLevel = quetionLevel;
		return question;
	case enQuestionsLevel::HardLevel:
		question.number1 = RandomNumber(50, 100);
		question.number2 = RandomNumber(50, 100);
		question.correctAnswer = SimpleCalculator(question.number1, question.number2, question.operationType);
		question.questionLevel = quetionLevel;
		return question;
	case enQuestionsLevel::MixLevel:
		question.number1 = RandomNumber(1, 100);
		question.number2 = RandomNumber(1, 100);
		question.correctAnswer = SimpleCalculator(question.number1, question.number2, question.operationType);
		question.questionLevel = quetionLevel;
		return question;
	}

	return question;

}
void GenerateQuizzQuestions(stQuizz& quizz) {
	for (short question = 0; question < quizz.numberOfQuestions; question++) {
		quizz.questionsList[question] = GenerateQuestion(quizz.questionsLevel, quizz.opType);
	}
}
short ReadQuestionAnswer() {
	short answer = 0;
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
void PrintTheQuestion(stQuizz& quizz, short questionNumber) {
	cout << "\n";
	cout << "Question [" << questionNumber + 1 << "/" << quizz.numberOfQuestions << "]\n\n";
	cout << quizz.questionsList[questionNumber].number1 << endl;
	cout << quizz.questionsList[questionNumber].number2 << " ";
	cout << GetOpTypeSymbol(quizz.questionsList[questionNumber].operationType);
	cout << "\n________";
}
void CorrectTheQuestionAnswer(stQuizz& quizz, short questionNumber) {
	if (quizz.questionsList[questionNumber].playAnswer != quizz.questionsList[questionNumber].correctAnswer) {
		quizz.questionsList[questionNumber].answerResult = false;
		cout << "Wrong Answer :-(\n";
		cout << "The right answer is: ";
		cout << quizz.questionsList[questionNumber].correctAnswer;
		quizz.numberOfWrongAnswers++;
		cout << "\n";

	}
	else {
		quizz.questionsList[questionNumber].answerResult = true;
		quizz.numberOfRightAnswers++;
		cout << "Right Answer :-)\n";

	}
	cout << endl;
	SetScreenColor(quizz.questionsList[questionNumber].answerResult);
}
void AskAndCorrectQuestionListAnswers(stQuizz& quizz) {
	for (short questionsNumber = 0; questionsNumber < quizz.numberOfQuestions; questionsNumber++) {
		PrintTheQuestion(quizz, questionsNumber);
		quizz.questionsList[questionsNumber].playAnswer = ReadQuestionAnswer();
		CorrectTheQuestionAnswer(quizz, questionsNumber);
	}
	quizz.isPass = (quizz.numberOfRightAnswers >= quizz.numberOfWrongAnswers);
}
string GetFinalResultsText(bool Pass) {
	if (Pass) {
		return"PASS :-)";
	}

	else {
		return"Fail :-(";
	}
}
void PrintQuizzResults(stQuizz quizz) {
	cout << "\n";
	cout << "________________________\n\n";
	cout << "Final Results is " << GetFinalResultsText(quizz.isPass);
	cout << "\n________________________________\n\n";
	cout << "Number of Questions     :" << quizz.numberOfQuestions << endl;
	cout << "Questions Level         :" << GetQuestionLevelText(quizz.questionsLevel) << endl;
	cout << "Operation Type          :" << GetOpTypeSymbol(quizz.opType) << endl;
	cout << "Numbers Of Right Answers:" << quizz.numberOfRightAnswers << endl;
	cout << "Numbers Of Wrong Answers:" << quizz.numberOfWrongAnswers << endl;
	cout << "____________________________________\n";
}
void PlayMathGame() {
	stQuizz quizz;
	quizz.numberOfQuestions = ReadHowManyQuestions();
	quizz.questionsLevel = ReadQuestionsLevel();
	quizz.opType = ReadOpType();

	GenerateQuizzQuestions(quizz);
	AskAndCorrectQuestionListAnswers(quizz);
	PrintQuizzResults(quizz);
}
void ResetScreen() {
	system("cls");
	system("color 0F");

}
void StartGame() {
	char playAgain = 'Y';
	do {
		ResetScreen();
		PlayMathGame();
		cout << endl << "Do you want to play again? Y/N? ";
		cin >> playAgain;

	} while (playAgain == 'Y' || playAgain == 'y');
}
int main() {
	srand((unsigned)time(NULL));
	StartGame();
	return 0;

}

