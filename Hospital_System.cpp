#include <iostream>

std::string names[21][6];
int status[21][6]{ 0 };
int queue_length[21]{ 0 };

int Menu()
{
	int choice = -1;
	while (choice == -1)
	{
		std::cout << "1) Add new patient\n";
		std::cout << "2) Print all the patients\n";
		std::cout << "3) get next patient\n";
		std::cout << "4) Exit\n";
		std::cin >> choice;
	}
	return choice;
}

int shift_right(int spec,int len)
{
	int pos = 1;
	for (int i = len; i > 1; i--)
	{
		if (status[spec][i] != 1)
		{
			names [spec][i + 1] = names [spec][i];
			status[spec][i + 1] = status[spec][i];
		}
		else
		{
			pos = i + 1;
			break;
		}
	}
	return pos;
}

void add_new_patient()
{
	std::cout << "Enter the specialization number , your name , status\n";
	int spec; std::cin >> spec;
	std::string name; std::cin >> name;
	int stat; std::cin >> stat;

	if (queue_length[spec] >= 5)
	{
		std::cout << "Sorry, we don't have room today\n";
		return;
	}
	int len = queue_length[spec];

	if (stat == 1 && len != 0)
	{
		int pos = shift_right(spec, len);
		names[spec][pos] = name;
		status[spec][pos] = stat;
		++queue_length[spec];
	}
	else
	{
		names  [spec][++queue_length[spec]] = name;
		status [spec][queue_length[spec]] = stat;
	}
}

void print_spec_patients(int spec)
{
	int len = queue_length[spec];
	for (size_t i = 1; i <= len; i++)
	{
		std::cout << names[spec][i] << "  ";
		(status[spec][i] == 1) ? std::cout << " urgent\n" : std::cout << " regular\n";
	}
}  
void print_all_patients()
{
	for (size_t i = 1; i < 21; i++)
	{
		if (queue_length[i] != 0)
		{
			std::cout << "There are " << queue_length[i] << " patients in spec" << i << '\n';
			print_spec_patients(i);
		}
		else
			continue;
	}
}

void shift_left(int spec)
{
	int len = queue_length[spec];
	for (size_t i = 1; i <= len+1; i++)
	{
		names [spec][i - 1] = names [spec][i];
		status[spec][i - 1] = status[spec][i];
	}
}

void get_next_patient()
{
	int spec;
	std::cout << "Please, Enter your spec\n";
	std::cin >> spec;
	int len = queue_length[spec]--;
	if (len != 0)
	{
		std::cout << "Please " << names[spec][1] << ", go with the Dr\n";
		shift_left(spec);
	}
	else
		std::cout << "No patients now, take a rest Dr\n";
}

void system()
{
	while (true)
	{
		int choice = Menu();
		if (choice == 1)
			add_new_patient();
		else if (choice == 2)
			print_all_patients();
		else if (choice == 3)
			get_next_patient();
		else if (choice == 4)
		{
			std::cout << "Have a nice day\n";
			break;
		}
		else
			Menu();
	}
	
}
int main()
{
	system();
}

