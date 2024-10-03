import time


def get_data() -> tuple:
    string_data_set = ["."] * (26**5)
    temp_set = [".", ".", ".", ".", "."]
    alphabet = "abcdefghijklmnopqrstuvwxyz"
    index = 0
    for i in range(len(alphabet)):
        temp_set[4] = alphabet[i]
        for j in range(len(alphabet)):
            temp_set[3] = alphabet[j]
            for k in range(len(alphabet)):
                temp_set[2] = alphabet[k]
                for l in range(len(alphabet)):
                    temp_set[1] = alphabet[l]
                    for m in range(len(alphabet)):
                        temp_set[0] = alphabet[m]
                        string_data_set[index] = (temp_set[0] + temp_set[1] + temp_set[2] + temp_set[3] + temp_set[4])
                        index += 1
    string_data_set.sort()
    string_data_tuple = tuple(string_data_set)
    return string_data_tuple

def linear_search(container: tuple, element: str) -> int:
    for i in range(len(container)):
        if container[i] == element:
            return i
    return -1

def binary_search(container: tuple, element: str) -> int:
    start = 0
    end = len(container)
    middle = (start + end) // 2
    while end > start:
        if container[middle] == element:
            return middle
        elif element > container[middle]:
            start = middle + 1
            middle = (start + end) // 2
        else:
            end = middle
            middle = (start + end) // 2
    try:
        if container[middle] == element:
            return middle
        else:
            return -1
    except:
        return -1


def main():
    string_data = get_data()
    start_time = time.time()
    print(linear_search(string_data, "not_here"))
    end_time = time.time()
    print(f'^linear - not_here {end_time - start_time}')
    start_time = time.time()
    print(binary_search(string_data, "not_here"))
    end_time = time.time()
    print(f'^binary - not_here {end_time - start_time}')
    start_time = time.time()
    print(linear_search(string_data, "mzzzz"))
    end_time = time.time()
    print(f'^linear - mzzzz {end_time - start_time}')
    start_time = time.time()
    print(binary_search(string_data, "mzzzz"))
    end_time = time.time()
    print(f'^binary - mzzzz {end_time - start_time}')
    start_time = time.time()
    print(linear_search(string_data, "aaaaa"))
    end_time = time.time()
    print(f'^linear - aaaaa {end_time - start_time}')
    start_time = time.time()
    print(binary_search(string_data, "aaaaa"))
    end_time = time.time()
    print(f'^binary - aaaaa {end_time - start_time}')


if __name__ == '__main__':
    main()
