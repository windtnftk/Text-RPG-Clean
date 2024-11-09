#include "pch.h"
#include "Default.h"
#include "set"


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

bool Yes_No() {
	std::string boolinput;
	const std::set<std::string> validYes = { "yes", "y" };
	const std::set<std::string> validNo = { "no", "n" };

	while (true) {
		std::cout << "yes �Ǵ� no�� �Է����ֽʽÿ� "<<std::endl<<"�Է�: ";
		std::cin >> boolinput;

		// �Է��� �ҹ��ڷ� ��ȯ
		std::transform(boolinput.begin(), boolinput.end(), boolinput.begin(), ::tolower);

		if (validYes.count(boolinput)) {
			return true;
		}
		else if (validNo.count(boolinput)) {
			return false;
		}
		else {
			ErrorCode(); // �߸��� �Է� �޽��� ���
		}
	}
}
