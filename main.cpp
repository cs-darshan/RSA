#include <iostream>
#include <string>
#include <sstream>
#include <boost/multiprecision/cpp_int.hpp>

namespace mp = boost::multiprecision;

class Encryption
{
public:
    mp::cpp_int p, q, e{}, d{}, T, N;
    mp::cpp_int public_key[2]{};
    mp::cpp_int private_key[2]{};
    mp::cpp_int encryption_value;

public:
    Encryption(const mp::cpp_int& prime1, const mp::cpp_int& prime2)
        : p(prime1), q(prime2), T((p - 1) * (q - 1)), N(p * q), encryption_value(0) {}

public:
    bool prime_check(const mp::cpp_int& num) const {
        if (num <= 1)
            return false;

        for (mp::cpp_int i = 2; i * i <= num; ++i) {
            if (num % i == 0) {
                std::cout << "Not a prime number" << std::endl;
                return false;
            }
        }
        return true;
    }

    void key() {
        for (e = 2; e < T; ++e) {
            if (mp::gcd(e, T) == 1) {
                public_key[0] = e;
                break;
            }
        }

        d = mp::powm(public_key[0], -1, T);

        public_key[1] = N;
        private_key[0] = d;
        private_key[1] = N;

        std::cout << "public_key[e] = " << public_key[0] << std::endl;
        std::cout << "public_key[N] = " << public_key[1] << std::endl;
        std::cout << "private_key[d] = " << private_key[0] << std::endl;
        std::cout << "private_key[N] = " << private_key[1] << std::endl;
    }

    mp::cpp_int character_encryption(const mp::cpp_int& m) {
        encryption_value = mp::powm(m, public_key[0], public_key[1]);
        return encryption_value;
    }
};

class Decryption
{
public:
    mp::cpp_int d, N;
    mp::cpp_int decryption_value;

public:
    Decryption(const mp::cpp_int& private_key_d, const mp::cpp_int& public_key_N)
        : d(private_key_d), N(public_key_N), decryption_value(0) {}

    mp::cpp_int character_decryption(const mp::cpp_int& c) {
        decryption_value = mp::powm(c, d, N);
        return decryption_value;
    }
};

int main() {
    char ch;
    std::cout << "Enter 'e' for encryption or 'd' for decryption" << std::endl;
    std::cin >> ch;

    if (ch == 'e') {
        mp::cpp_int p, q;
        std::cout << "Enter two prime numbers for p and q" << std::endl;
        std::cin >> p >> q;
        Encryption encrypt(p, q);

        if (!encrypt.prime_check(p) || !encrypt.prime_check(q)) {
            std::cout << "Invalid prime numbers" << std::endl;
            return 1;
        }

        std::cin.ignore();
        std::string statement;
        std::cout << "Enter a statement" << std::endl;
        std::getline(std::cin, statement);

        encrypt.key();

        std::cout << "Encrypted statement: ";
        for (char ch : statement) {
            mp::cpp_int ch_statement = static_cast<mp::cpp_int>(ch);
            mp::cpp_int encryption_e = encrypt.character_encryption(ch_statement);
            mp::cpp_int temp = ch_statement + encryption_e;
            std::cout << temp << " ";
        }
        std::cout << std::endl;
    } else if (ch == 'd') {
        mp::cpp_int private_key_d, public_key_N;
        std::cout << "Enter private key (d) and public key (N) for decryption" << std::endl;
        std::cin >> private_key_d >> public_key_N;

        Decryption decrypt(private_key_d, public_key_N);

        std::string encrypted_statement;
        std::cout << "Enter the encrypted statement to decrypt" << std::endl;
        std::cin.ignore();
        std::getline(std::cin, encrypted_statement);

        std::cout << "Decrypted statement: ";
        std::istringstream iss(encrypted_statement);
        mp::cpp_int c;
        while (iss >> c) {
            mp::cpp_int decrypted_char = decrypt.character_decryption(c);
            char original_char = static_cast<char>(decrypted_char);
            std::cout << original_char;
        }
        std::cout << std::endl;
    } else {
        std::cout << "Invalid choice" << std::endl;
    }

    return 0;
}
