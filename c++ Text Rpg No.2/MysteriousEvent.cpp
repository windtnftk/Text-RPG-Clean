#include "pch.h"
#include "MysteriousEvent.h"

void MysteriousEvent::Ez_Event1() const
{
	std::cout << "고대의 성소" << std::endl;
	std::cout << "당신은 " << std::endl
		<< "오래된 신전 앞에 섭니다." << std::endl
		<< "이 성소는 고대의 힘을 품고 있는 듯합니다." << std::endl
		<< "신전의 축복을 받을까요?" << std::endl;
	std::cout << "1) 축복을 받는다" << std::endl;
	std::cout << "2) 신전을 무시한다" << std::endl;
}

void MysteriousEvent::Ez_Event2() const
{
	std::cout << "저주받은 책" << std::endl;
	std::cout << "당신은 먼지 쌓인 오래된 책을 발견합니다." << std::endl
		<< "표지에는 기이한 문자가 새겨져 있습니다." << std::endl
		<< "책을 읽으면 힘을 얻을 수도 있지만, 저주의 위험도 있습니다." << std::endl;
	std::cout << "1) 책을 읽는다" << std::endl;
	std::cout << "2) 책을 두고 떠난다" << std::endl;
}

void MysteriousEvent::Ez_Event3() const
{
	std::cout << "상인과의 거래" << std::endl;
	std::cout << "덩굴로 뒤덮인 던전의 구석에서 상인을 만납니다." << std::endl
		<< "그는 다양한 물품을 판매하며, 일부는 조금 수상해 보입니다." << std::endl;
	std::cout << "1) 물건을 산다" << std::endl;
	std::cout << "2) 거래를 하지 않는다" << std::endl;
	while (true)
	{
		switch (CinAuto())
		{
		case 1: // 상점 함수 진행
		default:
			break;
		}

	}
	
}

void MysteriousEvent::Ez_Event4() const
{
	std::cout << "이상한 조각상" << std::endl;
	std::cout << "당신은 기이한 생물의 형상을 한 조각상을 발견합니다." << std::endl
		<< "조각상은 마치 당신을 지켜보는 듯합니다." << std::endl
		<< "무엇을 할까요?" << std::endl;
	std::cout << "1) 조각상을 만져본다" << std::endl;
	std::cout << "2) 무시하고 지나간다" << std::endl;
}

void MysteriousEvent::Ez_Event5() const
{
	std::cout << "함정에 걸린 보물 상자" << std::endl;
	std::cout << "당신은 반쯤 열려 있는 보물 상자를 발견합니다." << std::endl
		<< "그러나 주변에 함정이 있을 것 같은 불길한 기운이 느껴집니다." << std::endl;
	std::cout << "1) 상자를 열어본다" << std::endl;
	std::cout << "2) 상자를 무시한다" << std::endl;

}
void MysteriousEvent::Hard_Event1() const
{
	std::cout << "기이한 약초 상인" << std::endl;
	std::cout << "어두운 복도 끝에서 한 남자가 기이한 약초들을 판매하고 있습니다." << std::endl
		<< "그는 그것들이 전투에 도움이 된다고 주장합니다." << std::endl;
	std::cout << "1) 약초를 구입한다" << std::endl;
	std::cout << "2) 거절하고 떠난다" << std::endl;

}

void MysteriousEvent::Hard_Event2() const
{
	std::cout << "묘한 안개" << std::endl;
	std::cout << "당신은 갑자기 주변에 자욱한 안개가 깔리는 것을 느낍니다." << std::endl
		<< "안개 속으로 들어가면 알 수 없는 운명이 기다리고 있을 것입니다." << std::endl;
	std::cout << "1) 안개 속으로 들어간다" << std::endl;
	std::cout << "2) 안개를 피한다" << std::endl;
}

void MysteriousEvent::Hard_Event3() const
{
	std::cout << "배신한 전사" << std::endl;
	std::cout << "길을 가던 중 한 전사가 길을 막습니다." << std::endl
		<< "그는 도움이 필요한 척 접근하지만, 눈빛 속에 배신의 기운이 느껴집니다." << std::endl;
	std::cout << "1) 그의 말을 듣는다" << std::endl;
	std::cout << "2) 무시하고 떠난다" << std::endl;
}

void MysteriousEvent::Hard_Event4() const
{
	std::cout << "이상한 룬 문양" << std::endl;
	std::cout << "벽에 새겨진 기이한 룬 문양을 발견합니다." << std::endl
		<< "가까이 가서 룬을 만져보면 어떤 비밀이 풀릴 수도 있을 것 같습니다." << std::endl;
	std::cout << "1) 룬을 조사한다" << std::endl;
	std::cout << "2) 지나친다" << std::endl;

}

void MysteriousEvent::Hard_Event5() const
{
	std::cout << "시험의 방" << std::endl;
	std::cout << "당신은 문에 '용기의 시험'이라고 적힌 방 앞에 도착합니다." << std::endl
			  << "이 방은 당신을 시험하고, 보상을 줄 것입니다." << std::endl;
	std::cout << "1) 방에 들어간다" << std::endl;
	std::cout << "2) 방을 무시한다" << std::endl;

}

string MysteriousEvent::getEasyEventMessage() const
{
	switch (eventType)
	{
	case EventList::test1:
		Ez_Event1();
		break;
	case EventList::test2:
		Ez_Event2();
		break;
	case EventList::test3:
		Ez_Event3();
		break;
	case EventList::test4:
		Ez_Event4();
		break;
	case EventList::test5:
		Ez_Event5();
		break;
	default:
		break;
	}
	return string();
}

string MysteriousEvent::getHardEventMessage() const
{
	switch (eventType)
	{
	case EventList::test1:
		Hard_Event1();
		break;
	case EventList::test2:
		Hard_Event2();
		break;
	case EventList::test3:
		Hard_Event3();
		break;
	case EventList::test4:
		Hard_Event4();
		break;
	case EventList::test5:
		Hard_Event5();
		break;
	default:
		break;
	}
	return string();
}

void MysteriousEvent::StoreSetting() const
{
	/*MainItem::GetInst()->*/
}
