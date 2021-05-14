#include "libasm.h"

#define OK "[\e[0;32mOK\e[0m]\n"
#define KO "[\e[0;31mKO\e[0m]\n"
#define CHECK(x) (x ? OK : KO) 

void	free_lst(t_list *head)
{
	/* FREE */
	for (t_list *next, *cur = head; next && cur; cur = next)
	{
		next = cur->next;
		free(cur);
	}
}

void	print_errno()
{
	char *str = strerror(errno);
	write(1, str, strlen(str));
	write(1, "\n", 1);
}

void	strlen_t()
{
	printf("\t===================\e[0;35m[STRLEN]\e[0m==========================\n");

	char *strs[] = {"str1", "str2i ", "str33333333333", "str44444444444", "a",
	"", "asdfasdfasdfadsfa"
		, "veeeeiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiing", 0};

	for (size_t i = 0; strs[i]; i++)
	{
		char *s = strs[i];
		size_t std = strlen(s);
		size_t ft = ft_strlen(s);
		printf("\tstr[%ld]=\"%20.20s\"%20.20s\tstd %ld, %ld yours\n\n",
					   i , 	  s,CHECK(std == ft), std, ft);
	}
}

void	strcpy_t()
{
	printf("\t===================\e[0;35m[STRCPY]\e[0m==========================\n");

	char *strs[] = {"str1", "str2i ", "str33333333333", "str44444444444", "a",
	"", "asdfasdfasdfadsfa"
		, "veeeeiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiing", 0};
	
	char buf1[200];
	char buf2[200];

	for	(size_t i = 0; strs[i]; i++)
	{
		char *s = strs[i];
		char *std = strcpy(buf1, s);
		char *ft = ft_strcpy(buf2, s);
		int	cmp = strcmp(std, ft);	
		printf("\tstr[%ld]=\"%20.20s\"%20s\tstd \"%.20s\", \"%.20s\" yours\n\n",
					   i , 	  s,CHECK(cmp == 0), std, ft);
	}
}

void	strcmp_t()
{
	printf("\t===================\e[0;35m[STRCMP]\e[0m==========================\n");

	char *strs[] = {"str1", "str2i ", "str33333333333", "str44444444444", "a",
	"", "asdfasdfasdfadsfa"
		, "veeeeiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiing", 0};

	for	(size_t i = 0; strs[i]; i++)
	{
		for(size_t j = i;strs[j]; j++)
		{
			char	*s1 = strs[i];
			char	*s2 = strs[j];

			int		std = strcmp(s1, s2);
			std = std == 0 ? 0 : (std > 0 ? 1 : -1);
			int		ft = ft_strcmp(s1, s2);
			ft = ft == 0 ? 0 : (ft > 0 ? 1 : -1);

			printf("\ts1=\"%20.20s\" s2=\"%20.20s\" %s\tstd %i, %i yours\n\n",
					   	s1,	  s2,CHECK(std==ft), std, ft);
		}
	}
}

void	write_t()
{
	char str[] = "\n\t===================\e[0;35m[WRITE]\e[0m==========================\n";
	char *strs[] = {"str1", "str2i ", "str33333333333", "str44444444444", "a",
	"", "asdfasdfasdfadsfa"
		, "veeeeiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiing", 0};
	size_t check_len = strlen(CHECK(0));
	int ft, std;

	write(1, str, strlen(str));

	for (int i = 0; strs[i]; i++)
	{
		char *s = strs[i];
		size_t len = strlen(s);	

		write(1, "std:\"", 5);
		std = write(1, s, len);
		write(1, "\" ", 2);

		write(1, "\nft :\"", 6);
		ft = ft_write(1, s, len);
		write(1, "\" ", 2);
		write(1, CHECK(ft==std), check_len);
	}

	/* Check errno on error cases */
	int fail_fd = 32;
	std = write(fail_fd, "", 1); print_errno(); errno = 0;
	ft = ft_write(fail_fd, "", 1); print_errno(); errno = 0;
	write(1, CHECK(std==ft), check_len);
	std = write(1, NULL, 1); print_errno(); errno = 0;
	ft = ft_write(1, NULL, 1); print_errno(); errno = 0;
	write(1, CHECK(std==ft), check_len);

	std = write(1, "", -1); print_errno(); errno = 0;
	ft = ft_write(1, "", -1); print_errno(); errno = 0;
	write(1, CHECK(std==ft), check_len);
}

void	read_t()
{
	char str[] = "\n\t===================\e[0;35m[READ]\e[0m==========================\n";

	write(1, str, strlen(str));
	
	char *buf = calloc(sizeof(*buf), 1000);
	int fd = open("test.txt", O_RDWR);
	int std;
	int ft;
	int check_len = strlen(CHECK(1));
	/* Check on real file */
	std = read(fd, buf, 1000);
	lseek(fd, 0, SEEK_SET);
	write(1, buf, std);
	write(1, "\n", 1);
	ft = ft_read(fd, buf, 1000);
	lseek(fd, 0, SEEK_SET);
	write(1, buf, ft);
	write(1, CHECK(ft==std), check_len);	
	
	/* Check errno on error cases */	
	int fail_fd = 123;
	std = read(fail_fd, buf, 123); print_errno(); errno = 0;
	lseek(fd, 0, SEEK_SET);
	ft = ft_read(fail_fd, buf, 123); print_errno(); errno = 0;
	lseek(fd, 0, SEEK_SET);
	write(1, CHECK(ft==std), check_len);	
	
	char *fail_addr = NULL;
	std = read(fd, fail_addr, 123); print_errno(); errno = 0;
	lseek(fd, 0, SEEK_SET);
	ft = ft_read(fd, fail_addr, 123); print_errno(); errno = 0;
	lseek(fd, 0, SEEK_SET);
	write(1, CHECK(ft==std), check_len);	

	int	neg_size = -1;
	std = read(fd, buf,	neg_size); print_errno(); errno = 0;
	lseek(fd, 0, SEEK_SET);
	ft = ft_read(fd, buf, neg_size); print_errno(); errno = 0;
	lseek(fd, 0, SEEK_SET);
	write(1, CHECK(ft==std), check_len);	
	close(fd);
	
	/* Write only permission */
	fd = open("test.txt", O_WRONLY);
	std = read(fd, buf, 100); print_errno(); errno = 0;
	lseek(fd, 0, SEEK_SET);
	ft = ft_read(fd, buf, 100); print_errno(); errno = 0;
	lseek(fd, 0, SEEK_SET);
	write(1, CHECK(ft==std), check_len);	
	close(fd);	
}
void	strdup_t()
{
	printf("\t===================\e[0;35m[STRDUP]\e[0m==========================\n");

	char *str[] = {"str1", "str2i ", "str33333333333", "str44444444444", "a",
	"", "asdfasdfasdfadsfa"
		, "veeeeiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiing", 0};
	char *std;
	char *ft;
	int i = -1;
	while(str[++i])
	{
		ft = ft_strdup(str[i]);
		std = strdup(str[i]);
		printf("std[%ld]=\"%s\" ft[%ld]=\"%s\" %s",
				ft_strlen(std), std, ft_strlen(ft), ft, CHECK(ft_strcmp(ft, std)==0));
		free(ft);
		free(std);
	}

	/*here str[i] == NULL 
	  SIGSEGV excepted  
	
	ft = ft_strdup(str[i]);
	std = strdup(str[i]);
	printf("std[%ld]=\"%s\" ft[%ld]=\"%s\" %s", ft_strlen(std), std, ft_strlen(ft), ft,
	CHECK(ft_strcmp(ft, std)==0));*/
}

void	list_push_front_t()
{
	printf("\t===================\e[0;35m[STRDUP]\e[0m==========================\n");

	char *str[] = {"first", "second ", "3333333333333333333333", "4444444", "5555555",
	"next will be emty", ""
		, "last node", 0};

	t_list *head;
	int i;

	i = 0;
	while (str[i])  
		i++;
	head = NULL;
	head = list_init("I am the real first");
	for (i -= 1; i >= 0; i--)
		ft_list_push_front(&head, (void *)str[i]);
	for (t_list *cur = head; cur; cur = cur->next)
		printf("|%s|---->", (char *)cur->data);
	printf("|NULL|");
	
	free_lst(head);
}
void	list_size_t()
{
	
	printf("\t===================\e[0;35m[LIST_SIZE]\e[0m==========================\n");

	char *str[] = {"first", "second ", "3333333333333333333333", "4444444", "5555555",
	"next will be emty", ""
		, "last node", 0};

	t_list *head;
	head = NULL;
	int i = 0;
	int	size;
	while (str[i])
		ft_list_push_front(&head, str[i++]);
	size = ft_list_size(head);
	free_lst(head);
	printf("real [%d] == [%d] your %s", i, size, CHECK(size==i));
	size = ft_list_size(NULL);
	printf("real [%d] == [%d] your %s", i, size, CHECK(size==0));
}

void	bonus_t()
{
	list_push_front_t();
	list_size_t();
}
int		main()
{
	write_t();
	read_t();
	strlen_t();
	strcpy_t();
	strcmp_t();
	strdup_t();
	bonus_t();
}
