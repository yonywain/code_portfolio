#ifndef ILRD_CALC_H
#define ILRD_CALC_H

typedef struct operator
{
	char sign;
	int precedence;
}operator;
/* ( ^ * / + - */
typedef union input
{
	double num;
	struct operator operator;
} input;

typedef struct event_pack
{
	int event_enum;
	input input;
}event_pack;

typedef void (*action_func)(event_pack *event, void *param);
typedef char *(*get_input)(char *math, event_pack *event);
typedef double (*calc)(event_pack *event, double num1, double num2);
typedef double (*is_brace_err)(event_pack *event, double num1, double num2);

void Destroy();
void start();
void LUTPrecedenceInit();
void LUTGetEventInit();
void LUTStateTableInit();
void StacksInit();
void LUTGetEventTypeInit();
void LUTOperInit();
void LUTParenthesisInit();
void LUTIsBraceErrInit();
void IsMathExecInit();

char *GetNum(char *str, event_pack *event);
char *GetSign(char *str, event_pack *event);

void DoNothingVoid();
void TriggerError(event_pack *event, void *param);
void EventValid_StateValidOpen(event_pack *event, void *param);
void EventOper_StateOperClose(event_pack *event, void *param);
void EventOpen_StateValidOpen(event_pack *event, void *param);
void EventClose_StateOperClose(event_pack *event, void *param);
void EventEOS_StateOperClose(event_pack *event, void *param);

void PrecCalc(event_pack *event);
double Calc(event_pack *event, double num1, double num2);
double Multiply(event_pack *event, double num1, double num2);
double Divide(event_pack *event, double num1, double num2);
double Add(event_pack *event, double num1, double num2);
double Difference(event_pack *event, double num1, double num2);
double Power(event_pack *event, double num1, double num2);

double BracketError(event_pack *event, double num1, double num2);
double DoNothingVoidDouble();

#endif   /* ILRD_CALC_H */
