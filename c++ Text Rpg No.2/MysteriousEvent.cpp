#include "pch.h"
#include "MysteriousEvent.h"

void MysteriousEvent::Ez_Event1() const
{
	std::cout << "����� ����" << std::endl;
	std::cout << "����� " << std::endl
		<< "������ ���� �տ� ���ϴ�." << std::endl
		<< "�� ���Ҵ� ����� ���� ǰ�� �ִ� ���մϴ�." << std::endl
		<< "������ �ູ�� �������?" << std::endl;
	std::cout << "1) �ູ�� �޴´�" << std::endl;
	std::cout << "2) ������ �����Ѵ�" << std::endl;
}

void MysteriousEvent::Ez_Event2() const
{
	std::cout << "���ֹ��� å" << std::endl;
	std::cout << "����� ���� ���� ������ å�� �߰��մϴ�." << std::endl
		<< "ǥ������ ������ ���ڰ� ������ �ֽ��ϴ�." << std::endl
		<< "å�� ������ ���� ���� ���� ������, ������ ���赵 �ֽ��ϴ�." << std::endl;
	std::cout << "1) å�� �д´�" << std::endl;
	std::cout << "2) å�� �ΰ� ������" << std::endl;
}

void MysteriousEvent::Ez_Event3() const
{
	std::cout << "���ΰ��� �ŷ�" << std::endl;
	std::cout << "������ �ڵ��� ������ �������� ������ �����ϴ�." << std::endl
		<< "�״� �پ��� ��ǰ�� �Ǹ��ϸ�, �Ϻδ� ���� ������ ���Դϴ�." << std::endl;
	std::cout << "1) ������ ���" << std::endl;
	std::cout << "2) �ŷ��� ���� �ʴ´�" << std::endl;
	while (true)
	{
		switch (CinAuto())
		{
		case 1: // ���� �Լ� ����
		default:
			break;
		}

	}
	
}

void MysteriousEvent::Ez_Event4() const
{
	std::cout << "�̻��� ������" << std::endl;
	std::cout << "����� ������ ������ ������ �� �������� �߰��մϴ�." << std::endl
		<< "�������� ��ġ ����� ���Ѻ��� ���մϴ�." << std::endl
		<< "������ �ұ��?" << std::endl;
	std::cout << "1) �������� ��������" << std::endl;
	std::cout << "2) �����ϰ� ��������" << std::endl;
}

void MysteriousEvent::Ez_Event5() const
{
	std::cout << "������ �ɸ� ���� ����" << std::endl;
	std::cout << "����� ���� ���� �ִ� ���� ���ڸ� �߰��մϴ�." << std::endl
		<< "�׷��� �ֺ��� ������ ���� �� ���� �ұ��� ����� �������ϴ�." << std::endl;
	std::cout << "1) ���ڸ� �����" << std::endl;
	std::cout << "2) ���ڸ� �����Ѵ�" << std::endl;

}
void MysteriousEvent::Hard_Event1() const
{
	std::cout << "������ ���� ����" << std::endl;
	std::cout << "��ο� ���� ������ �� ���ڰ� ������ ���ʵ��� �Ǹ��ϰ� �ֽ��ϴ�." << std::endl
		<< "�״� �װ͵��� ������ ������ �ȴٰ� �����մϴ�." << std::endl;
	std::cout << "1) ���ʸ� �����Ѵ�" << std::endl;
	std::cout << "2) �����ϰ� ������" << std::endl;

}

void MysteriousEvent::Hard_Event2() const
{
	std::cout << "���� �Ȱ�" << std::endl;
	std::cout << "����� ���ڱ� �ֺ��� �ڿ��� �Ȱ��� �򸮴� ���� �����ϴ�." << std::endl
		<< "�Ȱ� ������ ���� �� �� ���� ����� ��ٸ��� ���� ���Դϴ�." << std::endl;
	std::cout << "1) �Ȱ� ������ ����" << std::endl;
	std::cout << "2) �Ȱ��� ���Ѵ�" << std::endl;
}

void MysteriousEvent::Hard_Event3() const
{
	std::cout << "����� ����" << std::endl;
	std::cout << "���� ���� �� �� ���簡 ���� �����ϴ�." << std::endl
		<< "�״� ������ �ʿ��� ô ����������, ���� �ӿ� ����� ����� �������ϴ�." << std::endl;
	std::cout << "1) ���� ���� ��´�" << std::endl;
	std::cout << "2) �����ϰ� ������" << std::endl;
}

void MysteriousEvent::Hard_Event4() const
{
	std::cout << "�̻��� �� ����" << std::endl;
	std::cout << "���� ������ ������ �� ������ �߰��մϴ�." << std::endl
		<< "������ ���� ���� �������� � ����� Ǯ�� ���� ���� �� �����ϴ�." << std::endl;
	std::cout << "1) ���� �����Ѵ�" << std::endl;
	std::cout << "2) ����ģ��" << std::endl;

}

void MysteriousEvent::Hard_Event5() const
{
	std::cout << "������ ��" << std::endl;
	std::cout << "����� ���� '����� ����'�̶�� ���� �� �տ� �����մϴ�." << std::endl
			  << "�� ���� ����� �����ϰ�, ������ �� ���Դϴ�." << std::endl;
	std::cout << "1) �濡 ����" << std::endl;
	std::cout << "2) ���� �����Ѵ�" << std::endl;

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
