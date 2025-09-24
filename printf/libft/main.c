#include "libft.h"

// ../github_libft/ft_atoi.c :
// int	main(void)
// {
// char test[]=" ---+--+1234ab567";
// printf("%d\n",ft_atoi(test));
// }

// ../github_libft/ft_bzero.c :
// int main()
// {
// char str[] ="AAAAAAAAaaaaaaaaaaaaaaa";
// bzero(str, 5);
// printf("%s\n",str);
// char str2[] ="AAAAAAAA";
// ft_bzero(str2, 5);
// printf("%s\n",str2);
// int i = 0;
// while(i<8)
// {
//     write(1,&str[i],1);
//     i++;
// }
// write(1,"\n",1);
// i=0;
// while(i<8)
// {
//     write(1,&str2[i],1);
//     i++;
// }
// write(1,"\n",1);
// }

// ../github_libft/ft_calloc.c :
// int main()
// {   
// int i;
// unsigned char *result = (unsigned char *)ft_calloc(3, 4);
// i = 0;
// while(i<3*4)
// {
// printf("%d ", result[i]);
// i++;
// }
// printf("\n");
// }

// ../github_libft/ft_isalnum.c :
// int main()
// {
//  	int c ='*';
//  	int d ='1';
//  	printf("%d\n",ft_isalnum(c));
//  	printf("%d\n",ft_isalnum(d));
//      printf("%d\n",isalnum(c));
//  	printf("%d\n",isalnum(d));
// }

// ../github_libft/ft_isalpha.c :
//  int main()
//  {
//  	int c ='Z';
//  	int d ='*';
//  	printf("%d\n",ft_isalpha(c));
//  	printf("%d\n",ft_isalpha(d));
//      printf("%d\n",isalpha(c));
//  	printf("%d\n",isalpha(d));
//  }

// ../github_libft/ft_isascii.c :
//  int main()
//  {
//  	int c = 50;
//  	int d = 500;
//  	printf("%d\n",ft_isascii(c));
//  	printf("%d\n",ft_isascii(d));
//      printf("%d\n",isascii(c));
//  	printf("%d\n",isascii(d));
//  }

// // ../github_libft/ft_isdigit.c :
//  int main()
//  {
//  	int c ='Z';
//  	int d ='1';
//  	printf("%d\n",ft_isdigit(c));
//  	printf("%d\n",ft_isdigit(d));
//      printf("%d\n",isdigit(c));
//  	printf("%d\n",isdigit(d));
//  }

// ../github_libft/ft_isprint.c :
//  int main()
//  {
//  	int c ='Z';
//  	int d ='\n';
//  	printf("%d\n",ft_isprint(c));
//  	printf("%d\n",ft_isprint(d));
//      printf("%d\n",isprint(c));
//  	printf("%d\n",isprint(d));
//  }

// ../github_libft/ft_itoa.c :
//  int main()
//  {
//  	int n = -2147483648;
//  	printf("%s\n",ft_itoa(n));
//  }

// ../github_libft/ft_memchr.c :
//  int main()
// int main()
// {
// char str1[]="aaaaaaaaaaaaaaaaa";
// str1[2]=-1;
// printf("%p\n", &str1[2]);
// printf("%p\n", memchr(str1,255,12));
// printf("%p\n", ft_memchr(str1,255,12));
// str1[4]=255;
// printf("%p\n", &str1[4]);
// printf("%p\n", memchr(str1,255,12));
// printf("%p\n", ft_memchr(str1,255,12));
// }
//  }

// ../github_libft/ft_memcmp.c :
//  int main()
//  {
//  	char s1[] = "aaaaaaaaaaaaaaaa";
//  	char s2[] = "aaaabaaa";
//  	size_t n = 6;
//  	printf("%d\n",memcmp(s1,s2,n));
//  	printf("%d\n",ft_memcmp(s1,s2,n));
//  }

// ../github_libft/ft_memcpy.c :
//  int main()
//  {
//  char dest1[] = "                             ";
//  char str[] ="AAAAAAAAaaaaaaaaaaaaaaa";
//  memcpy(dest1, str, 4);
//  printf ("%s\n",dest1);
//  char dest2[] = "                  ";
//  char str2[] ="AAAAAAAA";
//  ft_memcpy(dest2, str2, 4);
//  printf ("%s\n",dest2);
//  }

// ../github_libft/ft_memmove.c :
//  int main()
//  {
//  	char dest[] = "aaaaaaaaaaaaaaaaaaaaaa";
// 	printf ("%p\n",dest);
//  	char src[] = "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb";
//  	size_t n = 4;
//  	printf("%p\n",memmove(dest,src,n));
//  	printf ("%s\n",dest);
//  	char dest2[] = "aaaaaaaaaaaaaaaaaaaaaa";
// 	printf ("%p\n",dest2);
//  	char src2[] = "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb";
//  	size_t n2 = 4;
//  	printf("%p\n",ft_memmove(dest2,src2,n2));
//  	printf ("%s\n",dest2);
//  }

// ../github_libft/ft_memset.c :
//  int main()
//  {
//  char str[] ="AAAAAAAA";
//  memset(str, 'X', 4);
//  printf ("%s\n",str);
//  printf("%p\n",memset(str, 'X', 4));
//  char str2[] ="AAAAAAAA";
//  ft_memset(str2, 'X', 4);
//  printf ("%s\n",str2);
//  printf("%p\n",ft_memset(str2, 'X', 4));
//  }

// ../github_libft/ft_putchar_fd.c :
//  int main()
//  {
//  int fd = open("fichier.txt", O_WRONLY);
//  ft_putchar_fd('Z',fd);
//  }

// ../github_libft/ft_putendl_fd.c :
//  int main()
//  {
// char *s;
// s = "NULL";
//  int fd = open("fichier.txt", O_WRONLY);
//  ft_putendl_fd(s,fd);
//  }

// ../github_libft/ft_putnbr_fd.c :
//  int main()
//  {
//  int fd;
//  fd = open("fichier.txt", O_WRONLY);
//  ft_putnbr_fd(-2147483648,fd);
//  ft_putchar_fd('\n',fd);
//  ft_putnbr_fd(83648,fd);
//  ft_putchar_fd('\n',fd);
//  }

// ../github_libft/ft_putstr_fd.c :
 int main()
{
char *s;
s= NULL;

 int fd = open("fichier.txt", O_WRONLY);
 ft_putstr_fd(s,fd);
 }

// ../github_libft/ft_split.c :
//  int main()
//  {
//  	char *s = "Hello this is a test";
//  	char c = ' ';
//  	int i = 0;
//  	char **res;
//  	res = ft_split(s,c);
//  	while (res[i])
//  	{
//  		printf("%s\n",res[i]);
//  		free(res[i]);
//  		i++;
//  	}
//  	free(res);
//  }

// ../github_libft/ft_strchr.c :
//  int main()
//  {
//  const char str1[]="aaaaaabaaaaaaaaaaa";
//  printf("%p\n", strchr(str1,'b'));
//  printf("%p\n", ft_strchr(str1,'b'));
//  }

// ../github_libft/ft_striteri.c :
//  static void replace_odd_with_star(unsigned int i, char *c) 
// {
//     if (i % 2 != 0)
//     {
//         *c = '*';
//     }
// }
// int main()
// {
//  	char test[] ="irgeuirhguiehruig";
//  	ft_striteri(test, replace_odd_with_star);
//  	printf("%s\n",test);
// }

// ../github_libft/ft_strjoin.c :
//  int main()
//  {
//  	char const s1[] = "toto";
//  	char const s2[] = "tutu";
//  	printf("%s\n",ft_strjoin(s1,s2));
//  }

// ../github_libft/ft_strlcat.c :
//  int main()
//  {
//  char s1[30]="aa";
//  char s2[]="bb";
//  	printf("%d\n",ft_strlcat(s1,s2,15));
//  	printf ("%s\n",s1);
//  char s3[30]="aa";
//  char s4[]="bb";
//  printf("%zu\n",strlcat(s3,s4,15));
//  	printf ("%s\n",s3);
//  }

// ../github_libft/ft_strlcpy.c :
//  int main()
//  {
//  char s1[30]="aa";
//  char s2[]="bb";
//  	printf("%d\n",ft_strlcpy(s1,s2,15));
//  	printf ("%s\n",s1);
//  char s3[30]="aa";
//  char s4[]="bb";
//  printf("%zu\n",strlcpy(s3,s4,15));
//  	printf ("%s\n",s3);
//  }

// ../github_libft/ft_strlen.c :
// int main()
// {
// 	char s[]="aaaaa";
// 	printf("%d\n",ft_strlen(s));
// }

// ../github_libft/ft_strmapi.c :
// static char replace_odd_with_star(unsigned int i, char c) 
// {
//     if (i % 2 != 0)
//         return '*';
//     return c;
// }
//  int main()
//  {
//  	const char *test ="irgeuirhguiehruig";
//  	char	*res = ft_strmapi(test, replace_odd_with_star);
//  	printf("%s\n",res);
//  }

// ../github_libft/ft_strncmp.c :
//  int main()
//  {
//  	char s1[] = "aaaaaaaaaaaaaaaa";
//  	char s2[] = "aaaa1aaa";
//  	size_t n = 6;
//  	printf("%d\n",strncmp(s1,s2,n));
//  	printf("%d\n",ft_strncmp(s1,s2,n));
//  }

// ../github_libft/ft_strnstr.c :
//  int main()
//  {
//      char s1[]="ytjtj6u6bonjour ";
//  	char s2[]="bonlffdf ";
//  	printf("%s", ft_strnstr(s1,s2,3));
//  }

// ../github_libft/ft_strrchr.c :
//  int main()
//  {
//  const char str1[]="aaaaaabaaaabaaaaaaa";
//  printf("%p\n", strrchr(str1,'b'));
//  printf("%p\n", ft_strrchr(str1,'b'));
//  }

// ../github_libft/ft_substr.c :
//  int main()
//  {
//  char str2[]="aganeowohorihioeihe";
//  printf("%s\n", ft_substr(str2,4,3));
//  }

// ../github_libft/ft_tolower.c :
//  int main()
//  {
//  int c = 'B';
//  printf("%c\n",ft_tolower(c));
//  }

// ../github_libft/ft_toupper.c :
//  int main()
//  {
//  int c = 'b';
//  printf("%c\n",ft_toupper(c));gi
//  }

// ../github_libft/ft_strdup.c :
// int main()
// {	char *res;
// 	char *s = "AAAAAAAA";
// 	res = ft_strdup(s);
// 	printf("%s\n",res);
// }


// ../github_libft/ft_strtrim.c :
// int main()
// {
// 	char const *s="abcXXXabc";
// 	char const *set="cba";
// 	printf("%s\n",ft_strtrim(s,set));
// }
