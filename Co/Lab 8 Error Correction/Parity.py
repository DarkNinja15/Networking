def parity_check(data, parity_type="even"):
    """
    Implements parity error detection for a single bit string.

    Args:
        data (str): The data bit string entered by the user.
        parity_type (str, optional): The type of parity to use. Can be "even" (default) or "odd".

    Returns:
        str: The data string with the added parity bit.
    """

    data_bits = list(data)  # Convert string to list of bits

    # Count the number of 1s in the data
    num_ones = sum(int(bit) for bit in data_bits)

    # Determine the parity bit value based on the type
    if parity_type == "even":
        parity_bit = "0" if num_ones % 2 == 0 else "1"
    elif parity_type == "odd":
        parity_bit = "1" if num_ones % 2 == 0 else "0"
    else:
        raise ValueError("Invalid parity type. Must be 'even' or 'odd'.")

    # Add the parity bit to the end of the data
    data_bits.append(parity_bit)

    return "".join(data_bits)  # Convert list back to string

def check_parity(data_with_parity, parity_type="even"):
    """
    Checks for parity errors in the received data.

    Args:
        data_with_parity (str): The data string with the parity bit.
        parity_type (str, optional): The type of parity used. Can be "even" (default) or "odd".

    Returns:
        bool: True if no errors detected, False otherwise.
    """

    data_bits = list(data_with_parity[:-1])  # Extract data bits (excluding parity)
    received_parity = data_with_parity[-1]  # Get the received parity bit

    # Count the number of 1s in the data
    num_ones = sum(int(bit) for bit in data_bits)

    # Determine expected parity based on the type
    if parity_type == "even":
        expected_parity = "0" if num_ones % 2 == 0 else "1"
    elif parity_type == "odd":
        expected_parity = "1" if num_ones % 2 == 0 else "0"
    else:
        raise ValueError("Invalid parity type. Must be 'even' or 'odd'.")

    # Check if received parity matches expected parity
    return received_parity == expected_parity

# Get user input for data and parity type
data = input("Enter your data (single bit string, e.g., 0101): ")
parity_type = input("Enter parity type (even or odd): ").lower()  # Convert to lowercase for case-insensitive check

data_with_parity = parity_check(data, parity_type)
print("Data with parity:", data_with_parity)

# Simulate error (change second bit from 1 to 0)
error_data = data_with_parity[:2] + "0" + data_with_parity[3:]

if check_parity(error_data, parity_type):
    print("No errors detected (incorrect due to simulated error)")
else:
    print("Error detected!")

