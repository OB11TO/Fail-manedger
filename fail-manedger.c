/*BETA */


#include <unistd.h>
#include <termios.h>
#include <string.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <pwd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <dirent.h>
#include <time.h>
#include <linux/limits.h>

int scandir(const char* wd,struct dirent ***entry, int (*select)(const struct dirent *),int(*compar)(const struct dirent **, const struct dirent **));
struct winsize win;
char* get_current_dir_name (void);
int s1=0, s2=0, s3=0, s4=0, s5=0, s6=0,zn=0,niz=0,sm=0,ms=0,pr=0,sme;
char home_directory[1000];

/*курсор*/
struct curs
{
	int col;
	int row;
	int s_col;
};

/*перемещение на первую строку*/
struct curs na_nachalo (struct curs cur)
{
	if (cur.s_col == 0)
		cur.col = 1;
	if (cur.s_col == 1)
		cur.col = s2+1;
	if (cur.s_col == 2)
		cur.col = s3+1;
	if (cur.s_col == 3)
		cur.col = s4+1;
	if (cur.s_col == 4)
		cur.col = s5+1;
	if (cur.s_col == 5)
		cur.col = s6+1;
	if (cur.s_col == 6)
		cur.col = s1+1;
	zn = 0;
	return cur;
}

/*Перемещение вверх-вниз*/
struct curs vverh_vniz(struct curs cur, int i,int j, int f)
{
	if (cur.row == 3)
	{
		if (i == -1)
		{
			if (niz>0)
				niz--;
			return cur;
		}
		cur.row ++;
		cur = na_nachalo (cur);
		return cur;
	}
	if (cur.row > 3 && cur.row < j-2 && cur.row < f+2)
	{
		cur.row += i;
		cur = na_nachalo (cur);
		return cur;
	}
	if (cur.row == j-2 || cur.row == f+2)
	{
		if (i == 1)
		{
			if (niz<(f-(j-3)))
				niz ++;
			return cur;
		}
		cur.row --;
		cur = na_nachalo (cur);
		return cur;
	}
return cur;
}

/*вправо по колонкам - кнопка ]*/
struct curs vpravo(struct curs cur)
{
	if (cur.s_col==0)
	{
		cur.s_col = 1;
		cur.col = s2+1;
		return cur;
	}
	if (cur.s_col == 1)
	{
		cur.s_col = 2;
		cur.col = s3+1;
		return cur;
	}
	if (cur.s_col == 2)
	{
		cur.s_col = 3;
		cur.col = s4+1;
		return cur;
	}
	if (cur.s_col == 3)
	{
		cur.s_col = 4;
		cur.col = s5+1;
		return cur;
	}
	if (cur.s_col == 4)
	{
		cur.s_col = 5;
		cur.col = s6+1;
		return cur;
	}
	if (cur.s_col >= 5)
	{
		cur.s_col = 6;
		cur.col = s1+1;
		return cur;
	}
return cur;
}

/*перемещение по колонкам влево кнопкой [ */
struct curs vlevo(struct curs cur)
{
	if (cur.s_col<=1)
	{
		cur.s_col = 0;
		cur.col = 0;
		return cur;
	}
	if (cur.s_col == 2)
	{
		cur.s_col = 1;
		cur.col = s2+1;
		return cur;
	}
	if (cur.s_col == 3)
	{
		cur.s_col = 2;
		cur.col = s3+1;
		return cur;
	}
	if (cur.s_col == 4)
	{
		cur.s_col = 3;
		cur.col = s4+1;
		return cur;
	}
	if (cur.s_col == 5)
	{
		cur.s_col = 4;
		cur.col = s5+1;
		return cur;
	}
	if (cur.s_col == 6)
	{
		cur.s_col = 5;
		cur.col = s6+1;
		return cur;
	}
	return cur;
}

/*переход влево вправо*/
struct curs vpravo_vlevo(struct curs cur, int i, int j)
{
	if (cur.s_col == 0)
	{
		if (cur.col>1 && cur.col<(s2-1))
			cur.col+=i;
		if (cur.col==1 && i>0)
			cur.col+=i;
		if (cur.col==s2-1 && i<0)
			cur.col+=i;
		if (cur.col==1 && zn!=0)
			zn--;
	}
	if (cur.s_col == 1)
	{
		if (cur.col>s2+1 && cur.col<(s3-1))
			cur.col+=i;
		if (cur.col==s2+1 && i>0)
			cur.col+=i;
		if (cur.col==s3-1 && i<0)
			cur.col+=i;
		if (cur.col==s2+1 && zn!=0)
			zn--;
		if (cur.col == s3-1)
			zn++;
	}
	if (cur.s_col == 2)
	{
		if (cur.col>s3+1 && cur.col<(s4-1))
			cur.col+=i;
		if (cur.col==s3+1 && i>0)
			cur.col+=i;
		if (cur.col==s4-1 && i<0)
			cur.col+=i;
		if (cur.col==s3+1 && zn!=0)
			zn--;
		if (cur.col == s4-1)
			zn++;
	}
	if (cur.s_col == 3)
	{
		if (cur.col>s4+1 && cur.col<(s5-1))
			cur.col+=i;
		if (cur.col==s4+1 && i>0)
			cur.col+=i;
		if (cur.col==s5-1 && i<0)
			cur.col+=i;
		if (cur.col==s4+1 && zn!=0)
			zn--;
		if (cur.col == s5-1)
			zn++;
	}
	if (cur.s_col == 4)
	{
		if (cur.col>s5+1 && cur.col<(s6-1))
			cur.col+=i;
		if (cur.col==s5+1 && i>0)
			cur.col+=i;
		if (cur.col==s6-1 && i<0)
			cur.col+=i;
		if (cur.col==s5+1 && zn!=0)
			zn--;
		if (cur.col == s6-1)
			zn++;
	}
	if (cur.s_col == 5)
	{
		if (cur.col>s6+1 && cur.col<(s1-1))
			cur.col+=i;
		if (cur.col==s6+1 && i>0)
			cur.col+=i;
		if (cur.col==s1-1 && i<0)
			cur.col+=i;
		if (cur.col==s6+1 && zn!=0)
			zn--;
		if (cur.col == s1-1)
			zn++;
	}
	if (cur.s_col == 6)
	{
		if (cur.col>s1+1 && cur.col<(j-1))
			cur.col+=i;
		if (cur.col==s1+1 && i>0)
			cur.col+=i;
		if (cur.col==(j-1) && i<0)
			cur.col+=i;
		if (cur.col==s1+1 && zn!=0)
			zn--;
		if (cur.col == j-1)
			zn++;
	}
	return cur;
}

int alphasort(const struct dirent **a, const struct dirent **b)
{
	struct stat buff_1,buff_2;
	stat((*a)->d_name, &buff_1);
	stat((*b)->d_name, &buff_2);
	if ((S_ISDIR(buff_1.st_mode) && (S_ISDIR(buff_2.st_mode))) || (!S_ISDIR(buff_1.st_mode) && (!S_ISDIR(buff_2.st_mode))))
		return strcoll ((*a)->d_name,(*b)->d_name);
	else if (S_ISDIR(buff_1.st_mode))
		return 0;
	else
		return 1;
}

void PrintTerminal(void)
{
	char* dir_name;
	int n=0, i=0;
	char symbol = '1';
	dir_name = get_current_dir_name();
	struct curs cursor = {1,3,0};
	struct dirent **namelist;
	s1 = (win.ws_col-6)/9;
	s2 = 3*s1+((win.ws_col-6)%9);
	s3 = s2+s1+1;
	s4 = s3+s1+1;
	s5 = s4+s1+1;
	s6 = s5+s1+1;
	s1 += s6+1;
	printf ("\033[H");
	printf("\033[35;1m%s\033[0m",dir_name);
	printf ("\033[2;1f");
	if (cursor.s_col == 0)
		printf ("\033[36;1mName\033[33m");
	else
		printf ("\033[33;1mName");
	printf("\033[0m\033[2;%df|", s2);

	if (cursor.s_col == 1)
		printf ("\033[36;1mOwner\033[33m");
	else
		printf ("\033[33;1mOwner");
	printf("\033[0m\033[2;%df|", s3);

	if (cursor.s_col == 2)
		printf ("\033[36;1mGroup\033[33m");
	else
		printf ("\033[33;1mGroup");
	printf("\033[0m\033[2;%df|", s4);

	if (cursor.s_col == 3)
		printf ("\033[36;1mLaws\033[33m");
	else
		printf ("\033[33;1mLaws");
	printf("\033[0m\033[2;%df|", s5);

	if (cursor.s_col == 4)
		printf ("\033[36;1mMod\033[33m");
	else
		printf ("\033[33;1mMod");
	printf("\033[0m\033[2;%df|", s6);

	if (cursor.s_col == 5)
		printf ("\033[36;1mDostup\033[33m");
	else
		printf ("\033[33;1mDostup");
	printf("\033[0m\033[2;%df|", s1);
	if (cursor.s_col == 6)
		printf ("\033[36;1mType\033[33m");
	else
		printf ("\033[33;1mType");
	printf("\033[0m\033[3;1f");
}

int main()
{
	char* dir_name;
	int n=0, i=0,err =0;
	char symbol = '1';
	dir_name = get_current_dir_name();
	struct curs cursor = {1,3,0};
	struct dirent **namelist;
	struct termios old_attributes,new_attributes;
	if(!isatty(0))
	{
		printf("Redirection\n");
        	return 1;
    	}
    	tcgetattr(0,&old_attributes);
    	memcpy(&new_attributes,&old_attributes,sizeof(struct termios));
    	new_attributes.c_lflag &= ~ECHO;
    	new_attributes.c_lflag &= ~ICANON;
    	new_attributes.c_cc[VMIN] = 1;
	tcsetattr(0,TCSANOW,&new_attributes);
	n = scandir(dir_name, &namelist, NULL, alphasort);
	printf ("\033[2J");

	do
	{
		printf ("\033[0;0f\033[J\033[0;0f");
		ioctl(STDOUT_FILENO,TIOCGWINSZ,&win);
		while (win.ws_col<70)
		    {
			ioctl(STDOUT_FILENO, TIOCGWINSZ, &win);
			printf("\x1B[2J\x1B[1;1HНечитабельный размер - увеличте терминал\n");
			symbol=getchar();
		    }
		PrintTerminal();
		if (symbol == ']')
		{
			cursor = vpravo(cursor);
			PrintTerminal();
		}
		if (symbol == '[')
		{
			cursor = vlevo(cursor);
			PrintTerminal();
                }
		if (symbol == '^')
		{
			chdir ("..");
			n = scandir(dir_name, &namelist, NULL, alphasort);
			cursor.row = 3;
			cursor.col = 1;
			cursor.s_col = 0;
			PrintTerminal();
		}
		if (symbol == 10)
		{
			int er = 0;
			n = cursor.row - 3;
			er = chdir (namelist[n]->d_name);
			if (er == -1)
				err = -2;
			n = scandir(dir_name, &namelist, NULL, alphasort);
			cursor.row = 3;
			cursor.col = 1;
			cursor.s_col = 0;
			PrintTerminal();
		}
		if (symbol == '\n')
		{
			int result;
			result = chdir(home_directory);
			if (result !=0)
				printf("\x1B[%d;0HFailure of reading Directory ", win.ws_row);
			else
			{
				cursor.row=3;
    				cursor.col=1;
				PrintTerminal();
			}
		}

		if (symbol == 27)
		{
			symbol=getchar();
			if (symbol == 91)
			{
				symbol=getchar();
				if (symbol == 65)
				{
					cursor = vverh_vniz(cursor, -1, win.ws_row, n);
					PrintTerminal();
				}
				if (symbol == 66)
				{
					cursor = vverh_vniz(cursor, 1, win.ws_row, n);
					PrintTerminal();
				}
				if (symbol == 67)
				{
					cursor = vpravo_vlevo(cursor, 1, win.ws_col);
					PrintTerminal();
				}
				if (symbol == 68)
				{
					cursor = vpravo_vlevo(cursor, -1, win.ws_col);
					PrintTerminal();
				}
			}
		}

		char* dir_name ;
		dir_name = get_current_dir_name();
		char rwx[10]="---------";
		char line[1000];
		struct tm* aTm;
		struct dirent **namelist;
		struct stat buff;
		struct passwd *pw;
		i=3;
		n = scandir(dir_name, &namelist, NULL, alphasort);
		sme=n;
		while(i<=win.ws_row-1)
		{
			if ((i+sm-3)>=n)
				break;
			stat(namelist[i+sm-3]->d_name, &buff);
			strcpy(rwx,"---------");
			if (cursor.col>0 && cursor.col<s1 && cursor.row==i)
			{
				printf("\x1B[1m\x1B[2m\x1B[32m");

				strncpy(line,namelist[i+sm-3]->d_name+ms,s1);
				if((int)strlen(namelist[i+sm-3]->d_name+ms)>s1)
					line[s1-2]='>';
				if (ms>0)
					line[0]='<';
				line[s1-1]='\0';
				printf("\x1B[%d;0H%s",i,line);
				sprintf(home_directory,"%s",namelist[i+sm-3]->d_name);
			}
			else
			{
				printf("\x1B[0m");
				strncpy(line,namelist[i+sm-3]->d_name,s1);
				if((int)strlen(namelist[i+sm-3]->d_name)>s1)
					line[s1-2]='>';
				line[s1-1]='\0';
				printf("\x1B[%d;0H%s",i,line);
			}

			if (cursor.col>s1 && cursor.col<s2 && cursor.row==i)
				printf("\x1B[1m\x1B[2m\x1B[32m");
			else
				printf("\x1B[0m");
			if (S_ISDIR(buff.st_mode))
				printf("\x1B[%d;%dHDirectory ",i,s1+1);
			else if (S_ISLNK(buff.st_mode))
				printf("\x1B[%d;%dHLink ",i,s1+1);
			else if (S_ISREG(buff.st_mode))
				printf("\x1B[%d;%dHFile ",i,s1+1);
			else if (S_ISCHR(buff.st_mode))
				printf("\x1B[%d;%dHCHR ",i,s1+1);
			else if (S_ISBLK(buff.st_mode))
				printf("\x1B[%d;%dHBlock file ",i,s1+1);
			else if (S_ISFIFO(buff.st_mode))
				printf("\x1B[%d;%dHPipe or FIFO ",i,s1+1);
			else 	printf("\x1B[%d;%dHSOCK ",i,s1+1);
			if (cursor.col>s2 && cursor.col<s3 && cursor.row==i)
				printf("\x1B[1m\x1B[2m\x1B[32m");
			else
				printf("\x1B[0m");
				printf("\x1B[%d;%dH ",i,s2+1);
				pw = getpwuid (buff.st_uid);
				printf ("%s", pw->pw_name);

			if (cursor.col>s3 && cursor.col<s4 && cursor.row==i)
				printf("\x1B[1m\x1B[2m\x1B[32m");
			else
				printf("\x1B[0m");
			printf("\x1B[%d;%dH ",i,s3+1);
				pw = getpwuid (buff.st_uid);
				printf ("%s", pw->pw_name);


			if (buff.st_mode & S_IRUSR)
				rwx[0]='r';
			if (buff.st_mode & S_IWUSR)
				rwx[1]='w';
			if (buff.st_mode & S_IXUSR)
				rwx[2]='x';
			if (buff.st_mode & S_IRGRP)
				rwx[3]='r';
			if (buff.st_mode & S_IWGRP)
				rwx[4]='w';
			if (buff.st_mode & S_IXGRP)
				rwx[5]='x';
			if (buff.st_mode & S_IROTH)
				rwx[6]='r';
			if (buff.st_mode & S_IWOTH)
				rwx[7]='w';
			if (buff.st_mode & S_IXOTH)
				rwx[8]='x';

			if (cursor.col>s4 && cursor.col<s5 && cursor.row==i)
			{
				printf("\x1B[1m\x1B[2m\x1B[32m");
				strncpy(line,rwx+ms,(s5-s4));
				if((int)strlen(rwx+ms)>(s5-s4))
					line[s5-s4-2]='>';
				if (ms>0)
					line[0]='<';
				line[s5-s4-1]='\0';
				printf("\x1B[%d;%dH%s",i,s4+1,line);
			}
			else
			{
				printf("\x1B[0m");
				strncpy(line,rwx,(s5-s4));
				if((int)strlen(rwx)>(s5-s4))
					line[s5-s4-2]='>';
				line[s5-s4-1]='\0';
				printf("\x1B[%d;%dH%s",i,s4+1,line);
			}
			aTm= localtime(&buff.st_mtime);
			if (cursor.col>s5 && cursor.col<s6 && cursor.row==i)
			{
				printf("\x1B[1m\x1B[2m\x1B[32m");
				sprintf(line,"%s", asctime(aTm)+ms);
				printf("\x1B[%d;%dH",i,s5+1);
				if((int)strlen(line)>(s5-s4))
					line[s5-s4-2]='>';
				if (ms>0)
					line[0]='<';
				line[s5-s4-1]='\0';
				printf("\x1B[%d;%dH%s",i,s5+1,line);
			}
			else
			{
				printf("\x1B[0m");
				sprintf(line,"%s", asctime(aTm));
				printf("\x1B[%d;%dH",i,s5+1);
				if((int)strlen(line)>(s5-s4))
					line[s5-s4-2]='>';
				line[s5-s4-1]='\0';
				printf("\x1B[%d;%dH%s",i,s5+1,line);
			}

			aTm= localtime(&buff.st_atime);
			if (cursor.col>s6 && cursor.col<win.ws_col && cursor.row==i)
			{
				printf("\x1B[1m\x1B[2m\x1B[32m");
				sprintf(line,"%s", asctime(aTm)+ms);
				printf("\x1B[%d;%dH",i,s6+1);
				if((int)strlen(line)>(s5-s4))
					line[s5-s4-2]='>';
				if (ms>0)
					line[0]='<';
				line[s5-s4-1]='\0';
				printf("\x1B[%d;%dH%s",i,s6+1,line);
			}
			else
			{
				printf("\x1B[0m");
				sprintf(line,"%s", asctime(aTm));
				printf("\x1B[%d;%dH",i,s6+1);
				if((int)strlen(line)>(s5-s4))
					line[s5-s4-2]='>';
				line[s5-s4-1]='\0';
				printf("\x1B[%d;%dH%s",i,s6+1,line);
			}
			i++;
			printf("\x1B[%i;1H\x1B[K",i);
		}

		for(i=0;i<n;i++)
		{
			free(namelist[i]);
		}
		free(namelist);
		free (dir_name);

		printf ("\033[%d;%df", cursor.row, cursor.col);
	}

	 while ((symbol=getchar())!=EOF && symbol != 'q');
	tcsetattr(0,TCSANOW,&old_attributes);
	printf("\033[H\033[2J");
	printf("Настройки терминала изменены обратно\n");
	return 0;
}
