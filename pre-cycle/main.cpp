#include <iostream>

using namespace std;


const unsigned int DEFAULT_N = 42;

class Function {
public:
        Function(unsigned int _n) {
                if(n != 0) {
                        n = _n;
                } else {
                        Function();
                }
        }
        Function() {
                n = DEFAULT_N;
        }
        unsigned int operator()(unsigned int x) {
                return (myfunc(x) % n);
        }
        unsigned int operator()(unsigned int pow, unsigned int x) {
                unsigned int result = 0;
                if(pow > 1) {
                        result = this(pow-1, x)*myfunc(x);
                } else if(pow == 1) {
                        result = myfunc(x);
                }
                
                return result % n;
        }
private:
        unsigned myfunc(unsigned int x) {
                return x*x;
        }
        unsigned int n; 
};

int main() {
        unsigned int n = 0;
        cout << "Modulus:" << endl;
        cin >> n;
        Function f(n);
        
        unsigned int initial = 0;
        cout << "Initial number:" << endl;
        cin >> initial;

        unsigned int in_cycle = f(2n, initial);
        
        unsigned int counter = 0;
        unsigned int pointer = in_cycle;
        do {
                pointer = f(pointer);
                counter++;
        } while(pointer != in_cycle);
        
        unsigned int result = 0;
        do {
                result++;
        } while(f(result, initial) != f(result + counter, initial));

        cout << "Result: " << result << endl;

        return 0;
}
