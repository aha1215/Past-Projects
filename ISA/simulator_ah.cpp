#include <iostream>
#include <fstream>
#include <cstdlib>
#include <map>
#include <vector>

using namespace std;

int bin_to_dec(string bin);

int main()
{
    string filename;

    cout << "Enter filename: ";
    cin >> filename;

	fstream fin(filename);				//Open binary file containing instructions.

	if (fin.fail())
	{
		cout << "Error opening file\n";
		exit(0);
	}

	string instruction;						//Stores complete instruction from binary file
	string opcode;							//Stores binary opcode

	vector<string> memory;
	map<string, int> reg_map;				//string is binary bits that represent each register
	map<string, vector<int>> ary_map;		//every key is mapped to a vector

	//REGISTERS....keys for map, currently 16
	reg_map["0000"] = 0;                                    
	reg_map["0001"] = 0;                     
	reg_map["0010"] = 0;                     
	reg_map["0011"] = 0;                     
	reg_map["0100"] = 0;                     
	reg_map["0101"] = 0;                     
	reg_map["0110"] = 0;                     
	reg_map["0111"] = 0;

    reg_map["1000"] = 0;
    reg_map["1001"] = 0;
    reg_map["1010"] = 0;
    reg_map["1011"] = 0;
    reg_map["1100"] = 0;
    reg_map["1101"] = 0;
    reg_map["1110"] = 0;
    reg_map["1111"] = 0;

	while (fin >> instruction)				        //Read entire line of instruction (...bit)
	{
		memory.push_back(instruction);		        //Instruction placed into memory vector of strings
	}

	fin.close();							        //Program done loading.

    for (unsigned i = 0; i < memory.size(); i++)    // for loop to iterate through vector of instructions
    {
        
        instruction = memory.at(i);                 // retrieve the current instruction
        opcode = instruction.substr(0, 4);          // take the first 4 bits of the instruction
        
        if (opcode == "1110") //PUT : Convert binary to decimal and store value.
        {
            string n = instruction.substr(4, 12);     // read the 12 bits related to numerical value
            int val = bin_to_dec(n);                // convert binary to decimal

            string regis = instruction.substr(16, 4);    // find the 4 bits related to the register
            reg_map[regis] = val;
        }
        else if (opcode == "0000") //RESET
        {
            reg_map["0000"] = 0;
            reg_map["0001"] = 0;
            reg_map["0010"] = 0;
            reg_map["0011"] = 0;
            reg_map["0100"] = 0;
            reg_map["0101"] = 0;
            reg_map["0110"] = 0;
            reg_map["0111"] = 0;

            reg_map["1000"] = 0;
            reg_map["1001"] = 0;
            reg_map["1010"] = 0;
            reg_map["1011"] = 0;
            reg_map["1100"] = 0;
            reg_map["1101"] = 0;
            reg_map["1110"] = 0;
            reg_map["1111"] = 0;
        }
        else if (opcode == "0110") //SUM                 // SUM instruction is followed by three registers
        {
            string regisA = instruction.substr(4, 4);
            string regisB = instruction.substr(8, 4);
            string regisC = instruction.substr(12, 4);

            int sum_result = reg_map[regisA] + reg_map[regisB]; // add the first two registers
            reg_map[regisC] = sum_result;                       // place the result in the third register

        }
        else if (opcode == "0111") //SUB
        {
            string regisA = instruction.substr(4, 4);
            string regisB = instruction.substr(8, 4);
            string regisC = instruction.substr(12, 4);

            int sub_result = reg_map[regisA] - reg_map[regisB]; // subtract the first two registers
            reg_map[regisC] = sub_result;
        }
        else if (opcode == "1000") //MULT
        {
            string regisA = instruction.substr(4, 4);
            string regisB = instruction.substr(8, 4);
            string regisC = instruction.substr(12, 4);

            int sub_result = reg_map[regisA] * reg_map[regisB]; 
            reg_map[regisC] = sub_result;
        }
        else if (opcode == "1001") //DIV
        {
            string regisA = instruction.substr(4, 4);
            string regisB = instruction.substr(8, 4);
            string regisC = instruction.substr(12, 4);

            int sub_result = reg_map[regisA] / reg_map[regisB]; 
            reg_map[regisC] = sub_result;
        }
        else if (opcode == "1010") //MOD
        {
            string regisA = instruction.substr(4, 4);
            string regisB = instruction.substr(8, 4);
            string regisC = instruction.substr(12, 4);

            int sub_result = reg_map[regisA] % reg_map[regisB]; 
            reg_map[regisC] = sub_result;
        }
        else if (opcode == "0001") //COUT : Print to screen
        {
            string regis = instruction.substr(4, 4);    
            cout << reg_map[regis] << endl;            
        }
        else if(opcode == "0010") //CIN : Prompt to enter an int value
        {
            string regis = instruction.substr(4, 4);
            cin >> reg_map[regis];
        }
        else if (opcode == "0011") //LOOP
        {
            string regis = instruction.substr(16, 4); // Read 4 bit register
            string n = instruction.substr(4, 12);     // read the 12 bits related to numerical value
            int val = bin_to_dec(n);                  // Convert to decimal value

            if (reg_map[regis] > 0) //If register > 0, decrement by val + 1
                i -= (val + 1);
        }
        else if (opcode == "1111") //RETURN : Stops the program
        {
            cout << "Program has finished running.\n";
        }
        else
        {
            cout << "ERROR. OPCODE NOT FOUND. PROGRAM WILL TERMINATE.\n";
            exit(2);
        }
    }

    return 0;
}

int bin_to_dec(string bin)
{
    int num = 0;
    for (int i = 0; i < bin.length(); i++)
        if (bin[i] == '1')
            num += pow(2, bin.length() - 1 - i);

    return num;
}