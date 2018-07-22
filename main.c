#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

struct smb
{
	char data;
	smb* next;
	smb* prev;
};

smb* readList(FILE* file)
{
	smb *ch, *head;
	char c;

	head = new smb;
	ch = head;

	smb* temp = NULL;
	while ((c = fgetc(file)) != '.' && c != EOF)
	{
		ch->next = new smb;
		ch->next->prev = ch;

		temp = ch;
		ch->data = c;
		ch = ch->next;
	}

	temp->next = head;
	head->prev = temp;

	return head;
}

smb* deleteChars(smb* ch)
{
	smb* tail = ch->prev;
	
		do
		{
			if (ch->prev->data == ch->next->data && ch->prev != ch->next)
			{
				smb* temp = ch->next;

				ch->prev->next = ch->next;
				ch->next->prev = ch->prev;

				delete ch;

				ch = temp;
				tail = ch->prev;
			}
			else
			{
				if (ch->prev == ch->next)
				{
					smb* temp = ch->next;

					delete ch;

					ch = temp;
					tail = ch->prev = ch->next = ch;
				}

				ch = ch->next;
			}
		} while (ch != tail);
	return ch->next;
}

void writeList(FILE* file, smb* ch)
{
	smb* head = ch;

	do
	{
		fprintf(file, "%c", ch->data);
		ch = ch->next;
	} while (ch != head);
}

void main()
{
	FILE *read, *write;
	smb* qList;

	char file_name[] = "input.txt";
	if ((read = fopen(file_name, "r")) == NULL)
	{
		printf("\nError. Can't open file %s.", file_name);
	}
	qList = readList(read);
	fclose(read);

	if (qList != qList->prev)
	{
		qList = deleteChars(qList);

		if ((write = fopen("output.txt", "w")) == NULL)
		{
			printf("\nError. Can't open file %s.", "output.txt");
		}
		writeList(write, qList);
	}
	else
	{
		if ((write = fopen("output.txt", "w")) == NULL)
		{
			printf("\nError. Can't open file %s.", "output.txt");
		}
		writeList(write, qList);
	}
	fclose(write);
}
