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
                return myfunc(1, x);
        }
        unsigned int operator()(unsigned int pow, unsigned int x) { 
               return myfunc(pow, x);
        }
private:
        //FUNCTION IS HERE
        unsigned int function(unsigned int x) {
                return x*x % n;
        }

        unsigned int myfunc(unsigned int pow, unsigned int x) {
                unsigned int result = 0;
                if(pow > 0) {
                        result = myfunc(pow-1, function(x)) % n;
                } else if(pow == 0) {
                        result = x % n;
                }
                
                return result;
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

        unsigned int in_cycle = f(2*n, initial);
        
        unsigned int counter = 0;
        unsigned int pointer = in_cycle;
        do {
                pointer = f(pointer);
                counter++;
        } while(pointer != in_cycle);
        
        unsigned int result = 0;
        unsigned int initial_value = initial;
        unsigned int counter_value = f(counter, initial);
        while(initial_value != counter_value) {
                result++;
                initial_value = f(initial_value);
                counter_value = f(counter_value);
        }

        cout << "Result: " << result << endl;

        return 0;
}
