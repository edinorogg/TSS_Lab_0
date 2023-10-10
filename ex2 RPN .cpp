#include <iostream>
#include<fstream>
#include <string>
#include <cctype>
#include<ctime
#include<cmath>
#include <sstream>
using namespace std;

int Priority(char t) {
	switch (t) {
	case '(': return 1;
	case '+': case '-': return 2;
	case '*': case '/': case '%': return 3;
	case '^': return 4;
	default: return 0;
	}
}

template <typename T>
class Node {
public:

	Node* pnext;
	T value;

	Node(T value = T(), Node* pnext = nullptr) {
		this->value = value;
		this->pnext = pnext;
	}
};
template <typename T>
class List {

public:
	List();
	~List();
	virtual void Push(T value);
	int Size() { return List_Size; }
	void GetStack();
	bool IsEmpty();
	T Pop();
	void Clear();
	T Top();
	List(const List<T>& other);
	string ReversePolishNotation(string str);
	List& operator=(const List& other) {
		{
			if (this == &other) {
				// Проверяем на самоприсваивание
				return *this;
			}

			// Очищаем текущий список
			Clear();

			List_Size = other.List_Size;
			head = nullptr;

			Node<T>* otherNode = other.head;
			Node<T>* currentNode = nullptr;

			while (otherNode != nullptr) {
				if (head == nullptr) {
					head = new Node<T>(otherNode->value);
					currentNode = head;
				}
				else {
					currentNode->pnext = new Node<T>(otherNode->value);
					currentNode = currentNode->pnext;
				}

				otherNode = otherNode->pnext;
			}

			return *this;
		}
	};
protected:
	//template <typename T>
	//class Node {
	//public:

	//	Node* pnext;
	//	T value;

	//	Node(T value = T(), Node* pnext = nullptr) {
	//		this->value = value;
	//		this->pnext = pnext;
	//	}
	//};
	int List_Size;
	Node<T>* head;
};


template <typename T>
List<T>::List()
{
	//cout << "вызван конструктор: " << this << endl;
	List_Size = 0;
	head = nullptr;

}
template <typename T>
List<T>::~List() {
	//cout << "Вызван деструктор " << this << endl;
	if (IsEmpty()) {
		delete head;
	}
	else {
		Clear();
	}
}
template <typename T>
List<T>::List(const List<T>& other) {
	//cout << "Вызван конструктор копирования: " << this << endl;
	List_Size = other.List_Size;
	head = nullptr;

	Node<T>* otherNode = other.head;
	Node<T>* currentNode = nullptr;

	while (otherNode != nullptr) {
		if (head == nullptr) {
			head = new Node<T>(otherNode->value);
			currentNode = head;
		}
		else {
			currentNode->pnext = new Node<T>(otherNode->value);
			currentNode = currentNode->pnext;
		}

		otherNode = otherNode->pnext;
	}
}
//template <typename T>
//List<T>::List(const List& other) {
//	int List_Size = other.List_Size;
//	Node<T>* temp = other.head;
//	Node<T>* temp_data = new T[List_Size];
//	for (size_t i = List_Size; i > 0; i--)
//	{
//		temp_data[i] = new Node<T>(temp->value, temp);
//		temp = temp->pnext;
//	}
//	for (size_t i = 0; i < List_Size; i++)
//	{
//		this->Push(temp_data[i]->value, temp_data[i]->pnext);
//	}
//	this->GetStack();
//}

template <typename T>
void List<T>::Push(T value)
{

	if (head == nullptr) {
		head = new Node<T>(value);
	}
	else {
		Node<T>* temp = head;
		head = new Node<T>(value, temp);
	}
	List_Size++;
}
template <typename T>
bool List<T>::IsEmpty() {
	if (head == nullptr) {
		return 1;
	}
	else {
		return 0;
	}
}
template <typename T>
void List<T>::GetStack() {
	if (this->IsEmpty()) {
		cout << "В стеке ничего нет!" << endl;
	}
	else {
		Node<T>* temp = this->head;
		while (temp != nullptr) {
			T value = temp->value;
			cout << value << endl;
			temp = temp->pnext;
		}

	}

}
template <typename T>
T List<T>::Pop() {
	if (this->IsEmpty()) {
		cout << "Стек пуст" << endl;
		return 0;
	}
	else {
		Node<T>* temp = this->head;
		T value = head->value;
		head = head->pnext;
		delete temp;
		//cout << "Память была освобождена" << endl;
		List_Size--;
		return value;
	}
}
template <typename T>
void List<T>::Clear() {
	if (head == nullptr) {

	}
	else {
		int Local_List_Size = List_Size;
		for (size_t i = 0; i < Local_List_Size; i++)
		{
			Pop();
		}
	}

}
template <typename T>
T List<T>::Top() {
	if (this->IsEmpty()) {
		int check = 0;
		return check;
	}
	else {
		return head->value;
	}
}

template<typename T>
class Stack : public List<T> {
public:

	using List<T>::List;
	void Push(T value) override;

	~Stack() {
		/*cout << "вызван деструктор для стека: " << this << endl;*/
		List<T>::Clear();

	}
private:

};

template <typename T>
void Stack<T>::Push(T data)
{
	//typename List<T>::template Node<T>* nodePointer = nullptr;

	if (this->head == nullptr) {
		this->head = new typename List<T>::template Node<T>(data);
	}
	else {
		typename List<T>::template Node<T>* temp = this->head;
		this->head = new typename List<T>::template Node<T>(data, temp);
	}
	this->List_Size++;
}
void removeSpaces(string& str) {
	str.erase(remove_if(str.begin(), str.end(), ::isspace), str.end());
}
int GetResultRPN(string& str_out) {
	List<int> result;
	string tempstr{};
	int value = 0;
	int n1, n2, res = 0;

	for (size_t i = 0; i < str_out.size(); i++)
	{
		while ((str_out[i] != ' ') && (isdigit(str_out[i]))) {
			tempstr += str_out[i];
			i++;
		}
		if (!tempstr.empty()) {
			value = stoi(tempstr);
			result.Push(value);
			tempstr.clear();
		}
		if (str_out[i] != ' ') {
			n1 = result.Pop();
			n2 = result.Pop();
			switch (str_out[i]) {
			case '+': res = n1 + n2; break;
			case '-': res = n2 - n1; break;
			case '*': res = n1 * n2; break;
			case '/': if (n1 == 0) {
				throw(string)"Деление на 0 запрещено";
			}
					else {
				res = n2 / n1;
			}
					break;
			case '%':
				if (n1 == 0) {
					throw(string)" Взятие ост на 0 запрещено";
				}
				else {
					res = n2 % n1;
				}
				break;
			case '^': res = pow(num2, num1); 
			default: throw (string)"Ошибка";
			}
			result.Push(res);
		}

	}
	return result.Pop();

}
string ReversePolishNotation(string str) {
	int was_op = 0, np = 0;
	bool isdigitflag = false;
	List<char> op_stack;
	string str_in = str;
	removeSpaces(str_in);
	string str_out{};

	if ((!isdigit(str_in[0])) && str_in[0] != '(')
		throw (string)str + " " + "Выражение должно начинаться с числа или открывающей скобки";

	for (char curc : str_in) {
		if (isdigit(curc)) {
			str_out += curc;
			was_op = 0;
			isdigitflag = true;
		}
		else str_out += ' ';

		if (!isdigitflag) {
			switch (curc) {
			case '(':
				op_stack.Push(curc);
				++np;
				was_op = 0;
				break;
			case '*': case '/': case '+': case '-': case '^': case '%':
				if (!was_op) {
					was_op = 1;
					while (Priority(curc) <= Priority(op_stack.Top())) {
						str_out += op_stack.Pop();
						str_out += ' ';
					}
					if (Priority(curc) > Priority(op_stack.Top())) {
						op_stack.Push(curc);
					}
					break;
				}
				else throw (string)str + " " + "Несколько операций подряд";

			case ')':
				if (was_op)
					throw (string)str + " " + "Не найдена открывающая скобка";
				else
					while ((curc = op_stack.Pop()) != '(' && np > 0) {

						str_out += curc;
						str_out += ' ';
					}
				--np;
				break;
			default: {
				throw (string)str + " " + "Встречен неправильный символ в строке";
			}
			}
		}
		else {
			isdigitflag = false;
		}
	}
	while (op_stack.Size() != 0) {
		str_out += ' ';
		str_out += op_stack.Pop();
	}
	if (np)
		throw (string)str + " " + "Неправильное количество скобок";
	return str_out;
}
string ErrorFileNameGeneration(string& inputfile) {
	time_t currentTime;
	time(&currentTime);
	stringstream fileNameStream;
	fileNameStream << "C:\\Users\\ulyan\\Desktop\\Test" << "\\Result RPN for " << inputfile << ' ' << currentTime << ".txt";
	string fileName = fileNameStream.str();

	return fileName;
}
void WriteToErrorFile(string& exception, int line_counter, string& inputfile, string& outputfile) {
	string filepath = outputfile;

	ofstream targetFile(filepath, ios::app);
	if (!targetFile.is_open()) {
		cerr << "Не удалось создать целевой файл " << filepath << "." << endl;

	}
	else {
		targetFile << line_counter << endl;
		targetFile << exception << endl;

	}
	targetFile.close();

}
void GetInfo(string& input)
{
	int line_counter = 0;
	std::ifstream input_file(input);
	bool Exception = false;
	string str_out{};
	string Error_File_Name = ErrorFileNameGeneration(input);
	if (!input_file.is_open())
	{
		std::cerr << "Ошибка при открытии файла\n";
		Exception = true;
	}
	try
	{
		std::string line;
		while (std::getline(input_file, line))
		{
			try {
				str_out = ReversePolishNotation(line);
				cout << "исходная строка: " << line << endl;
				cout << "постфиксная форма: " << str_out << endl;
				cout << "результат: " << GetResultRPN(str_out) << endl;
			}
			catch (string exception) {
				WriteToErrorFile(exception, line_counter, input, Error_File_Name);
			}
			line_counter++;
		}
		Exception = true;
	}
	catch (string e)
	{
		std::cerr << "Возникло исключение: " << e << '\n';
		Exception = true;
	}

	input_file.close();

}


int main(int argc, char* argv[]) {

	setlocale(LC_ALL, "ru");
	if (argc < 2) {
		std::cout << "Похоже, вы забыли указать имя файла" << endl;
	}
	else {

		for (size_t i = 1; i < argc; i++)
		{
			string filename = argv[i];
			GetInfo(filename);

		}

	}
}
