#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

class Student;
class Subject;
class Score;
class Menu_manager;

class Student {
public:
	string name;	// 학생 이름
	int id;			// 학번
	double grade;	// 학점 계산용 변수1
	double grade2;	// 학점 계산용 변수2
	vector<string> subject_list;	// 학생이 수강중인 과목 리스트
	static void add_stud(vector<Student>& list);	// 학생을 추가하는 함수
	static void enroll_class(vector<Subject>& sub_list, vector<Student>& stud_list);	// 특정 학생의 수강 과목을 등록하는 함수
	static void calc_rank(vector<Subject>& sub_list, vector<Student>& stud_list, int only_major);	// 학생의 등수를 계산하는 함수
	static void stud_info(vector<Subject>& sub_list, vector<Student>& stud_list);	// 특정 학생의 수강 과목, 평점 정보를 출력하는 함수
};
class Subject {
public:
	string name;	// 과목 이름
	bool major;		// 전공 여부
	int semester;	// 해당 학기
	vector<Score> score_list;	// 해당 과목 수강생의 성적 리스트
	static void add_sub(vector<Subject>& list);	// 과목을 추가하는 함수
	static void top_n_subjects(vector<Subject>& sub_list, vector<Student>& stud_list);	// 과목 성적 상위 n명의 성명을 출력하는 함수
	static void print_overall_rank(vector<Subject>& sub_list, vector<Student>& stud_list, int only_major, int semester);	// 성적을 출력하는 함수
};
class Score {
public:
	int id;			// 해당 성적을 받은 학생의 학번
	double score;	// 평점
	double grade;	// 학점
	double get_grade() {
		if (score >= 95)		// A+
			return 4.5;
		else if (score >= 90)	// A
			return 4.0;
		else if (score >= 85)	// B+
			return 3.5;
		else if (score >= 80)	// B
			return 3.0;
		else if (score >= 75)	// C+
			return 2.5;
		else if (score >= 70)	// C
			return 2.0;
		else if (score >= 65)	// D+
			return 1.5;
		else if (score >= 60)	// D
			return 1.0;
		else
			return 0.0;			// F
	}
};

bool cmp_grade_vector(const Student& s1, const Student& s2) { // 학점 순으로 정렬 하기 위한 비교함수1
	return s1.grade > s2.grade;
}
bool cmp_grade2_vector(const Student& s1, const Student& s2) {	// 학점 순으로 정렬 하기 위한 비교함수2
	return s1.grade2 > s2.grade2;
}
bool cmp_score_vector(const Score& s1, const Score& s2) {	// 학점 순으로 정렬 하기 위한 비교함수3
	return s1.score > s2.score;
}
void calcul_now_grade(vector<Subject>& sub_list, vector<Student>& stud_list, int only_major, int semester) { // only_major : 전공 출력 명령, semester : 학기별 출력 명령
	int cnt, major_cnt, s1_cnt, s2_cnt; // cnt : 전체 학점 계산(나눗셈)을 위한 카운트, major_cnt : 전공 학점 계산(나눗셈)을 위한 카운트, s1_cnt : 1학기 학점 계산(나눗셈)을 위한 카운트, s2_cnt : 2학기 학점 계산(나눗셈)을 위한 카운트
	double get_grade, calcul_grade, major_grade, semester1_grade, semester2_grade; // get_grade : get_grade() 함수의 반환값을 저장, calcul_grade : 전체 학점, major_grade : 전공 학점, semester1_grade : 1학기 학점, semester2_grade : 2학기 학점
	for (auto it_stud = stud_list.begin(); it_stud != stud_list.end(); it_stud++) { // Student 벡터 속 클래스 객체들을 순회하는 iterator 반복문
		cnt = 0;			// 모든 변수 초기화
		major_cnt = 0;
		s1_cnt = 0;
		s2_cnt = 0;
		calcul_grade = 0;
		get_grade = 0;
		major_grade = 0;
		semester1_grade = 0;
		semester2_grade = 0;
		for (auto it_sublist = it_stud->subject_list.begin(); it_sublist != it_stud->subject_list.end(); it_sublist++) { // Student 클래스 객체들 속 subject_list 속 과목명들을 순회하는 iterator 반복문
			for (auto it_sub = sub_list.begin(); it_sub != sub_list.end(); it_sub++) { // Subject 벡터 속 클래스 객체들을 순회하는 iterator 반복문
				if (*it_sublist == it_sub->name) { // subject_list 속 과목명이 Subject 클래스 객체의 과목명과 같다면:
					for (auto it_score = it_sub->score_list.begin(); it_score != it_sub->score_list.end(); it_score++) { // Subject 클래스 속 score_list 벡터 속 성적들을 순회하는 iterator 반복문
						if (it_stud->id == it_score->id) { // Student 클래스 객체의 학번과 score_list 속 성적을 갖는 학번이 같다면:
							if (only_major == 1 && it_sub->major == true) {		// 전공 출력을 명령받고, Subject 클래스 객체가 전공 과목이라면:
								get_grade = it_score->get_grade(); 				// 성적 받아오기
								major_grade += get_grade; 						// 합산
								major_cnt++; 									// 카운트 후위 증가
							}
							else if (semester == 1) {							// 학기별 출력을 명령받았다면:
								if (it_sub->semester == 1) {					// 1학기라면:
									get_grade = it_score->get_grade(); 			// 성적 받아오기
									semester1_grade += get_grade; 				// 합산
									s1_cnt++; 									// 카운트 후위 증가
								}
								else if (it_sub->semester == 2) {				// 2학기라면:
									get_grade = it_score->get_grade(); 			// 성적 받아오기
									semester2_grade += get_grade; 				// 합산
									s2_cnt++;									// 카운트 후위 증가
								}
							}
							else {												// 전체 학점일 때:
								get_grade = it_score->get_grade(); 				// 성적 받아오기
								calcul_grade += get_grade; 						// 합산
								cnt++;											// 카운트 후위 증가
							}
						}
					}
				}
			}
		}
		if (only_major == 1) {													// 전공일 때:
			if (major_cnt == 0)													// 산출할 점수가 없다면:
				it_stud->grade2 = 0;											// 학점에 0할당
			else {
				major_grade = round((major_grade / major_cnt) * 100) / 100;		// 소수점 둘째자리 반올림으로 학점 계산(카운트 사용)
				it_stud->grade2 = major_grade;									// 학점 할당
			}
		}
		else if (semester == 1) {												// 학기일 때:
			if (s1_cnt == 0)													// 산출할 점수가 없다면:
				it_stud->grade = 0;												// 학점에 0할당
			else {
				semester1_grade = round((semester1_grade / s1_cnt) * 100) / 100;// 소수점 둘째자리 반올림으로 학점 계산(카운트 사용)
				it_stud->grade = semester1_grade;								// 학점 할당
			}
			if (s2_cnt == 0)													// 산출할 점수가 없다면:
				it_stud->grade2 = 0;											// 학점에 0할당
			else {
				semester2_grade = round((semester2_grade / s2_cnt) * 100) / 100;// 소수점 둘째자리 반올림으로 학점 계산(카운트 사용)
				it_stud->grade2 = semester2_grade;								// 학점 할당
			}
		}
		else {																	// 전체 학점일 때:
			if (cnt == 0)														// 산출할 점수가 없다면:
				it_stud->grade = 0;												// 학점에 0할당
			else {
				calcul_grade = round((calcul_grade / cnt) * 100) / 100;			// 소수점 둘째자리 반올림으로 학점 계산(카운트 사용)
				it_stud->grade = calcul_grade;									// 학점 할당
			}
		}
	}
}
void Student::add_stud(vector<Student>& list) {
	int num, id, isExist; // num : 추가할 학생 수, id : 학번, isExist : 중복 학번 추가 방지용
	string name; // name : 학생 이름
	Student tmp; // 추가를 위한 학생 클래스 객체 생성

	cout << endl << "추가할 학생 수 >>";	// 몇 명의 학생을 입력받을지 결정
	cin >> num;

	for (int i = 0; i < num; i++) {		// 입력한 학생 수 만큼 반복
		isExist = 0;
		cout << endl << i + 1 << "번" << endl << endl;

		cout << "학생 이름 입력 >>";	// 새로운 학생 정보 입력
		cin >> name;
		cout << "학번 입력 >>";
		cin >> id;

		for (int n = 0; n < list.size(); n++)	// 입력받은 학번이 존재하는지 중복 체크
			if (list[n].id == id) isExist = 1;
		if (isExist == 1) {						// 입력받은 학번이 존재한다면 추가하지 않고 넘어감
			cout << endl << "이미 존재하는 학번입니다." << endl << endl;
			continue;
		}
		tmp.name = name;	// 학생 클래스 객체에 이름과 학번 저장
		tmp.id = id;

		list.push_back(tmp);	// 새로운 객체를 전체 학생 리스트에 추가
	}
	cout << endl << endl;
}
void Student::enroll_class(vector<Subject>& sub_list, vector<Student>& stud_list) {
	int stud_num, sub_num, stud_index = 0, sub_index = 0;	// stud_num : 학생 번호, sub_num : 과목 번호
	Score tmp;	// 추가를 위한 점수 클래스 객체 생성

	try {
		if (stud_list.empty())		// 등록된 학생이 없으면 오류
			throw "등록된 학생이 없습니다";
		if (sub_list.empty())		// 개설된 과목이 없으면 오류
			throw "등록된 과목이 없습니다";

		cout << endl << "===학생 목록===" << endl;		// 학생 나열
		for (auto it_stud = stud_list.begin(); it_stud != stud_list.end(); it_stud++)
			cout << ++stud_index << "\t" << it_stud->name << " : " << it_stud->id << endl;

		while (true) {		// 수강 등록을 진행할 학생 번호 입력
			cout << endl << "수강 등록 학생 번호 입력 >>";
			cin >> stud_num;

			if ((stud_num < 1) || (stud_num > stud_list.size()))	// 학생 원소에 해당하는 값이 아닐때 반복
				cout << endl << "올바른 번호를 입력하세요" << endl;
			else
				break;
		}

		while (true) {		//과목을 등록하는 반복문
			sub_index = 0;
			cout << endl << "===개설된 과목 목록===" << endl;	// 개설 과목 나열
			cout << sub_index++ << "\t" << "입력 종료" << endl;
			for (auto it_sub = sub_list.begin(); it_sub != sub_list.end(); it_sub++)
				cout << sub_index++ << "\t" << it_sub->name << endl;

			cout << endl << stud_list[stud_num - 1].name << "의 신청 과목 번호 입력" << endl;	// 신청할 과목 번호 입력
			cout << ">>";
			cin >> sub_num;

			if ((sub_num < 0) || (sub_num > sub_list.size())) {		// 과목 번호에 해당하는 값이 아닐때 반복
				cout << endl << "올바른 번호를 입력하세요" << endl;
				continue;
			}
			else if (sub_num == 0)		// 0을 입력하면 과목 등록 종료
				break;

			//신청하려는 과목이 이미 등록되어있는지 isExist변수로 체크
			int isExist = 0;
			for (auto it_enrolled = stud_list[stud_num - 1].subject_list.begin(); it_enrolled != stud_list[stud_num - 1].subject_list.end(); it_enrolled++)
				if (*it_enrolled == sub_list[sub_num - 1].name)
					isExist = 1;

			if (isExist)
				cout << endl << "이미 등록된 과목입니다" << endl;	// 이미 등록한 과목이면 등록을 건너뜀
			else {
				stud_list[stud_num - 1].subject_list.push_back(sub_list[sub_num - 1].name);	// 학생 클래스 내부의 수강중인 과목 리스트에 저장

				double score;
				while (true) {		// 과목 평점 점수 입력
					cout << endl << "해당 과목의 점수를 입력하세요(1~100)" << endl;
					cout << ">>";
					cin >> score;

					if ((score < 0) || (score > 100))		// 범위 밖의 점수를 입력받으면 반복
						cout << endl << "올바른 점수를 입력하세요" << endl;
					else {
						tmp.id = stud_list[stud_num - 1].id;	// score 객체에 등록 학생의 학번, 점수, 학점 저장
						tmp.score = score;
						tmp.grade = tmp.get_grade();
						sub_list[sub_num - 1].score_list.push_back(tmp);	// 과목 클래스 내부의 score list에 학번과 점수, 학점 추가
						break;
					}
				}
			}
		}
	}
	catch (const char* s) {		// 등록된 학생 또는 개설된 과목이 없을 때 오류메세지 출력
		cout << endl << endl << s << endl << endl;
	}
	cout << endl;
}
void Student::calc_rank(vector<Subject>& sub_list, vector<Student>& stud_list, int only_major) {
	int num, stud_index = 0;	// num : 등수를 계산할 학생 번호

	try {
		if (stud_list.empty())		// 등록된 학생이 없으면 오류
			throw "등록된 학생이 없습니다";

		cout << endl << "===학생 목록===" << endl;		// 학생 나열
		for (auto it_stud = stud_list.begin(); it_stud != stud_list.end(); it_stud++)
			cout << ++stud_index << "\t" << it_stud->name << " : " << it_stud->id << endl;
	}
	catch (const char* s) {		// 등록된 학생이 없을 때 오류메세지 출력
		cout << endl << endl << s << endl << endl;
	}
	cout << endl;

	while (true) {		// 등수 확인할 학생 번호 입력
		cout << endl << "학생 번호 입력 >> ";
		cin >> num;

		if ((num < 1) || (num > stud_list.size()))		// 입력값이 학생 수 범위 밖이면 반복
			cout << endl << "올바른 번호를 입력하세요" << endl;
		else
			break;
	}
	//입력받은 학생 id 저장
	int check_id = stud_list[num - 1].id;

	//전체 학생 평점평균 계산
	int count = 0;	// 과목 개수 저장 변수
	for (auto it_stud = stud_list.begin(); it_stud != stud_list.end(); it_stud++) {	// 전체 학생에 대해 반복
		count = 0;	// 과목 개수 초기화
		it_stud->grade = 0;	// 학점 초기화
		for (auto it_sub = it_stud->subject_list.begin(); it_sub != it_stud->subject_list.end(); it_sub++) {	// 학생 개인이 수강하는 과목 리스트 조회
			auto subject = sub_list.begin();
			while ((*it_sub) != subject->name) { subject++; }	// 과목 리스트에 포함된 과목 정보 subject iterator에 불러오기

			if ((only_major == 1) && (subject->major == false))	// 전공만 확인하려는데 교양과목이 있을시에 교양과목의 점수는 합산하지 않고 건너뜀
				continue;

			auto it_score = subject->score_list.begin();	// 현재 학생의 점수 불러오기
			while (it_stud->id != it_score->id) { it_score++; } 

			it_stud->grade += it_score->grade;
			count++;
		}
		it_stud->grade /= count;	// 학생의 grade 변수에 평점평균 저장
	}

	sort(stud_list.begin(), stud_list.end(), cmp_grade_vector);	// 평점 평균 순으로 학생 리스트 정렬

	int rank = 1;
	auto it_stud = stud_list.begin();	
	while (check_id != it_stud->id) {	// 조회하려는 학생이 몇번째 등수인지 계산
		it_stud++;
		rank++;
	}

	cout << endl << "학생의 등수는 " << rank << "등 입니다" << endl << endl;	// 특정 학생 등수 출력
}
void Student::stud_info(vector<Subject>& sub_list, vector<Student>& stud_list) {
	int num, stud_index = 0;

	try {
		if (stud_list.empty())		// 등록된 학생이 없으면 예외 처리
			throw "등록된 학생이 없습니다";

		cout << endl << "===학생 목록===" << endl;		// 학생 나열
		for (auto it_stud = stud_list.begin(); it_stud != stud_list.end(); it_stud++)
			cout << ++stud_index << "\t" << it_stud->name << " : " << it_stud->id << endl;
	}
	catch (const char* s) {
		cout << endl << endl << s << endl << endl;	// 예외 발생시 오류메세지 출력
	}
	cout << endl;

	while (true) {		// 등수 확인할 학생 번호 입력
		cout << endl << "학생 번호 입력 >> ";
		cin >> num;

		if ((num < 1) || (num > stud_list.size()))		// 학생 수 범위 이외의 값 입력시 오류메세지 출력후 입력 반복
			cout << endl << "올바른 번호를 입력하세요" << endl;
		else
			break;
	}

	//수강중인 과목 리스트 출력
	int index = 0;
	for (auto it_sub = stud_list[num - 1].subject_list.begin(); it_sub != stud_list[num - 1].subject_list.end(); it_sub++)
		cout << ++index << " : " << *it_sub << endl;
	cout << endl;

	//1학기, 2학기, 총 평점 계산
	calcul_now_grade(sub_list, stud_list, 0, 1);	// 전공 여부 구분 X, 학기 여부 구분 O인 학점 계산 실행
	cout << "1학기 평점 : " << stud_list[num - 1].grade << endl;
	cout << "2학기 평점 : " << stud_list[num - 1].grade2 << endl;
	calcul_now_grade(sub_list, stud_list, 0, 0);	// 전공, 학기 여부 구분 X인 학점 계산 실행
	cout << "총 평점 : " << stud_list[num - 1].grade << endl;

}
void Subject::print_overall_rank(vector<Subject>& sub_list, vector<Student>& stud_list, int only_major, int semester) {
	int sort_stud_index = 0, rank_cnt = 1; // sort_stud_index : 순위,  rank_cnt : 동점을 고려하여 순위 보정을 하기 위한 카운트
	if (only_major == 1) { 																											// 전공 석차 출력을 명령 받았다면:
		calcul_now_grade(sub_list, stud_list, only_major, semester);																// 전공 학점 계산
		sort(stud_list.begin(), stud_list.end(), cmp_grade2_vector);																// 계산한 전공 학점에 따라 내림차순으로 Student 클래스 객체 정렬
		cout << endl << "===동국대학교 전체 학생 전공 석차 출력===" << endl;
		for (auto it_stud = stud_list.begin(); it_stud != stud_list.end(); it_stud++) {												// Student 벡터 속 클래스 객체들을 순회하는 iterator 반복문
			if (it_stud == stud_list.begin())																						// 첫 순회라면:
				cout << ++sort_stud_index << "\t" << "이름: " << it_stud->name << "\t" << "전공평점: " << it_stud->grade2 << endl;	// 1등 출력
			else if (it_stud->grade2 == (--it_stud)->grade2) {																		// iterator가 가르키는 학점이 직전에 가르켰던 학점과 같다면:
				cout << sort_stud_index << "\t" << "이름: " << (++it_stud)->name << "\t" << "전공평점: " << it_stud->grade2 << endl;	// 동순위로 출력
				rank_cnt++;																											// 카운트 후위 증가
			}
			else {																													// 첫 순회도 아니고 동순위도 아니라면:
				sort_stud_index += rank_cnt;																						// 순위에 카운트 더하기 (공동 1등 후 3등 -> {1, 1, 3} -> 카운트는 2 -> 1 + 2 = 3)
				cout << sort_stud_index << "\t" << "이름: " << (++it_stud)->name << "\t" << "전공평점: " << it_stud->grade2 << endl;	// 순위 출력
				rank_cnt = 1;																										// 카운트를 1로 초기화
			}
		}
		cout << endl;
	}
	else if (semester == 1) {																										// 학기별 석차 출력을 명령 받았다면:
		calcul_now_grade(sub_list, stud_list, only_major, semester);																// 학기별 학점 계산
		sort(stud_list.begin(), stud_list.end(), cmp_grade_vector);																	// 우선 계산한 1학기 학점에 따라 내림차순으로 Student 클래스 객체 정렬
		cout << endl << "===동국대학교 전체 학생 학기별 석차 출력===" << endl;
		cout << "==1학기==" << endl;
		for (auto it_stud = stud_list.begin(); it_stud != stud_list.end(); it_stud++) {												// Student 벡터 속 클래스 객체들을 순회하는 iterator 반복문
			if (it_stud == stud_list.begin())																						// 첫 순회라면:
				cout << ++sort_stud_index << "\t" << "이름: " << it_stud->name << "\t" << "학점평점: " << it_stud->grade << endl;		// 1등 출력
			else if (it_stud->grade == (--it_stud)->grade) {																		// iterator가 가르키는 학점이 직전에 가르켰던 학점과 같다면:
				cout << sort_stud_index << "\t" << "이름: " << (++it_stud)->name << "\t" << "학점평점: " << it_stud->grade << endl;	// 동순위로 출력
				rank_cnt++;																											// 카운트 후위 증가
			}
			else {																													// 첫 순회도 아니고 동순위도 아니라면:
				sort_stud_index += rank_cnt;																						// 순위에 카운트 더하기
				cout << sort_stud_index << "\t" << "이름: " << (++it_stud)->name << "\t" << "학점평점: " << it_stud->grade << endl;	// 순위 출력
				rank_cnt = 1;																										// 카운트를 1로 초기화
			}
		}	
		sort_stud_index = 0;																										// 순위를 0으로 초기화
		rank_cnt = 1;																												// 카운트를 1로 초기화
		sort(stud_list.begin(), stud_list.end(), cmp_grade2_vector);																// 계산한 2학기 학점에 따라 내림차순으로 Student 클래스 객체 재정렬
		cout << "==2학기==" << endl;
		for (auto it_stud = stud_list.begin(); it_stud != stud_list.end(); it_stud++) {												// 이하 동일
			if (it_stud == stud_list.begin())
				cout << ++sort_stud_index << "\t" << "이름: " << it_stud->name << "\t" << "학점평점: " << it_stud->grade2 << endl;
			else if (it_stud->grade2 == (--it_stud)->grade2) {
				cout << sort_stud_index << "\t" << "이름: " << (++it_stud)->name << "\t" << "학점평점: " << it_stud->grade2 << endl;
				rank_cnt++;
			}
			else {
				sort_stud_index += rank_cnt;
				cout << sort_stud_index << "\t" << "이름: " << (++it_stud)->name << "\t" << "학점평점: " << it_stud->grade2 << endl;
				rank_cnt = 1;
			}
		}
		cout << endl;
	}
	else {																															// 전체 학생 석차 출력을 명령 받았다면:
		calcul_now_grade(sub_list, stud_list, only_major, semester);
		sort(stud_list.begin(), stud_list.end(), cmp_grade_vector);
		cout << endl << "===동국대학교 전체 학생 석차 출력===" << endl;
		for (auto it_stud = stud_list.begin(); it_stud != stud_list.end(); it_stud++) {
			if (it_stud == stud_list.begin())
				cout << ++sort_stud_index << "\t" << "이름: " << it_stud->name << "\t" << "학점평점: " << it_stud->grade << endl;
			else if (it_stud->grade == (--it_stud)->grade) {																		// 전위 감소 연산을 했으므로
				cout << sort_stud_index << "\t" << "이름: " << (++it_stud)->name << "\t" << "학점평점: " << it_stud->grade << endl;	// 전위 증가 연산 후 정보 출력
				rank_cnt++;
			}
			else {
				sort_stud_index += rank_cnt;
				cout << sort_stud_index << "\t" << "이름: " << (++it_stud)->name << "\t" << "학점평점: " << it_stud->grade << endl;	// else if 문에서 감소 연산을 했기 때문에 전위 증가 연산을 해주어야 for문이 정상적으로 작동함
				rank_cnt = 1;
			}
		}
		cout << endl;
	}
}
void Subject::add_sub(vector<Subject>& list) {
	int num, semester, isExist;	// num : 개설 과목 수, semester : 학기, isExist : 중복 과목 개설 방지용
	char major; // major : 전공 여부
	string name; // name : 과목 이름
	Subject tmp; // 추가를 위한 과목 클래스 객체 생성

	cout << endl << "개설할 과목 수 >> ";		// 추가할 과목 개수 입력
	cin >> num;

	for (int i = 0; i < num; i++) {		// 입력받은 횟수만큼 과목 등록
		isExist = 0;
		cout << endl << i + 1 << "번" << endl << endl;

		cout << "과목 명 입력 >>";	// 과목 이름 입력
		cin >> name;
		for (int n = 0; n < list.size(); n++)	//입력받은 이름이 존재하는지 중복 체크
			if (list[n].name == name) isExist = 1;
		if (isExist == 1) {
			cout << endl << "이미 존재하는 과목입니다." << endl << endl;	// 입력받은 과목이 중복이라면 새로 등록하지 않고 건너뜀
			continue;
		}
		tmp.name = name;

		while (true) {	//전공 여부 기입
			cout << "전공 여부 입력(T/F) >>";
			cin >> major;

			if ((major == 'T') || (major == 't')) {		// T, t 입력시 전공
				tmp.major = true;
				break;
			}
			else if ((major == 'F') || (major == 'f')) {	// F, f 입력시 교양
				tmp.major = false;
				break;
			}
			else
				cout << "올바른 값을 입력하세요" << endl;		// T/F 이외의 입력값 입력시 오류메세지 출력
		}

		while (true) {	//학기 정보 기입
			cout << "개설 학기 입력(1/2) >>";
			cin >> semester;

			if ((semester == 1) || (semester == 2)) {	// 개설 과목이 1학기인지 2학기인지 구분
				tmp.semester = semester;
				break;
			}
			else
				cout << "올바른 값을 입력하세요" << endl;	// 1, 2 학기 이외의 값 입력시 오류메세지 출력
		}

		list.push_back(tmp);	// 과목 리스트에 새로운 과목 정보 추가
	}
	cout << endl << endl;
}
void Subject::top_n_subjects(vector<Subject>& sub_list, vector<Student>& stud_list) {
	int num, sub_num, sub_index = 0, sort_vec_index = 0; // num : 출력할 상위 n명

	while (true) {
		sub_index = 0;
		cout << endl << "===개설된 과목 목록===" << endl;	// 개설 과목 나열
		for (auto it_sub = sub_list.begin(); it_sub != sub_list.end(); it_sub++) // Subject 벡터 속 클래스 객체들을 순회하는 iterator 반복문
			cout << ++sub_index << "\t" << it_sub->name << endl; // 과목명 출력

		cout << endl << "출력할 과목 번호 >>";
		cin >> sub_num; // 과목 번호 입력받기

		if ((sub_num < 0) || (sub_num > sub_list.size())) // 입력 받은 번호가 0보다 작거나 저장된 과목수보다 많으면:
			cout << endl << "올바른 번호를 입력하세요" << endl; // 예외 문구 출력
		else
			break;
	}
	while (true) {
		cout << endl << "출력할 과목별 상위 학생 수 >>";
		cin >> num; // 학생 수 입력

		if ((num < 0) || (num > sub_list[sub_num - 1].score_list.size())) // 입력 받은 학생 수가 0보다 작거나 선택한 과목의 수강생보다 많으면:
			cout << endl << "입력값이 수강생 수 보다 많습니다" << endl; // 예외 문구 출력
		else
			break;
	}

	cout << endl << "===" << sub_list[sub_num - 1].name << "의 상위 " << num << "명 출력===" << endl; // 과목명, 학생 수를 통해 안내 문구 출력

	sort(sub_list[sub_num - 1].score_list.begin(), sub_list[sub_num - 1].score_list.end(), cmp_score_vector); // 평점을 내림차순으로 정렬

	for (auto it_score = sub_list[sub_num - 1].score_list.begin(); it_score != sub_list[sub_num - 1].score_list.end(); it_score++) { //  Subject 벡터 속 선택된 클래스 객체 속 score_list 벡터 속 객체들을 순회하는 iterator 반복문
		for (auto it_stud = stud_list.begin(); it_stud != stud_list.end(); it_stud++) { // Student 벡터 속 클래스 객체들을 순회하는 iterator 반복문
			if (it_stud->id == it_score->id) { // Student 클래스 객체의 학번과 Score 클래스 객체의 학번이 같다면:
				cout << ++sort_vec_index << "\t" << it_stud->name << endl; // index와 이름 출력
				break;
			}
		}
		if (sort_vec_index == num) // 입력 받은 출력할 상위 n명에 도달했을 때: 출력 중지
			break;
	}
	cout << endl;
}

class Menu_manager {
	string cmd;		// 입력 변수
	void subject_menu(vector<Subject>& sub_list, vector<Student>& stud_list);	// 과목 메뉴 함수
	void student_menu(vector<Subject>& sub_list, vector<Student>& stud_list);	// 학생 메뉴 함수
	void grade_menu(vector<Subject>& sub_list, vector<Student>& stud_list);		// 성적 메뉴 함수
public:
	void main_menu(vector<Subject>& sub_list, vector<Student>& stud_list);		// 메인 메뉴 함수
};

void Menu_manager::main_menu(vector<Subject>& sub_list, vector<Student>& stud_list) {
	while (true) {
		cout << "********************" << endl;
		cout << "1. 과목 관리" << endl;
		cout << "2. 학생 관리" << endl;
		cout << "3. 성적 조회" << endl;
		cout << "4. 프로그램 종료" << endl;
		cout << "********************" << endl;
		cout << ">> ";
		cin >> cmd;

		try {
			if ((cmd != "1") && (cmd != "2") && (cmd != "3") && (cmd != "4"))	// 프로그램 번호 이외의 값 입력시 예외 처리
				throw cmd;

			if (cmd == "1")
				subject_menu(sub_list, stud_list);	// 과목 관리 메뉴 실행
			else if (cmd == "2")
				student_menu(sub_list, stud_list);	// 학생 관리 메뉴 실행
			else if (cmd == "3")
				grade_menu(sub_list, stud_list);	// 성적 관리 메뉴실행
			else if (cmd == "4") {
				cout << "프로그램을 종료합니다." << endl;	// 프로그램 종료
				break;
			}

		}
		catch (string cmd) {
			cout << "1~4 사이의 메뉴 번호를 입력하세요" << endl << endl;		// 예외 발생시 오류메세지 출력
		}
	}
}
void Menu_manager::subject_menu(vector<Subject>& sub_list, vector<Student>& stud_list) {
	cout << endl;
	while (true) {
		cout << "********************" << endl;
		cout << "1. 과목 개설" << endl;
		cout << "2. 개설 과목별 상위 n명 학생 조회" << endl;
		cout << "3. 상위 메뉴로 돌아가기" << endl;
		cout << "********************" << endl;
		cout << ">> ";
		cin >> cmd;

		try {
			if ((cmd != "1") && (cmd != "2") && (cmd != "3"))	// 프로그램 번호 이외의 값 입력시 예외 처리
				throw cmd;

			if (cmd == "1")
				Subject::add_sub(sub_list);		// 과목 개설 함수 실행
			else if (cmd == "2")
				Subject::top_n_subjects(sub_list, stud_list);	// 특정 과목 상위 n명 학생 조회 함수 실행
			else if (cmd == "3") {
				cout << "상위 메뉴로 돌아갑니다." << endl << endl;	// 상위 메뉴로 이동
				break;
			}
		}
		catch (string cmd) {
			cout << "1~3 사이의 메뉴 번호를 입력하세요" << endl << endl;	// 예외 발생시 오류메세지 출력
		}
	}
}
void Menu_manager::student_menu(vector<Subject>& sub_list, vector<Student>& stud_list) {
	cout << endl;
	while (true) {
		cout << "********************" << endl;
		cout << "1. 학생 추가" << endl;
		cout << "2. 수강 과목 등록" << endl;
		cout << "3. 전체 과목 개인 등수 출력" << endl;
		cout << "4. 전공 과목 개인 등수 출력" << endl;
		cout << "5. 학생 수강 현황 조회" << endl;
		cout << "6. 상위 메뉴로 돌아가기" << endl;
		cout << "********************" << endl;
		cout << ">> ";
		cin >> cmd;

		try {
			if ((cmd != "1") && (cmd != "2") && (cmd != "3") && (cmd != "4") && (cmd != "5") && (cmd != "6"))	// 프로그램 번호 이외의 값 입력시 예외 처리
				throw cmd;

			if (cmd == "1")
				Student::add_stud(stud_list);	// 학생 추가 함수 실행
			else if (cmd == "2")
				Student::enroll_class(sub_list, stud_list);	// 특정 학생 수강 과목 등록 함수 실행
			else if (cmd == "3")
				Student::calc_rank(sub_list, stud_list, 0);	// 전체 과목 개인 등수 출력 함수 실행
			else if (cmd == "4")
				Student::calc_rank(sub_list, stud_list, 1);	// 전공 과목 개인 등수 출력 함수 실행
			else if (cmd == "5")
				Student::stud_info(sub_list, stud_list);	// 학생 정보 확인 함수 실행
			else if (cmd == "6") {
				cout << "상위 메뉴로 돌아갑니다." << endl << endl;	// 상위 메뉴로 이동
				break;
			}
		}
		catch (string cmd) {
			cout << "1~6 사이의 메뉴 번호를 입력하세요" << endl << endl;	// 예외 발생시 오류메세지 출력
		}
	}
}
void Menu_manager::grade_menu(vector<Subject>& sub_list, vector<Student>& stud_list) {
	cout << endl;
	while (true) {
		cout << "********************" << endl;
		cout << "1. 전체 학생 석차 조회" << endl;
		cout << "2. 전체 학생 석차 조회(전공)" << endl;
		cout << "3. 전체 학생 학기별 석차 조회" << endl;
		cout << "4. 상위 메뉴로 돌아가기" << endl;
		cout << "********************" << endl;
		cout << ">> ";
		cin >> cmd;

		try {
			if ((cmd != "1") && (cmd != "2") && (cmd != "3") && (cmd != "4"))	// 프로그램 번호 이외의 값 입력시 예외 처리
				throw cmd;

			if (cmd == "1")
				Subject::print_overall_rank(sub_list, stud_list, 0, 0); // 전체 학생 석차 조회 함수 실행, 전공만 출력 = False, 학기별 출력 = False
			else if (cmd == "2")
				Subject::print_overall_rank(sub_list, stud_list, 1, 0); // 전체 학생 전공 석차 조회 함수 실행, 전공만 출력 = True, 학기별 출력 = False
			else if (cmd == "3")
				Subject::print_overall_rank(sub_list, stud_list, 0, 1); // 전체 학생 학기별 석차 조회 함수 실행, 전공만 출력 = False, 학기별 출력 = True
			else if (cmd == "4") {
				cout << "상위 메뉴로 돌아갑니다." << endl << endl;	// 상위 메뉴로 이동
				break;
			}
		}
		catch (string cmd) {
			cout << "1~5 사이의 메뉴 번호를 입력하세요" << endl << endl;	// 예외 발생시 오류메세지 출력
		}
	}
}

int main() {
	vector<Subject> subject_list;	// 전체 과목 정보를 저장하는 리스트
	vector<Student> student_list;	// 전체 학생 정보를 저장하는 리스트

	Menu_manager m;
	m.main_menu(subject_list, student_list);
}