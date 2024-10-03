import math
# choices 1-6 when prompted should prompt the user to input "enter first operand\enter second operand"
# output "Current Result: ____\n\nCalculator Menu..."
# EXTRA CREDIT, allow user to use previous result as operand. They should be able to type RESULT and have the program replace it with the previous result


if __name__ == "__main__":
    total = 0.0
    print(f"\nCurrent Result: {total}\n\nCalculator Menu\n---------------\n0. Exit Program\n1. Addition\n2. Subtraction\n3. Multiplication\n4. Division\n5. Exponentiation\n6. Logarithm\n7. Display Average\n")
    answers = []
    choice = int(input('Enter Menu Selection: '))
    if choice == 0:
        # Exit program
        print("\nThanks for using this calculator. Goodbye!")
        exit()
    while choice != 0:
        bypass = True
        total = 0.0
        if choice == 7:
            # Display Average store results from every calculation and average by the number of calculations, if this is the first calculation print "Error: No calculations yet to average!"
            if len(answers) > 0:
                average = 0
                for x in answers:
                    average += x
                average /= len(answers)
                print("\nSum of calculations:", average * len(answers))
                print("Number of calculations:", len(answers))
                if math.fabs(average * 100) % 10 <= 0.5:
                    print(f"Average of calculations: {average:.1f}") # only to first decimal
                else:
                    print(f"Average of calculations: {average:.2f}") # only to second decimal
                choice = int(input('\nEnter Menu Selection: '))
                bypass = False
            else:
                print("\nError: No calculations yet to average!")
                #print(f"\nCurrent Result: {total}\n\nCalculator Menu\n---------------\n0. Exit Program\n1. Addition\n2. Subtraction\n3. Multiplication\n4. Division\n5. Exponentiation\n6. Logarithm\n7. Display Average\n")
                choice = int(input('\nEnter Menu Selection: '))
                bypass = False
        elif (choice <= 6) and (choice > 0):
            fOperand = input("Enter first operand: ")
            sOperand = input("Enter second operand: ")
            # changes result to the previous answer
            if sOperand == "RESULT":
                sOperand = answers[len(answers) - 1]
            if fOperand == "RESULT":
                fOperand = answers[len(answers) - 1]
            # changes inputs to integers
            fOperand = float(fOperand)
            sOperand = float(sOperand)

            if choice == 1:
                # Addition
                add = fOperand + sOperand
                total += add
                answers.append(add)
            elif choice == 2:
                # Subtraction
                sub = fOperand - sOperand
                total += sub
                answers.append(sub)
            elif choice == 3:
                # Multiplication
                mult = fOperand * sOperand
                total += mult
                answers.append(mult)
            elif choice == 4:
                # Division
                divide = fOperand / sOperand
                total += divide
                answers.append(divide)
            elif choice == 5:
                # Exponentiation first operand is the base, second operand is the exponent
                expon = fOperand ** sOperand
                total += expon
                answers.append(expon)
            elif choice == 6:
                # Logarithm first operand is the base, second operand is the yield
                logarithm = math.log(sOperand, fOperand)
                total += logarithm
                answers.append(logarithm)
        else:
            print("\nError: Invalid selection!")
            choice = int(input('\nEnter Menu Selection: '))
            bypass = False
        if bypass:
            print(f"\nCurrent Result: {total}\n\nCalculator Menu\n---------------\n0. Exit Program\n1. Addition\n2. Subtraction\n3. Multiplication\n4. Division\n5. Exponentiation\n6. Logarithm\n7. Display Average\n")
            choice = int(input('\nEnter Menu Selection: '))
    print("\nThanks for using this calculator. Goodbye!")
    exit()
