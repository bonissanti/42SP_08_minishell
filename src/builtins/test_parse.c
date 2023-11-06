#include <string.h>

#include <string.h>

int get_quote_type(char *arg)
{
	int i;
   	int quote_type;
	
   	i = 0;
   	quote_type = 0;
   	while (arg[i] != '\0')
   	{
		  if (arg[i] == '\'' && quote_type == 0)
			 quote_type = 1;
		  else if (arg[i] == '\"' && quote_type == 0)
			 quote_type = 2;
		  else if (arg[i] == '\"' && quote_type == 1)
			 quote_type = 3;
		  else if (arg[i] == '\'' && quote_type == 2)
			 quote_type = 4;
		  i++;
   	}
   	return (quote_type);
}


#include <stdio.h>

int main() {
   char arg[] = "Amanda 'tem' \"teta grande\"";
   int quote_type = get_quote_type(arg);
   printf("Quote type: %d\n", quote_type);
   return 0;
}
