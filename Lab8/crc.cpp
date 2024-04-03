#include <iostream>
#include <string>
using namespace std;

string crc_encode(string data, string divisor)
{
    string dividend = data + string(divisor.length() - 1, '0');

    for (size_t i = 0; i < data.length(); ++i)
    {
        if (dividend[i] == '1')
        {
            for (size_t j = 0; j < divisor.length(); ++j)
            {
                dividend[i + j] = (dividend[i + j] == divisor[j]) ? '0' : '1';
            }
        }
    }

    return dividend.substr(data.length());
}

bool crc_decode(string received_data, string divisor)
{
    string remainder = received_data;

    for (size_t i = 0; i < received_data.length() - (divisor.length() - 1); ++i)
    {
        if (remainder[i] == '1')
        {
            for (size_t j = 0; j < divisor.length(); ++j)
            {
                remainder[i + j] = (remainder[i + j] == divisor[j]) ? '0' : '1';
            }
        }
    }

    return (remainder.find('1') != string::npos);
}

int main()
{
    string data = "10011101";
    string divisor = "1001";

    string encoded_data = crc_encode(data, divisor);
    cout << "Encoded Data (with CRC): " << data + encoded_data << endl;

    string received_data = "10011101100"; // Introducing error
    bool error_detected = crc_decode(received_data, divisor);

    if (error_detected)
        cout << "Error detected!" << endl;
    else
        cout << "No error detected!" << endl;

    return 0;
}
