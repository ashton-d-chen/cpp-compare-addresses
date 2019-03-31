
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <codecvt>
#include <vector>
#include <algorithm>

using namespace std;

typedef vector<wstring*> StringCollection;

#define DEBUG 1;
/*
template<class T>
void binaryInsert(vector<T>& collection, wstring& text, unsigned int begin_index, unsigned int end_index)
{
	unsigned int current_index = end_index / 2;
	if (text.compare(collection[current_index]) > 0)
	{
		binaryInsert(collection, text, current_index, end_index);
	}
	else if (text.compare(collection[current_index]) < 0)
	{
		binaryInsert(collection, text, begin_index, current_index);
	}
	else
	{
		for (auto index == end_index; index > current_index)
	}
}
*/

void insertionSort(int sie, vector<wstring*>& collection)
{

}

#if DEBUG
void display(StringCollection data)
{
	for (auto item : data)
	{
		wcout << *item << '\n';
	}
}
#endif

bool compareWString(wstring left, wstring right)
{
	transform(left.begin(), left.end(), left.begin(), towlower);
	transform(right.begin(), right.end(), right.begin(), towlower);
	return (left < right);
}

StringCollection openFile(string fileName)
{
	wifstream file(fileName);
	wstring line;
	StringCollection collection;

	file.imbue(locale(locale::empty(), new codecvt_utf8<wchar_t>));

	if (!file.is_open())
	{
		cout << "File can't be opened";
	}

	while (file.good())
	{
		getline(file, line);
		if (file.eof())
		{
			break;
		}
		wstring* pt_text = new wstring[line.size()];
		*pt_text = line;

		/*
		auto &f = use_facet<ctype<wchar_t>>(locale());

		auto it = upper_bound(collection.begin(), collection.end(), pt_text, [&f](auto& lhs, auto&rhs){
			//return lexicographical_compare(a.begin(), a.end)
			return compareWString(*lhs, *rhs);
		});
		collection.insert(it, pt_text);
		*/
		collection.push_back(pt_text);
	}

	file.close();

	return collection;
}

void writeFile(string fileName, StringCollection collection)
{
	wstringstream strings;
	wofstream outputFile(fileName);

	for (auto i = collection.begin(); i < collection.end(); ++i)
	{
		if ((**i).compare(L"") != 0)
		{
			strings << **i << '\n';
		}
	}

	outputFile.imbue(locale(locale::empty(), new codecvt_utf8<wchar_t>));
	outputFile << strings.str();
	outputFile.close();
}

/*
void getUnique(StringCollection &dataA, StringCollection &dataB)
{
	auto iteratorA = dataA.begin();
	auto iteratorB = dataB.begin();

	while (iteratorA < dataA.end() && iteratorB < dataB.end())
	{

#if DEBUG
		wcout << "iterator A: " << *iteratorA << '\n';
		wcout << "iterator B: " << *iteratorB << '\n';
#endif

		if (compareWString(**iteratorA, **iteratorB) > 0)
		{
			++iteratorB;
		}
		else if (compareWString(**iteratorA, **iteratorB) < 0)
		{
			++iteratorA;
		}
		else
		{
			**iteratorA = L"";
			**iteratorB = L"";

			++iteratorA;
			++iteratorB;
		}
	}
}
*/
int main()
{

#if DEBUG
	string fileInputA = "TestFileA.txt";
	string fileInputB = "TestFileB.txt";

	string fileSortedA = "TestFileA_Sorted.txt";
	string fileSortedB = "TestFileB_Sorted.txt";
	
	string fileOutputA = "TestFileA_Unique.txt";
	string fileOutputB = "TestFileB_Unique.txt";
#else
	string fileInputA = "ItalyFileA.txt";
	string fileInputB = "ItalyFileB.txt";

	string fileSortedA = "ItalyFileA_Sorted.txt";
	string fileSortedB = "ItalyFileB_Sorted.txt";

	string fileOutputA = "ItalyFileA_Unique.txt";
	string fileOutputB = "ItalyFileB_Unique.txt";
#endif

	StringCollection dataA = openFile(fileInputA);
	StringCollection dataB = openFile(fileInputB);

	sort(dataA.begin(), dataA.end());
	sort(dataB.begin(), dataB.end());

#if DEBUG
	cout << "Display data A" << '\n';
	display(dataA);
	
	cout << "Display data B" << '\n';
	display(dataB);
#endif
	
	sort(dataA.begin(), dataA.end(), [](const wstring* lhs, const wstring* rhs) {
		return compareWString(*lhs, *rhs);
	});

	sort(dataB.begin(), dataB.end(), [](const wstring* lhs, const wstring* rhs) {
		return compareWString(*lhs, *rhs);
	});

	writeFile(fileSortedA, dataA);
	writeFile(fileSortedB, dataB);

	//getUnique(dataA, dataB, compareWString);

	writeFile(fileOutputA, dataA);
	writeFile(fileOutputB, dataB);

	return 0;
}