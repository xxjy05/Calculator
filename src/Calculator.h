#include <iostream>
#include <stack>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cctype>

using namespace std;

#define random(a,b) (rand()%(b-a+1)+a)

class Calculator {
private:
	string op[4] = { "+", "-", "*", "/" };
	static int priority(char c) {
		if (c == '+' || c == '-') return 1;
		if (c == '*' || c == '/') return 2;
		return 0;
	}
	vector<string> toPostfix(const string& s) {
		vector<string> res;
		stack<char> st;
		int n = s.size();
		for (int i = 0; i < n; ++i) {
			if (isdigit(s[i])) {
				int j = i;
				string num;
				while (j < n && isdigit(s[j])) {
					num += s[j++];
				}
				res.push_back(num);
				i = j - 1;
			}
			else {
				while (!st.empty() && priority(st.top()) >= priority(s[i])) {
					res.push_back(string(1, st.top()));
					st.pop();
				}
				st.push(s[i]);
			}
		}
		while (!st.empty()) {
			res.push_back(string(1, st.top()));
			st.pop();
		}
		return res;
	}
public:
	Calculator() {}
	string MakeFormula() {
		string formula;
		srand((unsigned int)time(NULL));
		int count = random(1, 3);
		formula += to_string(random(1, 100));
		for (int i = 0; i < count; ++i) {
			int opIdx = random(0, 3);
			int num = random(1, 100);
			while (opIdx == 3 && num == 0) {
				num = random(1, 100);
			}
			formula += op[opIdx] + to_string(num);
		}
		return formula;
	}
	string Solve(string formula) {
		vector<string> post = toPostfix(formula);
		stack<double> calc;

		for (auto& token : post) {
			if (token == "+" || token == "-" || token == "*" || token == "/") {
				double b = calc.top(); calc.pop();
				double a = calc.top(); calc.pop();
				if (token == "+") calc.push(a + b);
				else if (token == "-") calc.push(a - b);
				else if (token == "*") calc.push(a * b);
				else if (token == "/") {
					if (b == 0) return formula + " = ´íÎó£º³ýÁã£¡";
					calc.push(a / b);
				}
			}
			else {
				calc.push(stod(token));
			}
		}

		double ans = calc.top();
		if (ans == (int)ans)
			return formula + " = " + to_string((int)ans);
		else
			return formula + " = " + to_string(ans);
	}
};

int main()
{
	for (int i = 0; i < 1000000; i++)
	{
		Calculator calc;
		string question = calc.MakeFormula();
		string ret = calc.Solve("11+22");
	}
	return 0;
}