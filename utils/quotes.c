#include "../minishell.h"

bool	has_invalid_redirects(const char* str)
{
	int len;
	int redirectCount = 0;
	char current_char;

	len = ft_strlen(str);
	for (int i = 0; i < len; i++)
	{
		current_char = str[i];
		if (current_char == '>' || current_char == '<') {
			redirectCount++;
			if (redirectCount > 2) {
				printf("Error: Invalid Redirects\n");
				return true;
			}
		} else {
			redirectCount = 0;
		}
	}

	return false;
}

bool	has_missing_quotes(const char* str)
{
	int len;
	char current_char;
	bool insideSingleQuotes = false;
	bool insideDoubleQuotes = false;

	len = ft_strlen(str);
	for (int i = 0; i < len; i++) 
	{
		current_char = str[i];
		if (current_char == '\'' && !insideDoubleQuotes) 
			insideSingleQuotes = !insideSingleQuotes;
		else if (current_char == '\"' && !insideSingleQuotes) 
			insideDoubleQuotes = !insideDoubleQuotes;
	}

	if (insideSingleQuotes || insideDoubleQuotes) {
		printf("Error: Missing Quotes\n");
		return true;
	}

	return false;
}

bool	check_input(const char* str)
{
	if (hasInvalidRedirects(str) || hasMissingQuotes(str))
		return true;
	return false;
}
