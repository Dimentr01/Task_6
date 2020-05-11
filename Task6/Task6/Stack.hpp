#pragma once

template <typename T1>
struct Stack
{
	T1 value;
	Stack* next;
};

// inserts element at the top
template <typename T1>
void StackPush(Stack<T1>** stack, const T1& value)
{
	Stack<T1>* newValue = new Stack<T1>;
	newValue->value = value;
	newValue->next = *stack;

	*stack = newValue;
}

// accesses the top element from stack
template <typename T1>
T1 StackTop(Stack<T1>* stack)
{
	return stack->value;
}

// removes top element from stack
template <typename T1>
void StackPop(Stack<T1>** stack)
{
	Stack<T1>* tempValue = *stack;

	if (tempValue == nullptr)
		return;

	*stack = tempValue->next;
	delete tempValue;
}

// check whether stack is empty
template <typename T1>
bool StackIsEmpty(Stack<T1>* stack)
{
	if (stack == nullptr)
		return true;
	return false;
}

