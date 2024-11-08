#include "pch.h"
#include "Default.h"



void ErrorCode() 
{
    std::wcout << L"잘못된 입력입니다." << std::endl;
}
int CinAuto() {
	int choice;
	while (true) {
		std::cout << "숫자를 입력하세요: ";
		std::cin >> choice;
		if (std::cin.fail()) {
			// 잘못된 입력이 발생했을 경우
			std::cin.clear(); // cin의 오류 상태 플래그를 초기화
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 입력 버퍼를 비웁니다.
			std::cout << "잘못된 입력입니다.\n";
		}
		else
		{
			// 유효한 입력이 들어왔을 경우
			std::cout << std::endl;
			return choice; // 정상적인 경우 반복 종료 후 값 반환
		}
	}
}