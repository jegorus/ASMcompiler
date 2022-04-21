#define _CRT_SECURE_NO_WARNINGS
//#define DEBUG
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <cstring>

using namespace std;

enum codes {
	HALT = 0,
	SYSCALL = 1,
	ADD = 2,
	ADDI = 3,
	SUB = 4,
	SUBI = 5,
	MUL = 6,
	MULI = 7,
	DIV = 8,
	DIVI = 9,
	LC = 12,
	SHL = 13,
	SHLI = 14,
	SHR = 15,
	SHRI = 16,
	AND = 17,
	ANDI = 18,
	OR = 19,
	ORI = 20,
	XOR = 21,
	XORI = 22,
	NOT = 23,
	MOV = 24,
	ADDD = 32,
	SUBD = 33,
	MULD = 34,
	DIVD = 35,
	ITOD = 36,
	DTOI = 37,
	PUSH = 38,
	POP = 39,
	CALL = 40,
	CALLI = 41,
	RET = 42,
	CMP = 43,
	CMPI = 44,
	CMPD = 45,
	JMP = 46,
	JNE = 47,
	JEQ = 48,
	JLE = 49,
	JL = 50,
	JGE = 51,
	JG = 52,
	LOAD = 64,
	STORE = 65,
	LOAD2 = 66,
	STORE2 = 67,
	LOADR = 68,
	LOADR2 = 69,
	STORER = 70,
	STORER2 = 71
};
enum func_type {
	RM = 0,
	RR = 1,
	RI = 2,
	J = 3
};
enum syscall_code {
	EXIT = 0,
	SCANINT = 100,
	SCANDOUBLE = 101,
	PRINTINT = 102,
	PRINTDOUBLE = 103,
	GETCHAR = 104,
	PUTCHAR = 105
};

void print_int_bit(int x)
{
	for (int i = 31; i >= 0; i--)
	{
		cout << ((x >> i) & 1);
		if (i % 8 == 0) {
			cout << " ";
		}
	}
	cout << endl;
}
void print_long_long_bit(long long x)
{
	for (int i = 63; i >= 0; i--)
	{
		cout << ((x >> i) & 1);
		if (i % 8 == 0) {
			cout << " ";
		}
	}
	cout << endl;
}
void long_long_to_int(long long l, int& r0, int& r1)
{
	r0 = (int)l;
	r1 = l >> 32;
}
void int_to_long_long(long long& l, int r0, int r1)
{
	l = 0;
	l |= (long long)r0;
	l &= (1024 * 1024 * 4) - 1;
	l |= (long long)r1 << 32;
}
void int_to_double(double& a, int r0, int r1)
{
	long long l = 0;
	int_to_long_long(l, r0, r1);
	memcpy(&a, &l, sizeof a);
}
void double_to_int(double a, int& r0, int& r1)
{
	long long l = 0;
	memcpy(&l, &a, sizeof l);
	long_long_to_int(l, r0, r1);
}

void map_iterate(map <string, int> &x) // prints map
{
	for (auto it = x.begin(); it != x.end(); it++)
	{
		cout << it->first << " " << it->second << endl;
	}
}
void map_iterate(map <int, int> &x)
{
	for (auto it = x.begin(); it != x.end(); it++)
	{
		cout << it->first << " " << it->second << endl;
	}
}
void fill_name_code(map <string, int> &x)
{
	x["halt"] = HALT;
	x["syscall"] = SYSCALL;
	x["add"] = ADD;
	x["addi"] = ADDI;
	x["sub"] = SUB;
	x["subi"] = SUBI;
	x["mul"] = MUL;
	x["muli"] = MULI;
	x["div"] = DIV;
	x["divi"] = DIVI;
	x["lc"] = LC;
	x["shl"] = SHL;
	x["shli"] = SHLI;
	x["shr"] = SHR;
	x["shri"] = SHRI;
	x["and"] = AND;
	x["andi"] = ANDI;
	x["or"] = OR;
	x["ori"] = ORI;
	x["xor"] = XOR;
	x["xori"] = XORI;
	x["not"] = NOT;
	x["mov"] = MOV;
	x["addd"] = ADDD;
	x["subd"] = SUBD;
	x["muld"] = MULD;
	x["divd"] = DIVD;
	x["itod"] = ITOD;
	x["dtoi"] = DTOI;
	x["push"] = PUSH;
	x["pop"] = POP;
	x["call"] = CALL;
	x["calli"] = CALLI;
	x["ret"] = RET;
	x["cmp"] = CMP;
	x["cmpi"] = CMPI;
	x["cmpd"] = CMPD;
	x["jmp"] = JMP;
	x["jne"] = JNE;
	x["jeq"] = JEQ;
	x["jle"] = JLE;
	x["jl"] = JL;
	x["jge"] = JGE;
	x["jg"] = JG;
	x["load"] = LOAD;
	x["store"] = STORE;
	x["load2"] = LOAD2;
	x["store2"] = STORE2;
	x["loadr"] = LOADR;
	x["storer"] = STORER;
	x["loadr2"] = LOADR2;
	x["storer2"] = STORER2;
}

void fill_code_type(map <int, int> &x)
{
	x[HALT] = RI;
	x[SYSCALL] = RI;
	x[ADD] = RR;
	x[ADDI] = RI;
	x[SUB] = RR;
	x[SUBI] = RI;
	x[MUL] = RR;
	x[MULI] = RI;
	x[DIV] = RR;
	x[DIVI] = RI;
	x[LC] = RI;
	x[SHL] = RR;
	x[SHLI] = RI;
	x[SHR] = RR;
	x[SHRI] = RI;
	x[AND] = RR;
	x[ANDI] = RI;
	x[OR] = RR;
	x[ORI] = RI;
	x[XOR] = RR;
	x[XORI] = RI;
	x[NOT] = RI;
	x[MOV] = RR;
	x[ADDD] = RR;
	x[SUBD] = RR;
	x[MULD] = RR;
	x[DIVD] = RR;
	x[ITOD] = RR;
	x[DTOI] = RR;
	x[PUSH] = RI;
	x[POP] = RI;
	x[CALL] = RR;
	x[CALLI] = J;
	x[RET] = J; // RI initially
	x[CMP] = RR;
	x[CMPI] = RI;
	x[CMPD] = RR;
	x[JMP] = J;
	x[JNE] = J;
	x[JEQ] = J;
	x[JLE] = J;
	x[JL] = J;
	x[JGE] = J;
	x[JG] = J;
	x[LOAD] = RM;
	x[STORE] = RM;
	x[LOAD2] = RM;
	x[STORE2] = RM;
	x[LOADR] = RR;
	x[STORER] = RR;
	x[LOADR2] = RR;
	x[STORER2] = RR;
}

void rm_asm(int code_enum, string& str_line, int name_place, vector <int>& mem, int pc, map <string, int>& labels)
{
	mem[pc] = code_enum << 24;
	int reg_place = str_line.find('r', name_place) + 1;
	int end_reg = str_line.find(' ', reg_place);
	if ((int)str_line[end_reg] - 1 == ',') {
		end_reg--;
	}
	int reg = stoi(str_line.substr(reg_place, end_reg -reg_place));
	mem[pc] |= reg << 20;


	int beg_point = str_line.find(' ', reg_place);
	while ((int)str_line[beg_point + 1] == ' ') {
		beg_point++;
	}
	char first_sign = str_line[beg_point + 1];
	int end_point = str_line.find('\n');
	if ((int)str_line.find(' ', beg_point + 1) != -1) {
		end_point = str_line.find(' ', beg_point + 1);
	}
	int number = 0; 
	if ((first_sign >= '0' && first_sign <= '9') || first_sign == '-') {
		number = stoi(str_line.substr(beg_point + 1, end_point - beg_point - 1));
	}
	else {
		number = labels[str_line.substr(beg_point + 1, end_point - beg_point - 1)];
	}
	mem[pc] |= number & (1024 * 1024 - 1);
}
void rr_asm(int code_enum, string& str_line, int name_place, vector <int>& mem, int pc)
{
	mem[pc] = code_enum << 24;
	int reg_place = 0;
	int reg = 0;
	for (int i = 0; i < 2; i++)
	{
		reg_place = str_line.find('r', max(reg_place, name_place)) + 1;
		int end_reg = str_line.find(' ', reg_place);
		if (str_line[end_reg] - 1 == ',') {
			end_reg--;
		}
		reg = stoi(str_line.substr(reg_place, end_reg - reg_place));
		mem[pc] |= reg << (20 - 4 * i);
	}
	int beg_point = str_line.find(' ', reg_place);
	while (str_line[beg_point + 1] == ' ') {
		beg_point++;
	}
	int end_point = str_line.find('\n');
	if ((int)str_line.find(' ', beg_point + 1) != -1) {
		end_point = str_line.find(' ', beg_point + 1);
	}
	int number = stoi(str_line.substr(beg_point + 1, end_point - beg_point - 1));
	mem[pc] |= number & (65536 - 1);
}
void ri_asm(int code_enum, string &str_line, int name_place, vector <int> &mem, int pc, map <string, int>& labels)
{
	rm_asm(code_enum, str_line, name_place, mem, pc, labels);
}
void j_asm(int code_enum, string& str_line, int name_place, vector <int>& mem, int pc, map <string, int>& labels)
{
	mem[pc] = code_enum << 24;
	// can throw an error with label that starts with '-'
	char first_sign = str_line[str_line.find(' ', name_place) + 1];
	int beg_point = str_line.find(' ', name_place);
	while (str_line[beg_point + 1] == ' ') {
		beg_point++;
	}
	int end_point = str_line.find('\n');
	if ((int)str_line.find(' ', beg_point + 1) != -1) {
		end_point = str_line.find(' ', beg_point + 1);
	}
	int number = 0;
	if ((first_sign >= '0' && first_sign <= '9') || first_sign == '-') {
		number = stoi(str_line.substr(beg_point + 1, end_point - beg_point - 1));
	}
	else {
		number = labels[str_line.substr(beg_point + 1, end_point - beg_point - 1)];
	}
	mem[pc] |= number & (1024 * 1024 - 1);
}

void get_ri(int code_enum, int &reg1, int &number)
{
	reg1 = (code_enum >> 20) & (16 - 1);
	number = code_enum & (1024 * 1024 - 1);
	if (number >= 1024 * 512) {
		number -= 1024 * 1024;
	}
}
void get_rr(int code_enum, int& reg1, int& reg2, int& number)
{
	reg1 = (code_enum >> 20) & (16 - 1);
	reg2 = (code_enum >> 16) & (16 - 1);
	number = code_enum & (65536 - 1);
	if (number >= 256 * 128) {
		number -= 65536;
	}
}
void get_j(int code_enum, int& number)
{
	number = code_enum & (1024 * 1024 - 1);
	if (number >= 1024 * 512) {
		number -= 1024 * 1024;
	}
}

int main()
{
	FILE* input_file = fopen("input.fasm", "r");
	vector <int> mem(1024 * 1024, 0);
	int regs[16] = { 0 };
	bool flags[2] = { false }; // First flag - less, second flag - equal(zero)
	map <string, int> labels;
	map <string, int> name_code;
	map <int, int> code_type;
	map <string, double> labels_double;
	fill_name_code(name_code);
	fill_code_type(code_type);

	// First step
	int not_func_count = 0;
	const int max_size = 128;
	string last_label_found = "";
	int line_count = 0;

	while (!feof(input_file))
	{
		char line_char[max_size];
		fgets(line_char, max_size, input_file);
		string str_line = line_char;
		string func_str = "";
		bool colon_found = false;
		bool smth_found = false;
		bool func_started = false;
		for (int i = 0; i < (int)str_line.size(); i++)
		{
			if (str_line[i] >= 'a' && str_line[i] <= 'z') {
				func_started = true;
				smth_found = true;
				func_str += str_line[i];
				if (colon_found) {
					not_func_count--;
					colon_found = false;
				}
			} 
			else if (str_line[i] >= '0' && str_line[i] <= '9') {
				if (func_started) {
					func_str += str_line[i];
				}
			}
			else if (str_line[i] == ':') {
				labels[func_str] = line_count - not_func_count;
				last_label_found = func_str;
				func_str = "";
				colon_found = true;
				not_func_count++;
			}
			else if (str_line[i] == ';') {
				if (smth_found == false) {
					not_func_count++;
				}
				continue;
			}
			else if (str_line[i] == ' ' || str_line[i] == '\t' || str_line[i] == '\n') {
				if (func_str == "end") {
					not_func_count++;
					continue;
				}
				else if (func_str == "word") {
					int beg_point = str_line.find(' ', i);
					while (str_line[beg_point + 1] == ' ') beg_point++;
					int end_point = str_line.find('\n', beg_point + 1);
					if (str_line.find(' ', beg_point + 1) != -1) end_point = str_line.find(' ', beg_point + 1);
					labels[last_label_found] = stoi(str_line.substr(beg_point + 1, end_point - beg_point - 1));
					not_func_count++;
				}
				else if (func_str == "double") {
					int beg_point = str_line.find(' ', i);
					while (str_line[beg_point + 1] == ' ') beg_point++;
					int end_point = str_line.find('\n', beg_point + 1);
					if (str_line.find(' ', beg_point + 1) != -1) end_point = str_line.find(' ', beg_point + 1);
					labels_double[last_label_found] = stod(str_line.substr(beg_point + 1, end_point - beg_point - 1));
					not_func_count++;
				}
				func_str = "";
				func_started = false;
			}
		}
		line_count++;
	}

	// Second step
	int pc = 0;
	fseek(input_file, 0, SEEK_SET);

	while (!feof(input_file))
	{
		char line_char[max_size];
		fgets(line_char, max_size, input_file);
		string str_line = line_char;
		
		if (str_line.find(':') != -1) {
			bool f = true;
			for (int i = str_line.find(':'); i < (int)str_line.size(); i++)
			{
				if (str_line[i] >= 'a' && str_line[i] <= 'z') {
					f = false;
					break;
				}
			}
			if (f) continue;
		}

		if (str_line == "\n") {
			continue;
		}

		int end_label = str_line.find("end"); // Can throw and error with label end:
		if (end_label != -1) {
			int beg_point = end_label + 3;
			while (str_line[beg_point + 1] == ' ') beg_point++;
			int end_point = str_line.find('\n');
			if (str_line.find(' ', beg_point + 1) != -1) end_point = str_line.find(' ', beg_point + 1);
			string start_string = str_line.substr(beg_point + 1, end_point - beg_point - 1);
			regs[15] = labels[start_string];
			continue;
		}

		for (int i = str_line.find(':') + 1; (unsigned)i < str_line.size(); i++)
		{
			if (str_line[i] != ' ' && str_line[i] != '\t') {
				if (str_line[i] == ';') {
					break;
				}
				string func_name = str_line.substr(i, str_line.find(' ', i) - i);
				if (func_name == "word" || func_name == "double") {
					break;
				}
				else if (name_code.find(func_name) != name_code.end()) {
					mem[pc] = 0;
					switch (code_type[name_code[func_name]])
					{
						case RM:
							rm_asm(name_code[func_name], str_line, (int)func_name.size() + i, mem, pc, labels);
							break;
						case RR:
							rr_asm(name_code[func_name], str_line, (int)func_name.size() + i, mem, pc);
							break;
						case RI:
							ri_asm(name_code[func_name], str_line, (int)func_name.size() + i, mem, pc, labels);
							break;
						case J:
							j_asm(name_code[func_name], str_line, (int)func_name.size() + i, mem, pc, labels);
							break;
					}
					pc++;
				}
				else cout << "name_code find error " << func_name << " in line: " << str_line <<  endl;
				break;
			}
		}
	}

	fclose(input_file);

	regs[14] = 1048575;
	// Emulator
	bool running = true;
	while (running)
	{
		int code = mem[regs[15]];
		#ifdef DEBUG
		cout << "regs: ";
		for (int i = 0; i < 16; i++)
		{
			cout << regs[i] << " ";
		}
		cout << endl;
		cout << "less: " << flags[0] << ", zero: " << flags[1] << endl;
		cout << "stack: ";
		for (int i = 1048574; i >= regs[14]; i--) {
			cout << mem[i] << " ";
		}
		cout << endl;
		#endif
		regs[15]++;
		int func_code = code >> 24;
		int reg1 = 0;
		int reg2 = 0;
		int number = 0;
		switch (func_code)
		{
		case HALT: {
			running = false;
			cout << "exit with halt" << endl;
		}
				 break;
		case SYSCALL: {
			get_ri(code, reg1, number);

			switch (number)
			{
			case EXIT: {
				//cout << "exit with code 0" << endl;
				running = false;
			}
					 break;
			case SCANINT: {
				cin >> regs[reg1];
			}
						break;
			case SCANDOUBLE: {
				double a;
				cin >> a;
				double_to_int(a, regs[reg1], regs[reg1 + 1]);
			}
						   break;
			case PRINTINT: {
				cout << regs[reg1];
			}
						 break;
			case PRINTDOUBLE: {
				double a;
				int_to_double(a, regs[reg1], regs[reg1 + 1]);
				printf("%lg", a);
			}
							break;
			case GETCHAR: {
				regs[reg1] = getchar();
			}
						break;
			case PUTCHAR: {
				putchar(regs[reg1]);
			}
						break;
			}
		}
					break;
		case ADD: {
			get_rr(code, reg1, reg2, number);
			regs[reg1] += regs[reg2] + number;
		}
				break;
		case ADDI: {
			get_ri(code, reg1, number);
			regs[reg1] += number;
		}
				 break;
		case SUB: {
			get_rr(code, reg1, reg2, number);
			regs[reg1] -= regs[reg2] + number;
		}
				break;
		case SUBI: {
			get_ri(code, reg1, number);
			regs[reg1] -= number;
		}
				 break;
		case MUL: {
			get_rr(code, reg1, reg2, number);
			long long result = regs[reg1] * ((long long)regs[reg2] + number);
			long_long_to_int(result, regs[reg1], regs[reg1 + 1]);
		}
				break;
		case MULI: {
			get_ri(code, reg1, number);
			long long result = (long long)regs[reg1] * (long long)number;
			long_long_to_int(result, regs[reg1], regs[reg1 + 1]);
		}
				 break;
		case DIV: {
			get_rr(code, reg1, reg2, number);
			long long div_num = (long long)regs[reg1] + ((long long)regs[reg1 + 1] << 32);
			regs[reg1] = (int)(div_num / (long long)regs[reg2]);
			regs[reg1 + 1] = (int)(div_num % (long long)regs[reg2]);
		}
				break;
		case DIVI: {
			get_ri(code, reg1, number);
			long long div_num = (long long)regs[reg1] + ((long long)regs[reg1 + 1] << 32);
			regs[reg1] = (int)(div_num / (long long)number);
			regs[reg1 + 1] = (int)(div_num % (long long)number);
		}
				 break;
		case LC: {
			get_ri(code, reg1, number);
			regs[reg1] = number;
		}
			   break;
		case SHL: {
			get_rr(code, reg1, reg2, number);
			regs[reg1] <<= regs[reg2];
		}
				break;
		case SHLI: {
			get_ri(code, reg1, number);
			regs[reg1] <<= number;
		}
				 break;
		case SHR: {
			get_rr(code, reg1, reg2, number);
			regs[reg1] >>= regs[reg2];
		}
				break;
		case SHRI: {
			get_ri(code, reg1, number);
			regs[reg1] >>= number;
		}
				 break;
		case AND: {
			get_rr(code, reg1, reg2, number);
			regs[reg1] &= regs[reg2];
		}
				break;
		case ANDI: {
			get_ri(code, reg1, number);
			regs[reg1] &= number;
		}
				 break;
		case OR: {
			get_rr(code, reg1, reg2, number);
			regs[reg1] |= regs[reg2];
		}
			   break;
		case ORI: {
			get_ri(code, reg1, number);
			regs[reg1] |= number;
		}
				break;
		case XOR: {
			get_rr(code, reg1, reg2, number);
			regs[reg1] ^= regs[reg2];
		}
				break;
		case XORI: {
			get_ri(code, reg1, number);
			regs[reg1] ^= number;
		}
				 break;
		case NOT: {
			get_ri(code, reg1, number);
			regs[reg1] = ~regs[reg1];
		}
				break;
		case MOV: {
			get_rr(code, reg1, reg2, number);
			regs[reg1] = regs[reg2] + number;
		}
				break;
		case ADDD: {
			get_rr(code, reg1, reg2, number);
			double a1 = 0;
			double a2 = 0;
			int_to_double(a1, regs[reg1], regs[reg1 + 1]);
			int_to_double(a2, regs[reg2], regs[reg2 + 1]);
			double result = a1 + a2;
			double_to_int(result, regs[reg1], regs[reg1 + 1]);
		}
				 break;
		case SUBD: {
			get_rr(code, reg1, reg2, number);
			double a1 = 0;
			double a2 = 0;
			int_to_double(a1, regs[reg1], regs[reg1 + 1]);
			int_to_double(a2, regs[reg2], regs[reg2 + 1]);
			double result = a1 - a2;
			double_to_int(result, regs[reg1], regs[reg1 + 1]);
		}
				 break;
		case MULD: {
			get_rr(code, reg1, reg2, number);
			double a1 = 0;
			double a2 = 0;
			int_to_double(a1, regs[reg1], regs[reg1 + 1]);
			int_to_double(a2, regs[reg2], regs[reg2 + 1]);
			double result = a1 * a2;
			double_to_int(result, regs[reg1], regs[reg1 + 1]);
		}
				 break;
		case DIVD: {
			get_rr(code, reg1, reg2, number);
			double a1 = 0;
			double a2 = 0;
			int_to_double(a1, regs[reg1], regs[reg1 + 1]);
			int_to_double(a2, regs[reg2], regs[reg2 + 1]);
			double result = a1 / a2;
			double_to_int(result, regs[reg1], regs[reg1 + 1]);
		}
				 break;
		case ITOD: {
			get_rr(code, reg1, reg2, number);
			double a = (double)regs[reg2];
			double_to_int(a, regs[reg1], regs[reg1 + 1]);
		}
				 break;
		case DTOI: {
			get_rr(code, reg1, reg2, number);
			double a;
			int_to_double(a, regs[reg2], regs[reg2 + 1]);
			regs[reg1] = (int)a;
		}
				 break;
		case PUSH: {
			get_ri(code, reg1, number);
			regs[14]--;
			mem[regs[14]] = regs[reg1] + number;
		}
				 break;
		case POP: {
			get_ri(code, reg1, number);
			regs[reg1] = mem[regs[14]] + number;
			regs[14]++;
		}
				break;
		case CALL: {
			get_rr(code, reg1, reg2, number);
			regs[14]--;
			mem[regs[14]] = regs[15];
			regs[15] = regs[reg2] + number;
			regs[reg1] = regs[15];
		}
				 break;
		case CALLI: {
			get_j(code, number);
			regs[14]--;
			mem[regs[14]] = regs[15];
			regs[15] = number;
		}
				  break;
		case RET: {
			get_j(code, number);

			regs[15] = mem[regs[14]];
			regs[14]++;
			regs[14] += number;
		}
				break;
		case CMP: {
			get_rr(code, reg1, reg2, number);
			int a = regs[reg1] - regs[reg2];
			flags[0] = a < 0;
			flags[1] = a == 0;
		}
				break;
		case CMPI: {
			get_ri(code, reg1, number);
			int a = regs[reg1] - number;
			flags[0] = a < 0;
			flags[1] = a == 0;
		}
				 break;
		case CMPD: {
			get_rr(code, reg1, reg2, number);
			double a1;
			double a2;
			int_to_double(a1, regs[reg1], regs[reg1 + 1]);
			int_to_double(a2, regs[reg1], regs[reg1 + 1]);
			double a = a1 - a2;
			flags[0] = a < 0;
			flags[1] = a == 0;
		}
				 break;
		case JMP: {
			get_j(code, number);
			regs[15] = number;
		}
				break;
		case JNE: {
			get_j(code, number);
			if (flags[1] == 0) regs[15] = number;
		}
				break;
		case JEQ: {
			get_j(code, number);
			if (flags[1] == 1) regs[15] = number;
		}
				break;
		case JLE: {
			get_j(code, number);
			if (flags[0] == 1 || flags[1] == 1) regs[15] = number;
		}
				break;
		case JL: {
			get_j(code, number);
			if (flags[0] == 1 && flags[1] == 0) regs[15] = number;
		}
			   break;
		case JGE: {
			get_j(code, number);
			if (flags[0] == 0 || flags[1] == 1) regs[15] = number;
		}
				break;
		case JG: {
			get_j(code, number);
			if (flags[0] == 0 && flags[1] == 0) regs[15] = number;
		}
			   break;
		case LOAD: {
			get_ri(code, reg1, number);
			regs[reg1] = mem[number];
		}
				 break;
		case STORE: {
			get_ri(code, reg1, number);
			mem[number] = regs[reg1];
		}
				  break;
		case LOAD2: {
			get_ri(code, reg1, number);
			regs[reg1] = mem[number];
			regs[reg1 + 1] = mem[number + 1];
		}
				  break;
		case STORE2: {
			get_ri(code, reg1, number);
			mem[number] = regs[reg1];
			mem[number + 1] = regs[reg1 + 1];
		}
				   break;
		case LOADR: {
			get_rr(code, reg1, reg2, number);
			regs[reg1] = mem[number + regs[reg2]];
		}
				  break;
		case STORER: {
			get_rr(code, reg1, reg2, number);
			mem[number + regs[reg2]] = regs[reg1];
		}
				   break;
		case LOADR2: {
			get_rr(code, reg1, reg2, number);
			regs[reg1] = mem[number + regs[reg2]];
			regs[reg1 + 1] = mem[number + regs[reg2] + 1];
		}
				   break;
		case STORER2: {
			get_rr(code, reg1, reg2, number);
			mem[number + regs[reg2]] = regs[reg1];
			mem[number + regs[reg2] + 1] = regs[reg1 + 1];
		}
					break;
		}
	}
}
