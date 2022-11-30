#define _CRT_SECURE_NO_WARNINGS //scanf, file 관련 오류 숨김
#include <stdio.h>
#include <windows.h> //화면 초기화를 위한 헤더
#include <string.h>

struct phonebook_information {
	// 전화번호부의 기본 정보
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
			printf("출력을 선택하셨습니다.\n");
			first_menu_fileread();
			break;
		}
		case 2: {
			printf("추가를 선택하셨습니다.\n");
			second_menu_fileadd();
			break;
		}
		case 3: {
			printf("검색을 선택하셨습니다.\n");
			third_menu_filesearch();
			break;
		}
		case 4: {
			printf("종료를 선택하셨습니다.\n");
			exit(1);
		}
		case 5: {
			printf("화면을 초기화합니다.");
			Sleep(1000);
			system("cls");
			break;
		}
		default:
			printf("잘못된 번호를 입력하였습니다.\n");
			printf("프로그램을 종료합니다.\n");
			exit(1);
		}
	}
	system("pause");
	return 0;
}       

//기본메뉴를 출력하는 함수
void menu_print()
{
	printf("===============메뉴===============\n");
	printf("             1. 출력              \n");
	printf("             2. 추가              \n");
	printf("             3. 검색              \n");
	printf("             4. 종료              \n");
	printf("          5. 화면초기화           \n");
	printf("원하는 메뉴의 숫자를 입력해주세요.\n");
	printf("==================================\n");
}

// 파일 출력 함수
void first_menu_fileread() 
{
	struct phonebook_information data1;						// 파일에서 읽은 정보를 저장하는 구조체
	FILE* fp = fopen("phonebook.bin", "rb");				// 이진파일 읽기 모드로 파일 열기


	if (fp == NULL) 
	{
		printf("파일이 없습니다.\n");
		printf("내용을 추가한 후에 출력하세요.");
		system("pause");
		exit(1);
	}

	printf("1초뒤 화면을 초기화한 후에 출력됩니다.");
	Sleep(1000);											//1초 대기
	system("cls");											//화면초기화

	printf("\n");
	printf("==================================\n\n");
	fseek(fp, 0, SEEK_SET);
	while( (feof(fp)) == 0) 
	{
		fread(&data1, sizeof(data1), 1, fp);
		printf("이름 : %s\n", data1.name);
		printf("전화번호 : %s\n", data1.phone_number);
		printf("이메일 : %s\n", data1.email);
		printf("메모 : %s\n\n", data1.memo);
	}
	printf("==================================\n\n");
	fclose(fp);
}

void second_menu_fileadd() {
	FILE* fp = fopen("phonebook.bin", "ab");				// 파일을 덧붙이기(a), 이진(b)으로 읽기
	phonebook_information tdata;
	memset(&tdata, 0, sizeof(tdata));

	while (getchar() != '\n') continue; 
	// fflush로는 출력버퍼만 비우므로 getchar()로 읽은 값을 반환하도록 하여 \n을 읽으면 while문을 벗어나도록 하면서 사용가능하게 만듬.

	printf("이름 : ");			gets_s(tdata.name, sizeof(tdata.name));
	printf("전화번호 : ");		gets_s(tdata.phone_number, sizeof(tdata.phone_number));
	printf("이메일 : ");		gets_s(tdata.email, sizeof(tdata.email));
	printf("메모 : ");			gets_s(tdata.memo, sizeof(tdata.memo));

	fwrite(&tdata, sizeof(tdata), 1, fp);
	fclose(fp);
	printf("\n");
}

// 이름으로 전화번호부의 검색을 위한 함수
void third_menu_filesearch() {
	FILE* fp = fopen("phonebook.bin", "rb");
	phonebook_information temporarily_data;
	phonebook_information data1;
	char namesearch[20];

	memset(&data1, 0, sizeof(data1));
	memset(&temporarily_data, 0, sizeof(temporarily_data));

	fseek(fp, 0, SEEK_SET);
	printf("찾을 이름을 입력하세요.\n");

	while (getchar() != '\n') continue;
	// fflush로는 출력버퍼만 비우므로 getchar()로 읽은 값을 반환하도록 하여 \n을 읽으면 while문을 벗어나도록 하면서 사용가능하게 만듬.

	gets_s(namesearch, sizeof(namesearch));

	while (feof(fp) == 0) {
		fread(&temporarily_data, sizeof(temporarily_data), 1, fp);
		if ((strcmp(temporarily_data.name, namesearch)) == 0) {
			printf("이름을 찾았습니다.\n");

			printf("이름 : %s\n", temporarily_data.name);
			printf("전화번호 : %s\n", temporarily_data.phone_number);
			printf("이메일 : %s\n", temporarily_data.email);
			printf("메모 : %s\n\n", temporarily_data.memo);
			break;
		}
		else{
			printf("이름을 찾지 못했습니다.\n");
		}
	}
		fclose(fp);
		printf("\n");
}
