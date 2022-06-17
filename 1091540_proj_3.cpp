#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>

using namespace std;

struct Inst
{
	bool issued;
	string I;
	string N;
	string D;
	string S1;
	string S2;
};

struct RS_Inst
{
	int order;
	string O;
	string s1;
	string s2;
};

class RF
{
public:
	RF()
	{
		int RF_content = 0;
		RFs.assign(6, to_string(RF_content));

		for (int i = 1; i <= 5; i++)
		{
			RFs[i] = to_string(RF_content);
			RF_content += 2;
		}
	}

	void printAll()
	{
		cout << "     _ RF __\n";
		cout << "  F1 |  " << setw(2) << RFs[1] << " | \n";
		cout << "  F2 |  " << setw(2) << RFs[2] << " | \n";
		cout << "  F3 |  " << setw(2) << RFs[3] << " | \n";
		cout << "  F4 |  " << setw(2) << RFs[4] << " | \n";
		cout << "  F5 |  " << setw(2) << RFs[5] << " | \n";
		cout << "     -------\n";
	}

	string get_RFs(int i)
	{
		return RFs[i];
	}

	void set_RFs(int i, string data)
	{
		RFs[i] = data;
	}
private:
	vector<string> RFs;
};

class RAT
{
public:
	RAT()
	{
		string RAT_content = "   ";
		RATs.assign(6, RAT_content);
	}

	void print_all()
	{
		cout << "     _ RAT __\n";
		cout << "  F1 |  " << RATs[1] << " |\n";
		cout << "  F2 |  " << RATs[2] << " |\n";
		cout << "  F3 |  " << RATs[3] << " |\n";
		cout << "  F4 |  " << RATs[4] << " |\n";
		cout << "  F5 |  " << RATs[5] << " |\n";
		cout << "     --------\n";
	}

	string get_RATs(int i)
	{
		return RATs[i];
	}

	void set_RATs(int i, string data)
	{
		RATs[i] = data;
	}

	bool empty()
	{
		for (int i = 1; i <= 5; i++)
		{
			if (RATs[i] != "   ")
			{
				return false;
			}
		}

		return true;
	}
private:
	vector<string> RATs;
};

class RS
{
public:
	RS()
	{
		RS_Inst RS_content;
		RS_content.O = " ";
		RS_content.s1 = "   ";
		RS_content.s2 = "   ";
		RSs.assign(6, RS_content);
		Buffers.assign(2, "empty");
	}

	void print_all()
	{
		cout << "    _ RS _________________\n";
		cout << "RS1 |    " << RSs[1].O << " |  " << setw(3) << RSs[1].s1 << " |  " << setw(3) << RSs[1].s2 << " |\n";
		cout << "RS2 |    " << RSs[2].O << " |  " << setw(3) << RSs[2].s1 << " |  " << setw(3) << RSs[2].s2 << " |\n";
		cout << "RS3 |    " << RSs[3].O << " |  " << setw(3) << RSs[3].s1 << " |  " << setw(3) << RSs[3].s2 << " |\n";
		cout << "    ----------------------\n";
		cout << "BUFFER: " << Buffers[0] << "\n";
		cout << "\n";
		cout << "    ______________________\n";
		cout << "RS4 |    " << RSs[4].O << " |  " << setw(3) << RSs[4].s1 << " |  " << setw(3) << RSs[4].s2 << " |\n";
		cout << "RS5 |    " << RSs[5].O << " |  " << setw(3) << RSs[5].s1 << " |  " << setw(3) << RSs[5].s2 << " |\n";
		cout << "    ----------------------\n";
		cout << "BUFFER: " << Buffers[1] << "\n";
	}

	int left_not_full()
	{
		for (int i = 1; i <= 3; i++)
		{
			if (RSs[i].O == " " && RSs[i].s1 == "   " && RSs[i].s2 == "   ")
			{
				return i;
			}
		}

		return 0;
	}

	int right_not_full()
	{
		for (int i = 4; i <= 5; i++)
		{
			if (RSs[i].O == " " && RSs[i].s1 == "   " && RSs[i].s2 == "   ")
			{
				return i;
			}
		}

		return 0;
	}

	RS_Inst get_RSs(int i)
	{
		return RSs[i];
	}

	void set_RSs(int i, RS_Inst data)
	{
		RSs[i] = data;
	}

	void set_RSs_1(int i, string data)
	{
		RSs[i].s1 = data;
	}

	void set_RSs_2(int i, string data)
	{
		RSs[i].s2 = data;
	}

	string get_Buffers(int i)
	{
		return Buffers[i];
	}

	void set_Buffers(int i, string data)
	{
		Buffers[i] = data;
	}

	void change_order(int i, int data)
	{
		RSs[i].order = data;
	}

	bool empty()
	{
		for (int i = 1; i <= 5; i++)
		{
			if (RSs[i].O != " " || RSs[i].s1 != "   " || RSs[i].s2 != "   ")
			{
				return false;
			}
		}

		return true;
	}
private:
	vector<RS_Inst> RSs;
	vector<string> Buffers;
};

int main()
{
	vector<Inst> IQ;

	for (int i = 0; i < 8; i++)
	{
		string buffer = "";
		getline(cin, buffer);

		Inst temp;
		temp.I = buffer;

		stringstream ss;
		ss << buffer;

		ss >> buffer;
		temp.N = buffer;

		ss >> buffer;
		buffer.erase(buffer.end() - 1);
		temp.D = buffer;

		ss >> buffer;
		buffer.erase(buffer.end() - 1);
		temp.S1 = buffer;

		ss >> buffer;
		temp.S2 = buffer;

		temp.issued = false;

		IQ.emplace_back(temp);
	}

	int cycle = 0;

	RF register_file;
	RAT register_allocation_table;
	RS reservation_station;

	while (cycle < 13)
	{
		++cycle;

		for (int i = 1; i <= 5; i++)
		{
			if (reservation_station.get_RSs(i).O != " ")
			{
				reservation_station.change_order(i, reservation_station.get_RSs(i).order + 1);
			}
		}

		vector<Inst>::iterator it = IQ.end();

		for (int i = 0; i < IQ.size(); i++)
		{
			if (!IQ[i].issued)
			{
				it = IQ.begin() + i;
				break;
			}
		}

		if (it != IQ.end())
		{
			if (it->N == "ADDI" || it->N == "ADD" || it->N == "SUB")
			{
				if (reservation_station.left_not_full() != 0)
				{
					RS_Inst current;

					if (it->N == "ADDI")
					{
						current.O = "+";
						string register_num_1 = it->S1;
						register_num_1.erase(register_num_1.begin());

						if (register_allocation_table.get_RATs(stoi(register_num_1)) != "   ")
						{
							current.s1 = register_allocation_table.get_RATs(stoi(register_num_1));
						}
						else
						{
							current.s1 = register_file.get_RFs(stoi(register_num_1));
						}

						current.s2 = it->S2;
						current.order = 0;
					}
					else if (it->N == "ADD")
					{
						current.O = "+";
						string register_num_1 = it->S1;
						register_num_1.erase(register_num_1.begin());

						if (register_allocation_table.get_RATs(stoi(register_num_1)) != "   ")
						{
							current.s1 = register_allocation_table.get_RATs(stoi(register_num_1));
						}
						else
						{
							current.s1 = register_file.get_RFs(stoi(register_num_1));
						}

						string register_num_2 = it->S2;
						register_num_2.erase(register_num_2.begin());

						if (register_allocation_table.get_RATs(stoi(register_num_2)) != "   ")
						{
							current.s2 = register_allocation_table.get_RATs(stoi(register_num_2));
						}
						else
						{
							current.s2 = register_file.get_RFs(stoi(register_num_2));
						}

						current.order = 0;
					}
					else if (it->N == "SUB")
					{
						current.O = "-";
						string register_num_1 = it->S1;
						register_num_1.erase(register_num_1.begin());

						if (register_allocation_table.get_RATs(stoi(register_num_1)) != "   ")
						{
							current.s1 = register_allocation_table.get_RATs(stoi(register_num_1));
						}
						else
						{
							current.s1 = register_file.get_RFs(stoi(register_num_1));
						}

						string register_num_2 = it->S2;
						register_num_2.erase(register_num_2.begin());

						if (register_allocation_table.get_RATs(stoi(register_num_2)) != "   ")
						{
							current.s2 = register_allocation_table.get_RATs(stoi(register_num_2));
						}
						else
						{
							current.s2 = register_file.get_RFs(stoi(register_num_2));
						}

						current.order = 0;
					}

					string register_num = it->D;
					register_num.erase(register_num.begin());
					int left_RS_empty = reservation_station.left_not_full();

					switch (left_RS_empty)
					{
					case 1:
						reservation_station.set_RSs(1, current);
						register_allocation_table.set_RATs(stoi(register_num), "RS1");
						break;
					case 2:
						reservation_station.set_RSs(2, current);
						register_allocation_table.set_RATs(stoi(register_num), "RS2");
						break;
					case 3:
						reservation_station.set_RSs(3, current);
						register_allocation_table.set_RATs(stoi(register_num), "RS3");
						break;
					default:
						break;
					}

					it->issued = true;
				}
			}
			else if (it->N == "MUL" || it->N == "DIV")
			{
				if (reservation_station.right_not_full() != 0)
				{
					RS_Inst current;

					if (it->N == "MUL")
					{
						current.O = "*";
						string register_num_1 = it->S1;
						register_num_1.erase(register_num_1.begin());

						if (register_allocation_table.get_RATs(stoi(register_num_1)) != "   ")
						{
							current.s1 = register_allocation_table.get_RATs(stoi(register_num_1));
						}
						else
						{
							current.s1 = register_file.get_RFs(stoi(register_num_1));
						}

						string register_num_2 = it->S2;
						register_num_2.erase(register_num_2.begin());

						if (register_allocation_table.get_RATs(stoi(register_num_2)) != "   ")
						{
							current.s2 = register_allocation_table.get_RATs(stoi(register_num_2));
						}
						else
						{
							current.s2 = register_file.get_RFs(stoi(register_num_2));
						}

						current.order = 0;
					}
					else if (it->N == "DIV")
					{
						current.O = "/";
						string register_num_1 = it->S1;
						register_num_1.erase(register_num_1.begin());

						if (register_allocation_table.get_RATs(stoi(register_num_1)) != "   ")
						{
							current.s1 = register_allocation_table.get_RATs(stoi(register_num_1));
						}
						else
						{
							current.s1 = register_file.get_RFs(stoi(register_num_1));
						}

						string register_num_2 = it->S2;
						register_num_2.erase(register_num_2.begin());

						if (register_allocation_table.get_RATs(stoi(register_num_2)) != "   ")
						{
							current.s2 = register_allocation_table.get_RATs(stoi(register_num_2));
						}
						else
						{
							current.s2 = register_file.get_RFs(stoi(register_num_2));
						}

						current.order = 0;
					}

					string register_num = it->D;
					register_num.erase(register_num.begin());
					int right_RS_empty = reservation_station.right_not_full();

					switch (right_RS_empty)
					{
					case 4:
						reservation_station.set_RSs(4, current);
						register_allocation_table.set_RATs(stoi(register_num), "RS4");
						break;
					case 5:
						reservation_station.set_RSs(5, current);
						register_allocation_table.set_RATs(stoi(register_num), "RS5");
						break;
					default:
						break;
					}

					it->issued = true;
				}
			}
		}

		if (reservation_station.get_Buffers(0) == "empty")
		{
			int min_order_1 = 10000;

			for (int i = 1; i <= 3; i++)
			{
				if (reservation_station.get_RSs(i).O != " ")
				{
					if (reservation_station.get_RSs(i).s1.find('R') == string::npos && reservation_station.get_RSs(i).s2.find('R') == string::npos)
					{
						if (reservation_station.get_RSs(i).order > 0)
						{
							if (reservation_station.get_RSs(i).order < min_order_1)
							{
								min_order_1 = reservation_station.get_RSs(i).order;
							}
						}
					}
				}
			}

			string buffer_content_0 = "empty";

			for (int i = 1; i <= 3; i++)
			{
				if (reservation_station.get_RSs(i).O != " ")
				{
					if (reservation_station.get_RSs(i).order == min_order_1)
					{
						buffer_content_0 = "(RS" + to_string(i) + ") " + reservation_station.get_RSs(i).s1 + " " + reservation_station.get_RSs(i).O + " " + reservation_station.get_RSs(i).s2;
						reservation_station.set_Buffers(0, buffer_content_0);
						break;
					}
				}
			}
		}
		else
		{
			for (int i = 1; i <= 3; i++)
			{
				if (reservation_station.get_RSs(i).O != " ")
				{
					if (i != reservation_station.get_Buffers(0)[3] - 48 && reservation_station.get_RSs(i).order > 0)
					{
						reservation_station.change_order(i, reservation_station.get_RSs(i).order - 1);
					}
				}
			}
		}

		if (reservation_station.get_Buffers(0) == "empty" && reservation_station.get_Buffers(1) == "empty")
		{
			int min_order_2 = 10000;

			for (int i = 4; i <= 5; i++)
			{
				if (reservation_station.get_RSs(i).O != " ")
				{
					if (reservation_station.get_RSs(i).s1.find('R') == string::npos && reservation_station.get_RSs(i).s2.find('R') == string::npos)
					{
						if (reservation_station.get_RSs(i).order > 0)
						{
							if (reservation_station.get_RSs(i).order < min_order_2)
							{
								min_order_2 = reservation_station.get_RSs(i).order;
							}
						}
					}
				}
			}

			string buffer_content_1 = "empty";

			for (int i = 4; i <= 5; i++)
			{
				if (reservation_station.get_RSs(i).O != " ")
				{
					if (reservation_station.get_RSs(i).order == min_order_2)
					{
						buffer_content_1 = "(RS" + to_string(i) + ") " + reservation_station.get_RSs(i).s1 + " " + reservation_station.get_RSs(i).O + " " + reservation_station.get_RSs(i).s2;
						reservation_station.set_Buffers(1, buffer_content_1);
						break;
					}
				}
			}
		}
		else 
		{
			for (int i = 4; i <= 5; i++)
			{
				if (reservation_station.get_RSs(i).O != " ")
				{
					if (i != reservation_station.get_Buffers(1)[3] - 48 && reservation_station.get_RSs(i).order > 0)
					{
						reservation_station.change_order(i, reservation_station.get_RSs(i).order - 1);
					}
				}
			}
		}

		if (reservation_station.get_Buffers(0) != "empty" && reservation_station.get_RSs(reservation_station.get_Buffers(0)[3] - 48).order >= 2)
		{
			int t1, t2, result;

			if (reservation_station.get_RSs(reservation_station.get_Buffers(0)[3] - 48).O == "+")
			{
				t1 = stoi(reservation_station.get_RSs(reservation_station.get_Buffers(0)[3] - 48).s1);
				t2 = stoi(reservation_station.get_RSs(reservation_station.get_Buffers(0)[3] - 48).s2);
				result = t1 + t2;
			}
			else if (reservation_station.get_RSs(reservation_station.get_Buffers(0)[3] - 48).O == "-")
			{
				t1 = stoi(reservation_station.get_RSs(reservation_station.get_Buffers(0)[3] - 48).s1);
				t2 = stoi(reservation_station.get_RSs(reservation_station.get_Buffers(0)[3] - 48).s2);
				result = t1 - t2;
			}

			for (int i = 1; i <= 5; i++)
			{
				if (reservation_station.get_RSs(i).s1 == reservation_station.get_Buffers(0).substr(1, 3))
				{
					reservation_station.set_RSs_1(i, to_string(result));
				}

				if (reservation_station.get_RSs(i).s2 == reservation_station.get_Buffers(0).substr(1, 3))
				{
					reservation_station.set_RSs_2(i, to_string(result));
				}

				if (register_allocation_table.get_RATs(i) == reservation_station.get_Buffers(0).substr(1, 3))
				{
					register_file.set_RFs(i, to_string(result));
					register_allocation_table.set_RATs(i, "   ");
				}
			}

			RS_Inst new_RS_content;
			new_RS_content.O = " ";
			new_RS_content.s1 = "   ";
			new_RS_content.s2 = "   ";
			new_RS_content.order = 0;
			reservation_station.set_RSs(reservation_station.get_Buffers(0)[3] - 48, new_RS_content);
			reservation_station.set_Buffers(0, "empty");
		}
		else if (reservation_station.get_Buffers(1) != "empty" && reservation_station.get_RSs(reservation_station.get_Buffers(1)[3] - 48).order >= 2)
		{
			int t1, t2, result;

			if (reservation_station.get_RSs(reservation_station.get_Buffers(1)[3] - 48).O == "*")
			{
				t1 = stoi(reservation_station.get_RSs(reservation_station.get_Buffers(1)[3] - 48).s1);
				t2 = stoi(reservation_station.get_RSs(reservation_station.get_Buffers(1)[3] - 48).s2);
				result = t1 * t2;
			}
			else if (reservation_station.get_RSs(reservation_station.get_Buffers(1)[3] - 48).O == "/")
			{
				t1 = stoi(reservation_station.get_RSs(reservation_station.get_Buffers(1)[3] - 48).s1);
				t2 = stoi(reservation_station.get_RSs(reservation_station.get_Buffers(1)[3] - 48).s2);
				result = t1 / t2;
			}

			for (int i = 1; i <= 5; i++)
			{
				if (reservation_station.get_RSs(i).s1 == reservation_station.get_Buffers(1).substr(1, 3))
				{
					reservation_station.set_RSs_1(i, to_string(result));
				}

				if (reservation_station.get_RSs(i).s2 == reservation_station.get_Buffers(1).substr(1, 3))
				{
					reservation_station.set_RSs_2(i, to_string(result));
				}

				if (register_allocation_table.get_RATs(i) == reservation_station.get_Buffers(1).substr(1, 3))
				{
					register_file.set_RFs(i, to_string(result));
					register_allocation_table.set_RATs(i, "   ");
				}
			}

			RS_Inst new_RS_content;
			new_RS_content.O = " ";
			new_RS_content.s1 = "   ";
			new_RS_content.s2 = "   ";
			new_RS_content.order = 0;
			reservation_station.set_RSs(reservation_station.get_Buffers(1)[3] - 48, new_RS_content);
			reservation_station.set_Buffers(1, "empty");
		}

		cout << "Cycle: " << cycle << "\n\n";
		register_file.printAll();
		cout << "\n";
		register_allocation_table.print_all();
		cout << "\n";
		reservation_station.print_all();
		cout << "\n";
	}

	return 0;
}