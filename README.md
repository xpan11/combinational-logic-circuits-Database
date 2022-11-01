					          Report
Main idea:
The homework is asked to produce a way to not only identify different circuits but also ask us to recognize equivalent circuits with different forms (row and Colum permuting). So I try different cases and finally come up with three elements that can recognize equivalent circuits while it is also able to identify different circuits. The three elements are the uniqueness of truth table value, uniqueness of Colum, uniqueness of row. Missing each one of them may cause problems,  for example, circuit(0 1, 1 0) may have the same value(same binay sum or the same number of 1) and same row number as the circuit(0 01, 0 10), but since the column number of two circuits are different, which makes these two different. So if two circuits are equivalent, they must have the same number of columns and rows and also perform the same uniqueness of truth table. To ensure the uniqueness of value of different circuits, I will mention how I perform the value uniqueness in the Tadd and produce_key function.
Circuit Class of mine:
 

Structure(map<string, string>):
Besides Inputs and Output number, I choose map<string, string> as the structure to store the truth table, because the element inside exists as pair, I think it is a proper way to store each row in pair since it has two main values, Inputs and Output. 
Function Tadd(string c):
 
Tadd is a self-designed function to add each row of truth table to the map<string, string>. For the parameter string c, it is in form of “aaa bb”. Because the form of c looks like a binary number that represents a fixed decimal value. 
First, for each row of the truth table, I perform the binary form of each row by combining input and output(000 01-> 00001), by using substrate and  str+str.
Besides adding it to the map<string, string>, I also create an int decsum(decimal sum of the binary form) in the structure to sum up the binary form of each row to form the value uniqueness by using stoi. Since the decimal value of each binary form of row(000 01 -> 00001, where value = pow(2,0) = 1) are unique, thus the decimal sum of binary value of each row can produce a unique number for the whole truth table, which is int decsum.
Function produce_key():
 
Truthtable.size() represent how many rows are there in the truth table, which represents the uniqueness of row number.
Decsum is the decimal sum of the binary value of each row, which I mention in the Tadd(string c) function that represents the uniqueness of the value uniqueness of the truth table.
(Inputs*10+Output) represent the uniqueness of column numbers. Inputs * 10 instead of just adding them together is because it can avoid collisions (if the input is 2 and output is also 2, uniqueness = 4, which is the same as input is 3, the output is 1). 
When times three uniqueness together, it produces a unique value for the truth table which is hard to cause trouble (not likely to have two different circuits to have the same unique number). 
Database design, hash value, and equal_to:
 
 
Because the unique value produces by produce_key() in the Circuit class is very effective, so I just use it to perform both keys of the unordered_set, equal_to, and hash_value.
Main function:  
First, use ifstream to read from the text file, the first line is the number of circuits in the txt file. Then use that number in the for loop to produce Circuit object to each truth table. Use another for loop with the number(pow(2, in), since every truth tables have the row number of 2 to the power input number) to add each truth table row line, I use Tadd() function to add it to the Circuit object. If found duplicate, print the statement as the requirement.
Output:
Different circuits cases, find(), and print function:
 
 
Equivalent circuit cases, find(), and print function:
 
 




