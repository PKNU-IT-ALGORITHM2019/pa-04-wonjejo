#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#pragma warning(disable:4996)

#define MAX 500
#define WEBLOG 20000

typedef struct time {
	char day[MAX];
	int month;
	char year[MAX];
	char hour[MAX];
	char min[MAX];
	char second[MAX];
}Time;

typedef struct webLog {
	char ipAddress[MAX];
	char time[MAX];
	char url[MAX];
	char status[MAX];
}WebLog;

char buf[WEBLOG];
char delim[] = ",[\0\n";

WebLog data[WEBLOG];

int printFirst[4] = { 1,0,0,0 };
int cnt_weblog = 0;
char category[4][MAX];

void control();
int read(char *input);
void print();
void print_weblog(WebLog log);
int check_mon(char *month);
void copy_data(const void *p, Time *pTime);
int comp_time(const void *p, const void *q);
int comp_ip(const void *p, const void *q);


int main(void) {

	control();

	return 0;
}

void control() {
	char buf1[MAX];
	char *command = NULL;
	char *token;

	while (1) {

		if (command != NULL) {
			free(command);
			command = NULL;
		}

		printf("$ ");
		fgets(buf1, MAX, stdin);

		if (strcmp(buf1, "\n") == 0)
			continue;

		buf1[strlen(buf1) - 1] = '\0';

		command = strdup(strtok(buf1, " "));

		if (strcmp(command, "read") == 0) {
			token = strtok(NULL, "\n");

			char *input = strdup(token);

			if (read(input) == -1) {
				free(input);

				continue;
			}
			free(input);
		}
		else if (strcmp(command, "sort") == 0) {

			char *operand = strdup(strtok(NULL, "\n"));

			for (int i = 0; i < 4; i++) {
				printFirst[i] = 0;
			}

			if (strcmp(operand, "-t") == 0) {
				printFirst[1] = 1;
				qsort(data, cnt_weblog, sizeof(WebLog), comp_time);
			}

			else if (strcmp(operand, "-ip") == 0) {
				printFirst[0] = 1;
				qsort(data, cnt_weblog, sizeof(WebLog), comp_ip);
			}

			free(operand);
		}

		else if (strcmp(command, "print") == 0) {
			print();
		}

		else if (strcmp(command, "exit") == 0)
			break;

		else {
			printf("Not defined command.\n");
			continue;
		}
	}

	free(command);

}

int read(char *input) {
	FILE *fp = fopen(input, "r");

	if (fp == NULL) {
		printf("file open is failed.\n");
		return -1;
	}

	fgets(buf, WEBLOG, fp);
	buf[strlen(buf) - 1] = '\0';

	char *token = strtok(buf, delim);

	strcpy(category[0], token);
	token = strtok(NULL, delim);
	strcpy(category[1], token);
	token = strtok(NULL, delim);
	strcpy(category[2], token);
	token = strtok(NULL, delim);
	strcpy(category[3], token);

	while (!feof(fp)) {

		fgets(buf, WEBLOG, fp);
		buf[strlen(buf) - 1] = '\0';

		token = strtok(buf, delim);
		strcpy(data[cnt_weblog].ipAddress, token);
		token = strtok(NULL, delim);
		strcpy(data[cnt_weblog].time, token);
		token = strtok(NULL, delim);
		strcpy(data[cnt_weblog].url, token);
		token = strtok(NULL, delim);
		strcpy(data[cnt_weblog].status, token);
		cnt_weblog++;
	}
	fclose(fp);

	return 1;
}

void print() {

	for (int i = 0; i < cnt_weblog; i++)
		print_weblog(data[i]);

}

void print_weblog(WebLog log) {

	for (int i = 0; i < 4; i++) {
		if (printFirst[i] == 1) {
			switch (i) {

			case 0: printf("%s\n", log.ipAddress);	break;
			case 1: printf("%s\n", log.time);	break;
			case 2: printf("%s\n", log.url);	break;
			case 3: printf("%s\n", log.status);	break;
			default: break;

			}

			break;
		}

	}
	for (int i = 0; i < 4; i++) {

		if (printFirst[i] != 1) {
			switch (i) {
			case 0: printf("\t%s: %s\n", category[i], log.ipAddress);	break;
			case 1: printf("\t%s: %s\n", category[i], log.time);	break;
			case 2: printf("\t%s: %s\n", category[i], log.url);	break;
			case 3: printf("\t%s: %s\n", category[i], log.status);	break;
			default: break;

			}
		}
	}


}

int check_mon(char *mon) {

	if (strcmp(mon, "Jan") == 0)		return 1;
	else if (strcmp(mon, "Feb") == 0)		return 2;
	else if (strcmp(mon, "Mar") == 0)		return 3;
	else if (strcmp(mon, "Apr") == 0)		return 4;
	else if (strcmp(mon, "May") == 0)		return 5;
	else if (strcmp(mon, "Jun") == 0)		return 6;
	else if (strcmp(mon, "Jul") == 0)		return 7;
	else if (strcmp(mon, "Aug") == 0)		return 8;
	else if (strcmp(mon, "Sep") == 0)		return 9;
	else if (strcmp(mon, "Oct") == 0)		return 10;
	else if (strcmp(mon, "Nov") == 0)		return 11;
	else if (strcmp(mon, "Dec") == 0)		return 12;

	return -1;
}

void copy_data(const void *p, Time *pTime) {

	char *time_data = strdup(((WebLog *)p)->time);
	char *token = strtok(time_data, "/");

	strcpy(pTime->day, token);
	token = strtok(NULL, "/");
	pTime->month = check_mon(token);
	token = strtok(NULL, ":");
	strcpy(pTime->year, token);
	token = strtok(NULL, ":");
	strcpy(pTime->hour, token);
	token = strtok(NULL, ":");
	strcpy(pTime->min, token);
	token = strtok(NULL, "\0");
	strcpy(pTime->second, token);

	free(time_data);
}

int comp_time(const void *p, const void *q) {

	Time pTime = { "",0,"","","","" };
	Time qTime = { "",0,"","","","" };

	copy_data(p, &pTime);
	copy_data(q, &qTime);

	if (strcmp(pTime.year, qTime.year) != 0)
		return strcmp(pTime.year, qTime.year);
	if (pTime.month != qTime.month)
		return pTime.month - qTime.month;
	if (strcmp(pTime.day, qTime.day) != 0)
		return strcmp(pTime.day, qTime.day);
	if (strcmp(pTime.hour, qTime.hour) != 0)
		return strcmp(pTime.hour, qTime.hour);
	if (strcmp(pTime.min, qTime.min) != 0)
		return strcmp(pTime.min, qTime.min);
	if (strcmp(pTime.second, qTime.second) != 0)
		return strcmp(pTime.second, qTime.second);

	return 0;
}

int comp_ip(const void *p, const void *q) {

	if (strcmp(((WebLog *)p)->ipAddress, ((WebLog *)q)->ipAddress) != 0)
		return (strcmp(((WebLog *)p)->ipAddress, ((WebLog *)q)->ipAddress));

	return comp_time(p, q);
}