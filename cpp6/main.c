#include <stdio.h>
#include <string.h>  /* for strlen() */
#include "stack.h"

int isMatchingPair(char character1, char character2)
{
   if (character1 == '(' && character2 == ')')
     return 1;
   else if (character1 == '{' && character2 == '}')
     return 1;
   else if (character1 == '[' && character2 == ']')
     return 1;
   else if (character1 == '<' && character2 == '>')
     return 1;
   else
     return 0;
}


/*Return 1 if expression has balanced Parenthesis */
int areParenthesisBalanced(char *str)
{
   int i = 0;

   /* Declare an empty character stack */
   stackT stack;
   char *traverse;
   StackNew(&stack, strlen(str));

   /* Traverse the given expression to check matching parenthesis */
   for(traverse = str;*traverse !='\0'; traverse++)
   {

      /*If the *traverse is a starting parenthesis then push it*/
      if (*traverse == '{' || *traverse == '(' || *traverse == '[' || *traverse == '<')
            StackPush(&stack, *traverse);

      /* If *traverse is an ending parenthesis then pop from stack and
          check if the popped parenthesis is a matching pair*/
      if (*traverse == '}' || *traverse == ')' || *traverse == ']' || *traverse == '>')
      {

          /*If we see an ending parenthesis without a pair then return false*/
         if (StackIsEmpty(&stack))
           return 0;

         /* Pop the top element from stack, if it is not a pair
            parenthesis of character then there is a mismatch.
            This happens for expressions like {(}) */
         else {
            char c =  StackPop(&stack);
            if ( !isMatchingPair(c, *traverse) )
                return 0;
         }
      }
   }

   /* If there is something left in expression then there is a starting
      parenthesis without a closing parenthesis */
   if (StackIsEmpty(&stack))
     return 1; /*balanced*/
   else
     return 0;  /*not balanced*/
}

int main(void)
{
	   /* A stack to hold characters. */
	char str[81];   /* String entered by user. */
					 /*
					 * Get a string from the user--don't enter more
					 * than 80 characters!
					 */
	printf("Enter a string: ");

	gets(str);  /* Read line, discard newline. */

    if (areParenthesisBalanced(str))
        printf("\n Correct ");
    else
        printf("\n Not Correct ");
    return 0;
}
