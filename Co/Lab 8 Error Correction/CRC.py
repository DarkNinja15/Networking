def crc_remainder(data, divisor):
    """
    Calculates the CRC remainder for given data and divisor.
    """
    # Append zeros to data to match the length of divisor
    data += '0' * (len(divisor) - 1)
    # Convert data and divisor to lists of integers
    data = [int(bit) for bit in data]
    divisor = [int(bit) for bit in divisor]
    
    # Perform CRC division
    remainder = list(data)
    for i in range(len(data) - len(divisor) + 1):
        if remainder[i] == 1:
            for j in range(len(divisor)):
                remainder[i + j] ^= divisor[j]
    
    # Convert remainder back to a string
    remainder_str = ''.join(str(bit) for bit in remainder[-(len(divisor) - 1):])
    return remainder_str

def crc_encode(data, divisor):
    """
    Encodes data with CRC by appending the CRC remainder.
    """
    crc = crc_remainder(data, divisor)
    encoded_data = data + crc
    return encoded_data

def crc_check(data, divisor):
    """
    Checks if the CRC of the received data is valid.
    """
    crc_received = data[-(len(divisor) - 1):]
    data_to_check = data[:-len(crc_received)]
    crc_calculated = crc_remainder(data_to_check, divisor)
    return crc_received == crc_calculated

def get_input():
    """
    Get user input for data and divisor.
    """
    data = input("Enter the data to encode: ")
    divisor = input("Enter the divisor: ")
    return data, divisor

def main():
    # Get user input for data and divisor
    data, divisor = get_input()
    
    # Encode data with CRC
    encoded_data = crc_encode(data, divisor)
    print("Encoded data (with CRC):", encoded_data)
    
    # Simulating transmission, where errors might occur
    transmitted_data = input("Enter the transmitted data (with possible errors): ")
    
    # Checking the CRC of received data
    is_valid = crc_check(transmitted_data, divisor)
    if is_valid:
        print("No errors detected.")
    else:
        print("Error detected in received data.")

if __name__ == "__main__":
    main()

