/***************************************
* Author: Yoni Wainsztok
* Date: 6/1/19
***************************************/

#include <stdio.h>  /* printf */
#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */
#include <string.h> /* strlen */
#include <math.h> /* pow */

#include "stack.h" /* Stack Functions */
#include "calc.h" /* API */

const int ERROR = 4; /* for next.state definitions in LUT_state_table*/
const int END = 3; /* for next.state definitions in LUT_state_table*/

/* Machine Lut Components */
struct transition
{
	action_func action;
	int next_state;
};
typedef struct transition transition;

/*Calculator Stacks*/
stack_t *NUM_STACK;
stack_t *SIGN_STACK;

/* Machine States */
enum states
{
	VALID_OR_OPEN, 
	OPER_OR_CLOSE, 
	MAX_STATES
} current_state;

/* Machine Events */
enum events
{
	VALID, 
	OPER, 
	OPEN, 
	CLOSE, 
	NOT_VALID, 
	EOS, 
	SPACE, 
	WRONG_BRACKET, 
	MAX_EVENTS
} new_event;

/* Actions Precedence */
enum precedence
{
	Dummy, 
	Open_Bracket, 
	Plus_Minus, 
	Mult_Div, 
	Pow, 
	Close_Bracket
};

/* Machine LUT of state-table */
transition LUT_state_table [MAX_EVENTS][MAX_STATES];

/* Complementary LUTs */
int LUT_get_event[127] = {NOT_VALID}; 
get_input LUT_get_event_type[2] = {0}; 
int LUT_Sign_precedence[125] = {0};
calc LUT_oper[125] = {0};
int LUT_parenthesis[125] = {0};
is_brace_err LUT_is_braces_error[125][125] = {0};

int main(void)
{
	char math_exec[100] = {0};
	char *math = NULL;
	int state = 0;
	event_pack Event = {0};

	printf("Enter math exercise:\n"); 
	scanf("%[^\n]%*c", math_exec);
	math = math_exec;
	 
	start();
	do
	{
		math = LUT_get_event_type[state](math, &Event);
		LUT_state_table[Event.event_enum][state].action(&Event, NULL);
		state = LUT_state_table[Event.event_enum][state].next_state;

	}while(END > state);

	Destroy();
	return (0);
}

char *GetNum(char *str, event_pack *event)
{
	size_t len = 0;
	double extracted_num = 0;

	len = strlen(str);
	extracted_num = strtod(str, &str);
	if(len == strlen(str))
	{
		str = GetSign(str, event);
	}
	else
	{
		event->input.num = extracted_num;
		event->event_enum = VALID;
	}

	return (str);
}

char *GetSign(char *str, event_pack *event)
{
	event->input.operator.sign = *str;
	switch(*str)
	{
		case '+':
		case '-':
			event->event_enum = OPER;
			event->input.operator.precedence = Plus_Minus;
			break;
		case '*':
		case '/':
			event->event_enum = OPER;
			event->input.operator.precedence = Mult_Div;
			break;
		case '^':
			event->event_enum = OPER;
			event->input.operator.precedence = Pow;
			break;
		case '(':
		case '[':
		case '{':
			event->event_enum = OPEN;
			event->input.operator.precedence = Open_Bracket;
			break;
		case ')':
		case ']':
		case '}':
			event->event_enum = CLOSE;
			event->input.operator.precedence = Close_Bracket;
			break;
		case '\0':
			event->event_enum = EOS;
			break;
		case ' ':
			event->event_enum = SPACE;
			break;
		default :
			event->event_enum = NOT_VALID;
	}
	++str;

	return (str);
}

void Destroy()
{
	StackDestroy(SIGN_STACK);
	StackDestroy(NUM_STACK);
}

void start()
{
	StacksInit();
	LUTStateTableInit();
	LUTGetEventInit();
	LUTPrecedenceInit();
	LUTGetEventTypeInit();
	LUTOperInit();
	LUTParenthesisInit();
	LUTIsBraceErrInit();
}

void LUTIsBraceErrInit()
{
	LUT_is_braces_error['(']['('] = Calc;
	LUT_is_braces_error['(']['+'] = Calc;
	LUT_is_braces_error['(']['-'] = Calc;
	LUT_is_braces_error['(']['*'] = Calc;
	LUT_is_braces_error['(']['/'] = Calc;
	LUT_is_braces_error['(']['^'] = Calc;
	LUT_is_braces_error['(']['['] = BracketError;
	LUT_is_braces_error['(']['{'] = BracketError;
	LUT_is_braces_error['(']['$'] = BracketError;

	LUT_is_braces_error['[']['['] = Calc;
	LUT_is_braces_error['[']['+'] = Calc;
	LUT_is_braces_error['[']['-'] = Calc;
	LUT_is_braces_error['[']['*'] = Calc;
	LUT_is_braces_error['[']['/'] = Calc;
	LUT_is_braces_error['[']['^'] = Calc;
	LUT_is_braces_error['[']['('] = BracketError;
	LUT_is_braces_error['[']['{'] = BracketError;
	LUT_is_braces_error['[']['$'] = BracketError;

	LUT_is_braces_error['{']['{'] = Calc;
	LUT_is_braces_error['{']['+'] = Calc;
	LUT_is_braces_error['{']['-'] = Calc;
	LUT_is_braces_error['{']['*'] = Calc;
	LUT_is_braces_error['{']['/'] = Calc;
	LUT_is_braces_error['{']['^'] = Calc;
	LUT_is_braces_error['{']['('] = BracketError;
	LUT_is_braces_error['{']['['] = BracketError;
	LUT_is_braces_error['{']['$'] = BracketError;

	LUT_is_braces_error['+']['$'] = DoNothingVoidDouble;
	LUT_is_braces_error['-']['$'] = DoNothingVoidDouble;
	LUT_is_braces_error['*']['$'] = DoNothingVoidDouble;
	LUT_is_braces_error['/']['$'] = DoNothingVoidDouble;
	LUT_is_braces_error['^']['$'] = DoNothingVoidDouble;
}

void LUTParenthesisInit()
{
	LUT_parenthesis[')'] = '(';
	LUT_parenthesis[']'] = '[';
	LUT_parenthesis['}'] = '{';
}

void LUTOperInit()
{
	int i = 0;
	for(i = 0; i < 124; ++i)
	{
		LUT_oper[i] = DoNothingVoidDouble;
	}
	LUT_oper['*'] = Multiply;
	LUT_oper['+'] = Add;
	LUT_oper['-'] = Difference;
	LUT_oper['/'] = Divide;
	LUT_oper['^'] = Power;

	LUT_oper['('] = BracketError;
	LUT_oper['['] = BracketError;
	LUT_oper['{'] = BracketError;
}

void LUTGetEventTypeInit()
{
	LUT_get_event_type[0] = GetNum;
	LUT_get_event_type[1] = GetSign;
}
void LUTPrecedenceInit()
{
	LUT_Sign_precedence['$'] = Dummy;
	LUT_Sign_precedence['*'] = Mult_Div;
	LUT_Sign_precedence['+'] = Plus_Minus;
	LUT_Sign_precedence['-'] = Plus_Minus;
	LUT_Sign_precedence['/'] = Mult_Div;
	LUT_Sign_precedence['^'] = Pow;

	LUT_Sign_precedence['('] = Open_Bracket;
	LUT_Sign_precedence['['] = Open_Bracket;
	LUT_Sign_precedence['{'] = Open_Bracket;
}

void LUTGetEventInit()
{
	LUT_get_event[32] = SPACE;
	LUT_get_event['\0'] = EOS;
	LUT_get_event['$'] = OPER;
	LUT_get_event['('] = OPEN;
	LUT_get_event[')'] = CLOSE;
	LUT_get_event['*'] = OPER;
	LUT_get_event['+'] = OPER;
	LUT_get_event['-'] = OPER;
	LUT_get_event['/'] = OPER;
	LUT_get_event['['] = OPEN;
	LUT_get_event[']'] = CLOSE;
	LUT_get_event['^'] = OPER;
	LUT_get_event['{'] = OPEN;
	LUT_get_event['}'] = CLOSE;
}

void LUTStateTableInit()
{
	LUT_state_table[VALID][VALID_OR_OPEN].action = EventValid_StateValidOpen;
	LUT_state_table[VALID][VALID_OR_OPEN].next_state = OPER_OR_CLOSE;
	LUT_state_table[VALID][OPER_OR_CLOSE].action = TriggerError;
	LUT_state_table[VALID][OPER_OR_CLOSE].next_state = ERROR;
	LUT_state_table[OPER][VALID_OR_OPEN].action = TriggerError;
	LUT_state_table[OPER][VALID_OR_OPEN].next_state = ERROR;
	LUT_state_table[OPER][OPER_OR_CLOSE].action = EventOper_StateOperClose;
	LUT_state_table[OPER][OPER_OR_CLOSE].next_state = VALID_OR_OPEN;
	LUT_state_table[OPEN][VALID_OR_OPEN].action = EventOpen_StateValidOpen;
	LUT_state_table[OPEN][VALID_OR_OPEN].next_state = VALID_OR_OPEN;
	LUT_state_table[OPEN][OPER_OR_CLOSE].action = TriggerError;
	LUT_state_table[OPEN][OPER_OR_CLOSE].next_state = ERROR;
	LUT_state_table[CLOSE][VALID_OR_OPEN].action = TriggerError;
	LUT_state_table[CLOSE][VALID_OR_OPEN].next_state = ERROR;
	LUT_state_table[CLOSE][OPER_OR_CLOSE].action = EventClose_StateOperClose;
	LUT_state_table[CLOSE][OPER_OR_CLOSE].next_state = OPER_OR_CLOSE;
	LUT_state_table[NOT_VALID][VALID_OR_OPEN].action = TriggerError;
	LUT_state_table[NOT_VALID][VALID_OR_OPEN].next_state = ERROR;
	LUT_state_table[NOT_VALID][OPER_OR_CLOSE].action = TriggerError;
	LUT_state_table[NOT_VALID][OPER_OR_CLOSE].next_state = ERROR;
	LUT_state_table[EOS][VALID_OR_OPEN].action = TriggerError;
	LUT_state_table[EOS][VALID_OR_OPEN].next_state = ERROR;
	LUT_state_table[EOS][OPER_OR_CLOSE].action = EventEOS_StateOperClose;
	LUT_state_table[EOS][OPER_OR_CLOSE].next_state = END;
	LUT_state_table[SPACE][VALID_OR_OPEN].action = DoNothingVoid;
	LUT_state_table[SPACE][VALID_OR_OPEN].next_state = VALID_OR_OPEN;
	LUT_state_table[SPACE][OPER_OR_CLOSE].action = DoNothingVoid;
	LUT_state_table[SPACE][OPER_OR_CLOSE].next_state = OPER_OR_CLOSE;
	LUT_state_table[WRONG_BRACKET][VALID_OR_OPEN].action = DoNothingVoid;
	LUT_state_table[WRONG_BRACKET][VALID_OR_OPEN].next_state = ERROR;
	LUT_state_table[WRONG_BRACKET][OPER_OR_CLOSE].action = DoNothingVoid;
	LUT_state_table[WRONG_BRACKET][OPER_OR_CLOSE].next_state = ERROR;
}

void StacksInit()
{
	operator dummy = {0};

	dummy.sign = '$';
	dummy.precedence = Dummy;
	NUM_STACK = StackCreate(100, sizeof(double));
	SIGN_STACK = StackCreate(100, sizeof(operator));
	/*put $ as anchor*/
	StackPush(SIGN_STACK, &dummy);
}

double BracketError(event_pack *event, double num1, double num2)
{
	(void)num1;
	(void)num2;

	printf("Error!! Wrong Coupling of parenthesis !!\n");
	event->event_enum = WRONG_BRACKET;

	return (ERROR);
}

void DoNothingVoid()
{
}

void TriggerError(event_pack *event, void *param)
{
	(void)event;
	(void)param;

	printf("Error!! Undefined Input: %c\n", event->input.operator.sign);
}

void EventValid_StateValidOpen(event_pack *event, void *param)
{
	operator mult = {0};
	double minus_one = -1;
	char mult_oper = '*';
	
	(void)param;


	if(event->input.num < 0)
	{
		mult.sign = mult_oper;
		mult.precedence = Mult_Div;
		StackPush(NUM_STACK, &minus_one);
		StackPush(SIGN_STACK, &mult);
	}
	StackPush(NUM_STACK, &event->input.num);
}


void EventOper_StateOperClose(event_pack *event, void *param)
{
	(void)param;
	PrecCalc(event);
	StackPush(SIGN_STACK, &event->input.operator);
}

void EventOpen_StateValidOpen(event_pack *event, void *param)
{
	(void)param;
	StackPush(SIGN_STACK, &event->input.operator);
}


void EventClose_StateOperClose(event_pack *event, void *param)
{
	int sign_idx = -1;
	int stack_sign = -1;

	(void)param;

	stack_sign = *(int *)StackPeek(SIGN_STACK);
	sign_idx = LUT_parenthesis[(int)event->input.operator.sign];
	while(sign_idx != (stack_sign = *(int *)StackPeek(SIGN_STACK)) && 
		event->event_enum != WRONG_BRACKET)
	{
		LUT_is_braces_error[sign_idx][stack_sign](event, 0 ,0);
	}
	StackPop(SIGN_STACK);
}

void EventEOS_StateOperClose(event_pack *event, void *param)
{
	double result = 0;

	(void)event;
	(void)param;
	result = *(double *)StackPeek(NUM_STACK);
	while(1 < StackSize(NUM_STACK) && event->event_enum != WRONG_BRACKET)
	{
		result = Calc(event, 0, 0);
	}

	LUT_oper[*(int *)StackPeek(SIGN_STACK)](event, 0, 0);

	if(event->event_enum != WRONG_BRACKET)
	{
		printf("result = %f\n", result);
	}
}

void PrecCalc(event_pack *event)
{
	operator *oper = NULL;
	operator event_oper = {0};

	event_oper = event->input.operator;
	oper = StackPeek(SIGN_STACK);
	while(event_oper.precedence <= oper->precedence && 
		event_oper.precedence != Pow)
	{
		Calc(event, 0, 0);
		oper = StackPeek(SIGN_STACK);
	}
}

double Calc(event_pack *event, double num1, double num2)
{
	double result = 0;
	operator *oper = NULL;

	num1 = 0;
	num2 = 0;
	result = *(double *)StackPeek(NUM_STACK);

	oper = StackPeek(SIGN_STACK);
	StackPop(SIGN_STACK);
	num2 = *(double *)StackPeek(NUM_STACK);
	StackPop(NUM_STACK);
	num1 = *(double *)StackPeek(NUM_STACK);
	StackPop(NUM_STACK);
	result = LUT_oper[(int)oper->sign](event, num1, num2);
	StackPush(NUM_STACK, &result);

	return(result);
}


double Multiply(event_pack *event, double num1, double num2)
{
	(void)event;

	return (num1 * num2);
}

double Divide(event_pack *event, double num1, double num2)
{
	(void)event;
	
	return (num1 / num2);
}

double Add(event_pack *event, double num1, double num2)
{
	(void)event;

	return (num1 + num2);
}

double Difference(event_pack *event, double num1, double num2)
{
	(void)event;

	return (num1 - num2);
}

double Power(event_pack *event, double num1, double num2)
{
	(void)event;

	return (pow(num1, num2));
}

double DoNothingVoidDouble()
{
	return (0);
}