#include <iostream>
#include <string>
using namespace std;

char compute_parity_bit(string data)
{
    int count = 0;
    for (char bit : data)
    {
        if (bit == '1')
            count++;
    }
    return (count % 2 == 0) ? '0' : '1';
}

bool check_parity_error(string data, char parity_bit)
{
    int count = 0;
    for (char bit : data)
    {
        if (bit == '1')
            count++;
    }
    return ((count % 2 == 0) && (parity_bit == '1')) || ((count % 2 !=
                                                          0) &&
                                                         (parity_bit == '0'));
}

int main()
{
    string data = "1101";
    char parity_bit = compute_parity_bit(data);
    cout << "Parity Bit: " << parity_bit << endl;

    char received_parity_bit = '1'; // Introducing error
    bool error_detected = check_parity_error(data, received_parity_bit);

    if (error_detected)
        cout << "Error detected!" << endl;
    else
        cout << "No error detected!" << endl;

    return 0;
}