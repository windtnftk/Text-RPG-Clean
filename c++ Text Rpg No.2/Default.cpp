#include "pch.h"
#include "Default.h"



void ErrorCode() 
{
    std::wcout << L"�߸��� �Է��Դϴ�." << std::endl;
}
int CinAuto() {
	int choice;
	while (true) {
		std::cout << "���ڸ� �Է��ϼ���: ";
		std::cin >> choice;
		if (std::cin.fail()) {
			// �߸��� �Է��� �߻����� ���
			std::cin.clear(); // cin�� ���� ���� �÷��׸� �ʱ�ȭ
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // �Է� ���۸� ���ϴ�.
			std::cout << "�߸��� �Է��Դϴ�.\n";
		}
		else
		{
			// ��ȿ�� �Է��� ������ ���
			std::cout << std::endl;
			return choice; // �������� ��� �ݺ� ���� �� �� ��ȯ
		}
	}
}