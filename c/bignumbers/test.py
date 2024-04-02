def number_to_byte_array(number_str):
    num_digits = len(number_str)
    num_bytes = (num_digits + 2) // 3  # 3 digits per byte (base 256)

    byte_array = bytearray(num_bytes)

    index = 0
    chunk = 0
    for i in range(num_digits):
        chunk = chunk * 10 + int(number_str[i])
        if (i + 1) % 3 == 0:
            byte_array[index] = chunk & 0xFF  # Ensure chunk is within byte range
            index += 1
            chunk = 0

    if chunk != 0:  # Handle remaining digits
        byte_array[index] = chunk & 0xFF

    return byte_array

# Example usage
big_number_str = "257"
byte_array = number_to_byte_array(big_number_str)

# Print the byte array
for byte in byte_array:
    print(byte, end=' ')
print()
