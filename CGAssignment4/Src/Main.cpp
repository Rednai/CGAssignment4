#include "Application.hpp"
#include "Constants.hpp"

int main()
{
	Application application;
	if (!application.Init())
		return ERROR_RETURN;
	application.Loop();
	return SUCCESS_RETURN;
}
