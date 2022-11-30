#define _CRT_SECURE_NO_WARNINGS //scanf, file ���� ���� ����
#include <stdio.h>
#include <windows.h> //ȭ�� �ʱ�ȭ�� ���� ���
#include <string.h>

struct phonebook_information {
	// ��ȭ��ȣ���� �⺻ ����
	char name[20];
	char phone_number[15];
	char email[100];
	char memo[400];
}PB_Information;

void menu_print();
void first_menu_fileread();
void second_menu_fileadd();
void third_menu_filesearch();

int main(void) {
	for (;;) {
		menu_print();
		int select_num;
		scanf_s("%d", &select_num);
		switch (select_num) {
		case 1: {
			printf("����� �����ϼ̽��ϴ�.\n");
			first_menu_fileread();
			break;
		}
		case 2: {
			printf("�߰��� �����ϼ̽��ϴ�.\n");
			second_menu_fileadd();
			break;
		}
		case 3: {
			printf("�˻��� �����ϼ̽��ϴ�.\n");
			third_menu_filesearch();
			break;
		}
		case 4: {
			printf("���Ḧ �����ϼ̽��ϴ�.\n");
			exit(1);
		}
		case 5: {
			printf("ȭ���� �ʱ�ȭ�մϴ�.");
			Sleep(1000);
			system("cls");
			break;
		}
		default:
			printf("�߸��� ��ȣ�� �Է��Ͽ����ϴ�.\n");
			printf("���α׷��� �����մϴ�.\n");
			exit(1);
		}
	}
	system("pause");
	return 0;
}       

//�⺻�޴��� ����ϴ� �Լ�
void menu_print()
{
	printf("===============�޴�===============\n");
	printf("             1. ���              \n");
	printf("             2. �߰�              \n");
	printf("             3. �˻�              \n");
	printf("             4. ����              \n");
	printf("          5. ȭ���ʱ�ȭ           \n");
	printf("���ϴ� �޴��� ���ڸ� �Է����ּ���.\n");
	printf("==================================\n");
}

// ���� ��� �Լ�
void first_menu_fileread() 
{
	struct phonebook_information data1;						// ���Ͽ��� ���� ������ �����ϴ� ����ü
	FILE* fp = fopen("phonebook.bin", "rb");				// �������� �б� ���� ���� ����


	if (fp == NULL) 
	{
		printf("������ �����ϴ�.\n");
		printf("������ �߰��� �Ŀ� ����ϼ���.");
		system("pause");
		exit(1);
	}

	printf("1�ʵ� ȭ���� �ʱ�ȭ�� �Ŀ� ��µ˴ϴ�.");
	Sleep(1000);											//1�� ���
	system("cls");											//ȭ���ʱ�ȭ

	printf("\n");
	printf("==================================\n\n");
	fseek(fp, 0, SEEK_SET);
	while( (feof(fp)) == 0) 
	{
		fread(&data1, sizeof(data1), 1, fp);
		printf("�̸� : %s\n", data1.name);
		printf("��ȭ��ȣ : %s\n", data1.phone_number);
		printf("�̸��� : %s\n", data1.email);
		printf("�޸� : %s\n\n", data1.memo);
	}
	printf("==================================\n\n");
	fclose(fp);
}

void second_menu_fileadd() {
	FILE* fp = fopen("phonebook.bin", "ab");				// ������ �����̱�(a), ����(b)���� �б�
	phonebook_information tdata;
	memset(&tdata, 0, sizeof(tdata));

	while (getchar() != '\n') continue; 
	// fflush�δ� ��¹��۸� ���Ƿ� getchar()�� ���� ���� ��ȯ�ϵ��� �Ͽ� \n�� ������ while���� ������� �ϸ鼭 ��밡���ϰ� ����.

	printf("�̸� : ");			gets_s(tdata.name, sizeof(tdata.name));
	printf("��ȭ��ȣ : ");		gets_s(tdata.phone_number, sizeof(tdata.phone_number));
	printf("�̸��� : ");		gets_s(tdata.email, sizeof(tdata.email));
	printf("�޸� : ");			gets_s(tdata.memo, sizeof(tdata.memo));

	fwrite(&tdata, sizeof(tdata), 1, fp);
	fclose(fp);
	printf("\n");
}

// �̸����� ��ȭ��ȣ���� �˻��� ���� �Լ�
void third_menu_filesearch() {
	FILE* fp = fopen("phonebook.bin", "rb");
	phonebook_information temporarily_data;
	phonebook_information data1;
	char namesearch[20];

	memset(&data1, 0, sizeof(data1));
	memset(&temporarily_data, 0, sizeof(temporarily_data));

	fseek(fp, 0, SEEK_SET);
	printf("ã�� �̸��� �Է��ϼ���.\n");

	while (getchar() != '\n') continue;
	// fflush�δ� ��¹��۸� ���Ƿ� getchar()�� ���� ���� ��ȯ�ϵ��� �Ͽ� \n�� ������ while���� ������� �ϸ鼭 ��밡���ϰ� ����.

	gets_s(namesearch, sizeof(namesearch));

	while (feof(fp) == 0) {
		fread(&temporarily_data, sizeof(temporarily_data), 1, fp);
		if ((strcmp(temporarily_data.name, namesearch)) == 0) {
			printf("�̸��� ã�ҽ��ϴ�.\n");

			printf("�̸� : %s\n", temporarily_data.name);
			printf("��ȭ��ȣ : %s\n", temporarily_data.phone_number);
			printf("�̸��� : %s\n", temporarily_data.email);
			printf("�޸� : %s\n\n", temporarily_data.memo);
			break;
		}
		else{
			printf("�̸��� ã�� ���߽��ϴ�.\n");
		}
	}
		fclose(fp);
		printf("\n");
}
