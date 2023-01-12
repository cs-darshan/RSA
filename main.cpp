#include <iostream>
#include <numeric>
#include <string>
#include <sstream>

class encryption
{
public:

    int p, q, e{}, d{}, T, N;
    int public_key[2] {};
    int private_key[2]{};
    int encryption_value;


public:
    encryption(int prime1, int prime2)
    {
        p = prime1;
        q = prime2;
        T =(p-1)*(q-1);
        N = p * q;
        encryption_value = 0;
    }

    encryption() = default;

public:
    int prime_check() const{
        int ctr = 0;
        for (int i = 1; i < p; i++) {
            if (i % p == 0) {
                std::cout << "not a prime number" << std::endl;
                ctr++;
            }
        }
        for (int j = 1; j < q; j++) {
            if (j % q == 0) {
                std::cout << "not a prime number" << std::endl;
                ctr++;
            }

        }
        return true;
    }

    void key()
    {
        for(e = 2; e<T; e++)
        {
            if(T%e==1 || N%e==1) {
                public_key[0]=e;
            }
        }
        for(d = 1; d>0; d++)
        {
            long long value = public_key[0]*d % T;
            if(value== 1 && d!=public_key[0])
            {
                private_key[0]=d;
                break;
            }
        }
        public_key[1] = N;
        private_key[1] = N;

        std::cout << "public_key[e] = " << public_key[0] << std::endl;
        std::cout << "public_key[N] = " << public_key[1] <<std::endl;
        std::cout << "private_key[d] = " << private_key[0] << std::endl;
        std::cout << "private_key[N] = " << private_key[1] << std::endl;
    }

    int character_encryption(int m)
    {
        int temp = m;
        encryption_value = 1;
        for (int i = 1; i<=public_key[0]; i++)
        {
            m = temp*m;
        }
        encryption_value = m % public_key[1];
        return encryption_value;
    }
public:
    ~encryption()= default;
};

int main() {

    char ch;
    std::cout << "enter e for encryption"<<std::endl;
    std::cin>>ch;

    if(ch == 'e') {
        int p;
        int q;
        std::cout << "enter 2 prime numbers for p and q" << std::endl;
        std::cin >> p >> q;
        encryption encrypt(p, q);
        encrypt.prime_check();

        std::string statement;
        std::cout << "enter statement" << std::endl;
        std::cin.ignore();
        getline(std::cin, statement);


        char ch_statement;
        encrypt.key();
        int temp;
        int encryption_e;
        for (int i = 0; statement[i]; i++) {
            ch_statement = static_cast<int>(statement[i]);
            encryption_e = encrypt.character_encryption(ch_statement);
            temp = ch_statement + encryption_e;
            std::cout << temp << " ";
        }
        std::cout << std::endl << std::endl;
        encrypt.~encryption();
    }

    return 0;
}
