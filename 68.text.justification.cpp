#include <cassert>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> fullJustify(vector<string>& words, int maxWidth) {
	vector<string> justified;
	vector<string*> curLine;
	int left = maxWidth;
	for(int i = 0; i < words.size(); ++i) {
		// End of line (that is not the last one)

		int addSpace = curLine.empty() ? 0 : 1;
		if(words[i].size() + addSpace > left) {
			string line(*curLine[0]);

			// only one word => must left justify
			if(curLine.size() == 1) {
				line.append(left, ' ');
			// Otherwise we can actually left right justify
			} else {
				// Figure out how to divide extra spaces
				int minSpaces = left/(curLine.size() - 1) + 1;
				int numWithMoreSpaces = left % (curLine.size() - 1);

				// Place words and spaces
				for(int j = 1; j < curLine.size(); ++j) {
					// put spaces
					// uneven spaces?
					if(numWithMoreSpaces) {
						line.append(minSpaces + 1, ' ');
						--numWithMoreSpaces;
					} else {
						line.append(minSpaces, ' ');
					}
					// put following word
					line.append(*curLine[j]);
				}
			}
			
			justified.push_back(line);

			// Reset for next line
			curLine.clear();
			left = maxWidth;
		}

		// If word is not the first on line, it must be
		// preceded by space
		if(!curLine.empty()) {
			--left;
		}
		curLine.push_back(&words[i]);
		left -= words[i].size();
	}

	// last line requires left justification
	string line(*curLine[0]);
	for(int i = 1; i < curLine.size(); ++i) {
		line.push_back(' ');
		line.append(*curLine[i]);
	}
	// fill out with space
	line.append(left, ' ');

	justified.push_back(line);

	return justified;
}

void printVec(const vector<string> &v) {
	for(auto &row : v) {
		cerr << '"' << row << '"' << " (" << row.size() << ")" << endl;
	}
}
void check(const vector<string> &got, const vector<string> &expected) {
	if(got.size() != expected.size()) {
		cerr << "sizes do not match" << endl;
		goto problem;
	}
	for(int i = 0; i < got.size(); ++i) {
		if(got[i] != expected[i]) {
			cerr << "elements at index " << i << " do not match" << endl;
			goto problem;
		}
	}
	return;

problem:
	cerr << "got:" << endl;
	printVec(got);
	cerr << endl << "expected:" << endl;
	printVec(expected);
	cerr << endl;
}
struct TestCase {
	vector<string> words;
	int maxWidth;
	vector<string> expected;
};

int main() {
	vector<TestCase> testCases({
	{
		{"This", "is", "an", "example", "of", "text", "justification."},
		16,
		{
		   "This    is    an",
		   "example  of text",
		   "justification.  "
		}
	},
	{
		{"What","must","be","acknowledgment","shall","be"},
		16,
		{
		  "What   must   be",
		  "acknowledgment  ",
		  "shall be        "
		}
	},
	{
		{"Science","is","what","we","understand","well","enough","to","explain",
         "to","a","computer.","Art","is","everything","else","we","do"},
		20,
		{
		  "Science  is  what we",
		  "understand      well",
		  "enough to explain to",
		  "a  computer.  Art is",
		  "everything  else  we",
		  "do                  "
		}
	},
	{
		{"Hello","I", "am", "happy"},
		5,
		{"Hello", "I  am", "happy"}
	}
	});
	for(auto &testCase : testCases) {
		vector<string> got = fullJustify(testCase.words, testCase.maxWidth);
		check(got, testCase.expected);
	}
	return 0;
}
